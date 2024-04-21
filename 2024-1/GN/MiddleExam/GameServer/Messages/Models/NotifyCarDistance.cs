namespace GameServer.Messages.Models;

public class NotifyCarDistance: MessageBase {
    public double Distance { get; set; }
    public double DragTimespan { get; set; }
}