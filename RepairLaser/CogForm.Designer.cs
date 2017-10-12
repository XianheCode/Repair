

namespace VisionMod
{
    partial class CogForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CogForm));
            this.runJob_1_Btn = new System.Windows.Forms.Button();
            this.runJob_3_Btn = new System.Windows.Forms.Button();
            this.runJob_2_Btn = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TabControl_vision = new System.Windows.Forms.TabControl();
            this.ImageDisplay = new System.Windows.Forms.TabPage();
            this.tabControl_display = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox_camera = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label_display = new System.Windows.Forms.Label();
            this.button_camera_stop = new System.Windows.Forms.Button();
            this.button_camera_3 = new System.Windows.Forms.Button();
            this.button_camera_2 = new System.Windows.Forms.Button();
            this.button_camera_1 = new System.Windows.Forms.Button();
            this.cogDisplay1 = new Cognex.VisionPro.Display.CogDisplay();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.cogRecordsDisplay1 = new Cognex.VisionPro.CogRecordsDisplay();
            this.vsPage1 = new System.Windows.Forms.TabPage();
            this.cogToolGroupEditV21 = new Cognex.VisionPro.ToolGroup.CogToolGroupEditV2();
            this.vsPage2 = new System.Windows.Forms.TabPage();
            this.cogToolGroupEditV22 = new Cognex.VisionPro.ToolGroup.CogToolGroupEditV2();
            this.vsPage3 = new System.Windows.Forms.TabPage();
            this.cogToolGroupEditV23 = new Cognex.VisionPro.ToolGroup.CogToolGroupEditV2();
            this.groupBox_visionCtrl = new System.Windows.Forms.GroupBox();
            this.btn_saveVS = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.TabControl_vision.SuspendLayout();
            this.ImageDisplay.SuspendLayout();
            this.tabControl_display.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox_camera.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cogDisplay1)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.vsPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV21)).BeginInit();
            this.vsPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV22)).BeginInit();
            this.vsPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV23)).BeginInit();
            this.groupBox_visionCtrl.SuspendLayout();
            this.SuspendLayout();
            // 
            // runJob_1_Btn
            // 
            this.runJob_1_Btn.Location = new System.Drawing.Point(19, 120);
            this.runJob_1_Btn.Name = "runJob_1_Btn";
            this.runJob_1_Btn.Size = new System.Drawing.Size(75, 38);
            this.runJob_1_Btn.TabIndex = 0;
            this.runJob_1_Btn.Text = "RunJob1";
            this.runJob_1_Btn.UseVisualStyleBackColor = true;
            this.runJob_1_Btn.Click += new System.EventHandler(this.runJob_1_Btn_Click);
            // 
            // runJob_3_Btn
            // 
            this.runJob_3_Btn.Location = new System.Drawing.Point(19, 224);
            this.runJob_3_Btn.Name = "runJob_3_Btn";
            this.runJob_3_Btn.Size = new System.Drawing.Size(75, 38);
            this.runJob_3_Btn.TabIndex = 4;
            this.runJob_3_Btn.Text = "RunJob3";
            this.runJob_3_Btn.UseVisualStyleBackColor = true;
            this.runJob_3_Btn.Click += new System.EventHandler(this.runJob_3_Btn_Click);
            // 
            // runJob_2_Btn
            // 
            this.runJob_2_Btn.Location = new System.Drawing.Point(19, 172);
            this.runJob_2_Btn.Name = "runJob_2_Btn";
            this.runJob_2_Btn.Size = new System.Drawing.Size(75, 38);
            this.runJob_2_Btn.TabIndex = 5;
            this.runJob_2_Btn.Text = "RunJob2";
            this.runJob_2_Btn.UseVisualStyleBackColor = true;
            this.runJob_2_Btn.Click += new System.EventHandler(this.runJob_2_Btn_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.TabControl_vision);
            this.groupBox1.Location = new System.Drawing.Point(15, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(862, 504);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "视觉工具";
            // 
            // TabControl_vision
            // 
            this.TabControl_vision.Controls.Add(this.ImageDisplay);
            this.TabControl_vision.Controls.Add(this.vsPage1);
            this.TabControl_vision.Controls.Add(this.vsPage2);
            this.TabControl_vision.Controls.Add(this.vsPage3);
            this.TabControl_vision.Location = new System.Drawing.Point(6, 20);
            this.TabControl_vision.Name = "TabControl_vision";
            this.TabControl_vision.SelectedIndex = 0;
            this.TabControl_vision.Size = new System.Drawing.Size(842, 470);
            this.TabControl_vision.TabIndex = 0;
            // 
            // ImageDisplay
            // 
            this.ImageDisplay.Controls.Add(this.tabControl_display);
            this.ImageDisplay.Location = new System.Drawing.Point(4, 22);
            this.ImageDisplay.Name = "ImageDisplay";
            this.ImageDisplay.Padding = new System.Windows.Forms.Padding(3);
            this.ImageDisplay.Size = new System.Drawing.Size(834, 444);
            this.ImageDisplay.TabIndex = 0;
            this.ImageDisplay.Text = "显示图像";
            this.ImageDisplay.UseVisualStyleBackColor = true;
            // 
            // tabControl_display
            // 
            this.tabControl_display.Controls.Add(this.tabPage1);
            this.tabControl_display.Controls.Add(this.tabPage2);
            this.tabControl_display.Location = new System.Drawing.Point(7, 7);
            this.tabControl_display.Name = "tabControl_display";
            this.tabControl_display.SelectedIndex = 0;
            this.tabControl_display.Size = new System.Drawing.Size(821, 431);
            this.tabControl_display.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox_camera);
            this.tabPage1.Controls.Add(this.cogDisplay1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(813, 405);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Camera";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox_camera
            // 
            this.groupBox_camera.Controls.Add(this.groupBox2);
            this.groupBox_camera.Controls.Add(this.button_camera_stop);
            this.groupBox_camera.Controls.Add(this.button_camera_3);
            this.groupBox_camera.Controls.Add(this.button_camera_2);
            this.groupBox_camera.Controls.Add(this.button_camera_1);
            this.groupBox_camera.Location = new System.Drawing.Point(607, 7);
            this.groupBox_camera.Name = "groupBox_camera";
            this.groupBox_camera.Size = new System.Drawing.Size(200, 392);
            this.groupBox_camera.TabIndex = 1;
            this.groupBox_camera.TabStop = false;
            this.groupBox_camera.Text = "Select";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label_display);
            this.groupBox2.Location = new System.Drawing.Point(3, 20);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(187, 44);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            // 
            // label_display
            // 
            this.label_display.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_display.Location = new System.Drawing.Point(0, 0);
            this.label_display.Name = "label_display";
            this.label_display.Size = new System.Drawing.Size(187, 44);
            this.label_display.TabIndex = 4;
            this.label_display.Text = "Display:None";
            this.label_display.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // button_camera_stop
            // 
            this.button_camera_stop.Location = new System.Drawing.Point(60, 234);
            this.button_camera_stop.Name = "button_camera_stop";
            this.button_camera_stop.Size = new System.Drawing.Size(75, 38);
            this.button_camera_stop.TabIndex = 3;
            this.button_camera_stop.Text = "Stop";
            this.button_camera_stop.UseVisualStyleBackColor = true;
            this.button_camera_stop.Click += new System.EventHandler(this.button_camera_stop_Click);
            // 
            // button_camera_3
            // 
            this.button_camera_3.Location = new System.Drawing.Point(60, 186);
            this.button_camera_3.Name = "button_camera_3";
            this.button_camera_3.Size = new System.Drawing.Size(75, 38);
            this.button_camera_3.TabIndex = 2;
            this.button_camera_3.Text = "Camera3";
            this.button_camera_3.UseVisualStyleBackColor = true;
            this.button_camera_3.Click += new System.EventHandler(this.button_camera_3_Click);
            // 
            // button_camera_2
            // 
            this.button_camera_2.Location = new System.Drawing.Point(60, 138);
            this.button_camera_2.Name = "button_camera_2";
            this.button_camera_2.Size = new System.Drawing.Size(75, 38);
            this.button_camera_2.TabIndex = 1;
            this.button_camera_2.Text = "Camera2";
            this.button_camera_2.UseVisualStyleBackColor = true;
            this.button_camera_2.Click += new System.EventHandler(this.button_camera_2_Click);
            // 
            // button_camera_1
            // 
            this.button_camera_1.Location = new System.Drawing.Point(60, 90);
            this.button_camera_1.Name = "button_camera_1";
            this.button_camera_1.Size = new System.Drawing.Size(75, 38);
            this.button_camera_1.TabIndex = 0;
            this.button_camera_1.Text = "Camera1";
            this.button_camera_1.UseVisualStyleBackColor = true;
            this.button_camera_1.Click += new System.EventHandler(this.button_camera_1_Click);
            // 
            // cogDisplay1
            // 
            this.cogDisplay1.ColorMapLowerClipColor = System.Drawing.Color.Black;
            this.cogDisplay1.ColorMapLowerRoiLimit = 0D;
            this.cogDisplay1.ColorMapPredefined = Cognex.VisionPro.Display.CogDisplayColorMapPredefinedConstants.None;
            this.cogDisplay1.ColorMapUpperClipColor = System.Drawing.Color.Black;
            this.cogDisplay1.ColorMapUpperRoiLimit = 1D;
            this.cogDisplay1.DoubleTapZoomCycleLength = 2;
            this.cogDisplay1.DoubleTapZoomSensitivity = 2.5D;
            this.cogDisplay1.Location = new System.Drawing.Point(0, 0);
            this.cogDisplay1.MouseWheelMode = Cognex.VisionPro.Display.CogDisplayMouseWheelModeConstants.Zoom1;
            this.cogDisplay1.MouseWheelSensitivity = 1D;
            this.cogDisplay1.Name = "cogDisplay1";
            this.cogDisplay1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("cogDisplay1.OcxState")));
            this.cogDisplay1.Size = new System.Drawing.Size(482, 346);
            this.cogDisplay1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.cogRecordsDisplay1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(813, 405);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Records";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // cogRecordsDisplay1
            // 
            this.cogRecordsDisplay1.Location = new System.Drawing.Point(0, 0);
            this.cogRecordsDisplay1.Name = "cogRecordsDisplay1";
            this.cogRecordsDisplay1.SelectedRecordKey = null;
            this.cogRecordsDisplay1.ShowRecordsDropDown = false;
            this.cogRecordsDisplay1.Size = new System.Drawing.Size(595, 393);
            this.cogRecordsDisplay1.Subject = null;
            this.cogRecordsDisplay1.TabIndex = 1;
            // 
            // vsPage1
            // 
            this.vsPage1.Controls.Add(this.cogToolGroupEditV21);
            this.vsPage1.Location = new System.Drawing.Point(4, 22);
            this.vsPage1.Name = "vsPage1";
            this.vsPage1.Padding = new System.Windows.Forms.Padding(3);
            this.vsPage1.Size = new System.Drawing.Size(834, 444);
            this.vsPage1.TabIndex = 5;
            this.vsPage1.Text = "一级视觉";
            this.vsPage1.UseVisualStyleBackColor = true;
            // 
            // cogToolGroupEditV21
            // 
            this.cogToolGroupEditV21.AllowDrop = true;
            this.cogToolGroupEditV21.AutoCreateTool = false;
            this.cogToolGroupEditV21.ContextMenuCustomizer = null;
            this.cogToolGroupEditV21.Location = new System.Drawing.Point(7, 7);
            this.cogToolGroupEditV21.MinimumSize = new System.Drawing.Size(489, 0);
            this.cogToolGroupEditV21.Name = "cogToolGroupEditV21";
            this.cogToolGroupEditV21.ShowNodeToolTips = true;
            this.cogToolGroupEditV21.Size = new System.Drawing.Size(808, 410);
            this.cogToolGroupEditV21.SuspendElectricRuns = false;
            this.cogToolGroupEditV21.TabIndex = 0;
            // 
            // vsPage2
            // 
            this.vsPage2.Controls.Add(this.cogToolGroupEditV22);
            this.vsPage2.Location = new System.Drawing.Point(4, 22);
            this.vsPage2.Name = "vsPage2";
            this.vsPage2.Padding = new System.Windows.Forms.Padding(3);
            this.vsPage2.Size = new System.Drawing.Size(834, 444);
            this.vsPage2.TabIndex = 6;
            this.vsPage2.Text = "二级视觉";
            this.vsPage2.UseVisualStyleBackColor = true;
            // 
            // cogToolGroupEditV22
            // 
            this.cogToolGroupEditV22.AllowDrop = true;
            this.cogToolGroupEditV22.AutoCreateTool = false;
            this.cogToolGroupEditV22.ContextMenuCustomizer = null;
            this.cogToolGroupEditV22.Location = new System.Drawing.Point(7, 7);
            this.cogToolGroupEditV22.MinimumSize = new System.Drawing.Size(489, 0);
            this.cogToolGroupEditV22.Name = "cogToolGroupEditV22";
            this.cogToolGroupEditV22.ShowNodeToolTips = true;
            this.cogToolGroupEditV22.Size = new System.Drawing.Size(808, 410);
            this.cogToolGroupEditV22.SuspendElectricRuns = false;
            this.cogToolGroupEditV22.TabIndex = 0;
            // 
            // vsPage3
            // 
            this.vsPage3.Controls.Add(this.cogToolGroupEditV23);
            this.vsPage3.Location = new System.Drawing.Point(4, 22);
            this.vsPage3.Name = "vsPage3";
            this.vsPage3.Padding = new System.Windows.Forms.Padding(3);
            this.vsPage3.Size = new System.Drawing.Size(834, 444);
            this.vsPage3.TabIndex = 7;
            this.vsPage3.Text = "三级视觉";
            this.vsPage3.UseVisualStyleBackColor = true;
            // 
            // cogToolGroupEditV23
            // 
            this.cogToolGroupEditV23.AllowDrop = true;
            this.cogToolGroupEditV23.AutoCreateTool = false;
            this.cogToolGroupEditV23.ContextMenuCustomizer = null;
            this.cogToolGroupEditV23.Location = new System.Drawing.Point(6, 6);
            this.cogToolGroupEditV23.MinimumSize = new System.Drawing.Size(489, 0);
            this.cogToolGroupEditV23.Name = "cogToolGroupEditV23";
            this.cogToolGroupEditV23.ShowNodeToolTips = true;
            this.cogToolGroupEditV23.Size = new System.Drawing.Size(808, 410);
            this.cogToolGroupEditV23.SuspendElectricRuns = false;
            this.cogToolGroupEditV23.TabIndex = 0;
            // 
            // groupBox_visionCtrl
            // 
            this.groupBox_visionCtrl.Controls.Add(this.btn_saveVS);
            this.groupBox_visionCtrl.Controls.Add(this.runJob_1_Btn);
            this.groupBox_visionCtrl.Controls.Add(this.runJob_2_Btn);
            this.groupBox_visionCtrl.Controls.Add(this.runJob_3_Btn);
            this.groupBox_visionCtrl.Location = new System.Drawing.Point(883, 24);
            this.groupBox_visionCtrl.Name = "groupBox_visionCtrl";
            this.groupBox_visionCtrl.Size = new System.Drawing.Size(106, 504);
            this.groupBox_visionCtrl.TabIndex = 7;
            this.groupBox_visionCtrl.TabStop = false;
            this.groupBox_visionCtrl.Text = "视觉操作";
            // 
            // btn_saveVS
            // 
            this.btn_saveVS.Location = new System.Drawing.Point(19, 310);
            this.btn_saveVS.Name = "btn_saveVS";
            this.btn_saveVS.Size = new System.Drawing.Size(75, 43);
            this.btn_saveVS.TabIndex = 6;
            this.btn_saveVS.Text = "保存视觉对象";
            this.btn_saveVS.UseVisualStyleBackColor = true;
            this.btn_saveVS.Click += new System.EventHandler(this.btn_saveVS_Click);
            // 
            // CogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1000, 520);
            this.Controls.Add(this.groupBox_visionCtrl);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "CogForm";
            this.Text = "CogForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.CogForm_FormClosed);
            this.Load += new System.EventHandler(this.CogForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.TabControl_vision.ResumeLayout(false);
            this.ImageDisplay.ResumeLayout(false);
            this.tabControl_display.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox_camera.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cogDisplay1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.vsPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV21)).EndInit();
            this.vsPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV22)).EndInit();
            this.vsPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cogToolGroupEditV23)).EndInit();
            this.groupBox_visionCtrl.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button runJob_1_Btn;
        private System.Windows.Forms.Button runJob_3_Btn;
        private System.Windows.Forms.Button runJob_2_Btn;
        private System.Windows.Forms.GroupBox groupBox1;
        public System.Windows.Forms.GroupBox groupBox_visionCtrl;
        private System.Windows.Forms.TabControl TabControl_vision;
        private System.Windows.Forms.TabPage ImageDisplay;
        private System.Windows.Forms.TabControl tabControl_display;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox_camera;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label_display;
        private System.Windows.Forms.Button button_camera_stop;
        private System.Windows.Forms.Button button_camera_3;
        private System.Windows.Forms.Button button_camera_2;
        private System.Windows.Forms.Button button_camera_1;
        private Cognex.VisionPro.Display.CogDisplay cogDisplay1;
        private System.Windows.Forms.TabPage tabPage2;
        private Cognex.VisionPro.CogRecordsDisplay cogRecordsDisplay1;
        private System.Windows.Forms.TabPage vsPage1;
        private Cognex.VisionPro.ToolGroup.CogToolGroupEditV2 cogToolGroupEditV21;
        private System.Windows.Forms.TabPage vsPage2;
        private Cognex.VisionPro.ToolGroup.CogToolGroupEditV2 cogToolGroupEditV22;
        private System.Windows.Forms.TabPage vsPage3;
        private Cognex.VisionPro.ToolGroup.CogToolGroupEditV2 cogToolGroupEditV23;
        private System.Windows.Forms.Button btn_saveVS;
    }
}

