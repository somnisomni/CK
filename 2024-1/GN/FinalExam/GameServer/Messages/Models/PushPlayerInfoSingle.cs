using GameServer.Entity;

namespace GameServer.Messages.Models;

public class PushPlayerInfoSingle : MessageBase {
    public PlayerData Player { get; set; }
}
