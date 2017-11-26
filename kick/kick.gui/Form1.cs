using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Kick.Gui
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UpdateUi();
        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            UpdateUi();
        }
        
        private void UpdateUi()
        {
            tbxSendAddr.Width = this.Width - btnSend.Width - 37;
            tbxListenPort.Width = this.Width - btnListen.Width - 37;

            int box2_height = (int)((this.Height - 130) * 0.4);
            box2_height = box2_height < 180 ? box2_height : 180;
            bgxSendHeader.Height = box2_height;
            gbxSendBody.Height = this.Height - 130 - box2_height;
            bgxListenLog.Height = this.Height - 130;
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            string output = Kick.Execute("kick -r " + tbxSendHeader.Text + tbxSendBody.Text);
            MessageBox.Show(output);
        }

        private void btnListen_Click(object sender, EventArgs e)
        {

        }
    }
}
