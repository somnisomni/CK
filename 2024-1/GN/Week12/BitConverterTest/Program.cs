public class Program {
    public static void Main(string[] args) {
        byte[] boolBytes = BitConverter.GetBytes(true);
        byte[] shortBytes = BitConverter.GetBytes((short)32000);
        byte[] intBytes = BitConverter.GetBytes(12345678);
        
        Console.WriteLine(BitConverter.ToString(boolBytes));
        Console.WriteLine(BitConverter.ToString(shortBytes));
        Console.WriteLine(BitConverter.ToString(intBytes));
        
        bool boolValue = BitConverter.ToBoolean(boolBytes, 0);
        short shortValue = BitConverter.ToInt16(shortBytes, 0);
        int intValue = BitConverter.ToInt32(intBytes, 0);
        
        Console.WriteLine(boolValue);
        Console.WriteLine(shortValue);
        Console.WriteLine(intValue);
    }
}