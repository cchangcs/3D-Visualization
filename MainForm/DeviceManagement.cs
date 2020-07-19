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
    public partial class DeviceManagement : Form
    {
        private bool close;
        private String[] numbers;
        private String[] names;
        private String[] amount;
        private String[] Features;
        public DeviceManagement()
        {
            InitializeComponent();
            close = false;
            numbers = new String[]{"1", "2", "3", "4", "5", "6", "7", "8", "9" };
            String[] names = {"高分卫星", "无人机","通信车","高光谱设备","手持终端","水质传感器","手持多光谱","监测站", "摄像机"};
            String[] amount = { "1/3", "1/2", "1/1", "1/2", "1/5", "5/10", "1/3", "4/4", "1/2" };
            String[] Features = { "获取高分数据", "无人机倾斜摄影 | 无人机高光谱", "通信 | 数据处理中心", "获取高光谱影像", "获取位置信息及相关参数",  "采集水质数据", "采集多光谱信息", "监测位移信息", "拍摄现场照片" };
            //dataGridView 添加数据行
            for(int i = 0; i < 9; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                int index = dataGridView1.Rows.Add(row);
                dataGridView1.Rows[index].Cells[0].Value = numbers[i];
                dataGridView1.Rows[index].Cells[1].Value = names[i];
                dataGridView1.Rows[index].Cells[2].Value = amount[i];
                dataGridView1.Rows[index].Cells[3].Value = Features[i];
                dataGridView1.Rows[index].Cells[4].Value = "增加设备";
                dataGridView1.Rows[index].Cells[5].Value = "减少设备";
            }
        }

        public bool getClose()
        {
            return close;
        }

        private void DeviceManagement_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            int rowIndex = e.RowIndex;
            int colIndex = e.ColumnIndex;
            String buttonText = this.dataGridView1.Rows[rowIndex].Cells[colIndex].Value.ToString();
            if(buttonText == "增加设备")
            {
                string amount = this.dataGridView1.Rows[rowIndex].Cells[2].Value.ToString();
                String[] nums = amount.Split('/');
                int num_now = int.Parse(nums[0]);
                int num_total = int.Parse(nums[1]);
                if(num_now < num_total)
                {
                    num_now += 1;
                }
                else
                {
                    MessageBox.Show("设备已添加至最大可用数目！");
                    return;
                }
                this.dataGridView1.Rows[rowIndex].Cells[2].Value = num_now.ToString() + "/" + num_total.ToString();
            }
            
            if(buttonText == "减少设备")
            {
                string amount = this.dataGridView1.Rows[rowIndex].Cells[2].Value.ToString();
                String[] nums = amount.Split('/');
                int num_now = int.Parse(nums[0]);
                int num_total = int.Parse(nums[1]);
                if (num_now > 0)
                {
                    num_now -= 1;
                }
                else
                {
                    MessageBox.Show("无使用中设备！");
                    return;
                }
                this.dataGridView1.Rows[rowIndex].Cells[2].Value = num_now.ToString() + "/" + num_total.ToString();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("设备数目修改成功！");
            if (!this.getClose())
            {
                this.Close();
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!this.getClose())
            {
                this.Close();
            }
        }
    }
}
