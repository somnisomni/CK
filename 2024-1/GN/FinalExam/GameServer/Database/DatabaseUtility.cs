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
    
    public static bool UpdateOne(MySqlConnection connection, string tableName, int id, Dictionary<string, string> data) {
        List<string> fields = new();
        foreach(var item in data) {
            fields.Add($"{MySqlHelper.EscapeString(item.Key)} = \"{MySqlHelper.EscapeString(item.Value)}\"");
        }
        
        using MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"UPDATE {tableName} SET {string.Join(",", fields)} WHERE id = @id";
        command.Parameters.AddWithValue("@id", id);

        return command.ExecuteNonQuery() == 1;
    }
    
    public static bool IncrementField(MySqlConnection connection, string tableName, int userId, string fieldName, int amount) {
        using MySqlCommand command = DatabaseClient.Instance.Connection.CreateCommand();
        command.CommandText = $"UPDATE {tableName} SET {MySqlHelper.EscapeString(fieldName)} = {MySqlHelper.EscapeString(fieldName)} + @amount WHERE userId = @userId";
        command.Parameters.AddWithValue("@userId", userId);
        command.Parameters.AddWithValue("@amount", amount);

        return command.ExecuteNonQuery() == 1;
    }
}
