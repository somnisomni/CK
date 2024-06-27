using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public abstract class ProcessorBase {
    public abstract bool Process(JObject messageRaw);
}
