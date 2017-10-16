/*******************运动模块***********************
 * 1.速度参数  
 *      iMoveType:0(手动）1（自动） 2（自定义）
 *      iHandVelType:0(Low) 1(Mid) 2(High)
 *      只有当选择自定义时，需要给其他四个参数赋值
 * 2.回零参数
 *      homeType：0（限位回零） 1（Home回零） 2（Index回零）
 *      dOrgMove 零点偏移，最多搜索这么长的距离
 *      dHomeOff 回零完成之后的运动偏移
 *      
 * 3.关于壁障
 *      可以将视觉都放置在切割头的左侧，然后限制平台的移动范围，
 *      使得切割头不能进入屏幕左侧区域，防止和压合装置相撞
 *       
 * *************************************************/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Collections;
using System.Threading;
using System.IO;

namespace MotionMod
{
    #region 数据结构

    public enum velType { lowVel=0, midVel = 1, HighVel = 2, HomeVel = 3};
    public enum moveType { handType = 0, autoType = 1, customType = 2};

   
    

    [StructLayout(LayoutKind.Sequential)] 
    public struct SPEEDPrm
    {
        public int iCoorAxis;
        public int iMoveType;
        public int iHandVelType;
        public double dLowVel;
        public double dHighVel;
        public double dAcc;
        public double dDec;

    };


    [StructLayout(LayoutKind.Sequential)]
    public struct PTPPrm
    {
        public int iCoorAxis;
        public double dPos;

 
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct JOGPrm
    {
        public int iCoorAxis;
        public int iDirect;

    };

    [StructLayout(LayoutKind.Sequential)] 
    public struct STEPPrm
    {
	    public int iCoorAxis;
	    public double dStepPos;

    };

    [StructLayout(LayoutKind.Sequential)]
    public struct HOMEPrm
    {
        public int iCoorAxis;
        public int iDirect;
        public double dOrgMove;
        public double dHomeOff;

    };

    //[StructLayout(LayoutKind.Sequential)]
    //public struct ClickAxis
    //{
    //    public int iCoorAxis;
    //    public int iDirect;
    //}
    #endregion
    
    public sealed class MotionControl
    {
        #region DllImport方法
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Init")]
        private static extern int m_Init();


        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Close")]
        private static extern int m_Close();


        //按位输出信号
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_OutputBit")]
        private static extern int m_OutputBit(int bitNO, int iStatus);


        //输出信号
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Output")]
        private static extern int m_Output(int iOutState);


        //获取实时位置
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GetRealTimePos")]
        unsafe private static extern int m_GetRealTimePos(int iAxisNO, ref double dRealTimePos);



        //设置速度及速度模式
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_SetSglSpeed")]
        unsafe private static extern int m_SetSglSpeed(IntPtr p, int iArrayNum);

        //移动到指定位置及运动模式
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_PToPMove")]
        unsafe private static extern int m_PToPMove(IntPtr p, int iArrayNum);

        //步进运动
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_StepMove")]
        unsafe private static extern int m_StepMove(IntPtr p, int iArrayNum);


        //回原点
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Home")]
        unsafe private static extern int m_Home(IntPtr p, int iArrayNum, int iHomeType);


        //停止
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Stop")]
        private static extern int m_Stop();


        //输入信号
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_Input")]
        private static extern int m_Input(int iBitNO);


        //获取轴原点状态
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GetOriginStatusAxis")]
        private static extern bool m_GetOriginStatusAxis(int iAxisNO);


        //获取轴限位状态
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GetLimitStatusAxis")]
        unsafe private static extern bool m_GetLimitStatusAxis(int iAxisNO, ref int iLimitP, ref int iLimitN);



        //获取轴是运动状态
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_IsMoving")]
        unsafe private static extern int m_IsMoving(int* iAxisNO, int iLen);


        //持续运动
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_JogMove")]
        unsafe private static extern int m_JogMove(IntPtr p, int iArrayNum);




        //设轴绝对坐标
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_SetAbsPos")]
        private static extern int m_SetAbsPos(int iAxisNO, double dPos);




        //开激光
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_LaserOn")]
        private static extern int m_LaserOn(int iLaserBit);


        //关激光
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_LaserOff")]
        private static extern int m_LaserOff(int iLaserBit);


        //吹气
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GasOpen")]
        private static extern int m_GasOpen(int iGasBit);


        //关气
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GasClose")]
        private static extern int m_GasClose(int iGasBit);

        //开吸附
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_AbsorptionOpen")]
        private static extern int m_AbsorptionOpen(int iAbsorptionBit);


        //关吸附
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_AbsorptionClose")]
        private static extern int m_AbsorptionClose(int iAbsorptionBit);

        //暂停运动
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_PauseMove")]
        private static extern int m_PauseMove();

        //设置当前卡号
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_SetCardNO")]
        private static extern int m_SetCardNO(short cardNO);


        //获取当前卡号
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_GetCardNO")]
        unsafe private static extern int m_GetCardNO(ref short cardNO);

        //执行设置参数软件
        [DllImport("MotionInterfaceGoogolGTS.dll", EntryPoint = "EC_ExeSetParamApplication")]
        private static extern bool m_ExeSetParamApplication();

        #endregion

        #region 内部变量

        private FileStream fs;
        private StreamWriter sw;



        //test data
        private static double pos1 = 0;
        private static double pos2 = 1000;
        private static double pos3 = 2000;

        private bool isInit = false;
        private volatile static MotionControl _instance = null;
        private static readonly object lockHelper = new object();

        #endregion

        /* test
        #region Test

        private static int m_Init() { return 0; }



        private static int m_Close() { return 0; }


        //按位输出信号

        private static int m_OutputBit(int bitNO, int iStatus) { return 0; }


        //输出信号

        private static int m_Output(int iOutState) { return 0; }


        //获取实时位置

        unsafe private static int m_GetRealTimePos(int iAxisNO, double* dRealTimePos)
        {

            switch (iAxisNO)
            {
                case 0:
                    pos1 += 1;
                    *dRealTimePos = pos1;
                    break;

                case 1:
                    pos2 = pos2 + 1;
                    *dRealTimePos = pos2;
                    break;

                case 2:
                    pos3 = pos3 + 1;
                    *dRealTimePos = pos3;
                    break;

                default:
                    *dRealTimePos = 0;
                    break;
            }


            return 0;
        }



        //设置速度及速度模式

        unsafe private static int m_SetSglSpeed(SPEEDPrm* movePrm, int iArrayNum) { return 0; }

        //移动到指定位置及运动模式

        unsafe private static int m_PToPMove(PTPPrm* movePrm, int iArrayNum)
        {
            doSomeWork();
            return 0;
        }

        //步进运动

        unsafe private static int m_StepMove(STEPPrm* movePrm, int iArrayNum)
        {
            for (int i = 0; i < iArrayNum; i++)
            {
                Console.WriteLine("AxisID:{0}, StepDis:{1}", movePrm[i].iCoorAxis, movePrm[i].dStepPos);
            }

            doSomeWork();
            return 0;
        }




        //回原点

        unsafe private static int m_Home(HOMEPrm* movePrm, int iArrayNum, int iHomeType) { return 0; }


        //停止

        private static int m_Stop()
        {
            Console.WriteLine("Stop moving");
            return 0;
        }


        //输入信号

        private static int m_Input(int iBitNO) { return 0; }


        //获取轴原点状态

        private static bool m_GetOriginStatusAxis(int iAxisNO) { return true; }


        //获取轴限位状态

        unsafe private static bool m_GetLimitStatusAxis(int iAxisNO, int* iLimitP, int* iLimitN) { return true; }



        //获取轴是运动状态

        unsafe private static int m_IsMoving(int* iAxisNO, int iLen) { return 0; }


        //持续运动

        unsafe private static int m_JogMove(JOGPrm* movePrm, int iArrayNum)
        {
            for (int i = 0; i < iArrayNum; i++)
            {
                Console.WriteLine("AxisID:{0}, Direct:{1}", movePrm[i].iCoorAxis, movePrm[i].iDirect);
            }
            Console.WriteLine("Start move!");

            return 0;
        }




        //设轴绝对坐标

        private static int m_SetAbsPos(int iAxisNO, double dPos) { return 0; }




        //开激光

        private static int m_LaserOn(int iLaserBit) { return 0; }


        //关激光
        private static int m_LaserOff(int iLaserBit) { return 0; }


        //吹气
        private static int m_GasOpen(int iGasBit) { return 0; }


        //关气
        private static int m_GasClose(int iGasBit) { return 0; }

        //开吸附
        private static int m_AbsorptionOpen(int iAbsorptionBit) { return 0; }


        //关吸附
        private static int m_AbsorptionClose(int iAbsorptionBit) { return 0; }

        //暂停运动
        private static int m_PauseMove() { return 0; }

        //设置当前卡号
        private static int m_SetCardNO(short cardNO) { return 0; }


        //获取当前卡号
        unsafe private static int m_GetCardNO(short* cardNO) { return 0; }

        //执行设置参数软件
        private static bool m_ExeSetParamApplication() { return true; }

        private static void doSomeWork()
        {
            Console.WriteLine("StartWork!");
            Thread.Sleep(5000);
            Console.WriteLine("Work Stopped!");

        }

        #endregion
        */

        #region 轴控制函数的C#封装
        //C#封装，主要是去掉了指针的使用，不再向上层返回int值，而是转换为BOOL值
        public bool Motion_Init()
        {
            int ret = m_Init();
            sw.WriteLine("初始化结果:{0}", ret);
            sw.Flush();

            if (ret != 0)
                return false;
            else
                return true;
        }
	    public bool Motion_Close()
        {
            if(m_Close() < 0)
                return false;

            return true;
        }
        public bool Motion_OutputBit(int bitNO, int iStatus)
        {
            int ret = m_OutputBit(bitNO, iStatus);
            Console.WriteLine(ret);
            if (ret < 0)
                return false;

            return true;
        }

        public bool Motion_Output(int iOutState)
        {
            if (m_Output(iOutState) < 0)
                return false;

            return true;
        }
        unsafe public bool Motion_GetRealTimePosAxis(int iAxisNO, out double dRealTimePos)
        {
            double t_dRealTimePos=0;
            int ret = m_GetRealTimePos(iAxisNO, ref t_dRealTimePos);
            
            if(ret == 0)
            {
                dRealTimePos = t_dRealTimePos;
                return true;
            }
            else
            {
                dRealTimePos = 0;
                return false;
            }


        }


        //比较复杂的一个转换，因为C#中存在GC机制，如果不做特殊处理，对象的地址会被gc更改，导致指针失效
        unsafe public bool Motion_SetSglSpeed(SPEEDPrm[] movePrm)
        {
            
            int ilen = movePrm.Length;

            //使用Marshal手动分配内存，不托管给gc
            int size = Marshal.SizeOf(typeof(SPEEDPrm)) * ilen;
            byte[] bytes = new byte[size]; //我也不记得这一句是做什么的了，也许可以删除...
            IntPtr pBuff = Marshal.AllocHGlobal(size);
            long ptr = pBuff.ToInt64();

            //将数组的数据逐个复制进去
            for(int i = 0; i<ilen; i++)
            {
                IntPtr RPtr = new IntPtr(ptr);
                Marshal.StructureToPtr(movePrm[i], RPtr, false);
                ptr += Marshal.SizeOf(typeof(SPEEDPrm));
            }

            int ret = m_SetSglSpeed(pBuff, ilen);

            //务必记得手动释放，否则会内存泄漏
            Marshal.FreeHGlobal(pBuff);
            sw.WriteLine("setSpeed:{0}", ret);
            sw.Flush();


            if (ret != 0)
                return false;
            else
                return true;

        }

        unsafe public bool Motion_PToPMove(PTPPrm[] movePrm)
        {
            int ilen = movePrm.Length;

            int size = Marshal.SizeOf(typeof(PTPPrm)) * ilen;
            byte[] bytes = new byte[size];
            IntPtr pBuff = Marshal.AllocHGlobal(size);
            long ptr = pBuff.ToInt64();

            for (int i = 0; i < ilen; i++)
            {
                IntPtr RPtr = new IntPtr(ptr);
                Marshal.StructureToPtr(movePrm[i], RPtr, false);
                ptr += Marshal.SizeOf(typeof(PTPPrm));
            }

            int ret = m_PToPMove(pBuff, ilen);

            Marshal.FreeHGlobal(pBuff);
            Console.WriteLine("PTPMove:{0}", ret);
       


            if (ret != 0)
                return false;
            else
                return true;
        }



        unsafe public bool Motion_StepMove(STEPPrm[] movePrm)
        {
            int ilen = movePrm.Length;

            int size = Marshal.SizeOf(typeof(STEPPrm)) * ilen;
            byte[] bytes = new byte[size];
            IntPtr pBuff = Marshal.AllocHGlobal(size);
            long ptr = pBuff.ToInt64();

            for (int i = 0; i < ilen; i++)
            {
                IntPtr RPtr = new IntPtr(ptr);
                Marshal.StructureToPtr(movePrm[i], RPtr, false);
                ptr += Marshal.SizeOf(typeof(STEPPrm));
            }
            
            int ret = m_StepMove(pBuff, ilen);

            Marshal.FreeHGlobal(pBuff);
            sw.WriteLine("setpMove:{0}", ret);
            sw.Flush();


            if (ret != 0)
                return false;
            else
                return true;
        }


        unsafe public bool Motion_Home(HOMEPrm[] movePrm, int iHomeType)
        {
            int ilen = movePrm.Length;

            int size = Marshal.SizeOf(typeof(HOMEPrm)) * ilen;
            byte[] bytes = new byte[size];
            IntPtr pBuff = Marshal.AllocHGlobal(size);
            long ptr = pBuff.ToInt64();

            for (int i = 0; i < ilen; i++)
            {
                IntPtr RPtr = new IntPtr(ptr);
                Marshal.StructureToPtr(movePrm[i], RPtr, false);
                ptr += Marshal.SizeOf(typeof(HOMEPrm));
            }

            int ret = m_Home(pBuff, ilen, iHomeType);

            Marshal.FreeHGlobal(pBuff);
            sw.WriteLine("HOMEPrm:{0}", ret);
            sw.Flush();


            if (ret != 0)
                return false;
            else
                return true;
        }


        public bool Motion_Stop()
        {
            if (m_Stop() < 0)
                return false;

            return true;
        }
        public bool Motion_Input(int iBitNO)
        {
            if (m_Input(iBitNO) < 0)
                return false;

            return true;
        }

        public bool Motion_GetOriginStatusAxis(int iAxisNO)
        {
            return m_GetOriginStatusAxis(iAxisNO);

        }

        unsafe public bool Motion_GetLimitStatusAxis(int iAxisNO, out int limitP, out int limitN)
        {
            limitP = limitN = 0;
            bool ret = m_GetLimitStatusAxis(iAxisNO, ref limitP, ref limitN);


            return ret;
        }

        unsafe public bool Motion_IsMoving(int[] iAxisNo)
        {
            int iLen = iAxisNo.Length;

            if (iLen <= 0)
                return false;

            int ret;

            fixed (int* pAxisArray = &iAxisNo[0])
            {
                ret = m_IsMoving(pAxisArray, iLen);
            }

            if (ret < 0)
                return false;

            return true;
        }

        unsafe public bool Motion_JogMove(JOGPrm[] movePrm)
        {
            int ilen = movePrm.Length;

            int size = Marshal.SizeOf(typeof(JOGPrm)) * ilen;
            byte[] bytes = new byte[size];
            IntPtr pBuff = Marshal.AllocHGlobal(size);
            long ptr = pBuff.ToInt64();

            for (int i = 0; i < ilen; i++)
            {
                IntPtr RPtr = new IntPtr(ptr);
                Marshal.StructureToPtr(movePrm[i], RPtr, false);
                ptr += Marshal.SizeOf(typeof(JOGPrm));
            }

            int ret = m_JogMove(pBuff, ilen);

            Marshal.FreeHGlobal(pBuff);
            sw.WriteLine("JOGPrm:{0}", ret);
            sw.Flush();


            if (ret != 0)
                return false;
            else
                return true;

        }


        /*
        unsafe public bool Motion_SetJogSpeed(List<SPEEDPrm> ptopSpeedSet, SpeedType setSpeedType)
        {
            int iLen = ptopSpeedSet.Count;

            int[] iAxisNO = new int[iLen];
            double[] dHighSpeed = new double[iLen];
            double[] dLowSpeed = new double[iLen];
            double[] dAcc = new double[iLen];
            double[] dDec = new double[iLen];

            for (int i = 0; i < iLen; i++)
            {
                SPEEDPrm pSpeedSet = ptopSpeedSet[i];
                iAxisNO[i] = pSpeedSet.iAxisNO;
                dHighSpeed[i] = pSpeedSet.dHighSpeed;
                dLowSpeed[i] = pSpeedSet.dLowSpeed;
                dAcc[i] = pSpeedSet.dAcc;
                dDec[i] = pSpeedSet.dDec;
            }

            int ret;

            int sType;


            switch (setSpeedType)
            {
                case SpeedType.MinSpeed: sType = 0;
                    break;
                case SpeedType.MiddleSpeed: sType = 1;
                    break;
                case SpeedType.MaxSpeed: sType = 2;
                    break;
                case SpeedType.HomeSpeed: sType = 3;
                    break;
                case SpeedType.CustomSpeed: sType = 4;
                    break;
                default: sType = 0;
                    break;
            }

            fixed(int *piAxisNO = &iAxisNO[0])
            {
                fixed(double *pdHighSpeed = &dHighSpeed[0], pdLowSpeed = &dLowSpeed[0], 
                pdAcc = &dAcc[0], pdDec = &dDec[0])
                {
                    ret = m_SetJogSpeed(sType, piAxisNO,iLen,pdHighSpeed,pdLowSpeed,pdAcc,pdDec);
                }
            }

            if(ret < 0)
                return false;
            else 
                return true;
        }

        unsafe public bool Motion_SetStepSpeed(List<SPEEDPrm> ptopSpeedSet, SpeedType setSpeedType)
        {
            int iLen = ptopSpeedSet.Count;

            int[] iAxisNO = new int[iLen];
            double[] dHighSpeed = new double[iLen];
            double[] dLowSpeed = new double[iLen];
            double[] dAcc = new double[iLen];
            double[] dDec = new double[iLen];

            for (int i = 0; i < iLen; i++)
            {
                SPEEDPrm pSpeedSet = ptopSpeedSet[i];
                iAxisNO[i] = pSpeedSet.iAxisNO;
                dHighSpeed[i] = pSpeedSet.dHighSpeed;
                dLowSpeed[i] = pSpeedSet.dLowSpeed;
                dAcc[i] = pSpeedSet.dAcc;
                dDec[i] = pSpeedSet.dDec;
            }

            int ret;

            int sType;


            switch (setSpeedType)
            {
                case SpeedType.MinSpeed: sType = 0;
                    break;
                case SpeedType.MiddleSpeed: sType = 1;
                    break;
                case SpeedType.MaxSpeed: sType = 2;
                    break;
                case SpeedType.HomeSpeed: sType = 3;
                    break;
                case SpeedType.CustomSpeed: sType = 4;
                    break;
                default: sType = 0;
                    break;
            }

            fixed(int *piAxisNO = &iAxisNO[0])
            {
                fixed(double *pdHighSpeed = &dHighSpeed[0], pdLowSpeed = &dLowSpeed[0], 
                pdAcc = &dAcc[0], pdDec = &dDec[0])
                {
                    ret = m_SetStepSpeed(sType, piAxisNO,iLen,pdHighSpeed,pdLowSpeed,pdAcc,pdDec);
                }
            }

            if(ret < 0)
                return false;
            else 
                return true;
        }
         * 
         */

        public bool Motion_SetAbsPos(int iAxisNO, double dPos)
        {
            if (m_SetAbsPos(iAxisNO, dPos) < 0)
                return false;

            return true;
        }

        public bool Motion_LaserOn(int iLaserBit)
        {
            if (m_LaserOn(iLaserBit) < 0)
                return false;

            return true;
        }

        public bool Motion_LaserOff(int iLaserBit)
        {
            if (m_LaserOff(iLaserBit) < 0)
                return false;

            return true;
        }

        public bool Motion_GasOpen(int iGasBit)
        {
            if (m_GasOpen(iGasBit) < 0)
                return false;

            return true;
        }

        public bool Motion_GasClose(int iGasBit)
        {
            if (m_GasClose(iGasBit) < 0)
                return false;

            return true;
        }

        public bool Motion_AbsorptionOpen(int iAbsorptionBit)
        {
            if (m_AbsorptionOpen(iAbsorptionBit) < 0)
                return false;

            return true;
        }

        public bool Motion_AbsorptionClose(int iAbsorptionBit)
        {
            if (m_AbsorptionClose(iAbsorptionBit) < 0)
                return false;

            return true;
        }

        //可以将各个引脚的选择添加为运动参数，可以修改和读取。也可以固定写死。
        public bool Motion_locate(bool flag)
        {
            return Motion_OutputBit(1, 1);
        }

        public bool Motion_absorb(bool flag)
        {
            return Motion_OutputBit(2, 1);
        }

        public bool Motion_push(bool flag)
        {
            return Motion_OutputBit(3, 1);
        }

        public bool Motion_fixture_push()
        {
            if (!Motion_locate(true))
                return false;
            Thread.Sleep(100);
            if (!Motion_absorb(true))
                return false;
            Thread.Sleep(100);
            if (!Motion_push(true))
                return false;
            Thread.Sleep(500);

            return true;

        }

        public void Motion_fixture_relax()
        {
            Motion_push(false);
            Motion_absorb(false);
            Motion_locate(false);
            Thread.Sleep(500);
        }

        public bool Motion_PauseMove()
        {
            int ret = m_PauseMove();

            if (ret < 0)
                return false;
            else
                return true;
        }

        public bool Motion_SetCardNO(short cardNO)
        {

            int ret = m_SetCardNO(cardNO);

            if (ret < 0)
                return false;
            else
                return true;
        }

        unsafe public bool Motion_GetCardNO(out short cardNO)
        {
            cardNO = 0;
            int ret = m_GetCardNO(ref cardNO);
    

            if (ret < 0)
                return false;
            else
                return true;
        }


        public bool Motion_ExeSetParamApplication()
        {
            return m_ExeSetParamApplication();
        }

        #endregion

        #region 单例模式实现
        public static MotionControl CreateMotion()
        {
            if(_instance == null)
            {
                lock(lockHelper)
                {
                    if (_instance == null)
                    {
                        _instance = new MotionControl();
                        
                    }
                    
                }
            }

            return _instance;
            
        }
        private MotionControl()
        {
            fs = new FileStream("log2.txt", FileMode.Create);
            sw = new StreamWriter(fs);


            isInit = Motion_Init();


        }

        public bool  IsInit
        {
            get
            {
                return isInit;
            }
        }
        ~MotionControl()
        {
            //如果不注释，会在关闭时出现objectDisposedException
            //无法访问被释放的对象
            //sw.Flush();
            //sw.Close();
            fs.Close();

            Motion_Close();
        }

        #endregion
    }
}
