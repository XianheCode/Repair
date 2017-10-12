namespace SignalGenerator
{
    partial class SignalCtrlForm
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
            this.groupBox_connect = new System.Windows.Forms.GroupBox();
            this.button_cancel = new System.Windows.Forms.Button();
            this.textBoxBaud = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textBoxCom = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonOnLine = new System.Windows.Forms.Button();
            this.buttonShutDown = new System.Windows.Forms.Button();
            this.buttonSignalOff = new System.Windows.Forms.Button();
            this.buttonSignalOn = new System.Windows.Forms.Button();
            this.groupBox_select = new System.Windows.Forms.GroupBox();
            this.button_setRevTime = new System.Windows.Forms.Button();
            this.textBox_RevTime = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonChangePattern = new System.Windows.Forms.Button();
            this.buttonChangeModel = new System.Windows.Forms.Button();
            this.textBoxPatternName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxModelName = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBox_control = new System.Windows.Forms.GroupBox();
            this.button_saveSignalPrm = new System.Windows.Forms.Button();
            this.btn_hide = new System.Windows.Forms.Button();
            this.groupBox_connect.SuspendLayout();
            this.groupBox_select.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox_control.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox_connect
            // 
            this.groupBox_connect.Controls.Add(this.button_cancel);
            this.groupBox_connect.Controls.Add(this.textBoxBaud);
            this.groupBox_connect.Controls.Add(this.label2);
            this.groupBox_connect.Controls.Add(this.buttonConnect);
            this.groupBox_connect.Controls.Add(this.textBoxCom);
            this.groupBox_connect.Controls.Add(this.label1);
            this.groupBox_connect.Location = new System.Drawing.Point(24, 22);
            this.groupBox_connect.Name = "groupBox_connect";
            this.groupBox_connect.Size = new System.Drawing.Size(321, 97);
            this.groupBox_connect.TabIndex = 0;
            this.groupBox_connect.TabStop = false;
            this.groupBox_connect.Text = "串口设置";
            // 
            // button_cancel
            // 
            this.button_cancel.Location = new System.Drawing.Point(222, 55);
            this.button_cancel.Name = "button_cancel";
            this.button_cancel.Size = new System.Drawing.Size(76, 29);
            this.button_cancel.TabIndex = 5;
            this.button_cancel.Text = "关闭串口";
            this.button_cancel.UseVisualStyleBackColor = true;
            this.button_cancel.Click += new System.EventHandler(this.button_cancel_Click);
            // 
            // textBoxBaud
            // 
            this.textBoxBaud.Location = new System.Drawing.Point(77, 61);
            this.textBoxBaud.Name = "textBoxBaud";
            this.textBoxBaud.Size = new System.Drawing.Size(100, 21);
            this.textBoxBaud.TabIndex = 4;
            this.textBoxBaud.Text = "9600";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "波特率：";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(222, 20);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(76, 29);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "打开串口";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textBoxCom
            // 
            this.textBoxCom.Location = new System.Drawing.Point(77, 20);
            this.textBoxCom.Name = "textBoxCom";
            this.textBoxCom.Size = new System.Drawing.Size(100, 21);
            this.textBoxCom.TabIndex = 1;
            this.textBoxCom.Text = "4";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(36, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "COM：";
            // 
            // buttonOnLine
            // 
            this.buttonOnLine.Location = new System.Drawing.Point(29, 23);
            this.buttonOnLine.Name = "buttonOnLine";
            this.buttonOnLine.Size = new System.Drawing.Size(76, 31);
            this.buttonOnLine.TabIndex = 1;
            this.buttonOnLine.Text = "OnLine";
            this.buttonOnLine.UseVisualStyleBackColor = true;
            this.buttonOnLine.Click += new System.EventHandler(this.buttonOnLine_Click);
            // 
            // buttonShutDown
            // 
            this.buttonShutDown.Location = new System.Drawing.Point(29, 290);
            this.buttonShutDown.Name = "buttonShutDown";
            this.buttonShutDown.Size = new System.Drawing.Size(76, 31);
            this.buttonShutDown.TabIndex = 2;
            this.buttonShutDown.Text = "关机";
            this.buttonShutDown.UseVisualStyleBackColor = true;
            this.buttonShutDown.Click += new System.EventHandler(this.buttonShutDown_Click_1);
            // 
            // buttonSignalOff
            // 
            this.buttonSignalOff.Location = new System.Drawing.Point(29, 149);
            this.buttonSignalOff.Name = "buttonSignalOff";
            this.buttonSignalOff.Size = new System.Drawing.Size(76, 31);
            this.buttonSignalOff.TabIndex = 4;
            this.buttonSignalOff.Text = "关光";
            this.buttonSignalOff.UseVisualStyleBackColor = true;
            this.buttonSignalOff.Click += new System.EventHandler(this.button4_Click);
            // 
            // buttonSignalOn
            // 
            this.buttonSignalOn.Location = new System.Drawing.Point(29, 100);
            this.buttonSignalOn.Name = "buttonSignalOn";
            this.buttonSignalOn.Size = new System.Drawing.Size(76, 31);
            this.buttonSignalOn.TabIndex = 3;
            this.buttonSignalOn.Text = "开光";
            this.buttonSignalOn.UseVisualStyleBackColor = true;
            this.buttonSignalOn.Click += new System.EventHandler(this.button5_Click);
            // 
            // groupBox_select
            // 
            this.groupBox_select.Controls.Add(this.button_setRevTime);
            this.groupBox_select.Controls.Add(this.textBox_RevTime);
            this.groupBox_select.Controls.Add(this.button2);
            this.groupBox_select.Controls.Add(this.button1);
            this.groupBox_select.Controls.Add(this.buttonChangePattern);
            this.groupBox_select.Controls.Add(this.buttonChangeModel);
            this.groupBox_select.Controls.Add(this.textBoxPatternName);
            this.groupBox_select.Controls.Add(this.label3);
            this.groupBox_select.Controls.Add(this.textBoxModelName);
            this.groupBox_select.Controls.Add(this.label4);
            this.groupBox_select.Location = new System.Drawing.Point(24, 152);
            this.groupBox_select.Name = "groupBox_select";
            this.groupBox_select.Size = new System.Drawing.Size(321, 206);
            this.groupBox_select.TabIndex = 5;
            this.groupBox_select.TabStop = false;
            this.groupBox_select.Text = "更改设置";
            // 
            // button_setRevTime
            // 
            this.button_setRevTime.Location = new System.Drawing.Point(168, 160);
            this.button_setRevTime.Name = "button_setRevTime";
            this.button_setRevTime.Size = new System.Drawing.Size(96, 31);
            this.button_setRevTime.TabIndex = 10;
            this.button_setRevTime.Text = "设置接收延时";
            this.button_setRevTime.UseVisualStyleBackColor = true;
            this.button_setRevTime.Click += new System.EventHandler(this.button_setRevTime_Click);
            // 
            // textBox_RevTime
            // 
            this.textBox_RevTime.Location = new System.Drawing.Point(38, 166);
            this.textBox_RevTime.Name = "textBox_RevTime";
            this.textBox_RevTime.Size = new System.Drawing.Size(100, 21);
            this.textBox_RevTime.TabIndex = 8;
            this.textBox_RevTime.Text = "0";
            this.textBox_RevTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(168, 119);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(76, 31);
            this.button2.TabIndex = 6;
            this.button2.Text = "上一个模式";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(38, 119);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(76, 31);
            this.button1.TabIndex = 7;
            this.button1.Text = "下一个模式";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonChangePattern
            // 
            this.buttonChangePattern.Location = new System.Drawing.Point(222, 71);
            this.buttonChangePattern.Name = "buttonChangePattern";
            this.buttonChangePattern.Size = new System.Drawing.Size(76, 31);
            this.buttonChangePattern.TabIndex = 6;
            this.buttonChangePattern.Text = "更改模式";
            this.buttonChangePattern.UseVisualStyleBackColor = true;
            this.buttonChangePattern.Click += new System.EventHandler(this.buttonChangePattern_Click);
            // 
            // buttonChangeModel
            // 
            this.buttonChangeModel.Location = new System.Drawing.Point(222, 22);
            this.buttonChangeModel.Name = "buttonChangeModel";
            this.buttonChangeModel.Size = new System.Drawing.Size(76, 31);
            this.buttonChangeModel.TabIndex = 6;
            this.buttonChangeModel.Text = "更改模型";
            this.buttonChangeModel.UseVisualStyleBackColor = true;
            this.buttonChangeModel.Click += new System.EventHandler(this.buttonChangeModel_Click);
            // 
            // textBoxPatternName
            // 
            this.textBoxPatternName.Location = new System.Drawing.Point(77, 77);
            this.textBoxPatternName.Name = "textBoxPatternName";
            this.textBoxPatternName.Size = new System.Drawing.Size(100, 21);
            this.textBoxPatternName.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 80);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "模式名：";
            // 
            // textBoxModelName
            // 
            this.textBoxModelName.Location = new System.Drawing.Point(77, 28);
            this.textBoxModelName.Name = "textBoxModelName";
            this.textBoxModelName.Size = new System.Drawing.Size(100, 21);
            this.textBoxModelName.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 31);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "模型名：";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 365);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(491, 22);
            this.statusStrip1.TabIndex = 6;
            this.statusStrip1.Text = "111";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(476, 17);
            this.toolStripStatusLabel1.Spring = true;
            this.toolStripStatusLabel1.Text = "wait";
            this.toolStripStatusLabel1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // groupBox_control
            // 
            this.groupBox_control.Controls.Add(this.btn_hide);
            this.groupBox_control.Controls.Add(this.button_saveSignalPrm);
            this.groupBox_control.Controls.Add(this.buttonSignalOn);
            this.groupBox_control.Controls.Add(this.buttonSignalOff);
            this.groupBox_control.Controls.Add(this.buttonShutDown);
            this.groupBox_control.Controls.Add(this.buttonOnLine);
            this.groupBox_control.Location = new System.Drawing.Point(360, 22);
            this.groupBox_control.Name = "groupBox_control";
            this.groupBox_control.Size = new System.Drawing.Size(119, 336);
            this.groupBox_control.TabIndex = 7;
            this.groupBox_control.TabStop = false;
            this.groupBox_control.Text = "控制";
            // 
            // button_saveSignalPrm
            // 
            this.button_saveSignalPrm.Location = new System.Drawing.Point(29, 197);
            this.button_saveSignalPrm.Name = "button_saveSignalPrm";
            this.button_saveSignalPrm.Size = new System.Drawing.Size(76, 31);
            this.button_saveSignalPrm.TabIndex = 5;
            this.button_saveSignalPrm.Text = "应用参数";
            this.button_saveSignalPrm.UseVisualStyleBackColor = true;
            this.button_saveSignalPrm.Click += new System.EventHandler(this.button_saveSignalPrm_Click);
            // 
            // btn_hide
            // 
            this.btn_hide.Location = new System.Drawing.Point(29, 249);
            this.btn_hide.Name = "btn_hide";
            this.btn_hide.Size = new System.Drawing.Size(76, 31);
            this.btn_hide.TabIndex = 6;
            this.btn_hide.Text = "隐藏窗口";
            this.btn_hide.UseVisualStyleBackColor = true;
            this.btn_hide.Click += new System.EventHandler(this.btn_hide_Click);
            // 
            // SignalCtrlForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(491, 387);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox_control);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox_select);
            this.Controls.Add(this.groupBox_connect);
            this.Location = new System.Drawing.Point(300, 300);
            this.Name = "SignalCtrlForm";
            this.Text = "LightPrm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.groupBox_connect.ResumeLayout(false);
            this.groupBox_connect.PerformLayout();
            this.groupBox_select.ResumeLayout(false);
            this.groupBox_select.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox_control.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox_connect;
        private System.Windows.Forms.TextBox textBoxBaud;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textBoxCom;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonOnLine;
        private System.Windows.Forms.Button buttonShutDown;
        private System.Windows.Forms.Button buttonSignalOff;
        private System.Windows.Forms.Button buttonSignalOn;
        private System.Windows.Forms.GroupBox groupBox_select;
        private System.Windows.Forms.Button buttonChangePattern;
        private System.Windows.Forms.Button buttonChangeModel;
        private System.Windows.Forms.TextBox textBoxPatternName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxModelName;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.GroupBox groupBox_control;
        private System.Windows.Forms.Button button_cancel;
        private System.Windows.Forms.Button button_setRevTime;
        private System.Windows.Forms.TextBox textBox_RevTime;
        private System.Windows.Forms.Button button_saveSignalPrm;
        private System.Windows.Forms.Button btn_hide;
    }
}

