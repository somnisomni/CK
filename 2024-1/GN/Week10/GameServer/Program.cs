using System.Net;
using System.Net.Sockets;
using System.Text;

namespace GameServer;

public class Program {
    public static void Main(string[] args) {
        Thread serverThread = new(ServerFunc);
        serverThread.IsBackground = true;
        serverThread.Start();
        Thread.Sleep(500);
        
        Console.WriteLine(" * Neko game server * ");
        Console.WriteLine(" Press any key to exit");
        Console.WriteLine();
        
        Console.ReadKey();
    }

    private static void ServerFunc(object obj) {
        Socket sock = new(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        IPEndPoint endPoint = new(IPAddress.Any, 10200);

        sock.Bind(endPoint);

        byte[] recvBuffer = new byte[256];
        EndPoint clientEndPoint = new IPEndPoint(IPAddress.None, 0);
        
        while (true) {
            int recvSize = sock.ReceiveFrom(recvBuffer, ref clientEndPoint);
            string recvData = Encoding.UTF8.GetString(recvBuffer, 0, recvSize);
            Console.WriteLine($"[Client] RECV from {clientEndPoint} : {recvData}");
            
            byte[] sendData = Encoding.UTF8.GetBytes(recvData);
            sock.SendTo(sendData, clientEndPoint);
        }
    }
}
