using System.Net.Sockets;
using System.Text;

class TcpEchoClient {
    public static void Main(string[] args) {
        const string SERVERIP = "127.0.0.1";
        const int SERVERPORT = 9000;

        byte[] byteBuffer = Encoding.ASCII.GetBytes("TCP Client Connect Test!!!");

        TcpClient client = null;
        NetworkStream stream = null;

        try {
            client = new TcpClient(SERVERIP, SERVERPORT);
            Console.WriteLine("Connected to server, sending echo string...");

            stream = client.GetStream();
            stream.Write(byteBuffer, 0, byteBuffer.Length);
            Console.WriteLine("Sent {0} bytes to server", byteBuffer.Length);

            int totalBytesReceived = 0;
            int bytesReceived = 0;

            while(totalBytesReceived < byteBuffer.Length) {
                if((bytesReceived =
                       stream.Read(byteBuffer, totalBytesReceived, byteBuffer.Length - totalBytesReceived)) == 0) {
                    Console.WriteLine("Connection closed prematurely");
                    break;
                }

                totalBytesReceived += bytesReceived;
            }

            Console.WriteLine("Received {0} bytes from server: {1}", totalBytesReceived,
                Encoding.ASCII.GetString(byteBuffer, 0, totalBytesReceived));
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }
        
        stream?.Close();
        client?.Close();
    }
}