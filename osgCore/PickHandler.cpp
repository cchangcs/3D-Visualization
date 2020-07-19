#include "stdafx.h"
#include "PickHandler.h"

PickHandle::PickHandle(const osgEarth::SpatialReference* srs)
{
	m_pEllipsoid = srs->getGeodeticSRS()->getEllipsoid();
}

PickHandle::~PickHandle()
{

}

bool PickHandle::handle(const osgGA::GUIEventAdapter& ea,
	osgGA::GUIActionAdapter& aa)
{
	// 存储经纬度信息
	osg::Vec3d vecPos;
	switch (ea.getEventType())
	{
		// 点击事件
	case osgGA::GUIEventAdapter::PUSH:
	{
		osg::Vec3d pos = getPos(ea, aa, vecPos);
		// 鼠标左键
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			m_vecPostion = pos;
		}
		break;
	}

	// 鼠标移动事件
	case osgGA::GUIEventAdapter::MOVE:
	{
		osg::Vec3d pos = getPos(ea, aa, vecPos);
		//signalMoving(vecPos);
		//signalMovingXYZ(pos);
		break;
	}

	// 鼠标释放事件
	case osgGA::GUIEventAdapter::RELEASE:
	{
		osg::Vec3d pos = getPos(ea, aa, vecPos);
		// 鼠标左键
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			 //如果释放的点和点击的点同一，则发送单击事件发生的位置
			if (m_vecPostion == pos && m_vecPostion != osg::Vec3d(0, 0, 0))
			{
				//MessageBox(NULL, "Hi", ("(" + DoubleToStringByStringStream(pos.x()) +", " + DoubleToStringByStringStream(pos.y()) + ")").c_str(), MB_OK);

			}
			/*if ((abs(pos.y() - 44.230737) <= 0.001 && (abs(pos.x() - 81.622435) <= 0.001))
				|| (abs(pos.y() - 44.230899) <= 0.001 && (abs(pos.x() - 81.623091) <= 0.001))
				|| (abs(pos.y() - 44.231213) <= 0.001 && (abs(pos.x() - 81.624043) <= 0.001)))
			{
				MessageBox(NULL, "Hi", "111", MB_OK);
			}*/
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			//signalRightPicked();
		}
		break;
	}
	}

	return false;
}
std::string DoubleToStringByStringStream(double value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

osg::Vec3d PickHandle::getPos(const osgGA::GUIEventAdapter& ea,
	osgGA::GUIActionAdapter& aa, osg::Vec3d& pos)
{
	pos = osg::Vec3d(0, 0, 0);
	osgViewer::Viewer* pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (pViewer == NULL)
	{
		return osg::Vec3d(0, 0, 0);
	}
	// 获取当前点
	osgUtil::LineSegmentIntersector::Intersections intersection;
	double x = ea.getX();
	double y = ea.getY();
	pViewer->computeIntersections(ea.getX(), ea.getY(), intersection);
	osgUtil::LineSegmentIntersector::Intersections::iterator iter
		= intersection.begin();
	if (iter != intersection.end())
	{
		m_pEllipsoid->convertXYZToLatLongHeight(
			iter->getWorldIntersectPoint().x(), iter->getWorldIntersectPoint().y(), iter->getWorldIntersectPoint().z(),
			pos.y(), pos.x(), pos.z());
		pos.x() = osg::RadiansToDegrees(pos.x());
		pos.y() = osg::RadiansToDegrees(pos.y());
		return pos;
	}
	return osg::Vec3d(0, 0, 0);
}