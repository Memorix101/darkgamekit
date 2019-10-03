using System;
using System.IO;

namespace JustForFunCompiler
{
    class Program
    {
        private static string read_cfg = "NOT SET";
        private static string _filePath;

        static void Main(string[] args)
        {
            _filePath = AppDomain.CurrentDomain.BaseDirectory + "/main.cpp";
            Console.WriteLine("DarkGameKit DBPro Compiler v0.01");
            PrepareCFG();
            Console.ReadLine();
        }

        static void PrepareCFG()
        {
            // Create a file to write to
            using (StreamWriter sw = File.CreateText(_filePath))
            {
                sw.WriteLine("\n\tint main(void) \n" +
                             "\t{\n" +
                             "\t\tStartGDK();\n" +
                             "\t\tDarkGDK();\n" +
                             "\t\treturn 0;\n" +
                             "\t}");
            }

            ReadCFG();
        }

        static void ReadCFG()
        {
            // Open the file to read from.
            using (StreamReader sr = File.OpenText(_filePath))
            {
                string s = "";
                while ((s = sr.ReadLine()) != null)
                {
                    Console.WriteLine(s);

                    if (s.StartsWith("test="))
                    {
                        read_cfg = s.Substring(10);
                    }
                }
            }
        }
    }
}
