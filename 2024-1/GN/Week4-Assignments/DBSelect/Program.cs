using MySql.Data.MySqlClient;

class Program {
    static void Main(string[] args) {
        const string connStr = "Server=localhost;Port=9999;Database=assignmentdb;Uid=testuser;Pwd=test;";
        using MySqlConnection connection = new(connStr);

        // DB 연결
        try {
            connection.Open();
            Console.WriteLine("DB Connected!");
        } catch(MySqlException ex) {
            Console.WriteLine("Connect error: {0}", ex.Message);
            Environment.Exit(1);
        }

        while(true) {
            // 검색할 ID 입력
            Console.Write("\nEnter ID to search (negative number to exit): ");
            if(!int.TryParse(Console.ReadLine()!, out int inputId)) {
                Console.WriteLine("Invalid input, only numbers are allowed.");
                continue;
            }

            // 음수 입력 시 종료
            if(inputId < 0) break;
            
            // ID로 DB 레코드 검색
            string query = $"SELECT * FROM assignmentdb.Week5_Table1 WHERE id=@id";
            MySqlCommand command = new(query, connection);
            command.Parameters.AddWithValue("@id", inputId);
            
            // 검색 결과 출력
            using var reader = command.ExecuteReader();
            if(reader.HasRows) {
                while(reader.Read()) {
                    // 필드 값이 NULL이면 NULL이라고 출력
                    string text = reader.IsDBNull(reader.GetOrdinal("text")) ? "text(null)" : $"text: {reader.GetString("text")}";
                    string value = reader.IsDBNull(reader.GetOrdinal("value")) ? "value(null)" : $"value: {reader.GetInt32("value").ToString()}";
                    
                    Console.WriteLine($"id: {reader["id"]}, {text}, {value}");
                }
            } else {
                Console.WriteLine($"No record found for ID {inputId}!");
            }
        }
    }
}
