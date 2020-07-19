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
    public partial class Multispectral_data : Form
    {
        private int img_index;
        private bool closed;
        private Dictionary<int, String> im = new Dictionary<int, string>();
        private Dictionary<int, String> ms = new Dictionary<int, string>();
        /*
        label2:现场照片
        label6:多光谱信息
        */
        public Multispectral_data()
        {
            InitializeComponent();
            closed = false;
            im.Add(1, @".\pics\multispectum_and_scene\红色废渣IM.jpg");
            im.Add(2, @".\pics\multispectum_and_scene\泥土IM.jpg");
            im.Add(3, @".\pics\multispectum_and_scene\水体IM.jpg");
            im.Add(4, @".\pics\multispectum_and_scene\碎石路IM.jpg");
            im.Add(5, @".\pics\multispectum_and_scene\紫苏IM.jpg");
            ms.Add(1, @".\pics\multispectum_and_scene\红色废渣MS.jpg");
            ms.Add(2, @".\pics\multispectum_and_scene\泥土MS.jpg");
            ms.Add(3, @".\pics\multispectum_and_scene\水体MS.jpg");
            ms.Add(4, @".\pics\multispectum_and_scene\碎石路MS.jpg");
            ms.Add(5, @".\pics\multispectum_and_scene\紫苏MS.jpg");
            img_index = 1;
            label2.Image = Image.FromFile(im[img_index]);
            label6.Image = Image.FromFile(ms[img_index]);
        }

        public bool getClosed()
        {
            return closed;
        }

        public void setImgIndex(int index)
        {
            img_index = index;
            label2.Image = Image.FromFile(im[img_index]);
            label6.Image = Image.FromFile(ms[img_index]);
        }

        public int getImgIndex()
        {
            return img_index;
        }

        private void Multispectral_data_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        private void label3_Click(object sender, EventArgs e)
        {
            if (img_index > 1)
            {
                img_index -= 1;
                label2.Image = Image.FromFile(im[img_index]);
                label6.Image = Image.FromFile(ms[img_index]);
            }
            else
            {
                img_index = 5;
                label2.Image = Image.FromFile(im[img_index]);
                label6.Image = Image.FromFile(ms[img_index]);
            }
        }

        private void label4_Click(object sender, EventArgs e)
        {
            if (img_index < 5)
            {
                img_index += 1;
                label2.Image = Image.FromFile(im[img_index]);
                label6.Image = Image.FromFile(ms[img_index]);
            }
            else
            {
                img_index = 1;
                label2.Image = Image.FromFile(im[img_index]);
                label6.Image = Image.FromFile(ms[img_index]);
            }
        }
    }
}
