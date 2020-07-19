
#include "StdAfx.h"
#include "PickNodeHandler.h"

CPickHandler::CPickHandler(osgViewer::Viewer *viewer) :m_pViewer(viewer)
{
}


CPickHandler::~CPickHandler(void)
{
}

bool CPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch (ea.getEventType())
	{
		case(osgGA::GUIEventAdapter::RELEASE):
		{
			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				pick(ea.getX(), ea.getY());
			}
			return true;
		}
	}

	return false;
}
std::string DoubleToStringByStringStream(float value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

void CPickHandler::pick(float fX, float fY)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (m_pViewer->computeIntersections(fX, fY, intersections))
	{
		auto itr = intersections.begin();
		bool e = true;
		while(itr != intersections.end() && e)
		{
			if (!itr->nodePath.empty())
			{
				const osg::NodePath& np = itr->nodePath;
				int i = np.size() - 1;
				bool entry = true;
				while(i >= 0 && entry)
				{
					osg::ref_ptr<osg::Node> node = dynamic_cast<osg::Node *>(np[i]);
					if (NULL != node && node->getName().compare("baseStation1") == 0)
					{
						entry = false;
						e = false;
						
						//显示图片窗口
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\baseStation.jpg";

						const char *monitorX = ".\\pics\\monitor_data\\1_x.png";
						const char *monitorY = ".\\pics\\monitor_data\\1_y.png";
						const char *monitorH = ".\\pics\\monitor_data\\1_h.png";

						cv::Mat img = cv::imread(srcImageName);
						cv::Mat x_img = cv::imread(monitorX);
						cv::Mat y_img = cv::imread(monitorY);
						cv::Mat h_img = cv::imread(monitorH);

						int rows = img.rows;
						int cols = img.cols;

						cv::resize(x_img, x_img, cv::Size(500, rows / 3));
						cv::resize(y_img, y_img, cv::Size(500, rows / 3));
						cv::resize(h_img, h_img, cv::Size(500, rows / 3));

						cv::Mat dst;
						dst.create(rows, cols + 500, CV_8UC3);

						img.copyTo(dst(cv::Rect(0, 0, img.cols, img.rows)));
						x_img.copyTo(dst(cv::Rect(cols, 0, 500, img.rows / 3)));
						y_img.copyTo(dst(cv::Rect(cols, img.rows / 3, 500, img.rows / 3)));
						h_img.copyTo(dst(cv::Rect(cols, img.rows / 3 * 2, 500, img.rows / 3)));

						cv::namedWindow("监测站1", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("监测站1", dst.cols, dst.rows);
						cv::imshow("监测站1", dst);
						cv::waitKey(0);
						

						//启动HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}else if (NULL != node && node->getName().compare("baseStation2") == 0)
					{
						entry = false;
						e = false;
						/*
						ShExecInfo.lpFile = _T("");
						*/

						//显示图片窗口
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\baseStation.jpg";

						const char *monitorX = ".\\pics\\monitor_data\\2_x.png";
						const char *monitorY = ".\\pics\\monitor_data\\2_y.png";
						const char *monitorH = ".\\pics\\monitor_data\\2_h.png";

						cv::Mat img = cv::imread(srcImageName);
						cv::Mat x_img = cv::imread(monitorX);
						cv::Mat y_img = cv::imread(monitorY);
						cv::Mat h_img = cv::imread(monitorH);

						int rows = img.rows;
						int cols = img.cols;

						cv::resize(x_img, x_img, cv::Size(500, rows / 3));
						cv::resize(y_img, y_img, cv::Size(500, rows / 3));
						cv::resize(h_img, h_img, cv::Size(500, rows / 3));

						cv::Mat dst;
						dst.create(rows, cols + 500, CV_8UC3);

						img.copyTo(dst(cv::Rect(0, 0, img.cols, img.rows)));
						x_img.copyTo(dst(cv::Rect(cols, 0, 500, img.rows / 3)));
						y_img.copyTo(dst(cv::Rect(cols, img.rows / 3, 500, img.rows / 3)));
						h_img.copyTo(dst(cv::Rect(cols, img.rows / 3 * 2, 500, img.rows / 3)));

						cv::namedWindow("监测站2", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("监测站2", dst.cols, dst.rows);
						cv::imshow("监测站2", dst);
						cv::waitKey(0);
						

						//启动HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					
					else if (NULL != node && node->getName().compare("baseStation3") == 0)
					{
						entry = false;
						e = false;

						//显示图片窗口
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\baseStation.jpg";

						const char *monitorX = ".\\pics\\monitor_data\\3_x.png";
						const char *monitorY = ".\\pics\\monitor_data\\3_y.png";
						const char *monitorH = ".\\pics\\monitor_data\\3_h.png";

						cv::Mat img = cv::imread(srcImageName);
						cv::Mat x_img = cv::imread(monitorX);
						cv::Mat y_img = cv::imread(monitorY);
						cv::Mat h_img = cv::imread(monitorH);

						int rows = img.rows;
						int cols = img.cols;

						cv::resize(x_img, x_img, cv::Size(500, rows / 3));
						cv::resize(y_img, y_img, cv::Size(500, rows / 3));
						cv::resize(h_img, h_img, cv::Size(500, rows / 3));

						cv::Mat dst;
						dst.create(rows, cols + 500, CV_8UC3);

						img.copyTo(dst(cv::Rect(0, 0, img.cols, img.rows)));
						x_img.copyTo(dst(cv::Rect(cols, 0, 500, img.rows / 3)));
						y_img.copyTo(dst(cv::Rect(cols, img.rows / 3, 500, img.rows / 3)));
						h_img.copyTo(dst(cv::Rect(cols, img.rows / 3 * 2, 500, img.rows / 3)));

						cv::namedWindow("监测站3", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("监测站3", dst.cols, dst.rows);
						cv::imshow("监测站3", dst);
						cv::waitKey(0);
						

						//启动HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("base") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\base.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("基准站", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("基准站", img.cols, img.rows);
						cv::imshow("基准站", img);
						cv::waitKey(0);
						
						//启动HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("Person2") == 0)
					{
						entry = false;
						e = false;

						//显示图片窗口
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\mobile.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("手持终端", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("手持终端", img.cols, img.rows);
						cv::imshow("手持终端", img);
						cv::waitKey(0);
						//启动HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("T1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\1.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T1.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;
						
						cv::resize(img1, img1, cv::Size(cols, rows)); 
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T1现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T1现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T1现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\2.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T2.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T2现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T2现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T2现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\3.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T3.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T3现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T3现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T3现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\4.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T4.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T4现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T4现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T4现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T5") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\5.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T5.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T5现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T5现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T5现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T6") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\6.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T6.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T6现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T6现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T6现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T7") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\7.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T7.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T7现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T7现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T7现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T8") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\8.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T8.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T8现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T8现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T8现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T9") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\9.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T9.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T9现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T9现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T9现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T10") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\10.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T10.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T10现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T10现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T10现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T11") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\11.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T11.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T11现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T11现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T11现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T12") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\12.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T12.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T12现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T12现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T12现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T13") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\13.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T13.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T13现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T13现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T13现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T14") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\14.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T14.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T14现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T14现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T14现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T15") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\15.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T15.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T15现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T15现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T15现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T16") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\16.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T16.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T16现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T16现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T16现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T17") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\17.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T17.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T17现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T17现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T17现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T18") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\18.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T18.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T18现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T18现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T18现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T19") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\19.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T19.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T19现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T19现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T19现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T20") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\20.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T20.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T20现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T20现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T20现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T21") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\21.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T21.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T21现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T21现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T21现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T22") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\22.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T22.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T22现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T22现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T22现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T23") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\23.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T23.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T23现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T23现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T23现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T24") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\24.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T24.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T24现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T24现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T24现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T25") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\25.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T25.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T25现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T25现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T25现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T26") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\26.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T26.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T26现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T26现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T26现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T27") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\27.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T27.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T27现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T27现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T27现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T28") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\28.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T28.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T28现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T28现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T28现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T29") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\29.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T29.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T29现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T29现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T29现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T30") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\30.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\T30.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("T30现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("T30现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("T30现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("灰绿藜") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\灰绿藜.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\灰绿藜.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("灰绿藜现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("灰绿藜现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("灰绿藜现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("狭叶荨麻") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\狭叶荨麻.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\狭叶荨麻.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("狭叶荨麻现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("狭叶荨麻现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("狭叶荨麻现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("灰绿藜1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\灰绿藜1.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\灰绿藜.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("灰绿藜1现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("灰绿藜1现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("灰绿藜1现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("宾藜") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\宾藜.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\宾藜.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("宾藜现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("宾藜现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("宾藜现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					//else if (NULL != node && node->getName().compare("刺芹") == 0)
					//{
					//	entry = false;
					//	e = false;
					//	std::string node_name = node->getName();
					//	//显示窗口
					//	const char *srcImageName1 = ".\\pics\\scene\\刺芹.jpg";
					//	const char *srcImageName2 = ".\\pics\\spectrum\\刺芹.jpg";
					//	cv::Mat img1 = cv::imread(srcImageName1);
					//	cv::Mat img2 = cv::imread(srcImageName2);
					//	int rows = 400;
					//	int cols = 400;

					//	cv::resize(img1, img1, cv::Size(cols, rows));
					//	cv::resize(img2, img2, cv::Size(cols, rows));

					//	cv::Mat dst;
					//	dst.create(rows, cols * 2, CV_8UC3);

					//	img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
					//	img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
					//	cv::namedWindow("刺芹现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
					//	cv::resizeWindow("刺芹现场图和光谱图片", dst.cols, dst.rows);
					//	cv::imshow("刺芹现场图和光谱图片", dst);
					//	cv::waitKey(0);
					//}
					else if (NULL != node && node->getName().compare("小菊花") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\小菊花.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\小菊花.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("小菊花现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("小菊花现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("小菊花现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("紫苏") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\紫苏.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\紫苏.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("紫苏现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("紫苏现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("紫苏现场图和光谱图片", dst);
						cv::waitKey(0); 
						
					}
					else if (NULL != node && node->getName().compare("水泥块") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\水泥块.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\水泥块.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("水泥块现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("水泥块现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("水泥块现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("水泥板") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\水泥板.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\水泥板.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("水泥板现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("水泥板现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("水泥板现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("土路") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\土路.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\土路.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("土路现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("土路现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("土路现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("碎石路") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\碎石路.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\碎石路.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("碎石路现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("碎石路现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("碎石路现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("泥土") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\泥土.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\泥土.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("泥土现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("泥土现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("泥土现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("黄土") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\黄土.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\黄土.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("黄土现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("黄土现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("黄土现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("红色废渣") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\红色废渣.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\红色废渣.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("红色废渣现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("红色废渣现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("红色废渣现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("Satellite") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\satellite_data\\2015-1.tif";
						cv::Mat img = cv::imread(srcImageName);
						/*
						std::string text = "嘻嘻嘻~你发现了彩蛋，不过并没有什么用！";
						int font_face = cv::FONT_HERSHEY_COMPLEX;
						double font_scale = 2;
						int thickness = 2;
						int baseline;
						//获取文本框的长宽
						cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);

						//将文本框居中绘制
						cv::Point origin;
						origin.x = img.cols / 2 - text_size.width / 2;
						cv::putText(img, text, origin, font_face, font_scale, cv::Scalar(255, 255, 255), thickness, 8, 0);
						*/
						cv::namedWindow("高分1号影像", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("高分1号影像", img.cols, img.rows);
						cv::imshow("高分1号影像", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("水体") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName1 = ".\\pics\\scene\\水体.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\水体.jpg";
						cv::Mat img1 = cv::imread(srcImageName1);
						cv::Mat img2 = cv::imread(srcImageName2);
						int rows = 600;
						int cols = 600;

						cv::resize(img1, img1, cv::Size(cols, rows));
						cv::resize(img2, img2, cv::Size(cols, rows));

						cv::Mat dst;
						dst.create(rows, cols * 2, CV_8UC3);

						img1.copyTo(dst(cv::Rect(0, 0, img1.cols, img1.rows)));
						img2.copyTo(dst(cv::Rect(cols, 0, img2.cols, img2.rows)));
						cv::namedWindow("水体现场图和光谱图片", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("水体现场图和光谱图片", dst.cols, dst.rows);
						cv::imshow("水体现场图和光谱图片", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\1.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("终端采集点1信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("终端采集点1信息", img.cols, img.rows);
						cv::imshow("终端采集点1信息", img);
						cv::waitKey(0);
						 
					}
					else if (NULL != node && node->getName().compare("point2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\2.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("终端采集点2信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("终端采集点2信息", img.cols, img.rows);
						cv::imshow("终端采集点2信息", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\3.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("终端采集点3信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("终端采集点3信息", img.cols, img.rows);

						cv::imshow("终端采集点3信息", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\4.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("终端采集点4信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("终端采集点4信息", img.cols, img.rows);
						cv::imshow("终端采集点4信息", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point5") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\5.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("终端采集点5信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("终端采集点5信息", img.cols, img.rows);
						cv::imshow("终端采集点5信息", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point6") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\point\\水体更新.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("水体更新信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("水体更新信息", img.cols, img.rows);
						cv::imshow("水体更新信息", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\sensor_data\\sensor1.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("1号传感器信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("1号传感器信息", img.cols, img.rows);
						cv::imshow("1号传感器信息", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\sensor_data\\sensor2.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("2号传感器信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("2号传感器信息", img.cols, img.rows);
						cv::imshow("2号传感器信息", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\sensor_data\\sensor4.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("4号传感器信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("4号传感器信息", img.cols, img.rows);
						cv::imshow("4号传感器信息", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\sensor_data\\sensor5.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("5号传感器信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("5号传感器信息", img.cols, img.rows);
						cv::imshow("5号传感器信息", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("dam") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//显示窗口
						const char *srcImageName = ".\\pics\\sensor_data\\sensor3.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("3号传感器信息", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL参数表示用户可以改变窗口大小
						cv::resizeWindow("3号传感器信息", img.cols, img.rows);
						cv::imshow("3号传感器信息", img);
						cv::waitKey(0);

					}

					i -= 1;
				}
			}
			++itr;
		}
	}
}