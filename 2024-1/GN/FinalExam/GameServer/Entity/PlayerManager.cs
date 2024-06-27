using System.Collections.Concurrent;
using GameServer.Database;
using GameServer.Messages.Models;

namespace GameServer.Entity;

public struct PlayerData {
    public uint Id { get; set; }
    public string Name { get; set; }
    public float YRotation { get; set; }
    public SimpleVector3 CurrentPosition { get; set; }
}

public static class PlayerManager {
    private static readonly ConcurrentDictionary<uint, PlayerData> playerPositions = new();
    
    public static IEnumerable<PlayerData> ForEachPlayer() {
        return playerPositions.Select(player => player.Value);
    }

    public static bool AddPlayer(uint id, PlayerData data, out long dbId) {
        playerPositions.TryAdd(id, data);
        
        dbId = DatabaseUtility.InsertOne(DatabaseClient.Instance.Connection, TableNames.Users, new Dictionary<string, string> {
            { "nickname", data.Name }
        }) ?? -1;
        DatabaseUtility.InsertOne(DatabaseClient.Instance.Connection, TableNames.Records, new Dictionary<string, string> {
            { "userId", dbId.ToString() },
            { "hitCount", "0" }
        });

        return dbId >= 0;
    }

    public static PlayerData? GetPlayerPosition(uint id) {
        if(playerPositions.TryGetValue(id, out var position)) {
            return position;
        }

        return null;
    }
    
    public static void SetPlayerPosition(uint id, SimpleVector3 position) {
        PlayerData data = playerPositions[id];
        data.CurrentPosition = position;
        playerPositions[id] = data;
    }
    
    public static void RemovePlayer(uint id) {
        playerPositions.TryRemove(id, out _);
    }
}
