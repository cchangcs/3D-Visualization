using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form13 : Form
    {
        private bool close;
        public Form13()
        {
            InitializeComponent();
            this.BackColor = Color.Gray;
            textBox4.BackColor = Color.Gray;
            close = false;
        }

        public void Start_Or_End_Sensor()
        {
            if (button1.Text.Equals("启动采集"))
            {
                this.label7.Text = "正在工作";
                this.BackColor = Color.White;
                textBox4.BackColor = Color.White;
                this.label7.ForeColor = Color.Blue;
                button1.Text = "结束采集";
            }
            else
            {
                this.label7.Text = "未工作";
                this.BackColor = Color.Gray;
                textBox4.BackColor = Color.Gray;
                this.label7.ForeColor = Color.Red;
                button1.Text = "启动采集";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Start_Or_End_Sensor();
        }
        public bool getClose()
        {
            return close;
        }

        private void Form13_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + 5"启动或者停止传感器数据采集
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D5)
            {
                this.Start_Or_End_Sensor();
            }
            //"Ctrl + 6"触发关闭传感器数据采集框
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D6)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
