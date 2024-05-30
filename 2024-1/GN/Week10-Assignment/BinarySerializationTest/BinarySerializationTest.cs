public class BinarySerializationTest {
    /// <summary>
    /// 테스트용 바이너리 데이터
    ///
    /// string "Awesome Data!",
    ///    int 111,
    ///  float 23.456f,
    /// double 19.4464253d,
    ///   bool true
    /// </summary>
    private static readonly byte[] TEST_DATA = new byte[] {
        0x0D,  // string length
        0x41, 0x77, 0x65, 0x73, 0x6F, 0x6D, 0x65, 0x20, 0x44, 0x61, 0x74, 0x61, 0x21,  // string content
        
        0x6F, 0x00, 0x00, 0x00, // int
        0xE3, 0xA5, 0xBB, 0x41, // float(single)
        0x64, 0x9B, 0xAF, 0xED, 0x48, 0x72, 0x33, 0x40, // double
        0x01                    // bool
    };
    // BinaryReader/Writer는 Little-endian으로 데이터를 읽고 쓴다.
    // 참고: https://learn.microsoft.com/en-us/dotnet/api/system.io.binarywriter.write
    
    public static void Main(string[] args) {
        // 데이터 읽기
        Console.WriteLine("*** Read binary data");
        {
            using var stream = new MemoryStream(TEST_DATA);
            using var reader = new BinaryReader(stream);
            
            string str = reader.ReadString();
            int    i   = reader.ReadInt32();
            float  f   = reader.ReadSingle();
            double d   = reader.ReadDouble();
            bool   b   = reader.ReadBoolean();
            
            Console.WriteLine($"String: {str}");
            Console.WriteLine($"Int: {i}");
            Console.WriteLine($"Float: {f}");
            Console.WriteLine($"Double: {d}");
            Console.WriteLine($"Bool: {b}");
        }
        Console.WriteLine();
        
        // 데이터 쓰기
        Console.WriteLine("*** Write binary data");
        {
            using var stream = new MemoryStream();
            using var writer = new BinaryWriter(stream);
            
            const string str = "Another Data!";
            const int    i   = 222;
            const float  f   = 563.24f;
            const double d   = 0.123456789d;
            const bool   b   = false;

            Console.WriteLine(str); writer.Write("Another Data!");
            Console.WriteLine(i);   writer.Write(222);
            Console.WriteLine(f);   writer.Write(563.24f);
            Console.WriteLine(d);   writer.Write(0.123456789d);
            Console.WriteLine(b);   writer.Write(false);

            stream.Position = 0;
            byte[] data = stream.ToArray();
            Console.WriteLine("0x" + BitConverter.ToString(data).Replace("-", " 0x"));
        }
        Console.WriteLine();
    }
}
