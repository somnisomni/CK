using System.Net.Sockets;

namespace InitSocket {
    class Program {
        static void Main(string[] args) {
            Socket sock = null;
            try {
                sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                Console.WriteLine("[알림] 소켓 생성 성공");
            } catch(Exception e) {
                Console.WriteLine(e.Message);
                Environment.Exit(1);
            }

            sock.Close();
        }
    }
}
