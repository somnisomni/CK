using System.Collections.Concurrent;
using GameServer.Database;
using GameServer.Messages.Models;

namespace GameServer.Entity;

public struct DotData {
    public ulong Id { get; set; }
    public SimpleVector3 Position { get; set; }
    public long GeneratedAt { get; set; } // Timestamp
}

public static class DotManager {
    private static readonly ConcurrentDictionary<ulong, DotData> dots = new();

    private const float radius = 0.33f;
    private const long timeToLive = 5; // seconds
    
    public static IEnumerable<DotData> ForEachDot() {
        foreach(var dot in dots) {
            if(dot.Value.GeneratedAt + timeToLive < DateTimeOffset.Now.ToUnixTimeSeconds()) {
                dots.TryRemove(dot.Key, out _);
                continue;
            }
            
            yield return dot.Value;
        }
    }
    
    public static void AddDot(ulong id, DotData data) {
        dots.TryAdd(id, data);
    }
    
    public static bool HitTest(SimpleVector3 position, out ulong dotId) {
        foreach(var dot in ForEachDot()) {
            var positionNormalized = position with { Y = 0.0f };
            var dotPositionNormalized = dot.Position with { Y = 0.0f };
            
            if(SimpleVector3.Distance(positionNormalized,dotPositionNormalized) <= radius / 2) {
                dotId = dot.Id;
                return true;
            }
        }

        dotId = 0;
        return false;
    }
    
    public static void ClearDot(ulong dotId, long hitByDbId, uint hitByClientId) {
        if(!dots.TryRemove(dotId, out _)) {
            Console.WriteLine($"Ignore nonexistent dot removal (dot ID: {dotId})");
            return;
        }

        // DB update
        DatabaseUtility.IncrementField(DatabaseClient.Instance.Connection, TableNames.Records, (int)hitByDbId, "hitCount", 1);
        
        // Push dot cleared to all
        UDPServer.Instance.QueueSend(0, new PushDotCleared {
            DotId = dotId
        });
        
        // Push rank data to all
        RankManager.PushRankData();
        
        // Push hit count to the player
        var hitCount = RankManager.QueryMyHitCount(hitByDbId);
        if(hitCount != null) {
            UDPServer.Instance.QueueSend(hitByClientId, new PushMyHitCount {
                HitCount = hitCount.Value
            });
        }
    }
}
