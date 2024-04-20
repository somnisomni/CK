using System.Collections.ObjectModel;
using GameServer.Messages;
using GameServer.Processor;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class RequestController {
    private static ReadOnlyDictionary<MessageId, ProcessorBase> Processors { get; } = new(new Dictionary<MessageId, ProcessorBase> {
        { MessageId.StartGameRequest, new StartGameProcessor() },
        { MessageId.NotifyCarDistance, new CarDistanceProcessor() },
    });

    public static bool TryProcess(JObject messageRaw) {
        Processors.TryGetValue(messageRaw.ParseMessageMetadataOnly().MessageId, out ProcessorBase? processor);

        return processor != null && processor.Process(messageRaw);
    }
}
