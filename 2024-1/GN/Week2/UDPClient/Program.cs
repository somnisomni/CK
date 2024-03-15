using System.Net;
using System.Net.Sockets;
using System.Text;

class Program {
    private const string SERVERIP = "192.168.110.232";
    private const int  SERVERPORT = 9000;
    private const int  BUFFERSIZE = 512;
    
    public static void Main(string[] args) {
        Socket? socket = null;
        int retval;

        try {
            socket = new(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        } catch(Exception e) {
            Console.Error.WriteLine(e.Message);
            Environment.Exit(1);
        }
        
        Console.WriteLine(" * UDP Client has started.");

        byte[] buffer = new byte[BUFFERSIZE];
        IPEndPoint serverAddr = new(IPAddress.Parse(SERVERIP), SERVERPORT);
        while(true) {
            Console.Write("Input> ");
            string input = Console.ReadLine()!;
            if(input.Length == 0) break;
            
            try {
                byte[] data = Encoding.Default.GetBytes(input);
                int size = data.Length;
                if(size > BUFFERSIZE) size = BUFFERSIZE;
                retval = socket.SendTo(data, size, SocketFlags.None, serverAddr);
                Console.WriteLine("[UDP Client] {0} bytes sent.", retval);
                
                EndPoint peerAddr = new IPEndPoint(IPAddress.Any, 0);
                retval = socket.ReceiveFrom(buffer, retval, SocketFlags.None, ref peerAddr);
                if(!((IPEndPoint) peerAddr).Equals(serverAddr)) throw new Exception("Server address mismatch.");
                string recvData = Encoding.Default.GetString(buffer, 0, retval);
                Console.WriteLine("[UDP/{0}:{1}] {2}", ((IPEndPoint)peerAddr).Address, ((IPEndPoint)peerAddr).Port, recvData);
            } catch(Exception e) {
                Console.Error.WriteLine(e.Message);
                break;
            }
        }

        socket.Close();
    }
}