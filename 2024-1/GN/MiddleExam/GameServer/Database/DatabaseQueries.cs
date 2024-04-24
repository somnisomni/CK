namespace GameServer.Database;

public static class DatabaseQueries {
    public const string TopFiveRank = $"SELECT userName, minimumDistance, dragTimespan"
                                      + " FROM records"
                                      + " WHERE minimumDistance >= 0 AND dragTimespan > 0"
                                      + " ORDER BY minimumDistance ASC, dragTimespan ASC"
                                      + " LIMIT 5";
}
