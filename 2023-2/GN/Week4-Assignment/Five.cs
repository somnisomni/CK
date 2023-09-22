// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #5 3주차 TCPClient.cpp를 직접 C#로 변환/이해

using System.Net;
using System.Net.Sockets;
using System.Text;

namespace AssignmentTCPClient {
  class Program {
    private static string SERVER_IP = "127.0.0.1";
    private static ushort SERVER_PORT = 5555;
    private const ushort BUFFER_SIZE = 512;

    static void Main(string[] args) {
      // 명령줄에 인수가 있으면 IP 주소로 사용
      // C#에서는 args에 프로그램 경로가 포함되어 있지 않아 0번 인덱스부터 사용 가능
      if(args.Length >= 1) SERVER_IP = args[0];

      /* 소켓 초기화 */
      Socket? socket = null;
      try {
        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);  // TCP 소켓 생성
        Console.WriteLine("소켓 생성 성공");
      } catch {
        Console.WriteLine("소켓 초기화 중 오류 발생");
        Environment.Exit(1);
      }

      /* 서버 연결 */
      Console.WriteLine("서버 연결 중...");
      try {
        IPAddress serverAddr = IPAddress.Parse(SERVER_IP);  // 서버 IP 문자열로 IPAddress 객체 생성
        socket.Connect(serverAddr, SERVER_PORT);            // 서버에 연결
      } catch {
        Console.WriteLine("서버 연결 중 오류 발생");
        Environment.Exit(1);
      }
      Console.WriteLine("** 서버 연결됨 **");

      /* 데이터 송수신 */
      bool shutdown = false;  // 프로그램 종료 플래그
      while(!shutdown) {
        /* 데이터 입력 */
        Console.WriteLine();
        Console.Write("[보낼 데이터] ");
        string? data = Console.ReadLine()!.Trim();   // 콘솔 입력을 받고 입력 문자열 처음/끝에 존재하는 화이트스페이스 제거
        if(data == null || data.Length <= 0) break;  // 입력이 유효하지 않으면 루프 종료

        /* 데이터 전송 */
        int sentSize;
        try {
          sentSize = socket.Send(Encoding.UTF8.GetBytes(data));  // 입력한 데이터를 바이트 배열로 변환하고 서버로 전송
        } catch {
          Console.WriteLine("데이터 전송 중 오류 발생");
          break;
        }
        Console.WriteLine($"데이터 전송 성공 ({sentSize} 바이트)");

        /* 데이터 수신 */
        byte[] bytes = new byte[BUFFER_SIZE];  // 버퍼 사이즈만큼 바이트 배열 생성
        int recvSize;                          // 수신 바이트 수
        try {
          recvSize = socket.Receive(bytes);    // 서버로부터 데이터를 바이트 배열로 수신
        } catch {
          Console.WriteLine("데이터 수신 중 오류 발생");
          break;
        }
        Console.WriteLine($"데이터 수신 성공 ({recvSize} 바이트)");

        /* 수신 데이터 출력 */
        string recvData = Encoding.UTF8.GetString(bytes, 0, recvSize);  // 받은 데이터를 문자열로 변환
        Console.WriteLine($"[수신 데이터] {recvData}");

        /* 수신 데이터가 "shutdown"일 경우 프로그램 종료 플래그 설정 */
        if(recvData.Equals("shutdown")) {
          Console.WriteLine("클라이언트 종료");
          shutdown = true;
          break;
        }
      }

      /* 소켓 종료 */
      socket.Close();

      /* 프로그램 종료 */
      Console.WriteLine("프로그램을 종료하려면 아무 키나 누르세요.");
      Console.ReadKey();
    }
  }
}
