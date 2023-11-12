using System.Diagnostics;

namespace TeamStudy {
  class TeamStudy {
    private static int val = 0; // 스레드에서 공통적으로 접근할 변수
    private readonly static Stopwatch sw = new(); // 작업에 걸린 시간을 측정하기 위한 Stopwatch 객체
    private readonly static Mutex mutex = new();  // Mutex 객체

    public static void Main(string[] args) {
      // 스레드 3개 생성
      Thread t1 = new(ThreadLoop);
      Thread t2 = new(ThreadLoop);
      Thread t3 = new(ThreadLoop);

      Console.WriteLine("Threads are created, starting threads...");

      // 시간 측정 시작
      sw.Start();
      // 스레드 시작
      t1.Start();
      t2.Start();
      t3.Start();
      // 스레드 종료 대기
      t1.Join();
      t2.Join();
      t3.Join();
      // 시간 측정 종료
      sw.Stop();

      // 공통 변수 값 출력, 예상 val 값 = 1500000000
      Console.WriteLine($"All threads are finished, val = {val}, elapsed = {sw.Elapsed.TotalSeconds}s");
    }

    private static void ThreadLoop() {
      Console.WriteLine($"Thread #{Environment.CurrentManagedThreadId} loop start");

      mutex.WaitOne();      // Lock
      
      /* 임계 영역 진입 */
      Console.WriteLine($"Thread #{Environment.CurrentManagedThreadId} entered critical section");

      // 공통 변수의 값을 5억 번 증가시킴
      for(int i = 0; i < 500_000_000; i++) {
        val++;
      }

      /* 임계 영역 종료 */
      Console.WriteLine($"Thread #{Environment.CurrentManagedThreadId} left critical section");

      mutex.ReleaseMutex(); // Unlock

      Console.WriteLine($"Thread #{Environment.CurrentManagedThreadId} loop end, val = {val}");
    }
  }
}
