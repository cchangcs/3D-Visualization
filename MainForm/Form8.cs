using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form8 : Form
    {

        bool closed;
        private HelloWorl.UserControl1 userControl11;
        public Form8()
        {
            InitializeComponent();
            closed = false;
            userControl11 = new HelloWorl.UserControl1();
        }

        public bool isRunning()
        {
            return backgroundWorker1.IsBusy;
        }


        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (backgroundWorker1.IsBusy)
            {
                backgroundWorker1.CancelAsync();
            }
            else
            {
                backgroundWorker1.RunWorkerAsync();
            }
           
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            for (int i = 0; i <= 100; i++)
            {
                if (backgroundWorker1.CancellationPending)
                {
                    e.Cancel = true; //这里才真正取消 
                    return;
                }
                Thread.Sleep(100);
                backgroundWorker1.ReportProgress(i);
            }
        }
        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // 获取异步任务进行的百分比
            progressBar1.Value = e.ProgressPercentage;
            this.label2.Text = e.ProgressPercentage.ToString() + "%";
            if(e.ProgressPercentage == 100)
            {
                label1.Text = "处理完成！";
            }
        }


        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                /*
                Form1 form1 = (Form1)this.Owner;
                form1.checkBox6.Visible = true;
                form1.checkBox4.Visible = true;
                form1.checkBox5.Visible = true;
                form1.checkBox9.Visible = true;
                form1.checkBox11.Visible = true;
                form1.checkBox12.Visible = true;
                form1.checkBox7.Visible = true;
                form1.Refresh();
                */

            }
        }

        private void Form8_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        public bool getClosed()
        {
            return closed;
        }

        private Form3 form3;

        public void setForm3(Form3 form)
        {
            form3 = form;
        }
        
        public Form3 getForm3()
        {
            return form3;
        }

        private void Form8_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + 4"触发关闭数据处理框、应急进度框、移除数据传输链路
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D4)
            {
                if(this.getForm3() != null)
                {
                    if (this.getForm3().getType().Equals("uav"))
                    {
                        userControl11.HideLink();
                    }
                    else
                    {
                        userControl11.HideSensorNetwork();
                    }
                    if (!this.getForm3().getClose())
                    {
                        this.getForm3().Close();
                    }
                }
                if (!this.getClosed())
                {
                    this.Close();
                }
                
            }
        }
    }
}
