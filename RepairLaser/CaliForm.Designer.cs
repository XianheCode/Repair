namespace RepairLaser
{
    partial class CaliForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

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
            this.gb_selectVision = new System.Windows.Forms.GroupBox();
            this.rbtn_3 = new System.Windows.Forms.RadioButton();
            this.rbtn_2 = new System.Windows.Forms.RadioButton();
            this.rbtn_1 = new System.Windows.Forms.RadioButton();
            this.btn_start = new System.Windows.Forms.Button();
            this.gb_cali = new System.Windows.Forms.GroupBox();
            this.lb_cali = new System.Windows.Forms.Label();
            this.btn_over = new System.Windows.Forms.Button();
            this.btn_cali = new System.Windows.Forms.Button();
            this.btn_cancel = new System.Windows.Forms.Button();
            this.btn_close = new System.Windows.Forms.Button();
            this.btn_origion = new System.Windows.Forms.Button();
            this.gb_selectCali = new System.Windows.Forms.GroupBox();
            this.gb_control = new System.Windows.Forms.GroupBox();
            this.gb_caliOrigion = new System.Windows.Forms.GroupBox();
            this.lb_caliOri = new System.Windows.Forms.Label();
            this.btn_caliOri_2 = new System.Windows.Forms.Button();
            this.btn_caliOri_1 = new System.Windows.Forms.Button();
            this.gb_selectVision.SuspendLayout();
            this.gb_cali.SuspendLayout();
            this.gb_selectCali.SuspendLayout();
            this.gb_control.SuspendLayout();
            this.gb_caliOrigion.SuspendLayout();
            this.SuspendLayout();
            // 
            // gb_selectVision
            // 
            this.gb_selectVision.Controls.Add(this.rbtn_3);
            this.gb_selectVision.Controls.Add(this.rbtn_2);
            this.gb_selectVision.Controls.Add(this.rbtn_1);
            this.gb_selectVision.Location = new System.Drawing.Point(13, 13);
            this.gb_selectVision.Name = "gb_selectVision";
            this.gb_selectVision.Size = new System.Drawing.Size(98, 103);
            this.gb_selectVision.TabIndex = 0;
            this.gb_selectVision.TabStop = false;
            this.gb_selectVision.Text = "相机选择";
            // 
            // rbtn_3
            // 
            this.rbtn_3.AutoSize = true;
            this.rbtn_3.Location = new System.Drawing.Point(7, 67);
            this.rbtn_3.Name = "rbtn_3";
            this.rbtn_3.Size = new System.Drawing.Size(59, 16);
            this.rbtn_3.TabIndex = 2;
            this.rbtn_3.TabStop = true;
            this.rbtn_3.Text = "相机三";
            this.rbtn_3.UseVisualStyleBackColor = true;
            // 
            // rbtn_2
            // 
            this.rbtn_2.AutoSize = true;
            this.rbtn_2.Location = new System.Drawing.Point(7, 44);
            this.rbtn_2.Name = "rbtn_2";
            this.rbtn_2.Size = new System.Drawing.Size(59, 16);
            this.rbtn_2.TabIndex = 1;
            this.rbtn_2.TabStop = true;
            this.rbtn_2.Text = "相机二";
            this.rbtn_2.UseVisualStyleBackColor = true;
            // 
            // rbtn_1
            // 
            this.rbtn_1.AutoSize = true;
            this.rbtn_1.Location = new System.Drawing.Point(7, 21);
            this.rbtn_1.Name = "rbtn_1";
            this.rbtn_1.Size = new System.Drawing.Size(59, 16);
            this.rbtn_1.TabIndex = 0;
            this.rbtn_1.TabStop = true;
            this.rbtn_1.Text = "相机一";
            this.rbtn_1.UseVisualStyleBackColor = true;
            // 
            // btn_start
            // 
            this.btn_start.Location = new System.Drawing.Point(15, 18);
            this.btn_start.Name = "btn_start";
            this.btn_start.Size = new System.Drawing.Size(91, 32);
            this.btn_start.TabIndex = 1;
            this.btn_start.Text = "开始当量标定";
            this.btn_start.UseVisualStyleBackColor = true;
            this.btn_start.Click += new System.EventHandler(this.btn_start_Click);
            // 
            // gb_cali
            // 
            this.gb_cali.Controls.Add(this.lb_cali);
            this.gb_cali.Controls.Add(this.btn_over);
            this.gb_cali.Controls.Add(this.btn_cali);
            this.gb_cali.Location = new System.Drawing.Point(13, 134);
            this.gb_cali.Name = "gb_cali";
            this.gb_cali.Size = new System.Drawing.Size(238, 155);
            this.gb_cali.TabIndex = 2;
            this.gb_cali.TabStop = false;
            this.gb_cali.Text = "当量/方向标定";
            // 
            // lb_cali
            // 
            this.lb_cali.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lb_cali.Location = new System.Drawing.Point(103, 34);
            this.lb_cali.Name = "lb_cali";
            this.lb_cali.Size = new System.Drawing.Size(124, 95);
            this.lb_cali.TabIndex = 4;
            // 
            // btn_over
            // 
            this.btn_over.Location = new System.Drawing.Point(6, 91);
            this.btn_over.Name = "btn_over";
            this.btn_over.Size = new System.Drawing.Size(91, 38);
            this.btn_over.TabIndex = 3;
            this.btn_over.Text = "完成";
            this.btn_over.UseVisualStyleBackColor = true;
            this.btn_over.Click += new System.EventHandler(this.btn_over_Click);
            // 
            // btn_cali
            // 
            this.btn_cali.Location = new System.Drawing.Point(6, 34);
            this.btn_cali.Name = "btn_cali";
            this.btn_cali.Size = new System.Drawing.Size(91, 38);
            this.btn_cali.TabIndex = 2;
            this.btn_cali.Text = "标定当前点";
            this.btn_cali.UseVisualStyleBackColor = true;
            this.btn_cali.Click += new System.EventHandler(this.btn_cali_Click);
            // 
            // btn_cancel
            // 
            this.btn_cancel.Location = new System.Drawing.Point(15, 18);
            this.btn_cancel.Name = "btn_cancel";
            this.btn_cancel.Size = new System.Drawing.Size(91, 32);
            this.btn_cancel.TabIndex = 3;
            this.btn_cancel.Text = "取消标定";
            this.btn_cancel.UseVisualStyleBackColor = true;
            this.btn_cancel.Click += new System.EventHandler(this.btn_cancel_Click);
            // 
            // btn_close
            // 
            this.btn_close.Location = new System.Drawing.Point(15, 57);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(91, 31);
            this.btn_close.TabIndex = 4;
            this.btn_close.Text = "关闭窗口";
            this.btn_close.UseVisualStyleBackColor = true;
            this.btn_close.Click += new System.EventHandler(this.btn_close_Click);
            // 
            // btn_origion
            // 
            this.btn_origion.Location = new System.Drawing.Point(15, 57);
            this.btn_origion.Name = "btn_origion";
            this.btn_origion.Size = new System.Drawing.Size(91, 30);
            this.btn_origion.TabIndex = 5;
            this.btn_origion.Text = "开始原点标定";
            this.btn_origion.UseVisualStyleBackColor = true;
            this.btn_origion.Click += new System.EventHandler(this.btn_origion_Click);
            // 
            // gb_selectCali
            // 
            this.gb_selectCali.Controls.Add(this.btn_start);
            this.gb_selectCali.Controls.Add(this.btn_origion);
            this.gb_selectCali.Location = new System.Drawing.Point(126, 12);
            this.gb_selectCali.Name = "gb_selectCali";
            this.gb_selectCali.Size = new System.Drawing.Size(121, 104);
            this.gb_selectCali.TabIndex = 6;
            this.gb_selectCali.TabStop = false;
            this.gb_selectCali.Text = "标定选择";
            // 
            // gb_control
            // 
            this.gb_control.Controls.Add(this.btn_close);
            this.gb_control.Controls.Add(this.btn_cancel);
            this.gb_control.Location = new System.Drawing.Point(377, 12);
            this.gb_control.Name = "gb_control";
            this.gb_control.Size = new System.Drawing.Size(121, 104);
            this.gb_control.TabIndex = 7;
            this.gb_control.TabStop = false;
            this.gb_control.Text = "控制";
            // 
            // gb_caliOrigion
            // 
            this.gb_caliOrigion.Controls.Add(this.lb_caliOri);
            this.gb_caliOrigion.Controls.Add(this.btn_caliOri_2);
            this.gb_caliOrigion.Controls.Add(this.btn_caliOri_1);
            this.gb_caliOrigion.Location = new System.Drawing.Point(260, 134);
            this.gb_caliOrigion.Name = "gb_caliOrigion";
            this.gb_caliOrigion.Size = new System.Drawing.Size(238, 155);
            this.gb_caliOrigion.TabIndex = 5;
            this.gb_caliOrigion.TabStop = false;
            this.gb_caliOrigion.Text = "原点标定";
            // 
            // lb_caliOri
            // 
            this.lb_caliOri.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lb_caliOri.Location = new System.Drawing.Point(103, 34);
            this.lb_caliOri.Name = "lb_caliOri";
            this.lb_caliOri.Size = new System.Drawing.Size(124, 95);
            this.lb_caliOri.TabIndex = 4;
            // 
            // btn_caliOri_2
            // 
            this.btn_caliOri_2.Location = new System.Drawing.Point(6, 91);
            this.btn_caliOri_2.Name = "btn_caliOri_2";
            this.btn_caliOri_2.Size = new System.Drawing.Size(91, 38);
            this.btn_caliOri_2.TabIndex = 3;
            this.btn_caliOri_2.Text = "标定";
            this.btn_caliOri_2.UseVisualStyleBackColor = true;
            this.btn_caliOri_2.Click += new System.EventHandler(this.btn_caliOri_2_Click);
            // 
            // btn_caliOri_1
            // 
            this.btn_caliOri_1.Location = new System.Drawing.Point(6, 34);
            this.btn_caliOri_1.Name = "btn_caliOri_1";
            this.btn_caliOri_1.Size = new System.Drawing.Size(91, 38);
            this.btn_caliOri_1.TabIndex = 2;
            this.btn_caliOri_1.Text = "记录当前位置";
            this.btn_caliOri_1.UseVisualStyleBackColor = true;
            this.btn_caliOri_1.Click += new System.EventHandler(this.btn_caliOri_1_Click);
            // 
            // CaliForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(510, 316);
            this.ControlBox = false;
            this.Controls.Add(this.gb_caliOrigion);
            this.Controls.Add(this.gb_control);
            this.Controls.Add(this.gb_selectCali);
            this.Controls.Add(this.gb_cali);
            this.Controls.Add(this.gb_selectVision);
            this.Name = "CaliForm";
            this.Text = "CaliForm";
            this.TopMost = true;
            this.gb_selectVision.ResumeLayout(false);
            this.gb_selectVision.PerformLayout();
            this.gb_cali.ResumeLayout(false);
            this.gb_selectCali.ResumeLayout(false);
            this.gb_control.ResumeLayout(false);
            this.gb_caliOrigion.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gb_selectVision;
        private System.Windows.Forms.RadioButton rbtn_3;
        private System.Windows.Forms.RadioButton rbtn_2;
        private System.Windows.Forms.RadioButton rbtn_1;
        private System.Windows.Forms.Button btn_start;
        private System.Windows.Forms.GroupBox gb_cali;
        private System.Windows.Forms.Button btn_cancel;
        private System.Windows.Forms.Button btn_over;
        private System.Windows.Forms.Button btn_cali;
        private System.Windows.Forms.Label lb_cali;
        private System.Windows.Forms.Button btn_close;
        private System.Windows.Forms.Button btn_origion;
        private System.Windows.Forms.GroupBox gb_selectCali;
        private System.Windows.Forms.GroupBox gb_control;
        private System.Windows.Forms.GroupBox gb_caliOrigion;
        private System.Windows.Forms.Label lb_caliOri;
        private System.Windows.Forms.Button btn_caliOri_2;
        private System.Windows.Forms.Button btn_caliOri_1;
    }
}