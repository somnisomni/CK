namespace GameServer.Messages.Models;

public class PushPlayerPosition : MessageBaseWithPosition {
    public uint PlayerId { get; set; }
}
