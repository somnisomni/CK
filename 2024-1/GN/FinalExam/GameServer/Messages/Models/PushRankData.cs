namespace GameServer.Messages.Models;

public struct RankData {
    public uint PlayerId { get; set; }
    public string PlayerNickname { get; set; }
    public uint HitCount { get; set; }
}

public class PushRankData : MessageBase {
    public RankData[] Rank { get; set; }
}
