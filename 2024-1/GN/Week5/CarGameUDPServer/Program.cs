using System.Net;
using System.Net.Sockets;
using System.Text;

namespace CarGameUDPServer;

class Program {
    public static void Main(string[] args) {
        var serverThread = new Thread(ServerFunc) {
            IsBackground = true
        };
        serverThread.Start();

        Console.WriteLine(" *** Car Game UDP Server *** ");
        Console.WriteLine("Press enter to shutdown...");
        Console.ReadLine();
        Environment.Exit(0);
    }

    private static void ServerFunc(object? arg) {
        using Socket sock = new(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        IPEndPoint endPoint = new(IPAddress.Any, 10200);
        
        sock.Bind(endPoint);
        Console.WriteLine(" - UDP server is running...");

        byte[] buff = new byte[1024];
        EndPoint clientEP = new IPEndPoint(IPAddress.None, 0);
        
        while(true) {
            int recv = sock.ReceiveFrom(buff, ref clientEP);
            string txt = Encoding.Default.GetString(buff, 0, recv);
            Console.WriteLine($" - Received: {txt}");
            
            sock.SendTo(Encoding.Default.GetBytes($"server OK: {txt}"), clientEP);
        }
    }
}
