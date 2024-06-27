using System.Collections.ObjectModel;
using GameServer.Messages;
using GameServer.Processor;
using Newtonsoft.Json.Linq;

namespace GameServer;

public static class RequestController {
    private static ReadOnlyDictionary<MessageId, ProcessorBase[]> Processors { get; } = new(new Dictionary<MessageId, ProcessorBase[]> {
        { MessageId.NotifyClientShutdown, new ProcessorBase[] { new ClientShutdownProcessor() } },
        { MessageId.NotifyPlayerPosition, new ProcessorBase[] { new PlayerPositionProcessor() } },
        { MessageId.NotifyPlayerClick, new ProcessorBase[] { new PlayerClickProcessor() } },
        { MessageId.RequestPlayerJoin, new ProcessorBase[] { new PlayerJoinRequestProcessor() } }
    });

    public static bool TryProcess(JObject messageRaw) {
        Processors.TryGetValue(messageRaw.ParseMessageMetadataOnly().MessageId, out ProcessorBase[]? processors);
        
        return processors != null && processors.All((proc) => proc.Process(messageRaw));
    }
}
