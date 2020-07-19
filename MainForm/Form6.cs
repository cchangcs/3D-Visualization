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
    public partial class Form6 : Form
    {

        bool closed;

        public Form6()
        {
            InitializeComponent();
            closed = false;
        }

        public bool getClosed()
        {
            return closed;
        }

        private void Form6_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }
    }
}
