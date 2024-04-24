namespace GameServer.Messages.Models;

public class NotifyCarMoveStart : MessageBase {
    public float DragDistance { get; set; }
}