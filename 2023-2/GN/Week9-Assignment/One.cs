namespace ThreadTest1 {
  class Point3D {
    public int x, y, z;
    public Point3D(int x, int y, int z) {
      this.x = x;
      this.y = y;
      this.z = z;
    }
  }

  class One {
    static void MyThread(object arg) {
      // 스레드 함수

      // 현재 스레드를 1초 대기
      Thread.Sleep(1000);

      // 포인트를 arg에서 가져옴
      Point3D pt = (Point3D)arg;

      // 출력
      Console.WriteLine("Running MyThread() {0}: {1}, {2}, {3}",
        Thread.CurrentThread.ManagedThreadId,
        pt.x, pt.y, pt.z);
    }

    static void Main(string[] args) {
      // 첫 번째 스레드 생성
      Point3D pt1 = new Point3D(10, 20, 30);
      Thread hThread1 = new Thread(MyThread);
      hThread1.Start(pt1);  // C#(.NET)에서는 스레드는 수동으로 시작 필요

      // 두 번째 스레드 생성
      Point3D pt2 = new Point3D(40, 50, 60);
      Thread hThread2 = new Thread(MyThread);
      hThread2.Start(pt2);

      Console.WriteLine("Running main() {0}",
        Thread.CurrentThread.ManagedThreadId);
        Thread.Sleep(2000);
    }
  }
}