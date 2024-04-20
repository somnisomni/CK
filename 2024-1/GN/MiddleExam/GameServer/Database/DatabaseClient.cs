using MySql.Data.MySqlClient;

namespace GameServer.Database;

public static class TableNames {
    public const string Users = "users";
    public const string Records = "records";
}

public sealed class DatabaseClient: IDisposable {
    private static DatabaseClient? _instance = null;
    public static DatabaseClient Instance => _instance ??= new DatabaseClient();

    public MySqlConnection Connection { get; private set; } = null;
    
    private DatabaseClient() {
        try {
            Connection =
                new MySqlConnection(
                    $"Server={Constants.DBHost};Port={Constants.DBPort};Database={Constants.DBName};Uid={Constants.DBUser};Pwd={Constants.DBPass};");
            Connection.Open();
            Console.WriteLine("[DB] Database connection opened.");
        } catch(Exception e) {
            Console.WriteLine("[DB/ERR] Opening database connection failed.");
        }
    }
    
    ~DatabaseClient() {
        Dispose();
    }
    
    public void Dispose() {
        Connection?.Close();
        Connection?.Dispose();
        Connection = null;

        _instance = null;
        GC.SuppressFinalize(this);
    }
}
