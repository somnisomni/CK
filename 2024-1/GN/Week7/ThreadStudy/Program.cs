using System.Diagnostics;
using ThreadState = System.Diagnostics.ThreadState;

namespace ThreadStudy;

public class Program {
    public static void Main(string[] args) {
        Process thisProc = Process.GetCurrentProcess();
        ProcessThreadCollection thisThreads = thisProc.Threads;

        foreach(ProcessThread thread in thisThreads) {
            // DateTime startTime = thread.StartTime;
            TimeSpan cpuTime = thread.TotalProcessorTime;
            int priority = thread.BasePriority;
            ThreadState state = thread.ThreadState;
            
            Console.WriteLine($"*** Thread ID: {thread.Id}");
            // Console.WriteLine($"Start Time: {startTime}");
            Console.WriteLine($"    CPU Time: {cpuTime}");
            Console.WriteLine($"    Priority: {priority}");
            Console.WriteLine($"    Thread State: {state.ToString()}");
            Console.WriteLine();
        }
        
        /* === */
        Console.WriteLine("\n\n");
        /* === */

        Thread th = new Thread(ThreadFunc);
        Console.WriteLine("[MAIN] Thread created");
        th.Start();
        Console.WriteLine("[MAIN] Thread started");
        Console.WriteLine("[MAIN] Main procedure reached end.");
    }

    private static void ThreadFunc() {
        Console.WriteLine("[SUB] ThreadFunc() called, complete in 5 seconds...");
        Thread.Sleep(5000);
        Console.WriteLine("[SUB] ThreadFunc() complete.");
    }
}