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
    public partial class EventResourceAssociationTable : Form
    {
        private bool close;
        public EventResourceAssociationTable()
        {
            InitializeComponent();
            close = false;
        }

        public bool getClose()
        {
            return close;
        }

        private void EventResourceAssociationTable_FormClosed(object sender, FormClosedEventArgs e)
        {
            close = true;
        }

        public void setTabPageSelectedIndex(int index)
        {
            if(index == 0)
            {
                //选择常态监测事件-资源关联表
                tabPage.SelectedTab = tabPage1;
            }
            else if(index == 1)
            {
                //选择应急响应事件-资源关联表
                tabPage.SelectedTab = tabPage2;
            }
        }

        private void EventResourceAssociationTable_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl +Enter"触发显示 事件-资源表 应急响应模块
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Enter)
            {
                this.setTabPageSelectedIndex(1);
            }
            //"Ctrl + End"触发关闭 事件-资源表 展示界面
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.End)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }

        private void tabPage_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl +Enter"触发显示 事件-资源表 应急响应模块
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Enter)
            {
                this.setTabPageSelectedIndex(1);
            }
            //"Ctrl + End"触发关闭 事件-资源表 展示界面
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.End)
            {
                if (!this.getClose())
                {
                    this.Close();
                }
            }
        }
    }
}
