namespace GameServer.Messages.Models;

public class PushPlayerClick : MessageBaseWithPosition {
    public uint PlayerId { get; set; }
}
