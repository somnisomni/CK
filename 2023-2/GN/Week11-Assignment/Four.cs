using System.Text;
using System.Net;
using System.Net.Sockets;

namespace BroadcastSender {
  class Program {
    static string REMOTEIP = "255.255.255.255"; // 브로드캐스트 주소
    const int REMOTEPORT = 9000;                // 브로드캐스트 리모트 포트
    const int BUFSIZE = 512;                    // 데이터 버퍼 크기

    static void Main(string[] args) {
      int retval;
      // 명령행 인수가 있으면 IP 주소로 사용
      if(args.Length > 0) REMOTEIP = args[0];

      Socket? sock = null;
      try {
        // 소켓 생성 (UDP)
        sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

        // 브로드캐스팅 활성화 (브로드캐스트 시 옵션 필수)
        sock.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Broadcast, true);
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      // 소켓 주소 객체 초기화
      IPEndPoint serveraddr = new(IPAddress.Parse(REMOTEIP), REMOTEPORT);

      // 브로드캐스트 데이터 보내기
      while(true) {
        // 데이터 입력
        Console.Write("\n[보낼 데이터] ");
        string data = Console.ReadLine()!;
        if(data.Length == 0) break;

        try {
          // 데이터 보내기 (최대 길이를 BUFSIZE로 제한)
          byte[] senddata = Encoding.Default.GetBytes(data);  // 기본 인코딩으로 데이터를 바이트 배열로 변환
          int size = senddata.Length;
          if(size > BUFSIZE) size = BUFSIZE;

          retval = sock.SendTo(senddata, 0, size, SocketFlags.None, serveraddr);
          Console.WriteLine("[UDP] {0}바이트를 보냈습니다.", retval);
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