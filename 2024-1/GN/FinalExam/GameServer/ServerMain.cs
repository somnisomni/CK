using GameServer.Entity;
using GameServer.Messages.Models;
using GameServer.Processor;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class ServerMain {
    private static Thread dotGenerationThread;
    
    public static void Main(string[] args) {
        UDPServer.Instance.OnReceive += OnReceive;
        UDPServer.Instance.OnNewClientConnect += OnNewClientConnect;
        
        StartDotGeneration();
    }

    private static void OnReceive(object sender, JObject data) {
        RequestController.TryProcess(data);
    }

    private static void OnNewClientConnect(object sender, uint playerId) {
        UDPServer.Instance.QueueSend(playerId, new PushPlayersInfo {
            Players = PlayerManager.ForEachPlayer().ToArray()
        });
    }

    private static void StartDotGeneration() {
        dotGenerationThread = new Thread(DotGenerateProcessor.Process);
        dotGenerationThread.Start();
    }
}
