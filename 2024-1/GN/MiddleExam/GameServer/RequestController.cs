using System.Collections.ObjectModel;
using GameServer.Messages;
using GameServer.Processor;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class RequestController {
    private static ReadOnlyDictionary<MessageId, ProcessorBase[]> Processors { get; } = new(new Dictionary<MessageId, ProcessorBase[]> {
        { MessageId.StartGameRequest, new ProcessorBase[] { new StartGameProcessor(), new PushGameInitialData() } },
        { MessageId.NotifyCarDistance, new ProcessorBase[] { new CarDistanceProcessor() } },
        { MessageId.NotifyClientShutdown, new ProcessorBase[] { new ClientShutdownProcessor() } },
        { MessageId.NotifyPlayerRestart, new ProcessorBase[] { new PlayerRestartProcessor() } },
        { MessageId.NotifyCarMoveStart, new ProcessorBase[] { new PlayerCarMoveProcessor() } }
    });

    public static bool TryProcess(JObject messageRaw) {
        Processors.TryGetValue(messageRaw.ParseMessageMetadataOnly().MessageId, out ProcessorBase[]? processors);
        
        return processors != null && processors.All((proc) => proc.Process(messageRaw));
    }
}
