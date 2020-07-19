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

	//新增地标
	void addLabel();

	//ptr
	//1:指针:COSGObject
	//2:指针:文件名
	//3:整型:地标数量
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

	//填充世界地图
	void FillWorld(bool isFill);
	void SetFillWorldTrans(double dfill);

	//是否显示等高线
	void ShowDengGao(bool isShow);

	//添加显示视点信息的控件
	void addViewPointLabel();
	CLabelControlEventHandler *labelEvent;

	//飞往
	void FlyTo(double lon, double lat, double hei);

public:
	osg::ref_ptr<osgEarth::MapNode> mapNode;

	//国界线图层
	osg::ref_ptr<osgEarth::ImageLayer> china_boundaries;
	osg::ref_ptr<osg::Node> world;

	//等高线
	osg::ref_ptr<osg::Node> dengGao;
	bool isShowDengGao;

	//地标
	osg::ref_ptr<osg::Group> earthLabel;

	//是否填充
	bool isFillWorld;
	osg::ref_ptr<CEventHandler> eh;

	//设置填充透明度
	double worldFillTrans;


	//地表的矩阵操作
public:
	osg::ref_ptr<osg::CoordinateSystemNode> csn;

public:
	osg::ref_ptr<osg::Node> airport;
	osg::ref_ptr<osg::MatrixTransform> mtAirport;
	//设置机场
	void addAirport();

	osg::ref_ptr<osg::Node> flyAirport;
	osg::ref_ptr<osg::MatrixTransform> mtFlySelf;
	osg::ref_ptr<osg::MatrixTransform> mtfly;

public:
	//设置道路车辆
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
	//根据输入的控制点，输出一个路径，控制点格式为（经，纬，高，速）
	osg::AnimationPath* CreateAirLinePath(osg::Vec4Array* ctrl);
	osg::AnimationPath* CreateAirLinePath2(osg::Vec4Array* ctrl);
	osg::AnimationPath* CreateAirLinePath3(osg::Vec4Array* ctrl);

	//两点间的距离公式
	double GetDis(osg::Vec3 from, osg::Vec3 to);

	//计算两点间需要行驶的时间
	double GetRunTime(osg::Vec3 from, osg::Vec3 to, double speed);

	//设置一个预设置路径
	void DoAPreLine();

	//生成的预设置路径
	osg::ref_ptr<osg::AnimationPathCallback> apcFly1;
	osg::ref_ptr<osg::AnimationPathCallback> apcCar;
	osg::ref_ptr<osg::AnimationPathCallback> apcPerson;

	//启动预设置路径
	//飞机飞行
	bool isPathStart;
	void DoPreLineNow(bool isStart);
	//车辆移动
	bool isCarStart;
	void DoPreLineNow2(bool isStart);
	// 行人移动
	bool isPersonStart;
	void DoPreLineNow3(bool isStart);

	void isTrackFly(bool btrack);

	void isTrackCar(bool btrack);
	//
	void isTrackPerson(bool btrack);
	//Build尾迹
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
	//测量相关
	void isTestJu(bool isTest);

	osgEarth::Util::Controls::LabelControl* flyCoords;
	osg::ref_ptr<osgGA::StateSetManipulator> stateSetMani;

public:
	void setModule(int module);

	void swapStereo();

	void createCompress();

	osg::MatrixTransform* createCompressPart(const std::string& image, float radius, float height);

	//表盘，指针
	osg::MatrixTransform* _plate;
	osg::MatrixTransform* _needle;

public:
	osg::ref_ptr<osg::Camera> radar;
	void CreateRadar();
	osg::ref_ptr<osgEarth::Annotation::PlaceNode> airLabel;
	osg::ref_ptr<osgEarth::Annotation::PlaceNode> ffLabel;

public:
	//绘制直线
	//实线的Style，Node
	//无人机
	osgEarth::Symbology::Style m_lineFlyStyle;
	osgEarth::Features::Feature* m_pFlyFeature;
	osgEarth::Annotation::FeatureNode* m_pFlyFeatureNode;

	void drawFlyLine();
	void clearFlyLine();

	//车辆
	osgEarth::Symbology::Style m_lineCarStyle;
	osgEarth::Features::Feature* m_pCarFeature;
	osgEarth::Annotation::FeatureNode* m_pCarFeatureNode;

	void drawCarLine();
	void clearCarLine();

	//行人
	osgEarth::Symbology::Style m_linePersonStyle;
	osgEarth::Features::Feature* m_pPersonFeature;
	osgEarth::Annotation::FeatureNode* m_pPersonFeatureNode;

	void drawPersonLine();
	void clearPersonLine();

	//读取坐标文件
	void readFlyCoords(char * filename);

	void readCarCoords(char * filename);

	void readPersonCoords(char * filename);
	

	//获取高程数据
	double query_resolution;
	double out_resolution;
	osgEarth::ElevationQuery *query;

	//添加模型并进行移动
	void addFLyAndMove(char * filename, bool start);
	void addCarAndMove(char * filename, bool start);
	void addPersonAndMove(char * filename, bool start);
public:
	//添加卫星
	void addSatellite();

	osg::ref_ptr<osg::Node> satellite;
	osg::ref_ptr<osg::MatrixTransform> mtSatelliteSelf;
	osg::ref_ptr<osg::MatrixTransform> mtSatellite;

	osg::ref_ptr<osg::Node> satellite2;
	osg::ref_ptr<osg::MatrixTransform> mtSatelliteSelf2;
	osg::ref_ptr<osg::MatrixTransform> mtSatellite2;

public:
	//添加数据中心
	void addDataCenter();
	
public:
	//绘制洪水
	void drawFlood();
public:
	//污染扩散
	void drawPollution();

public:
	osg::ref_ptr<osg::MatrixTransform> mtBaseStation; // mtAirport
	//添加基站1
	void addBaseStation();
	osg::ref_ptr<osg::Node> baseStation; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation; //mtfly


	osg::ref_ptr<osg::MatrixTransform> mtBaseStation2; // mtAirport
	//添加基站2
	void addBaseStation2();
	osg::ref_ptr<osg::Node> baseStation2; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf2; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation2; //mtfly

	osg::ref_ptr<osg::MatrixTransform> mtBaseStation3; //mtAirport
	//添加基站3
	void addBaseStation3();
	osg::ref_ptr<osg::Node> baseStation3; //flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseStationSelf3; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtStation3; //mtfly

	//添加基准站
	osg::ref_ptr<osg::MatrixTransform> mtBase; //mtAirport
													   
	void addBase();
	osg::ref_ptr<osg::Node> base; //flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtBaseSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mt_base; //mtfly

//绘制通信链路
public:
	osgEarth::Annotation::FeatureNode* m_pLakeFeatureNode;
	osgEarth::Annotation::FeatureNode* m_pLakeFeatureNode2;
	//显示链路
	void drawLink();
	//隐藏链路
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
	//添加传感器
	void addSensor();

	//显示传感器连接网络
	void addSensorNetwork();

	//隐藏传感器连接网络
	void hideSensorNetwork();

	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode;
	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode2;
	osg::ref_ptr<osg::Node> sensor;
	osg::ref_ptr<osg::MatrixTransform> mtSensorSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtSensor; //mtfly
public:
	//显示卫星数据——>直接叠加高分影像进行显示即可


	//添加指挥中心
	osg::ref_ptr<osg::MatrixTransform> mtCommandCenter; // mtAirport
													  //添加基站1
	void addCommandCenter();
	osg::ref_ptr<osg::Node> commandCenter; // flyAirport
	osg::ref_ptr<osg::MatrixTransform> mtCommandCenterSelf; //mtFlySelf
	osg::ref_ptr<osg::MatrixTransform> mtCenter; //mtfly
};

