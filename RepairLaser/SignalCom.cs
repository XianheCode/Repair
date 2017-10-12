using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;
using System.Threading;

namespace Com
{
    public class SignalCom
    {
        private SerialPort com = new SerialPort();
        private bool bOnline = false;
        public string mLastError = "nothing";

        public int COM = 1;
        public int BaudRate = 9600;

        public int RevTime = 0;

        public string LastError
        {
            get
            {
                return mLastError;
            }
        }

        public bool isOpen()
        {
            return com.IsOpen;
        }

        public bool isOnline()
        {
            return bOnline;
        }

        //打开串口
        public bool Open()
        {
            try
            {
                Close();
                com.PortName = "COM" + COM;
                com.BaudRate = BaudRate;
                com.DataBits = 8;
                com.StopBits = StopBits.One;
                com.Parity = Parity.None;
                com.ReadTimeout = 5000;
                com.Open();
                return true;
            }
            catch (Exception er)
            {
                mLastError = er.Message;
                return false;
            }
        }

        //关闭串口
        public void Close()
        {
            if (com.IsOpen)
            {
                com.Close();
            }
        }

        //接收信号发生器返回的data，注意当延迟时间太短时会接受不到完整的数据
        //对接受到的数据进行分析，判断操作是否成功
        public bool RecvData()
        {
            char[] bchRec = new char[255];
            int iRecvNum = 0;
            try
            {
                iRecvNum = com.Read(bchRec, 0, 255);
            }
            catch (Exception er)
            {
                mLastError = er.Message;
                return false;
            }
            if (iRecvNum < 8)
            {
                string buffer = new string(bchRec);
                mLastError = buffer;
                return false;
            }

            bool rvsts = bchRec[6] == 'O' && bchRec[7] == 'K';

            if (rvsts)
            {
                return true;
            }
            else
            {
              
                string buffer = new string(bchRec);
                mLastError = buffer;
                return false;
            }
    
        }

        //开启信号发生器，在开启之后才能进行pattern的选择，注意group的选择不能通过串口进行
        public bool OnLine()
        {
            byte[] byUCommand = new byte[255];

            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'O';
            byUCommand[3] = (byte)'L';
            byUCommand[4] = (byte)'N';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'8';
            byUCommand[7] = (byte)'8';
            byUCommand[8] = (byte)'#';


            //char[] byUCommand = new char[255];

            //byUCommand[0] = (char)'@';
            //byUCommand[1] = (char)'U';
            //byUCommand[2] = (char)'O';
            //byUCommand[3] = (char)'L';
            //byUCommand[4] = (char)'N';
            //byUCommand[5] = ':';
            //byUCommand[6] = '8';
            //byUCommand[7] = '8';
            //byUCommand[8] = '#';

            
            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);

            bOnline =  RecvData();

            return bOnline;
        }

        //关闭
        public bool ShutDown()
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'O';
            byUCommand[3] = (byte)'S';
            byUCommand[4] = (byte)'D';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'8';
            byUCommand[7] = (byte)'B';
            byUCommand[8] = (byte)'#';

            
            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);
            return RecvData();
        }

        //开信号
        public bool SignalOn()
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'S';
            byUCommand[3] = (byte)'O';
            byUCommand[4] = (byte)'N';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'8';
            byUCommand[7] = (byte)'1';
            byUCommand[8] = (byte)'#';

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);

            return RecvData();
        }
        
        //关信号
        public bool SignalOff()
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'S';
            byUCommand[3] = (byte)'O';
            byUCommand[4] = (byte)'F';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'8';
            byUCommand[7] = (byte)'9';
            byUCommand[8] = (byte)'#';

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);

            return RecvData();
        }

        //应用下一个模式
        public bool NextPattern()
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'P';
            byUCommand[3] = (byte)'C';
            byUCommand[4] = (byte)'N';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'9';
            byUCommand[7] = (byte)'0';
            byUCommand[8] = (byte)'#';

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);

            return RecvData();
        }

        //应用上一个模式
        public bool PreviousPattern()
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'P';
            byUCommand[3] = (byte)'C';
            byUCommand[4] = (byte)'P';
            byUCommand[5] = (byte)':';
            byUCommand[6] = (byte)'8';
            byUCommand[7] = (byte)'E';
            byUCommand[8] = (byte)'#';

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            Thread.Sleep(RevTime);
            return RecvData();
        }


        /*
        public bool ChangeModel(char[] pchModelName, int iLen)
        {
            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'R';
            byUCommand[3] = (byte)'C';
            byUCommand[4] = (byte)'M';
            byUCommand[5] = (byte)':';

            int iCount = 0;
            for (int i = 0; i < iLen;i++ )
            {
                byUCommand[6 + i] = (byte)(pchModelName[i]);
                iCount++;
            }
            
            //计算效验码
            int iSum = 0;
            for (int i = 0; i < iCount + 5;i++ )
            {
                iSum += byUCommand[i+1];
            }
            iSum = 0 - iSum;
            byUCommand[iCount + 6] = (byte)((iSum >> 4) & 0xF);
            byUCommand[iCount + 7] = (byte)((iSum) & 0xF);
            byUCommand[iCount + 8] = (byte)'#';

            Console.WriteLine("{0}{1}", (char)byUCommand[iCount + 6], (char)byUCommand[iCount + 7]);

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, 9);

            return RecvData();
         
        }

        public bool ChangePattern(char[] pchPatternName, int iLen)
        {
            if (iLen > 200)
            {
                mLastError = "too long";
                return false;
            }

            byte[] byUCommand = new byte[255];
            byUCommand[0] = (byte)'@';
            byUCommand[1] = (byte)'U';
            byUCommand[2] = (byte)'P';
            byUCommand[3] = (byte)'T';
            byUCommand[4] = (byte)'C';
            byUCommand[5] = (byte)':';


            for (int i = 0; i < iLen; i++)
            {
                byUCommand[6 + i] = (byte)(pchPatternName[i]);

            }

            int iCount = 6 + iLen;
            //计算效验码
            int iSum = 0;
            for (int i = 1; i < iCount; i++)
            {
                iSum += byUCommand[i];
            }
            iSum = 0 - iSum;
            //byUCommand[iCount + 6] = (byte)((iSum >> 4) & 0xF);
            //byUCommand[iCount + 7] = (byte)((iSum) & 0xF);

            byte bSum = (byte)iSum;
            string strSum = string.Format("{0:X}", bSum);

            byUCommand[iCount] = (byte)strSum[0];
            byUCommand[iCount + 1] = (byte)strSum[1];
            byUCommand[iCount + 2] = (byte)'#';

            Console.WriteLine("{0},{1}", byUCommand[iCount], byUCommand[iCount + 1]);

            //发送数据
            com.DiscardInBuffer();
            com.Write(byUCommand, 0, iCount + 3);








            Thread.Sleep(1000);
            return RecvData();
        }

        */

        public bool ChangeModel2(string str)
        {
            string ss = "URCM:";
            ss = ss + str;

            int len = ss.Length;
            int sum = 0;
            for (int i = 0; i < len; i++)
            {
                sum += (char)ss[i];
            }
            sum = 0 - sum;
            sum = sum & 0xff;
            byte bSum = (byte)sum;
            string t = string.Format("{0:X}", bSum);
            ss = '@' + ss + t + '#';
            Console.WriteLine(ss);

            com.DiscardInBuffer();
            com.Write(ss);

            Thread.Sleep(RevTime);

            return RecvData();
        }

        public bool ChangePattern2(string str)
        {
            string ss = "UPTC:";
            ss = ss + str;

            int len = ss.Length;
            int sum = 0;
            for(int i=0;i<len;i++)
            {
                sum += (char)ss[i];
            }
            sum = 0 - sum;
            sum = sum & 0xff;
            byte bSum = (byte)sum;
            string t = string.Format("{0:X}", bSum);
            ss = '@'+ ss + t + '#';
            Console.WriteLine(ss);

            com.DiscardInBuffer();
            com.Write(ss);

            Thread.Sleep(RevTime);

            return RecvData();

        }

    }
}
