using GameServer.Database;
using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class CarDistanceProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyCarDistance>()!;
        
        DatabaseUtility.InsertOne(
            connection: DatabaseClient.Instance.Connection,
            tableName: TableNames.Records,
            data: new Dictionary<string, string> {
                { "userId", UDPServer.Instance.clientDbIdMap[message.ClientId].dbId.ToString() },
                { "userName", UDPServer.Instance.clientDbIdMap[message.ClientId].name },
                { "minimumDistance", message.Message.Distance.ToString() },
                { "dragTimespan", message.Message.DragTimespan.ToString() }
            }
        );

        return true;
    }
}
