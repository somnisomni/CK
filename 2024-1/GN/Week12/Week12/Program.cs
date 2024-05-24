public class Program {
    public static void Main(string[] args) {
        DateTime before = DateTime.Now;
        Sum();
        DateTime after = DateTime.Now;
        
        long gap = after.Ticks - before.Ticks;
        
        Console.WriteLine("Total ticks: " + gap);
        Console.WriteLine("Total milliseconds: " + gap / 10_000);
        Console.WriteLine("Seconds: " + gap / 10_000 / 1_000);
    }

    private static long Sum() {
        long sum = 0;
        for(int i = 0; i < 100_000_000; i++) {
            sum += i;
        }

        return sum;
    }
}