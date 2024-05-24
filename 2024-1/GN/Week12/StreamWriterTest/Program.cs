using System.Text;

public class Program {
    public static void Main(string[] args) {
        MemoryStream ms = new MemoryStream();
        {
            using StreamWriter sw = new StreamWriter(ms, Encoding.UTF8);
            using StreamReader sr = new StreamReader(ms, Encoding.UTF8);
        
            sw.WriteLine("It's high noon");
            sw.Write(16384);
            sw.Flush();

            ms.Position = 0;
            string txt = sr.ReadToEnd();

            Console.WriteLine(txt);
        }
        
        // --- //
        {
            ms.Dispose();
            ms = new MemoryStream();
            using BinaryWriter bw = new BinaryWriter(ms, Encoding.UTF8);
            using BinaryReader br = new BinaryReader(ms, Encoding.UTF8);

            bw.Write("Wow it's working" + Environment.NewLine);
            bw.Write(33443);

            ms.Position = 0;
            string first = br.ReadString();
            int second = br.ReadInt32();
            
            Console.Write(first);
            Console.WriteLine(second);
        }
    }
}