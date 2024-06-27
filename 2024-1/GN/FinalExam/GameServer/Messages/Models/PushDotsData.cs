using GameServer.Entity;

namespace GameServer.Messages.Models;

public class PushDotsData : MessageBase {
    public DotData[] Dots { get; set; }
}
