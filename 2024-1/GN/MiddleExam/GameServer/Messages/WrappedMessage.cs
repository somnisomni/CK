using GameServer.Messages.Models;

namespace GameServer.Messages;

public sealed class WrappedMessage<T> where T: MessageBase {
    public uint ClientId { get; set; }
    public MessageId MessageId { get; set; }
    
    public T Message { get; set; }
}
