using System.Net;
using System.Net.Sockets;
using System.Text;

class Program {
    private const int SERVERPORT = 9000;
    private const int BUFFERSIZE = 512;
    
    public static void Main(string[] args) {
        Socket? socket = null;
        int retval;

        try {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            socket.Bind(new IPEndPoint(IPAddress.Any, SERVERPORT));
        } catch(Exception e) {
            Console.Error.WriteLine(e.Message);
            Environment.Exit(1);
        }
        
        Console.WriteLine(" * UDP Server has started.");

        byte[] buffer = new byte[BUFFERSIZE];
        while(true) {
            try {
                EndPoint peerAddr = new IPEndPoint(IPAddress.Any, 0);
                retval = socket.ReceiveFrom(buffer, BUFFERSIZE, SocketFlags.None, ref peerAddr);
                
                string data = Encoding.Default.GetString(buffer, 0, retval);
                Console.WriteLine("[UDP/{0}:{1}] {2}", ((IPEndPoint)peerAddr).Address, ((IPEndPoint)peerAddr).Port, data);

                socket.SendTo(buffer, retval, SocketFlags.None, peerAddr);
            } catch(Exception e) {
                Console.Error.WriteLine(e.Message);
                break;
            }
        }
        
        socket.Close();
    }
}