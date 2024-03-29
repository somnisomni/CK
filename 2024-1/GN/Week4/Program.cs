using MySql.Data.MySqlClient;

public class Program {
    public static void Main(string[] args) {
        string connStr = "Server=localhost;Database=gamedb;Uid=root;";
        using MySqlConnection connection = new MySqlConnection(connStr);
        
        try {
            connection.Open();

            // string query =
            //    "INSERT INTO gamedb.User(userid, name, password, phonenumber) VALUES ('csharp2', 'C# Test 2', 'awesomegood', '010-1111-0000')";

            string query = "UPDATE gamedb.User SET password='thisisverylongpassword' WHERE userid='csharp2'";
            
            MySqlCommand command = new MySqlCommand(query, connection);
            Console.WriteLine($"success: {command.ExecuteNonQuery()} row(s) affected");
            
            connection.Close();
        } catch (MySqlException ex) {
            Console.WriteLine("Error: {0}", ex.StackTrace);
        }
    }
}
