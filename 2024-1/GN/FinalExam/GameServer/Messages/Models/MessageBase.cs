namespace GameServer.Messages.Models;

public struct SimpleVector3 {
    public float X { get; set; }
    public float Y { get; set; }
    public float Z { get; set; }
    
    public static SimpleVector3 Zero => new() { X = 0.0f, Y = 0.0f, Z = 0.0f };
    
    public static float Distance(SimpleVector3 a, SimpleVector3 b) {
        return (float)Math.Sqrt(Math.Pow(b.X - a.X, 2) + Math.Pow(b.Y - a.Y, 2) + Math.Pow(b.Z - a.Z, 2));
    }
}

public struct SimpleVector2 {
    public float X { get; set; }
    public float Y { get; set; }
    
    public static SimpleVector2 Zero => new() { X = 0.0f, Y = 0.0f };
}

public abstract class MessageBase { }

public abstract class MessageBaseWithPosition : MessageBase {
    public SimpleVector3 Position { get; set; }
}
