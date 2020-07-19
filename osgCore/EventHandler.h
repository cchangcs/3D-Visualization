#pragma once

#include <osgGA\GUIEventHandler>
#include <osgViewer\Viewer>
#include <osgUtil\LineSegmentIntersector>
#include <osgEarth\MapNode>
#include <osgEarthUtil\Controls>
#include <osgGA\StateSetManipulator>
#include <osgEarthUtil\EarthManipulator>
#include <osgEarthAnnotation\PlaceNode>

class CEventHandler : public osgGA::GUIEventHandler
{
public:
	CEventHandler(void);
	~CEventHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	//���������ģ�ͣ���������������ɵ�����ģ���Ƿ��н���
	osg::Node* IntersectPoint(osg::Vec3 XPosition, osg::Vec3 YPosition, osg::ref_ptr<osg::Node> Node, std::string name);

	osg::Vec3d IntersectPoint(osg::Vec3 XPosition, osg::Vec3 YPosition, osg::ref_ptr<osg::Node> Node);

	void RecoverGeom(osg::Geometry* geom, osg::Vec4 color);

	void isStartTest(bool  isTest);

	double GetDis(osg::Vec3 from, osg::Vec3  to);

	osgEarth::Util::Controls::LabelControl* flyLabel;

public:
	osgEarth::MapNode* mapNode;

	//����������ͼ
	osg::Node* computeIntersect;

	//�ϴε��geom
	osg::Geometry* geomLast;
	osg::Vec4 color;

	//�Ƿ��������ͼ
	bool isPickWorld;

	bool isTestJu;

	//0����δ˫����ʼ���Ծ���
	//1�Ѿ����������
	//2�Ѿ��������յ�
	//
	int jieDuan;

	osg::ref_ptr<osg::Geode> lineStrip;

	osg::Vec3 startPoint;
	osg::Vec3 endPoint;
	osg::ref_ptr<osg::Vec3Array> vectex;
	osg::ref_ptr<osg::Geode> qiuqiu;

	double GetDis(osg::Vec3Array * vec);

	osgGA::StateSetManipulator* stateSetMani;
	int fmeNum;

	//���̣�ָ��
	osg::MatrixTransform* _plate;

public:
	osg::Camera* radar;
	osgEarth::Annotation::PlaceNode* ffLabel;
	osg::MatrixTransform* JQ;
};