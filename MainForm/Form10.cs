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
    public partial class Form10 : Form
    {
        private bool close;

        public Form10()
        {
            InitializeComponent();
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        private void Form10_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        private void Form10_KeyDown(object sender, KeyEventArgs e)
        {
             //"Ctrl + X"关闭传感器常态监测
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.X)
            {
                if (!getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
