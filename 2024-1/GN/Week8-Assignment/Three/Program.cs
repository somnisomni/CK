using System.Net;
using System.Net.Sockets;

class SockProp {
    public static void Main() {
        IPAddress ia = IPAddress.Parse("127.0.0.1");
        IPEndPoint ie = new IPEndPoint(ia, 8000);

        Socket test = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        
        Console.WriteLine("AddressFamily: {0}", test.AddressFamily);
        Console.WriteLine("SocketType: {0}", test.SocketType);
        Console.WriteLine("ProtocolType: {0}", test.ProtocolType);
        
        Console.WriteLine("Blocking: {0}", test.Blocking);

        test.Blocking = false;
        Console.WriteLine("New Blocking: {0}", test.Blocking);
        Console.WriteLine("Connected: {0}", test.Connected);
        
        test.Bind(ie);
        IPEndPoint iep = (IPEndPoint)test.LocalEndPoint;
        Console.WriteLine("Local End Point: {0}", iep.ToString());
        
        test.Close();
    }
}