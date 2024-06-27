namespace GameServer.Messages.Models;

public class NotifyPlayerClick : MessageBaseWithPosition {
    public uint PlayerId { get; set; }
}
