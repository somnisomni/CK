using System.Net;
using System.Net.Sockets;
using System.Text;

class UdpEchoClient {
    public static void Main(string[] args) {
        const string SERVERIP = "127.0.0.1";
        const int SERVERPORT = 9100;
        
        byte[] byteBuffer = Encoding.ASCII.GetBytes("UDP Client Test!!!");

        using UdpClient client = new UdpClient();
        try {
            client.Send(byteBuffer, byteBuffer.Length, SERVERIP, SERVERPORT);
            Console.WriteLine("Sent {0} bytes to the server {1}:{2}", byteBuffer.Length, SERVERIP, SERVERPORT);

            IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);
            byte[] recvBuffer = client.Receive(ref remoteEP);
            Console.WriteLine("Received {0} bytes from {1}: {2}", recvBuffer.Length, remoteEP,
                Encoding.ASCII.GetString(recvBuffer, 0, recvBuffer.Length));
        } catch(SocketException e) {
            Console.WriteLine(e.ErrorCode + ": " + e.Message);
        }
    }
}