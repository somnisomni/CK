using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Week12_Assignment {
  internal class AdvancedChatClient {
    static readonly string BROADCAST_IP = "255.255.255.255";
    static readonly int REMOTEPORT = 9000;
    static readonly IPEndPoint BROADCAST_ENDPOINT = new(IPAddress.Parse(BROADCAST_IP), REMOTEPORT);
    static readonly IPEndPoint ANY_ENDPOINT = new(IPAddress.Any, REMOTEPORT);
    static readonly int BUFFERSIZE = 512;

    static int  multicastNum = -1;
    private static int _multicastReceiveThreadId = -1;
    static bool shutdown = false;

    private static void SocketReceiveThread(object? arg) {
      Socket? broadcastReceiveSocket;
      try {
        broadcastReceiveSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        broadcastReceiveSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        broadcastReceiveSocket.Bind(ANY_ENDPOINT);
      } catch(Exception e) {
        Console.Error.WriteLine(e.Message);
        return;
      }

      byte[] buffer = new byte[BUFFERSIZE];

      EndPoint? sender = BROADCAST_ENDPOINT;
      while(!shutdown) {
        try {
          int bytesReceived = broadcastReceiveSocket.ReceiveFrom(buffer, SocketFlags.None, ref sender);
          if(bytesReceived > 0) {
            IPEndPoint ipSender = (IPEndPoint)sender;
            Console.WriteLine($"[BC {ipSender.Address}:{ipSender.Port}] {Encoding.Default.GetString(buffer, 0, bytesReceived)}");
          }
        } catch(Exception e) {
          Console.Error.WriteLine(e.Message);
          break;
        }
      }

      broadcastReceiveSocket.Close();
    }

    private static void MulticastSendThread(object? arg) {
      string multicastAddr = $"235.1.2.{multicastNum}";
      IPEndPoint multicastEndpoint = new(IPAddress.Parse(multicastAddr), REMOTEPORT);

      Socket? multicastSendSocket;
      try {
        multicastSendSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        multicastSendSocket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.MulticastTimeToLive, 5);
        multicastSendSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
      } catch(Exception e) {
        Console.Error.WriteLine(e.Message);
        return;
      }

      while(!shutdown || multicastNum > 0) {
        Console.Write($"\n(#{multicastNum}) 데이터 입력 > ");
        string data = Console.ReadLine()!;
        if(data.Length == 0) break;

        try {
          byte[] senddata = Encoding.Default.GetBytes(data);
          int size = senddata.Length;
          if(size > BUFFERSIZE) size = BUFFERSIZE;

          int bytesSend = multicastSendSocket.SendTo(senddata, 0, size, SocketFlags.None, multicastEndpoint);
        } catch(Exception e) {
          Console.Error.WriteLine(e.Message);
          break;
        }
      }

      multicastSendSocket.Close();
    }

    private static void MulticastReceiveThread(object? arg) {
      int curId = _multicastReceiveThreadId = (int)arg!;
      int curNum = multicastNum;
      string multicastAddr = $"235.1.2.{multicastNum}";
      IPEndPoint multicastEndpoint = new(IPAddress.Parse(multicastAddr), REMOTEPORT);
      MulticastOption multicastOp = new(multicastEndpoint.Address);

      Socket? multicastReceiveSocket;
      try {
        multicastReceiveSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        multicastReceiveSocket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, multicastOp);
        multicastReceiveSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
        multicastReceiveSocket.Bind(ANY_ENDPOINT);
      } catch(Exception e) {
        Console.Error.WriteLine(e.Message);
        return;
      }

      byte[] buffer = new byte[BUFFERSIZE];

      EndPoint? sender = ANY_ENDPOINT;
      while(!shutdown && multicastNum == curNum && _multicastReceiveThreadId == curId) {
        try {
          int bytesReceived = multicastReceiveSocket.ReceiveFrom(buffer, SocketFlags.None, ref sender);

          if(multicastNum != curNum || _multicastReceiveThreadId != curId) break;

          if(bytesReceived > 0) {
            IPEndPoint ipSender = (IPEndPoint)sender;
            Console.WriteLine($"[(#{multicastNum}) {ipSender.Address}:{ipSender.Port}] {Encoding.Default.GetString(buffer, 0, bytesReceived)}");
          }
        } catch(Exception e) {
          Console.Error.WriteLine(e.Message);
          break;
        }
      }

      multicastReceiveSocket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.DropMembership, multicastOp);
      multicastReceiveSocket.Close();
      _multicastReceiveThreadId = -1;
    }

  static void Main(string[] args) {
      Socket? socket = null;
      try {
        socket = new(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Broadcast, true);
        socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
      } catch(Exception e) {
        Console.Error.WriteLine(e.Message);
        Environment.Exit(1);
      }

      Console.WriteLine("*** UDP 클라이언트 실행 *** \n\n");

      Thread? mcReceiveThread = null;
      Thread? mcSendThread = null;
      Thread bcReceiveThread = new(SocketReceiveThread);
      bcReceiveThread.Start(socket);

      while(!shutdown) {
        Console.Write("\n데이터 입력 > ");
        string data = Console.ReadLine()!;
        if(data.Length == 0) continue;

        try {
          byte[] senddata = Encoding.Default.GetBytes(data);
          int size = senddata.Length;
          if(size > BUFFERSIZE) size = BUFFERSIZE;

          if(data.StartsWith("#") && int.TryParse(data[1..], out _)) {
            multicastNum = int.Parse(data[1..]);

            if(multicastNum <= 254 && multicastNum >= 1) {
              Console.WriteLine($"** 방 접속: #{multicastNum} **\n");

              mcReceiveThread = new(MulticastReceiveThread);
              mcReceiveThread.Start(new Random().Next(0, int.MaxValue));
              mcSendThread = new(MulticastSendThread);
              mcSendThread.Start();
              mcSendThread.Join();

              Console.WriteLine($"** #{multicastNum} 방 퇴장 **\n");

              multicastNum = -1;
              mcReceiveThread = null;
              mcSendThread = null;
            } else {
              Console.Error.WriteLine("잘못된 방 번호.");
            }

            continue;
          }

          int bytesSent = socket.SendTo(senddata, 0, size, SocketFlags.None, BROADCAST_ENDPOINT);
        } catch(Exception e) {
          Console.Error.WriteLine(e.Message);
          break;
        }
      }

      socket.Close();
    }

    ~AdvancedChatClient() {
      shutdown = true;
    }
  }
}
