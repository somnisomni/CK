namespace Events {
  class Program {
    /* 이벤트 기반 스레드 동기화 */

    // 버퍼
    const int BUFSIZE = 10;
    static readonly int[] buf = new int[BUFSIZE];
    // 이벤트
    static readonly AutoResetEvent hWriteEvent = new(false);
    static readonly AutoResetEvent hReadEvent = new(false);

    static void WriteThread(object? arg) {
      for(int k = 1; k <= 500; k++) {
        // 읽기 완료 대기 (읽기 완료 이벤트가 설정될 때까지 대기)
        hReadEvent.WaitOne();

        // 공유 버퍼에 데이터 저장
        for(int i = 0; i < BUFSIZE; i++)
          buf[i] = k;

        // 쓰기 완료 알림
        hWriteEvent.Set();
      }
    }

    static void ReadThread(object? arg) {
      while(true) {
        // 쓰기 완료 대기 (쓰기 완료 이벤트가 설정될 때까지 대기)
        hWriteEvent.WaitOne();

        // 읽은 데이터 출력 후 버퍼를 0으로 초기화
        Console.Write($"Thread {Thread.CurrentThread.Name}:\t");
        for(int i = 0; i < BUFSIZE; i++)
          Console.Write("{0:D3} ", buf[i]);
        Console.WriteLine();
        Array.Clear(buf, 0, buf.Length);

        // 읽기 완료 알림
        hReadEvent.Set();
      }
    }

    static void Main(string[] args) {
      // 스레드 세 개 생성 (쓰기 1개, 읽기 2개)
      Thread[] hThread = new Thread[3];
      hThread[0] = new Thread(WriteThread) { Name = "Write" };
      hThread[1] = new Thread(ReadThread) { Name = "Read #1" };
      hThread[2] = new Thread(ReadThread) { Name = "Read #2" };
      hThread[0].Start();
      hThread[1].Start();
      hThread[2].Start();

      // 읽기 완료 알림
      hReadEvent.Set();

      // 스레드 세 개 종료 대기
      hThread[0].Join();
      hThread[1].Join();
      hThread[2].Join();

      // 이벤트 제거
      hWriteEvent.Close();
      hReadEvent.Close();
    }
  }
}