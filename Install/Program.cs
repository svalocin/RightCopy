using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Install
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n 本软件主要功能是为鼠标右键菜单加入“复制路径”“复制名称”的功能");
            Console.WriteLine("\n 选择操作：安装输入“1”，卸载输入“2”，退出输入“3”");
        Put: Console.Write("\n 操作：");
            string r = Console.ReadLine();
            switch (r)
            {
                case "1":
                    Install();
                    break;
                case "2":
                    Uninstall();
                    break;
                case "3":
                    return;
                default:
                    Console.WriteLine("\n 请输入正确的参数！");
                    goto Put;
            }

            Console.WriteLine("\n 按任意键推出...");
            Console.ReadKey(true);
        }

        private static void Install()
        {
            string rootPath = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;

            Console.WriteLine("\n 开始安装...");
            if (File.Exists("ContextCopy.exe") && File.Exists("install.reg"))
            {
                Console.WriteLine("\n 设置注册表项目...");
                string regPath = rootPath + "r.reg";
                StreamReader sr = new StreamReader(rootPath + "install.reg");
                StreamWriter sw = new StreamWriter(regPath, false, System.Text.Encoding.Unicode);

                string str = sr.ReadLine();
                string exePath = (rootPath + "ContextCopy.exe").Replace(@"\", @"\\");

                while (str != null)
                {
                    str = str.Replace("%exePath%", exePath);
                    sw.WriteLine(str);
                    str = sr.ReadLine();
                }
                sw.Close();

                Console.WriteLine("\n 导入注册表...");
                Process.Start("regedit", string.Format(" /s \"{0}\"", regPath));

                System.Threading.Thread.Sleep(3000);
                File.Delete(regPath);
                Console.WriteLine("\n 安装完成！！！");
            }
            else
            {
                Console.WriteLine("\n 安装程序已经损坏，无法安装");
            }
        }

        private static void Uninstall()
        {
            //删除注册表
            RegistryKey key = Registry.ClassesRoot;
            key.DeleteSubKey(@"*\shell\CopyName\command", false);
            key.DeleteSubKey(@"*\shell\CopyName", false);
            key.DeleteSubKey(@"*\shell\CopyPath\command", false);
            key.DeleteSubKey(@"*\shell\CopyPath", false);
            key.DeleteSubKey(@"Directory\shell\CopyName\command", false);
            key.DeleteSubKey(@"Directory\shell\CopyName", false);
            key.DeleteSubKey(@"Directory\shell\CopyPath\command", false);
            key.DeleteSubKey(@"Directory\shell\CopyPath", false);

            key.Close();

            Console.WriteLine("\n 删除完成！！！");
        }
    }
}
