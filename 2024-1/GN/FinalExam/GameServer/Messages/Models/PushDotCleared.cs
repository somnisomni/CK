namespace GameServer.Messages.Models;

public class PushDotCleared : MessageBase {
    public ulong DotId { get; set; }
}
