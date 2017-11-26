namespace Kick.Gui
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.bgxSendAddr = new System.Windows.Forms.GroupBox();
            this.tbxSendAddr = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.bgxSendHeader = new System.Windows.Forms.GroupBox();
            this.tbxSendHeader = new System.Windows.Forms.TextBox();
            this.gbxSendBody = new System.Windows.Forms.GroupBox();
            this.tbxSendBody = new System.Windows.Forms.TextBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.gbxListenPort = new System.Windows.Forms.GroupBox();
            this.btnListen = new System.Windows.Forms.Button();
            this.tbxListenPort = new System.Windows.Forms.TextBox();
            this.bgxListenLog = new System.Windows.Forms.GroupBox();
            this.tbxListenLog = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.bgxSendAddr.SuspendLayout();
            this.bgxSendHeader.SuspendLayout();
            this.gbxSendBody.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.gbxListenPort.SuspendLayout();
            this.bgxListenLog.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(695, 441);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.bgxSendAddr);
            this.tabPage1.Controls.Add(this.bgxSendHeader);
            this.tabPage1.Controls.Add(this.gbxSendBody);
            this.tabPage1.Location = new System.Drawing.Point(4, 23);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(687, 414);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "发送";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // bgxSendAddr
            // 
            this.bgxSendAddr.Controls.Add(this.tbxSendAddr);
            this.bgxSendAddr.Controls.Add(this.btnSend);
            this.bgxSendAddr.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bgxSendAddr.Location = new System.Drawing.Point(3, 6);
            this.bgxSendAddr.Name = "bgxSendAddr";
            this.bgxSendAddr.Size = new System.Drawing.Size(681, 67);
            this.bgxSendAddr.TabIndex = 4;
            this.bgxSendAddr.TabStop = false;
            this.bgxSendAddr.Text = "对端地址";
            // 
            // tbxSendAddr
            // 
            this.tbxSendAddr.Font = new System.Drawing.Font("Consolas", 20F);
            this.tbxSendAddr.Location = new System.Drawing.Point(6, 17);
            this.tbxSendAddr.Name = "tbxSendAddr";
            this.tbxSendAddr.Size = new System.Drawing.Size(540, 39);
            this.tbxSendAddr.TabIndex = 0;
            // 
            // btnSend
            // 
            this.btnSend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSend.Location = new System.Drawing.Point(552, 17);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(126, 39);
            this.btnSend.TabIndex = 1;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // bgxSendHeader
            // 
            this.bgxSendHeader.Controls.Add(this.tbxSendHeader);
            this.bgxSendHeader.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bgxSendHeader.Location = new System.Drawing.Point(3, 73);
            this.bgxSendHeader.Name = "bgxSendHeader";
            this.bgxSendHeader.Size = new System.Drawing.Size(681, 140);
            this.bgxSendHeader.TabIndex = 3;
            this.bgxSendHeader.TabStop = false;
            this.bgxSendHeader.Text = "消息头";
            // 
            // tbxSendHeader
            // 
            this.tbxSendHeader.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbxSendHeader.Font = new System.Drawing.Font("Consolas", 11F);
            this.tbxSendHeader.Location = new System.Drawing.Point(3, 18);
            this.tbxSendHeader.Multiline = true;
            this.tbxSendHeader.Name = "tbxSendHeader";
            this.tbxSendHeader.Size = new System.Drawing.Size(675, 119);
            this.tbxSendHeader.TabIndex = 0;
            // 
            // gbxSendBody
            // 
            this.gbxSendBody.Controls.Add(this.tbxSendBody);
            this.gbxSendBody.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.gbxSendBody.Location = new System.Drawing.Point(3, 213);
            this.gbxSendBody.Name = "gbxSendBody";
            this.gbxSendBody.Size = new System.Drawing.Size(681, 198);
            this.gbxSendBody.TabIndex = 2;
            this.gbxSendBody.TabStop = false;
            this.gbxSendBody.Text = "消息体";
            // 
            // tbxSendBody
            // 
            this.tbxSendBody.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbxSendBody.Font = new System.Drawing.Font("Consolas", 11F);
            this.tbxSendBody.Location = new System.Drawing.Point(3, 18);
            this.tbxSendBody.Multiline = true;
            this.tbxSendBody.Name = "tbxSendBody";
            this.tbxSendBody.Size = new System.Drawing.Size(675, 177);
            this.tbxSendBody.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.gbxListenPort);
            this.tabPage2.Controls.Add(this.bgxListenLog);
            this.tabPage2.Location = new System.Drawing.Point(4, 23);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(687, 414);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "接收";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // gbxListenPort
            // 
            this.gbxListenPort.Controls.Add(this.btnListen);
            this.gbxListenPort.Controls.Add(this.tbxListenPort);
            this.gbxListenPort.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.gbxListenPort.Location = new System.Drawing.Point(3, 17);
            this.gbxListenPort.Name = "gbxListenPort";
            this.gbxListenPort.Size = new System.Drawing.Size(681, 67);
            this.gbxListenPort.TabIndex = 0;
            this.gbxListenPort.TabStop = false;
            this.gbxListenPort.Text = "监听端口";
            // 
            // btnListen
            // 
            this.btnListen.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnListen.Font = new System.Drawing.Font("Consolas", 9F);
            this.btnListen.Location = new System.Drawing.Point(552, 17);
            this.btnListen.Name = "btnListen";
            this.btnListen.Size = new System.Drawing.Size(126, 39);
            this.btnListen.TabIndex = 2;
            this.btnListen.Text = "Listen";
            this.btnListen.UseVisualStyleBackColor = true;
            this.btnListen.Click += new System.EventHandler(this.btnListen_Click);
            // 
            // tbxListenPort
            // 
            this.tbxListenPort.Font = new System.Drawing.Font("Consolas", 20F);
            this.tbxListenPort.Location = new System.Drawing.Point(6, 17);
            this.tbxListenPort.Name = "tbxListenPort";
            this.tbxListenPort.Size = new System.Drawing.Size(540, 39);
            this.tbxListenPort.TabIndex = 1;
            // 
            // bgxListenLog
            // 
            this.bgxListenLog.Controls.Add(this.tbxListenLog);
            this.bgxListenLog.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bgxListenLog.Location = new System.Drawing.Point(3, 84);
            this.bgxListenLog.Name = "bgxListenLog";
            this.bgxListenLog.Size = new System.Drawing.Size(681, 327);
            this.bgxListenLog.TabIndex = 1;
            this.bgxListenLog.TabStop = false;
            this.bgxListenLog.Text = "监听日志";
            // 
            // tbxListenLog
            // 
            this.tbxListenLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbxListenLog.Location = new System.Drawing.Point(3, 18);
            this.tbxListenLog.Multiline = true;
            this.tbxListenLog.Name = "tbxListenLog";
            this.tbxListenLog.Size = new System.Drawing.Size(675, 306);
            this.tbxListenLog.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 441);
            this.Controls.Add(this.tabControl1);
            this.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "Form1";
            this.Text = "Kick.Gui";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.SizeChanged += new System.EventHandler(this.Form1_SizeChanged);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.bgxSendAddr.ResumeLayout(false);
            this.bgxSendAddr.PerformLayout();
            this.bgxSendHeader.ResumeLayout(false);
            this.bgxSendHeader.PerformLayout();
            this.gbxSendBody.ResumeLayout(false);
            this.gbxSendBody.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.gbxListenPort.ResumeLayout(false);
            this.gbxListenPort.PerformLayout();
            this.bgxListenLog.ResumeLayout(false);
            this.bgxListenLog.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.TextBox tbxSendAddr;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox bgxSendHeader;
        private System.Windows.Forms.TextBox tbxSendHeader;
        private System.Windows.Forms.GroupBox gbxSendBody;
        private System.Windows.Forms.TextBox tbxSendBody;
        private System.Windows.Forms.GroupBox bgxSendAddr;
        private System.Windows.Forms.GroupBox bgxListenLog;
        private System.Windows.Forms.TextBox tbxListenLog;
        private System.Windows.Forms.GroupBox gbxListenPort;
        private System.Windows.Forms.Button btnListen;
        private System.Windows.Forms.TextBox tbxListenPort;
    }
}

