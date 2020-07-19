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
    public partial class Level2EventResourceMatch : Form
    {
        private bool closed;

        public Level2EventResourceMatch()
        {
            InitializeComponent();
            closed = false;
        }

        public bool getClose()
        {
            return closed;
        }

        private void Level2EventResourceMatch_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        //设置label11文字
        public void setLabel11Text(string text)
        {
            this.label11.Text = text;
        }

        //设置label11文字颜色
        public void setLabel11TextColor(String color)
        {
            if (color.Equals("red"))
            {
                this.label11.ForeColor = Color.Red;
            }
            else if (color.Equals("blue"))
            {
                this.label11.ForeColor = Color.Blue;
            }
        }

        //设置label3可见性
        public void setLabel3Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label3.Visible = true;
                label3.Image = Image.FromFile(@".\pics\EventResourceTable\time_circle.png");
            }
            else
            {
                this.label3.Visible = false;
            }
        }

        //设置label6可见性
        public void setLabel6Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label6.Visible = true;
                label6.Image = Image.FromFile(@".\pics\EventResourceTable\time_rectangle.png");
            }
            else
            {
                this.label6.Visible = false;
            }
        }

        //设置label5可见性
        public void setLabel5Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label5.Visible = true;
                label5.Image = Image.FromFile(@".\pics\EventResourceTable\time_circle.png");
            }
            else
            {
                this.label5.Visible = false;
            }
        }

        //设置label8可见性
        public void setLabel8Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label8.Visible = true;
                label8.Image = Image.FromFile(@".\pics\EventResourceTable\time_rectangle.png");
            }
            else
            {
                this.label8.Visible = false;
            }
        }

        //设置label9可见性
        public void setLabel9Visibility(bool isVisible)
        {
            if (isVisible)
            {
                this.label9.Visible = true;
                label9.Image = Image.FromFile(@".\pics\EventResourceTable\time_circle.png");
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
                label10.Image = Image.FromFile(@".\pics\EventResourceTable\time_rectangle.png");
            }
            else
            {
                this.label10.Visible = false;
            }
        }

        private void Level2EventResourceMatch_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Subtract)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
