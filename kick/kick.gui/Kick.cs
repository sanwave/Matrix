using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kick.Gui
{
    class Kick
    {
        public static string Execute(string command)
        {
            string output = "";
            try
            {

                Process cmd = new Process();
                cmd.StartInfo.FileName = "kick";
                cmd.StartInfo.Arguments = command;

                cmd.StartInfo.UseShellExecute = false;

                cmd.StartInfo.RedirectStandardInput = true;
                cmd.StartInfo.RedirectStandardOutput = true;

                cmd.StartInfo.CreateNoWindow = true;
                cmd.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;

                cmd.Start();

                output = cmd.StandardOutput.ReadToEnd();
                Console.WriteLine(output);
                cmd.WaitForExit();
                cmd.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            return output;
        }
    }
}
