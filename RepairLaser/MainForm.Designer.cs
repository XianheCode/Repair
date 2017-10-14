namespace RepairLaser
{
    partial class MainForm
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
            this.panel_Vision = new System.Windows.Forms.Panel();
            this.panel_Motion = new System.Windows.Forms.Panel();
            this.groupBox_Operate = new System.Windows.Forms.GroupBox();
            this.btn_goBack = new System.Windows.Forms.Button();
            this.button_stopWork = new System.Windows.Forms.Button();
            this.button_startWork = new System.Windows.Forms.Button();
            this.groupBox_prm = new System.Windows.Forms.GroupBox();
            this.btn_testJob3 = new System.Windows.Forms.Button();
            this.btn_test = new System.Windows.Forms.Button();
            this.button_savePrm = new System.Windows.Forms.Button();
            this.groupBox_otherPrm = new System.Windows.Forms.GroupBox();
            this.gb_zhiju = new System.Windows.Forms.GroupBox();
            this.btn_pushdown = new System.Windows.Forms.Button();
            this.btn_local = new System.Windows.Forms.Button();
            this.btn_absorb = new System.Windows.Forms.Button();
            this.btn_setMotionPrm = new System.Windows.Forms.Button();
            this.button_SetSignalPrm = new System.Windows.Forms.Button();
            this.btn_cali = new System.Windows.Forms.Button();
            this.button_gap = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_gap = new System.Windows.Forms.TextBox();
            this.groupBox_posPrm = new System.Windows.Forms.GroupBox();
            this.tb_focusZPos2 = new System.Windows.Forms.TextBox();
            this.btn_focusMove2 = new System.Windows.Forms.Button();
            this.btn_focusRcd2 = new System.Windows.Forms.Button();
            this.tb_focusZPos1 = new System.Windows.Forms.TextBox();
            this.btn_focusMove1 = new System.Windows.Forms.Button();
            this.btn_focusRcd1 = new System.Windows.Forms.Button();
            this.button_EndPos_ap = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox_EndPos_x = new System.Windows.Forms.TextBox();
            this.textBox_EndPos_y = new System.Windows.Forms.TextBox();
            this.button_EndPos_rc = new System.Windows.Forms.Button();
            this.button_EndPos_mv = new System.Windows.Forms.Button();
            this.button_PhotoPos_ap = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_PhotoPos_x = new System.Windows.Forms.TextBox();
            this.textBox_PhotoPos_y = new System.Windows.Forms.TextBox();
            this.button_PhotoPos_rc = new System.Windows.Forms.Button();
            this.button_PhotoPos_mv = new System.Windows.Forms.Button();
            this.button_StartPos_ap = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_StartPos_x = new System.Windows.Forms.TextBox();
            this.textBox_StartPos_y = new System.Windows.Forms.TextBox();
            this.button_StartPos_rc = new System.Windows.Forms.Button();
            this.button_StartPos_mv = new System.Windows.Forms.Button();
            this.statusLabel_1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.cb_pos = new System.Windows.Forms.ComboBox();
            this.btn_ap = new System.Windows.Forms.Button();
            this.tb_pos_x = new System.Windows.Forms.TextBox();
            this.tb_pos_y = new System.Windows.Forms.TextBox();
            this.btn_rc = new System.Windows.Forms.Button();
            this.btn_mv = new System.Windows.Forms.Button();
            this.groupBox_Operate.SuspendLayout();
            this.groupBox_prm.SuspendLayout();
            this.groupBox_otherPrm.SuspendLayout();
            this.gb_zhiju.SuspendLayout();
            this.groupBox_posPrm.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel_Vision
            // 
            this.panel_Vision.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_Vision.Location = new System.Drawing.Point(5, 10);
            this.panel_Vision.Name = "panel_Vision";
            this.panel_Vision.Size = new System.Drawing.Size(1000, 520);
            this.panel_Vision.TabIndex = 0;
            // 
            // panel_Motion
            // 
            this.panel_Motion.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_Motion.Location = new System.Drawing.Point(1010, 10);
            this.panel_Motion.Name = "panel_Motion";
            this.panel_Motion.Size = new System.Drawing.Size(350, 520);
            this.panel_Motion.TabIndex = 1;
            // 
            // groupBox_Operate
            // 
            this.groupBox_Operate.Controls.Add(this.btn_goBack);
            this.groupBox_Operate.Controls.Add(this.button_stopWork);
            this.groupBox_Operate.Controls.Add(this.button_startWork);
            this.groupBox_Operate.Location = new System.Drawing.Point(5, 536);
            this.groupBox_Operate.Name = "groupBox_Operate";
            this.groupBox_Operate.Size = new System.Drawing.Size(135, 241);
            this.groupBox_Operate.TabIndex = 3;
            this.groupBox_Operate.TabStop = false;
            // 
            // btn_goBack
            // 
            this.btn_goBack.Location = new System.Drawing.Point(18, 176);
            this.btn_goBack.Name = "btn_goBack";
            this.btn_goBack.Size = new System.Drawing.Size(100, 33);
            this.btn_goBack.TabIndex = 3;
            this.btn_goBack.Text = "回到初始状态";
            this.btn_goBack.UseVisualStyleBackColor = true;
            this.btn_goBack.Click += new System.EventHandler(this.btn_goBack_Click);
            // 
            // button_stopWork
            // 
            this.button_stopWork.Location = new System.Drawing.Point(18, 114);
            this.button_stopWork.Name = "button_stopWork";
            this.button_stopWork.Size = new System.Drawing.Size(100, 33);
            this.button_stopWork.TabIndex = 2;
            this.button_stopWork.Text = "停止";
            this.button_stopWork.UseVisualStyleBackColor = true;
            this.button_stopWork.Click += new System.EventHandler(this.button_stopWork_Click);
            // 
            // button_startWork
            // 
            this.button_startWork.Location = new System.Drawing.Point(18, 52);
            this.button_startWork.Name = "button_startWork";
            this.button_startWork.Size = new System.Drawing.Size(100, 33);
            this.button_startWork.TabIndex = 0;
            this.button_startWork.Text = "加工";
            this.button_startWork.UseVisualStyleBackColor = true;
            this.button_startWork.Click += new System.EventHandler(this.button_startWork_Click);
            // 
            // groupBox_prm
            // 
            this.groupBox_prm.Controls.Add(this.btn_testJob3);
            this.groupBox_prm.Controls.Add(this.btn_test);
            this.groupBox_prm.Controls.Add(this.button_savePrm);
            this.groupBox_prm.Controls.Add(this.groupBox_otherPrm);
            this.groupBox_prm.Controls.Add(this.groupBox_posPrm);
            this.groupBox_prm.Location = new System.Drawing.Point(146, 536);
            this.groupBox_prm.Name = "groupBox_prm";
            this.groupBox_prm.Size = new System.Drawing.Size(1212, 241);
            this.groupBox_prm.TabIndex = 4;
            this.groupBox_prm.TabStop = false;
            // 
            // btn_testJob3
            // 
            this.btn_testJob3.Location = new System.Drawing.Point(902, 124);
            this.btn_testJob3.Name = "btn_testJob3";
            this.btn_testJob3.Size = new System.Drawing.Size(61, 45);
            this.btn_testJob3.TabIndex = 29;
            this.btn_testJob3.Text = "RunJob3并分析路径";
            this.btn_testJob3.UseVisualStyleBackColor = true;
            // 
            // btn_test
            // 
            this.btn_test.Location = new System.Drawing.Point(989, 124);
            this.btn_test.Name = "btn_test";
            this.btn_test.Size = new System.Drawing.Size(68, 45);
            this.btn_test.TabIndex = 24;
            this.btn_test.Text = "测试用";
            this.btn_test.UseVisualStyleBackColor = true;
            this.btn_test.Click += new System.EventHandler(this.btn_test_Click);
            // 
            // button_savePrm
            // 
            this.button_savePrm.Location = new System.Drawing.Point(1093, 124);
            this.button_savePrm.Name = "button_savePrm";
            this.button_savePrm.Size = new System.Drawing.Size(68, 45);
            this.button_savePrm.TabIndex = 23;
            this.button_savePrm.Text = "保存所有参数至文件";
            this.button_savePrm.UseVisualStyleBackColor = true;
            // 
            // groupBox_otherPrm
            // 
            this.groupBox_otherPrm.Controls.Add(this.gb_zhiju);
            this.groupBox_otherPrm.Controls.Add(this.btn_setMotionPrm);
            this.groupBox_otherPrm.Controls.Add(this.button_SetSignalPrm);
            this.groupBox_otherPrm.Controls.Add(this.btn_cali);
            this.groupBox_otherPrm.Controls.Add(this.button_gap);
            this.groupBox_otherPrm.Controls.Add(this.label4);
            this.groupBox_otherPrm.Controls.Add(this.textBox_gap);
            this.groupBox_otherPrm.Location = new System.Drawing.Point(426, 20);
            this.groupBox_otherPrm.Name = "groupBox_otherPrm";
            this.groupBox_otherPrm.Size = new System.Drawing.Size(393, 215);
            this.groupBox_otherPrm.TabIndex = 22;
            this.groupBox_otherPrm.TabStop = false;
            this.groupBox_otherPrm.Text = "其他参数";
            // 
            // gb_zhiju
            // 
            this.gb_zhiju.Controls.Add(this.btn_pushdown);
            this.gb_zhiju.Controls.Add(this.btn_local);
            this.gb_zhiju.Controls.Add(this.btn_absorb);
            this.gb_zhiju.Location = new System.Drawing.Point(221, 44);
            this.gb_zhiju.Name = "gb_zhiju";
            this.gb_zhiju.Size = new System.Drawing.Size(115, 134);
            this.gb_zhiju.TabIndex = 32;
            this.gb_zhiju.TabStop = false;
            this.gb_zhiju.Text = "治具控制";
            // 
            // btn_pushdown
            // 
            this.btn_pushdown.Location = new System.Drawing.Point(21, 89);
            this.btn_pushdown.Name = "btn_pushdown";
            this.btn_pushdown.Size = new System.Drawing.Size(75, 23);
            this.btn_pushdown.TabIndex = 31;
            this.btn_pushdown.Text = "下压";
            this.btn_pushdown.UseVisualStyleBackColor = true;
            this.btn_pushdown.Click += new System.EventHandler(this.btn_pushdown_Click);
            // 
            // btn_local
            // 
            this.btn_local.Location = new System.Drawing.Point(21, 28);
            this.btn_local.Name = "btn_local";
            this.btn_local.Size = new System.Drawing.Size(75, 23);
            this.btn_local.TabIndex = 29;
            this.btn_local.Text = "定位";
            this.btn_local.UseVisualStyleBackColor = true;
            this.btn_local.Click += new System.EventHandler(this.btn_local_Click);
            // 
            // btn_absorb
            // 
            this.btn_absorb.Location = new System.Drawing.Point(21, 60);
            this.btn_absorb.Name = "btn_absorb";
            this.btn_absorb.Size = new System.Drawing.Size(75, 23);
            this.btn_absorb.TabIndex = 30;
            this.btn_absorb.Text = "吸附";
            this.btn_absorb.UseVisualStyleBackColor = true;
            this.btn_absorb.Click += new System.EventHandler(this.btn_absorb_Click);
            // 
            // btn_setMotionPrm
            // 
            this.btn_setMotionPrm.Location = new System.Drawing.Point(119, 72);
            this.btn_setMotionPrm.Name = "btn_setMotionPrm";
            this.btn_setMotionPrm.Size = new System.Drawing.Size(61, 45);
            this.btn_setMotionPrm.TabIndex = 27;
            this.btn_setMotionPrm.Text = "运动参数设置";
            this.btn_setMotionPrm.UseVisualStyleBackColor = true;
            this.btn_setMotionPrm.Click += new System.EventHandler(this.btn_setMotionPrm_Click);
            // 
            // button_SetSignalPrm
            // 
            this.button_SetSignalPrm.Location = new System.Drawing.Point(29, 133);
            this.button_SetSignalPrm.Name = "button_SetSignalPrm";
            this.button_SetSignalPrm.Size = new System.Drawing.Size(61, 45);
            this.button_SetSignalPrm.TabIndex = 25;
            this.button_SetSignalPrm.Text = "信号发生器设置";
            this.button_SetSignalPrm.UseVisualStyleBackColor = true;
            this.button_SetSignalPrm.Click += new System.EventHandler(this.button_SetSignalPrm_Click);
            // 
            // btn_cali
            // 
            this.btn_cali.Location = new System.Drawing.Point(29, 72);
            this.btn_cali.Name = "btn_cali";
            this.btn_cali.Size = new System.Drawing.Size(63, 45);
            this.btn_cali.TabIndex = 26;
            this.btn_cali.Text = "相机标定";
            this.btn_cali.UseVisualStyleBackColor = true;
            this.btn_cali.Click += new System.EventHandler(this.btn_cali_Click);
            // 
            // button_gap
            // 
            this.button_gap.Location = new System.Drawing.Point(153, 15);
            this.button_gap.Name = "button_gap";
            this.button_gap.Size = new System.Drawing.Size(53, 23);
            this.button_gap.TabIndex = 24;
            this.button_gap.Text = "应用";
            this.button_gap.UseVisualStyleBackColor = true;
            this.button_gap.Click += new System.EventHandler(this.button_gap_Click);
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(6, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 23);
            this.label4.TabIndex = 21;
            this.label4.Text = "光斑间隙";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBox_gap
            // 
            this.textBox_gap.Location = new System.Drawing.Point(74, 17);
            this.textBox_gap.Name = "textBox_gap";
            this.textBox_gap.Size = new System.Drawing.Size(64, 21);
            this.textBox_gap.TabIndex = 22;
            // 
            // groupBox_posPrm
            // 
            this.groupBox_posPrm.Controls.Add(this.btn_ap);
            this.groupBox_posPrm.Controls.Add(this.tb_pos_x);
            this.groupBox_posPrm.Controls.Add(this.tb_pos_y);
            this.groupBox_posPrm.Controls.Add(this.btn_rc);
            this.groupBox_posPrm.Controls.Add(this.btn_mv);
            this.groupBox_posPrm.Controls.Add(this.cb_pos);
            this.groupBox_posPrm.Controls.Add(this.tb_focusZPos2);
            this.groupBox_posPrm.Controls.Add(this.btn_focusMove2);
            this.groupBox_posPrm.Controls.Add(this.btn_focusRcd2);
            this.groupBox_posPrm.Controls.Add(this.tb_focusZPos1);
            this.groupBox_posPrm.Controls.Add(this.btn_focusMove1);
            this.groupBox_posPrm.Controls.Add(this.btn_focusRcd1);
            this.groupBox_posPrm.Controls.Add(this.button_EndPos_ap);
            this.groupBox_posPrm.Controls.Add(this.label3);
            this.groupBox_posPrm.Controls.Add(this.textBox_EndPos_x);
            this.groupBox_posPrm.Controls.Add(this.textBox_EndPos_y);
            this.groupBox_posPrm.Controls.Add(this.button_EndPos_rc);
            this.groupBox_posPrm.Controls.Add(this.button_EndPos_mv);
            this.groupBox_posPrm.Controls.Add(this.button_PhotoPos_ap);
            this.groupBox_posPrm.Controls.Add(this.label2);
            this.groupBox_posPrm.Controls.Add(this.textBox_PhotoPos_x);
            this.groupBox_posPrm.Controls.Add(this.textBox_PhotoPos_y);
            this.groupBox_posPrm.Controls.Add(this.button_PhotoPos_rc);
            this.groupBox_posPrm.Controls.Add(this.button_PhotoPos_mv);
            this.groupBox_posPrm.Controls.Add(this.button_StartPos_ap);
            this.groupBox_posPrm.Controls.Add(this.label1);
            this.groupBox_posPrm.Controls.Add(this.textBox_StartPos_x);
            this.groupBox_posPrm.Controls.Add(this.textBox_StartPos_y);
            this.groupBox_posPrm.Controls.Add(this.button_StartPos_rc);
            this.groupBox_posPrm.Controls.Add(this.button_StartPos_mv);
            this.groupBox_posPrm.Location = new System.Drawing.Point(6, 14);
            this.groupBox_posPrm.Name = "groupBox_posPrm";
            this.groupBox_posPrm.Size = new System.Drawing.Size(414, 221);
            this.groupBox_posPrm.TabIndex = 20;
            this.groupBox_posPrm.TabStop = false;
            this.groupBox_posPrm.Text = "位置参数";
            // 
            // tb_focusZPos2
            // 
            this.tb_focusZPos2.Location = new System.Drawing.Point(139, 192);
            this.tb_focusZPos2.Name = "tb_focusZPos2";
            this.tb_focusZPos2.ReadOnly = true;
            this.tb_focusZPos2.Size = new System.Drawing.Size(76, 21);
            this.tb_focusZPos2.TabIndex = 38;
            // 
            // btn_focusMove2
            // 
            this.btn_focusMove2.Location = new System.Drawing.Point(88, 191);
            this.btn_focusMove2.Name = "btn_focusMove2";
            this.btn_focusMove2.Size = new System.Drawing.Size(45, 23);
            this.btn_focusMove2.TabIndex = 37;
            this.btn_focusMove2.Text = "移动";
            this.btn_focusMove2.UseVisualStyleBackColor = true;
            this.btn_focusMove2.Click += new System.EventHandler(this.btn_focusMove2_Click);
            // 
            // btn_focusRcd2
            // 
            this.btn_focusRcd2.Location = new System.Drawing.Point(8, 191);
            this.btn_focusRcd2.Name = "btn_focusRcd2";
            this.btn_focusRcd2.Size = new System.Drawing.Size(74, 23);
            this.btn_focusRcd2.TabIndex = 36;
            this.btn_focusRcd2.Text = "记录焦距2";
            this.btn_focusRcd2.UseVisualStyleBackColor = true;
            this.btn_focusRcd2.Click += new System.EventHandler(this.btn_focusRcd2_Click);
            // 
            // tb_focusZPos1
            // 
            this.tb_focusZPos1.Location = new System.Drawing.Point(139, 162);
            this.tb_focusZPos1.Name = "tb_focusZPos1";
            this.tb_focusZPos1.ReadOnly = true;
            this.tb_focusZPos1.Size = new System.Drawing.Size(76, 21);
            this.tb_focusZPos1.TabIndex = 35;
            // 
            // btn_focusMove1
            // 
            this.btn_focusMove1.Location = new System.Drawing.Point(88, 161);
            this.btn_focusMove1.Name = "btn_focusMove1";
            this.btn_focusMove1.Size = new System.Drawing.Size(45, 23);
            this.btn_focusMove1.TabIndex = 34;
            this.btn_focusMove1.Text = "移动";
            this.btn_focusMove1.UseVisualStyleBackColor = true;
            this.btn_focusMove1.Click += new System.EventHandler(this.btn_focusMove1_Click);
            // 
            // btn_focusRcd1
            // 
            this.btn_focusRcd1.Location = new System.Drawing.Point(8, 161);
            this.btn_focusRcd1.Name = "btn_focusRcd1";
            this.btn_focusRcd1.Size = new System.Drawing.Size(74, 23);
            this.btn_focusRcd1.TabIndex = 33;
            this.btn_focusRcd1.Text = "记录焦距1";
            this.btn_focusRcd1.UseVisualStyleBackColor = true;
            this.btn_focusRcd1.Click += new System.EventHandler(this.btn_focusRcd1_Click);
            // 
            // button_EndPos_ap
            // 
            this.button_EndPos_ap.Location = new System.Drawing.Point(220, 82);
            this.button_EndPos_ap.Name = "button_EndPos_ap";
            this.button_EndPos_ap.Size = new System.Drawing.Size(53, 23);
            this.button_EndPos_ap.TabIndex = 32;
            this.button_EndPos_ap.Text = "应用";
            this.button_EndPos_ap.UseVisualStyleBackColor = true;
            this.button_EndPos_ap.Click += new System.EventHandler(this.button_EndPos_ap_Click);
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(6, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 23);
            this.label3.TabIndex = 27;
            this.label3.Text = "下料位置";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBox_EndPos_x
            // 
            this.textBox_EndPos_x.Location = new System.Drawing.Point(74, 83);
            this.textBox_EndPos_x.Name = "textBox_EndPos_x";
            this.textBox_EndPos_x.Size = new System.Drawing.Size(64, 21);
            this.textBox_EndPos_x.TabIndex = 28;
            // 
            // textBox_EndPos_y
            // 
            this.textBox_EndPos_y.Location = new System.Drawing.Point(147, 83);
            this.textBox_EndPos_y.Name = "textBox_EndPos_y";
            this.textBox_EndPos_y.Size = new System.Drawing.Size(64, 21);
            this.textBox_EndPos_y.TabIndex = 29;
            // 
            // button_EndPos_rc
            // 
            this.button_EndPos_rc.Location = new System.Drawing.Point(344, 82);
            this.button_EndPos_rc.Name = "button_EndPos_rc";
            this.button_EndPos_rc.Size = new System.Drawing.Size(53, 23);
            this.button_EndPos_rc.TabIndex = 30;
            this.button_EndPos_rc.Text = "记录";
            this.button_EndPos_rc.UseVisualStyleBackColor = true;
            this.button_EndPos_rc.Click += new System.EventHandler(this.button_EndPos_rc_Click);
            // 
            // button_EndPos_mv
            // 
            this.button_EndPos_mv.Location = new System.Drawing.Point(282, 82);
            this.button_EndPos_mv.Name = "button_EndPos_mv";
            this.button_EndPos_mv.Size = new System.Drawing.Size(53, 23);
            this.button_EndPos_mv.TabIndex = 31;
            this.button_EndPos_mv.Text = "移动";
            this.button_EndPos_mv.UseVisualStyleBackColor = true;
            this.button_EndPos_mv.Click += new System.EventHandler(this.button_EndPos_mv_Click);
            // 
            // button_PhotoPos_ap
            // 
            this.button_PhotoPos_ap.Location = new System.Drawing.Point(220, 49);
            this.button_PhotoPos_ap.Name = "button_PhotoPos_ap";
            this.button_PhotoPos_ap.Size = new System.Drawing.Size(53, 23);
            this.button_PhotoPos_ap.TabIndex = 26;
            this.button_PhotoPos_ap.Text = "应用";
            this.button_PhotoPos_ap.UseVisualStyleBackColor = true;
            this.button_PhotoPos_ap.Click += new System.EventHandler(this.button_PhotoPos_ap_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(6, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 23);
            this.label2.TabIndex = 21;
            this.label2.Text = "拍照位置";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBox_PhotoPos_x
            // 
            this.textBox_PhotoPos_x.Location = new System.Drawing.Point(74, 50);
            this.textBox_PhotoPos_x.Name = "textBox_PhotoPos_x";
            this.textBox_PhotoPos_x.Size = new System.Drawing.Size(64, 21);
            this.textBox_PhotoPos_x.TabIndex = 22;
            // 
            // textBox_PhotoPos_y
            // 
            this.textBox_PhotoPos_y.Location = new System.Drawing.Point(146, 50);
            this.textBox_PhotoPos_y.Name = "textBox_PhotoPos_y";
            this.textBox_PhotoPos_y.Size = new System.Drawing.Size(64, 21);
            this.textBox_PhotoPos_y.TabIndex = 23;
            // 
            // button_PhotoPos_rc
            // 
            this.button_PhotoPos_rc.Location = new System.Drawing.Point(344, 49);
            this.button_PhotoPos_rc.Name = "button_PhotoPos_rc";
            this.button_PhotoPos_rc.Size = new System.Drawing.Size(53, 23);
            this.button_PhotoPos_rc.TabIndex = 24;
            this.button_PhotoPos_rc.Text = "记录";
            this.button_PhotoPos_rc.UseVisualStyleBackColor = true;
            this.button_PhotoPos_rc.Click += new System.EventHandler(this.button_PhotoPos_rc_Click);
            // 
            // button_PhotoPos_mv
            // 
            this.button_PhotoPos_mv.Location = new System.Drawing.Point(282, 49);
            this.button_PhotoPos_mv.Name = "button_PhotoPos_mv";
            this.button_PhotoPos_mv.Size = new System.Drawing.Size(53, 23);
            this.button_PhotoPos_mv.TabIndex = 25;
            this.button_PhotoPos_mv.Text = "移动";
            this.button_PhotoPos_mv.UseVisualStyleBackColor = true;
            this.button_PhotoPos_mv.Click += new System.EventHandler(this.button_PhotoPos_mv_Click);
            // 
            // button_StartPos_ap
            // 
            this.button_StartPos_ap.Location = new System.Drawing.Point(220, 17);
            this.button_StartPos_ap.Name = "button_StartPos_ap";
            this.button_StartPos_ap.Size = new System.Drawing.Size(53, 23);
            this.button_StartPos_ap.TabIndex = 20;
            this.button_StartPos_ap.Text = "应用";
            this.button_StartPos_ap.UseVisualStyleBackColor = true;
            this.button_StartPos_ap.Click += new System.EventHandler(this.button_StartPos_ap_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(6, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 23);
            this.label1.TabIndex = 0;
            this.label1.Text = "上料位置";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBox_StartPos_x
            // 
            this.textBox_StartPos_x.Location = new System.Drawing.Point(74, 18);
            this.textBox_StartPos_x.Name = "textBox_StartPos_x";
            this.textBox_StartPos_x.Size = new System.Drawing.Size(64, 21);
            this.textBox_StartPos_x.TabIndex = 1;
            // 
            // textBox_StartPos_y
            // 
            this.textBox_StartPos_y.Location = new System.Drawing.Point(147, 18);
            this.textBox_StartPos_y.Name = "textBox_StartPos_y";
            this.textBox_StartPos_y.Size = new System.Drawing.Size(64, 21);
            this.textBox_StartPos_y.TabIndex = 2;
            // 
            // button_StartPos_rc
            // 
            this.button_StartPos_rc.Location = new System.Drawing.Point(344, 17);
            this.button_StartPos_rc.Name = "button_StartPos_rc";
            this.button_StartPos_rc.Size = new System.Drawing.Size(53, 23);
            this.button_StartPos_rc.TabIndex = 3;
            this.button_StartPos_rc.Text = "记录";
            this.button_StartPos_rc.UseVisualStyleBackColor = true;
            this.button_StartPos_rc.Click += new System.EventHandler(this.button_StartPos_rc_Click);
            // 
            // button_StartPos_mv
            // 
            this.button_StartPos_mv.Location = new System.Drawing.Point(282, 17);
            this.button_StartPos_mv.Name = "button_StartPos_mv";
            this.button_StartPos_mv.Size = new System.Drawing.Size(53, 23);
            this.button_StartPos_mv.TabIndex = 4;
            this.button_StartPos_mv.Text = "移动";
            this.button_StartPos_mv.UseVisualStyleBackColor = true;
            this.button_StartPos_mv.Click += new System.EventHandler(this.button_StartPos_mv_Click);
            // 
            // statusLabel_1
            // 
            this.statusLabel_1.AutoSize = false;
            this.statusLabel_1.Name = "statusLabel_1";
            this.statusLabel_1.Size = new System.Drawing.Size(300, 17);
            this.statusLabel_1.Text = "Wait";
            this.statusLabel_1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel_1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 780);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1424, 22);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "status_MainForm";
            // 
            // cb_pos
            // 
            this.cb_pos.FormattingEnabled = true;
            this.cb_pos.Items.AddRange(new object[] {
            "位置1",
            "位置2",
            "位置3",
            "位置4",
            "位置5",
            "位置6",
            "位置7",
            "位置8",
            "位置9"});
            this.cb_pos.Location = new System.Drawing.Point(8, 113);
            this.cb_pos.Name = "cb_pos";
            this.cb_pos.Size = new System.Drawing.Size(57, 20);
            this.cb_pos.TabIndex = 39;
            this.cb_pos.SelectedIndexChanged += new System.EventHandler(this.cb_pos_SelectedIndexChanged);
            // 
            // btn_ap
            // 
            this.btn_ap.Location = new System.Drawing.Point(220, 111);
            this.btn_ap.Name = "btn_ap";
            this.btn_ap.Size = new System.Drawing.Size(53, 23);
            this.btn_ap.TabIndex = 44;
            this.btn_ap.Text = "应用";
            this.btn_ap.UseVisualStyleBackColor = true;
            this.btn_ap.Click += new System.EventHandler(this.btn_ap_Click);
            // 
            // tb_pos_x
            // 
            this.tb_pos_x.Location = new System.Drawing.Point(74, 112);
            this.tb_pos_x.Name = "tb_pos_x";
            this.tb_pos_x.Size = new System.Drawing.Size(64, 21);
            this.tb_pos_x.TabIndex = 40;
            // 
            // tb_pos_y
            // 
            this.tb_pos_y.Location = new System.Drawing.Point(147, 112);
            this.tb_pos_y.Name = "tb_pos_y";
            this.tb_pos_y.Size = new System.Drawing.Size(64, 21);
            this.tb_pos_y.TabIndex = 41;
            // 
            // btn_rc
            // 
            this.btn_rc.Location = new System.Drawing.Point(344, 111);
            this.btn_rc.Name = "btn_rc";
            this.btn_rc.Size = new System.Drawing.Size(53, 23);
            this.btn_rc.TabIndex = 42;
            this.btn_rc.Text = "记录";
            this.btn_rc.UseVisualStyleBackColor = true;
            this.btn_rc.Click += new System.EventHandler(this.btn_rc_Click);
            // 
            // btn_mv
            // 
            this.btn_mv.Location = new System.Drawing.Point(282, 111);
            this.btn_mv.Name = "btn_mv";
            this.btn_mv.Size = new System.Drawing.Size(53, 23);
            this.btn_mv.TabIndex = 43;
            this.btn_mv.Text = "移动";
            this.btn_mv.UseVisualStyleBackColor = true;
            this.btn_mv.Click += new System.EventHandler(this.btn_mv_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1424, 802);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox_prm);
            this.Controls.Add(this.groupBox_Operate);
            this.Controls.Add(this.panel_Motion);
            this.Controls.Add(this.panel_Vision);
            this.IsMdiContainer = true;
            this.Name = "MainForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultBounds;
            this.Text = "Repair";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBox_Operate.ResumeLayout(false);
            this.groupBox_prm.ResumeLayout(false);
            this.groupBox_otherPrm.ResumeLayout(false);
            this.groupBox_otherPrm.PerformLayout();
            this.gb_zhiju.ResumeLayout(false);
            this.groupBox_posPrm.ResumeLayout(false);
            this.groupBox_posPrm.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel_Vision;
        private System.Windows.Forms.Panel panel_Motion;
        private System.Windows.Forms.GroupBox groupBox_Operate;
        private System.Windows.Forms.Button button_stopWork;
        private System.Windows.Forms.Button button_startWork;
        private System.Windows.Forms.GroupBox groupBox_prm;
        private System.Windows.Forms.GroupBox groupBox_posPrm;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_StartPos_x;
        private System.Windows.Forms.TextBox textBox_StartPos_y;
        private System.Windows.Forms.Button button_StartPos_rc;
        private System.Windows.Forms.Button button_StartPos_mv;
        private System.Windows.Forms.Button button_EndPos_ap;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox_EndPos_x;
        private System.Windows.Forms.TextBox textBox_EndPos_y;
        private System.Windows.Forms.Button button_EndPos_rc;
        private System.Windows.Forms.Button button_EndPos_mv;
        private System.Windows.Forms.Button button_PhotoPos_ap;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_PhotoPos_x;
        private System.Windows.Forms.TextBox textBox_PhotoPos_y;
        private System.Windows.Forms.Button button_PhotoPos_rc;
        private System.Windows.Forms.Button button_PhotoPos_mv;
        private System.Windows.Forms.Button button_StartPos_ap;
        private System.Windows.Forms.GroupBox groupBox_otherPrm;
        private System.Windows.Forms.Button button_gap;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_gap;
        private System.Windows.Forms.Button button_SetSignalPrm;
        private System.Windows.Forms.Button btn_focusMove1;
        private System.Windows.Forms.Button btn_focusRcd1;
        private System.Windows.Forms.TextBox tb_focusZPos1;
        private System.Windows.Forms.Button btn_cali;
        private System.Windows.Forms.TextBox tb_focusZPos2;
        private System.Windows.Forms.Button btn_focusMove2;
        private System.Windows.Forms.Button btn_focusRcd2;
        private System.Windows.Forms.Button btn_setMotionPrm;
        private System.Windows.Forms.Button button_savePrm;
        private System.Windows.Forms.Button btn_pushdown;
        private System.Windows.Forms.Button btn_absorb;
        private System.Windows.Forms.Button btn_local;
        private System.Windows.Forms.Button btn_goBack;
        private System.Windows.Forms.GroupBox gb_zhiju;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel_1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Button btn_testJob3;
        private System.Windows.Forms.Button btn_test;
        private System.Windows.Forms.Button btn_ap;
        private System.Windows.Forms.TextBox tb_pos_x;
        private System.Windows.Forms.TextBox tb_pos_y;
        private System.Windows.Forms.Button btn_rc;
        private System.Windows.Forms.Button btn_mv;
        private System.Windows.Forms.ComboBox cb_pos;
    }
}

