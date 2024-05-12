using System.Net;
using System.Net.Sockets;

class UdpEchoServer {
    private const int SERVERPORT = 9100;
    
    public static void Main(string[] args) {
        UdpClient client = null;

        try {
            client = new UdpClient(SERVERPORT);
            Console.WriteLine(" * UDP server has started on port {0}", SERVERPORT);
        } catch(SocketException e) {
            Console.WriteLine(e.ErrorCode + ": " + e.Message);
            Environment.Exit(e.ErrorCode);
        }
        
        IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);

        for(;;) {
            try {
                byte[] byteBuffer = client.Receive(ref remoteEP);
                Console.WriteLine(" * Received {0} bytes from {1}", byteBuffer.Length, remoteEP.ToString());

                client.Send(byteBuffer, byteBuffer.Length, remoteEP);
                Console.WriteLine(" * Echoed {0} bytes", byteBuffer.Length);
            } catch(SocketException e) {
                Console.WriteLine(e.ErrorCode + ": " + e.Message);
            }
        }
    }
}