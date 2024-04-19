namespace ThreadParam;

class Program {
    private struct ThreadParam {
        public int intValue { get; init; }
        public string strValue { get; init; }
    }
    
    public static void Main(string[] args) {
        Thread thread = new Thread(ThreadFunc);
        ThreadParam value = new ThreadParam() {
            intValue = 10,
            strValue = "what"
        };
        
        thread.Start(value);
    }

    private static void ThreadFunc(object? initialValue) {
        ThreadParam value = (ThreadParam)initialValue;
        Console.WriteLine($"intval: {value.intValue}, strval: {value.strValue}");
    }
}
