using GameServer.Database;
using GameServer.Messages.Models;
using MySql.Data.MySqlClient;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class ServerMain {
    public static void Main(string[] args) {
        UDPServer.Instance.OnReceive += OnReceive;
        
        /* Thread pushThread = new(PushThreadFunc);
        pushThread.Start(); */
    }
    
    private static void OnReceive(object sender, JObject data) {
        RequestController.TryProcess(data);
    }
    
    private static void PushThreadFunc() {
        while(true) {
            Thread.Sleep(Constants.PUSH_INTERVAL);
            
            
        }
    }
}
