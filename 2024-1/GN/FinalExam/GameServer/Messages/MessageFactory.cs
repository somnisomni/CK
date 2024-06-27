using System.Collections.ObjectModel;
using GameServer.Messages.Models;

namespace GameServer.Messages;

public enum MessageId : uint {
    Unspecified = 0,
    
    // Server -> Client Responses
    AcquireClientIdResponse = 10001,
    
    // Client -> Server Notifications
    NotifyClientShutdown = 20001,
    NotifyPlayerPosition = 20002,
    NotifyPlayerClick = 20003,
    
    // Server -> Client Pushes
    PushPlayersInfo = 30001,
    PushPlayerInfoSingle = 30002,
    PushPlayerShutdown = 30003,
    PushPlayerPosition = 30004,
    PushDotsData = 30005,
    PushPlayerClick = 30006,
    PushDotCleared = 30007,
    PushRankData = 30008,
    PushMyHitCount = 30009,
    
    // Client -> Server Requests
    RequestPlayerJoin = 40001
}

public class MessageFactory {
    private static MessageFactory? _instance = null;
    public static MessageFactory Instance => _instance ??= new MessageFactory();

    public static ReadOnlyDictionary<MessageId, Type> MessageTypes { get; } = new(new Dictionary<MessageId, Type> {
        { MessageId.NotifyClientShutdown, typeof(NotifyClientShutdown) },
        { MessageId.NotifyPlayerPosition, typeof(NotifyPlayerPosition) },
        { MessageId.NotifyPlayerClick , typeof(NotifyPlayerClick) },
        { MessageId.AcquireClientIdResponse, typeof(AcquireClientIdResponse) },
        { MessageId.PushPlayersInfo, typeof(PushPlayersInfo) },
        { MessageId.PushPlayerInfoSingle, typeof(PushPlayerInfoSingle) },
        { MessageId.PushPlayerShutdown, typeof(PushPlayerShutdown) },
        { MessageId.PushPlayerPosition, typeof(PushPlayerPosition) },
        { MessageId.PushPlayerClick, typeof(PushPlayerClick) },
        { MessageId.PushDotsData, typeof(PushDotsData) },
        { MessageId.PushDotCleared, typeof(PushDotCleared) },
        { MessageId.PushRankData, typeof(PushRankData) },
        { MessageId.PushMyHitCount, typeof(PushMyHitCount) },
        { MessageId.RequestPlayerJoin, typeof(RequestPlayerJoin) }
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
        try {
            return MessageTypes[messageId];
        } catch(KeyNotFoundException) {
            Console.Error.WriteLine($"Message ID unrecognized! {Enum.GetName(messageId)}");
            return null;
        }
    }
    
    private MessageId? GetMessageId<T>() where T : MessageBase {
        return MessageTypes.First(item => item.Value == typeof(T)).Key;
    }
}
