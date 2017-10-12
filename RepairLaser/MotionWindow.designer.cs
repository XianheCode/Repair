namespace MotionMod
{
    partial class MotionWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        public MotionMod.MotionControl m_motion = MotionControl.CreateMotion();

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.statusBar = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.button_Y_P = new System.Windows.Forms.Button();
            this.groupBox_MoveOp = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rBtn_jog = new System.Windows.Forms.RadioButton();
            this.rBtn_step = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.rBtn_pos = new System.Windows.Forms.RadioButton();
            this.textBox_StepDistance = new System.Windows.Forms.TextBox();
            this.radioButton_Move_L = new System.Windows.Forms.RadioButton();
            this.radioButton_Move_M = new System.Windows.Forms.RadioButton();
            this.radioButton_Move_H = new System.Windows.Forms.RadioButton();
            this.button_Z_P = new System.Windows.Forms.Button();
            this.button_Z_N = new System.Windows.Forms.Button();
            this.button_X_P = new System.Windows.Forms.Button();
            this.button_Y_N = new System.Windows.Forms.Button();
            this.button_X_N = new System.Windows.Forms.Button();
            this.groupBox_ControlOp = new System.Windows.Forms.GroupBox();
            this.button_setPrm = new System.Windows.Forms.Button();
            this.button_Home = new System.Windows.Forms.Button();
            this.button_Stop = new System.Windows.Forms.Button();
            this.groupBox_MoveState = new System.Windows.Forms.GroupBox();
            this.textBox_Y_Pos = new System.Windows.Forms.TextBox();
            this.textBox_Z_Pos = new System.Windows.Forms.TextBox();
            this.textBox_X_Pos = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.statusBar.SuspendLayout();
            this.groupBox_MoveOp.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox_ControlOp.SuspendLayout();
            this.groupBox_MoveState.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusBar
            // 
            this.statusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel});
            this.statusBar.Location = new System.Drawing.Point(0, 498);
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(350, 22);
            this.statusBar.TabIndex = 1;
            this.statusBar.Text = "wait";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(31, 17);
            this.statusLabel.Text = "wait";
            // 
            // button_Y_P
            // 
            this.button_Y_P.Location = new System.Drawing.Point(48, 36);
            this.button_Y_P.Name = "button_Y_P";
            this.button_Y_P.Size = new System.Drawing.Size(66, 32);
            this.button_Y_P.TabIndex = 2;
            this.button_Y_P.Text = "Y+";
            this.button_Y_P.UseVisualStyleBackColor = true;
            this.button_Y_P.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_Y_P_MouseDown);
            this.button_Y_P.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_Y_P_MouseUp);
            // 
            // groupBox_MoveOp
            // 
            this.groupBox_MoveOp.Controls.Add(this.groupBox1);
            this.groupBox_MoveOp.Controls.Add(this.radioButton_Move_L);
            this.groupBox_MoveOp.Controls.Add(this.radioButton_Move_M);
            this.groupBox_MoveOp.Controls.Add(this.radioButton_Move_H);
            this.groupBox_MoveOp.Controls.Add(this.button_Z_P);
            this.groupBox_MoveOp.Controls.Add(this.button_Z_N);
            this.groupBox_MoveOp.Controls.Add(this.button_X_P);
            this.groupBox_MoveOp.Controls.Add(this.button_Y_N);
            this.groupBox_MoveOp.Controls.Add(this.button_X_N);
            this.groupBox_MoveOp.Controls.Add(this.button_Y_P);
            this.groupBox_MoveOp.Location = new System.Drawing.Point(12, 137);
            this.groupBox_MoveOp.Name = "groupBox_MoveOp";
            this.groupBox_MoveOp.Size = new System.Drawing.Size(321, 269);
            this.groupBox_MoveOp.TabIndex = 3;
            this.groupBox_MoveOp.TabStop = false;
            this.groupBox_MoveOp.Text = "运动操作";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rBtn_jog);
            this.groupBox1.Controls.Add(this.rBtn_step);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.rBtn_pos);
            this.groupBox1.Controls.Add(this.textBox_StepDistance);
            this.groupBox1.Location = new System.Drawing.Point(7, 196);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(308, 45);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            // 
            // rBtn_jog
            // 
            this.rBtn_jog.AutoSize = true;
            this.rBtn_jog.Checked = true;
            this.rBtn_jog.Location = new System.Drawing.Point(139, 20);
            this.rBtn_jog.Name = "rBtn_jog";
            this.rBtn_jog.Size = new System.Drawing.Size(41, 16);
            this.rBtn_jog.TabIndex = 14;
            this.rBtn_jog.TabStop = true;
            this.rBtn_jog.Text = "Jog";
            this.rBtn_jog.UseVisualStyleBackColor = true;
            this.rBtn_jog.CheckedChanged += new System.EventHandler(this.rBtn_jog_CheckedChanged);
            // 
            // rBtn_step
            // 
            this.rBtn_step.AutoSize = true;
            this.rBtn_step.Location = new System.Drawing.Point(69, 20);
            this.rBtn_step.Name = "rBtn_step";
            this.rBtn_step.Size = new System.Drawing.Size(47, 16);
            this.rBtn_step.TabIndex = 13;
            this.rBtn_step.Text = "步进";
            this.rBtn_step.UseVisualStyleBackColor = true;
            this.rBtn_step.CheckedChanged += new System.EventHandler(this.rBtn_step_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(285, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 12);
            this.label1.TabIndex = 13;
            this.label1.Text = "mm";
            // 
            // rBtn_pos
            // 
            this.rBtn_pos.AutoSize = true;
            this.rBtn_pos.Location = new System.Drawing.Point(6, 20);
            this.rBtn_pos.Name = "rBtn_pos";
            this.rBtn_pos.Size = new System.Drawing.Size(47, 16);
            this.rBtn_pos.TabIndex = 12;
            this.rBtn_pos.Text = "点位";
            this.rBtn_pos.UseVisualStyleBackColor = true;
            this.rBtn_pos.CheckedChanged += new System.EventHandler(this.rBtn_pos_CheckedChanged);
            // 
            // textBox_StepDistance
            // 
            this.textBox_StepDistance.Location = new System.Drawing.Point(220, 15);
            this.textBox_StepDistance.Name = "textBox_StepDistance";
            this.textBox_StepDistance.Size = new System.Drawing.Size(59, 21);
            this.textBox_StepDistance.TabIndex = 12;
            this.textBox_StepDistance.Text = "1";
            this.textBox_StepDistance.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // radioButton_Move_L
            // 
            this.radioButton_Move_L.AutoSize = true;
            this.radioButton_Move_L.Checked = true;
            this.radioButton_Move_L.Location = new System.Drawing.Point(211, 164);
            this.radioButton_Move_L.Name = "radioButton_Move_L";
            this.radioButton_Move_L.Size = new System.Drawing.Size(47, 16);
            this.radioButton_Move_L.TabIndex = 10;
            this.radioButton_Move_L.TabStop = true;
            this.radioButton_Move_L.Text = "低速";
            this.radioButton_Move_L.UseVisualStyleBackColor = true;
            this.radioButton_Move_L.CheckedChanged += new System.EventHandler(this.radioButton_Move_L_CheckedChanged);
            // 
            // radioButton_Move_M
            // 
            this.radioButton_Move_M.AutoSize = true;
            this.radioButton_Move_M.Location = new System.Drawing.Point(109, 164);
            this.radioButton_Move_M.Name = "radioButton_Move_M";
            this.radioButton_Move_M.Size = new System.Drawing.Size(47, 16);
            this.radioButton_Move_M.TabIndex = 9;
            this.radioButton_Move_M.Text = "中速";
            this.radioButton_Move_M.UseVisualStyleBackColor = true;
            this.radioButton_Move_M.CheckedChanged += new System.EventHandler(this.radioButton_Move_M_CheckedChanged);
            // 
            // radioButton_Move_H
            // 
            this.radioButton_Move_H.AutoSize = true;
            this.radioButton_Move_H.Location = new System.Drawing.Point(7, 164);
            this.radioButton_Move_H.Name = "radioButton_Move_H";
            this.radioButton_Move_H.Size = new System.Drawing.Size(47, 16);
            this.radioButton_Move_H.TabIndex = 8;
            this.radioButton_Move_H.Text = "高速";
            this.radioButton_Move_H.UseVisualStyleBackColor = true;
            this.radioButton_Move_H.CheckedChanged += new System.EventHandler(this.radioButton_Move_H_CheckedChanged);
            // 
            // button_Z_P
            // 
            this.button_Z_P.Location = new System.Drawing.Point(209, 36);
            this.button_Z_P.Name = "button_Z_P";
            this.button_Z_P.Size = new System.Drawing.Size(66, 32);
            this.button_Z_P.TabIndex = 7;
            this.button_Z_P.Text = "Z+";
            this.button_Z_P.UseVisualStyleBackColor = true;
            this.button_Z_P.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_Z_P_MouseDown);
            this.button_Z_P.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_Z_P_MouseUp);
            // 
            // button_Z_N
            // 
            this.button_Z_N.Location = new System.Drawing.Point(209, 112);
            this.button_Z_N.Name = "button_Z_N";
            this.button_Z_N.Size = new System.Drawing.Size(66, 32);
            this.button_Z_N.TabIndex = 6;
            this.button_Z_N.Text = "Z-";
            this.button_Z_N.UseVisualStyleBackColor = true;
            this.button_Z_N.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_Z_N_MouseDown);
            this.button_Z_N.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_Z_N_MouseUp);
            // 
            // button_X_P
            // 
            this.button_X_P.Location = new System.Drawing.Point(93, 74);
            this.button_X_P.Name = "button_X_P";
            this.button_X_P.Size = new System.Drawing.Size(66, 32);
            this.button_X_P.TabIndex = 5;
            this.button_X_P.Text = "X+";
            this.button_X_P.UseVisualStyleBackColor = true;
            this.button_X_P.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_X_P_MouseDown);
            this.button_X_P.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_X_P_MouseUp);
            // 
            // button_Y_N
            // 
            this.button_Y_N.Location = new System.Drawing.Point(48, 112);
            this.button_Y_N.Name = "button_Y_N";
            this.button_Y_N.Size = new System.Drawing.Size(66, 32);
            this.button_Y_N.TabIndex = 4;
            this.button_Y_N.Text = "Y-";
            this.button_Y_N.UseVisualStyleBackColor = true;
            this.button_Y_N.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_Y_N_MouseDown);
            this.button_Y_N.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_Y_N_MouseUp);
            // 
            // button_X_N
            // 
            this.button_X_N.Location = new System.Drawing.Point(6, 74);
            this.button_X_N.Name = "button_X_N";
            this.button_X_N.Size = new System.Drawing.Size(66, 32);
            this.button_X_N.TabIndex = 3;
            this.button_X_N.Text = "X-";
            this.button_X_N.UseVisualStyleBackColor = true;
            this.button_X_N.MouseDown += new System.Windows.Forms.MouseEventHandler(this.button_X_N_MouseDown);
            this.button_X_N.MouseUp += new System.Windows.Forms.MouseEventHandler(this.button_X_N_MouseUp);
            // 
            // groupBox_ControlOp
            // 
            this.groupBox_ControlOp.Controls.Add(this.button_setPrm);
            this.groupBox_ControlOp.Controls.Add(this.button_Home);
            this.groupBox_ControlOp.Location = new System.Drawing.Point(12, 13);
            this.groupBox_ControlOp.Name = "groupBox_ControlOp";
            this.groupBox_ControlOp.Size = new System.Drawing.Size(136, 118);
            this.groupBox_ControlOp.TabIndex = 4;
            this.groupBox_ControlOp.TabStop = false;
            this.groupBox_ControlOp.Text = "控制操作";
            // 
            // button_setPrm
            // 
            this.button_setPrm.Location = new System.Drawing.Point(27, 69);
            this.button_setPrm.Name = "button_setPrm";
            this.button_setPrm.Size = new System.Drawing.Size(66, 32);
            this.button_setPrm.TabIndex = 6;
            this.button_setPrm.Text = "参数设置";
            this.button_setPrm.UseVisualStyleBackColor = true;
            this.button_setPrm.Click += new System.EventHandler(this.button_setPrm_Click);
            // 
            // button_Home
            // 
            this.button_Home.Location = new System.Drawing.Point(27, 20);
            this.button_Home.Name = "button_Home";
            this.button_Home.Size = new System.Drawing.Size(66, 32);
            this.button_Home.TabIndex = 5;
            this.button_Home.Text = "回原";
            this.button_Home.UseVisualStyleBackColor = true;
            this.button_Home.Click += new System.EventHandler(this.button_Home_Click);
            // 
            // button_Stop
            // 
            this.button_Stop.Location = new System.Drawing.Point(197, 51);
            this.button_Stop.Name = "button_Stop";
            this.button_Stop.Size = new System.Drawing.Size(90, 51);
            this.button_Stop.TabIndex = 4;
            this.button_Stop.Text = "停止";
            this.button_Stop.UseVisualStyleBackColor = true;
            this.button_Stop.Click += new System.EventHandler(this.button_Stop_Click);
            // 
            // groupBox_MoveState
            // 
            this.groupBox_MoveState.Controls.Add(this.textBox_Y_Pos);
            this.groupBox_MoveState.Controls.Add(this.textBox_Z_Pos);
            this.groupBox_MoveState.Controls.Add(this.textBox_X_Pos);
            this.groupBox_MoveState.Controls.Add(this.label4);
            this.groupBox_MoveState.Controls.Add(this.label3);
            this.groupBox_MoveState.Controls.Add(this.label2);
            this.groupBox_MoveState.Location = new System.Drawing.Point(17, 412);
            this.groupBox_MoveState.Name = "groupBox_MoveState";
            this.groupBox_MoveState.Size = new System.Drawing.Size(321, 83);
            this.groupBox_MoveState.TabIndex = 5;
            this.groupBox_MoveState.TabStop = false;
            this.groupBox_MoveState.Text = "状态";
            // 
            // textBox_Y_Pos
            // 
            this.textBox_Y_Pos.Location = new System.Drawing.Point(54, 52);
            this.textBox_Y_Pos.Name = "textBox_Y_Pos";
            this.textBox_Y_Pos.ReadOnly = true;
            this.textBox_Y_Pos.Size = new System.Drawing.Size(64, 21);
            this.textBox_Y_Pos.TabIndex = 5;
            // 
            // textBox_Z_Pos
            // 
            this.textBox_Z_Pos.Location = new System.Drawing.Point(180, 25);
            this.textBox_Z_Pos.Name = "textBox_Z_Pos";
            this.textBox_Z_Pos.ReadOnly = true;
            this.textBox_Z_Pos.Size = new System.Drawing.Size(99, 21);
            this.textBox_Z_Pos.TabIndex = 4;
            // 
            // textBox_X_Pos
            // 
            this.textBox_X_Pos.Location = new System.Drawing.Point(54, 25);
            this.textBox_X_Pos.Name = "textBox_X_Pos";
            this.textBox_X_Pos.ReadOnly = true;
            this.textBox_X_Pos.Size = new System.Drawing.Size(64, 21);
            this.textBox_X_Pos.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(23, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "Y轴";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(149, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "Z轴";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(23, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "X轴";
            // 
            // MotionWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(350, 520);
            this.Controls.Add(this.groupBox_MoveState);
            this.Controls.Add(this.groupBox_ControlOp);
            this.Controls.Add(this.button_Stop);
            this.Controls.Add(this.groupBox_MoveOp);
            this.Controls.Add(this.statusBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "MotionWindow";
            this.Text = "Motion";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MotionWindow_FormClosed);
            this.Load += new System.EventHandler(this.testForm_Load);
            this.statusBar.ResumeLayout(false);
            this.statusBar.PerformLayout();
            this.groupBox_MoveOp.ResumeLayout(false);
            this.groupBox_MoveOp.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox_ControlOp.ResumeLayout(false);
            this.groupBox_MoveState.ResumeLayout(false);
            this.groupBox_MoveState.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusBar;
        private System.Windows.Forms.Button button_Y_P;
        private System.Windows.Forms.GroupBox groupBox_MoveOp;
        private System.Windows.Forms.TextBox textBox_StepDistance;
        private System.Windows.Forms.RadioButton radioButton_Move_L;
        private System.Windows.Forms.RadioButton radioButton_Move_M;
        private System.Windows.Forms.RadioButton radioButton_Move_H;
        private System.Windows.Forms.Button button_Z_P;
        private System.Windows.Forms.Button button_Z_N;
        private System.Windows.Forms.Button button_X_P;
        private System.Windows.Forms.Button button_Y_N;
        private System.Windows.Forms.Button button_X_N;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox_ControlOp;
        private System.Windows.Forms.Button button_Home;
        private System.Windows.Forms.Button button_Stop;
        private System.Windows.Forms.GroupBox groupBox_MoveState;
        private System.Windows.Forms.TextBox textBox_Y_Pos;
        private System.Windows.Forms.TextBox textBox_Z_Pos;
        private System.Windows.Forms.TextBox textBox_X_Pos;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.Button button_setPrm;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rBtn_jog;
        private System.Windows.Forms.RadioButton rBtn_step;
        private System.Windows.Forms.RadioButton rBtn_pos;
    }
}