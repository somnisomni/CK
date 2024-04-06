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
            Console.Write("\nEnter ID to edit (-1 to add, -2 or below to exit): ");
            if(!int.TryParse(Console.ReadLine()!, out int inputId)) {
                Console.WriteLine("Invalid input, only numbers are allowed.");
                continue;
            }

            // 음수 입력 시 종료
            if(inputId <= -2) {
                break;
            } else if(inputId <= -1) {
                AddRecord(connection);
                continue;
            }
            
            // ID로 DB 레코드 검색
            string query = $"SELECT * FROM assignmentdb.Week5_Table3 WHERE id=@id";
            MySqlCommand command = new(query, connection);
            command.Parameters.AddWithValue("@id", inputId);
            
            // 검색 결과 출력
            var reader = command.ExecuteReader();
            if(reader.HasRows) {
                while(reader.Read()) {
                    Console.WriteLine($"id: {reader["id"]}, {reader["name"]}, age: {reader["age"]}");
                }
                reader.Close();
            } else {
                Console.WriteLine($"No record found for ID {inputId}!");
                reader.Close();
                continue;
            }
            
            // 옵션 출력
            Console.WriteLine("\n1. Update record");
            Console.WriteLine("2. Delete record");
            Console.WriteLine("0. Return to main\n");
            Console.Write("Select an option: ");
            if(!int.TryParse(Console.ReadLine()!, out int option)) {
                Console.WriteLine("Invalid input, only numbers are allowed.");
                continue;
            }

            switch(option) {
                case 0: continue;
                case 1: UpdateRecord(connection, inputId); break;
                case 2: DeleteRecord(connection, inputId); break;
                default: Console.WriteLine("Invalid option, please try again."); break;
            }
        }
    }
    
    static void UpdateRecord(in MySqlConnection connection, int id) {
        // 필드 출력
        Console.WriteLine("[name (string)] [age (int)]");
        
        // 필드값 입력
        Console.Write("Input values in a row: ");
        string[] input = Console.ReadLine()!.Split();

        if(input.Length != 2) {
            Console.WriteLine("Invalid input, exactly 2 values are required.");
            return;
        }
        
        // 업데이트 쿼리 설정
        string query = "UPDATE assignmentdb.Week5_Table3 SET name=@name, age=@age WHERE id=@id";
        MySqlCommand command = new(query, connection);
        command.Parameters.AddWithValue("@id", id);
        command.Parameters.AddWithValue("@name", MySqlHelper.EscapeString(input[0]));
        command.Parameters.AddWithValue("@age", int.Parse(input[1]));
        
        // 쿼리 실행
        try {
            command.ExecuteNonQuery();
            Console.WriteLine("Record updated successfully!");
        } catch(MySqlException ex) {
            Console.WriteLine("Update error: {0}", ex.Message);
        }
    }

    static void DeleteRecord(in MySqlConnection connection, int id) {
        // 삭제 쿼리 설정
        string query = "DELETE FROM assignmentdb.Week5_Table3 WHERE id=@id";
        MySqlCommand command = new(query, connection);
        command.Parameters.AddWithValue("@id", id);
        
        // 쿼리 실행
        try {
            command.ExecuteNonQuery();
            Console.WriteLine("Record deleted successfully!");
        } catch(MySqlException ex) {
            Console.WriteLine("Delete error: {0}", ex.Message);
        }
    }

    static void AddRecord(in MySqlConnection connection) {
        // 필드 출력
        Console.WriteLine("[name (string)] [age (int)]");
        
        // 필드값 입력
        Console.Write("Input values in a row: ");
        string[] input = Console.ReadLine()!.Split();
            
        if(input.Length != 2) {
            Console.WriteLine("Invalid input, exactly 2 values are required.");
            return;
        }
        
        // 추가 쿼리 설정
        string query = "INSERT INTO assignmentdb.Week5_Table3 (name, age) VALUES (@name, @age)";
        MySqlCommand command = new(query, connection);
        command.Parameters.AddWithValue("@name", MySqlHelper.EscapeString(input[0]));
        command.Parameters.AddWithValue("@age", int.Parse(input[1]));
        
        // 쿼리 실행
        try {
            command.ExecuteNonQuery();
            Console.WriteLine("Record added successfully!");
        } catch(MySqlException ex) {
            Console.WriteLine("Add error: {0}", ex.Message);
        }
    }
}
