#pragma once
#include <osgGA\GUIEventHandler>
#include <osgEarth\SpatialReference>
#include <osgViewer\Viewer>

class PickHandle : public osgGA::GUIEventHandler
{
public:
	PickHandle(const osgEarth::SpatialReference* srs);
	~PickHandle();
	friend std::string DoubleToStringByStringStream(double value);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa);

private:
	osg::Vec3d getPos(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa, osg::Vec3d& pos);

	// ��γ����Ϣ
	//void signalPicked(osg::Vec3d pos);
	//void signalMoving(osg::Vec3d pos);

	// ����������Ϣ
	//void signalPickedXYZ(osg::Vec3d pos);
	//void signalMovingXYZ(osg::Vec3d pos);

	//void signalRightPicked();

private:
	osg::Vec3d m_vecPostion;
	const osg::EllipsoidModel* m_pEllipsoid;
};