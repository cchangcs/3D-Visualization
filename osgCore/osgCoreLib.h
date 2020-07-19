#pragma once
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>		 
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>		 
#include <osg/ShapeDrawable>
#include <osgEarthUtil/Sky>
#include <osgGA/TrackballManipulator>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/MapNode>
#include <osgEarthUtil/Controls>
#include "LabelControlEventHandler.h"
#include "EventHandler.h"

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgEarth/ImageLayer>
#include <osgEarthAnnotation/PlaceNode>
#include <osgUtil\Optimizer>

#include <osgEarthUtil/Controls>
#include <osg/AnimationPath>
#include <osgParticle/FireEffect>
#include <osg/ShapeDrawable>
#include <osgGA\StateSetManipulator>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/FeatureEditing>
#include <osgEarthFeatures/Feature>
#include <string>
#include <osgEarth/ElevationQuery>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarth/Map>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthSymbology/Style>
#include <osgAnimation/BasicAnimationManager>
#include <osg/LineWidth>
#include <osg/DrawPixels>
#include <thread>
#include "UpdateFlood.h"
#include "AnimationManagerFinder.h"
#include "AGGLiteOptions.h"
#include "PickHandler.h"
#include "PickNodeHandler.h"
#include "AnimationEventHandle.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <process.h>

#include<osgEarthDrivers\gdal\GDALOptions>

#include<osgEarthDrivers\colorramp\ColorRampOptions>

#include "UpdateLink.h"

using namespace std;

class TrailerCallback : public osg::NodeCallback
{
public:
	TrailerCallback(osg::Geometry* ribbon, int size)
	{
		_ribbon = ribbon;
		this->size = size;
	}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::MatrixTransform* trans = dynamic_cast<osg::MatrixTransform*>(node);
		if (trans && _ribbon.valid())
		{
			osg::Matrix matrix = trans->getMatrix();
			osg::Vec3Array* vertexs = dynamic_cast<osg::Vec3Array*>(_ribbon->getVertexArray());

			for (unsigned int i = 0; i<size - 3; i += 2)
			{
				(*vertexs)[i] = (*vertexs)[i + 2];
				(*vertexs)[i + 1] = (*vertexs)[i + 3];
			}

			(*vertexs)[size - 2] = osg::Vec3(0.0f, -10, 0.0f)*matrix;
			(*vertexs)[size - 1] = osg::Vec3(0.0f, 10, 0.0f)*matrix;
			vertexs->dirty();
			_ribbon->dirtyBound();
		}
	}

private:
	osg::observer_ptr<osg::Geometry> _ribbon;
	int size;
};


class osgCoreLib
{
public:
	osgCoreLib(HWND hWnd);
	~osgCoreLib(void);
	void setup(bool isfullscreen, int recwidth, int recheight);
    void InitOSG(bool isfullscreen,int recwidth,int recheight);
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	HWND m_hWnd;
	int int_recwidth;
	int int_recheight;

public:
	static void Render(void * ptr);

	void InitOsgEarth();

	osgViewer::Viewer *getViewer();

	void setChinaBoundariesOpacity(double opt);
	double getChinaBoundariesOpacity();
	void rmvChinaBoundaryes();
	void addChinaBoundaryes();

	//�����ر�
	void addLabel();

	//ptr
	//1:ָ��:COSGObject
	//2:ָ��:�ļ���
	//3:����:�ر�����
	static void ReadLabelThread(void * ptr);

	osg::Image* sheng;
	osg::Image* cityCenter;
	osg::Image* city;
	osg::Image* countycity;
	osg::Image* county;
	osg::Image* town;
	osg::Image* vi;
	osgEarth::Style style;

	unsigned int shaanxiParam[3];
	std::string shaanxiTxt;

	unsigned int shanxiParam[3];
	std::string shanxiTxt;

	//unsigned int shaanxiParam[3];
	//std::string shaanxiTxt;
	//
	static void CreateLabelThread(void * ptr);
	unsigned int processI;

	//��������ͼ
	void FillWorld(bool isFill);
	void SetFillWorldTrans(double dfill);

	//�Ƿ���ʾ�ȸ���
	void ShowDengGao(bool isShow);

	//�����ʾ�ӵ���Ϣ�Ŀؼ�
	void addViewPointLabel();
	CLabelControlEventHandler *labelEvent;

	//����
	void FlyTo(double lon, double lat, double hei);

public:
	osg::ref_ptr<osgEarth::MapNode> mapNode;

	//������ͼ��
	osg::ref_ptr<osgEarth::ImageLayer> china_boundaries;
	osg::ref_ptr<osg::Node> world;

	//�ȸ���
	osg::ref_ptr<osg::Node> dengGao;
	bool isShowDengGao;

	//�ر�
	osg::ref_ptr<osg::Group> earthLabel;

	//�Ƿ����
	bool isFillWorld;
	osg::ref_ptr<CEventHandler> eh;

	//�������͸����
	double worldFillTrans;


	//�ر�ľ������
public:
	osg::ref_ptr<osg::CoordinateSystemNode> csn;

public:
	osg::ref_ptr<osg::Node> airport;
	osg::ref_ptr<osg::MatrixTransform> mtAirport;
	//���û���
	void addAirport();

	osg::ref_ptr<osg::Node> flyAirport;
	osg::ref_ptr<osg::MatrixTransform> mtFlySelf;
	osg::ref_ptr<osg::MatrixTransform> mtfly;

public:
	//���õ�·����
	void addCar();

	osg::ref_ptr<osg::Node> car;
	osg::ref_ptr<osg::MatrixTransform> mtCarSelf;
	osg::ref_ptr<osg::MatrixTransform> mtCar;

public:

	void addPerson();

	osg::ref_ptr<osg::Node> person;
	osg::ref_ptr<osg::MatrixTransform> mtPersonSelf;
	osg::ref_ptr<osg::MatrixTransform> mtPerson;

	void addPerson2();

	osg::ref_ptr<osg::Node> person2;
	osg::ref_ptr<osg::MatrixTransform> mtPersonSelf2;
	osg::ref_ptr<osg::MatrixTransform> mtPerson2;

	void modifyPerson(int label);

public:
	//��������Ŀ��Ƶ㣬���һ��·�������Ƶ��ʽΪ������γ���ߣ��٣�
	osg::AnimationPath* CreateAirLinePath(osg::Vec4Array* ctrl);
	osg::AnimationPath* CreateAirLinePath2(osg::Vec4Array* ctrl);
	osg::AnimationPath* CreateAirLinePath3(osg::Vec4Array* ctrl);

	//�����ľ��빫ʽ
	double GetDis(osg::Vec3 from, osg::Vec3 to);

	//�����������Ҫ��ʻ��ʱ��
	double GetRunTime(osg::Vec3 from, osg::Vec3 to, double speed);

	//����һ��Ԥ����·��
	void DoAPreLine();

	//���ɵ�Ԥ����·��
	osg::ref_ptr<osg::AnimationPathCallback> apcFly1;
	osg::ref_ptr<osg::AnimationPathCallback> apcCar;
	osg::ref_ptr<osg::AnimationPathCallback> apcPerson;

	//����Ԥ����·��
	//�ɻ�����
	bool isPathStart;
	void DoPreLineNow(bool isStart);
	//�����ƶ�
	bool isCarStart;
	void DoPreLineNow2(bool isStart);
	// �����ƶ�
	bool isPersonStart;
	void DoPreLineNow3(bool isStart);

	void isTrackFly(bool btrack);

	void isTrackCar(bool btrack);
	//
	void isTrackPerson(bool btrack);
	//Buildβ��
	void BuildTail(osg::Vec3 &position, osg::MatrixTransform* scaler);

	//Buildribbon
	void BuildRibbonFly0(int size, osg::MatrixTransform* scalar);
	osg::ref_ptr<TrailerCallback> tcFly0;
	osg::ref_ptr<osg::Geode> gnodeFly0;
	osg::ref_ptr<osg::Geode> gnodeboud0;

	void BuildRibbonCar(int size, osg::MatrixTransform* scalar);
	osg::ref_ptr<TrailerCallback> tcCar;
	osg::ref_ptr<osg::Geode> gnodeCar;
	osg::ref_ptr<osg::Geode> gnodeboud3;

	void BuildRibbonPerson(int size, osg::MatrixTransform* scalar);
	osg::ref_ptr<TrailerCallback> tcPerson;
	osg::ref_ptr<osg::Geode> gnodePerson;
	osg::ref_ptr<osg::Geode> gnodeboud4;
public:
	//�������
	void isTestJu(bool isTest);

	osgEarth::Util::Controls::LabelControl* flyCoords;
	osg::ref_ptr<osgGA::StateSetManipulator> stateSetMani;

public:
	void setModule(int module);

	void swapStereo();

	void createCompress();

	osg::MatrixTransform* createCompressPart(const std::string& image, float radius, float height);

	//���̣�ָ��
	osg::MatrixTransform* _plate;
	osg::MatrixTransform* _needle;

public:
	osg::ref_ptr<osg::Camera> radar;
	void CreateRadar();
	osg::ref_ptr<osgEarth::Annotation::PlaceNode> airLabel;
	osg::ref_ptr<osgEarth::Annotation::PlaceNode> ffLabel;

public:
	//����ֱ��
	//ʵ�ߵ�Style��Node
	//���˻�
	osgEarth::Symbology::Style m_lineFlyStyle;
	osgEarth::Features::Feature* m_pFlyFeature;
	osgEarth::Annotation::FeatureNode* m_pFlyFeatureNode;

	void drawFlyLine();
	void clearFlyLine();

	//����
	osgEarth::Symbology::Style m_lineCarStyle;
	osgEarth::Features::Feature* m_pCarFeature;
	osgEarth::Annotation::FeatureNode* m_pCarFeatureNode;

	void drawCarLine();
	void clearCarLine();

	//����
	osgEarth::Symbology::Style m_linePersonStyle;
	osgEarth::Features::Feature* m_pPersonFeature;
	osgEarth::Annotation::FeatureNode* m_pPersonFeatureNode;

	void drawPersonLine();
	void clearPersonLine();

	//��ȡ�����ļ�
	void readFlyCoords(char * filename);

	void readCarCoords(char * filename);

	void readPersonCoords(char * filename);
	

	//��ȡ�߳�����
	double query_resolution;
	double out_resolution;
	osgEarth::ElevationQuery *query;

	//���ģ�Ͳ������ƶ�
	void addFLyAndMove(char * filename, bool start);
	void addCarAndMove(char * filename, bool start);
	void addPersonAndMove(char * filename, bool start);
public:
	//�������
	void addSatellite();

	osg::ref_ptr<osg::Node> satellite;
	osg::ref_ptr<osg::MatrixTransform> mtSatelliteSelf;
	osg::ref_ptr<osg::MatrixTransform> mtSatellite;

	osg::ref_ptr<osg::Node> satellite2;
	osg::ref_ptr<osg::MatrixTransform> mtSatelliteSelf2;
	osg::ref_ptr<osg::MatrixTransform> mtSatellite2;

public:
	//�����������
	void addDataCenter();
	
public:
	//���ƺ�ˮ
	void drawFlood();
public:
	//��Ⱦ��ɢ
	void drawPollution();

public:
	osg::ref_ptr<osg::MatrixTransform> mtBaseStation; // mtAirport
	//��ӻ�վ1
	void addBaseStation();
	osg::ref_ptr<osg::Node> baseStation; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation; //mtfly


	osg::ref_ptr<osg::MatrixTransform> mtBaseStation2; // mtAirport
	//��ӻ�վ2
	void addBaseStation2();
	osg::ref_ptr<osg::Node> baseStation2; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf2; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation2; //mtfly

	osg::ref_ptr<osg::MatrixTransform> mtBaseStation3; //mtAirport
	//��ӻ�վ3
	void addBaseStation3();
	osg::ref_ptr<osg::Node> baseStation3; //flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf3; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation3; //mtfly

	//��ӻ�׼վ
	osg::ref_ptr<osg::MatrixTransform> mtBase; //mtAirport
													   
	void addBase();
	osg::ref_ptr<osg::Node> base; //flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mt_base; //mtfly

//����ͨ����·
public:
	osgEarth::Annotation::FeatureNode* m_pLakeFeatureNode;
	osgEarth::Annotation::FeatureNode* m_pLakeFeatureNode2;
	//��ʾ��·
	void drawLink();
	//������·
	void hideLink();
public:
	osgEarth::Map* map;

	osg::ref_ptr<osgEarth::ImageLayer> imageLayer2015;
	void showImageLayer2015();
	void hideImageLayer2015();

	osg::ref_ptr<osgEarth::ImageLayer> imageLayer2017;
	void showImageLayer2017();
	void hideImageLayer2017();

	osg::ref_ptr<osgEarth::ImageLayer> cliassificationImage2015;
	void showCliassificationImageLayer2015();
	void hideCliassificationImageLayer2015();

	osg::ref_ptr<osgEarth::ImageLayer> cliassificationImage2017;
	void showCliassificationImageLayer2017();
	void hideCliassificationImageLayer2017();

	osg::ref_ptr<osgEarth::ImageLayer> transferImage;
	void showTransferImage();
	void hideTransferImage();

	osg::ref_ptr<osgEarth::ImageLayer> xinJiangImage;
	void showXinJiangImage();
	void hideXinJiangImage();

	osg::ref_ptr<osgEarth::ImageLayer> pollutionImage;
	void showPollutionImage();
	void hidePollutionImage();

	osg::ref_ptr<osgEarth::ImageLayer> spectrumImage2018;
	void showSpectrumImage2018();
	void hideSpectrumImage2018();

	osg::ref_ptr<osgEarth::ImageLayer> spectrumImage2019;
	void showSpectrumImage2019();
	void hideSpectrumImage2019();

	osg::ref_ptr<osgEarth::ImageLayer> spectrumClassificationImage2018;
	void showSpectrumClassificationImage2018();
	void hideSpectrumClassificationImage2018();

	osg::ref_ptr<osgEarth::ImageLayer> spectrumClassificationImage2019;
	void showSpectrumClassificationImage2019();
	void hideSpectrumClassificationImage2019();


	osg::ref_ptr<osgEarth::ImageLayer> spectrumTransferImage;
	void showSpectrumTransferImage();
	void hideSpectrumTransferImage();

	osg::ref_ptr<osgEarth::ImageLayer> SlopeImage;
	void showSlopeImage();
	void hideSlopeImage();

	osg::ref_ptr<osgEarth::ImageLayer> AspectImage;
	void showAspectImage();
	void hideAspectImage();
public:
	void addTerrain();

public:
	void addPositionName();

public: //util
	std::wstring String2WString(const std::string& s);
	std::string DoubleToStringByStringStream(float value);

public:
	void addPersonPoint();

public:
	void showClassLabel();

public:
	//��Ӵ�����
	void addSensor();

	//��ʾ��������������
	void addSensorNetwork();

	//���ش�������������
	void hideSensorNetwork();

	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode;
	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode2;
	osg::ref_ptr<osg::Node> sensor;
	osg::ref_ptr<osg::MatrixTransform> mtSensorSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtSensor; //mtfly
public:
	//��ʾ�������ݡ���>ֱ�ӵ��Ӹ߷�Ӱ�������ʾ����


	//���ָ������
	osg::ref_ptr<osg::MatrixTransform> mtCommandCenter; // mtAirport
													  //��ӻ�վ1
	void addCommandCenter();
	osg::ref_ptr<osg::Node> commandCenter; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtCommandCenterSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtCenter; //mtfly
};

