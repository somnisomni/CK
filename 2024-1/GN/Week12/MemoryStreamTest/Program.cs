public class Program {
    public static void Main(string[] args) {
        byte[] shortBytes = BitConverter.GetBytes((short)32000);
        byte[] intBytes = BitConverter.GetBytes(12345678);
        using MemoryStream ms = new MemoryStream();
        
        ms.Write(shortBytes, 0, shortBytes.Length);
        ms.Write(intBytes, 0, intBytes.Length);
        ms.Position = 0;

        byte[] outBytes = new byte[2];
        ms.Read(outBytes, 0, 2);
        int shortResult = BitConverter.ToInt16(outBytes, 0);
        Console.WriteLine(shortResult);
        
        outBytes = new byte[4];
        ms.Read(outBytes, 0, 4);
        int intResult = BitConverter.ToInt32(outBytes, 0);
        Console.WriteLine(intResult);
    }
}