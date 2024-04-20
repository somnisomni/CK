namespace ThreadSync;

class Program {
    private static int sum = 0;
    
    public static void Main(string[] args) {
        int num = 100;
        Thread thread = new Thread(ThreadFunc);
        Console.WriteLine($" Before: {sum}");
        thread.Start(num);
        thread.Join();
        Console.WriteLine($" After: {sum}");
    }

    private static void ThreadFunc(object? arg) {
        int num = (int)arg;

        for(int i = 1; i <= num; i++) {
            sum += i;
        }
    }
}
