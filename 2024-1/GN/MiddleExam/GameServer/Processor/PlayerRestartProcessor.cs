using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class PlayerRestartProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyPlayerRestart>();
        
        if(message?.ClientId != null) {
            UDPServer.Instance.QueueSend(0, new PushPlayerRestart {
                ClientId = message.ClientId
            });
            return true;
        }

        return false;
    }
}
