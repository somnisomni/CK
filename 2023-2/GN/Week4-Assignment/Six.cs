// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #6 3주차 TCPServer.cpp를 직접 C#로 변환/이해
// 202313259 최민규

using System.Net;
using System.Net.Sockets;
using System.Text;

namespace AssignmentTCPServer {
  class Program {
    private static ushort SERVER_PORT = 5555;
    private const ushort BUFFER_SIZE = 512;

    static void Main(string[] args) {
      /* 소켓 초기화 */
      Socket? socket = null;
      try {
        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);  // TCP 소켓 생성
        Console.WriteLine("소켓 생성 성공");
      } catch {
        Console.WriteLine("소켓 초기화 중 오류 발생");
        Environment.Exit(1);
      }

      /* 서버 바인드 */
      Console.WriteLine("서버 바인딩...");
      try {
        EndPoint serverEP = new IPEndPoint(
          BitConverter.ToInt32(IPAddress.Any.GetAddressBytes()),
          SERVER_PORT);         // 모든 IP 주소 영역에서 서버 포트로의 연결을 가리키는 IPEndPoint 객체 생성
        socket.Bind(serverEP);  // 해당 엔드포인트에 서버 소켓 바인딩
      } catch {
        Console.WriteLine("서버 바인딩 중 오류 발생");
        Environment.Exit(1);
      }

      /* 리스닝 */
      Console.WriteLine("서버 리스닝...");
      try {
        socket.Listen((int)SocketOptionName.MaxConnections);  // 엔드포인트에서 들어오는 소켓 연결 리스닝
      } catch {
        Console.WriteLine("서버 리스닝 중 오류 발생");
        Environment.Exit(1);
      }

      /* 서버 루프 */
      Socket? client = null;  // 서버에 연결한 클라이언트의 소켓
      bool shutdown = false;  // 프로그램 종료 플래그

      while(!shutdown) {
        Console.WriteLine();

        /* 클라이언트 연결 수락 */
        try {
          client = socket.Accept();  // 들어오는 연결을 수락하고 클라이언트 소켓을 할당
        } catch {
          Console.WriteLine("클라이언트 연결 실패");
          Environment.Exit(1);
        }

        /* 클라이언트 정보 출력 */
        IPEndPoint clientEP = (IPEndPoint)client.RemoteEndPoint!;  // 클라이언트에 대한 엔드포인트
        string clientIP = clientEP.Address.ToString();              // 클라이언트 IP
        int clientPort = clientEP.Port;                             // 클라이언트 포트
        Console.WriteLine($"[TCP 서버] 클라이언트 접속: IP 주소={clientIP}, 포트={clientPort}");

        /* 클라이언트와 데이터 송수신 */
        while(true) {
          /* 데이터 수신 */
          byte[] bytes = new byte[BUFFER_SIZE];  // 버퍼 사이즈만큼 바이트 배열 생성
          int recvSize;                          // 수신 바이트 수
          try {
            recvSize = client.Receive(bytes, SocketFlags.None);  // 클라이언트로부터 데이터를 바이트 배열로 수신
          } catch {
            Console.WriteLine("데이터 수신 중 오류 발생");
            break;
          }

          /* 수신 데이터 출력 */
          string recvData = Encoding.UTF8.GetString(bytes, 0, recvSize);  // 받은 바이트 배열을 문자열로 변환
          Console.WriteLine($"[TCP/{clientIP}:{clientPort}] {recvData}"); // 출력

          /* 데이터 전송 (에코) */
          try {
            client.Send(bytes, recvSize, SocketFlags.None);  // 받은 바이트 배열을 그대로 클라이언트로 전송 (에코)
          } catch {
            Console.WriteLine("데이터 전송 중 오류 발생");
            break;
          }

          /* 수신 데이터가 "shutdown"일 경우 프로그램 종료 플래그 설정 */
          if(recvData.Equals("shutdown")) {
            Console.WriteLine("서버 종료");
            shutdown = true;
            break;
          }
        }

        /* 클라이언트 소켓 종료 */
        client.Close();
      }

      /* 서버 소켓 종료 */
      socket.Close();

      /* 프로그램 종료 */
      Console.WriteLine("프로그램을 종료하려면 아무 키나 누르세요.");
      Console.ReadKey();
    }
  }
}
