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
    public partial class UAV_Image : Form
    {
        private int img_index;
        private bool closed;

        public UAV_Image()
        {
            InitializeComponent();
            img_index = 1;
            String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
            label2.Image = Image.FromFile(file_path);
            closed = false;
        }

        public void setImgIndex(int index)
        {
            img_index = index;
            String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
            label2.Image = Image.FromFile(file_path);
        }

        public int getImgIndex()
        {
            return img_index;
        }

        /**
         * 范围：from 1 to 263 
         */
        private void label3_Click(object sender, EventArgs e)
        {
            if(img_index > 1)
            {
                img_index -= 1;
                String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
                label2.Image = Image.FromFile(file_path);
            }
            else
            {
                img_index= 263;
                String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
                label2.Image = Image.FromFile(file_path);
            }
        }

        private void label4_Click(object sender, EventArgs e)
        {
            if (img_index < 263)
            {
                img_index += 1;
                String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
                label2.Image = Image.FromFile(file_path);
            }
            else
            {
                img_index = 1;
                String file_path = @".\pics\uav\" + img_index.ToString() + ".jpg";
                label2.Image = Image.FromFile(file_path);
            }
        }

        private void UAV_Image_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        public bool getClosed()
        {
            return closed;
        }
    }
}
