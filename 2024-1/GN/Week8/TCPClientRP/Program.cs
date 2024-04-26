using System.Net;
using System.Net.Sockets;
using System.Text;

namespace TCPClientRP;

public static class Program {
    private const string SERVERIP = "127.0.0.1";
    private const int SERVERPORT = 9000;
    private const int BUFFERSIZE = 1024;
    
    public static void Main(string[] args) {
        TcpClient client = null;
        NetworkStream netStream = null;

        try {
            client = new TcpClient(SERVERIP, SERVERPORT);
            netStream = client.GetStream();
            
            Console.WriteLine("[TCP] Client initialized.");
        } catch(SocketException e) {
            Console.WriteLine($"Error ({e.ErrorCode}): {e.Message}");
            Environment.Exit(e.ErrorCode);
            return;
        }
        
        byte[] buffer = Encoding.Default.GetBytes("Hello World! TCP client test~");
        try {
            netStream.Write(buffer, 0, buffer.Length);
            Console.WriteLine($"[TCP] Data sent. ({buffer.Length} bytes)");
        } catch(Exception e) {
            Console.WriteLine($"Error while sending data: {e.Message}");
            netStream.Close();
            return;
        }

        try {
            int totalRecv = 0;
            while(totalRecv < buffer.Length) {
                int recv = 0;
                if((recv = netStream.Read(buffer, totalRecv, buffer.Length - totalRecv)) == 0) {
                    Console.WriteLine("[TCP] Connection closed by server.");
                    break;
                }

                totalRecv += recv;
            }

            Console.WriteLine($"[TCP] Data received ({buffer.Length} bytes): {Encoding.Default.GetString(buffer)}");
        } catch(Exception e) {
            Console.WriteLine($"Error while receiving data: {e.Message}");
            return;
        } finally {
            netStream.Close();
            client.Close();
        }
    }
}
