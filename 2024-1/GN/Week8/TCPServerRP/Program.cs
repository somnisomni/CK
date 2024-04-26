using System.Net;
using System.Net.Sockets;

namespace TCPServerRP;

public static class Program {
    private const int SERVERPORT = 9000;
    private const int BUFFERSIZE = 1024;
    
    public static void Main(string[] args) {
        TcpListener listener = null;

        try {
            listener = new TcpListener(IPAddress.Any, SERVERPORT);
            listener.Start();
            
            Console.WriteLine($"TCP server started on port {SERVERPORT}");
        } catch(SocketException e) {
            Console.WriteLine($"Error ({e.ErrorCode}): {e.Message}");
            Environment.Exit(e.ErrorCode);
            return;
        }

        byte[] buffer = new byte[BUFFERSIZE];
        int recv = 0;
        while(true) {
            TcpClient client = null;
            NetworkStream netStream = null;

            try {
                client = listener.AcceptTcpClient();
                netStream = client.GetStream();
                
                Console.WriteLine($"Client connected: {client.Client.RemoteEndPoint}");

                int echoRecv = 0;
                while((recv = netStream.Read(buffer, 0, buffer.Length)) > 0) {
                    netStream.Write(buffer, 0, recv);
                    echoRecv += recv;
                }
                
                Console.WriteLine($"Echoed {echoRecv} bytes to {client.Client.RemoteEndPoint}");
            } catch(Exception e) {
                Console.WriteLine($"Error while accepting client: {e.Message}");
                netStream.Close();
                continue;
            }
        }
    }
}
