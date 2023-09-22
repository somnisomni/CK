// CK 2023-2 / Introduction to Game Network / Week4 Assignment / #4 domain name resolution

using System.Net;

namespace NameResolution {
  class Program {
    const string TESTNAME = "www.google.com";  // 구글

    // 도메인 이름 -> IPv4 주소
    static bool GetIPAddr(string name, ref IPAddress addr) {
      IPHostEntry? hostent = null;
      // IPHostEntry: DNS 호스트네임과 그에 할당된 IP 주소들을 저장하는 클래스

      try {
        // Dns 클래스의 함수를 통해 도메인 주소(name)를 resolve하고 IPHostEntry 객체를 반환받음
        hostent = Dns.GetHostEntry(name);
      } catch(Exception e) {
        // 오류 발생 시 오류 출력
        Console.WriteLine(e.Message);
        return false;
      }

      // resolve된 IP 주소 중 첫 번째 주소를 참조 매개변수 addr에 저장
      addr = hostent.AddressList[0];
      return true;
    }

    // IPv4 주소 -> 도메인 이름
    static bool GetDomainName(IPAddress addr, ref string name) {
      // 구조는 GetIPAddr 함수와 거의 동일하지만, IPAddress를 받고 DNS resolve하여 도메인 이름을 참조 매개변수 name에 저장

      IPHostEntry? hostent = null;

      try {
        hostent = Dns.GetHostEntry(addr);
      } catch(Exception e) {
        Console.WriteLine(e.Message);
        return false;
      }

      name = hostent.HostName;
      return true;
    }
    // 성공/실패 여부도 알 수 있으면서 결과값을 저장하기 위해 참조 매개변수(ref) 사용

    static void Main(string[] args) {
      Console.WriteLine("도메인 이름(변환 전) = {0}", TESTNAME);

      // 도메인 이름 -> IP 주소
      IPAddress? addr = null;
      if(GetIPAddr(TESTNAME, ref addr)) {
        // 성공이면 결과 출력
        Console.WriteLine("IP 주소(변환 후) = {0}", addr);

        // IP 주소 -> 도메인 이름
        string? name = null;
        if(GetDomainName(addr, ref name)) {
          // 성공이면 결과 출력
          Console.WriteLine("도메인 이름(다시 변환 후) = {0}", name);
        }
      }
    }
  }
}
