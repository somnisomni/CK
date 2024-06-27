using GameServer.Entity;
using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class PlayerJoinRequestProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<RequestPlayerJoin>();
        
        if(message?.ClientId != null) {
            float yRot = Random.Shared.NextSingle() * 360.0f;

            PlayerData newPlayerData = new() {
                Id = message.ClientId,
                Name = message.Message.Nickname,
                YRotation = yRot,
                CurrentPosition = SimpleVector3.Zero
            };
            
            // Send joined player info to all clients
            UDPServer.Instance.QueueSend(0, new PushPlayerInfoSingle {
                Player = newPlayerData
            });
            
            // Register player
            if(PlayerManager.AddPlayer(message.ClientId, newPlayerData, out long dbId)) {
                UDPServer.Instance.clientDbIdMap.Add(message.ClientId, (dbId, message.Message.Nickname));
            }
            
            // Send all players info to joined player
            UDPServer.Instance.QueueSend(message.ClientId, new PushPlayersInfo {
                Players = PlayerManager.ForEachPlayer().ToArray()
            });
            
            // Send rank data to joined player
            RankManager.PushRankData(message.ClientId, true);
            
            return true;
        }

        return false;
    }
}

public class PlayerPositionProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyPlayerPosition>();
        
        if(message?.ClientId != null) {
            PlayerManager.SetPlayerPosition(message.ClientId, message.Message.Position);
            
            UDPServer.Instance.QueueSend(0, new PushPlayerPosition {
                PlayerId = message.ClientId,
                Position = message.Message.Position
            });
            
            return true;
        }

        return false;
    }
}

public class PlayerClickProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<NotifyPlayerClick>();

        if(message?.ClientId == null) return false;
        
        PlayerManager.SetPlayerPosition(message.ClientId, message.Message.Position);
        
        UDPServer.Instance.QueueSend(0, new PushPlayerClick {
            PlayerId = message.ClientId,
            Position = message.Message.Position
        });
        
        if(DotManager.HitTest(message.Message.Position, out ulong dotId)) {
            DotManager.ClearDot(dotId, UDPServer.Instance.clientDbIdMap[message.ClientId].dbId, message.ClientId);
        }

        return true;
    }
}