using MySql.Data.MySqlClient;

namespace GameServer.Database;

public static class DatabaseUtility {
    public static MySqlDataReader ExecuteQueryWithReader(MySqlConnection connection, string query) {
        MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = query;

        return command.ExecuteReader();
    }
    
    public static MySqlDataReader SelectOne(MySqlConnection connection, string tableName, int id) {
        MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"SELECT * FROM {tableName} WHERE id = @id";
        command.Parameters.AddWithValue("@id", id);
        
        return command.ExecuteReader();
    }
    
    public static MySqlDataReader SelectAll(MySqlConnection connection, string tableName) {
        return ExecuteQueryWithReader(connection, $"SELECT * FROM {MySqlHelper.EscapeString(tableName)}");
    }
    
    public static long? InsertOne(MySqlConnection connection, string tableName, Dictionary<string, string> data) {
        List<string> fieldNames = new(), fieldValues = new();
        foreach(var item in data) {
            fieldNames.Add(MySqlHelper.EscapeString(item.Key));
            fieldValues.Add($"\"{MySqlHelper.EscapeString(item.Value)}\"");
        }
        
        using MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"INSERT INTO {tableName} ({string.Join(",", fieldNames)}) VALUES ({string.Join(",", fieldValues)})";

        if(command.ExecuteNonQuery() == 1) {
            return command.LastInsertedId;
        }

        return null;
    }
}
