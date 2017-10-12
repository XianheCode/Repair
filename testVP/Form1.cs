using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Cognex.VisionPro;
using Cognex.VisionPro.ToolGroup;
using Cognex.VisionPro.QuickBuild;

namespace testVP
{
    public partial class Form1 : Form
    {
        string m_strVppFileName = "test1.vpp";
        CogJobManager m_JobManager = null;
        CogJob m_Job_1 = null;
        
        public Form1()
        {
            InitializeComponent();
            initVPP();
        }

        public void initVPP()
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


            if (nCount < 1)
            {
                MessageBox.Show("Wrong CCD Model:Job count less than 3.");
                this.Close();
            }

            m_Job_1 = m_JobManager.Job(0);

            if (m_Job_1 == null)
                MessageBox.Show("null");

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(m_Job_1 == null)
            {
                MessageBox.Show("Null");
                return;
            }
            m_Job_1.Run();
        }
    }
}
