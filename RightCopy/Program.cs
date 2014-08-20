using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace RightCopy
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length >= 2)
            {
                string str = "";
                switch (args[0])
                {
                    case "Path":
                        str = args[1];
                        break;
                    case "Name":
                        int f = args[1].LastIndexOf("\\");
                        if (f > 0)
                        {
                            str = args[1].Substring(f + 1, args[1].Length - f - 1);
                        }
                        else { str = args[1]; }
                        break;
                }
                if (str != "")
                {
                    Clipboard.SetData(DataFormats.Text, (object)str);
                }
            }
        }
    }
}
