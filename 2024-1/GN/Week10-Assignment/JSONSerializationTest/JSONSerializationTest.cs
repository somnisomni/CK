using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

public class JSONSerializationTest {
    /// <summary>
    /// 테스트용 JSON 문자열
    /// </summary>
    private const string TEST_JSON = "{" +
                                     "  \"name\": \"John\"," +
                                     "  \"grade\": 2," +
                                     "  \"lastAvgScore\": 3.336," +
                                     "  \"extraInfo\": null" +
                                     "}";
    
    /// <summary>
    /// 직렬화/역직렬화할 학생 구조체
    /// </summary>
    public readonly struct Student {
        public string Name { get; }
        public int Grade { get; }
        public double LastAvgScore { get; }
        public string? ExtraInfo { get; }
        
        // 변경할 수 없는 타입(여기서는 "읽기 전용 구조체")의 경우,
        // 생성자에 JsonConstructor 어트리뷰트를 사용해야 역직렬화 가능
        // 참고: https://learn.microsoft.com/ko-kr/dotnet/standard/serialization/system-text-json/immutability
        [JsonConstructor]
        public Student(string name, int grade, double lastAvgScore, string? extraInfo) {
            Name = name;
            Grade = grade;
            LastAvgScore = lastAvgScore;
            ExtraInfo = extraInfo;
        }

        public override string ToString() {
            return $"Student Name: {Name}, Grade: {Grade}, LastAvgScore: {LastAvgScore}, ExtraInfo: {ExtraInfo ?? "(null)"}";
        }
    }
    
    public static void Main(string[] args) {
        // JSON 직렬화 옵션 설정 (프로퍼티명이 카멜 케이스임을 지정)
        var options = new JsonSerializerOptions {
            PropertyNamingPolicy = JsonNamingPolicy.CamelCase
        };
        
        // JSON 문자열을 plain object로 역직렬화
        Console.WriteLine("*** Deserialize JSON to plain object");
        object? student = JsonSerializer.Deserialize<object>(TEST_JSON, options);
        Console.WriteLine(student);
        Console.WriteLine();
        
        // JSON 문자열을 구조체 타입을 지정하여 역직렬화
        Console.WriteLine("*** Deserialize JSON to struct");
        Student typedStudent = JsonSerializer.Deserialize<Student>(TEST_JSON, options);
        Console.WriteLine(typedStudent);
        Console.WriteLine();
        
        // 코드 상에서 생성된 구조체 객체를 JSON 문자열로 직렬화
        Console.WriteLine("*** Serialize struct to JSON");
        Student newStudent = new("Jane", 1, 4.2242d, "Awesome student");
        string newStudentJson = JsonSerializer.Serialize(newStudent, options);
        Console.WriteLine(newStudent);
        Console.WriteLine($" -> {newStudentJson}");
        Console.WriteLine();
        
        // 메모리 스트림으로부터 JSON 문자열을 역직렬화
        Console.WriteLine("*** Deserialize JSON from memory stream");
        {
            using var stream = new MemoryStream(Encoding.UTF8.GetBytes(TEST_JSON));
            Student streamStudent = JsonSerializer.Deserialize<Student>(stream, options);
            Console.WriteLine(streamStudent);
        }
        Console.WriteLine();
        
        // 메모리 스트림에 구조체를 JSON 문자열로 직렬화
        Console.WriteLine("*** Serialize JSON to memory stream");
        {
            using var stream = new MemoryStream();
            JsonSerializer.Serialize(stream, newStudent, options);
            Console.WriteLine(Encoding.UTF8.GetString(stream.ToArray()));
        }
        Console.WriteLine();
    }
}
