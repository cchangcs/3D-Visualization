using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form2 : Form
    {

        private HelloWorl.UserControl1 userControl11;
        public Form2()
        {
            userControl11 = new HelloWorl.UserControl1();
            InitializeComponent();
            initTimer();
            initListbox();
        }

        private System.Timers.Timer t1;
        private void initTimer()
        {
            t1 = new System.Timers.Timer(1000); //定时时间1000ms
            t1.Enabled = true;
            t1.Elapsed += new System.Timers.ElapsedEventHandler(t1_Tick);

        }
        private void t1_Tick(object sender, System.Timers.ElapsedEventArgs e)
        {
            DirectoryInfo TheFolder = new DirectoryInfo(@".//line//");
            int length = TheFolder.GetFiles().Length;
            int len_checkbox = listBox1.Controls.Count + listBox2.Controls.Count + listBox3.Controls.Count;
            if (length > len_checkbox)
            {

            }
        }


        private static int uav_nums = 1;
        private static int car_nums = 1;
        private static int person_nums = 1;
        private static int last_y1 = 0;
        private static int last_y2 = 0;
        private static int last_y3 = 0;
        private void initListbox()
        {
            DirectoryInfo TheFolder = new DirectoryInfo(@".//line//");
            //遍历文件
            int x1 = this.listBox1.Location.X;
            int y1 = 10;

            int y2 = 10;
            
            int y3 = 10;

           foreach (FileInfo NextFile in TheFolder.GetFiles())
           {
                if (NextFile.Name.Contains("uav"))
                {
                    last_y1 = y1;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new System.Drawing.Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y1);
                    y1 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "无人机" + uav_nums.ToString();
                    uav_nums += 1;
                    this.listBox1.Controls.Add(checkbox);

                }
                if (NextFile.Name.Contains("car"))
                {

                    last_y2 = y2;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new System.Drawing.Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y2);
                    y2 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "车辆" + car_nums.ToString();
                    car_nums += 1;
                    this.listBox2.Controls.Add(checkbox);
                }
                if (NextFile.Name.Contains("person"))
                {
                    last_y3 = y3;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new System.Drawing.Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y3);
                    y3 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "人员" + person_nums.ToString();
                    person_nums += 1;
                    this.listBox3.Controls.Add(checkbox);
                }
            }
        }


        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(this.checkBox1.CheckState == CheckState.Checked)
            {
                foreach(var control in listBox1.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Checked;
                }
                foreach (var control in listBox2.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Checked;
                }
                foreach (var control in listBox3.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Checked;
                }
            }
            else
            {
                foreach (var control in listBox1.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Unchecked;
                }
                foreach (var control in listBox2.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Unchecked;
                }
                foreach (var control in listBox3.Controls)
                {
                    CheckBox checkbox = (CheckBox)control;
                    checkbox.CheckState = CheckState.Unchecked;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {


            //if (this.checkBox10.CheckState == CheckState.Checked)
            //{
            //    userControl11.AddPersonAndMove3(".//line//person3.txt");
            //}
            foreach (var control in listBox1.Controls)
            {
                CheckBox checkbox = (CheckBox)control;
                if(checkbox.CheckState == CheckState.Checked)
                {
                    userControl11.AddFLyAndMove("./line/"+checkbox.Name, true);
                }
            }

            foreach (var control in listBox2.Controls)
            {
                CheckBox checkbox = (CheckBox)control;
                if (checkbox.CheckState == CheckState.Checked)
                {
                    userControl11.AddCarAndMove("./line/" + checkbox.Name, true);
                }
            }

            foreach (var control in listBox3.Controls)
            {
                CheckBox checkbox = (CheckBox)control;
                if (checkbox.CheckState == CheckState.Checked)
                {
                    userControl11.AddPersonAndMove("./line/" + checkbox.Name, true);
                }
            }

            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            //this.button3.PerformClick();
        }

        private void button3_Click(object sender, EventArgs e)
        {

            t1.Enabled = false;
            this.listBox1.Controls.Clear();
            this.listBox2.Controls.Clear();
            this.listBox3.Controls.Clear();
            DirectoryInfo TheFolder = new DirectoryInfo(@".//line//");

            //遍历文件
            int x1 = this.listBox1.Location.X;
            int y1 = 10;

            int y2 = 10;

            int y3 = 10;
            int uav = 1;
            int car = 1;
            int person = 1;
            foreach (FileInfo NextFile in TheFolder.GetFiles())
            {
                if (NextFile.Name.Contains("uav"))
                {
                    last_y1 = y1;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y1);
                    y1 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "无人机" + uav.ToString();
                    uav += 1;
                    this.listBox1.Controls.Add(checkbox);

                }
                if (NextFile.Name.Contains("car"))
                {

                    last_y2 = y2;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new System.Drawing.Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y2);
                    y2 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "车辆" + car.ToString();
                    car += 1;
                    this.listBox2.Controls.Add(checkbox);
                }
                if (NextFile.Name.Contains("person"))
                {
                    last_y3 = y3;
                    CheckBox checkbox = new CheckBox();
                    checkbox.Font = new System.Drawing.Font("宋体", 10F);
                    checkbox.Location = new Point(x1 + 30, last_y3);
                    y3 += 30;
                    checkbox.Name = NextFile.Name;
                    checkbox.Text = "人员" + person.ToString();
                    person += 1;
                    this.listBox3.Controls.Add(checkbox);
                }
            }
            t1.Enabled = true;
        }
    }
}
