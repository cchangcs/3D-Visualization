using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using System.Security;
using System.Security.Permissions;


namespace HelloWorl
{
    [Guid("F742E011-3467-4447-B069-C5BF3D148EF8")]
    public partial class UserControl1 : UserControl,IObjectSafety
    {
        public UserControl1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        #region IObjectSafety 成员

        private const string _IID_IDispatch = "{00020400-0000-0000-C000-000000000046}";
        private const string _IID_IDispatchEx = "{a6ef9860-c720-11d0-9337-00a0c90dcaa9}";
        private const string _IID_IPersistStorage = "{0000010A-0000-0000-C000-000000000046}";
        private const string _IID_IPersistStream = "{00000109-0000-0000-C000-000000000046}";
        private const string _IID_IPersistPropertyBag = "{37D84F60-42CB-11CE-8135-00AA004BB851}";

        private const int INTERFACESAFE_FOR_UNTRUSTED_CALLER = 0x00000001;
        private const int INTERFACESAFE_FOR_UNTRUSTED_DATA = 0x00000002;
        private const int S_OK = 0;
        private const int E_FAIL = unchecked((int)0x80004005);
        private const int E_NOINTERFACE = unchecked((int)0x80004002);

        private bool _fSafeForScripting = true;
        private bool _fSafeForInitializing = true;

        public int GetInterfaceSafetyOptions(ref Guid riid, ref int pdwSupportedOptions, ref int pdwEnabledOptions)
        {
            int Rslt = E_FAIL;

            string strGUID = riid.ToString("B");
            pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
            switch (strGUID)
            {
                case _IID_IDispatch:
                case _IID_IDispatchEx:
                    Rslt = S_OK;
                    pdwEnabledOptions = 0;
                    if (_fSafeForScripting == true)
                        pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
                    break;
                case _IID_IPersistStorage:
                case _IID_IPersistStream:
                case _IID_IPersistPropertyBag:
                    Rslt = S_OK;
                    pdwEnabledOptions = 0;
                    if (_fSafeForInitializing == true)
                        pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
                    break;
                default:
                    Rslt = E_NOINTERFACE;
                    break;
            }

            return Rslt;
        }

        public int SetInterfaceSafetyOptions(ref Guid riid, int dwOptionSetMask, int dwEnabledOptions)
        {
            int Rslt = E_FAIL;
            string strGUID = riid.ToString("B");
            switch (strGUID)
            {
                case _IID_IDispatch:
                case _IID_IDispatchEx:
                    if (((dwEnabledOptions & dwOptionSetMask) == INTERFACESAFE_FOR_UNTRUSTED_CALLER) && (_fSafeForScripting == true))
                        Rslt = S_OK;
                    break;
                case _IID_IPersistStorage:
                case _IID_IPersistStream:
                case _IID_IPersistPropertyBag:
                    if (((dwEnabledOptions & dwOptionSetMask) == INTERFACESAFE_FOR_UNTRUSTED_DATA) && (_fSafeForInitializing == true))
                        Rslt = S_OK;
                    break;
                default:
                    Rslt = E_NOINTERFACE;
                    break;
            }

            return Rslt;
        }

        #endregion

          public void showTime()
        {
            MessageBox.Show(DateTime.Now.ToString());
        }

      

        //public string getKey()
        //{
        //    return IEncryKey.EncryKeyTool.getHaspID();

        //}
        //  [DllImport(@"digitalEarthHZHOsgEarthCore.dll", EntryPoint = "osgRunCow", CallingConvention = CallingConvention.Cdecl), SecuritySafeCritical]
        // private static extern int osgRunCow(IntPtr m_hWnd);
        [DllImport(@"osgCore.dll", EntryPoint = "osgRun", CallingConvention = CallingConvention.Cdecl), SecuritySafeCritical]
        private static extern int osgRun(IntPtr hWnd, bool isfullscreen, int recwidth, int recheight);
        public void ShowOsgEarth()
        {
            Thread threadOsgEarth = new Thread(new ThreadStart(func));//多开一个线程防止界面假死
            threadOsgEarth.IsBackground = true;
            threadOsgEarth.Priority = ThreadPriority.Normal;
            threadOsgEarth.Start();
            //func();
        }

        private void func()
        {

            try
            {
                //  string output = osgRunCow(this.panel1.Handle).ToString();
                osgRun(this.panel1.Handle, false, 1000, 500);
                //MessageBox.Show(Add(10, 10).ToString());               
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showChinabound", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showChinabound(Boolean isShowChinaBoundary);
        public void ShowChinaBound(Boolean isShowChinaBound)
        {
            showChinabound(isShowChinaBound);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "fillWorld", CallingConvention = CallingConvention.Cdecl)]
        private static extern void fillWorld(Boolean isFillWorld);
        public void FillWorld(Boolean isFilleWorld)
        {
            fillWorld(isFilleWorld);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showDenggao", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showDenggao(Boolean isShowDengGao);
        public void ShowDenggao(Boolean isShowDengGao)
        {
            showDenggao(isShowDengGao);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "flyTo", CallingConvention = CallingConvention.Cdecl)]
        private static extern void flyTo(double flylat, double flylon, double flyhei);
        public void FlyTo(double flylat, double flylon, double flyhei)
        {
            flyTo(flylat, flylon, flyhei);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "trackFly", CallingConvention = CallingConvention.Cdecl)]
        private static extern void trackFly(Boolean isTrackFly);
        public void TrackFly(Boolean isTrackFly)
        {
            trackFly(isTrackFly);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "trackCar", CallingConvention = CallingConvention.Cdecl)]
        private static extern void trackCar(Boolean isTrackCar);
        public void TrackCar(Boolean isTrackCar)
        {
            trackCar(isTrackCar);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "trackPerson", CallingConvention = CallingConvention.Cdecl)]
        private static extern void trackPerson(Boolean isTrackPerson);
        public void TrackPerson(Boolean isTrackPerson)
        {
            trackPerson(isTrackPerson);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "testJu", CallingConvention = CallingConvention.Cdecl)]
        private static extern void testJu(Boolean isTestJu);
        public void TestJu(Boolean isTestJu)
        {
            testJu(isTestJu);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "setFace", CallingConvention = CallingConvention.Cdecl)]
        private static extern void setFace();
        public void SetFace()
        {
            setFace();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "setLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern void setLine();
        public void SetLine()
        {
            setLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "setPoint", CallingConvention = CallingConvention.Cdecl)]
        private static extern void setPoint();
        public void SetPoint()
        {
            setPoint();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "flyXian", CallingConvention = CallingConvention.Cdecl)]
        private static extern void flyXian();
        public void FlyXian()
        {
            flyXian();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "flyYanliang", CallingConvention = CallingConvention.Cdecl)]
        private static extern void flyYanliang();
        public void FlyYanliang()
        {
            flyYanliang();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "flyAirport", CallingConvention = CallingConvention.Cdecl)]
        private static extern void flyAirport();
        public void FlyAirport()
        {
            flyAirport();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "swapStereo", CallingConvention = CallingConvention.Cdecl)]
        private static extern void swapStereo();
        public void SwapStereo()
        {
            swapStereo();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "monitor", CallingConvention = CallingConvention.Cdecl)]
        private static extern void monitor();
        public void Monitor()
        {
            monitor();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "replyFly", CallingConvention = CallingConvention.Cdecl)]
        private static extern void replyFly(Boolean isStartFly);
        public void ReplyFly(Boolean isStartFly)
        {
            replyFly(isStartFly);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "replyCar", CallingConvention = CallingConvention.Cdecl)]
        private static extern void replyCar(Boolean isStartCar);
        public void ReplyCar(Boolean isStartCar)
        {
            replyCar(isStartCar);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "replyPerson", CallingConvention = CallingConvention.Cdecl)]
        private static extern void replyPerson(Boolean isStartPerson);
        public void ReplyPerson(Boolean isStartPerson)
        {
            replyPerson(isStartPerson);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "Add", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Add(int x, int y);
        public int Add_(int x, int y)
        {
            return x + y;
        }

        [DllImport(@"osgCore.dll", EntryPoint = "drawFlyLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void drawFlyLine();
        public void DrawFlyLine()
        {
            drawFlyLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "clearFlyLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void clearFlyLine();
        public void ClearFlyLine()
        {
            clearFlyLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "drawCarLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void drawCarLine();
        public void DrawCarLine()
        {
            drawCarLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "clearCarLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void clearCarLine();
        public void ClearCarLine()
        {
            clearCarLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "drawPersonLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void drawPersonLine();
        public void DrawPersonLine()
        {
            drawPersonLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "clearPersonLine", CallingConvention = CallingConvention.Cdecl)]
        private static extern  void clearPersonLine();
        public void ClearPersonLine()
        {
            clearPersonLine();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "DoPreLineNow", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DoPreLineNow(Boolean isStart);
        public void DoPreLineNow_(Boolean isStart)
        {
            DoPreLineNow(isStart);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "DoPreLineNow2", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DoPreLineNow2(Boolean isStart);
        public void DoPreLineNow2_(Boolean isStart)
        {
            DoPreLineNow2(isStart);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "DoPreLineNow3", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DoPreLineNow3(Boolean isStart);
        public void DoPreLineNow3_(Boolean isStart)
        {
            DoPreLineNow3(isStart);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "readFlyCoords", CallingConvention = CallingConvention.Cdecl)]
        private static extern void readFlyCoords(String filename);
        public void ReadFlyCoords(String filename)
        {
            readFlyCoords(filename);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "readCarCoords", CallingConvention = CallingConvention.Cdecl)]
        private static extern void readCarCoords(String filename);
        public void ReadCarCoords(String filename)
        {
            readCarCoords(filename);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "readPersonCoords", CallingConvention = CallingConvention.Cdecl)]
        private static extern void readPersonCoords(String filename);
        public void ReadPersonCoords(String filename)
        {
            readPersonCoords(filename);
        }
        
        [DllImport(@"osgCore.dll", EntryPoint = "addFLyAndMove", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addFLyAndMove(String filename, bool start);
        public void AddFLyAndMove(String filename, bool start)
        {
            addFLyAndMove(filename, start);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "addCarAndMove", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addCarAndMove(String filename, bool start);
        public void AddCarAndMove(String filename, bool start)
        {
            addCarAndMove(filename, start);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "addPersonAndMove", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addPersonAndMove(String filename, bool start);
        public void AddPersonAndMove(String filename, bool start)
        {
            addPersonAndMove(filename, start);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "drawPollution", CallingConvention = CallingConvention.Cdecl)]
        private static extern void drawPollution();
        public void DrawPollution()
        {
            drawPollution();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "drawLink", CallingConvention = CallingConvention.Cdecl)]
        private static extern void drawLink();
        public void DrawLink()
        {
            drawLink();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showImageLayer2015", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showImageLayer2015();
        public void ShowImageLayer2015()
        {
            showImageLayer2015();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideImageLayer2015", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideImageLayer2015();
        public void HideImageLayer2015()
        {
            hideImageLayer2015();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showImageLayer2017", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showImageLayer2017();
        public void ShowImageLayer2017()
        {
            showImageLayer2017();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideImageLayer2017", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideImageLayer2017();
        public void HideImageLayer2017()
        {
            hideImageLayer2017();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showCliassificationImageLayer2015", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showCliassificationImageLayer2015();
        public void ShowCliassificationImageLayer2015()
        {
            showCliassificationImageLayer2015();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideCliassificationImageLayer2015", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideCliassificationImageLayer2015();
        public void HideCliassificationImageLayer2015()
        {
            hideCliassificationImageLayer2015();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showCliassificationImageLayer2017", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showCliassificationImageLayer2017();
        public void ShowCliassificationImageLayer2017()
        {
            showCliassificationImageLayer2017();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideCliassificationImageLayer2017", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideCliassificationImageLayer2017();
        public void HideCliassificationImageLayer2017()
        {
            hideCliassificationImageLayer2017();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showTransferImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showTransferImage();
        public void ShowTransferImage()
        {
            showTransferImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideTransferImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideTransferImage();
        public void HideTransferImage()
        {
            hideTransferImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showXinJiangImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showXinJiangImage();
        public void ShowXinJiangImage()
        {
            showXinJiangImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideXinJiangImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideXinJiangImage();
        public void HideXinJiangImage()
        {
            hideXinJiangImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showPollutionImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showPollutionImage();
        public void ShowPollutionImage()
        {
            showPollutionImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hidePollutionImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hidePollutionImage();
        public void HidePollutionImage()
        {
            hidePollutionImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showClassLabel", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showClassLabel();
        public void ShowClassLabel()
        {
            showClassLabel();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSpectrumImage2018", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSpectrumImage2018();
        public void ShowSpectrumImage2018()
        {
            showSpectrumImage2018();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSpectrumImage2018", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSpectrumImage2018();
        public void HideSpectrumImage2018()
        {
            hideSpectrumImage2018();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSpectrumImage2019", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSpectrumImage2019();
        public void ShowSpectrumImage2019()
        {
            showSpectrumImage2019();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSpectrumImage2019", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSpectrumImage2019();
        public void HideSpectrumImage2019()
        {
            hideSpectrumImage2019();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSpectrumClassificationImage2018", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSpectrumClassificationImage2018();
        public void ShowSpectrumClassificationImage2018()
        {
            showSpectrumClassificationImage2018();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSpectrumClassificationImage2018", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSpectrumClassificationImage2018();
        public void HideSpectrumClassificationImage2018()
        {
            hideSpectrumClassificationImage2018();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSpectrumClassificationImage2019", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSpectrumClassificationImage2019();
        public void ShowSpectrumClassificationImage2019()
        {
            showSpectrumClassificationImage2019();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSpectrumClassificationImage2019", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSpectrumClassificationImage2019();
        public void HideSpectrumClassificationImage2019()
        {
            hideSpectrumClassificationImage2019();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSpectrumTransferImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSpectrumTransferImage();
        public void ShowSpectrumTransferImage()
        {
            showSpectrumTransferImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showSlopeImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showSlopeImage();
        public void ShowSlopeImage()
        {
            showSlopeImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSlopeImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSlopeImage();
        public void HideSlopeImage()
        {
            hideSlopeImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "showAspectImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void showAspectImage();
        public void ShowAspectImage()
        {
            showAspectImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideAspectImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideAspectImage();
        public void HideAspectImage()
        {
            hideAspectImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSpectrumTransferImage", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSpectrumTransferImage();
        public void HideSpectrumTransferImage()
        {
            hideSpectrumTransferImage();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideLink", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideLink();
        public void HideLink()
        {
            hideLink();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "addTerrain", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addTerrain();
        public void AddTerrain()
        {
            addTerrain();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "addPersonPoint", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addPersonPoint();
        public void AddPersonPoint()
        {
            addPersonPoint();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "modifyPerson", CallingConvention = CallingConvention.Cdecl)]
        private static extern void modifyPerson(int label);
        public void ModifyPerson(int label)
        {
            modifyPerson(label);
        }

        [DllImport(@"osgCore.dll", EntryPoint = "addSensorNetwork", CallingConvention = CallingConvention.Cdecl)]
        private static extern void addSensorNetwork();
        public void AddSensorNetwork()
        {
            addSensorNetwork();
        }

        [DllImport(@"osgCore.dll", EntryPoint = "hideSensorNetwork", CallingConvention = CallingConvention.Cdecl)]
        private static extern void hideSensorNetwork();
        public void HideSensorNetwork()
        {
            hideSensorNetwork();
        }

        private void osgEarthUserControl_Click(object sender, EventArgs e)
        {
            this.Focus();
        }

        private void osgEarthUserControl_Enter(object sender, EventArgs e)
        {
            this.Focus();
        }

        private void osgEarthUserControl_Leave(object sender, EventArgs e)
        {

        }


        private void UserControl1_Load(object sender, EventArgs e)
        {
          //  showOsgEarth();
        }

        

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
        }

    }
}