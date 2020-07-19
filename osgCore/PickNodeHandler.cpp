
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
						
						//��ʾͼƬ����
						std::string node_name = node->getName();
						//��ʾ����
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

						cv::namedWindow("���վ1", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("���վ1", dst.cols, dst.rows);
						cv::imshow("���վ1", dst);
						cv::waitKey(0);
						

						//����HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}else if (NULL != node && node->getName().compare("baseStation2") == 0)
					{
						entry = false;
						e = false;
						/*
						ShExecInfo.lpFile = _T("");
						*/

						//��ʾͼƬ����
						std::string node_name = node->getName();
						//��ʾ����
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

						cv::namedWindow("���վ2", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("���վ2", dst.cols, dst.rows);
						cv::imshow("���վ2", dst);
						cv::waitKey(0);
						

						//����HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					
					else if (NULL != node && node->getName().compare("baseStation3") == 0)
					{
						entry = false;
						e = false;

						//��ʾͼƬ����
						std::string node_name = node->getName();
						//��ʾ����
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

						cv::namedWindow("���վ3", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("���վ3", dst.cols, dst.rows);
						cv::imshow("���վ3", dst);
						cv::waitKey(0);
						

						//����HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("base") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\base.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("��׼վ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��׼վ", img.cols, img.rows);
						cv::imshow("��׼վ", img);
						cv::waitKey(0);
						
						//����HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("Person2") == 0)
					{
						entry = false;
						e = false;

						//��ʾͼƬ����
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\mobile.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ֳ��ն�", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ֳ��ն�", img.cols, img.rows);
						cv::imshow("�ֳ��ն�", img);
						cv::waitKey(0);
						//����HCDisplay
						//system(".\\exe\\HCDisplay.exe");
					}
					else if (NULL != node && node->getName().compare("T1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T1�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T1�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T1�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T2�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T2�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T2�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T3�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T3�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T3�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T4�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T4�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T4�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T5") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T5�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T5�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T5�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T6") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T6�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T6�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T6�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T7") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T7�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T7�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T7�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T8") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T8�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T8�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T8�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T9") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T9�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T9�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T9�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T10") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T10�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T10�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T10�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T11") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T11�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T11�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T11�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T12") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T12�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T12�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T12�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T13") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T13�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T13�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T13�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T14") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T14�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T14�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T14�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T15") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T15�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T15�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T15�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T16") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T16�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T16�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T16�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T17") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T17�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T17�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T17�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T18") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T18�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T18�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T18�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T19") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T19�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T19�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T19�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T20") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T20�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T20�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T20�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T21") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T21�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T21�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T21�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T22") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T22�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T22�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T22�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T23") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T23�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T23�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T23�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T24") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T24�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T24�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T24�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T25") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T25�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T25�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T25�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T26") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T26�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T26�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T26�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T27") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T27�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T27�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T27�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T28") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T28�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T28�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T28�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T29") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T29�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T29�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T29�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("T30") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
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
						cv::namedWindow("T30�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("T30�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("T30�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("����޼") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\����޼.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\����޼.jpg";
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
						cv::namedWindow("����޼�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("����޼�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("����޼�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("��Ҷݡ��") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\��Ҷݡ��.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\��Ҷݡ��.jpg";
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
						cv::namedWindow("��Ҷݡ���ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��Ҷݡ���ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("��Ҷݡ���ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("����޼1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\����޼1.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\����޼.jpg";
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
						cv::namedWindow("����޼1�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("����޼1�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("����޼1�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("��޼") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\��޼.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\��޼.jpg";
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
						cv::namedWindow("��޼�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��޼�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("��޼�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					//else if (NULL != node && node->getName().compare("����") == 0)
					//{
					//	entry = false;
					//	e = false;
					//	std::string node_name = node->getName();
					//	//��ʾ����
					//	const char *srcImageName1 = ".\\pics\\scene\\����.jpg";
					//	const char *srcImageName2 = ".\\pics\\spectrum\\����.jpg";
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
					//	cv::namedWindow("�����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
					//	cv::resizeWindow("�����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
					//	cv::imshow("�����ֳ�ͼ�͹���ͼƬ", dst);
					//	cv::waitKey(0);
					//}
					else if (NULL != node && node->getName().compare("С�ջ�") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\С�ջ�.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\С�ջ�.jpg";
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
						cv::namedWindow("С�ջ��ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("С�ջ��ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("С�ջ��ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("����") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\����.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\����.jpg";
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
						cv::namedWindow("�����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("�����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0); 
						
					}
					else if (NULL != node && node->getName().compare("ˮ���") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\ˮ���.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\ˮ���.jpg";
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
						cv::namedWindow("ˮ����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("ˮ����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("ˮ����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("ˮ���") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\ˮ���.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\ˮ���.jpg";
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
						cv::namedWindow("ˮ����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("ˮ����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("ˮ����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("��·") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\��·.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\��·.jpg";
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
						cv::namedWindow("��·�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��·�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("��·�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("��ʯ·") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\��ʯ·.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\��ʯ·.jpg";
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
						cv::namedWindow("��ʯ·�ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��ʯ·�ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("��ʯ·�ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("����") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\����.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\����.jpg";
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
						cv::namedWindow("�����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("�����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("����") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\����.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\����.jpg";
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
						cv::namedWindow("�����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("�����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("��ɫ����") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\��ɫ����.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\��ɫ����.jpg";
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
						cv::namedWindow("��ɫ�����ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("��ɫ�����ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("��ɫ�����ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("Satellite") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\satellite_data\\2015-1.tif";
						cv::Mat img = cv::imread(srcImageName);
						/*
						std::string text = "������~�㷢���˲ʵ���������û��ʲô�ã�";
						int font_face = cv::FONT_HERSHEY_COMPLEX;
						double font_scale = 2;
						int thickness = 2;
						int baseline;
						//��ȡ�ı���ĳ���
						cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);

						//���ı�����л���
						cv::Point origin;
						origin.x = img.cols / 2 - text_size.width / 2;
						cv::putText(img, text, origin, font_face, font_scale, cv::Scalar(255, 255, 255), thickness, 8, 0);
						*/
						cv::namedWindow("�߷�1��Ӱ��", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�߷�1��Ӱ��", img.cols, img.rows);
						cv::imshow("�߷�1��Ӱ��", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("ˮ��") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName1 = ".\\pics\\scene\\ˮ��.jpg";
						const char *srcImageName2 = ".\\pics\\spectrum\\ˮ��.jpg";
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
						cv::namedWindow("ˮ���ֳ�ͼ�͹���ͼƬ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("ˮ���ֳ�ͼ�͹���ͼƬ", dst.cols, dst.rows);
						cv::imshow("ˮ���ֳ�ͼ�͹���ͼƬ", dst);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\1.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ն˲ɼ���1��Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ն˲ɼ���1��Ϣ", img.cols, img.rows);
						cv::imshow("�ն˲ɼ���1��Ϣ", img);
						cv::waitKey(0);
						 
					}
					else if (NULL != node && node->getName().compare("point2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\2.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ն˲ɼ���2��Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ն˲ɼ���2��Ϣ", img.cols, img.rows);
						cv::imshow("�ն˲ɼ���2��Ϣ", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\3.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ն˲ɼ���3��Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ն˲ɼ���3��Ϣ", img.cols, img.rows);

						cv::imshow("�ն˲ɼ���3��Ϣ", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\4.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ն˲ɼ���4��Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ն˲ɼ���4��Ϣ", img.cols, img.rows);
						cv::imshow("�ն˲ɼ���4��Ϣ", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point5") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\5.png";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("�ն˲ɼ���5��Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("�ն˲ɼ���5��Ϣ", img.cols, img.rows);
						cv::imshow("�ն˲ɼ���5��Ϣ", img);
						cv::waitKey(0);
						
					}
					else if (NULL != node && node->getName().compare("point6") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\point\\ˮ�����.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("ˮ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("ˮ�������Ϣ", img.cols, img.rows);
						cv::imshow("ˮ�������Ϣ", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river1") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\sensor_data\\sensor1.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("1�Ŵ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("1�Ŵ�������Ϣ", img.cols, img.rows);
						cv::imshow("1�Ŵ�������Ϣ", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river2") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\sensor_data\\sensor2.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("2�Ŵ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("2�Ŵ�������Ϣ", img.cols, img.rows);
						cv::imshow("2�Ŵ�������Ϣ", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river3") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\sensor_data\\sensor4.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("4�Ŵ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("4�Ŵ�������Ϣ", img.cols, img.rows);
						cv::imshow("4�Ŵ�������Ϣ", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("river4") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\sensor_data\\sensor5.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("5�Ŵ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("5�Ŵ�������Ϣ", img.cols, img.rows);
						cv::imshow("5�Ŵ�������Ϣ", img);
						cv::waitKey(0);

					}
					else if (NULL != node && node->getName().compare("dam") == 0)
					{
						entry = false;
						e = false;
						std::string node_name = node->getName();
						//��ʾ����
						const char *srcImageName = ".\\pics\\sensor_data\\sensor3.jpg";
						cv::Mat img = cv::imread(srcImageName);

						cv::namedWindow("3�Ŵ�������Ϣ", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
						cv::resizeWindow("3�Ŵ�������Ϣ", img.cols, img.rows);
						cv::imshow("3�Ŵ�������Ϣ", img);
						cv::waitKey(0);

					}

					i -= 1;
				}
			}
			++itr;
		}
	}
}