using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class ClientShutdownProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyClientShutdown>();
        
        if(message?.ClientId != null) {
            UDPServer.Instance.QueueSend(0, new PushPlayerShutdown {
                ClientId = message.ClientId
            });
            return true;
        }

        return false;
    }
}
