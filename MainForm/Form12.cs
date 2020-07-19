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
    public partial class Form12 : Form
    {
        private bool close;
        public Form12()
        {
            InitializeComponent();
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        private void Form12_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        /*
         * 
         */

       

        private void button1_Click(object sender, EventArgs e)
        {
            if (!getClose())
            {
                this.Close();
            }
        }

        private void Form12_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + NumPad2"关闭水质污染超标报警
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad2)
            {
                 if (!getClose())
                {
                    this.Close();
                }
            }
        }

        private void button1_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + NumPad2"关闭水质污染超标报警
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad2)
            {
                if (!getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
