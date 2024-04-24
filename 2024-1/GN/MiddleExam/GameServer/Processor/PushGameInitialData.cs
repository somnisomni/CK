using GameServer.Database;
using GameServer.Messages.Models;
using MySql.Data.MySqlClient;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class PushGameInitialData : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<StartGameRequest>()!;
        
        QueueSendRankData(message.ClientId);
        UDPServer.Instance.QueueSend(message.ClientId, new PushPlayersInfo {
            Players = UDPServer.Instance.clientDbIdMap.Select(x => new PlayerData {
                Id = (int)x.Key,
                Name = x.Value.name,
            }).ToArray()
        });

        return true;
    }
    
    public static void QueueSendRankData(uint clientId) {
        using MySqlDataReader reader = DatabaseUtility.ExecuteQueryWithReader(
            connection: DatabaseClient.Instance.Connection,
            query: DatabaseQueries.TopFiveRank);
            
        List<RecordData> data = new();
        while(reader.Read()) {    
            data.Add(new RecordData {
                Name = reader.GetString("userName"),
                MinimumDistance = Math.Round(reader.GetDouble("minimumDistance"), 4),
                DragTimespan = Math.Round(reader.GetDouble("dragTimespan"), 4)
            });
        }
            
        UDPServer.Instance.QueueSend(clientId, new PushRankData {
            Rank = data.ToArray()
        });
    }
}
