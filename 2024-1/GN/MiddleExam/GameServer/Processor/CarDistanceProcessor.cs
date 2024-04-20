using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class CarDistanceProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyCarDistance>()!;
        
        Console.WriteLine(message.Message.Distance);

        return true;
    }
}
