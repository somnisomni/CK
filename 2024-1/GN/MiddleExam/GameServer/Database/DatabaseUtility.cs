using MySql.Data.MySqlClient;

namespace GameServer.Database;

public static class DatabaseUtility {
    public static MySqlDataReader SelectOne(MySqlConnection connection, string tableName, int id) {
        MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"SELECT * FROM {tableName} WHERE id = @id";
        command.Parameters.AddWithValue("@id", id);
        
        return command.ExecuteReader();
    }
    
    public static MySqlDataReader SelectAll(MySqlConnection connection, string tableName) {
        MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"SELECT * FROM {tableName}";
        
        return command.ExecuteReader();
    }
    
    public static bool InsertOne(MySqlConnection connection, string tableName, Dictionary<string, string> data) {
        List<string> fieldNames = new(), fieldValues = new();
        foreach(var item in data) {
            fieldNames.Add(MySqlHelper.EscapeString(item.Key));
            fieldValues.Add($"\"{MySqlHelper.EscapeString(item.Value)}\"");
        }
        
        MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"INSERT INTO {tableName} ({string.Join(",", fieldNames)}) VALUES ({string.Join(",", fieldValues)})";

        return command.ExecuteNonQuery() == 1;
    }
}
