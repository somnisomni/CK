namespace GameServer.Messages.Models;

public class PushPlayerCarMoveStart : MessageBase {
    public uint ClientId { get; set; }
    public float DragDistance { get; set; }
}
