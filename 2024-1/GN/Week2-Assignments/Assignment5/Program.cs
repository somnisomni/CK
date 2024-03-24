namespace CriticalSections {
    // Monitor 기법을 사용한 스레드 동기화
    
    class Program {
        const int MAXCNT = 100000000;
        static int count = 0;

        // 2씩 증가시키는 함수
        static void MyThread1(object arg) {
            for(int i = 0; i < MAXCNT; i++) {
                Monitor.Enter(arg);
                count += 2;
                Monitor.Exit(arg);
            }
        }

        // 2씩 감소시키는 함수
        static void MyThread2(object arg) {
            for(int i = 0; i < MAXCNT; i++) {
                Monitor.Enter(arg);
                count -= 2;
                Monitor.Exit(arg);
            }
        }

        static void Main(string[] args) {
            // 동기화용 오브젝트 생성
            object obj = new object();
            
            // 스레드 두 개 생성
            Thread[] hThread = new Thread[2];
            hThread[0] = new Thread(MyThread1);
            hThread[1] = new Thread(MyThread2);
            hThread[0].Start(obj);
            hThread[1].Start(obj);
            
            // 스레드 두 개 종료 대기
            hThread[0].Join();
            hThread[1].Join();
            
            // 결과 출력
            // 이론적(스레드 동기화가 제대로 이루어졌을 경우) 결과는 0
            Console.WriteLine("count = {0}", count);
        }
    }
}