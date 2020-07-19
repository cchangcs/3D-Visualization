using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form3 : Form
    {

        private bool close;

        private String type;
        private HelloWorl.UserControl1 userControl11;

        public Form3()
        {
            InitializeComponent();
            close = false;
            userControl11 = new HelloWorl.UserControl1();
        }

        public bool getClose()
        {
            return close;
        }

        public bool isRunning1()
        {
            return backgroundWorker1.IsBusy;
        }

        public bool isRunning2()
        {
            return backgroundWorker2.IsBusy;
        }

        public bool isRunning3()
        {
            return backgroundWorker3.IsBusy;
        }

        public void stopProcess1()
        {
            backgroundWorker1.CancelAsync();
        }

        public void stopProcess2()
        {
            backgroundWorker2.CancelAsync();
        }

        public void stopProcess3()
        {
            backgroundWorker3.CancelAsync();
        }

        public void startProcess1()
        {
            backgroundWorker1.RunWorkerAsync();
        }

        public void startProcess2()
        {
            backgroundWorker2.RunWorkerAsync();
        }

        public void startProcess3()
        {
            backgroundWorker3.RunWorkerAsync();
        }

        public void setType(String type)
        {
            this.type = type;
        }

        public String getType()
        {
            return type;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            backgroundWorker1.ReportProgress(100);
            if (type.Equals("uav"))
            {
                for (int i = 0; i <= 100; i++)
                {
                    if (backgroundWorker1.CancellationPending)
                    {
                        e.Cancel = true; //这里才真正取消 
                        return;
                    }
                    Thread.Sleep(400);
                    if (i == 35)
                    {
                        Form1 form1 = new Form1();
                        form1.DoPreLineNow(false);
                        form1.readFlyCoors(@".\line\uav2.txt");
                    }
                }
            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            
            // 获取异步任务进行的百分比
            progressBar1.Value = e.ProgressPercentage;
            
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                Form1 form1 = new Form1();
                //form1.setCheckBox1(false);
                //form1.setCheckBox2(true);
                this.label4.Text = "用时：90min"; 
            }
        }


        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {
            backgroundWorker2.ReportProgress(100);
            for (int i = 0; i <= 100; i++)
            {
                if (backgroundWorker2.CancellationPending)
                {
                    e.Cancel = true; //这里才真正取消 
                    return;
                }
                Thread.Sleep(100);
                
            }
            
        }

        private void backgroundWorker2_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // 获取异步任务进行的百分比
            progressBar2.Value = e.ProgressPercentage;
            
        }

        private void backgroundWorker2_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                this.label6.Text = "用时：28min"; 
            }
        }

        private void backgroundWorker3_DoWork(object sender, DoWorkEventArgs e)
        {
            for (int i = 0; i <= 100; i++)
            {
                if (backgroundWorker3.CancellationPending)
                {
                    e.Cancel = true; //这里才真正取消 
                    return;
                }
            }
            backgroundWorker3.ReportProgress(100);
        }

        private void backgroundWorker3_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // 获取异步任务进行的百分比
            progressBar3.Value = e.ProgressPercentage;
        }

        private void backgroundWorker3_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                this.label5.Text = "用时：110min";
                this.label7.Text = "总耗时：3.8h";
            }
        }

        private void Form3_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        Form8 form8 = new Form8();
        private void Form3_KeyDown(object sender, KeyEventArgs e)
        {
            /**
             * form31:uav
             * form32:car
             */
           //大坝位移超标事件数据传输
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.E)
            {
                this.setType("uav");
                if (this.isRunning2())
                {
                    this.stopProcess2();
                }
                else
                {
                    this.startProcess2();
                }
                
                //调用数据传输程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\ERSSky\bind\ERSSky.exe";
                m_Process.Start();

                //睡眠一段时间
                Thread.Sleep(10000);

                //关闭进程
                Process[] proc = Process.GetProcessesByName("ERSSky");
                for (int i = 0; i < proc.Length; i++)
                {
                    proc[i].Kill();  //逐个结束进程.
                }
            }
            //"Ctrl + I"显示或隐藏数据传输链路
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.I)
            {
                //绘制数据传输链路
                this.userControl11.DrawLink();
            }
            //大坝位移超标事件数据处理
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.F)
            {
                this.setType("uav");
                if (this.isRunning3())
                {
                    this.stopProcess3();
                }
                else
                {
                    this.startProcess3();
                }

                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.setForm3(this);
                    if (!form8.Visible)
                    {
                        form8.Show();
                    }
                }
                else
                {
                    form8.setForm3(this);
                    if (!form8.Visible)
                    {
                        form8.Show();
                    }
                }
            }
            //水质污染超标事件数据传输
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad6)
            {
                this.setType("car");
                if (this.isRunning2())
                {
                    this.stopProcess2();
                }
                else
                {
                    this.startProcess2();
                }
            }
            //水质污染超标事件数据传输链路
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad3)
            {
                userControl11.AddSensorNetwork();
            }
            else if(e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad7)
            {
                this.setType("car");
                //数据传输
                if (this.isRunning2())
                {
                    this.stopProcess2();
                }
                else
                {
                    this.startProcess2();
                }

                //数据处理
                if (this.isRunning3())
                {
                    this.stopProcess3();
                }
                else
                {
                    this.startProcess3();
                }

                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.setForm3(this);
                    if (!form8.Visible)
                    {
                        form8.Show();
                    }
                }
                else
                {
                    form8.setForm3(this);
                    if (!form8.Visible)
                    {
                        form8.Show();
                    }
                }
            }
        }
    }
}
