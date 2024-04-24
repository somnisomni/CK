namespace GameServer.Messages.Models;

public class PushPlayerRestart : MessageBase {
    public uint ClientId { get; set; }
}
