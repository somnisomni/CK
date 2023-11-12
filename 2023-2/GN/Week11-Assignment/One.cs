using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UDPServer {
  class Program {
    const int SERVERPORT = 9000; // 서버 포트
    const int BUFSIZE = 512;     // 데이터 버퍼 크기

    static void Main(string[] args) {
      int retval;
      Socket? sock = null;

      try {
        // 소켓 생성 (UDP)
        sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

        // Bind(), 아무 주소든 접속 허용
        sock.Bind(new IPEndPoint(IPAddress.Any, SERVERPORT));
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      Console.WriteLine("[UDP SERVER STARTED]");

      // 데이터 통신에 사용할 변수
      byte[] buf = new byte[BUFSIZE];
      while(true) {
        try {
          // 데이터 받기
          IPEndPoint anyaddr = new(IPAddress.Any, 0);
          EndPoint peeraddr = anyaddr;
          retval = sock.ReceiveFrom(buf, BUFSIZE, SocketFlags.None, ref peeraddr);

          // 받은 데이터 출력
          Console.WriteLine("[UDP/{0}:{1}] {2}", ((IPEndPoint)peeraddr).Address, ((IPEndPoint)peeraddr).Port, Encoding.Default.GetString(buf, 0, retval));

          // 데이터를 보내온 지점으로 다시 데이터 보내기
          sock.SendTo(buf, 0, retval, SocketFlags.None, peeraddr);
        } catch(Exception e) {
          Console.WriteLine(e.Message);
          break;
        }
      }

      // 소켓 닫기
      sock.Close();
    }
  }
}