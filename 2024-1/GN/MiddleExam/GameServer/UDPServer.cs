using System.Net;
using System.Net.Sockets;
using System.Text;
using GameServer.Messages;
using GameServer.Messages.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace GameServer;

public sealed class UDPServer: IDisposable {
    private const string LISTEN_HOST = "127.0.0.1";
    private const int PORT = 30303;
    private static readonly IPEndPoint LISTEN_ENDPOINT = new(IPAddress.Parse(LISTEN_HOST), PORT);

    private static UDPServer? _instance = null;
    public static UDPServer Instance => _instance ??= new UDPServer();
    
    private readonly object lockObj = new();
    private UdpClient? listener = null;
    private readonly Dictionary<uint, IPEndPoint> clients = new();
    private readonly Queue<(uint clientId, byte[] data)> sendQueue = new();
    
    private readonly CancellationTokenSource threadCancelToken = new();
    private Thread receiveThread = null;
    private Thread sendThread = null;

    public event EventHandler<JObject>? OnReceive;
    public event EventHandler? OnSendComplete;

    private UDPServer() {
        Console.WriteLine("[UDP] Server instance created.");
        Startup();
    }
    ~UDPServer() {
        Dispose();
    }

    private void Startup() {
        /*** === Abort startup if already initialized === ***/
        if(listener != null) {
            Console.WriteLine("[UDP/WARN] UDP server already initialized.");
            return;
        }
        
        /* === Initialize UDP server(listener) instance === */
        listener = new UdpClient(LISTEN_ENDPOINT);
        Console.WriteLine($"[UDP] Server started on port {((IPEndPoint?) listener.Client.LocalEndPoint)?.Address.ToString()}:{PORT}.");

        /* === Start receive/send threads === */
        receiveThread = new Thread(ReceiveThreadFunc);
        sendThread = new Thread(SendThreadFunc);
        
        receiveThread.Start();
        sendThread.Start();
        
        /* === Register default events === */
        OnReceive += OnClientShutdown;
    }

    private void ReceiveThreadFunc() {
        while(true) {
            /*** === Thread loop condition check === ***/
            if(listener == null || listener.Available <= 0) {
                if(threadCancelToken.Token.IsCancellationRequested) {
                    break;
                }
                
                Thread.Sleep(1000 / 120);
                continue;
            }

            /*** === Receive data === ***/
            IPEndPoint remoteEndPoint = new(IPAddress.Any, PORT);
            byte[] data = listener.Receive(ref remoteEndPoint);
            Console.WriteLine($"[UDP] Received, byte length = {data.Length}, from {remoteEndPoint} \n" 
                            + $"      Data: {Encoding.UTF8.GetString(data)}");

            if(Encoding.UTF8.GetString(data).Equals(Constants.ClientIdRequestString)) {
                uint randomClientId = 0;
                do {
                    randomClientId = (uint) new Random().Next(1, int.MaxValue);
                } while(clients.ContainsKey(randomClientId));
                
                clients.Add(randomClientId, remoteEndPoint);
                QueueSend(randomClientId, new AcquireClientIdResponse {
                    ClientId = randomClientId
                });
                Console.WriteLine($"[UDP] Client {randomClientId} registered, sending ID back to client");

                continue;
            }

            if(clients.ContainsValue(remoteEndPoint)) {
                OnReceive?.Invoke(this, JObject.Parse(Encoding.UTF8.GetString(data)));
            }
        }
    }

    private void SendThreadFunc() {
        while(true) {
            /*** === Thread loop condition check === ***/
            int sendQueueCount;
            lock(lockObj) {
                sendQueueCount = sendQueue.Count;
            }

            if(listener == null || sendQueueCount <= 0) {
                if(threadCancelToken.Token.IsCancellationRequested) {
                    break;
                }
                
                Thread.Sleep(1000 / 120);
                continue;
            }

            /*** === Send data from queue === ***/
            (uint clientId, byte[] data) sendData;
            lock(lockObj) {
                sendData = sendQueue.Dequeue();
            }
            
            if(sendData.clientId == 0) {
                Console.WriteLine($"[UDP] Sending {sendData.data.Length} byte(s) to ALL clients \n" 
                                + $"      Data: {Encoding.UTF8.GetString(sendData.data)}");
                
                foreach(IPEndPoint client in clients.Values) {
                    listener.Send(sendData.data, client);
                }
                OnSendComplete?.Invoke(this, EventArgs.Empty);
            } else {
                if(clients.TryGetValue(sendData.clientId, out IPEndPoint? client)) {
                    Console.WriteLine($"[UDP] Sending {sendData.data.Length} byte(s) to client {sendData.clientId} ({client}) \n" 
                                    + $"      Data: {Encoding.UTF8.GetString(sendData.data)}");
                    
                    listener.Send(sendData.data, client);
                    OnSendComplete?.Invoke(this, EventArgs.Empty);
                } else {
                    Console.WriteLine($"[UDP/WARN] Client {sendData.clientId} not registered, failed to send.");
                }
            }
        }
    }
    
    private void QueueSend(uint clientId, byte[] data) {
        lock(lockObj) {
            sendQueue.Enqueue((clientId, data));
        }
    }

    public void QueueSend<T>(uint clientId, T message) where T: MessageBase {
        QueueSend(
            clientId: clientId,
            data: Encoding.UTF8.GetBytes(
                JsonConvert.SerializeObject(
                    MessageFactory.Instance.CreateMessage(message, clientId)))
        );
    }

    private void OnClientShutdown(object? sender, JObject data) {
        if(data.ParseMessage<NotifyClientShutdown>() is not { } message
           || !clients.ContainsKey(message.ClientId)) return;
        
        clients.Remove(message.ClientId);
        Console.WriteLine($"[UDP] Client {message.ClientId} disconnected, removed from client list.");
    }
    
    public void Dispose() {
        threadCancelToken.Cancel();
        
        listener?.Close();
        listener?.Dispose();
        listener = null;
        
        clients.Clear();
        
        _instance = null;
        GC.SuppressFinalize(this);
    }
}
