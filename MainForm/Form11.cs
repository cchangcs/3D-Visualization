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
    public partial class Form11 : Form
    {
        private bool close;
        public Form11()
        {
            InitializeComponent();
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        /*
         * MessageBox.Show("大坝位移超标！", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
           
         */
        private void Form11_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            if (!getClose())
            {
                this.Close();
            }
        }

        private void Form11_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + NumPad1"关闭大坝位移超标报警
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad1)
            {
                if (!getClose())
                {
                    this.Close();
                }
            }
        }

        private void button1_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + NumPad1"关闭大坝位移超标报警
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad1)
            {
                if (!getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
