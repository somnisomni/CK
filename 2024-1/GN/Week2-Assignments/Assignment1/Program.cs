using System.Text;
using System.Net;
using System.Net.Sockets;

namespace ThreadTCPServer {
    class Program {
        const int SERVERPORT = 9000;  // 서버 포트
        const int BUFSIZE = 512;      // 버퍼 크기

        // 클라이언트와의 통신 함수 (스레드에 사용)
        static void ProcessClient(object arg) {
            int retval;  // 소켓 함수 반환값 (수신 바이트 수 등)
            Socket clientSock = (Socket)arg;  // 전달받은 클라이언트 소켓
            IPEndPoint clientAddr;  // 클라이언트 주소 정보
            byte[] buf = new byte[BUFSIZE];  // 데이터 버퍼
            
            // 클라이언트 정보 얻기
            clientAddr = (IPEndPoint)clientSock.RemoteEndPoint;
            
            // 데이터 송수신 루프
            while(true) {
                try {
                    // 데이터 받기
                    retval = clientSock.Receive(buf, BUFSIZE, SocketFlags.None);
                    if(retval == 0) break;  // 받은 데이터가 없으면 송수신 종료
                    
                    // 받은 데이터 출력
                    Console.WriteLine("[TCP/{0}:{1}] {2}",
                        clientAddr.Address, clientAddr.Port,
                        Encoding.Default.GetString(buf, 0, retval));
                    
                    // 받은 데이터 그대로 보내기 (echo)
                    clientSock.Send(buf, retval, SocketFlags.None);
                } catch(Exception e) {
                    Console.WriteLine(e.Message);
                    break;
                }
            }

            // 소켓 닫기
            clientSock.Close();
            Console.WriteLine("[TCP 서버] 클라이언트 종료: IP 주소={0}, 포트 번호={1}",
                clientAddr.Address, clientAddr.Port);
        }

        static void Main(string[] args) {
            Socket listenSock = null;  // 서버 소켓
            
            // 소켓 설정
            try {
                // 소켓 생성
                listenSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                
                // Bind()
                listenSock.Bind(new IPEndPoint(IPAddress.Any, SERVERPORT));
                
                // Listen()
                listenSock.Listen(int.MaxValue);
            } catch(Exception e) {
                Console.WriteLine(e.Message);
                Environment.Exit(1);
            }

            Console.WriteLine(" * TCP Server 가 정상 동작을 시작했습니다.");
            
            // 데이터 통신에 사용할 변수
            Socket clientSock = null;  // 클라이언트 소켓
            Thread hThread;  // 데이터 송수신 스레드
            
            // 클라이언트 연결 루프
            while(true) {
                try {
                    // accept()
                    clientSock = listenSock.Accept();
                    
                    // 접속한 클라이언트 정보 출력
                    IPEndPoint clientAddr = (IPEndPoint)clientSock.RemoteEndPoint;
                    Console.WriteLine("\n[TCP 서버] 클라이언트 접속: IP 주소={0}, 포트 번호={1}",
                        clientAddr.Address, clientAddr.Port);
                    
                    // 데이터 송수신 스레드 생성 및 시작
                    hThread = new Thread(ProcessClient);
                    hThread.Start(clientSock);
                }
                catch(Exception e) {
                    Console.WriteLine(e.Message);
                    break;
                }
            }

            // 서버 소켓 닫기
            listenSock.Close();
        }
    }
}