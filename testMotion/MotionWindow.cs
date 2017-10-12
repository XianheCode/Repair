/**********运动模块*****************
 * 1.MotionControl中，有三个调用是阻塞的：Motion_StepMove，Motion_PToPMove，Motion_Home
 *   在MotionWindow中实现了它们的非阻塞版本，并加入了按钮控制
 * 2.其他界面可以将它们的按钮控制函数加入MotionWindow的事件：moveStarted、moveStopped
 *   也可以将MotionWindow的按钮控制函数enable_moveBtn、disable_moveBtn加入它们自己的启停事件，实现运动互锁
 * 3.MotionWindow中对于阻塞函数的调用都新开了子线程，在其他界面中如果直接调用MotionControl中的阻塞函数，
 *   务必新开子线程，并进行按钮的使能控制。注意按钮只能在GUI所在线程操作，所以按钮控制函数应该用Invoke进行迁移。
 * 
 * 4.回零方式：Home回零故障，所以暂时采用限位回零
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
using System.Threading;
using System.IO;



namespace MotionMod
{
    
    
    public partial class MotionWindow : Form
    {
            FileStream fs = null;
            StreamWriter sw = null;


        public delegate void moveDelegate();
        public event moveDelegate  moveStopped;
        public event moveDelegate moveStarted;
        private System.Windows.Forms.Timer m_timer;

        //用于回零后重置速度，其实用事件实现更好
        private velType m_velType;


        private string stepText = null;
        public MotionWindow()
        {
            InitializeComponent();
            moveStopped += enable_moveBtn;
            moveStarted += disable_moveBtn;

      
        }

        private void testForm_Load(object sender, EventArgs e)
        {
            bool ret = m_motion.IsInit;
            if (!ret)
            {
                MessageBox.Show("运动模块初始化失败，请关闭软件！");
                this.Close();
            }
            else
            {
                statusLabel.Text = "运动模块初始化成功！";
            }


            m_timer = new System.Windows.Forms.Timer();
            m_timer.Tick += timer_tick;
            m_timer.Interval = 100;
            m_timer.Start();



            fs = new FileStream("log.txt", FileMode.Create);
            sw = new StreamWriter(fs);
            sw.WriteLine("Go");

            BtnSetSpeed((int)velType.lowVel);
            m_velType = velType.lowVel;

        }


        private void timer_tick(object sender, EventArgs e)
        {
            double pos;
            m_motion.Motion_GetRealTimePosAxis(0, out pos);
            textBox_X_Pos.Text = pos.ToString();

            m_motion.Motion_GetRealTimePosAxis(1, out pos);
            textBox_Y_Pos.Text = pos.ToString();

            m_motion.Motion_GetRealTimePosAxis(2, out pos);
            textBox_Z_Pos.Text = pos.ToString();
        }

        //没有使用
        private void checkStatus(bool flag)
        {
            if(flag)
            {
                statusLabel.Text = "动作执行成功！";
            }
            else
            {
                statusLabel.Text = "动作执行失败！";
            }
        }

        //暂未实现
        private void button_Home_Click(object sender, EventArgs e)
        {
   


            HOMEPrm[] movePrm = new HOMEPrm[3];
            HOMEPrm xPrm;
            xPrm.iCoorAxis = 0;
            xPrm.iDirect = -1;
            xPrm.dOrgMove = 0;
            xPrm.dHomeOff = 200;
            movePrm[0] = xPrm;

            HOMEPrm yPrm;
            yPrm.iCoorAxis = 1;
            yPrm.iDirect = -1;
            yPrm.dOrgMove = 0;
            yPrm.dHomeOff = 200;
            movePrm[1] = yPrm;

            HOMEPrm zPrm;
            zPrm.iCoorAxis = 2;
            zPrm.iDirect = -1;
            zPrm.dOrgMove = 0;
            zPrm.dHomeOff = 40;
            movePrm[2] = zPrm;

            Motion_Home_unblock(movePrm);

            
        }


        private void button_Stop_Click(object sender, EventArgs e)
        {
            m_motion.Motion_Stop();
        }

        //单轴Jog移动，输入为轴号和方向，非阻塞调用
        private void singleAxisJogMove(int iAxisNO, int iDirect)
        {

            InspectThePrm(iAxisNO, iDirect);

            JOGPrm z_jogprm;
            z_jogprm.iCoorAxis = iAxisNO;
           
            z_jogprm.iDirect = iDirect;

            JOGPrm[] array_jog = new JOGPrm[1];
            array_jog[0] = z_jogprm;

            m_motion.Motion_JogMove(array_jog);
        }
        
        //开启新线程，执行步进移动，
        private Thread  startStepMove(int iAxisNO, int iDirect)
        {
            if(moveStarted != null)
                moveStarted();
            var t = new Thread(() =>
                {
                    stepMove_Axis(iAxisNO, iDirect);
                    if (moveStopped != null)
                        moveStopped();
                } );
            t.IsBackground = true;
            t.Start();
            return t;
        }

        //步进移动，输入轴号和方向，步距会从界面读取
        private void stepMove_Axis(int iAxisNO, int iDirection)
        {

            InspectThePrm(iAxisNO, iDirection);
         
            
                STEPPrm z_stepprm;

                z_stepprm.iCoorAxis = iAxisNO;
                double stepdis;
                bool ret = double.TryParse(stepText, out stepdis);
                if (!ret ||  stepdis <= 0 || (iAxisNO == 2 && stepdis > 10))
                {
                    MessageBox.Show("请正确设置步距，且Z轴步距应不大于10mm！");
                }
                else
                {
                    z_stepprm.dStepPos = stepdis * iDirection;
                    STEPPrm[] array_step = new STEPPrm[1];
                    array_step[0] = z_stepprm;

                    bool flag = m_motion.Motion_StepMove(array_step);

                    sw.WriteLine("move {0}", flag);
                    sw.Flush();
                }

            

            moveStopped();

        }

        //参数检查
        private bool InspectThePrm(int iAxisNO, int iDirection)
        {
            if (iAxisNO < 0 || iAxisNO > 7)
            {
                MessageBox.Show("轴号选择有误！");
                return false;
            }

            if (iDirection != -1 && iDirection != 1)
            {
                MessageBox.Show("方向输入错误");
                return false;
            }

            return true;
        }

        //按钮使能，如果在子线程调用，会转移到主线程再执行
        public void enable_moveBtn()
        {
            if (InvokeRequired)
            {
                
                this.Invoke(new moveDelegate(enable_moveBtn));
                return;
            }

            groupBox_MoveOp.Enabled = true;
            button_Home.Enabled = true;
            button_setPrm.Enabled = true;
        }

        public void disable_moveBtn()
        {
            if(InvokeRequired)
            {
                this.Invoke(new moveDelegate(disable_moveBtn));
                return;
            }
            groupBox_MoveOp.Enabled = false;
            button_Home.Enabled = false;
            button_setPrm.Enabled = false;
        }

        #region 运动按钮系列操作
        //按下操作共用函数，如勾选步进，则进行步进移动；如没勾选，则开启Jog移动
        private void BtnDown(int iAxisNO, int iDirect)
        {

            if (checkBox_Step.Checked)
            {
                stepText = textBox_StepDistance.Text;
                startStepMove(iAxisNO, iDirect);
            }
            else
            {
                if (iAxisNO == 2)
                    iDirect = iDirect * (-1);
                singleAxisJogMove(iAxisNO, iDirect);
            }
        }

        //松开操作共用函数，如勾选步进，则什么都不做；如没勾选，则停止Jog移动
        private void BtnUp()
        {
            if (!checkBox_Step.Checked)
            {
                m_motion.Motion_Stop();
            }
        }

        private void button_Z_P_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(2, 1);
        }

        private void button_Z_P_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        private void button_Z_N_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(2, -1);
        }

        private void button_Z_N_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        private void button_Y_P_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(1, 1);
        }

        private void button_Y_P_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        private void button_Y_N_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(1, -1);
        }

        private void button_Y_N_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        private void button_X_P_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(0, 1);
        }

        private void button_X_P_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        private void button_X_N_MouseDown(object sender, MouseEventArgs e)
        {
            BtnDown(0, -1);
        }

        private void button_X_N_MouseUp(object sender, MouseEventArgs e)
        {
            BtnUp();
        }

        #endregion

        //速度选择按钮共用函数
        //注意！！！暂时改为了2，没有设置z轴速度，因为共享库中参数设置问题
        private void BtnSetSpeed(int iHandVelType)
        {
       
            SPEEDPrm[] array_sprm = new SPEEDPrm[3];
            for (int i = 0; i < 3; i++)
            {
                SPEEDPrm sprm;
                sprm.dAcc = sprm.dDec = sprm.dLowVel = sprm.dHighVel = 0;
                sprm.iCoorAxis = i;
                sprm.iMoveType = (int)moveType.handType;
                sprm.iHandVelType = iHandVelType;
                array_sprm[i] = sprm;
            }

            if (!m_motion.Motion_SetSglSpeed(array_sprm))
                MessageBox.Show("速度设置失败！");
        }


        private void radioButton_Move_H_CheckedChanged(object sender, EventArgs e)
        {
            if(radioButton_Move_H.Checked)
            {
              
                BtnSetSpeed((int)velType.HighVel);
                m_velType = velType.HighVel;
            }

        }


        private void radioButton_Move_M_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Move_M.Checked)
            {
                
                BtnSetSpeed((int)velType.midVel);
                m_velType = velType.midVel;
            }
        }

        private void radioButton_Move_L_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Move_L.Checked)
            {
                BtnSetSpeed((int)velType.lowVel);
                m_velType = velType.lowVel;
            }
        }


        //Home非阻塞版本，在其中新开了子线程，触发了按钮控制事件，使用lambda函数实现参数传递
        public void Motion_Home_unblock(HOMEPrm[] movePrm)
        {
            if (moveStarted != null)
                moveStarted();
            var t = new Thread(() =>
                {
                    BtnSetSpeed((int)velType.HomeVel);
                    m_motion.Motion_Home(movePrm, 0);
                    //if(!stopHomeFlag)
                    //m_motion.Motion_Home(movePrm, 1);

                    BtnSetSpeed((int)m_velType);
                    if (moveStopped != null)
                        moveStopped();
                });
            t.Start();
        }

        public void Motion_PToPMove_unblock(PTPPrm[] movePrm)
        {
            if (moveStarted != null)
                moveStarted();
            Thread t = new Thread(() =>
                {
                    Console.WriteLine("start ptp move ");
                    m_motion.Motion_PToPMove(movePrm);
                    if(moveStopped != null)
                        moveStopped();
                });
            t.Start();
        }


        public void Motion_StepMove_unblock(STEPPrm[] movePrm)
        {
            if(moveStarted != null)
                moveStarted();
            var t = new Thread(() =>
                {
                    m_motion.Motion_StepMove(movePrm);
                    if(moveStopped != null)
                        moveStopped();
                });
            t.Start();
        }

        private void MotionWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            
            //sw.Flush();
            //sw.Close();
            fs.Close();
        }

        private void button_setPrm_Click(object sender, EventArgs e)
        {
            m_motion.Motion_ExeSetParamApplication();
        }
       

        


       
    }
}
