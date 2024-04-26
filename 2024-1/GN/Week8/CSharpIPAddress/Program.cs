using System.Net;

namespace CSharpSocket;

public static class Program {
    public static void Main(string[] args) {
        IPAddress test1 = IPAddress.Parse("192.168.1.1");
        IPAddress test2 = IPAddress.Loopback;
        IPAddress test3 = IPAddress.Any;
        IPAddress test4 = IPAddress.Broadcast;
        IPAddress test5 = IPAddress.None;

        IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
        IPAddress myself = host.AddressList[0];
        
        Console.WriteLine($" test1: {test1}");
        Console.WriteLine($" loopback: {test2}");
        Console.WriteLine($" any: {test3}");
        Console.WriteLine($" broadcast: {test4}");
        Console.WriteLine($" none: {test5}");
        Console.WriteLine($" myself: {myself}");
    }
}
