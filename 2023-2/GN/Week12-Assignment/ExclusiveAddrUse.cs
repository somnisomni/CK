using System.Net;
using System.Net.Sockets;

namespace Week12_Assignment {
  internal class ExclusiveAddrUse {
    readonly static IPEndPoint endPoint = new(IPAddress.Any, 9000);
    readonly static IPEndPoint specificEndPoint = new(IPAddress.Parse("10.39.39.39"), 9000);

    static void Main(string[] args) {
      Console.WriteLine("** SO_EXCLUSIVEADDRUSE 테스트 **\n\n");

      Test(endPoint);
    }

    private static void Test(IPEndPoint endpoint) {
      Console.WriteLine($"\n * 바인드 주소: {endpoint.Address}:{endpoint.Port}\n");

      /* ========== */
      Console.WriteLine("\n 테스트 #1");
      Console.WriteLine("  1. 소켓 옵션을 지정하지 않은 소켓 바인드");
      Console.WriteLine("  2. SO_REUSEADDR 옵션이 지정된 다른 소켓을 동일 주소로 바인드\n");

      Socket? sock1 = null, sock2 = null;
      try {
        // 소켓 생성 (TCP)
        sock1 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        sock2 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        Console.WriteLine(" * 소켓1/소켓2 생성");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 서버 바인드
      try {
        sock1.Bind(endpoint);
        Console.WriteLine(" * 소켓1 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 옵션 지정 및 바인드
      try {
        sock2.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        Console.WriteLine(" * 소켓2에 SO_REUSEADDR 옵션 지정");
        sock2.Bind(endpoint);
        Console.WriteLine(" * 소켓2 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 클린업
      sock1.Close(); sock1 = null;
      sock2.Close(); sock2 = null;
      /* ========== */

      /* ========== */
      Console.WriteLine("\n\n 테스트 #2");
      Console.WriteLine("  1. SO_REUSEADDR 옵션이 지정된 소켓 바인드");
      Console.WriteLine("  2. SO_REUSEADDR 옵션이 지정된 다른 소켓을 동일 주소로 바인드\n");

      try {
        // 소켓 생성 (TCP)
        sock1 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        sock2 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        Console.WriteLine(" * 소켓1/소켓2 생성");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 서버 바인드
      try {
        sock1.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        Console.WriteLine(" * 소켓1에 SO_REUSEADDR 옵션 지정");
        sock1.Bind(endpoint);
        Console.WriteLine(" * 소켓1 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 옵션 지정 및 바인드
      try {
        sock2.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        Console.WriteLine(" * 소켓2에 SO_REUSEADDR 옵션 지정");
        sock2.Bind(endpoint);
        Console.WriteLine(" * 소켓2 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 클린업
      sock1.Close(); sock1 = null;
      sock2.Close(); sock2 = null;
      /* ========== */

      /* ========== */
      Console.WriteLine("\n\n 테스트 #3");
      Console.WriteLine("  1. SO_REUSEADDR 옵션이 지정된 소켓 바인드");
      Console.WriteLine("  2. SO_EXCLUSIVEADDRUSE 옵션이 지정된 다른 소켓을 동일 주소로 바인드\n");

      try {
        // 소켓 생성 (TCP)
        sock1 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        sock2 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        Console.WriteLine(" * 소켓1/소켓2 생성");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 서버 바인드
      try {
        sock1.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        Console.WriteLine(" * 소켓1에 SO_REUSEADDR 옵션 지정");
        sock1.Bind(endpoint);
        Console.WriteLine(" * 소켓1 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 옵션 지정 및 바인드
      try {
        sock2.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ExclusiveAddressUse, true);
        Console.WriteLine(" * 소켓2에 SO_EXCLUSIVEADDRUSE 옵션 지정");
        sock2.Bind(endpoint);
        Console.WriteLine(" * 소켓2 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 클린업
      sock1.Close(); sock1 = null;
      sock2.Close(); sock2 = null;
      /* ========== */

      /* ========== */
      Console.WriteLine("\n\n 테스트 #4");
      Console.WriteLine("  1. SO_EXCLUSIVEADDRUSE 옵션이 지정된 소켓 바인드");
      Console.WriteLine("  2. SO_REUSEADDR 옵션이 지정된 다른 소켓을 동일 주소로 바인드\n");

      try {
        // 소켓 생성 (TCP)
        sock1 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        sock2 = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        Console.WriteLine(" * 소켓1/소켓2 생성");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 서버 바인드
      try {
        sock1.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ExclusiveAddressUse, true);
        Console.WriteLine(" * 소켓1에 SO_EXCLUSIVEADDRUSE 옵션 지정");
        sock1.Bind(endpoint);
        Console.WriteLine(" * 소켓1 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 옵션 지정 및 바인드
      try {
        sock2.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        Console.WriteLine(" * 소켓2에 SO_REUSEADDR 옵션 지정");
        sock2.Bind(endpoint);
        Console.WriteLine(" * 소켓2 바인드");
      } catch(Exception e) {
        Console.WriteLine(e.Message);
      }

      // 소켓 클린업
      sock1.Close(); sock1 = null;
      sock2.Close(); sock2 = null;
      /* ========== */

      Console.WriteLine("\n\n\n");
    }
  }
}
