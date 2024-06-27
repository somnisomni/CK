using System.Collections.ObjectModel;
using GameServer.Database;
using GameServer.Messages.Models;

namespace GameServer.Entity;

public static class RankManager {
    private static string lastSerializedRankData = string.Empty;
    
    /// <returns>`true` if rank data changed from last query</returns>
    public static bool QueryRankData(out ReadOnlyCollection<RankData> data) {
        using var reader = DatabaseUtility.ExecuteQueryWithReader(DatabaseClient.Instance.Connection, DatabaseQueries.TopFiveRank);
        var rankData = new List<RankData>();

        // db read
        while(reader.Read()) {
            rankData.Add(new RankData {
                PlayerId = Convert.ToUInt32(reader["id"]),
                PlayerNickname = (string)reader["nickname"],
                HitCount = Convert.ToUInt32(reader["hitCount"])
            });
        }

        // array out
        data = rankData.AsReadOnly();
        
        // check changes
        var serializedRankData = string.Join(',', rankData.Select(rank => $"{rank.PlayerId}:{rank.PlayerNickname}:{rank.HitCount}"));
        if(serializedRankData == lastSerializedRankData) return false;
        lastSerializedRankData = serializedRankData;
        return true;
    }

    public static uint? QueryMyHitCount(long playerDbId) {
        using var reader = DatabaseUtility.ExecuteQueryWithReader(
            DatabaseClient.Instance.Connection,
            DatabaseQueries.GetMyHitCountQuery(playerDbId)
        );

        if(reader.Read()) {
            return Convert.ToUInt32(reader["hitCount"]);
        }

        return null;
    }

    public static bool PushRankData(uint targetClientId = 0, bool force = false) {
        if(QueryRankData(out var rankData) || force) {
            UDPServer.Instance.QueueSend(targetClientId, new PushRankData {
                Rank = rankData.ToArray()
            });
            return true;
        }

        return false;
    }
}
