// CK 2023-2 / Introduction to Game Network / Week5 Assignment / #2 TCP 클라이언트

using System.Text;
using System.Net.Sockets;

namespace TCPClient {
  class Program {
    static string SERVERIP = "127.0.0.1";  // 접속할 서버의 IP 주소
    const int SERVERPORT = 9000;           // 접속할 서버의 포트 번호
    const int BUFSIZE = 512;               // 송수신 데이터 버퍼 크기

    static void Main(string[] args) {
      int retval;  // 메서드 반환값 저장용

      // 명령행 인수가 있으면 IP 주소로 사용
      if(args.Length > 0)
        SERVERIP = args[0];

      Socket? sock = null;  // 클라이언트 소켓
      try {
        // 소켓 생성 (TCP)
        sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        // Connect()
        sock.Connect(SERVERIP, SERVERPORT);
        // 서버 IP:포트로 접속 시도

        Console.Write(" * Client 프로그램이 Server 에 정상적으로 연결되었습니다. ");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      // 데이터 통신에 사용할 변수 선언
      byte[] buf = new byte[BUFSIZE];  // 송수신 버퍼 바이트 배열

      // 서버와 데이터 통신
      while(true) {
        // 데이터 입력
        Console.Write("\n[보낼 데이터] ");
        string? data = Console.ReadLine();
        if(data == null || data.Length == 0)
          break;
        // 유효한 입력이 아닐 경우 통신 종료

        try {
          // 데이터 보내기 (최대 길이를 BUFSIZE로 제한)
          byte[] senddata = Encoding.Default.GetBytes(data);  // string을 byte array로 변환
          int size = senddata.Length;
          if(size > BUFSIZE)
            size = BUFSIZE;
          retval = sock.Send(senddata, 0, size, SocketFlags.None);
          Console.WriteLine("[TCP 클라이언트] {0}바이트를 보냈습니다.", retval);

          // 데이터 받기
          retval = ReceiveN(sock, buf, retval, SocketFlags.None);
          if(retval == 0)
            break;
          // 반환값이 0이면 송수신 종료

          // 받은 데이터 출력
          Console.WriteLine( "[TCP 클라이언트] {0}바이트를 받았습니다.", retval);
          Console.WriteLine("[받은 데이터] {0}", Encoding.Default.GetString(buf, 0, retval));  // byte array를 string으로 변환하고 출력
        } catch(Exception e) {
          Console.WriteLine(e.Message);
          break;
        }
      }

      // 소켓 닫기
      sock.Close();
    }

    // C/C++, Python과 달리 데이터 수신 소켓 함수가 MSG_WAITALL
    // 플래그를 지원하지 않으므로 해당 기능을 직접 구현한다.
    static int ReceiveN(Socket sock, byte[] buf, int len, SocketFlags flags) {
      int received;       // 수신 바이트 수
      int offset = 0;     // 수신 오프셋
      int left = len;     // 남은 바이트 수
      
      while(left > 0) {   // 수신받아야 할 바이트가 남아있다면  (#1)
        try {
          received = sock.Receive(buf, offset, left, flags);
          // 남은 바이트 수만큼의 데이터를 수신받고 버퍼에 오프셋 위치부터 시작하여 데이터 저장

          if(received == 0)
            break;
          // 수신 데이터가 없어 반환값이 0이면 수신 종료  (#2)

          left -= received;
          offset += received;
          // 남은 바이트 수는 수신한 바이트 수만큼 빼주고,
          // 오프셋은 수신한 바이트 수만큼 증가
        } catch {
          // 수신 오류  (#3)
          throw;
        }
      }

      // 실제로 받은 바이트 수를 반환
      return len - left;
    }
  }
  // MSG_WAITALL의 의미 (참고: https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-recv)
  //                           https://man7.org/linux/man-pages/man2/recv.2.html
  // : 데이터를 전부 수신받을 때까지 대기(blocking)하겠다는 의미.
  //   다음 경우 중 한 가지의 이벤트라도 발생되면 데이터가 전부 수신되지 않더라도 대기를 종료하고 반환.
  //      1. 수신 버퍼에 데이터가 완전히 가득 찬 경우
  //      2. 연결이 종료된 경우
  //      3. 수신 요청이 취소되거나 오류가 발생한 경우
}
