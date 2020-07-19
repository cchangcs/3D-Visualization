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
    public partial class Level1EventResourceMatch : Form
    {
        private bool close;

        private String eventType;

        public String getEventType()
        {
            return eventType;
        }

        public void setEventType(String type)
        {
            eventType = type;
            switch (eventType)
            {
                case "dam_monitor":
                    label1.Text = "大坝变形监测事件-资源类型关联匹配";
                    label3.Image = Image.FromFile(@".\pics\EventResourceTable\dam_monitor.png");
                    break;
                case "dam_response":
                    label1.Text = "水质污染监测事件-资源类型关联匹配";
                    label3.Image = Image.FromFile(@".\pics\EventResourceTable\dam_response.png");
                    break;
                case "water_monitor":
                    label1.Text = "大坝位移超标事件事件-资源类型关联匹配";
                    label3.Image = Image.FromFile(@".\pics\EventResourceTable\water_monitor.png");
                    break;
                case "water_response":
                    label1.Text = "水质污染超标事件事件-资源类型关联匹配";
                    label3.Image = Image.FromFile(@".\pics\EventResourceTable\water_response.png");
                    break;
            }
        }

        //设置文字显示label的Text属性
        public void setLabel4Text(String text)
        {
            label4.Text = text;
        }

        //设置红色圆的Visible属性（表示不在“事件-资源”表中的资源）
        public void setLabel2Visibility(bool isVisible)
        {
            if (isVisible)
            {
                label2.Image = Image.FromFile(@".\pics\EventResourceTable\event2.png");
                label2.Visible = true;
            }
            else
            {

                label2.Visible = false;
            }
        }

        //设置蓝色圆的Visible属性（表示在“事件-资源”表中的资源）
        public void setLabel8Visibility(bool isVisible)
        {
            if (isVisible)
            {
                label8.Image = Image.FromFile(@".\pics\EventResourceTable\event1.jpg");
                label8.Visible = true;
            }
            else
            {
                label8.Visible = false;
            }
        }

        //设置资源类型文字说明（label5）
        public void setLabel5Text(String text)
        {
            this.label5.Text = text;
        }

        //设置label4提示文字颜色
        public void setLabel4textColor(String color)
        {
            if (color.Equals("red"))
            {
                label4.ForeColor = Color.Red;
            }
            else if(color.Equals("green"))
            {
                label4.ForeColor = Color.Green;
            }
        }

        //设置“事件-资源”关联表的Visible属性
        public void setLabel3Visibility(bool isVisible)
        {
           
            label3.Visible = isVisible;
        }

        public Level1EventResourceMatch()
        {
            InitializeComponent();
            //setEventType("water_response");
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        private void EventResourceMatch_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        private void Level1EventResourceMatch_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.PageDown)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
