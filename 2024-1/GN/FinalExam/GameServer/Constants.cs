namespace GameServer;

public static class Constants {
    public const string ClientIdRequestString = "SESSION_REQUEST";

    public const float DotGenerateXRange = 3.0f;  // -2.0f ~ 2.0f
    public const float DotGenerateZRange = 3.0f;  // -2.0f ~ 2.0f
    public const int DotGenerateIntervalBase = 1000;
    public const int DotGenerateIntervalRange = 500;
    
    public const string DBHost = "localhost";
    public const int DBPort = 9999;
    public const string DBUser = "dev";
    public const string DBPass = "dev";
    public const string DBName = "GNFinalExam";
}
