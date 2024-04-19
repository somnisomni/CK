using System.Net;
using System.Net.Sockets;
using System.Text;

namespace GameServer;

public sealed class UDPServer: IDisposable {
    private const int PORT = 30303;

    private static UDPServer? _instance = null;
    public static UDPServer Instance => _instance ??= new UDPServer();

    private readonly object lockObj = new();
    private UdpClient? udp = null;
    private Dictionary<uint, Socket> clients = new();
    private Thread receiveThread;
    private Thread sendThread;
    private Queue<(uint clientId, byte[] data)> sendQueue = new();

    public event EventHandler OnReceive;
    public event EventHandler OnSendComplete;

    private UDPServer() {
        Console.WriteLine("[UDP] Server instance created.");
        Startup();
    }
    ~UDPServer() {
        Dispose();
    }

    private void Startup() {
        if(udp != null) {
            Console.WriteLine("[UDP/WARN] UDP server already initialized.");
            return;
        }
        
        udp = new UdpClient(PORT, AddressFamily.InterNetwork);
        Console.WriteLine($"[UDP] Server started on port {((IPEndPoint?) udp.Client.LocalEndPoint)?.Address.ToString()}:{PORT}.");

        receiveThread = new Thread(ReceiveThreadFunc);
        sendThread = new Thread(SendThreadFunc);
    }

    private void ReceiveThreadFunc() {
        while(true) {
            IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, PORT);
            byte[] data = udp.Receive(ref remoteEP);
            Console.WriteLine($"[UDP] Received, byte length = {data.Length}, from {remoteEP}");
        }
        
        OnReceive.Invoke(this, EventArgs.Empty);
    }

    private void SendThreadFunc() {
        
        OnSendComplete.Invoke(this, EventArgs.Empty);
    }

    public void Dispose() {
        udp?.Close();
        udp?.Dispose();
    }
}
