namespace GameServer.Messages.Models;

public struct RecordData {
    public string Name { get; set; }
    public double MinimumDistance { get; set; }
    public double DragTimespan { get; set; }
}

public class PushRankData : MessageBase {
    public RecordData[] Rank { get; set; }    
}
