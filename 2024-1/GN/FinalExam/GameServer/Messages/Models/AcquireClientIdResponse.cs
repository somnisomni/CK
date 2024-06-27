namespace GameServer.Messages.Models;

public class AcquireClientIdResponse: MessageBase {
    public uint ClientId { get; set; }
}
