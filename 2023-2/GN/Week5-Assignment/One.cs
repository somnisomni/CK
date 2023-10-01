// CK 2023-2 / Introduction to Game Network / Week5 Assignment / #1 TCP 서버

using System.Text;
using System.Net;
using System.Net.Sockets;

namespace TCPServer {
  class Program {
    const int SERVERPORT = 9000;  // 서버에 할당될 포트 번호
    const int BUFSIZE = 512;      // 송수신 데이터 버퍼 크기

    static void Main(string[] args) {
      int retval;  // 메서드 반환값 저장용

      Socket? listen_sock = null;  // 서버 소켓
      try {
        // 소켓 생성 (TCP)
        listen_sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        // Bind()
        listen_sock.Bind(new IPEndPoint(IPAddress.Any, SERVERPORT));
        // "모든 IP 영역에서 지정한 포트 번호로 들어오는 연결을 듣겠다"

        // Listen()
        listen_sock.Listen(int.MaxValue);
        // (2^32개의 연결 대기 큐를 가지고) 들어오는 연결 듣기

        Console.WriteLine(" * Echo Server 가 정상 동작을 시작했습니다.");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      // 데이터 통신에 사용할 변수 선언
      Socket? client_sock = null;       // 연결된 클라이언트 소켓
      IPEndPoint? clientaddr = null;    // 연결된 클라이언트의 IP주소/포트 정보
      byte[] buf = new byte[BUFSIZE];   // 송수신 버퍼 바이트 배열

      // 서버 루프
      while(true) {
        try {
          // accept()
          client_sock = listen_sock.Accept();
          // 들어오는 연결을 수락하고 클라이언트 소켓 변수에 할당

          // 접속한 클라이언트 정보 출력
          clientaddr = (IPEndPoint?)client_sock.RemoteEndPoint;  // 원격(클라이언트) 접속지점
          Console.WriteLine("\n[TCP 서버] 클라이언트 접속: IP 주소={0}, 포트번호={1}",
              clientaddr?.Address, clientaddr?.Port);

          // 클라이언트와 데이터 통신
          while(true) {
            // 데이터 받기
            retval = client_sock.Receive(buf, BUFSIZE, SocketFlags.None);
            if(retval == 0)
              break;
            // 반환값이 0이면 송수신 종료

            // 받은 데이터 출력
            Console.WriteLine("[TCP/{0}:{1}] {2}",
              clientaddr?.Address, clientaddr?.Port,
              Encoding.Default.GetString(buf, 0, retval));

            // 데이터 보내기
            client_sock.Send(buf, retval, SocketFlags.None);
          }

          // 소켓 닫기
          client_sock.Close();
          Console.WriteLine("[TCP 서버] 클라이언트 종료: IP 주소={0}, 포트번호={1}",
              clientaddr?.Address, clientaddr?.Port);
        } catch(Exception e) {
          Console.WriteLine(e.Message);
          break;
        }
      }

      // 서버 소켓 닫기
      listen_sock.Close();
    }
  }
}
