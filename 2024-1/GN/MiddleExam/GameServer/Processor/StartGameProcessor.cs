using GameServer.Database;
using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class StartGameProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<StartGameRequest>()!;
        
        DatabaseUtility.InsertOne(DatabaseClient.Instance.Connection, TableNames.Users, new Dictionary<string, string> {
            { "name", message.Message.Name }
        });

        UDPServer.Instance.QueueSend(message.ClientId, new StartGameResponse {
            Status = true
        });
        return true;
    }
}
