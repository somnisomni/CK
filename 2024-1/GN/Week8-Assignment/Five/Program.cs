using System.Net;
using System.Net.Sockets;

class TcpEchoServer {
    private const int BUFFERSIZE = 32;
    private const int PORT = 9000;

    public static void Main() {
        TcpListener listener = null;

        try {
            listener = new TcpListener(IPAddress.Any, PORT);
            listener.Start();
            Console.WriteLine(" * TCP server has started on port {0}", PORT);
        } catch(SocketException e) {
            Console.WriteLine(e.ErrorCode + ": " + e.Message);
            Environment.Exit(e.ErrorCode);
        }

        byte[] recvBuffer = new byte[BUFFERSIZE];
        int bytesReceived = 0;

        for(;;) {
            TcpClient client = null;
            NetworkStream stream = null;
            
            try {
                client = listener.AcceptTcpClient();
                stream = client.GetStream();
                Console.WriteLine(" * Connection from {0}, handling client", client.Client.RemoteEndPoint);

                int totalBytesEchoed = 0;
                while((bytesReceived = stream.Read(recvBuffer, 0, recvBuffer.Length)) > 0) {
                    stream.Write(recvBuffer, 0, bytesReceived);
                    totalBytesEchoed += bytesReceived;
                }

                Console.WriteLine(" * Echoed {0} bytes.", totalBytesEchoed);
            } catch(Exception e) {
                Console.WriteLine(e.Message);
            }
            
            stream?.Close();
            client?.Close();
        }
    }
}