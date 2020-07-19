using System;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //treeView1.CheckBoxes = true;
            treeView2.CheckBoxes = true; //设置treeView2的节点为CheckBox
            form31.setType("uav");
            form32.setType("car");
        }

        private void userControl11_Load(object sender, EventArgs e)
        {
            userControl11.ShowOsgEarth();
        }


        private void 无人机ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }


        private void 车辆ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 行人ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 实时监控数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //擦除原有路径
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();

            //绘制路径
            userControl11.DrawFlyLine();
            userControl11.DrawCarLine();
            userControl11.DrawPersonLine();

            //无人机、车辆、行人移动
            userControl11.DoPreLineNow_(true);
            userControl11.DoPreLineNow2_(true);
            userControl11.DoPreLineNow3_(true);
        }

        private void 无人机跟踪ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 车辆跟踪ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 行人跟踪ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 飞往机场ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.FlyTo(34.3834, 109.1347, 1000);
        }

        private void 飞往西安ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.FlyTo(34.45, 109.35, 400000);
        }

        private void 飞往阎良ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.FlyTo(34.65471, 109.22735, 40000);
        }

        private void 面模式ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.SetFace();
        }

        private void 线模式ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.SetLine();
        }

        private void 点模式ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            userControl11.SetPoint();
        }

        private static Boolean monitor = true;
        private void 实时位置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (monitor)
            {
                //擦除原有路径
                userControl11.ClearFlyLine();
                userControl11.ClearCarLine();
                userControl11.ClearPersonLine();

                //绘制路径
                userControl11.DrawFlyLine();
                userControl11.DrawCarLine();
                userControl11.DrawPersonLine();

                //无人机、车辆、行人移动
                userControl11.DoPreLineNow_(true);
                userControl11.DoPreLineNow2_(true);
                userControl11.DoPreLineNow3_(true);
                monitor = false;
            }
        }

        private static Boolean isTrackFly = false;
        private static Boolean isTrackCar = false;
        private static Boolean isTrackPerson = false;
        private void 车辆ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            isTrackFly = false;
            isTrackCar = !isTrackCar;
            isTrackPerson = false;
            userControl11.TrackCar(isTrackCar);
        }

        private void 人员ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            isTrackFly = false;
            isTrackCar = false;
            isTrackPerson = !isTrackPerson;
            userControl11.TrackPerson(isTrackPerson);
        }

        private void 无人机ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            isTrackFly = !isTrackFly;
            isTrackCar = false;
            isTrackPerson = false;
            userControl11.TrackFly(isTrackFly);
        }

        private void 隐藏位置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //擦除原有路径
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();

            //无人机、车辆、行人移动
            userControl11.DoPreLineNow_(false);
            userControl11.DoPreLineNow2_(false);
            userControl11.DoPreLineNow3_(false);
            monitor = true;
        }

        private void 显示救援轨迹ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            //绘制路径
            userControl11.DrawFlyLine();
            userControl11.DrawCarLine();
            userControl11.DrawPersonLine();
        }

        private void 隐藏救援轨迹ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            //擦除原有路径
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();
        }

        private static Boolean isStartCar = false;
        private void 车辆ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();
            userControl11.DrawCarLine();
            isStartCar = !isStartCar;

            userControl11.DoPreLineNow_(false);
            userControl11.DoPreLineNow2_(isStartCar);
            userControl11.DoPreLineNow3_(false);
        }
        private static Boolean isStartPerson = false;
        private void 人员ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();
            userControl11.DrawPersonLine();
            isStartPerson = !isStartPerson;

            userControl11.DoPreLineNow_(false);
            userControl11.DoPreLineNow2_(false);
            userControl11.DoPreLineNow3_(isStartPerson);
        }

        private static Boolean isStartFly = false;
        private void 无人机ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            userControl11.ClearFlyLine();
            userControl11.ClearCarLine();
            userControl11.ClearPersonLine();
            userControl11.DrawFlyLine();
            isStartFly = !isStartFly;

            userControl11.DoPreLineNow_(isStartFly);
            userControl11.DoPreLineNow2_(false);
            userControl11.DoPreLineNow3_(false);

        }

        private void 车辆坐标文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog pOpenFileDialog = new OpenFileDialog();
            pOpenFileDialog.Title = "打开设备文件";
            pOpenFileDialog.Filter = "车辆坐标文件(*.txt)|*.txt";
            if (pOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filename = pOpenFileDialog.FileName;//获取显示文件名

                userControl11.ReadCarCoords(filename);
            }
        }

        private void 人员坐标文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog pOpenFileDialog = new OpenFileDialog();
            pOpenFileDialog.Title = "打开设备文件";
            pOpenFileDialog.Filter = "人员坐标文件(*.txt)|*.txt";
            if (pOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filename = pOpenFileDialog.FileName;//获取显示文件名

                userControl11.ReadPersonCoords(filename);
            }

        }

        private void 无人机坐标文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog pOpenFileDialog = new OpenFileDialog();
            pOpenFileDialog.Title = "打开设备文件";
            pOpenFileDialog.Filter = "无人机坐标文件(*.txt)|*.txt";
            if (pOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                String filename = pOpenFileDialog.FileName;//获取显示文件名
                userControl11.ReadFlyCoords(filename);
            }
        }
        
        public void readCarCoors(String filename)
        {
            userControl11.ReadCarCoords(filename);
        }

        public void readPersonCoors(String filename)
        {
            userControl11.ReadPersonCoords(filename);
        }

        public void readFlyCoors(String filename)
        {
            userControl11.ReadFlyCoords(filename);
        }
        Form2 form2 = new Form2();
        private void 添加终端ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //carMonitor = false;
            if (!form2.Visible)
            {
                form2.Show();
            }
            else
            {
                form2.Hide();
            }
        }

        private void 隐藏终端ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        //private void button1_Click_1(object sender, EventArgs e)
        //{
        //    if (!textBox1.Text.Equals("") && !textBox2.Text.Equals(""))
        //    {
        //        double lon = Double.Parse(textBox1.Text);//经度
        //        double lat = Double.Parse(textBox2.Text);//维度
        //        userControl11.FlyTo(lat, lon, 4000);
        //    }
        //    else
        //    {
        //        if (textBox1.Text.Equals("") && !textBox2.Text.Equals(""))
        //        {
        //            MessageBox.Show("请输入经度！");
        //        }
        //        else if (!textBox1.Text.Equals("") && textBox2.Text.Equals(""))
        //        {
        //            MessageBox.Show("请输入维度！");
        //        }
        //        else if (textBox1.Text.Equals("") && textBox2.Text.Equals(""))
        //        {
        //            MessageBox.Show("请输入经度和纬度！");
        //        }
        //    }
        //}


        //C#调用外部程序
        private bool StartProcess(String fullFilePath, params string[] args)
        {
            string s = "";
            foreach (string arg in args)
            {
                s = s + arg + " ";
            }
            s = s.Trim();
            Process process = new Process(); //创建进程对象
            ProcessStartInfo startInfo = new ProcessStartInfo(fullFilePath, s); //参数为（程序名，传入的参数）
            process.StartInfo = startInfo;
            process.Start();
            return true;
        }

        //显示传感器数据（显示环保坝的作为代表）
        Form10 form10 = new Form10();
        public void showSensorData()
        {
            if (form10.getClose())
            {
                form10 = new Form10();
                if (!form10.Visible)
                {
                    form10.Show();
                }
            }
            else
            {
                if (!form10.Visible)
                {
                    form10.Show();
                }
            }
        }
       
        /*
        //创建随机点文件
        private void CreateRandomPointFile(String path, String lon, String lat)
        {
            string exe_path = @"G:\proj\ClipRaster1.0\代码\ClipRaster1.0\bin\Debug\ClipRaster1.0.exe";
            string[] the_args = { "point", path, lon, lat };
            StartProcess(exe_path, the_args);
        }

        //通过随机点文件创建TIN
        private void CreateTin(String savepath, string filepath)
        {
            string exe_path = @"G:\proj\ClipRaster1.0\代码\ClipRaster1.0\bin\Debug\ClipRaster1.0.exe";
            string[] the_args = { "create", savepath, filepath};
            StartProcess(exe_path, the_args);
        }

        //TIN转Raster
        private void Tin2Raster(String in_tin, String out_raster)
        {
            string exe_path = @"G:\proj\ClipRaster1.0\代码\ClipRaster1.0\bin\Debug\ClipRaster1.0.exe";
            string[] the_args = { "transfer", in_tin, out_raster };
            StartProcess(exe_path, the_args);
        }

        //裁剪Raster
        private void CropRaster(String in_raster, String in_shp, String out_raster)
        {
            string exe_path = @"G:\proj\ClipRaster1.0\代码\ClipRaster1.0\bin\Debug\ClipRaster1.0.exe";
            string[] the_args = { "crop", in_raster, in_shp, out_raster};
            StartProcess(exe_path, the_args);
        }
        */
        
        public void addTerrain()
        {
            this.userControl11.AddTerrain();
        }

        public void addPersonPoint()
        {
            this.userControl11.AddPersonPoint();
        }

        public void ReadPersonCoords(string path)
        {
            this.userControl11.ReadPersonCoords(path);
        }

        public void DoPreLineNow(Boolean start)
        {
            userControl11.DoPreLineNow_(start);

        }

        public void DoPreLineNow2(Boolean start)
        {
            userControl11.DoPreLineNow2_(start);

        }

        public void DoPreLineNow3(Boolean start)
        {
            userControl11.DoPreLineNow3_(start);

        }

        Form3 form31 = new Form3();
        Form3 form32 = new Form3();
        Form8 form8 = new Form8();
        Form9 form9 = new Form9();
        Form11 form11 = new Form11();
        Form12 form12 = new Form12();
        Form13 form13 = new Form13();
        MERM_TTL merm = new MERM_TTL();
        UAV_Image uav_image = new UAV_Image();
        DeviceManagement deviceManagement = new DeviceManagement();//设备管理模拟
        EventResourceAssociationTable eraTable = new EventResourceAssociationTable();//事件-资源关联表
        Level1EventResourceMatch erMatchBaseType = new Level1EventResourceMatch();//事件-资源类型关联匹配
        Level2EventResourceMatch erMatchBaseTime = new Level2EventResourceMatch();//事件-资源时间关联匹配
        Level3EventResourceMatch erMatchBaseLocation = new Level3EventResourceMatch();//事件-资源空间关联匹配
        //treeView节点触发事件
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            form31.setType("uav");
            form32.setType("car");
            if (e.Node.Text == "灾害场景模拟")
            {

            }
            else if (e.Node.Text == "阿希金矿")
            {
                userControl11.FlyTo(44.23, 81.62, 3000);

            }
            else if (e.Node.Text == "灾害中")
            {
                userControl11.FlyTo(44.23, 81.62, 2000000);

            }
            else if (e.Node.Text == "大坝日常变形监测系统")
            {

                // 调用大坝变形监测系统
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\HCDisplay.exe";
                m_Process.Start();


                /*
                显示数据界面 
                
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }*/
            }
            else if (e.Node.Text == "遥感卫星常态监测")
            {

            }
            else if (e.Node.Text == "传感器常态监测")
            {
                showSensorData();
            }
            else if (e.Node.Text == "无人机数据采集")
            {
                //进入数据采集、传输、处理位置
                userControl11.FlyTo(44.240013, 81.623840, 1700);
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (!form31.Visible)
                    {
                        form31.Show();
                    }
                }
                else
                {
                    if (!form31.Visible)
                    {
                        form31.Show();
                    }
                }
                if (form31.isRunning1())
                {
                    form31.stopProcess1();
                }
                else
                {
                    form31.startProcess1();
                }

                //无人机、车辆、救援人员移动
                this.userControl11.DoPreLineNow_(false);
                this.userControl11.DoPreLineNow2_(false);
                readFlyCoors(@".\line\uav1.txt");
                readCarCoors(@".\line\car.txt");

            }
            else if (e.Node.Text == "数据传输1")
            {
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (form31.isRunning2())
                    {
                        form31.stopProcess2();
                    }
                    else
                    {
                        form31.startProcess2();
                    }

                }
                else
                {
                    if (form31.isRunning2())
                    {
                        form31.stopProcess2();
                    }
                    else
                    {
                        form31.startProcess2();
                    }
                }
                //绘制数据传输链路
                //this.userControl11.DrawLink();
                //setCheckBox13(true);
                //调用数据传输程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\ERSSky\bind\ERSSky.exe";
                m_Process.Start();

            }
            else if (e.Node.Text == "监督分类")
            {
                //调用地物监督分类程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\supervised_class\Supervisedclass.exe";
                m_Process.Start();

            }
            else if (e.Node.Text == "变化检测")
            {
                //调用地物变化检测程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\change_detection\ChangeDetection.exe";
                m_Process.Start();
            }
            else if (e.Node.Text == "数据处理1")
            {
                /*
                 进度条
                 */
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (form31.isRunning3())
                    {
                        form31.stopProcess3();
                    }
                    else
                    {
                        form31.startProcess3();
                    }
                }
                else
                {

                    if (form31.isRunning3())
                    {
                        form31.stopProcess3();
                    }
                    else
                    {
                        form31.startProcess3();
                    }

                }
                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.Owner = this;
                    form8.Show();
                }
                else
                {
                    form8.Owner = this;
                    form8.Show();
                }
            }
            else if (e.Node.Text == "手持终端数据采集1")
            {
                if (entry)
                {
                    this.userControl11.ModifyPerson(3);
                }
                DoPreLineNow3(false);
                ReadPersonCoords(@".\line\person1.txt");
                if (backgroundWorker1.IsBusy)
                {
                    backgroundWorker1.CancelAsync();
                }
                else
                {
                    backgroundWorker1.RunWorkerAsync();
                }
            }
            else if (e.Node.Text == "传感器数据采集")
            {
                //进入传感器区域
                userControl11.FlyTo(44.229914, 81.623246, 1000);
                //调出数据采集进度条
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (!form32.Visible)
                    {
                        form32.Show();
                    }
                }
                else
                {
                    if (!form32.Visible)
                    {
                        form32.Show();
                    }
                }
                if (form32.isRunning1())
                {
                    form32.stopProcess1();
                }
                else
                {
                    form32.startProcess1();
                }
                //无人机、车辆、救援人员移动
                this.userControl11.DoPreLineNow2_(false);
                readCarCoors(@".\line\car.txt");
                if (form13.getClose())
                {
                    form13 = new Form13();
                    if (!form13.Visible)
                    {
                        form13.Show();
                    }
                }
                else
                {
                    if (!form13.Visible)
                    {
                        form13.Show();
                    }
                }
            }
            else if (e.Node.Text == "手持终端数据采集2")
            {
                //进入数据采集、传输、处理位置
                userControl11.FlyTo(44.228425, 81.623174, 1800);
                if (entry)
                {
                    this.userControl11.ModifyPerson(3);
                }
                DoPreLineNow3(false);
                ReadPersonCoords(@".\line\person1.txt");
                if (backgroundWorker1.IsBusy)
                {
                    backgroundWorker1.CancelAsync();
                }
                else
                {
                    backgroundWorker1.RunWorkerAsync();
                }
            }
            else if (e.Node.Text == "数据传输2")
            {
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (form32.isRunning2())
                    {
                        form32.stopProcess2();
                    }
                    else
                    {
                        form32.startProcess2();
                    }

                }
                else
                {
                    if (form32.isRunning2())
                    {
                        form32.stopProcess2();
                    }
                    else
                    {
                        form32.startProcess2();
                    }
                }
                //显示水质污染超标事件数据传输链路
                if (this.checkBox2.CheckState == CheckState.Checked)
                {
                    this.checkBox2.CheckState = CheckState.Unchecked;
                    this.checkBox2.Checked = false;
                }
                else
                {
                    this.checkBox2.CheckState = CheckState.Checked;
                    this.checkBox2.Checked = true;
                }

            }
            else if (e.Node.Text == "数据处理2")
            {
                /*
                 进度条
                 */
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (form32.isRunning3())
                    {
                        form32.stopProcess3();
                    }
                    else
                    {
                        form32.startProcess3();
                    }
                }
                else
                {

                    if (form32.isRunning3())
                    {
                        form32.stopProcess3();
                    }
                    else
                    {
                        form32.startProcess3();
                    }

                }
                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.Owner = this;
                    form8.Show();
                }
                else
                {
                    form8.Owner = this;
                    form8.Show();
                }
            }
            else if (e.Node.Text == "大坝位移超标")
            {
                //MessageBox.Show("水质污染超标！", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                if (form11.getClose())
                {
                    form11 = new Form11();
                    if (!form11.Visible)
                    {
                        form11.Show();
                    }
                }
                else
                {
                    if (!form11.Visible)
                    {
                        form11.Show();
                    }
                }
            }
            else if (e.Node.Text == "水质污染超标")
            {
                //MessageBox.Show("水质污染超标！", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                if (form12.getClose())
                {
                    form12 = new Form12();
                    if (!form12.Visible)
                    {
                        form12.Show();
                    }
                }
                else
                {
                    if (!form12.Visible)
                    {
                        form12.Show();
                    }
                }
            }
            else if (e.Node.Text == "设备管理")
            {
                if (deviceManagement.getClose())
                {
                    deviceManagement = new DeviceManagement();
                    if (!deviceManagement.Visible)
                    {
                        deviceManagement.Show();
                    }
                }
                else
                {
                    if (!deviceManagement.Visible)
                    {
                        deviceManagement.Show();
                    }
                }
            }
            else if (e.Node.Text == "事件-资源关联表")
            {
                if (eraTable.getClose())
                {
                    eraTable = new EventResourceAssociationTable();
                    if (!eraTable.Visible)
                    {
                        eraTable.Show();
                    }
                }
                else
                {
                    if (!eraTable.Visible)
                    {
                        eraTable.Show();
                    }
                }
            }
            else if (e.Node.Text == "事件-资源类型关联匹配")
            {
                if (erMatchBaseType.getClose())
                {
                    erMatchBaseType = new Level1EventResourceMatch();
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(delegate () { level1EventResourceMatch_func("dam_monitor"); });
                Thread childThread = new Thread(childref);
                childThread.Start();

            }
            else if (e.Node.Text == "事件-资源时间关联匹配")
            {
                if (erMatchBaseTime.getClose())
                {
                    erMatchBaseTime = new Level2EventResourceMatch();
                    if (!erMatchBaseTime.Visible)
                    {
                        erMatchBaseTime.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseTime.Visible)
                    {
                        erMatchBaseTime.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(level2EventResourceMatch_func);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            else if (e.Node.Text == "事件-资源空间关联匹配")
            {
                if (erMatchBaseLocation.getClose())
                {
                    erMatchBaseLocation = new Level3EventResourceMatch();
                    if (!erMatchBaseLocation.Visible)
                    {
                        erMatchBaseLocation.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseLocation.Visible)
                    {
                        erMatchBaseLocation.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(level3EventResourceMatch_func);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            else if(e.Node.Text == "MERM_TTL算法")
            {
                if (merm.getClose())
                {
                    merm = new MERM_TTL();
                    if (!merm.Visible)
                    {
                        merm.Show();
                    }
                }
                else
                {
                    if (!merm.Visible)
                    {
                        merm.Show();
                    }
                }
            }
            else if(e.Node.Text == "环境灾害应急监测链")
            {
                ThreadStart childref = new ThreadStart(executeServiceChain);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
        }

        private void executeServiceChain()
        {
            test.MonitorEmergencyTest me = new test.MonitorEmergencyTest();
            me.executeXML();
        }

        private void level3EventResourceMatch_func()
        {
            erMatchBaseLocation.setLabel12TextColor("red");
            erMatchBaseLocation.setLabel12Text("开始事件-资源空间关联匹配");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel6Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12Text("未满足事件-资源空间关联匹配条件，已过滤");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel6Visibility(false);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel2Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12TextColor("blue");
            erMatchBaseLocation.setLabel12Text("满足事件-资源空间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel8Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12Text("满足事件-资源空间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel5Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12Text("满足事件-资源空间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel7Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12Text("满足事件-资源空间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel9Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12TextColor("red");
            erMatchBaseLocation.setLabel12Text("未满足事件-资源空间关联匹配条件，已过滤");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel9Visibility(false);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel10Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseLocation.setLabel12Text("未满足事件-资源空间关联匹配条件，已过滤");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel10Visibility(false);
            erMatchBaseLocation.setLabel12Text("");
            Thread.Sleep(2000);
            erMatchBaseLocation.setLabel12Text("结束事件-资源空间关联匹配");
        }

        private void level2EventResourceMatch_func()
        {
            erMatchBaseTime.setLabel11TextColor("blue");
            erMatchBaseTime.setLabel11Text("开始事件-资源时间关联匹配");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel3Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("满足事件-资源时间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel6Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("满足事件-资源时间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel5Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("满足事件-资源时间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel8Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("满足事件-资源时间关联匹配条件，已保留");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11TextColor("red");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel9Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("未满足事件-资源时间关联匹配条件，已过滤");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel9Visibility(false);
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel10Visibility(true);
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("未满足事件-资源时间关联匹配条件，已过滤");
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel10Visibility(false);
            Thread.Sleep(2000);
            erMatchBaseTime.setLabel11Text("");
            Thread.Sleep(1000);
            erMatchBaseTime.setLabel11Text("结束事件-资源时间关联匹配");
        }

        private void level1EventResourceMatch_func(String type)
        {
           
            erMatchBaseType.setLabel4textColor("red");
            Thread.Sleep(1000);
            erMatchBaseType.setLabel5Text("传感器资源");
            erMatchBaseType.setLabel2Visibility(true);
            Thread.Sleep(2000);
            erMatchBaseType.setLabel4Text("开始事件-资源类型关联匹配");
            Thread.Sleep(2000);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表.");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表..");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表...");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表.");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表..");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表...");
            Thread.Sleep(1000);
            erMatchBaseType.setEventType(type);
            Thread.Sleep(1000);
            erMatchBaseType.setLabel4Text("该资源未在大坝变形监测事件-资源关联表中，已过滤。");
            Thread.Sleep(7000);
            erMatchBaseType.setLabel5Text("");
            erMatchBaseType.setLabel4Text("");
            erMatchBaseType.setLabel2Visibility(false);
            erMatchBaseType.setLabel3Visibility(false);
            Thread.Sleep(3000);
            erMatchBaseType.setLabel4textColor("green");
            erMatchBaseType.setLabel5Text("大坝位移监测信息");
            erMatchBaseType.setLabel8Visibility(true);
            Thread.Sleep(2000);
            erMatchBaseType.setLabel4Text("开始事件-资源类型关联匹配");
            Thread.Sleep(2000);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表.");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表..");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表...");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表.");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表..");
            Thread.Sleep(500);
            erMatchBaseType.setLabel4Text("查询大坝变形监测事件-资源关联表...");
            Thread.Sleep(2000);
            erMatchBaseType.setLabel3Visibility(true);
            Thread.Sleep(3000);
            erMatchBaseType.setLabel4Text("该资源在大坝变形监测事件-资源关联表中，已保留。");
            Thread.Sleep(5000);
            erMatchBaseType.setLabel4Text("结束事件-资源类型关联匹配");
        }
       /*
         按键监听事件
         */
        Form4 form4 = new Form4();
        Form5 form5 = new Form5();
        Form6 form6 = new Form6();
        SlopeImage slope = new SlopeImage();
        AspectImage aspect = new AspectImage();
        WaterAnalyze analyzer = new WaterAnalyze();
        Multispectral_data md = new Multispectral_data();
        SamplingAndAnalyzingData saData = new SamplingAndAnalyzingData();
        private void rssm_main_KeyDown(object sender, KeyEventArgs e)
        {
            //"Ctrl + A"触发进入应急区域阿希金矿事件
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.A)
            {
                userControl11.FlyTo(44.23, 81.62, 3000);
            }
            //"Ctrl + B"触发大坝日常变形常态监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.B)
            {
                //进入大坝监测站所在位置
                userControl11.FlyTo(44.234984, 81.622577, 1000);
                // MessageBox.Show("快捷键");
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
            }
            //"Ctrl + C"触发无人机数据采集
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.C)
            {
                //进入数据采集、传输、处理位置
                userControl11.FlyTo(44.233222, 81.623122, 1700);
                //启动数据采集进度条界面
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (!form31.Visible)
                    {
                        form31.Show();
                    }
                }
                else
                {
                    if (!form31.Visible)
                    {
                        form31.Show();
                    }
                }
                if (form31.isRunning1())
                {
                    form31.stopProcess1();
                }
                else
                {
                    form31.startProcess1();
                }

                //无人机、车辆、救援人员移动
                this.userControl11.DoPreLineNow_(false);
                this.userControl11.DoPreLineNow2_(false);
                readFlyCoors(@".\line\uav1.txt");
                readCarCoors(@".\line\car.txt");
            }
            //"Ctrl + D"触发手持终端数据采集1
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D)
            {
                if (entry)
                {
                    this.userControl11.ModifyPerson(3);
                }
                DoPreLineNow3(false);
                ReadPersonCoords(@".\line\person1.txt");
                if (backgroundWorker1.IsBusy)
                {
                    backgroundWorker1.CancelAsync();
                }
                else
                {
                    backgroundWorker1.RunWorkerAsync();
                }
            }
            //"Ctrl + E"触发数据传输1
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.E)
            {
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (form31.isRunning2())
                    {
                        form31.stopProcess2();
                    }
                    else
                    {
                        form31.startProcess2();
                    }

                }
                else
                {
                    if (form31.isRunning2())
                    {
                        form31.stopProcess2();
                    }
                    else
                    {
                        form31.startProcess2();
                    }
                }
                //绘制数据传输链路
                //this.userControl11.DrawLink();
                setCheckBox13(true);
                //调用数据传输程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\ERSSky\bind\ERSSky.exe";
                m_Process.Start();
            }
            //"Ctrl + F"触发数据处理
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.F)
            {
                /*
                 进度条
                 */
                if (form31.getClose())
                {
                    form31 = new Form3();
                    if (form31.isRunning3())
                    {
                        form31.stopProcess3();
                    }
                    else
                    {
                        form31.startProcess3();
                    }
                }
                else
                {

                    if (form31.isRunning3())
                    {
                        form31.stopProcess3();
                    }
                    else
                    {
                        form31.startProcess3();
                    }

                }
                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.Owner = this;
                    form8.Show();
                }
                else
                {
                    form8.Owner = this;
                    form8.Show();
                }
            }
            //"Ctrl + G"触发地物监督分类
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.G)
            {
                //调用地物监督分类程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\supervised_class\Supervisedclass.exe";
                m_Process.Start();
            }
            //"Ctrl + H"触发地物变化检测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.H)
            {
                //调用地物变化检测程序
                Process m_Process = new Process();
                m_Process.StartInfo.FileName = @".\exe\change_detection\ChangeDetection.exe";
                m_Process.Start();
            }
            //"Ctrl + I"显示或隐藏数据传输链路
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.I)
            {
                if (this.checkBox13.CheckState == CheckState.Checked)
                {
                    this.checkBox13.CheckState = CheckState.Unchecked;
                    this.checkBox13.Checked = false;
                }
                else
                {
                    this.checkBox13.CheckState = CheckState.Checked;
                    this.checkBox13.Checked = true;
                }
            }
            //"Ctrl + J"显示或隐藏2015历史高分2影像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.J)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("2015高分2影像", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowImageLayer2015();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideImageLayer2015();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + K"显示或隐藏历史高分2影像分类图
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.K)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("2015高分2影像分类图", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowCliassificationImageLayer2015();
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideCliassificationImageLayer2015();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + L"显示或隐藏历史高光谱影像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.L)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("历史高光谱影像", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowSpectrumImage2018();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumImage2018();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + M"显示或隐藏历史高光谱影像分类图
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.M)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("历史高光谱影像分类图", true);
                if (!nodes[0].Checked)
                {
                    if (form5.getClosed())
                    {
                        form5 = new Form5();
                        form5.Show();
                    }
                    else
                    {
                        form5.Show();
                    }
                    this.userControl11.ShowSpectrumClassificationImage2018();
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!form5.getClosed())
                    {
                        form5.Close();
                    }
                    this.userControl11.HideSpectrumClassificationImage2018();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + N"显示或隐藏航拍正射影像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.N)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("航拍正射影像", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowXinJiangImage();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideXinJiangImage();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + O"显示或隐藏航拍正射影像分类图
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.O)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("航拍正射影像分类图", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowCliassificationImageLayer2017();
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideCliassificationImageLayer2017();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + P"显示或隐藏应急变化分析
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.P)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("应急变化分析", true);
                if (!nodes[0].Checked)
                {
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    this.userControl11.ShowTransferImage();
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideTransferImage();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + Q"显示或隐藏应急高光谱影像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Q)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("应急高光谱影像", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowSpectrumImage2019();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumImage2019();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + R"显示或隐藏应急高光谱影像分类图
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.R)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("应急高光谱影像分类图", true);
                if (!nodes[0].Checked)
                {
                    if (form6.getClosed())
                    {
                        form6 = new Form6();
                        form6.Show();
                    }
                    else
                    {
                        form6.Show();
                    }
                    this.userControl11.ShowSpectrumClassificationImage2019();
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!form6.getClosed())
                    {
                        form6.Close();
                    }
                    this.userControl11.HideSpectrumClassificationImage2019();
                    nodes[0].Checked = false;
                }

            }
            //"Ctrl + S"显示或隐藏高光谱变化检测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.S)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("高光谱精细变化分析", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowSpectrumTransferImage();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumTransferImage();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + T"显示或隐藏终端采集数据
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.T)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("终端采集数据", true);
                if (!nodes[0].Checked)
                {
                    nodes[0].Checked = true;
                }
                else
                {
                    nodes[0].Checked = false;
                }
                Process.Start(@".\excel\采集终端导出数据（2019-01-15--2019-01-16）.csv");
            }
            //"Ctrl + U"传感器常态监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.U)
            {
                //进入传感器所在位置
                userControl11.FlyTo(44.229914, 81.623246, 1000);
                showSensorData();
            }
            //"Ctrl + V"遥感卫星常态监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.V)
            {
                userControl11.FlyTo(44.23, 81.62, 3000);
                //ShowSatelliteData();
            }
            //"Ctrl + W"关闭大坝位移监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.W)
            {
                if (!form9.getClose())
                {
                    form9.Close();
                }
            }
            //"Ctrl + X"关闭传感器常态监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.X)
            {
                if (!form10.getClose())
                {
                    form10.Close();
                }
            }
            //"Ctrl + Y"关闭遥感卫星常态监测
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Y)
            {
                //setCheckBox1(false);

            }
            //"Ctrl + Z"大坝位移超标报警
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Z)
            {
                //进入大坝监测站所在位置
                userControl11.FlyTo(44.234984, 81.622577, 1000);
                //大坝位移超标报警
                //MessageBox.Show("大坝位移超标！", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                if (form11.getClose())
                {
                    form11 = new Form11();
                    if (!form11.Visible)
                    {
                        form11.Show();
                    }
                }
                else
                {
                    if (!form11.Visible)
                    {
                        form11.Show();
                    }
                }
            }
            //"Ctrl + NumPad0"水质污染超标报警
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad0)
            {
                //进入传感器所在位置
                userControl11.FlyTo(44.229914, 81.623246, 1000);
                //MessageBox.Show("水质污染超标！", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                //水质污染超标报警
                if (form12.getClose())
                {
                    form12 = new Form12();
                    if (!form12.Visible)
                    {
                        form12.Show();
                    }
                }
                else
                {
                    if (!form12.Visible)
                    {
                        form12.Show();
                    }
                }
            }
            //"Ctrl + NumPad1"关闭大坝位移超标报警
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad1)
            {
                if (!form11.getClose())
                {
                    form11.Close();
                }
            }
            ////"Ctrl + NumPad2"关闭水质污染超标报警
            //else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad2)
            //{
            //    if (!form12.getClose())
            //    {
            //        form12.Close();
            //    }
            //}
            //"Ctrl + NumPad3"触发水质污染超标事件数据传输链路
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad3)
            {
                //隐藏或显示水质污染超标事件数据传输链路
                if (this.checkBox2.CheckState == CheckState.Checked)
                {
                    this.checkBox2.CheckState = CheckState.Unchecked;
                    this.checkBox2.Checked = false;
                }
                else
                {
                    this.checkBox2.CheckState = CheckState.Checked;
                    this.checkBox2.Checked = true;
                }
            }
            //"Ctrl + NumPad4"触发传感器数据采集
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad4)
            {
                //进入传感器区域
                //userControl11.FlyTo(44.231638, 81.624592, 1000);
                //调出数据采集进度条
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (!form32.Visible)
                    {
                        form32.Show();
                    }
                }
                else
                {
                    if (!form32.Visible)
                    {
                        form32.Show();
                    }
                }
                if (form32.isRunning1())
                {
                    form32.stopProcess1();
                }
                else
                {
                    form32.startProcess1();
                }
                //无人机、车辆、救援人员移动
                this.userControl11.DoPreLineNow2_(false);
                readCarCoors(@".\line\car.txt");
                if (form13.getClose())
                {
                    form13 = new Form13();
                    if (!form13.Visible)
                    {
                        form13.Show();
                    }
                }
                else
                {
                    if (!form13.Visible)
                    {
                        form13.Show();
                    }
                }
            }
            //"Ctrl + NumPad5"触发手持终端数据采集2
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad5)
            {
                //进入数据采集、传输、处理位置
                userControl11.FlyTo(44.228425, 81.623174, 1800);
                //启动救援人员进行数据采集
                if (entry)
                {
                    this.userControl11.ModifyPerson(3);
                }
                DoPreLineNow3(false);
                ReadPersonCoords(@".\line\person1.txt");
                if (backgroundWorker1.IsBusy)
                {
                    backgroundWorker1.CancelAsync();
                }
                else
                {
                    backgroundWorker1.RunWorkerAsync();
                }
            }
            //"Ctrl + NumPad6"触发数据传输2
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad6)
            {

                //数据传输进度条显示
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (form32.isRunning2())
                    {
                        form32.stopProcess2();
                    }
                    else
                    {
                        form32.startProcess2();
                    }

                }
                else
                {
                    if (form32.isRunning2())
                    {
                        form32.stopProcess2();
                    }
                    else
                    {
                        form32.startProcess2();
                    }
                }
                //显示水质污染超标事件数据传输链路
                //if (this.checkBox2.CheckState == CheckState.Checked)
                //{
                //    this.checkBox2.CheckState = CheckState.Unchecked;
                //    this.checkBox2.Checked = false;
                //}
                //else
                //{
                //    this.checkBox2.CheckState = CheckState.Checked;
                //    this.checkBox2.Checked = true;
                //}

            }
            //"Ctrl + NumPad7"触发数据处理2
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad7)
            {
                /*
                 进度条
                 */
                if (form32.getClose())
                {
                    form32 = new Form3();
                    if (form32.isRunning3())
                    {
                        form32.stopProcess3();
                    }
                    else
                    {
                        form32.startProcess3();
                    }
                }
                else
                {

                    if (form32.isRunning3())
                    {
                        form32.stopProcess3();
                    }
                    else
                    {
                        form32.startProcess3();
                    }

                }
                if (form8.getClosed())
                {
                    form8 = new Form8();
                    form8.Owner = this;
                    form8.Show();
                }
                else
                {
                    form8.Owner = this;
                    form8.Show();
                }
            }
            //"Ctrl + NumPad8"触发显示和隐藏2017高分2影像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad8)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("2017高分2影像", true);
                if (!nodes[0].Checked)
                {
                    this.userControl11.ShowImageLayer2017();
                    nodes[0].Checked = true;
                }
                else
                {
                    this.userControl11.HideImageLayer2017();
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + NumPad9"触发无人机图像
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad9)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("无人机影像", true);
                if (!nodes[0].Checked)
                {
                    if (uav_image.getClosed())
                    {
                        uav_image = new UAV_Image();
                        if (!uav_image.Visible)
                        {
                            uav_image.Show();
                        }
                    }
                    else
                    {
                        if (!uav_image.Visible)
                        {
                            uav_image.Show();
                        }
                    }
                    nodes[0].Checked = true;
                }
                else
                {
                    if (!uav_image.getClosed())
                    {
                        uav_image.Close();
                    }
                    nodes[0].Checked = false;
                }

                ThreadStart childref = new ThreadStart(CallToChildThread);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + 0"触发显示和隐藏多光谱信息
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D0)
            {
                md.setImgIndex(1);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            //"Ctrl + 1"触发显示和隐藏现场照片
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D1)
            {
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(CallToChildThread2);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + 2"触发显示和隐藏传感器数据
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D2)
            {
                //在窗口中显示数据
                showSensorData();

                //显示Excel数据
                Process.Start(@".\excel\传感器监测数据.csv");
            }
            //"Ctrl + 3"触发显示和隐藏监测站实时信息
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D3)
            {
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(CallToChildThread3);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + 4"触发关闭数据处理框、应急进度框、移除数据传输链路
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D4)
            {
                if (!form31.getClose())
                {
                    form31.Close();
                    userControl11.HideLink();
                }
                if (!form32.getClose())
                {
                    form32.Close();
                    userControl11.HideSensorNetwork();
                }
                if (!form8.getClosed())
                {
                    form8.Close();
                }
            }
            //"Ctrl + 5"触发启动传感器数据采集
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D5)
            {
                if (form13.getClose())
                {
                    form13 = new Form13();
                    form13.Start_Or_End_Sensor();
                }
                else
                {
                    form13.Start_Or_End_Sensor();
                }
            }
            //"Ctrl + 6"触发关闭传感器数据采集框
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D6)
            {
                if (!form13.getClose())
                {
                    form13.Close();
                }
            }
            //"Ctrl + 7"触发显示水质分析报告
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D7)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("水质分析", true);
                if (!nodes[0].Checked)
                {
                    
                    if (saData.getClosed())
                    {
                        saData = new SamplingAndAnalyzingData();
                        saData.setDataType("water");
                        if (!saData.Visible)
                        {
                            saData.Show();
                        }
                    }
                    else
                    {
                        saData.setDataType("water");
                        if (!saData.Visible)
                        {
                            saData.Show();
                        }
                    }
                }
            }
            //"Ctrl + 8"触发关闭水质分析报告
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D8)
            {
                TreeNode[] nodes = treeView2.Nodes.Find("水质分析", true);
                if (nodes[0].Checked)
                {
                    if (!saData.getClosed())
                    {
                        saData.Close();
                    }
                    nodes[0].Checked = false;
                }
            }
            //"Ctrl + 9"触发显示 事件-资源表 常态监测部分
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.D9)
            {
                //
                if (eraTable.getClose())
                {
                    eraTable = new EventResourceAssociationTable();
                    if (!eraTable.Visible)
                    {
                        eraTable.Show();
                    }
                }
                else
                {
                    if (!eraTable.Visible)
                    {
                        eraTable.Show();
                    }
                }
            }
            //"Ctrl + Enter"触发显示 事件-资源表 应急响应模块
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Enter)
            {
                eraTable.setTabPageSelectedIndex(1);
            }
            //"Ctrl + End"触发显示 dam_monitor 事件-资源匹配算法类型关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.End)
            {
                //if (!eraTable.getClose())
                //{
                //    eraTable.Close();
                //}
                if (erMatchBaseType.getClose())
                {
                    erMatchBaseType = new Level1EventResourceMatch();
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(delegate () { level1EventResourceMatch_func("dam_monitor"); });
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + pageUp"触发显示
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.PageUp)
            {
                
            }
            //"Ctrl + delete"触发显示 water_monitor 事件-资源匹配算法类型关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.NumPad2)
            {
                if (erMatchBaseType.getClose())
                {
                    erMatchBaseType = new Level1EventResourceMatch();
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(delegate () { level1EventResourceMatch_func("water_monitor"); });
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + pageDown"触发关闭事件-资源匹配算法类型关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.PageDown)
            {
                //if (!erMatchBaseType.getClose())
                //{
                //    erMatchBaseType.Close();
                //}
                
            }
            //"Ctrl + +"触发显示事件-资源匹配算法时间关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Add)
            {
                if (erMatchBaseTime.getClose())
                {
                    erMatchBaseTime = new Level2EventResourceMatch();
                    if (!erMatchBaseTime.Visible)
                    {
                        erMatchBaseTime.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseTime.Visible)
                    {
                        erMatchBaseTime.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(level2EventResourceMatch_func);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + -"触发显示 dam_response 事件-资源匹配算法类型关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Subtract)
            {
                //if(!erMatchBaseTime.getClose())
                //{
                //    erMatchBaseTime.Close();
                //}
                if (erMatchBaseType.getClose())
                {
                    erMatchBaseType = new Level1EventResourceMatch();
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(delegate () { level1EventResourceMatch_func("dam_response"); });
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + *"触发显示事件资源匹配算法空间关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Multiply)
            {
                if (erMatchBaseLocation.getClose())
                {
                    erMatchBaseLocation = new Level3EventResourceMatch();
                    if (!erMatchBaseLocation.Visible)
                    {
                        erMatchBaseLocation.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseLocation.Visible)
                    {
                        erMatchBaseLocation.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(level3EventResourceMatch_func);
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + /"触发显示 water_response 事件-资源匹配算法类型关联匹配
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Divide)
            {
                //if (!erMatchBaseLocation.getClose())
                //{
                //    erMatchBaseLocation.Close();
                //}
                if (erMatchBaseType.getClose())
                {
                    erMatchBaseType = new Level1EventResourceMatch();
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                else
                {
                    if (!erMatchBaseType.Visible)
                    {
                        erMatchBaseType.Show();
                    }
                }
                ThreadStart childref = new ThreadStart(delegate () { level1EventResourceMatch_func("water_response"); });
                Thread childThread = new Thread(childref);
                childThread.Start();
            }
            //"Ctrl + Oem-"触发
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.OemMinus)
            {
                MessageBox.Show("OemMinus");
            }
            //"Ctrl + Oem+"触发
            else if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Oemplus)
            {
                MessageBox.Show("Oemplus");
            }
        }

        private  void CallToChildThread()
        {
            try
            {

                Console.WriteLine("Child thread starts");
                int index = 2;
                while (index < 264)
                {
                    Thread.Sleep(100);
                    uav_image.setImgIndex(index);
                    index += 1;
                }
                Console.WriteLine("Child Thread Completed");

            }
            catch (ThreadAbortException e)
            {
                Console.WriteLine("Thread Abort Exception");
            }
            finally
            {
                Console.WriteLine("Couldn't catch the Thread Exception");
            }

        }

        public void CallToChildThread2()
        {
            try
            {

                Console.WriteLine("Child thread starts");
                int index = 2;
                while (index < 6)
                {
                    Thread.Sleep(1000);
                    md.setImgIndex(index);
                    index += 1;
                }
                Console.WriteLine("Child Thread Completed");

            }
            catch (ThreadAbortException e)
            {
                Console.WriteLine("Thread Abort Exception");
            }
            finally
            {
                Console.WriteLine("Couldn't catch the Thread Exception");
            }

        }

        public void CallToChildThread3()
        {
            try
            {

                Console.WriteLine("Child thread starts");
                int index = 2;
                while (index < 4)
                {
                    Thread.Sleep(1000);
                    form9.setImgIndex(index);
                    index += 1;
                }
                Console.WriteLine("Child Thread Completed");

            }
            catch (ThreadAbortException e)
            {
                Console.WriteLine("Thread Abort Exception");
            }
            finally
            {
                Console.WriteLine("Couldn't catch the Thread Exception");
            }

        }

        /**
         *TreeView：用于实现数据资源的管理
         */
        private void treeView2_AfterSelect(object sender, TreeViewEventArgs e)
        {
            //显示和隐藏2015高分2影像
            if(e.Node.Text == "历史高分2影像")
            {
                if (!e.Node.Checked)
                {
                    this.userControl11.ShowImageLayer2015();
                    e.Node.Checked = true;
                }else
                {
                    this.userControl11.HideImageLayer2015();
                    e.Node.Checked = false;
                }
            }
            //显示和隐藏2017高分2影像
            else if(e.Node.Text=="近期高分2影像")
            {
                if(!e.Node.Checked)
                {
                    this.userControl11.ShowImageLayer2017();
                    e.Node.Checked = true;
                }
                else
                {
                    this.userControl11.HideImageLayer2017();
                    e.Node.Checked = false;
                }
            }
            //显示和隐藏历史高光谱数据
            else if(e.Node.Text=="历史高光谱影像")
            {
                if (!e.Node.Checked)
                {
                    this.userControl11.ShowSpectrumImage2018();
                    e.Node.Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumImage2018();
                    e.Node.Checked = false;
                }
            }
            //显示和隐藏应急高光谱影像
            else if (e.Node.Text == "实时高光谱影像")
            {
                if (!e.Node.Checked)
                {
                    this.userControl11.ShowSpectrumImage2019();
                    e.Node.Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumImage2019();
                    e.Node.Checked = false;
                }
            }
            //显示和隐藏2015高分2影像分类图
            else if(e.Node.Text == "历史高分2影像地物覆盖分类图")
            {
                if(!e.Node.Checked)
                {
                    this.userControl11.ShowCliassificationImageLayer2015();
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    e.Node.Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideCliassificationImageLayer2015();
                    e.Node.Checked = false;
                }
            }
            //显示和隐藏航拍正射影像分类图
            else if(e.Node.Text == "近期高分2影像地物覆盖分类图")
            {
                if(!e.Node.Checked)
                {
                    this.userControl11.ShowCliassificationImageLayer2017();
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    e.Node.Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideCliassificationImageLayer2017();
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "历史高光谱影像地物分类图")
            {
                if (!e.Node.Checked)
                {
                    if (form5.getClosed())
                    {
                        form5 = new Form5();
                        form5.Show();
                    }
                    else
                    {
                        form5.Show();
                    }
                    this.userControl11.ShowSpectrumClassificationImage2018();
                    e.Node.Checked = true;
                }
                else
                {
                    if (!form5.getClosed())
                    {
                        form5.Close();
                    }
                    this.userControl11.HideSpectrumClassificationImage2018();
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "实时高光谱影像地物分类图")
            {
                if (!e.Node.Checked)
                {
                    if (form6.getClosed())
                    {
                        form6 = new Form6();
                        form6.Show();
                    }
                    else
                    {
                        form6.Show();
                    }
                    this.userControl11.ShowSpectrumClassificationImage2019();
                    e.Node.Checked = true;
                }
                else
                {
                    if (!form6.getClosed())
                    {
                        form6.Close();
                    }
                    this.userControl11.HideSpectrumClassificationImage2019();
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "初步地物覆盖变化检测信息")
            {
                if (!e.Node.Checked)
                {
                    if (form4.getClosed())
                    {
                        form4 = new Form4();
                        form4.Show();
                    }
                    else
                    {
                        form4.Show();
                    }
                    this.userControl11.ShowTransferImage();
                    e.Node.Checked = true;
                }
                else
                {
                    if (!form4.getClosed())
                    {
                        form4.Close();
                    }
                    this.userControl11.HideTransferImage();
                    e.Node.Checked = false;
                }
            }
            else if (e.Node.Text == "尾矿坝坡度信息")
            {
                if (!e.Node.Checked)
                {
                    if (slope.getClosed())
                    {
                        slope = new SlopeImage();
                        slope.Show();
                    }
                    else
                    {
                        slope.Show();
                    }
                    this.userControl11.ShowSlopeImage();
                    e.Node.Checked = true;
                }
                else
                {
                    if (!slope.getClosed())
                    {
                        slope.Close();
                    }
                    this.userControl11.HideSlopeImage();
                    e.Node.Checked = false;
                }
            }
            else if (e.Node.Text == "尾矿坝坡向信息")
            {
                if (!e.Node.Checked)
                {
                    if (aspect.getClosed())
                    {
                        aspect = new AspectImage();
                        aspect.Show();
                    }
                    else
                    {
                        aspect.Show();
                    }
                    this.userControl11.ShowAspectImage();
                    e.Node.Checked = true;
                }
                else
                {
                    if (!aspect.getClosed())
                    {
                        aspect.Close();
                    }
                    this.userControl11.HideAspectImage();
                    e.Node.Checked = false;
                }
            }
            else if (e.Node.Text == "水质采样分析结果")
            {
                if (!e.Node.Checked)
                {
                    if (analyzer.getClosed())
                    {
                        analyzer = new WaterAnalyze();
                        analyzer.Show();
                    }
                    else
                    {
                        analyzer.Show();
                    }
                    e.Node.Checked = true;
                }
                else
                {
                    if (!analyzer.getClosed())
                    {
                        analyzer.Close();
                    }
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "高光谱精细地物覆盖变化检测信息")
            {
                if(!e.Node.Checked)
                {
                    this.userControl11.ShowSpectrumTransferImage();
                    e.Node.Checked = true;
                }
                else
                {
                    this.userControl11.HideSpectrumTransferImage();
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "IMG1")
            {
                uav_image.setImgIndex(1);
                if (uav_image.getClosed())
                {
                    uav_image = new UAV_Image();
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
                else
                {
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
            }
            else if (e.Node.Text == "IMG2")
            {
                uav_image.setImgIndex(2);
                if (uav_image.getClosed())
                {
                    uav_image = new UAV_Image();
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
                else
                {
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
            }
            else if (e.Node.Text == "IMG3")
            {
                uav_image.setImgIndex(3);
                if (uav_image.getClosed())
                {
                    uav_image = new UAV_Image();
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
                else
                {
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
            }
            else if (e.Node.Text == "IMG4")
            {
                uav_image.setImgIndex(4);
                if (uav_image.getClosed())
                {
                    uav_image = new UAV_Image();
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
                else
                {
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
            }
            else if (e.Node.Text == "IMG5")
            {
                uav_image.setImgIndex(5);
                if (uav_image.getClosed())
                {
                    uav_image = new UAV_Image();
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
                else
                {
                    if (!uav_image.Visible)
                    {
                        uav_image.Show();
                    }
                }
            }
            else if(e.Node.Text == "航拍正射影像")
            {
                if (!e.Node.Checked)
                {
                    this.userControl11.ShowXinJiangImage();
                    e.Node.Checked = true;
                }
                else
                {
                    this.userControl11.HideXinJiangImage();
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "红色废渣MS")
            {
                md.setImgIndex(1);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "碎石路MS")
            {
                md.setImgIndex(2);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }

            }
            else if (e.Node.Text == "水体MS")
            {
                md.setImgIndex(3);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "紫苏MS")
            {
                md.setImgIndex(4);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }

            }
            else if (e.Node.Text == "泥土MS")
            {
                md.setImgIndex(5);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }

            }
            else if (e.Node.Text == "红色废渣IM")
            {
                md.setImgIndex(1);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "碎石路IM")
            {
                md.setImgIndex(2);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "水体IM")
            {
                md.setImgIndex(3);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "紫苏IM")
            {
                md.setImgIndex(4);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if (e.Node.Text == "泥土IM")
            {
                md.setImgIndex(5);
                if (md.getClosed())
                {
                    md = new Multispectral_data();
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
                else
                {
                    if (!md.Visible)
                    {
                        md.Show();
                    }
                }
            }
            else if(e.Node.Text =="终端采集数据")
            {
                if (!e.Node.Checked)
                {
                    Process.Start(@".\excel\采集终端导出数据（2019-01-15--2019-01-16）.csv");
                    e.Node.Checked = true;
                }
                else
                {
                    e.Node.Checked = false;
                }
            }
            else if(e.Node.Text == "传感器数据")
            {
                if (!e.Node.Checked)
                {
                    //在窗口中显示数据
                    showSensorData();

                    //显示Excel数据
                    Process.Start(@".\excel\传感器监测数据.csv");
                    e.Node.Checked = true;
                }
                else
                {
                    e.Node.Checked = false;
                }
                
            }
            else if(e.Node.Text == "水质传感器数据")
            {
                if (!e.Node.Checked)
                {
                    
                    if (saData.getClosed())
                    {
                        saData = new SamplingAndAnalyzingData();
                        saData.setDataType("water");
                        if (!saData.Visible)
                        {
                            saData.Show();
                        }
                    }
                    else
                    {
                        if (!saData.Visible)
                        {
                            saData.Show();
                        }
                    }
                    e.Node.Checked = true;
                }
                else
                {
                    if (!saData.getClosed())
                    {
                        saData.Close();
                    }
                    e.Node.Checked = false;
                }
                
            }
            else if(e.Node.Text == "监测站实时信息1")
            {
                form9.setImgIndex(1);
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
            }
            else if(e.Node.Text == "监测站实时信息2")
            {
                form9.setImgIndex(2);
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
            }
            else if(e.Node.Text == "监测站实时信息3")
            {
                form9.setImgIndex(3);
                if (form9.getClose())
                {
                    form9 = new Form9();
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
                else
                {
                    if (!form9.Visible)
                    {
                        form9.Show();
                    }
                }
            }
        }
        

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
            {
                this.userControl11.AddSensorNetwork();
            }
            else
            {
                this.userControl11.HideSensorNetwork();
            }
        }
        

        private void checkBox13_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox13.Checked)
            {
                this.userControl11.DrawLink();
            }else
            {
                this.userControl11.HideLink();
            }
        }

        //设置CheckBox选中与未选中
        
        public void setCheckBox2(bool entry)
        {
            if (entry)
            {
                this.checkBox2.CheckState = CheckState.Checked;
                this.checkBox2.Checked = true;
            }
            else
            {
                this.checkBox2.CheckState = CheckState.Unchecked;
                this.checkBox2.Checked = false;
            }
        }

        public void setCheckBox13(bool entry)
        {
            if (entry)
            {
                this.checkBox13.CheckState = CheckState.Checked;
                this.checkBox13.Checked = true;
            }
            else
            {
                this.checkBox13.CheckState = CheckState.Unchecked;
                this.checkBox13.Checked = false;
            }
        }

        
        
        bool entry = false;
        private void backgroundWorker1_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
         
            for (int i = 0; i <= 100; i++)
            {
                if (backgroundWorker1.CancellationPending)
                {
                    e.Cancel = true; //这里才真正取消 
                    return;
                }
                Thread.Sleep(500);
                if (i == 17)
                {
                    DoPreLineNow3(false);
                    ReadPersonCoords(@".\line\person2.txt");
                }
                else if (i == 32)
                {
                    DoPreLineNow3(false);
                    ReadPersonCoords(@".\line\person3.txt");
                }
                else if (i == 47)
                {
                    DoPreLineNow3(false);
                    ReadPersonCoords(@".\line\person4.txt");
                }
                else if (i == 70)
                {
                    DoPreLineNow3(false);
                    ReadPersonCoords(@".\line\person5.txt");
                }
                else if(i == 90)
                {
                    DoPreLineNow3(false);
                    this.userControl11.ModifyPerson(4);
                    entry = true;
                }
            }

        }

        private void backgroundWorker1_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
        {
            
        }
        bool entry2 = false;
        private void backgroundWorker1_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                //调用显示采集点
                if (!entry2)
                {
                    addTerrain();
                    addPersonPoint();
                    entry2 = true;
                }
            }
        }

        //图层的显示与隐藏事件
        public void ShowCliassificationImageLayer2015()
        {
            this.userControl11.ShowCliassificationImageLayer2015();

        }

        public void ShowCliassificationImageLayer2017()
        {
            this.userControl11.ShowCliassificationImageLayer2017();
        }

        public void ShowImageLayer2015()
        {
            this.userControl11.ShowImageLayer2015();
        }

        public void ShowImageLayer2017()
        {
            this.userControl11.ShowImageLayer2017();
        }

        public void ShowTransferImage()
        {
            this.userControl11.ShowTransferImage();
        }

        public void ShowPollutionImage()
        {
            this.userControl11.ShowPollutionImage();
        }

        public void ShowXinJiangImage()
        {
            this.userControl11.ShowXinJiangImage();
        }

        public void HideCliassificationImageLayer2015()
        {
            this.userControl11.HideCliassificationImageLayer2015();
        }

        public void HideCliassificationImageLayer2017()
        {
            this.userControl11.HideCliassificationImageLayer2017();
        }

        public void HideImageLayer2015()
        {
            this.userControl11.HideImageLayer2015();
        }

        public void HideImageLayer2017()
        {
            this.userControl11.HideImageLayer2017();
        }

        public void HideTransferImage()
        {
            this.userControl11.HideTransferImage();
        }

        public void HidePollutionImage()
        {
            this.userControl11.HidePollutionImage();
        }

        public void HideXinJiangImage()
        {
            this.userControl11.HideXinJiangImage();
        }

        public void ShowSpectrumImage2018()
        {
            this.userControl11.ShowSpectrumImage2018();
        }

        public void HideSpectrumImage2018()
        {
            this.userControl11.HideImageLayer2015();
        }

        public void ShowSpectrumImage2019()
        {
            this.userControl11.ShowSpectrumImage2019();
        }

        public void HideSpectrumImage2019()
        {
            this.userControl11.HideSpectrumImage2019();
        }

        public void ShowSpectrumClassificationImage2018()
        {
            this.userControl11.ShowSpectrumClassificationImage2018();
        }

        public void HideSpectrumClassificationImage2018()
        {
            this.userControl11.HideSpectrumClassificationImage2018();
        }

        public void ShowSpectrumClassificationImage2019()
        {
            this.userControl11.ShowSpectrumClassificationImage2019();
        }

        public void HideSpectrumClassificationImage2019()
        {
            this.userControl11.HideSpectrumClassificationImage2019();
        }

        public void ShowSpectrumTransferImage()
        {
            this.userControl11.ShowSpectrumTransferImage();
        }

        public void HideSpectrumTransferImage()
        {
            this.userControl11.HideSpectrumTransferImage();
        }

        
    }
}
