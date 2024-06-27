using GameServer.Entity;
using GameServer.Messages.Models;

namespace GameServer.Processor;

public static class DotGenerateProcessor {
    // Not a packet processor

    private static ulong lastDotId = 1;
    
    public static void Process() {
        while(true) {
            if(!UDPServer.Instance.HasAnyClients) continue;

            Thread.Sleep(Random.Shared.Next(
                minValue: Constants.DotGenerateIntervalBase - Constants.DotGenerateIntervalRange,
                maxValue: Constants.DotGenerateIntervalBase + Constants.DotGenerateIntervalRange
            ));
            
            foreach(var _ in DotManager.ForEachDot()) { } // Cleanup expired dots

            int count = Random.Shared.Next(1, 3);
            List<DotData> dots = new();

            for(int i = 0; i < count; i++) {
                double x = Math.Round(Random.Shared.NextSingle() * Constants.DotGenerateXRange - (Constants.DotGenerateXRange / 2.0f), 3);
                double z = Math.Round(Random.Shared.NextSingle() * Constants.DotGenerateZRange - (Constants.DotGenerateZRange / 2.0f), 3);
                DotData dot = new() {
                    Id = lastDotId,
                    Position = new SimpleVector3 {
                        X = (float)x,
                        Y = 0.0f,
                        Z = (float)z,
                    },
                    GeneratedAt = DateTimeOffset.Now.ToUnixTimeSeconds()
                };
                
                dots.Add(dot);
                DotManager.AddDot(lastDotId, dot);
                
                lastDotId++;
            }

            UDPServer.Instance.QueueSend(0, new PushDotsData {
                Dots = dots.ToArray()
            });
        }
    }
}