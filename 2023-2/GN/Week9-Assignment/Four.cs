using System.Text;
using System.Net;
using System.Net.Sockets;

namespace ThreadTCPServer {
  class Four {
    const int SERVERPORT = 9000;
    const int BUFSIZE = 512;

    // 클라이언트와 데이터 통신 (스레드 함수)
    static void ProcessClient(object arg) {
      int retval;                        // 받은 데이터 크기
      Socket client_sock = (Socket)arg;  // 클라이언트 소켓 (arg로부터 받음)
      IPEndPoint clientaddr;             // 클라이언트의 엔드포인트 정보
      byte[] buf = new byte[BUFSIZE];    // 받은 데이터 버퍼

      // 클라이언트 정보 얻기
      clientaddr = (IPEndPoint)client_sock.RemoteEndPoint;

      while(true) {
        try {
          // 데이터 받기
          retval = client_sock.Receive(buf, BUFSIZE, SocketFlags.None);
          if(retval == 0)
            break;

          // 받은 데이터 출력
          Console.WriteLine("[TCP/{0}:{1}] {2}",
            clientaddr.Address, clientaddr.Port,
            Encoding.Default.GetString(buf, 0, retval));

          // 데이터 보내기
          client_sock.Send(buf, retval, SocketFlags.None);
        } catch(Exception e) {
          Console.WriteLine(e.Message);
          break;
        }
      }

      // 소켓 닫기
      client_sock.Close();
      Console.WriteLine("[TCP 서버] 클라이언트 종료: IP 주소={0}, 포트 번호={1}",
        clientaddr.Address, clientaddr.Port);
    }
    static void Main(string[] args) {
      Socket listen_sock = null;

      try {
        // 소켓 생성
        listen_sock = new Socket(AddressFamily.InterNetwork,
          SocketType.Stream, ProtocolType.Tcp);

        // Bind()
        listen_sock.Bind(new IPEndPoint(IPAddress.Any, SERVERPORT));

        // Listen()
        listen_sock.Listen(Int32.MaxValue);
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      Console.WriteLine(" * Echo Server 가 정상 동작을 시작했습니다.");

      // 데이터 통신에 사용할 변수
      Socket client_sock = null;
      Thread hThread;
      while(true) {
        try {
          // accept()
          client_sock = listen_sock.Accept();

          // 접속한 클라이언트 정보 출력
          IPEndPoint clientaddr = (IPEndPoint)client_sock.RemoteEndPoint;
          Console.WriteLine("\n[TCP 서버] 클라이언트 접속: IP 주소={0}, 포트 번호={1}",
            clientaddr.Address, clientaddr.Port);

          // 현재 클라이언트로부터 데이터를 받고 보내는 스레드 생성
          hThread = new Thread(ProcessClient);
          hThread.Start(client_sock);
        } catch(Exception e) {
          Console.WriteLine(e.Message);
          break;
        }
      }

      // 소켓 닫기
      listen_sock.Close();
    }
  }
}
