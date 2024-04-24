namespace GameServer.Messages.Models;

public class PushPlayerShutdown : MessageBase {
    public uint ClientId { get; set; }
}
