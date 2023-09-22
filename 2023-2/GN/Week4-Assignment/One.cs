// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #1 socket creation

using System.Net.Sockets;

namespace InitSocket {
  class Program {
    static void Main(string[] args) {
      // 소켓 오브젝트 선언 (null로 초기화)
      Socket? sock = null;

      try {
        // 소켓 생성
        // new Socket(AddressFamily 주소스키마, SocketType 소켓종류, ProtocolType 프로토콜종류)
        sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        // ↑ TCP일 경우 new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        // ↑ UDP일 경우 new Socket(AddressFamily.InterNetwork, SocketType.Dgram,  ProtocolType.Udp);
        // ↑ IPv4 대신 IPv6 => ... AddressFamily.InterNetworkV6 ...

        Console.WriteLine("[알림] 소켓 생성 성공");
      } catch(Exception e) {
        // 소켓 생성 중 오류 발생 시 오류 메시지 출력 및 프로그램 종료
        Console.WriteLine(e.Message);
        Environment.Exit(1);
      }

      // 소켓 닫기
      sock.Close();
    }
  }
}
