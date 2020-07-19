#pragma once
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/Viewer>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <process.h>
class CPickHandler : public osgGA::GUIEventHandler
{
public:
	CPickHandler(osgViewer::Viewer *viewer);
	~CPickHandler(void);

	osgViewer::Viewer *m_pViewer;

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	LPCWSTR stringToLPCWSTR(std::string orig);
	void pick(float fX, float fY);
	friend std::string DoubleToStringByStringStream();
};
