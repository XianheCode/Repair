/*************************************
 * 1.关于工作流程和停止
 *     -使用一个stopFlag，在工作的每一步之间进行检测，如果检测到为真，则函数返回。
 *     -按下停止按钮时，将stopFlag赋值为true，且调用运动模块的停止方法
 *     -因为实际的工作流程在另外一个线程，所以不会阻塞停止方法的调用
 *     
 * 2.停止后的复原问题
 *     当因为意外原因停止时（停止按钮、修复失败、检测坏点失败等），处理如下：
 *     -对于治具和点亮的结果不做检测
 *     -对于第二级和第三级的修复结果不做检测
 *     -如果在第二级/第三级视觉中没有检测到坏点，直接跳过不做处理
 *     -如果在第一级视觉中没有检测到坏点，则停止加工并弹出警告窗口
 *     -如果在修复完成后检测到坏点，则停止加工并弹出窗口
 *     以上的停止加工都不会进行复原，而是停在当前位置等待人工处理。
 *     复原操作包括：回到初始位置、取消点亮信号，释放治具等。
 *     
 * 3.自动复原
 *     为了方便在停止后自动复原，添加复原按钮，其动作顺序为：
 *     -回到初始位置-取消点亮信号-释放治具
 *     
 * ***********************************/




using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MotionMod;
using VisionMod;
using System.Threading;
using System.IO;

using INIFile;
using SignalGenerator;


namespace RepairLaser
{
    public partial class MainForm : Form
    {

        public MotionWindow moWin = new MotionWindow();
        public CogForm cogWin = new CogForm();
        private SignalCtrlForm signalWin;
        private CaliForm caWin;

        private volatile bool stopFlag = false;
        private delegate void myWorkDelegate();
        private event myWorkDelegate workStarted;
        private event myWorkDelegate workStopped;

        private bool flag_local = false;
        private bool flag_absorb = false;
        private bool flag_push = false;
      

        
        private workPrm m_prm = new workPrm();

 
        public MainForm()
        {
            InitializeComponent();
            this.Top = 0;
            this.Left = 0;
            this.MaximumSize  = new Size(Screen.PrimaryScreen.WorkingArea.Width, 
                Screen.PrimaryScreen.WorkingArea.Height);

            moWin.MdiParent = this;
            moWin.Parent = this.panel_Motion;
            moWin.Show();

            cogWin.MdiParent = this;
            cogWin.Parent = this.panel_Vision;
            cogWin.Show();

            caWin = new CaliForm(this);
            signalWin = new SignalCtrlForm();
        }
        

        private void initPrmTextbox()
        {
            textBox_StartPos_x.Text = m_prm.startPos_x.ToString();
            textBox_StartPos_y.Text = m_prm.startPos_y.ToString();
            textBox_PhotoPos_x.Text = m_prm.PhotoPos_x.ToString();
            textBox_PhotoPos_y.Text = m_prm.PhotoPos_y.ToString();
            textBox_EndPos_x.Text = m_prm.endPos_x.ToString();
            textBox_EndPos_y.Text = m_prm.endPos_y.ToString();
            tb_focusZPos1.Text = m_prm.FocusPos_z.ToString();
            tb_focusZPos2.Text = m_prm.FocusPos_z_2.ToString();


            textBox_gap.Text = m_prm.gap.ToString();
            
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            m_prm.initPrm();

            initPrmTextbox();

            workStarted += disableForm;
            workStarted += moWin.disable_moveBtn;

            workStopped += enableForm;
            workStopped += moWin.enable_moveBtn;

            moWin.moveStarted += this.disableForm;
            moWin.moveStopped += this.enableForm;

            moWin.homeOver += enableForm;

            //disableForm();

            //statusLabel_1.Text = "请先回原！";
        }

        private void HomeOverFunc()
        {
            if (InvokeRequired)
            {

                this.Invoke(new myWorkDelegate(HomeOverFunc));
                return;
            }

            statusLabel_1.Text = "回原成功！";
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            cogWin.Close(); 
            moWin.Close();
            signalWin.Close();
            caWin.Close();
            
        }

        private void button_startWork_Click(object sender, EventArgs e)
        {
            if(workStarted != null)
                workStarted();
            Thread workThd = new Thread(doWork);
            workThd.IsBackground = true;
            if(workStopped != null)
                workThd.Start();

        }

        private void doWork()
        {
            stopFlag = false;
            
            //去放料位置
            if (stopFlag)
                return;

            //重置治具和信号发生器
            if (stopFlag)
                return;

            //机械手上料
            if (stopFlag)
                return;

            //治具压合
            if (stopFlag)
                return;

            //信号发生器点亮
            //if (!signalWin.lightUp())
            //    return;
            if (stopFlag)
                return;

            //去拍照位置
            goto_photoPos();
        

            if (stopFlag)
                return;

            visionPro_1();

            if (stopFlag)
                return;

            

            //检验是否修复成功
            if (stopFlag)
                return;

            //去下料位置
            if (stopFlag)
                return;

            //熄灭
            //signalWin.CloseSignal();
            if (stopFlag)
                return;

            //治具松开
            if (stopFlag)
                return;

            //机械手下料
            if (stopFlag)
                return;
            

            workStopped();
        }

        private void visionPro_1()
        {
            //一级视觉处理，得到一系列坐标
            double[] vision_1_x;
            double[] vision_1_y;
            int vision_1_num;
            cogWin.Job1_Run(out vision_1_x, out vision_1_y, out vision_1_num);

            if (stopFlag)
                return;
            if (vision_1_num <= 0)
            {
                Console.WriteLine("not found");
                workStopped();
                return;
            }

            //注意，这里在相对运动时出现未考虑到的情况，即后面点的初始位置已经变化。改用点位运动。
            //每一级视觉标定时，都是以下级视觉的中心为原点标定的，所以得到的坐标值即*-1 就得到移动到下一级视觉的step值
            double cPos_1_x, cPos_1_y;
            moWin.m_motion.Motion_GetRealTimePosAxis(0, out cPos_1_x);
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out cPos_1_y);


            for (int i = 0; i < vision_1_num; i++)
            {

                PTPPrm[] movePrm_2 = new PTPPrm[3];

                PTPPrm prm_2_x;
                prm_2_x.iCoorAxis = 0;
                prm_2_x.dPos = cPos_1_x - vision_1_x[i];

                PTPPrm prm_2_y;
                prm_2_y.iCoorAxis = 1;
                prm_2_y.dPos = cPos_1_y - vision_1_y[i];


                PTPPrm prm_2_z;
                prm_2_z.iCoorAxis = 2;
                prm_2_z.dPos = m_prm.FocusPos_z_2;

                movePrm_2[0] = prm_2_x;
                movePrm_2[1] = prm_2_y;
                movePrm_2[2] = prm_2_z;
                moWin.m_motion.Motion_PToPMove(movePrm_2);



                if (stopFlag)
                    return;

                //物镜切换、自动对焦
                if (stopFlag)
                    return;

                //二级视觉处理，得到若干坐标
                visionPro_2();

                if (stopFlag)
                    return;

                //检验是否修复成功
                if (stopFlag)
                    return;
            }
        }
        private void visionPro_2()
        {
            //二级视觉处理，得到若干坐标
            double[] vision_2_x;
            double[] vision_2_y;
            int vision_2_num;
            cogWin.Job2_Run(out vision_2_x, out vision_2_y, out vision_2_num);

            if (stopFlag)
                return;

            double cPos_2_x, cPos_2_y;
            moWin.m_motion.Motion_GetRealTimePosAxis(0, out cPos_2_x);
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out cPos_2_y);




            for (int j = 0; j < vision_2_num; j++)
            {
                PTPPrm[] movePrm_3 = new PTPPrm[3];

                PTPPrm prm_3_x;
                prm_3_x.iCoorAxis = 0;
                prm_3_x.dPos = cPos_2_x - vision_2_x[j];

                PTPPrm prm_3_y;
                prm_3_y.iCoorAxis = 1;
                prm_3_y.dPos = cPos_2_y - vision_2_y[j];


                PTPPrm prm_3_z;
                prm_3_z.iCoorAxis = 2;
                prm_3_z.dPos = m_prm.FocusPos_z;


                movePrm_3[0] = prm_3_x;
                movePrm_3[1] = prm_3_y;
                movePrm_3[2] = prm_3_z;
                moWin.m_motion.Motion_PToPMove(movePrm_3);



                if (stopFlag)
                    return;

                //物镜切换、自动对焦
                if (stopFlag)
                    return;

                //三级视觉处理，得到轮廓路径坐标
                //三级视觉只获得最靠近视野中心的那个斑点的路径
                visionPro_3();

                if (stopFlag)
                    return;
            }
        }

        //对于是否需要根据运行成功返回bool值
        //暂时不需要，一个坏点搜索失败可以弹出一个警告框/写一个log或者完全不处理，继续修复下一个坏点
        //如果是因为stopflag而停止，上层调用中应该在函数返回后进行stopFlag判定,调用栈依次退出即可
        //如果在中间发生了严重错误，必须停止整个加工流程，则可以设置stopFlag
        private void visionPro_3()
        {
            double[] vision_3_x;
            double[] vision_3_y;
            int vision_3_num;
            cogWin.Job3_Run(out vision_3_x, out vision_3_y, out vision_3_num, 2);

            if (vision_3_num == 0 || vision_3_x == null || vision_3_y == null)
            {
                //statusLabel_1.Text = "坏点路径搜索失败！";
                workStopped();
                return ;
            }

            //记录，测试用
            string file = "raw pos.txt";
            StreamWriter sw = new StreamWriter(file);

            for (int k = 0; k < vision_3_num; k++)
            {
                sw.WriteLine(vision_3_x[k]);
                sw.WriteLine(vision_3_y[k]);
            }

            sw.WriteLine(vision_3_num);
            sw.Flush();
            sw.Close();



            if (stopFlag)
                return;

            //坐标间隔处理，得到一系列加工点
            double[] work_x;
            double[] work_y;
            int work_num;

            datapro(vision_3_x, vision_3_y, vision_3_num, m_prm.gap, out work_x, out work_y, out work_num);


            //将相对位置转换为绝对位置
            double axisPos_x, axisPos_y;
            moWin.m_motion.Motion_GetRealTimePosAxis(0, out axisPos_x);
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out axisPos_y);

            for (int k = 0; k < work_num; k++)
            {
                work_x[k] = axisPos_x - work_x[k];
                work_y[k] = axisPos_y - work_y[k];
            }

            //路径记录，用于测试
            file = "work path.txt";
            sw = new StreamWriter(file, true);

            for (int k = 0; k < work_num; k++)
            {
                sw.WriteLine(work_x[k]);
                sw.WriteLine(work_y[k]);
            }

            sw.WriteLine(work_num);
            sw.Flush();
            sw.Close();


            if (stopFlag)
                return;
            //激光修复
            PTPPrm[] movePrm_work = new PTPPrm[2];
            for (int k = 0; k < work_num; k++)
            {
                movePrm_work[0].iCoorAxis = 0;
                movePrm_work[0].dPos = work_x[k];
                movePrm_work[1].iCoorAxis = 1;
                movePrm_work[1].dPos = work_y[k];

                moWin.m_motion.Motion_PToPMove(movePrm_work);
                //moWin.m_motion.Motion_LaserOn(1);
                if (stopFlag)
                    return;
            }
        }

        //移动到记录位置公用函数
        //num：1-10时为用户自定义，21，22，23分别为上料，拍照，下料位置
        //type=0时为阻塞式，type=1时为非阻塞式，默认为0
        private void goto_recordPos(int num, int type)
        {
            double x, y;
            switch(num)
            {
                case 21:
                    x = m_prm.startPos_x;
                    y = m_prm.startPos_y;
                    break;
                case 22:
                    x = m_prm.PhotoPos_x;
                    y = m_prm.PhotoPos_y;
                    break;
                case 23:
                    x = m_prm.endPos_x;
                    y = m_prm.endPos_y;
                    break;
                default:
                    //在这里添加自定义位置的判断和处理
                    return;
                    break;
            }

            PTPPrm[] movePrm = new PTPPrm[2];
            movePrm[0].iCoorAxis = 0;
            movePrm[0].dPos = x;

            movePrm[1].iCoorAxis = 1;
            movePrm[1].dPos = y;

            switch (type)
            {
                case 0:
                    moWin.m_motion.Motion_PToPMove(movePrm);
                    break;
                case 1:
                    moWin.Motion_PToPMove_unblock(movePrm);
                    break;
            }
        }
        private void goto_photoPos(int type=0)
        {
            goto_recordPos(22, type);
        }

        private void goto_endPos(int type=0)
        {
            goto_recordPos(23, type);
        }

        private void goto_startPos(int type=0)
        {
            goto_recordPos(21, type);
        }
        private void testWork()
        {

            Console.WriteLine("do the work");
            Thread.Sleep(3000);
            if (workStopped != null)
                workStopped();
        }


        private void getBoundary()
        {
            double[] pos_x;
            double[] pos_y;
            int number;

            double[] path_x;
            double[] path_y;
            int path_number;

            cogWin.Job3_Run(out pos_x, out pos_y, out number, 2);

            string file = "pos.txt";
            StreamWriter sw = new StreamWriter(file);

            for(int i=0;i<number;i++)
            {
                sw.WriteLine(pos_x[i]);
                sw.WriteLine(pos_y[i]);
            }


     
            sw.WriteLine(number);
            sw.Flush();
            sw.Close();


            datapro(pos_x, pos_y, number, m_prm.gap, out path_x, out path_y, out path_number);

            file = "path.txt";
            sw = new StreamWriter(file);
            for (int i = 0; i < path_number; i++)
            {
                sw.WriteLine(path_x[i]);
                sw.WriteLine(path_y[i]);
            }

            sw.WriteLine(path_number);
            sw.Flush();
            sw.Close();

            
            
            
        }

        private void pointDisper(double gap, double[] vision_x, double[] vision_y, int vision_num, 
            out double[]points_x, out double[]points_y, out int points_num)
        {
            gap = 0;
            points_x = vision_x;
            points_y = vision_y;
            points_num = vision_num;
        }


        private void enableForm()
        {
            if(InvokeRequired)
            {
                this.Invoke(new myWorkDelegate(enableForm));
                return;
            }

            button_startWork.Enabled = true;
            groupBox_posPrm.Enabled = true;
            groupBox_otherPrm.Enabled = true;
            button_SetSignalPrm.Enabled = true;

        }

        private void disableForm()
        {
            if (InvokeRequired)
            {
                this.Invoke(new myWorkDelegate(disableForm));
                return;
            }

            button_startWork.Enabled = false ;
            groupBox_posPrm.Enabled = false;
            groupBox_otherPrm.Enabled = false;
            button_SetSignalPrm.Enabled = false;
        }

 
        private void button_stopWork_Click(object sender, EventArgs e)
        {
            stopFlag = true;
            moWin.m_motion.Motion_Stop();
            Thread.Sleep(200);
            if(workStopped != null)
                workStopped();
        }

        //记录、应用、移动
        //记录：从运动模块读取坐标，并显示在屏幕，但是不会应用
        //应用：将textBox中的数据应用到控制参数
        //移动：移动到控制参数中的位置，注意不一定是TextBox中的数值
        private void button_StartPos_rc_Click(object sender, EventArgs e)
        {
            double pos_x, pos_y;
            if(moWin.m_motion.Motion_GetRealTimePosAxis(0, out pos_x) &&
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out pos_y))
            {
                textBox_StartPos_x.Text = pos_x.ToString();
                textBox_StartPos_y.Text = pos_y.ToString();
                statusLabel_1.Text = "拍照位置记录成功";
            }
            else
            {
                statusLabel_1.Text = "拍照位置记录失败";
            }

        }

        private void button_StartPos_ap_Click(object sender, EventArgs e)
        {
            double temp1,temp2;
            bool ret1 = double.TryParse(this.textBox_StartPos_x.Text, out temp1);
            bool ret2 = double.TryParse(this.textBox_StartPos_y.Text, out temp2);

            if(ret1 && ret2)
            {
                m_prm.startPos_x = temp1;
                m_prm.startPos_y = temp2;
                statusLabel_1.Text = "参数应用成功";
            }
            else
            {
                statusLabel_1.Text = "参数应用失败,请检查参数格式";
            }
        }
        private void button_StartPos_mv_Click(object sender, EventArgs e)
        {
            goto_startPos(1);

        }


        private void button_PhotoPos_rc_Click(object sender, EventArgs e)
        {
            double photo_x, photo_y;
            if (moWin.m_motion.Motion_GetRealTimePosAxis(0, out photo_x) && moWin.m_motion.Motion_GetRealTimePosAxis(1, out photo_y))
            {

                textBox_PhotoPos_x.Text = photo_x.ToString();
                textBox_PhotoPos_y.Text = photo_y.ToString();
                statusLabel_1.Text = "拍照位置记录成功";
            }
            else
            {
                statusLabel_1.Text = "拍照位置记录失败";
            }
        }

        private void button_PhotoPos_ap_Click(object sender, EventArgs e)
        {
            double temp1, temp2;
            bool ret1 = double.TryParse(this.textBox_PhotoPos_x.Text, out temp1);
            bool ret2 = double.TryParse(this.textBox_PhotoPos_y.Text, out temp2);

            if (ret1 && ret2)
            {
                m_prm.PhotoPos_x = temp1;
                m_prm.PhotoPos_y = temp2;
                statusLabel_1.Text = "参数应用成功";
            }
            else
            {
                statusLabel_1.Text = "参数应用失败,请检查参数格式";
            }
        }
        private void button_PhotoPos_mv_Click(object sender, EventArgs e)
        {
            goto_photoPos(1);
        }

        private void button_EndPos_rc_Click(object sender, EventArgs e)
        {
            double pos_x, pos_y;
            if (moWin.m_motion.Motion_GetRealTimePosAxis(0, out pos_x) &&
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out pos_y))
            {
                textBox_EndPos_x.Text = pos_x.ToString();
                textBox_EndPos_y.Text = pos_y.ToString();
                statusLabel_1.Text = "下料位置记录成功";
            }
            else
            {
                statusLabel_1.Text = "下料位置记录失败";
            }
        }
        private void button_EndPos_ap_Click(object sender, EventArgs e)
        {
            double temp1, temp2;
            bool ret1 = double.TryParse(this.textBox_EndPos_x.Text, out temp1);
            bool ret2 = double.TryParse(this.textBox_EndPos_y.Text, out temp2);

            if (ret1 && ret2)
            {
                m_prm.endPos_x = temp1;
                m_prm.endPos_y = temp2;
                statusLabel_1.Text = "参数应用成功";
            }
            else
            {
                statusLabel_1.Text = "参数应用失败,请检查参数格式";
            }
        }
        private void button_EndPos_mv_Click(object sender, EventArgs e)
        {
            goto_endPos(1);
        }



        private void button_gap_Click(object sender, EventArgs e)
        {
            double temp1;
            bool ret1 = double.TryParse(this.textBox_gap.Text, out temp1);

            if (ret1)
            {
                m_prm.gap = temp1;
                statusLabel_1.Text = "参数应用成功";
            }
            else
            {
                statusLabel_1.Text = "参数应用失败,请检查参数格式";
            }
        }


        //将参数保存至离线ini文件
        private void button_savePrm_Click(object sender, EventArgs e)
        {
            if (m_prm.savePrm())
                statusLabel_1.Text = "参数保存成功";
            else
                statusLabel_1.Text = "参数保存失败";
        }


        private void button_SetSignalPrm_Click(object sender, EventArgs e)
        {
            signalWin.Show();
        }



        static void datapro(double[] pos_x, double[] pos_y, int pos_number,
            double gap, out double[] path_x, out double[] path_y, out int path_number)
        {
            path_x = null;
            path_y = null;
            path_number = 0;
            if (pos_x == null || pos_y == null || pos_number == 0)
                return;
            if (pos_x.Length != pos_number || pos_y.Length != pos_number)
                return;
            path_x = new double[pos_number];
            path_y = new double[pos_number];

            path_x[0] = pos_x[0];
            path_y[0] = pos_y[0];

            int k = 0;
            double temp_x = path_x[k];
            double temp_y = path_y[k];
            k++;


            for (int i = 1; i < pos_number; i++)
            {
                while (i < pos_number && distance(pos_x[i], pos_y[i], temp_x, temp_y) < gap)
                {
                    i++;
                }

                if (i < pos_number)
                {

                    temp_x = path_x[k] = pos_x[i];
                    temp_y = path_y[k] = pos_y[i];
                    k++;

                }
                else
                {
                    if (distance(pos_x[0], pos_y[0], temp_x, temp_y) >= gap)
                    {
                        temp_x = path_x[k] = pos_x[i-1];
                        temp_y = path_y[k] = pos_y[i-1];
                        k++;
                    }
                }
            }

            path_number = k;
        }

        static double distance(double x1, double y1, double x2, double y2)
        {
            double temp = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
            temp = Math.Sqrt(temp);
            return temp;
        }

        private void btn_cali_Click(object sender, EventArgs e)
        {
            caWin.Show();
        }

        private void btn_focusRcd1_Click(object sender, EventArgs e)
        {
            double zPos;
            if (moWin.m_motion.Motion_GetRealTimePosAxis(2, out zPos))
            {
                m_prm.FocusPos_z = zPos;
                tb_focusZPos1.Text = zPos.ToString();
                statusLabel_1.Text = "焦距位置应用成功";
            }
            else
            {
                statusLabel_1.Text = "焦距位置应用失败";
            }
        }

        private void btn_focusMove1_Click(object sender, EventArgs e)
        {
            PTPPrm[] movePrm = new PTPPrm[1];
            PTPPrm prm;
            prm.iCoorAxis = 2;
            prm.dPos = m_prm.FocusPos_z;
            movePrm[0] = prm;
            moWin.Motion_PToPMove_unblock(movePrm);
        }

        private void btn_focusRcd2_Click(object sender, EventArgs e)
        {
            double zPos;
            if (moWin.m_motion.Motion_GetRealTimePosAxis(2, out zPos))
            {
                m_prm.FocusPos_z_2 = zPos;
                tb_focusZPos2.Text = zPos.ToString();
                statusLabel_1.Text = "焦距位置应用成功";
            }
            else
            {
                statusLabel_1.Text = "焦距位置应用失败";
            }
        }

        private void btn_focusMove2_Click(object sender, EventArgs e)
        {
            PTPPrm[] movePrm = new PTPPrm[1];
            PTPPrm prm;
            prm.iCoorAxis = 2;
            prm.dPos = m_prm.FocusPos_z_2;
            movePrm[0] = prm;
            moWin.Motion_PToPMove_unblock(movePrm);
        }

        private void btn_setMotionPrm_Click(object sender, EventArgs e)
        {
            moWin.m_motion.Motion_ExeSetParamApplication();
        }

        private void btn_testJob3_Click(object sender, EventArgs e)
        {

        }

        private void runJob3_getPath()
        {
            double[] vision_3_x;
            double[] vision_3_y;
            int vision_3_num;
            cogWin.Job3_Run(out vision_3_x, out vision_3_y, out vision_3_num, 2);

            if (vision_3_num == 0 || vision_3_x == null || vision_3_y == null)
            {
                return;
            }

            //记录，测试用
            string file = "raw pos.txt";
            StreamWriter sw = new StreamWriter(file);

            for (int k = 0; k < vision_3_num; k++)
            {
                sw.WriteLine(vision_3_x[k]);
                sw.WriteLine(vision_3_y[k]);
            }

            sw.WriteLine(vision_3_num);
            sw.Flush();
            sw.Close();




            //坐标间隔处理，得到一系列加工点
            double[] work_x;
            double[] work_y;
            int work_num;

            datapro(vision_3_x, vision_3_y, vision_3_num, m_prm.gap, out work_x, out work_y, out work_num);


            double axisPos_x, axisPos_y;
            moWin.m_motion.Motion_GetRealTimePosAxis(0, out axisPos_x);
            moWin.m_motion.Motion_GetRealTimePosAxis(1, out axisPos_y);

            for (int k = 0; k < work_num; k++)
            {
                work_x[k] = axisPos_x - work_x[k];
                work_y[k] = axisPos_y - work_y[k];
            }

            //ceshi
            file = "work path.txt";
            sw = new StreamWriter(file, true);

            for (int k = 0; k < work_num; k++)
            {
                sw.WriteLine(work_x[k]);
                sw.WriteLine(work_y[k]);
            }

            sw.WriteLine(work_num);
            sw.Flush();
            sw.Close();
        }

        private void btn_local_Click(object sender, EventArgs e)
        {
            if(flag_local)
            {
                moWin.m_motion.Motion_OutputBit(1, 1);
                btn_local.Text = "定位";
                flag_local = false;
            }
            else
            {
                moWin.m_motion.Motion_OutputBit(1, 0);
                btn_local.Text = "取消定位";
                flag_local = true;
            }
        }

        private void btn_absorb_Click(object sender, EventArgs e)
        {
            if (flag_absorb)
            {
                moWin.m_motion.Motion_OutputBit(3, 1);
                btn_absorb.Text = "吸附";
                flag_absorb = false;
            }
            else
            {
                moWin.m_motion.Motion_OutputBit(3, 0);
                btn_absorb.Text = "关闭吸附";
                flag_absorb = true;
            }
        }

        private void btn_pushdown_Click(object sender, EventArgs e)
        {
            if (flag_push)
            {
                moWin.m_motion.Motion_OutputBit(5, 1);
                btn_pushdown.Text = "下压";
                flag_push = false;
            }
            else
            {
                moWin.m_motion.Motion_OutputBit(5, 0);
                btn_pushdown.Text = "取消下压";
                flag_push = true;
            }
        }

        private void btn_goBack_Click(object sender, EventArgs e)
        {
            signalWin.lightDown();
            Thread.Sleep(100);
            lightDown_release();

        }

        private void lightUp_push()
        {
            moWin.m_motion.Motion_OutputBit(1, 0);
            Thread.Sleep(500);
            moWin.m_motion.Motion_OutputBit(3, 0);
            Thread.Sleep(200);
            moWin.m_motion.Motion_OutputBit(5, 0);
            Thread.Sleep(500);
        }

        private void lightDown_release()
        {
            moWin.m_motion.Motion_OutputBit(5, 1);
            Thread.Sleep(200);
            moWin.m_motion.Motion_OutputBit(3, 1);
            Thread.Sleep(200);
            moWin.m_motion.Motion_OutputBit(1, 1);
            Thread.Sleep(100);
        }


        
    }
}
