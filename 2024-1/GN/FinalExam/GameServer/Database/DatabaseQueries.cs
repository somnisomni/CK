namespace GameServer.Database;

public static class DatabaseQueries {
    public const string TopFiveRank = $"SELECT users.id as id, nickname, hitCount"
                                      + " FROM users LEFT JOIN records"
                                      + " ON users.id = records.userId"
                                      + " WHERE hitCount > 0"
                                      + " ORDER BY hitCount DESC"
                                      + " LIMIT 5";
    
    public static string GetMyHitCountQuery(long userId) => $"SELECT hitCount FROM records WHERE userId = {userId}";
}
