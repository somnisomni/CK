using System.Text;
using System.Net.Sockets;

namespace TCPClient {
    class Program {
        static string SERVERIP = "127.0.0.1";  // 서버 IP 주소
        const int SERVERPORT = 9000;  // 서버 포트
        const int BUFSIZE = 512;  // 버퍼 크기

        static void Main(string[] args) {
            int retval;  // 소켓 함수 반환값 (수신 바이트 수 등)
            Socket sock = null;  // 클라이언트 소켓
            
            // 명령행 인수가 있으면 IP 주소로 사용
            if(args.Length > 0) SERVERIP = args[0];
            
            // 소켓 설정
            try {
                // 소켓 생성
                sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                
                // Connect()
                sock.Connect(SERVERIP, SERVERPORT);
                Console.Write(" * Client 프로그램이 Server 에 정상적으로 연결되었습니다. ");
            } catch(Exception e) {
                Console.WriteLine(e.Message);
                Environment.Exit(1);
            }

            // 데이터 통신에 사용할 변수
            byte[] buf = new byte[BUFSIZE];
            
            // 서버와 데이터 통신 루프
            while(true) {
                // 데이터 입력
                Console.Write("\n[보낼 데이터] ");
                string data = Console.ReadLine();
                if(data.Length == 0) break;  // 아무것도 입력하지 않으면 종료
                
                try {
                    // 데이터 준비 (최대 길이를 BUFSIZE로 제한)
                    byte[] senddata = Encoding.Default.GetBytes(data);
                    int size = senddata.Length;
                    if(size > BUFSIZE) size = BUFSIZE;
                    
                    // 입력한 데이터를 서버로 전송
                    retval = sock.Send(senddata, 0, size, SocketFlags.None);
                    Console.WriteLine("[TCP 클라이언트] {0}바이트를 보냈습니다.", retval);
                    
                    // 데이터 받기
                    retval = ReceiveN(sock, buf, retval, SocketFlags.None);
                    if(retval == 0) break;
                    
                    // 받은 데이터 출력
                    Console.WriteLine("[TCP 클라이언트] {0}바이트를 받았습니다.", retval);
                    Console.WriteLine("[받은 데이터] {0}",
                        Encoding.Default.GetString(buf, 0, retval));
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
            int offset = 0;  // 버퍼 내 현재 오프셋
            int left = len;  // 받아야 할 남은 바이트 수
            
            // 받아야 할 데이터가 남아있는 경우 루프
            while(left > 0) {
                try {
                    // 데이터 수신
                    int received = sock.Receive(buf, offset, left, flags);
                    if(received == 0) break;
                    
                    // 실제로 받은 데이터 크기만큼 오프셋/남은 바이트 수 계산
                    left -= received;
                    offset += received;
                } catch(Exception e) {
                    throw e;
                }
            }

            return len - left;
        }
    }
}