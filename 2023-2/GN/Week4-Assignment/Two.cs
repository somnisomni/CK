// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #2 byte ordering

using System.Net;

namespace ByteOrder {
  class Program {
    static void Main(string[] args) {
      // 테스트용 변수
      short x1 = 0x1234;    // 2바이트 데이터 (Little Endian 이라고 가정)
      int y1 = 0x12345678;  // 4바이트 데이터 (Little Endian 이라고 가정)
      short x2;             // 2바이트 데이터 (Big Endian 이라고 가정)
      int y2;               // 4바이트 데이터 (Big Endian 이라고 가정)

      // 호스트 바이트 -> 네트워크 바이트
      Console.WriteLine("[호스트 바이트 -> 네트워크 바이트]");
      x2 = IPAddress.HostToNetworkOrder(x1); // 2바이트 HtN 변환
      Console.WriteLine("0x{0:x} -> 0x{1:x}", x1, x2);
      y2 = IPAddress.HostToNetworkOrder(y1); // 4바이트 HtN 변환
      Console.WriteLine("0x{0:x} -> 0x{1:x}", y1, y2);

      // 네트워크 바이트 -> 호스트 바이트
      Console.WriteLine("\n[네트워크 바이트 -> 호스트 바이트]");
      Console.WriteLine("0x{0:x} -> 0x{1:x}", x2, IPAddress.NetworkToHostOrder(x2)); // 2바이트 NtH 변환 (=> x1)
      Console.WriteLine("0x{0:x} -> 0x{1:x}", y2, IPAddress.NetworkToHostOrder(y2)); // 4바이트 NtH 변환 (=> y1)

      // 잘못된 사용 예
      Console.WriteLine("\n[잘못된 사용 예]");
      Console.WriteLine("0x{0:x} -> 0x{1:x}", x1, IPAddress.NetworkToHostOrder((int)x1)); // Byte Size Mismatch
    }
  }
}
