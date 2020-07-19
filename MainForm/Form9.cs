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
    public partial class Form9 : Form
    {
        private int img_index;
        private bool close;
        public Form9()
        {
            InitializeComponent();
            img_index = 1;
            label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
            label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
            label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        private void Form9_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        private void Form9_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + W"关闭大坝位移监测
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.W)
            {
                if (!getClose())
                {
                    this.Close();
                }
            }
        }

        public void setImgIndex(int index)
        {
            img_index = index;
            label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
            label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
            label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
        }

        public int getImgIndex()
        {
            return img_index;
        }

        private void label5_Click(object sender, EventArgs e)
        {
            if (img_index > 1)
            {
                img_index -= 1;
                label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
                label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
                label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
            }
            else
            {
                img_index = 3;
                label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
                label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
                label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {
            if (img_index < 3)
            {
                img_index += 1;
                label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
                label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
                label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
            }
            else
            {
                img_index = 1;
                label2.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_x.png");
                label3.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_y.png");
                label4.Image = Image.FromFile(@".\pics\monitor_data\" + img_index.ToString() + "_h.png");
            }
        }
    }
}
