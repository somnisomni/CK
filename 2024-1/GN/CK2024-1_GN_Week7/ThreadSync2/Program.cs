namespace ThreadSync2;

public class Program {
    public int number = 0;
    
    public static void Main(string[] args) {
        Program program = new Program();
        Thread thread1 = new Thread(ThreadFunc);
        Thread thread2 = new Thread(ThreadFunc);
        
        thread1.Start(program);
        thread2.Start(program);

        thread1.Join();
        thread2.Join();
        
        Console.WriteLine(program.number);
    }

    private static void ThreadFunc(object? instance) {
        Program program = (Program)instance;
        
        for(int i = 1; i <= 100_000_000; i++) {
            program.number += 1;
        }
    }
}
