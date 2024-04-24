using System.Collections.ObjectModel;
using GameServer.Messages.Models;

namespace GameServer.Messages;

public enum MessageId : uint {
    Unspecified = 0,
    
    // Server -> Client Responses
    AcquireClientIdResponse = 10001,
    StartGameResponse = 10002,
    
    // Client -> Server Notifications
    NotifyClientShutdown = 20001,
    NotifyCarDistance = 20002,
    NotifyCarMoveStart = 20003,
    NotifyPlayerRestart = 20004,
    
    // Server -> Client Pushes
    PushRankData = 30001,
    PushPlayersInfo = 30002,
    PushPlayerInfoSingle = 30003,
    PushPlayerShutdown = 30004,
    PushPlayerCarMoveStart = 30005,
    PushPlayerRestart = 30006,
    
    // Client -> Server Requests
    StartGameRequest = 40001,
}

public class MessageFactory {
    private static MessageFactory? _instance = null;
    public static MessageFactory Instance => _instance ??= new MessageFactory();

    public static ReadOnlyDictionary<MessageId, Type> MessageTypes { get; } = new(new Dictionary<MessageId, Type> {
        { MessageId.AcquireClientIdResponse, typeof(AcquireClientIdResponse) },
        { MessageId.StartGameResponse, typeof(StartGameResponse) },
        { MessageId.NotifyClientShutdown, typeof(NotifyClientShutdown) },
        { MessageId.NotifyCarDistance, typeof(NotifyCarDistance) },
        { MessageId.NotifyCarMoveStart, typeof(NotifyCarMoveStart) },
        { MessageId.NotifyPlayerRestart, typeof(NotifyPlayerRestart) },
        { MessageId.PushRankData, typeof(PushRankData) },
        { MessageId.PushPlayersInfo, typeof(PushPlayersInfo) },
        { MessageId.PushPlayerInfoSingle, typeof(PushPlayerInfoSingle) },
        { MessageId.PushPlayerShutdown, typeof(PushPlayerShutdown) },
        { MessageId.PushPlayerCarMoveStart, typeof(PushPlayerCarMoveStart) },
        { MessageId.PushPlayerRestart, typeof(PushPlayerRestart) },
        { MessageId.StartGameRequest, typeof(StartGameRequest) }
    });

    private MessageFactory() { }
    
    public WrappedMessage<T> CreateMessage<T>(T baseMessage, uint clientId = 0) where T : MessageBase {
        if(GetMessageId<T>() is MessageId messageId) {
            return new WrappedMessage<T> {
                ClientId = clientId,
                MessageId = messageId,
                Message = baseMessage
            };
        }

        throw new InvalidOperationException("Can't find message type for the given message.");
    }
    
    public Type GetMessageType(MessageId messageId) {
        return MessageTypes[messageId];
    }
    
    private MessageId? GetMessageId<T>() where T : MessageBase {
        return MessageTypes.First(item => item.Value == typeof(T)).Key;
    }
}
