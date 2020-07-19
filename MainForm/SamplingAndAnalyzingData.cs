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
    public partial class SamplingAndAnalyzingData : Form
    {
        private bool close;

        private String dataType;

        public SamplingAndAnalyzingData()
        {
            InitializeComponent();
            close = false;
            setDataType("water");
        }

        public void setDataType(String type)
        {
            this.dataType = type;
            if (dataType.Equals("soil"))
            {
                this.label3.Text = "土壤采样分析";
                this.label2.Image = Image.FromFile("");
            }
            else if(dataType.Equals("water"))
            {
                this.label3.Text = "水质采样分析";
                this.label2.Image = Image.FromFile(@".\pics\sensor_data\sensor_data.png");
            }
        }

        public String getDataType()
        {
            return this.dataType;
        }

        public bool getClosed()
        {
            return close;
        }

        private void SamplingAndAnalyzingData_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }
    }
}
