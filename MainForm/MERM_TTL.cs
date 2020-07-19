using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class MERM_TTL : Form
    {
        private bool closed;

        Event DamDisplacement;//大坝位移超标事件
        Event WaterPollution;//水质污染超标事件
        List<String> EmergencyDataTableDam;//大坝位移超标事件应急数据资源表
        List<String> EmergencyDataTableWater;//大坝位移超标事件应急数据资源表

        List<Resource> HistoryDataSet = new List<Resource>();//历史资源集合
        List<Resource> HistortDataSubset = new List<Resource>();//历史资源子集
        List<Resource> EmergencyDataSetDam = new List<Resource>();//大坝位移超标事件应急数据资源
        List<Resource> EmergencyDataSetWater = new List<Resource>();//水质污染超标事件应急数据资源
        List<Resource> ResourceDataSubset = new List<Resource>();//数据资源子集
        List<Resource> EmergencyDataSubset = new List<Resource>();//应急资源子集

        public MERM_TTL()
        {
            InitializeComponent();
            initialEventAndResource();
            closed = false;
        }

        public bool getClose()
        {
            return closed;
        }
        private void MERM_TTL_FormClosed(object sender, FormClosedEventArgs e)
        {
            closed = true;
        }

        //MERM_TTL-L1 “事件-资源”类型关联匹配算法
        private void MERM_TTL_L1(Event event1, List<Resource> resource)
        {
            List<String> EmergencyDataTable = getEmergencyDataTableFromEventResourceMatchTable(event1);
            foreach (Resource r in resource)
            {
                if (EmergencyDataTable.Contains(r.GetType())){
                    HistortDataSubset.Add(r);
                }
            }
        }

        //MERM_TTL-L2 “事件-资源”时间关联匹配算法
        private void MERM_TTL_L2(Event event1, List<Resource> resource1, List<Resource> resource2)
        {
            foreach (Resource r in resource1)
            {
                TimeSpan ts1 = Convert.ToDateTime(event1.GetBegin()) - Convert.ToDateTime(r.GetEnd());
                TimeSpan ts2 = Convert.ToDateTime(r.GetBegin()) - Convert.ToDateTime(event1.GetEnd());
                if ((ts1.TotalHours >=0 && ts1.TotalHours <= 4) || (ts2.TotalHours >= 0 && ts2.TotalHours <= 4))
                {
                    ResourceDataSubset.Add(r);
                }
            }

            foreach (Resource r in resource2)
            {
                TimeSpan ts1 = Convert.ToDateTime(event1.GetBegin()) - Convert.ToDateTime(r.GetEnd());
                TimeSpan ts2 = Convert.ToDateTime(r.GetBegin()) - Convert.ToDateTime(event1.GetEnd());
                if ((ts1.TotalHours >= 0 && ts1.TotalHours <= 4) || (ts2.TotalHours >= 0 && ts2.TotalHours <= 4))
                {
                    ResourceDataSubset.Add(r);
                }
            }
        }


    //MERM_TTL-L3 “事件-资源”空间关联匹配算法
    private void MERM_TTL_L3(Event event1, List<Resource> resource1)
        {
            foreach (Resource r in resource1)
            {
                if (event1.GetLat1() >= r.GetLat1() && event1.GetLat1() <= r.GetLat2()
                    && event1.GetLon1() >= r.GetLon1() && event1.GetLon1() <= r.GetLon2())
                {
                    EmergencyDataSubset.Add(r);
                }
            }
        }
       
        //类型匹配
        private void button2_Click(object sender, EventArgs e)
        {
            this.listBox1.Items.Add("");
            this.listBox1.Items.Add("输出：======================================");
            MERM_TTL_L1(DamDisplacement, HistoryDataSet);
            listBox1.Items.Add("应急数据资源表");
            String text = textBox1.Text;
            if (text.Equals("大坝位移超标事件"))
            {
                StringBuilder table = new StringBuilder();
                EmergencyDataTableDam = getEmergencyDataTableFromEventResourceMatchTable(DamDisplacement);
                foreach (String s in EmergencyDataTableDam)
                {
                    table.Append(s + "    ");
                }
                listBox1.Items.Add(table.ToString());
            }
            else if (text.Equals("水质污染超标事件"))
            {
                StringBuilder table = new StringBuilder();
                EmergencyDataTableWater = getEmergencyDataTableFromEventResourceMatchTable(WaterPollution);
                foreach (String s in EmergencyDataTableWater)
                {
                    table.Append(s + "    ");
                }
                listBox1.Items.Add(table.ToString());
            }
            this.listBox1.Items.Add("");
            listBox1.Items.Add("历史资源子集");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in HistortDataSubset)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
        }

        //时间匹配
        private void button3_Click(object sender, EventArgs e)
        {
            this.listBox1.Items.Add("");
            this.listBox1.Items.Add("输出：======================================");
            MERM_TTL_L2(DamDisplacement, HistortDataSubset, EmergencyDataSetDam);
            listBox1.Items.Add("数据资源子集");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in ResourceDataSubset)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
        }

        //空间匹配
        private void button4_Click(object sender, EventArgs e)
        {
            this.listBox1.Items.Add("");
            this.listBox1.Items.Add("输出：======================================");
            MERM_TTL_L3(DamDisplacement, ResourceDataSubset);
            listBox1.Items.Add("应急资源子集");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in EmergencyDataSubset)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
        }

        //类型匹配-输入
        private void button5_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            this.listBox1.Items.Add("输入：=====================================");
            listBox1.Items.Add("历史数据资源");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in HistoryDataSet)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
        }

        
        //时间匹配-输入
        private void button6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            this.listBox1.Items.Add("输入：=====================================");
            listBox1.Items.Add("历史资源子集");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in HistortDataSubset)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
            this.listBox1.Items.Add("");
            String text = this.textBox1.Text;
            listBox1.Items.Add("应急数据资源");
            listBox1.Items.Add(Info);
            if (text.Equals("大坝位移超标事件"))
            {
                foreach (Resource resource in EmergencyDataSetDam)
                {
                    String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                    listBox1.Items.Add(resourceInfo);
                }
            }else if (text.Equals("水质污染超标事件"))
            {
                foreach (Resource resource in EmergencyDataSetWater)
                {
                    String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                    listBox1.Items.Add(resourceInfo);
                }
            }
        }

        //空间匹配-输入
        private void button7_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            this.listBox1.Items.Add("输入：=====================================");
            listBox1.Items.Add("数据资源子集");
            String Info = "ID，资源类型，开始时间，结束时间，经度范围，纬度范围";
            listBox1.Items.Add(Info);
            foreach (Resource resource in ResourceDataSubset)
            {
                String resourceInfo = resource.GetID() + "，" +
                    resource.GetType() + "，" + resource.GetBegin() + "，" +
                    resource.GetEnd() + "，" + resource.GetLon1().ToString() +
                    "-" + resource.GetLon2() + "，" + resource.GetLat1() + "-"
                    + resource.GetLat2();
                listBox1.Items.Add(resourceInfo);
            }
        }

        //初始化事件和数据资源集合
        public void initialEventAndResource()
        {
            //事件初始化
            //大坝位移超标事件描述
            DamDisplacement = new Event("Dam001", "大坝位移超标事件",
                "2019-8-25 12:00:00", "2019-8-25 13:00:00", 81.622381,
               81.622381, 44.230939, 44.230939);
            //水质位移超标事件描述
            WaterPollution = new Event("Water001", "水质污染超标事件",
                "2019-8-25 12:00:00", "2019-8-25 13:00:00", 81.624970,
               81.624970, 44.227523, 44.227523);

            //历史数据资源
            Resource resource1 = new Resource("DamStation001",
                "大坝位移信息", "2019-8-25 12:00:00", "2019-8-25 12:00:00",
              81.622381, 81.622381, 44.230939, 44.230939);
            HistoryDataSet.Add(resource1);

            Resource resource2 = new Resource("DamStation002",
                "大坝位移信息", "2019-8-25 04:00:00", "2019-8-25 04:00:00",
                 81.622381, 81.622381, 44.230939, 44.230939);
            HistoryDataSet.Add(resource2);

            Resource resource3 = new Resource("DamStation003",
                "大坝位移信息", "2019-8-25 12:00:00", "2019-8-25 12:00:00",
                81.623717, 81.623717, 44.231271, 44.231271);
            HistoryDataSet.Add(resource3);

            Resource resource4 = new Resource("UAV001",
                "坡度坡向信息", "2019-7-11 15:03:00", "2019-7-11 15:38:00",
                81.614721, 81.634160, 44.226929, 44.240365);
            HistoryDataSet.Add(resource4);

            Resource resource5 = new Resource("UAV002",
                "坡度坡向信息", "2019-8-25 10:22:00", "2019-8-25 10:58:00",
                81.614721, 81.634160,  44.226929, 44.240365);
            HistoryDataSet.Add(resource5);

            Resource resource6 = new Resource("WaterSensor001",
                "水质信息（传感器）", "2019-8-21 09:42:59", "2019-8-21 10:42:59",
                 81.624970, 81.624970, 44.227523, 44.227523);
            HistoryDataSet.Add(resource6);

            Resource resource7 = new Resource("WaterSensor002",
                "水质信息（传感器）", "2019-8-25 12:00:00", "2019-8-25 12:00:00",
              81.624364, 81.624364, 44.227102, 44.227102);
            HistoryDataSet.Add(resource7);

            Resource resource8 = new Resource("WaterAnalyzer001",
                "水质信息（分析仪）", "2019-7-11 12:00:00", "2019-7-11 13:00:00",
               81.622177, 81.625381, 44.210037, 44.228013);
            HistoryDataSet.Add(resource8);

            Resource resource9 = new Resource("WaterAnalyzer002",
                "水质信息（分析仪）", "2019-8-25 13:42:00", "2019-8-25 14:42:00",
               81.622177, 81.625381, 44.210037, 44.228013);
            HistoryDataSet.Add(resource9);


            //大坝位移超标事件应急数据资源
            // EmergencyDataSetDam
            Resource resource10 = new Resource("DamStation004",
                "大坝位移信息", "2019-8-25 13:00:00", "2019-8-25 13:00:00",
                81.622381, 81.622381, 44.230939, 44.230939);
            EmergencyDataSetDam.Add(resource10);

            Resource resource11 = new Resource("DamStation005",
                "大坝位移信息", "2019-8-25 14:00:00", "2019-8-25 14:00:00",
               81.623717, 81.623717, 44.231271, 44.231271);
            EmergencyDataSetDam.Add(resource11);

            Resource resource12 = new Resource("DamStation006",
                "大坝位移信息", "2019-8-25 18:00:00", "2019-8-25 18:00:00",
                81.622381, 81.622381, 44.230939, 44.230939);
            EmergencyDataSetDam.Add(resource12);

            Resource resource13 = new Resource("UAV003",
                "坡度坡向信息", "2019-8-25 12:21:00", "2019-8-25 12:58:00",
                81.614721, 81.634160, 44.226929, 44.240365);
            EmergencyDataSetDam.Add(resource13);

            Resource resource14 = new Resource("UAV004",
                "坡度坡向信息", "2019-8-25 13:31:00", "2019-8-25 14:08:00",
                81.627081, 81.633827, 44.251371, 44.262238);
            EmergencyDataSetDam.Add(resource14);
            //水质污染超标事件应急数据资源
            //EmergencyDataSetWater
            Resource resource15 = new Resource("WaterSensor003",
                "水质信息（传感器）", "2019-8-25 14:42:59", "2019-8-25 14:42:59",
                81.624970, 81.624970, 44.227523, 44.227523);
            EmergencyDataSetWater.Add(resource15);

            Resource resource16 = new Resource("WaterSensor004",
                "水质信息（传感器）", "2019-8-25 15:00:00", "2019-8-25 15:00:00",
               81.624364, 81.624364, 44.227102, 44.227102);
            EmergencyDataSetWater.Add(resource16);

            Resource resource17 = new Resource("WaterAnalyzer003",
                 "水质信息（分析仪）", "2019-8-25 15:00:00", "2019-7-11 16:00:00",
                81.622177, 81.625381, 44.210037, 44.228013);
            EmergencyDataSetWater.Add(resource17);

            Resource resource18 = new Resource("WaterAnalyzer004",
                "水质信息（分析仪）", "2019-8-25 14:21:00", "2019-8-25 15:21:00",
                81.627177, 81.631027, 44.230071, 44.231127);
            EmergencyDataSetWater.Add(resource18);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String text = textBox1.Text;
            if (text.Equals("大坝位移超标事件"))
            {
                label6.Text = "事件ID：" + DamDisplacement.GetID();
                label4.Text = "事件主题：" + DamDisplacement.GetTheme();
                label5.Text = "开始时间：" + DamDisplacement.GetBegin();
                label11.Text = "结束时间：" + DamDisplacement.GetEnd();
                label13.Text = "纬度范围：" + DamDisplacement.GetLat1().ToString() + " ~ " + DamDisplacement.GetLat2().ToString();
                label12.Text = "经度范围：" + DamDisplacement.GetLon1().ToString() + " ~ " + DamDisplacement.GetLon2().ToString();
            }
            else if (text.Equals("水质位移超标事件"))
            {
                label6.Text = "事件ID：" + WaterPollution.GetID();
                label4.Text = "事件主题：" + WaterPollution.GetTheme();
                label5.Text = "开始时间：" + WaterPollution.GetBegin();
                label11.Text = "结束时间：" + WaterPollution.GetEnd();
                label13.Text = "纬度范围：" + WaterPollution.GetLat1().ToString() + " ~ " + DamDisplacement.GetLat2().ToString();
                label12.Text = "经度范围：" + WaterPollution.GetLon1().ToString() + " ~ " + DamDisplacement.GetLon2().ToString();
            }
        }

        private List<String> getEmergencyDataTableFromEventResourceMatchTable(Event event1)
        {
            List<String> table = new List<string>();
            if (event1.GetTheme().Equals("大坝位移超标事件"))
            {
                table.Add("大坝位移信息");
                table.Add("坡度坡向信息");
            }
            else if (event1.GetTheme().Equals("水质污染超标事件"))
            {
                table.Add("水质信息（传感器）");
                table.Add("水质信息（分析仪）");
            }
            return table;
        }

    }
}
