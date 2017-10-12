/***********标定模块*************
 * -开始标定之前，必须在相应的视觉序列里准备好模板
 * -先选择相机，再点击开始标定
 * -每次标定一个位置，至少标定三个位置，最好能布满相机的视野
 * -标定完成后，必须点击视觉工具上的保存，否则退出软件后无效
 * 
 * 
 * 
 * **********************/




using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace RepairLaser
{
    public partial class CaliForm : Form
    {
        public delegate void myDelegrate();
        public event myDelegrate caliStarting;
        public event myDelegrate caliStopped;
        public event myDelegrate caliOriStarting;
        public event myDelegrate caliOriStopped;

        int camNum = 0;
        int caliNum = 0;
        bool caliFlag;
        bool caliFlag_ori;

        struct caliPoint
        {
            public PointF pixPos;
            public PointF realPos;

            
        };

        List<caliPoint> mList = new List<caliPoint>();


        double Ori_pos1_x, Ori_pos1_y, Ori_pos2_x, Ori_pos2_y, Ori_cali_x, Ori_cali_y;


        MainForm mf;
        public CaliForm(MainForm form)
        {
            mf = form;
            InitializeComponent();
            initForm();
        }

        private void initForm()
        {
            //注册标定开始和结束的事件处理函数
            caliStarting += preWork;
            caliStopped += caliEnd;
            lb_cali.Text = "标定未开始";

            caliOriStarting += preWork_Ori;
            caliOriStopped += caliEnd_Ori;

            gb_selectCali.Enabled = true;
            gb_selectVision.Enabled = true;
            gb_cali.Enabled = false;
            gb_caliOrigion.Enabled = false;
        }

        private void camaraCheck()
        {
            if (rbtn_1.Checked)
                camNum = 1;
            else if (rbtn_2.Checked)
                camNum = 2;
            else
                camNum = 3;
        }

        //标定之前的准备工作：确定相机号，初始化参数，按钮控制等
        public void preWork()
        {
            camaraCheck();

            gb_selectVision.Enabled = false;
            gb_selectCali.Enabled = false;
            gb_caliOrigion.Enabled = false;
            gb_cali.Enabled = true;
            btn_cali.Enabled = true;
            btn_over.Enabled = false;

            lb_cali.Text = "请移动到目标位置，标定第一个点";
            mList.Clear();
            caliNum = 0;
            caliFlag = true;


        }

        public void preWork_Ori()
        {
            camaraCheck();

            gb_selectVision.Enabled = false;
            gb_selectCali.Enabled = false;
            gb_caliOrigion.Enabled = true;
            gb_cali.Enabled = false;

            lb_caliOri.Text = string.Format("请将标志物移动到{0}级视觉的视野中心，点击<记录当前位置>按钮",camNum+1);
            btn_caliOri_2.Enabled = false;
            btn_caliOri_1.Enabled = true;

            caliFlag_ori = true;
        }

        //标定完成后的善后工作
        private void caliEnd()
        {
            if (InvokeRequired)
            {
                this.Invoke(new myDelegrate(caliEnd));
                return;
            }

            lb_cali.Text = string.Format("标定完成");
            gb_cali.Enabled = false;
            gb_selectVision.Enabled = true;
            gb_selectCali.Enabled = true;
        }

        private void caliEnd_Ori()
        {
            if (InvokeRequired)
            {
                this.Invoke(new myDelegrate(caliEnd_Ori));
                return;
            }

            if (caliFlag_ori)
            {
                lb_caliOri.Text = string.Format("标定完成");
            }
            else
            {
                lb_caliOri.Text = string.Format("标定失败，请检查并重新标定");
            }

            gb_caliOrigion.Enabled = false;
            gb_selectVision.Enabled = true;
            gb_selectCali.Enabled = true;
        }

        public void checkVision()
        {

        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            //添加异常处理
                caliStarting();


        }

        //注意，和其他窗口一样，Cognex的处理必须新开子线程；界面操作必须回到gui线程
        private void btn_cali_Click(object sender, EventArgs e)
        {
            btn_cali.Enabled = false;
            lb_cali.Text = string.Format("开始标定第{0}个点", caliNum+1);

            var t = new Thread(caliOnePos);
            t.Start();


        }

        //使用模板匹配工具确定一个点的像素坐标/真实坐标，使用前必须保证视觉序列中已经准备好模板
        private void caliOnePos()
        {
            double x,y;
            mf.moWin.m_motion.Motion_GetRealTimePosAxis(0, out x);
            mf.moWin.m_motion.Motion_GetRealTimePosAxis(1, out y);
            PointF rpos = new  PointF((float)x, (float)y);

            
            double[] arrayX = null, arrayY = null;
            int number;
            switch (camNum)
            {
                case 1:
                    mf.cogWin.Job1_Run(out arrayX, out arrayY, out number, 1);
                    break;
                case 2:
                    mf.cogWin.Job2_Run(out arrayX, out arrayY, out number, 1);
                    break;
                case 3:
                    mf.cogWin.Job3_Run(out arrayX, out arrayY, out number, 1);
                    break;
                default:
                    number = 0;
                    break;
            }
            if(number <= 0)
            {
                caliFlag = false;
                resumeForm();
                return;
            }
            
           
           

            PointF ppos = new PointF((float)arrayX[0], (float)arrayY[0]); 

            //PointF ppos = new PointF(1, 1); 

            caliPoint cp;
            cp.pixPos = ppos;
            cp.realPos = rpos;

            caliNum++;
            mList.Add(cp);
            resumeForm();
            return;
        }

        //按钮使能恢复
        private void resumeForm()
        {
            if (InvokeRequired)
            {
                this.Invoke(new myDelegrate(resumeForm));
                return;
            }

            if(caliFlag)
            {
                lb_cali.Text = string.Format("当前点标定成功。请移动到第{0}个点", caliNum + 1);
                if (caliNum >= 3)
                    btn_over.Enabled = true;
                btn_cali.Enabled = true;
            }
            else
            {
                lb_cali.Text = string.Format("当前点标定失败，请点击取消退出");
                btn_cali.Enabled = false;
            }
        }

        //在子线程中进行标定
        private void btn_over_Click(object sender, EventArgs e)
        {

            var t = new Thread(doCalibrate);
            t.Start();
            
        }

        //根据得到的坐标数组进行标定
        private void doCalibrate()
        {
            string path = string.Format("Cameracali.txt");
            StreamWriter sw = new StreamWriter(path);
            sw.WriteLine(DateTime.Now);
            sw.WriteLine("camera{0} start cali:", camNum);

            Cognex.VisionPro.CalibFix.CogCalibNPointToNPoint myCali;

            switch (camNum)
            {
                case 1:
                    myCali = mf.cogWin.calibTool_1.Calibration;
                    break;
                case 2:
                    myCali = mf.cogWin.calibTool_2.Calibration;
                    break;
                case 3:
                    myCali = mf.cogWin.calibTool_3.Calibration;
                    break;
                default:
                    sw.WriteLine("camNum error");
                    sw.Close();
                    return;
            }

            try
            {
                int numberPoints = mList.Count;

               

                myCali.NumPoints = numberPoints;
                for (int i = 0; i < numberPoints; i++)
                {
                    caliPoint cp = mList[i];
                    myCali.SetUncalibratedPoint(i, cp.pixPos.X, cp.pixPos.Y);
                    myCali.SetRawCalibratedPoint(i, cp.realPos.X, cp.realPos.Y);
                }

                myCali.CalibratedOriginX = 0;
                myCali.CalibratedOriginY = 0;

                myCali.Calibrate();


            }
            catch (Cognex.VisionPro.Exceptions.CogException e)
            {
                sw.WriteLine("exception occur:{0}", e.Message);
            }
            finally
            {
                if (myCali.Calibrated)
                    sw.WriteLine("cali succeed");
                else
                    sw.WriteLine("cali failed");
                sw.Close();
            }

            caliStopped();
            

        }


        private void btn_cancel_Click(object sender, EventArgs e)
        {
            lb_cali.Text = "标定未开始";
            gb_cali.Enabled = false;
            gb_caliOrigion.Enabled = false;
            gb_selectVision.Enabled = true;
            gb_selectCali.Enabled = true;
        }

        private void btn_close_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void btn_origion_Click(object sender, EventArgs e)
        {
            if (camNum == 3) return;
            caliOriStarting();
        }

        private void btn_caliOri_1_Click(object sender, EventArgs e)
        {

            mf.moWin.m_motion.Motion_GetRealTimePosAxis(0, out Ori_pos1_x);
            mf.moWin.m_motion.Motion_GetRealTimePosAxis(1, out Ori_pos1_y);
            lb_caliOri.Text = string.Format("当前位置记录成功，请移动到{0}级视觉，并点击<标定>按钮", camNum);

            btn_caliOri_2.Enabled = true;
            btn_caliOri_1.Enabled = false;
        }

        private void btn_caliOri_2_Click(object sender, EventArgs e)
        {
            var t = new Thread(caliOri);
            t.Start();
        }


        //用类似于python的上下文管理 with ...as更好。或者直接用try ..finally..
        private void caliOri()
        {
            mf.moWin.m_motion.Motion_GetRealTimePosAxis(0, out Ori_pos2_x);
            mf.moWin.m_motion.Motion_GetRealTimePosAxis(1, out Ori_pos2_y);

            double[] arrayX = null, arrayY = null;
            int number;
            switch (camNum)
            {
                case 1:
                    mf.cogWin.Job1_Run(out arrayX, out arrayY, out number, 0);
                    break;
                case 2:
                    mf.cogWin.Job2_Run(out arrayX, out arrayY, out number, 0);
                    break;
                case 3:
                    mf.cogWin.Job3_Run(out arrayX, out arrayY, out number, 2);
                    break;
                default:
                    number = 0;
                    break;
            }
            if (number <= 0)
            {
                //lb_caliOri.Text = "视觉工具运行失败，请重新标定";
                caliFlag_ori = false;
                caliOriStopped();
                return;
            }


            Ori_cali_x = arrayX[0];
            Ori_cali_y = arrayY[0];

            double offset_x = Ori_cali_x + Ori_pos1_x - Ori_pos2_x;
            double offset_y = Ori_cali_y + Ori_pos1_y - Ori_pos2_y;


            string path = string.Format("Cameracali.txt");
            StreamWriter sw = new StreamWriter(path,true);
            sw.WriteLine(DateTime.Now);
            sw.WriteLine("camera{0} start cali:", camNum);

            Cognex.VisionPro.CalibFix.CogCalibNPointToNPoint myCali;

            switch (camNum)
            {
                case 1:
                    myCali = mf.cogWin.calibTool_1.Calibration;
                    break;
                case 2:
                    myCali = mf.cogWin.calibTool_2.Calibration;
                    break;
                case 3:
                    myCali = mf.cogWin.calibTool_3.Calibration;
                    break;
                default:
                    sw.WriteLine("camNum error");
                    sw.Close();
                    caliFlag_ori = false;
                    caliOriStopped();
                    return;
            }

            try
            {
                myCali.CalibratedOriginX += offset_x;
                myCali.CalibratedOriginY += offset_y;
                myCali.Calibrate();

            }
            catch (Cognex.VisionPro.Exceptions.CogException e)
            {
                sw.WriteLine("exception occur:{0}", e.Message);
            }
            finally
            {
                if (myCali.Calibrated)
                    sw.WriteLine("cali succeed");
                else
                    sw.WriteLine("cali failed");
                sw.Close();
            }

            caliOriStopped();

            return;
        }

        
    }
}
