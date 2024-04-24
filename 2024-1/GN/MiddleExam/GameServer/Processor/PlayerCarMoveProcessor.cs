using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class PlayerCarMoveProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyCarMoveStart>();
        
        if(message?.Message.DragDistance != null) {
            UDPServer.Instance.QueueSend(0, new PushPlayerCarMoveStart {
                ClientId = message.ClientId,
                DragDistance = message.Message.DragDistance
            });
            return true;
        }

        return false;
    }
}
