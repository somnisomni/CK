using System.Collections.Concurrent;

public class Program {
    public static void Main() {
        var dict = new ConcurrentDictionary<int, string>();

        Task t1 = Task.Factory.StartNew(() => {
            int key = 0;

            while(key++ < 100) {
                if(dict.TryAdd(key, "Value" + key)) {
                    Console.WriteLine("added key: " + key);
                }
                
                Thread.Sleep(100);
            }
        });

        Task t2 = Task.Factory.StartNew(() => {
            int key = 0;
            string value;

            while(key++ < 100) {
                if(dict.TryGetValue(key, out value)) {
                    Console.WriteLine("read key: " + key + " value: " + value);
                }
                
                Thread.Sleep(125);
            }
        });

        Task.WaitAll(t1, t2);
    }
}