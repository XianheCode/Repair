using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Com;

namespace SignalGenerator
{
    public partial class SignalCtrlForm : Form
    {
        public SignalCom _signal = new SignalCom();
        private signalPrm sgprm = new signalPrm();

        public SignalCtrlForm()
        {
            InitializeComponent();
            //groupBox_select.Enabled = false;
            //groupBox_control.Enabled = false;

            sgprm.initPrm();
            _signal.COM = sgprm.portNumber;
            _signal.BaudRate = sgprm.baudRate;



            textBoxCom.Text = sgprm.portNumber.ToString();
            textBoxBaud.Text = sgprm.baudRate.ToString();
            textBox_RevTime.Text = sgprm.recvTime.ToString();
            textBoxModelName.Text = sgprm.modelName;
            textBoxPatternName.Text = sgprm.patterName;

        }


        private void button4_Click(object sender, EventArgs e)
        {
            if(_signal.SignalOff())
            {
                toolStripStatusLabel1.Text = "SignalOff成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "SignalOff失败" + _signal.mLastError;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if(_signal.SignalOn())
            {
                toolStripStatusLabel1.Text = "SignalOn成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "SignalOn失败" + _signal.mLastError;
            }
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            _signal.COM = Convert.ToInt32(textBoxCom.Text);
            _signal.BaudRate = Convert.ToInt32(textBoxBaud.Text);
            if(_signal.Open())
            {
                toolStripStatusLabel1.Text = string.Format("COM{0}连接成功，波特率为{1}", _signal.COM, _signal.BaudRate);
                groupBox_select.Enabled = true;
                groupBox_control.Enabled = true;
            }
            else
            {
                toolStripStatusLabel1.Text = string.Format("COM{0}连接失败", _signal.COM);
            }
            
        }

        private void buttonOnLine_Click(object sender, EventArgs e)
        {

        

            if (_signal.OnLine())
            {
                toolStripStatusLabel1.Text = "OnLine成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "OnLine失败"+_signal.mLastError;
            }
        }

        private void buttonChangeModel_Click(object sender, EventArgs e)
        {
            string str = textBoxModelName.Text;

            
            if (_signal.ChangeModel2(str))
            {
                toolStripStatusLabel1.Text = "ChangeModel成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "ChangeModel失败" + _signal.mLastError;
            }

        }

        private void buttonChangePattern_Click(object sender, EventArgs e)
        {
            string strName = textBoxPatternName.Text;

            Console.WriteLine(strName);


            if (_signal.ChangePattern2(strName))
            {
                toolStripStatusLabel1.Text = "ChangePattern成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "ChangePattern失败" + _signal.mLastError;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(_signal.NextPattern())
            {
                toolStripStatusLabel1.Text = "ChangePattern成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "ChangePattern失败" + _signal.mLastError;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if(_signal.PreviousPattern())
            {
                toolStripStatusLabel1.Text = "ChangePattern成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "ChangePattern失败" + _signal.mLastError;
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            _signal.Close();
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            _signal.Close();
            groupBox_select.Enabled = false;
            groupBox_control.Enabled = false;
        }

        private void buttonShutDown_Click_1(object sender, EventArgs e)
        {
            //if (_signal.ShutDown())
            //{
            //    toolStripStatusLabel1.Text = "ShutDown成功";
            //}
            //else
            //{
            //    toolStripStatusLabel1.Text = "ShutDown失败" + _signal.mLastError;
            //}
            MessageBox.Show("又点错了吧哈哈哈，对不起已经迟了");
            MessageBox.Show("还好我已经把这个功能屏蔽了> <");
        }

        private void button_setRevTime_Click(object sender, EventArgs e)
        {
            int time = 0;
            if (int.TryParse(textBox_RevTime.Text, out time) && time >= 0)
            {
                _signal.RevTime = time;
                toolStripStatusLabel1.Text = "SetRecvTime成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "SetRecvTime失败，请输入一个正整数";
            }
        }

        private void button_saveSignalPrm_Click(object sender, EventArgs e)
        {
            int portNumber = 0, baudRate = 9600, recvTime=0;
            string modelName = textBoxModelName.Text;
            string patterName = textBoxPatternName.Text;
 

            bool ret;
            ret = int.TryParse(textBoxCom.Text, out portNumber);
            ret = ret && int.TryParse(textBoxBaud.Text, out baudRate);
            ret = ret && int.TryParse(textBox_RevTime.Text, out recvTime);
            ret = ret && (modelName != null) && (patterName != null);

            if(ret)
            {
                _signal.COM = portNumber;
                _signal.BaudRate = baudRate;
                _signal.RevTime = recvTime;

                sgprm.portNumber = portNumber;
                sgprm.baudRate = baudRate;
                sgprm.recvTime = recvTime;
                sgprm.modelName = modelName;
                sgprm.patterName = patterName;



                sgprm.savePrm();
                toolStripStatusLabel1.Text = "参数应用成功";
            }
            else
            {
                toolStripStatusLabel1.Text = "参数应用失败，请检查参数格式";
            }
        }
        
        public void RaiseSignal()
        {
            if (!_signal.isOpen())
                _signal.Open();

            _signal.OnLine();
            _signal.ChangeModel2(sgprm.modelName);
            _signal.SignalOn();
            _signal.ChangePattern2(sgprm.patterName);
        }

        public bool initSignal()
        {
            if (!_signal.isOpen())
            {
                if(!_signal.Open())
                {
                    MessageBox.Show("串口打开失败！");
                    return false;
                }
                
            }
            if(!_signal.isOnline())
            {
                if (!_signal.OnLine())
                {
                    MessageBox.Show("信号发生器Online失败！");
                    return false;
                }

            }

            return true;
                
        }

        public bool lightUp()
        {
            if (!initSignal())
                return false;
            return _signal.SignalOn();
        }

        public bool lightDown()
        {
            return _signal.SignalOff();
        }

        private void btn_hide_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}
