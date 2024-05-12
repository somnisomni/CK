using System.Net;

namespace AddressTest {
    class IPAddressExample {
        public static void PrintHostInfo(string host) {
            try {
                IPHostEntry hostInfo;

                hostInfo = Dns.GetHostEntry(host);

                Console.WriteLine($"\t Canonical name: {hostInfo.HostName}");

                Console.Write("\t IP addresses: ");
                foreach(IPAddress ipAddr in hostInfo.AddressList) {
                    Console.Write(ipAddr.ToString() + " ");
                }

                Console.WriteLine();

                Console.Write("\t Aliases: ");
                foreach(string alias in hostInfo.Aliases) {
                    Console.Write(alias + " ");
                }

                Console.WriteLine();
            } catch(Exception) {
                Console.WriteLine("\t Unable to resolve host: " + host);
            }

            Console.WriteLine();
        }

        public static void Main(string[] args) {
            Console.WriteLine();
            
            try {
                Console.WriteLine("*** Local Host ***");
                Console.WriteLine($"\t Host name: {Dns.GetHostName()}");

                PrintHostInfo(Dns.GetHostName());
            } catch(Exception) {
                Console.WriteLine("Unable to resolve local host\n");
            }

            foreach(string arg in args) {
                Console.WriteLine($"*** Host: {arg} ***");
                PrintHostInfo(arg);
            }
        }
    }
}