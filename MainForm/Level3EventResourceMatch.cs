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
    public partial class Level3EventResourceMatch : Form
    {
        private bool closed;

        public Level3EventResourceMatch()
        {
            InitializeComponent();
            closed = false;
        }

        public bool getClose()
        {
            return closed;
        }

        private void Level3EventResourceMatch_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        //设置label12文字
        public void setLabel12Text(string text)
        {
            this.label12.Text = text;
        }

        //设置label12文字颜色
        public void setLabel12TextColor(String color)
        {
            if (color.Equals("red"))
            {
                this.label12.ForeColor = Color.Red;
            }
            else if (color.Equals("blue"))
            {
                this.label12.ForeColor = Color.Blue;
            }
        }

        //设置label6可见性
        public void setLabel6Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label6.Visible = true;
                label6.Image = Image.FromFile(@".\pics\EventResourceTable\location_point.png");
                label6.Size = new Size(82, 81);
                //label6.Size = new Size(104, 48); 
            }
            else
            {
                this.label6.Visible = false;
            }
        }

        //设置label2可见性
        public void setLabel2Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label2.Visible = true;
                label2.Image = Image.FromFile(@".\pics\EventResourceTable\location_point.png");
                label2.BackColor = SystemColors.GradientActiveCaption;
                label2.Size = new Size(82, 81);
                //label6.Size = new Size(104, 48); 
            }
            else
            {
                this.label2.Visible = false;
            }
        }

        //设置label8可见性
        public void setLabel8Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label8.Visible = true;
                label8.Image = Image.FromFile(@".\pics\EventResourceTable\location_point.png");
                label8.BackColor = SystemColors.GradientActiveCaption;
                label8.Size = new Size(82, 81);
                //label6.Size = new Size(104, 48); 
            }
            else
            {
                this.label8.Visible = false;
            }
        }

        //设置label5可见性
        public void setLabel5Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label5.Visible = true;
                label5.Image = Image.FromFile(@".\pics\EventResourceTable\location_area.jpg");
                label5.BackColor = SystemColors.GradientActiveCaption;
                label5.Size = new Size(104, 48); 
            }
            else
            {
                this.label5.Visible = false;
            }
        }

        //设置label7可见性
        public void setLabel7Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label7.Visible = true;
                label7.Image = Image.FromFile(@".\pics\EventResourceTable\location_area.jpg");
                label7.BackColor = SystemColors.GradientActiveCaption;
                label7.Size = new Size(104, 48);
            }
            else
            {
                this.label7.Visible = false;
            }
        }

        //设置label9可见性
        public void setLabel9Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label9.Visible = true;
                label9.Image = Image.FromFile(@".\pics\EventResourceTable\location_area.jpg");
                label9.BackColor = SystemColors.GradientActiveCaption;
                label9.Size = new Size(104, 48);
            }
            else
            {
                this.label9.Visible = false;
            }
        }

        //设置label10可见性
        public void setLabel10Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label10.Visible = true;
                label10.Image = Image.FromFile(@".\pics\EventResourceTable\location_area.jpg");
                label10.BackColor = SystemColors.GradientActiveCaption;
                label10.Size = new Size(104, 48);
            }
            else
            {
                this.label10.Visible = false;
            }
        }

        private void Level3EventResourceMatch_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Divide)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
