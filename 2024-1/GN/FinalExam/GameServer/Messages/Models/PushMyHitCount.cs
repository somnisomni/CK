namespace GameServer.Messages.Models;

public class PushMyHitCount : MessageBase {
    public uint HitCount { get; set; }
}
