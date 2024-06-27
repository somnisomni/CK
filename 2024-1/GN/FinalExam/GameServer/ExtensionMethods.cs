using GameServer.Messages;
using GameServer.Messages.Models;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class ExtensionMethods {
    public static WrappedMessage<T>? ParseMessage<T>(this JObject jObject) where T : MessageBase {
        if(jObject.TryGetValue("MessageId", out JToken? messageIdToken)
           && messageIdToken.Value<uint>() is uint messageIdRaw
           && Enum.IsDefined(typeof(MessageId), messageIdRaw)
           && Enum.TryParse(messageIdRaw.ToString(), out MessageId messageId)
           && MessageFactory.Instance.GetMessageType(messageId) == typeof(T)
               
           && jObject.TryGetValue("ClientId", out JToken? clientIdToken)
           && clientIdToken.Value<uint>() is uint clientId
               
           && jObject.TryGetValue("Message", out JToken? messageToken)
           && messageToken.ToObject<T>() is T realMessage) {
            return new WrappedMessage<T> {
                ClientId = clientId,
                MessageId = messageId,
                Message = realMessage
            };
        }

        return null;
    }

    public static WrappedMessage<MessageBase> ParseMessageMetadataOnly(this JObject jObject) {
        if(jObject.TryGetValue("MessageId", out JToken? messageIdToken)
           && messageIdToken.Value<uint>() is uint messageIdRaw
           && Enum.IsDefined(typeof(MessageId), messageIdRaw)
           && Enum.TryParse(messageIdRaw.ToString(), out MessageId messageId)

           && jObject.TryGetValue("ClientId", out JToken? clientIdToken)
           && clientIdToken.Value<uint>() is uint clientId) {
            return new WrappedMessage<MessageBase> {
                ClientId = clientId,
                MessageId = messageId
            };
        }

        return null;
    }
    
    public static WrappedMessage<T>? ParseMessageFromJson<T>(this string json) where T : MessageBase {
        return JObject.Parse(json).ParseMessage<T>();
    }
}
