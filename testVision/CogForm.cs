/*****************************************************
 * 1.对外部程序而言，Job1_Run()函数的调用是阻塞的
 * 2.内部实现：在调用run后，VisionPro会开启子线程执行计算，这里使用信号量进行同步；计算完成后，用getLocalResult函数获取结果并返回
 * 3.Run函数绝对不能在GUI所在的主线程里调用，否则会死锁！请务必和文中按钮操作一样，新开子线程进行调用
 * 4.在有Job在执行时，会将按钮置灰，计算完成后恢复使能
 * 5.加入pattern参数，用于决定获取结果的内容：0-blobTool结果 1-PMATool结果 2-blob轮廓 ；默认值为0. 
 * **************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Collections;
using System.Threading;
using System.Runtime.InteropServices;


using Cognex.VisionPro;
using Cognex.VisionPro.QuickBuild;
using Cognex.VisionPro.ToolGroup;
using Cognex.VisionPro.PMAlign;
using Cognex.VisionPro.Blob;
using Cognex.VisionPro.Display;
//using Cognex.VisionPro.ImageFile;
using Cognex.VisionPro.CalibFix;
using Cognex.VisionPro.Internal;
//using Cognex.VisionPro.DSCameraSetup;

namespace VisionMod
{
  
    public partial class CogForm : Form
    {
        

        #region 变量定义

        private const int MAX_ITEM = 100;
        private const int MAX_POINT = 9999;
        private const int Group_Number = 2;
        private string m_strVppFileName = "CogTest02.vpp";

        //private const string m_strLogFileName = "log.txt";
        //private StreamWriter logfile = null;




        private CogJobManager m_JobManager = null;
        // Job
        private CogJob m_Job_1 = null;
        private CogJob m_Job_2 = null;
        private CogJob m_Job_3 = null;



        //CogToolGroup toolGroup_1 = null;
        CogBlobTool blobTool_1 = null;
        CogBlobTool blobTool_2 = null;
        CogBlobTool blobTool_3 = null;

        public CogCalibNPointToNPointTool calibTool_1 = null;
        public CogCalibNPointToNPointTool calibTool_2 = null;
        public CogCalibNPointToNPointTool calibTool_3 = null;



        CogAcqFifoTool acqFifoTool_1 = null;
        CogAcqFifoTool acqFifoTool_2 = null;
        CogAcqFifoTool acqFifoTool_3 = null;

        ICogAcqFifo mAcqFifo_1 = null;
        ICogAcqFifo mAcqFifo_2 = null;
        ICogAcqFifo mAcqFifo_3 = null;

        CogPMAlignTool pmaTool_1 = null;
        CogPMAlignTool pmaTool_2 = null;
        CogPMAlignTool pmaTool_3 = null;

        // Delegate whose signature matches CJM events.
        delegate void myJobDelegate(Object Sender,
          CogJobActionEventArgs e);

        //public delegate void Job_1_RanEventHandler(double[] item_x, double[] item_y, int count);
        //public event Job_1_RanEventHandler Job_1_Ran;

        static AutoResetEvent mEvent_1 = new AutoResetEvent(false);
        static Semaphore sem_1 = new Semaphore(0, 1);
        static Semaphore sem_2 = new Semaphore(0, 1);
        static Semaphore sem_3 = new Semaphore(0, 1);

        #endregion

      
        #region 结果获取
        //toolNum和Pattern两个参数决定结果的来源
        //Blob工具的结果获取函数
        private bool getBlobToolResult(out double[] item_x, out double[] item_y, out int item_number, int toolNum)
        {
            CogBlobTool blobTool = null;

            item_x = null;
            item_y = null;
            item_number = 0;

            switch (toolNum)
            {
                case 1:
                    blobTool = blobTool_1;
                    break;
                case 2:
                    blobTool = blobTool_2;
                    break;
                case 3:
                    blobTool = blobTool_3;
                    break;
                default:
                    return false;
            }
            if(blobTool.Results == null)
            {
                return false;
            }

            CogBlobResultCollection blobResult = blobTool.Results.GetBlobs();
            if(blobResult==null)
            {
                return false;
            }
            item_number = blobResult.Count;

            if (item_number <= 0)
            {
                item_x = new double[0];
                item_y = new double[0];
                return false;
            }


            item_x = new double[item_number];
            item_y = new double[item_number];




            for (int i = 0; i < item_number; i++)
            {
                item_x[i] = blobResult[i].CenterOfMassX;
                item_y[i] = blobResult[i].CenterOfMassY;
            }

            return true;
        }

        private bool getBlobBoundary(out double[] pos_x, out double[] pos_y, out int pos_number, int toolNum, int index)
        {
            CogBlobTool blobTool = null;
            pos_x = null;
            pos_y = null;
            pos_number = 0;

            switch (toolNum)
            {
                case 1:
                    blobTool = blobTool_1;
                    break;
                case 2:
                    blobTool = blobTool_2;
                    break;
                case 3:
                    blobTool = blobTool_3;
                    break;
                default:
                    return false;
            }

            if(blobTool.Results == null)
            {
                return false;
            }

            CogBlobResultCollection blobResult = blobTool.Results.GetBlobs();

            if(blobResult==null)
            {
                return false;
            }
            int number = blobResult.Count;
            if (index >= number || index < 0)
                return false;

            CogPolygon blobBoundary = blobResult[index].GetBoundary();


            int verticesNum = blobBoundary.NumVertices;
            pos_x = new double[verticesNum];
            pos_y = new double[verticesNum];

            for(int i=0; i< verticesNum; i++)
            {
                pos_x[i] = blobBoundary.GetVertexX(i);
                pos_y[i] = blobBoundary.GetVertexY(i);
            }

            pos_number = verticesNum;

            return true;
            




        }

        //模板匹配工具的结果获取函数
        private bool getPMAToolResult(out double[] item_x, out double[] item_y, out int item_number, int toolNum)
        {
            CogPMAlignTool PMATool = null;

            switch (toolNum)
            {
                case 1:
                    PMATool = pmaTool_1;
                    break;
                case 2:
                    PMATool = pmaTool_2;
                    break;
                case 3:
                    PMATool = pmaTool_3;
                    break;

                default:
                    item_x = new double[0];
                    item_y = new double[0];
                    item_number = 0;
                    return false;
                    break;
            }

            item_number = PMATool.Results.Count;

            if (item_number <= 0)
            {
                item_x = new double[0];
                item_y = new double[0];
                return false;
            }


            item_x = new double[item_number];
            item_y = new double[item_number];




            for (int i = 0; i < item_number; i++)
            {
                item_x[i] = PMATool.Results[i].GetPose().TranslationX;
                item_y[i] = PMATool.Results[i].GetPose().TranslationY;
            }

            return true;
        }

        private bool getReault(out double[] item_x, out double[] item_y, out int item_number, int toolNum, int pattern)
        {
            switch (pattern)
            {
                case 0:
                    return getBlobToolResult(out item_x, out item_y, out item_number, toolNum);

                case 1:
                    return getPMAToolResult(out item_x, out item_y, out item_number, toolNum);

                case 2:
                    return getBlobBoundary(out item_x, out item_y, out item_number, toolNum, 0);
                default:
                    return getBlobToolResult(out item_x, out item_y, out item_number, toolNum);
            }
        }
        private bool GetLocateResult1(out double[] item_x, out double[] item_y, out int item_number, int pattern)
        {
            return getReault(out item_x, out item_y, out item_number, 1, pattern);
        }

        private bool GetLocateResult2(out double[] item_x, out double[] item_y, out int item_number, int pattern)
        {
            return getReault(out item_x, out item_y, out item_number, 2, pattern);

        }

        //暂时只抓取一个斑点的轮廓
        private bool GetLocateResult3(out double[] item_x, out double[] item_y, out int item_number, int pattern)
        {
            return getReault(out item_x, out item_y, out item_number, 3, pattern);

           
        }

        #endregion

        #region Run函数&事件
        private void myJob1_Stopped(object sender, CogJobActionEventArgs e)
        {
       
            if (InvokeRequired)
            {
    
                sem_1.Release();
                Invoke(new myJobDelegate(myJob1_Stopped),
                    new object[] { sender, e });
                return;
            }


            groupBox_visionCtrl.Enabled = true;


        }

        //Job2完成事件处理函数，在底层Run()所在的线程里release信号量，再切换到GUI线程enable按钮群
        //也完全可以将两部分的处理分开写，将enable操作写成一个委托，用Invoke调用即可
        //注意：事件处理所在的线程是由VisionPro开启的子线程，不可能在GUI线程里，所以第一次进入时，InvokeRequired必定为true
        private void myJob2_Stopped(object sender, CogJobActionEventArgs e)
        {
            if (InvokeRequired)
            {

                sem_2.Release();
                Invoke(new myJobDelegate(myJob1_Stopped),
                    new object[] { sender, e });
                return;
            }


            groupBox_visionCtrl.Enabled = true;
        }

        private void myJob3_Stopped(object sender, CogJobActionEventArgs e)
        {
            if (InvokeRequired)
            {

                sem_3.Release();
                Invoke(new myJobDelegate(myJob1_Stopped),
                    new object[] { sender, e });
                return;
            }


            groupBox_visionCtrl.Enabled = true;
        }

        //Run函数不能在GUI线程里运行，否则会发生死锁
        public bool Job1_Run(out double[] arrayX, out double[] arrayY, out int number, int pattern = 0)
        {
            m_Job_1.Run();
            sem_1.WaitOne();
            return GetLocateResult1(out arrayX, out arrayY, out number, pattern);
        }

        public bool Job2_Run(out double[] arrayX, out double[] arrayY, out int number, int pattern = 0)
        {
            m_Job_2.Run();
            sem_2.WaitOne();
            return GetLocateResult2(out arrayX, out arrayY, out number, pattern);
        }

        public bool Job3_Run(out double[] arrayX, out double[] arrayY, out int number, int pattern = 0)
        {
            m_Job_3.Run();
            sem_3.WaitOne();
            return GetLocateResult3(out arrayX, out arrayY, out number, pattern);
        }

        #endregion


        #region 窗体操作

        public CogForm()
        {
            InitializeComponent();



        }


        //初始化函数1
        private void InitialVPP()
        {
            string path = System.Environment.CurrentDirectory;
            m_strVppFileName = path + "//" + m_strVppFileName;

            Console.WriteLine(m_strVppFileName);

            // 加载Vpp
            if (!System.IO.File.Exists(m_strVppFileName))
            {
                MessageBox.Show("Vpp Job文件不存在\n退出软件?", "警告");
                this.Close();

                return;
            }



            m_JobManager = (CogJobManager)CogSerializer.LoadObjectFromFile(m_strVppFileName);
            if (m_JobManager == null)
            {
                MessageBox.Show("NULL错误", "警告");
                this.Close();
            }
            int nCount = m_JobManager.JobCount;


            if (nCount < 3)
            {
                MessageBox.Show("Wrong CCD Model:Job count less than 3.");
                this.Close();
            }

            m_Job_1 = m_JobManager.Job(0);
            m_Job_2 = m_JobManager.Job(1);
            m_Job_3 = m_JobManager.Job(2);




            // 注册Job完成事件
            m_Job_1.Stopped += new CogJob.CogJobStoppedEventHandler(myJob1_Stopped);
            m_Job_2.Stopped += new CogJob.CogJobStoppedEventHandler(myJob2_Stopped);
            m_Job_3.Stopped += new CogJob.CogJobStoppedEventHandler(myJob3_Stopped);


            //Job_1_Ran += new Job_1_RanEventHandler(testJob_1);


            // 刷新队列
            m_JobManager.UserQueueFlush();
            m_JobManager.FailureQueueFlush();

        }

        //private void initLog()
        //{
        //    string path = System.Environment.CurrentDirectory;
        //    m_strVppFileName = path + "//" + m_strVppFileName;
        //    logfile = new StreamWriter(m_strLogFileName);


        //}

        //private void closeLog()
        //{
        //    logfile.Close();
        //}

        //初始化函数2
        private void initToolEdit()
        {

            //JobManagerEdit.Subject = m_JobManager;

            //一级视觉
            CogToolGroup m_ToolGroup_1 = (CogToolGroup)m_Job_1.VisionTool;
            cogToolGroupEditV21.Subject = m_ToolGroup_1;

            

            if (m_ToolGroup_1 == null)
            {
                MessageBox.Show("toolgroup1工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

      
            blobTool_1 = (CogBlobTool)m_ToolGroup_1.Tools["CogBlobTool1"];
            if (blobTool_1 == null)
            {
                MessageBox.Show("blob1工具读取失败,请退出软件");
            }




            pmaTool_1 = (CogPMAlignTool)m_ToolGroup_1.Tools["caliPMATool"];
            if (pmaTool_1 == null)
            {
                MessageBox.Show("pma1工具读取失败,请退出软件");

            }

            calibTool_1 = (CogCalibNPointToNPointTool)m_ToolGroup_1.Tools["CogCalibNPointToNPointTool1"];
            if(calibTool_1 == null)
            {
                MessageBox.Show("calib1工具读取失败，请退出软件");

            }

            acqFifoTool_1 = (CogAcqFifoTool)m_ToolGroup_1.Tools["CogAcqFifoTool1"];
            if (acqFifoTool_1 == null)
            {
                MessageBox.Show("acqfifo1工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

            mAcqFifo_1 = acqFifoTool_1.Operator;

            if (mAcqFifo_1 == null)
            {
                MessageBox.Show("macqfifo1为 null，窗口将自动关闭");
                this.Close();
                return;
            }


            mAcqFifo_1.Timeout = 1000;








            //二级视觉
            CogToolGroup m_ToolGroup_2 = (CogToolGroup)m_Job_2.VisionTool;
            cogToolGroupEditV22.Subject = m_ToolGroup_2;


            if (m_ToolGroup_2 == null)
            {
                MessageBox.Show("toolgroup2工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

            blobTool_2 = (CogBlobTool)m_ToolGroup_2.Tools["CogBlobTool1"];
            if (blobTool_2 == null)
            {
                MessageBox.Show("blob2工具读取失败，请退出软件");
            }

            pmaTool_2 = (CogPMAlignTool)m_ToolGroup_2.Tools["caliPMATool"];
            if (pmaTool_2 == null)
            {
                MessageBox.Show("pma2工具读取失败，请退出软件");
            }

            calibTool_2 = (CogCalibNPointToNPointTool)m_ToolGroup_2.Tools["CogCalibNPointToNPointTool1"];
            if (calibTool_2 == null)
            {
                MessageBox.Show("calib2工具读取失败，请退出软件");
            }


            acqFifoTool_2 = (CogAcqFifoTool)m_ToolGroup_2.Tools["CogAcqFifoTool1"];
            if (acqFifoTool_2 == null)
            {
                MessageBox.Show("acqfifo2工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

            mAcqFifo_2 = acqFifoTool_2.Operator;

            if (mAcqFifo_2 == null)
            {
                MessageBox.Show("macqfifo2为 null，窗口将自动关闭");
                this.Close();
                return;
            }



            mAcqFifo_2.Timeout = 1000;

            ////对比度Test
            //ICogAcqContrast mContrast = mAcqFifo_2.OwnedContrastParams;
            //double val = mContrast.Contrast;
            //Console.WriteLine(val);





            //三级视觉
            CogToolGroup m_ToolGroup_3 = (CogToolGroup)m_Job_3.VisionTool;
            cogToolGroupEditV23.Subject = m_ToolGroup_3;


            if (m_ToolGroup_3 == null)
            {
                MessageBox.Show("toolgroup3工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

            blobTool_3 = (CogBlobTool)m_ToolGroup_3.Tools["CogBlobTool1"];
            if (blobTool_3 == null)
            {
                MessageBox.Show("blob3工具读取失败,请退出软件");
            }
            pmaTool_3 = (CogPMAlignTool)m_ToolGroup_3.Tools["caliPMATool"];
            if (pmaTool_3 == null)
            {
                MessageBox.Show("pma3工具读取失败，请退出软件");

            }

            calibTool_3 = (CogCalibNPointToNPointTool)m_ToolGroup_3.Tools["CogCalibNPointToNPointTool1"];
            if (calibTool_3 == null)
            {
                MessageBox.Show("calib3工具读取失败，请退出软件");

            }


            acqFifoTool_3 = (CogAcqFifoTool)m_ToolGroup_3.Tools["CogAcqFifoTool1"];
            if (acqFifoTool_3 == null)
            {
                MessageBox.Show("acqfifo3工具读取失败，窗口将自动关闭");
                this.Close();
                return;
            }

            mAcqFifo_3 = acqFifoTool_3.Operator;

            if (mAcqFifo_3 == null)
            {
                MessageBox.Show("macqfifo3为 null，窗口将自动关闭");
                this.Close();
                return;
            }



            mAcqFifo_3.Timeout = 1000;





           

        }

        private void initTest()
        {

        }
        private void CogForm_Load(object sender, EventArgs e)
        {
            InitialVPP();

            initToolEdit();
        }

        private void CogForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_JobManager != null)
                m_JobManager.Shutdown();
            cogDisplay1.Dispose();
            CogFrameGrabbers grabbers = new CogFrameGrabbers();
            foreach (ICogFrameGrabber fg in grabbers)
                fg.Disconnect(false);



        }
        private void testWork1()
        {
            double[] test_x;
            double[] test_y;
            int number;
            Job1_Run(out test_x, out test_y, out number);
        }
        private void testWork2()
        {
            double[] test_x;
            double[] test_y;
            int number;
            Job2_Run(out test_x, out test_y, out number);
        }
        private void testWork3()
        {
            double[] test_x;
            double[] test_y;
            int number;
            Job3_Run(out test_x, out test_y, out number);
        }

        private void runJob_1_Btn_Click(object sender, EventArgs e)
        {
            groupBox_visionCtrl.Enabled = false;

            Thread runThd = new Thread(testWork1);
            runThd.IsBackground = true;
            runThd.Start();
        }

        private void runJob_2_Btn_Click(object sender, EventArgs e)
        {

            groupBox_visionCtrl.Enabled = false;

            Thread runThd = new Thread(testWork2);
            runThd.IsBackground = true;
            runThd.Start();

        }

        private void runJob_3_Btn_Click(object sender, EventArgs e)
        {
            groupBox_visionCtrl.Enabled = false;

            Thread runThd = new Thread(testWork3);
            runThd.IsBackground = true;
            runThd.Start();
        }

        private void button_camera_1_Click(object sender, EventArgs e)
        {
            if (cogDisplay1.LiveDisplayRunning)
            {
                cogDisplay1.StopLiveDisplay();
            }
          

            cogDisplay1.StartLiveDisplay(acqFifoTool_1.Operator);

            label_display.Text = "Display:Camera1";
        }

        private void button_camera_2_Click(object sender, EventArgs e)
        {
            if (cogDisplay1.LiveDisplayRunning)
            {
                cogDisplay1.StopLiveDisplay();
            }

            cogDisplay1.StartLiveDisplay(acqFifoTool_2.Operator);
            label_display.Text = "Display:Camera2";

        }

        private void button_camera_3_Click(object sender, EventArgs e)
        {
            if (cogDisplay1.LiveDisplayRunning)
            {
                cogDisplay1.StopLiveDisplay();
            }

            cogDisplay1.StartLiveDisplay(acqFifoTool_3.Operator);
            label_display.Text = "Display:Camera3";
        }

        private void button_camera_stop_Click(object sender, EventArgs e)
        {
            if (cogDisplay1.LiveDisplayRunning)
            {
                cogDisplay1.StopLiveDisplay();
            }

            label_display.Text = "Display:None";

        }

        #endregion

        private void button1_Click(object sender, EventArgs e)
        {
            CogSerializer.SaveObjectToFile(m_JobManager, "test.vpp");
        }




    }
}
