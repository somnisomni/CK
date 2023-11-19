using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Week12_Assignment {
  internal class DontFragment {
    static void Main(string[] args) {
      Socket? sock = null;
      try {
        sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      try {
        Console.WriteLine($"현재 IP_DONTFRAGMENT 값: {sock.GetSocketOption(SocketOptionLevel.IP, SocketOptionName.DontFragment)}");
        sock.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.DontFragment, true);
        Console.WriteLine($"설정된 IP_DONTFRAGMENT 값: {sock.GetSocketOption(SocketOptionLevel.IP, SocketOptionName.DontFragment)}");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      string test = string.Empty;
      for(int i = 0; i < 50; i++) test += "Hello";
      sock.SendTo(Encoding.Default.GetBytes(test), new IPEndPoint(IPAddress.Loopback, 9000));

      sock.Close();
    }
  }
}
