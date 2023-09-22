// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #3 IP address conversion

using System.Net;

namespace IPAddr {
  class Program {
    static void Main(string[] args) {
      /*----------------*/
      /* IPv4 변환 연습 */
      /*----------------*/
      // 원래의 IPv4 주소 출력
      string ipv4test = "147.46.114.70";  // 서울대 IP ?!
      Console.WriteLine("IPv4 주소(변환 전) = {0}", ipv4test);

      // Parse() 함수 연습
      IPAddress ipv4num = IPAddress.Parse(ipv4test);     // IPv4 주소로 IPAddress 객체 생성
      byte[] bytes1 = ipv4num.GetAddressBytes();         // IPv4 주소를 바이트 배열로 변환
      Console.WriteLine("IPv4 주소(변환 후) = 0x{0:x}", BitConverter.ToInt32(bytes1, 0));  // 바이트 배열을 int로 변환
      // ↑ IPv4 주소는 32비트(4바이트)이므로 BitConvert.ToInt32를 통한 변환이 가능

      // Implicit ToString() 함수 연습
      Console.WriteLine("IPv4 주소(다시 변환 후) = {0}\n", ipv4num);
      // ↑ 객체(Object)를 String에 formatting할 때 자동으로 ToString() 함수를 호출함
      //   클래스에서 ToString() 함수를 오버라이드하여 반환값을 직접 지정할 수 있음
      //   IPAddress 클래스의 경우, IP 주소를 문자열로 변환 및 반환함

      /*----------------*/
      /* IPv6 변환 연습 */
      /*----------------*/
      // 원래의 IPv6 주소 출력
      string ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
      Console.WriteLine("IPv6 주소(변환 전) = {0}", ipv6test);

      // Parse() 함수 연습
      IPAddress ipv6num = IPAddress.Parse(ipv6test);      // IPv6 주소로 IPAddress 객체 생성
      Console.Write("IPv6 주소(변환 후) = 0x");
      byte[] bytes2 = ipv6num.GetAddressBytes();          // IPv6 주소를 바이트 배열로 변환
      for(int i = 0; i < bytes2.Length; i++)
        Console.Write("{0:x}", bytes2[i]);
      // ↑ IPv6 주소는 128비트(16바이트)이므로 BitConverter를 통한 다른 자료형으로 변환 불가
      //   그렇기 때문에 바이트 배열에서 loop를 돌며 1바이트씩 출력
      Console.WriteLine();

      // Implicit ToString() 함수 연습
      Console.WriteLine("IPv6 주소(다시 변환 후) = {0}\n", ipv6num);
      // ↑ IP 주소를 문자열로 변환 및 반환
    }
  }
}
