using GameServer.Entity;

namespace GameServer.Messages.Models;

public class PushPlayersInfo : MessageBase {
    public PlayerData[] Players { get; set; }
}
