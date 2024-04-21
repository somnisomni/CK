using GameServer.Database;
using GameServer.Messages.Models;
using MySql.Data.MySqlClient;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class ServerMain {
    public static void Main(string[] args) {
        UDPServer.Instance.OnReceive += OnReceive;

        Thread pushThread = new(PushThreadFunc);
        pushThread.Start();
    }
    
    private static void OnReceive(object sender, JObject data) {
        RequestController.TryProcess(data);
    }
    
    private static void PushThreadFunc() {
        while(true) {
            Thread.Sleep(Constants.PUSH_INTERVAL);
            
            using MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
            command.CommandText = $"SELECT userName, minimumDistance, dragTimespan" 
                                  + " FROM records"
                                  + " WHERE minimumDistance >= 0 AND dragTimespan > 0"
                                  + " ORDER BY minimumDistance ASC, dragTimespan ASC"
                                  + " LIMIT 10";
            using MySqlDataReader reader = command.ExecuteReader();
            
            List<RecordData> data = new();
            while(reader.Read()) {    
                data.Add(new RecordData {
                    Name = reader.GetString("userName"),
                    MinimumDistance = reader.GetDouble("minimumDistance"),
                    DragTimespan = reader.GetDouble("dragTimespan")
                });
            }
            
            UDPServer.Instance.QueueSend(0, new PushRankData {
                Rank = data.ToArray()
            });
        }
    }
}
