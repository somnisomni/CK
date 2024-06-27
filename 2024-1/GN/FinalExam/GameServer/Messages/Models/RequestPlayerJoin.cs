namespace GameServer.Messages.Models;

public class RequestPlayerJoin : MessageBase {
    public string Nickname { get; set; }
}
