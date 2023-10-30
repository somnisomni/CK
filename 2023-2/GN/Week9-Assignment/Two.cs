namespace ThreadTest2 {
  class Two {
    static void MyThread(object arg) {
      // 무한 루프 스레드
      while(true);
    }

    static void Main(string[] args) {
      // 우선순위 값의 범위를 출력한다.
      Console.WriteLine("우선순위: {0} ~ {1}",
        (int)ThreadPriority.Lowest,
        (int)ThreadPriority.Highest);

      // CPU 개수를 알아낸다.
      int NumberOfProcessors = Environment.ProcessorCount;

      // CPU 개수만큼 스레드를 생성한다.
      for(int i = 0; i < NumberOfProcessors; i++) {
        // 스레드를 생성한다.
        Thread hThread = new Thread(MyThread);
        hThread.IsBackground = true;
        // 우선순위를 높게 설정한다.
        hThread.Priority = ThreadPriority.AboveNormal;
        hThread.Start();
      }

      // 우선순위를 낮게 설정한다.
      Thread.CurrentThread.Priority = ThreadPriority.BelowNormal;

      // 1초 후에 출력이 되어야하지만 생성된 스레드의 처리로 인해 매우 지연됨
      //  + OS 반응속도 저하
      Thread.Sleep(1000);
      Console.WriteLine("주 스레드 실행!");
    }
  }
}