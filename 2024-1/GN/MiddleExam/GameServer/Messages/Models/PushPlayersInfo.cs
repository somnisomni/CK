namespace GameServer.Messages.Models;

public struct PlayerData {
    public int Id { get; set; }
    public string Name { get; set; }
}

public class PushPlayersInfo : MessageBase {
    public PlayerData[] Players { get; set; }
}
