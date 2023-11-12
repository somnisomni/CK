namespace CriticalSections {
  class Program {
    /* Monitor 기반 스레드 동기화 */

    const int MAXCNT = 100000000;  // 루프 반복 횟수
    static int count = 0;          // 공통 변수

    static void MyThread1(object? arg) {
      // count를 2씩 더하는 스레드

      for(int i = 0; i < MAXCNT; i++) {
        Monitor.Enter(arg!);
        // 임계 영역 진입
        count += 2;
        // 임계 영역 종료
        Monitor.Exit(arg!);
      }
    }

    static void MyThread2(object? arg) {
      // count를 2씩 빼는 스레드
      
      for(int i = 0; i < MAXCNT; i++) {
        Monitor.Enter(arg!);
        // 임계 영역 진입
        count -= 2;
        // 임계 영역 종료
        Monitor.Exit(arg!);
      }
    }

    static void Main(string[] args) {
      // 동기화용 오브젝트 생성
      object obj = new();

      // 스레드 두 개 생성
      Thread[] hThread = new Thread[2];
      hThread[0] = new Thread(MyThread1);
      hThread[1] = new Thread(MyThread2);
      hThread[0].Start(obj);
      hThread[1].Start(obj);

      // 스레드 두 개 종료 대기
      hThread[0].Join();
      hThread[1].Join();

      // 결과 출력, 예상 값 = 0
      Console.WriteLine("count = {0}", count);
    }
  }
}