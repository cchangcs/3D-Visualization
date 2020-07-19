#include "stdafx.h"
#include "osgCoreLib.h"

osgCoreLib::osgCoreLib(HWND hWnd)
{ 
	m_hWnd = hWnd;
	processI = 0;
	isFillWorld = true;
	worldFillTrans = 0.1;
	isShowDengGao = false;
	labelEvent = 0;
	isPathStart = false;
	isCarStart = false;
	isPersonStart = false;
	apcFly1 = 0;
	mViewer=new osgViewer::Viewer();
    mRoot = new osg::Group;
	//osg::DisplaySettings::instance()->setNumMultiSamples(16); //�����Կ���֧�� 0428 hu
	//���ݾ�γ�Ȼ�ȡ�߳�
	query_resolution = 0.00000001;
	out_resolution = 0.0;

}
osgCoreLib::~osgCoreLib(void)
{
}
void osgCoreLib::InitOSG(bool isfullscreen,int recwidth,int recheight)
{
	int_recwidth=recwidth;
	int_recheight=recheight;
	mRoot = new osg::Group;
    osg::ref_ptr<osg::Node> mp = osgDB::readNodeFile("./china-simple.earth");
    mRoot->addChild(mp);
    mapNode = dynamic_cast<osgEarth::MapNode*>(mp.get());
	map = mapNode->getMap();
	//��ʼ���̲߳�ѯ
	query = new osgEarth::ElevationQuery(mapNode->getMap());
	setup( isfullscreen, recwidth, recheight);
	
}

void osgCoreLib::setup(bool isfullscreen, int recwidth, int recheight)
{
	if (isfullscreen == false)
	{
		// ���ش���Size
		RECT rect;
		::GetWindowRect(m_hWnd, &rect);
		// ��ʼ��ͼ�λ���GraphicsContext Traits
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		// Init the Windata Variable that holds the handle for the Window to display OSG in.
		osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);
		// ����traits ����
		traits->x = 0;
		traits->y = 0;
		traits->width = rect.right - rect.left;
		traits->height = rect.bottom - rect.top;
		traits->windowDecoration = false;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		traits->setInheritedWindowPixelFormat = true;
		traits->inheritedWindowData = windata;
		// ����ͼ�λ���Graphics Context
		osg::GraphicsContext * gc = osg::GraphicsContext::createGraphicsContext(traits.get());
		{
			// ���ݷֱ���ȷ�����ʵ�ͶӰ����֤��ʾ��ͼ�β�����
			double fovy = 0.0;
			double aspectRatio = 0.0;
			double zNear = 0.0;
			double zFar = 0.0;
			mViewer->getCamera()->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);
			double newAspectRatio = double(traits->width) / double(traits->height);
			double aspectRatioChange = newAspectRatio / aspectRatio;
			if (aspectRatioChange != 1.0)
			{
				mViewer->getCamera()->getProjectionMatrix() *= osg::Matrix::scale(1.0 / aspectRatioChange, 1.0, 1.0);
			}
		}
		mViewer->getCamera()->setViewport(0, 0, traits->width, traits->height);
		mViewer->getCamera()->setGraphicsContext(gc);
		mViewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 1000.0);
		mViewer->getCamera()->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//������Ȳ���
		mViewer->getCamera()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

		//mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
		mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
		mViewer->getCamera()->setNearFarRatio(0.000003f);
		em = new osgEarth::Util::EarthManipulator;
		if (mapNode.valid())
		{
			em->setNode(mapNode);
		}
		em->getSettings()->setArcViewpointTransitions(true);
		mViewer->setCameraManipulator(em);
		const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
		//mViewer->addEventHandler(new PickHandle(geoSRS));
		mViewer->addEventHandler(new CPickHandler(mViewer));
		em->setViewpoint(osgEarth::Util::Viewpoint("", 112.44, 33.75, 444.02, -15.84, -53.01, 4028182.75), 5);
	}

	//��ȡ������ͼ��
	china_boundaries = mapNode->getMap()->getImageLayerByName("china_boundaries");
	world = osgDB::readNodeFile("./globe/world.ive");
	dengGao = osgDB::readNodeFile("./globe/DengGao.ive");

	eh = new CEventHandler;
	eh->mapNode = mapNode;
	eh->computeIntersect = world;
	//�ر��ʼ��
	earthLabel = new osg::Group;
	mRoot->addChild(earthLabel);
	//�����ر�
	addLabel();

	//������ʾ�ӵ���Ϣ�Ŀؼ�
	addViewPointLabel();

	//���ӻ���
	addAirport();

	//���ӵ�·����
	addCar();

	//���ӵ�·����
	addPerson();
	addPerson2();
	modifyPerson(1);

	//��������
	addSatellite();

	//��Ӽ���վ
	addBaseStation();
	addBaseStation2();
	addBaseStation3();

	//��ӻ�׼վ
	addBase();

	//���Ӧ��ָ������
	addCommandCenter();

	//�����������
	//addDataCenter();

	//���ƺ���
	//drawFlood();

	//����½�����
	addPositionName();

	//��Ⱦ��ɢ
	//drawPollution();

	//���ز�
	hideImageLayer2015();
	hideImageLayer2017();
	hideCliassificationImageLayer2015();
	hideCliassificationImageLayer2017();
	hideTransferImage();
	hidePollutionImage();
	hideXinJiangImage();
	hideSpectrumImage2018();
	hideSpectrumImage2019();
	hideSpectrumClassificationImage2018();
	hideSpectrumClassificationImage2019();
	hideSpectrumTransferImage();
	hideAspectImage();
	hideSlopeImage();

	//FillWorld(true);

	//��Ӵ�����
	addSensor();

	//��Ӵ���������ṹ
	//addSensorNetwork();

	//����Ԥ����·��
	DoAPreLine();

	eh->flyLabel = flyCoords;

	stateSetMani = new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet());
	mViewer->addEventHandler(stateSetMani);
	mViewer->addEventHandler(eh);
	eh->stateSetMani = stateSetMani;

	int viewdis = recheight;
	if (recwidth>recheight)
	{
		viewdis = recwidth;
	}


	osgUtil::Optimizer optimizer;
	optimizer.optimize(mRoot.get());
	mViewer->setSceneData(mRoot.get());
	//��ʼ�����
	osgEarth::Config skyConf;
	double hours = skyConf.value("hours", 12.0);
	osgEarth::Util::SkyNode* sky_node = osgEarth::Util::SkyNode::create(mapNode);
	sky_node->setDateTime(hours);
	sky_node->attach(mViewer, 1);
	mRoot->addChild(sky_node);
	
	// ��ʼ������������
	mViewer->realize();
	//mViewer->run();
	while (!mViewer->done())
	{
		mViewer->frame();
		//Sleep(10);
	}
	
}

std::string osgCoreLib::DoubleToStringByStringStream(float value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

void osgCoreLib::InitOsgEarth() {
	

	/*CreateRadar();
	eh->radar = radar;
	eh->JQ = mtfly;
	eh->ffLabel = ffLabel;*/
}

void osgCoreLib::Render(void * ptr)
{
	osgCoreLib *osg = (osgCoreLib*)ptr;
	osgViewer::Viewer * viewer = osg->getViewer();
	while (!viewer->done())
	{
		viewer->frame();
	}

}


osgViewer::Viewer *osgCoreLib::getViewer()
{
	return mViewer;
}

void osgCoreLib::setChinaBoundariesOpacity(double opt)
{
	if (china_boundaries)
	{
		china_boundaries->setOpacity(opt);
	}
}

double osgCoreLib::getChinaBoundariesOpacity()
{
	if (china_boundaries)
	{
		return china_boundaries->getOpacity();
	}
	else
	{
		return -1.0;
	}
}

void osgCoreLib::rmvChinaBoundaryes()
{
	if (china_boundaries)
	{
		mapNode->getMap()->removeImageLayer(china_boundaries);
	}
}

void osgCoreLib::addChinaBoundaryes()
{
	if (china_boundaries)
	{
		mapNode->getMap()->addImageLayer(china_boundaries);
	}
}

void unicodeToUTF8(const wstring &src, string& result)
{
	int n = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0);
	result.resize(n);
	::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0);
}

void osgCoreLib::addLabel()
{
	//
	osgEarth::Style style;
	osgEarth::Symbology::TextSymbol * textStyle = style.getOrCreateSymbol<osgEarth::Symbology::TextSymbol>();
	//������ɫ
	textStyle->fill()->color() = osg::Vec4f(1.0, 1.0, 1.0, 1.0);
	//���ñ߿�
	textStyle->halo()->color() = osg::Vec4f(0.0, 0.0, 0.0, 1.0);
	textStyle->font() = "simkai.ttf";
	textStyle->size() = 20.0;
	//textStyle->pixelOffset() = osg::Vec2s(100, 100.0);
	textStyle->encoding() = osgEarth::Symbology::TextSymbol::ENCODING_UTF8;
	
	osg::Image* china = osgDB::readImageFile("./label/chinaIcon.jpg");
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	std::string _strWideName;
	unicodeToUTF8(L"�й�", _strWideName);
	osgEarth::Annotation::PlaceNode *pn = new osgEarth::Annotation::PlaceNode(mapNode, osgEarth::GeoPoint(geoSRS, 110, 34), china, _strWideName, style);

	earthLabel->addChild(pn);
	osg::Image* tempImg = 0;
	osg::Image* cityCenter = osgDB::readImageFile("./label/icon25.png");
	osg::Image* city = osgDB::readImageFile("./label/icon26.png");
	osg::Image* countycity = osgDB::readImageFile("./label/icon25.png");
	osg::Image* county = osgDB::readImageFile("./label/icon25.png");
	osg::Image* town = osgDB::readImageFile("./label/icon10.png");
	osg::Image* vi = osgDB::readImageFile("./label/icon24.png");


	//{
	//	std::string tempStr = "./ival/shaanxi/";
	//	std::string centerFile = tempStr + "center.center";
	//	char tempChar[256];

	//	std::fstream fin(centerFile, std::ios::in);
	//	//37939
	//	for (int index = 0; index<800; index++)
	//	{
	//		sprintf(tempChar, "%d.ive", index);
	//		std::string temp = tempStr;
	//		temp += tempChar;
	//		osg::ref_ptr<osg::PagedLOD> plod = new osg::PagedLOD;
	//		plod->setFileName(0, temp);

	//		//��ȡcenter��dist
	//		int x, y, z;
	//		long dist;
	//		fin >> x >> y >> z >> dist;
	//		plod->setCenter(osg::Vec3(x, y, z));
	//		plod->setRange(0, 0, dist);
	//		plod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
	//		earthLabel->addChild(plod);
	//	}
	//	fin.close();
	//}

	{
		//����ʡ��
		std::string tempStr = "./ival/Sheng/";
		std::string centerFile = tempStr + "center.center";
		char tempChar[256];
		osg::EllipsoidModel* emodel = new osg::EllipsoidModel();

		std::fstream fin(centerFile, std::ios::in);
		for (int index = 0; index<32; index++)
		{
			sprintf(tempChar, "%d.ive", index);
			std::string temp = tempStr;
			temp += tempChar;
			osg::ref_ptr<osg::PagedLOD> plod = new osg::PagedLOD;
			plod->setFileName(0, temp);
			//��ȡcenter��dist
			int x, y, z;
			long dist;
			fin >> x >> y >> z >> dist;
			plod->setCenter(osg::Vec3(x, y, z));
			plod->setRange(0, 0, dist);
			plod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
			earthLabel->addChild(plod);
		}
		fin.close();
	}

}

void osgCoreLib::ReadLabelThread(void * ptr)
{
	//COSGObject
	unsigned int *tempArray = (unsigned int *)ptr;

	//����0
	osgCoreLib* osg = (osgCoreLib*)tempArray[0];

	//����1
	std::string *fileFullPath = (std::string*)tempArray[1];

	//����2
	unsigned int count = tempArray[2];

	std::fstream f(fileFullPath->c_str(), std::ios::in);
	char name[128];
	wchar_t wname[128];
	char area[256];
	int level;
	float lon;
	float lat;

	osg::Image* tempImg = 0;

	for (int i = 0; i<count;)
	{
		int j = 0;
		osg::ref_ptr<osg::Group> gp = new osg::Group;
		while (j<100 && i<count)
		{
			j++;
			i++;

			f >> name >> area >> level >> lon >> lat;

			//����γ��ת��Ϊȫ�������
			osg::Vec3d center;
			osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
			emodel->convertLatLongHeightToXYZ(osg::DegreesToRadians(lon), osg::DegreesToRadians(lat), 0, center.x(), center.y(), center.z());

			osg::ref_ptr<osg::LOD> lod = new osg::LOD;
			lod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
			lod->setCenter(center);

			//������ȡ����ת���ɿ��ַ�
			//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, 128, wname, 128);
			long dist;

			switch (level)
			{
			case 8:
			{
				dist = 5000000;
				tempImg = osg->sheng;
			}
			break;
			case 16:
			{
				dist = 500000;
				tempImg = osg->cityCenter;
			}
			break;
			case 64:
			{
				dist = 100000;
				tempImg = osg->city;
			}
			break;
			case 256:
			{
				dist = 50000;
				tempImg = osg->countycity;
			}
			break;
			case 512:
			{
				dist = 25000;
				tempImg = osg->county;
			}
			break;
			case 1024:
			{
				dist = 12000;
				tempImg = osg->town;
			}
			break;
			case 4096:
			{
				dist = 6000;
				tempImg = osg->vi;
			}
			break;
			default:
			{
				dist = 10;
			}
			break;
			}

			lod->addChild(new osgEarth::Annotation::PlaceNode(osg->mapNode, osgEarth::GeoPoint(0, lon, lat), tempImg, name, osg->style), 0, dist);
			gp->addChild(lod);
		}



		osg->earthLabel->addChild(gp);

		Sleep(10);
	}
	f.close();
}

void osgCoreLib::CreateLabelThread(void * ptr)
{
	//COSGObject
	unsigned int *tempArray = (unsigned int *)ptr;

	//����0, 
	osgCoreLib* osg = (osgCoreLib*)tempArray[0];

	//����1, �ر��ļ�·��
	std::string *fileFullPath = (std::string*)tempArray[1];

	//����2, �ر�����
	unsigned int count = tempArray[2];

	//����3, �ر�����ļ�·�� F:/abc/
	std::string *fileOutputPath = (std::string*)tempArray[3];

	//��ʱ����
	std::string centerFile = *fileOutputPath;


	std::string outputPath = *fileOutputPath;
	centerFile += "center.center";

	std::fstream f(fileFullPath->c_str(), std::ios::in);
	std::fstream fou(centerFile.c_str(), std::ios::out);

	char name[128];
	wchar_t wname[128];
	char area[256];
	int level;
	float lon;
	float lat;
	f >> count;

	osg::Image* tempImg = 0;
	char iTemp[10];
	char iFout[256];
	for (int i = 0; i<count; i++)
	{
		osg->processI = i;

		osg::ref_ptr<osg::Group> gp = new osg::Group;

		f >> name >> area >> level >> lon >> lat;

		//����γ��ת��Ϊȫ�������
		osg::Vec3d center;
		osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
		emodel->convertLatLongHeightToXYZ(osg::DegreesToRadians(lon), osg::DegreesToRadians(lat), 0, center.x(), center.y(), center.z());
		//osg::ref_ptr<osg::LOD> lod = new osg::LOD;
		//lod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
		//lod->setCenter(center);

		//������ȡ����ת���ɿ��ַ�
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, 128, wname, 128);
		long dist;

		switch (level)
		{
		case 8:
		{
			dist = 5000000;
			tempImg = osg->sheng;
		}
		break;
		case 16:
		{
			dist = 500000;
			tempImg = osg->cityCenter;
		}
		break;
		case 64:
		{
			dist = 100000;
			tempImg = osg->city;
		}
		break;
		case 256:
		{
			dist = 50000;
			tempImg = osg->countycity;
		}
		break;
		case 512:
		{
			dist = 25000;
			tempImg = osg->county;
		}
		break;
		case 1024:
		{
			dist = 12000;
			tempImg = osg->town;
		}
		break;
		case 4096:
		{
			dist = 6000;
			tempImg = osg->vi;
		}
		break;
		default:
		{
			dist = 10;
		}
		break;
		}
		sprintf(iFout, "%.0f %.0f %.0f %ld\n", center.x(), center.y(), center.z(), dist);
		fou << iFout;

		sprintf(iTemp, "%d", i);

		outputPath += iTemp;
		outputPath += ".ive";

		osgEarth::Annotation::PlaceNode* pn = new osgEarth::Annotation::PlaceNode(osg->mapNode, osgEarth::GeoPoint(0, lon, lat), tempImg, name, osg->style);
		osgDB::Registry::instance()->writeNode(*pn, outputPath, osgDB::Registry::instance()->getOptions());

		outputPath.pop_back();
		outputPath.pop_back();
		outputPath.pop_back();
		outputPath.pop_back();

		int widthiTemp = strlen(iTemp);
		while (widthiTemp>0)
		{
			widthiTemp--;
			outputPath.pop_back();
		}

		//
		//while(!theApp.bCanModify)Sleep(1);
		//osg->earthLabel->addChild(gp);
		//
		//Sleep(10);
	}
	f.close();
	fou.close();

}

void osgCoreLib::FillWorld(bool isFill)
{



	if (isFill == this->isFillWorld)
	{

		return;
	}

	isFillWorld = isFill;

	if (isFill)
	{
		/*
		mapNode->getOverlayGroup()->addChild(world);
		mapNode->updateOverlayGraph();
		*/
		mapNode->getModelLayerGroup()->addChild(world);
		mViewer->addEventHandler(eh);
	}
	else
	{
		/*mapNode->getOverlayGroup()->removeChild(world);
		mapNode->updateOverlayGraph();*/
		mapNode->getModelLayerGroup()->removeChild(world);

		mViewer->removeEventHandler(eh);
	}

}

void osgCoreLib::SetFillWorldTrans(double dfill)
{


	if (worldFillTrans == dfill)
	{

		return;
	}

	worldFillTrans = dfill;

	osg::Group* gp = dynamic_cast<osg::Group*> (world.get());

	if (gp)
	{
		for (int i = 0; i<gp->getNumChildren(); i++)
		{
			osg::Geode* gnode = dynamic_cast<osg::Geode*>(gp->getChild(i));
			if (gnode)
			{
				osg::Geometry* tempGeom = dynamic_cast<osg::Geometry*> (gnode->getDrawable(0));
				if (tempGeom)
				{
					osg::Vec4Array* tempColorArray = dynamic_cast<osg::Vec4Array*>(tempGeom->getColorArray());
					if (tempColorArray)
					{
						osg::Vec4Array::iterator iter = tempColorArray->begin();
						for (iter; iter != tempColorArray->end(); iter++)
						{
							iter->set(iter->r(), iter->g(), iter->b(), worldFillTrans);
						}
					}
					tempGeom->dirtyDisplayList();
				}
			}

		}
	}

}

void osgCoreLib::ShowDengGao(bool isShow)
{



	if (isShow == this->isShowDengGao)
	{

		return;
	}

	isShowDengGao = isShow;

	if (isShow)
	{
		mapNode->getModelLayerGroup()->addChild(dengGao);
	}
	else
	{
		mapNode->getModelLayerGroup()->removeChild(dengGao);
		/*mapNode->getOverlayGroup()->removeChild(dengGao);
		mapNode->updateOverlayGraph();*/
	}

}

void osgCoreLib::addViewPointLabel()
{

	mRoot->addChild(osgEarth::Util::Controls::ControlCanvas::get(mViewer));

	osgEarth::Util::Controls::ControlCanvas* canvas = osgEarth::Util::Controls::ControlCanvas::get(mViewer);


	//��ӿؼ���������ʾ�ӵ���Ϣ
	osgEarth::Util::Controls::LabelControl* viewCoords = new osgEarth::Util::Controls::LabelControl("TestViewPoint", 18.0, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	viewCoords->setHorizAlign(osgEarth::Util::Controls::Control::ALIGN_LEFT);
	viewCoords->setVertAlign(osgEarth::Util::Controls::Control::ALIGN_TOP);
	viewCoords->setBackColor(0, 0, 0, 0.5);
	viewCoords->setSize(800, 50);
	viewCoords->setMargin(10);
	canvas->addControl(viewCoords);

	//��ӿؼ���������ʾ��꽻����Ϣ
	osgEarth::Util::Controls::LabelControl* mouseCoords = new osgEarth::Util::Controls::LabelControl("TestViewPoint", 18.0, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	mouseCoords->setHorizAlign(osgEarth::Util::Controls::Control::ALIGN_RIGHT);
	mouseCoords->setVertAlign(osgEarth::Util::Controls::Control::ALIGN_BOTTOM);
	mouseCoords->setBackColor(0, 0, 0, 0.5);
	mouseCoords->setSize(400, 50);
	mouseCoords->setMargin(10);
	canvas->addControl(mouseCoords);

	//��ӿؼ�������ʾ�ɻ�����
	flyCoords = new osgEarth::Util::Controls::LabelControl("Fly", 18.0, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	flyCoords->setHorizAlign(osgEarth::Util::Controls::Control::ALIGN_RIGHT);
	flyCoords->setVertAlign(osgEarth::Util::Controls::Control::ALIGN_TOP);
	flyCoords->setBackColor(0, 0, 0, 0.5);
	flyCoords->setSize(400, 600);
	flyCoords->setMargin(10);
	canvas->addControl(flyCoords);

	if (labelEvent == 0)
	{
		labelEvent = new CLabelControlEventHandler(viewCoords, mouseCoords, mapNode);
	}
	
	//mViewer->addEventHandler(labelEvent);  cc ���ڻ���ֿ�������
}

void osgCoreLib::FlyTo(double lon, double lat, double hei)
{

	em->setViewpoint(osgEarth::Util::Viewpoint("", lon, lat, hei, 0, -45, hei), 2);

}



void osgCoreLib::addAirport()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	double out_haml = 0.0;
	osg::Matrixd mtTemp; 

	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	flyAirport = osgDB::readNodeFile("./Module/fly2/dynamicheli.FBX");//, a);
	flyAirport->setName("Fly");
	mtFlySelf = new osg::MatrixTransform;
	mtFlySelf->setMatrix(osg::Matrixd::scale(0.03, 0.03, 0.03) * osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f)*osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f)
		/** osg::Matrixd::rotate(osg::inDegrees(55.0f), 0.0f, 0.0f, 1.0f)
		
		* osg::Matrixd::rotate(osg::inDegrees(10.f), 1.0f, 0.0f, 0.0f)*/
	);
	mtFlySelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtFlySelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	//mtFlySelf->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	mtFlySelf->addChild(flyAirport);

	mtfly = new osg::MatrixTransform;
	mtfly->addChild(mtFlySelf);
	mRoot->addChild(mtfly);
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.618753, 44.245163, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.245163), osg::DegreesToRadians(81.618753), out_haml + 1, mtTemp);
	mtfly->setMatrix(mtTemp);

}

//��ӵ�·����
void osgCoreLib::addCar()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	osg::Matrixd mtTemp;

	//���ݾ�γ�Ȼ�ȡ�߳�
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.619053, 44.245049, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	//*car = osgDB::readNodeFile("./Module/car2/car.obj", a);*/
	//car = osgDB::readNodeFile("./Module/car/Body.obj", a);
	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	car = osgDB::readNodeFile("./Module/car/van car.obj", a);

	car->setName("Car");
	mtCarSelf = new osg::MatrixTransform;
	mtCarSelf->setMatrix(osg::Matrixd::scale(2, 2, 2) * osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));//** osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));
	mtCarSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtCarSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	mtCarSelf->addChild(car);

	mtCar = new osg::MatrixTransform;
	mtCar->addChild(mtCarSelf);
	mRoot->addChild(mtCar);
	

	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.245049), osg::DegreesToRadians(81.619053), out_haml + 1, mtTemp);
	mtCar->setMatrix(mtTemp);

}



//��ӵ�·����
void osgCoreLib::addPerson()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	//road2 = osgDB::readNodeFile("./Module/airport/airport.ive");
	
	//���ݾ�γ�Ȼ�ȡ�߳�
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.621537, 44.235622, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	osg::Matrixd mtTemp;
	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	//person = osgDB::readNodeFile("./Module/person/average_man_02.FBX");
	//person = osgDB::readNodeFile("./Module/person/william.FBX");// a);
	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	//person = osgDB::readNodeFile("./Module/person/c_zom_der_richtofen_cin_fb.obj", a);

	person = osgDB::readNodeFile("./Module/person3/walkperson.FBX");
	//person = osgDB::readNodeFile("./Module/person3/worker.FBX");

	//�Ż�ģ��
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(person.get());
	//optimizer.reset();
	//person = osgDB::readNodeFile("./Module/person2/bb8.FBX");

	person->setName("Person");
	person->setNodeMask(1);
	mtPersonSelf = new osg::MatrixTransform;
	mtPersonSelf->setMatrix(osg::Matrixd::scale(0.1, 0.1, 0.1)*osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f));/// *osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f));
																//mtFlySelf->setMatrix(osg::Matrixd::scale(10, 10, 10)* osg::Matrixd::rotate(osg::inDegrees(50.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f));
	mtPersonSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtPersonSelf->addChild(person);

	mtPerson = new osg::MatrixTransform;
	mtPerson->addChild(mtPersonSelf);
	mRoot->addChild(mtPerson);


	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.235622), osg::DegreesToRadians(81.621537), out_haml + 1, mtTemp);

	mtPerson->setMatrix(mtTemp);

	//=====================================��ýڵ�Ķ����б�=====================================
	AnimationManagerFinder *m_cFinder = new AnimationManagerFinder();
	m_cFinder->apply(person);
	person->accept(*m_cFinder);
	if (m_cFinder->_am.valid())
	{
		person->addUpdateCallback(m_cFinder->_am.get());
	}
	osgAnimation::AnimationList::const_iterator it = m_cFinder->_am->getAnimationList().begin();

	std::string animationName = (*it)->getName();
	osgAnimation::Animation::PlayMode playMode = osgAnimation::Animation::LOOP;
	(*it)->setPlayMode(playMode);//���ò���ģʽ
	(*it)->setDuration(0.7);//���ò���ʱ��

							//�Ӷ����б���ѡ��һ������������
	m_cFinder->_am->playAnimation(*it);
	//m_cFinder->_am->stopAnimation(*it);
	//=====================================��ýڵ�Ķ����б�=====================================
}

void osgCoreLib::addPerson2()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	//���ݾ�γ�Ȼ�ȡ�߳�
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.622984, 44.233594, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	osg::Matrixd mtTemp;
	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	//person = osgDB::readNodeFile("./Module/person/average_man_02.FBX");
	//person = osgDB::readNodeFile("./Module/person/william.FBX");// a);
	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	//person = osgDB::readNodeFile("./Module/person/c_zom_der_richtofen_cin_fb.obj", a);

	person2 = osgDB::readNodeFile("./Module/person/Worker stand N260412.3DS");
	
	//person = osgDB::readNodeFile("./Module/person3/worker.FBX");
	
	//�Ż�ģ��
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(person.get());
	//optimizer.reset();
	//person = osgDB::readNodeFile("./Module/person2/bb8.FBX");

	person2->setName("Person2");
	mtPersonSelf2 = new osg::MatrixTransform;
	mtPersonSelf2->setMatrix(osg::Matrixd::scale(0.1, 0.1, 0.1));/// *osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f));
	//mtFlySelf->setMatrix(osg::Matrixd::scale(10, 10, 10)* osg::Matrixd::rotate(osg::inDegrees(50.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f));
	mtPersonSelf2->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtPersonSelf2->addChild(person2);
	person2->setNodeMask(0);
	mtPerson2 = new osg::MatrixTransform;
	mtPerson2->addChild(mtPersonSelf2);
	mRoot->addChild(mtPerson2);	

	
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.233594), osg::DegreesToRadians(81.622984), out_haml + 1, mtTemp);
	
	mtPerson2->setMatrix(mtTemp);
}
//��Ӽ���վ
void osgCoreLib::addBaseStation()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	mtBaseStation = new osg::MatrixTransform;
	mRoot->addChild(mtBaseStation);

	osg::Matrixd mtTemp;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.62238145, 44.23093983, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23093983), osg::DegreesToRadians(81.62238145), out_haml + 1, mtTemp);
	mtBaseStation->setMatrix(mtTemp);

	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	baseStation = osgDB::readNodeFile("./Module/pillar/monitor.3DS");//, a);
	mtBaseStationSelf = new osg::MatrixTransform;
	mtBaseStationSelf->setMatrix(osg::Matrixd::scale(0.05, 0.05, 0.05)
		/** osg::Matrixd::rotate(osg::inDegrees(55.0f), 0.0f, 0.0f, 1.0f)
		* osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f)
		* osg::Matrixd::rotate(osg::inDegrees(10.f), 1.0f, 0.0f, 0.0f)*/
	);

	baseStation->setName("baseStation1");
	mtBaseStationSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtBaseStationSelf->addChild(baseStation);


	mtStation = new osg::MatrixTransform;
	mtStation->addChild(mtBaseStationSelf);
	mRoot->addChild(mtStation);

	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23093983), osg::DegreesToRadians(81.62238145), out_haml +1, mtTemp);
	mtStation->setMatrix(mtTemp);

}

void osgCoreLib::addBaseStation2()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	mtBaseStation2 = new osg::MatrixTransform;
	mRoot->addChild(mtBaseStation2);

	osg::Matrixd mtTemp;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.62305244, 44.23110580, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23110580), osg::DegreesToRadians(81.62305244), out_haml + 1, mtTemp);
	mtBaseStation2->setMatrix(mtTemp);

	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	baseStation2 = osgDB::readNodeFile("./Module/pillar/monitor.3DS");//, a);

	baseStation2->setName("baseStation2");

	mtBaseStationSelf2 = new osg::MatrixTransform;
	mtBaseStationSelf2->setMatrix(osg::Matrixd::scale(0.05, 0.05, 0.05)
		/** osg::Matrixd::rotate(osg::inDegrees(55.0f), 0.0f, 0.0f, 1.0f)
		* osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f)
		* osg::Matrixd::rotate(osg::inDegrees(10.f), 1.0f, 0.0f, 0.0f)*/
	);
	mtBaseStationSelf2->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtBaseStationSelf2->addChild(baseStation2);

	mtStation2 = new osg::MatrixTransform;
	mtStation2->addChild(mtBaseStationSelf2);
	mRoot->addChild(mtStation2);

	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23110580), osg::DegreesToRadians(81.62305244), out_haml + 1, mtTemp);
	mtStation2->setMatrix(mtTemp);

}

void osgCoreLib::addBaseStation3()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	mtBaseStation3 = new osg::MatrixTransform;
	mRoot->addChild(mtBaseStation3);

	osg::Matrixd mtTemp;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.623711704, 44.23127153, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23127153), osg::DegreesToRadians(81.623711704), out_haml, mtTemp);
	mtBaseStation3->setMatrix(mtTemp);

	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	baseStation3 = osgDB::readNodeFile("./Module/pillar/monitor.3DS");//, a);

	baseStation3->setName("baseStation3");

	mtBaseStationSelf3 = new osg::MatrixTransform;
	mtBaseStationSelf3->setMatrix(osg::Matrixd::scale(0.05, 0.05, 0.05));
	mtBaseStationSelf3->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtBaseStationSelf3->addChild(baseStation3);

	mtStation3 = new osg::MatrixTransform;
	mtStation3->addChild(mtBaseStationSelf3);
	mRoot->addChild(mtStation3);

	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23127153), osg::DegreesToRadians(81.623711704), out_haml + 1, mtTemp);
	mtStation3->setMatrix(mtTemp);

}


void osgCoreLib::addBase()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	mtBase = new osg::MatrixTransform;
	mRoot->addChild(mtBase);
	
	osg::Matrixd mtTemp;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.62165139, 44.23093888, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23093888), osg::DegreesToRadians(81.62165139), out_haml + 1, mtTemp);
	mtBase->setMatrix(mtTemp);

	osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	base = osgDB::readNodeFile("./Module/pillar/monitor.3DS");
	
	base->setName("base");

	mtBaseSelf = new osg::MatrixTransform;
	mtBaseSelf->setMatrix(osg::Matrixd::scale(0.05, 0.05, 0.05)
		/** osg::Matrixd::rotate(osg::inDegrees(55.0f), 0.0f, 0.0f, 1.0f)
		* osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f)
		* osg::Matrixd::rotate(osg::inDegrees(10.f), 1.0f, 0.0f, 0.0f)*/
	);
	mtBaseSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtBaseSelf->addChild(base);

	mt_base = new osg::MatrixTransform;
	mt_base->addChild(mtBaseSelf);
	mRoot->addChild(mt_base);
	
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.23093888), osg::DegreesToRadians(81.62165139), out_haml + 1, mtTemp);
	mt_base->setMatrix(mtTemp);

}

//�ɻ���·������
void osgCoreLib::DoPreLineNow(bool isStart)
{
	if (isStart != isPathStart)
	{
		isPathStart = isStart;
		if (isPathStart)
		{
			mtFlySelf->setMatrix(osg::Matrixd::scale(0.03, 0.03, 0.03)*osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f) *osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f));// * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));
			mtfly->setUpdateCallback(apcFly1);
			
			//em->setViewpoint(osgEarth::Viewpoint("", 81.620762, 44.238978, 1400 , 24.261, -21.6, 1400), 1);
			//���ٷɻ�
			//em->setTetherNode(flyAirport);
			//mtfly->removeUpdateCallback(apcFly1);
			apcFly1->reset();
			//BuildTail(osg::Vec3(0, -10, 0), mtfly);
			//BuildTail(osg::Vec3(0, 10, 0), mtfly);
			//BuildRibbonFly0(512, mtfly);

			//===========================��ýڵ�Ķ����б�===========================
			AnimationManagerFinder *m_cFinder = new AnimationManagerFinder();
			m_cFinder->apply(flyAirport);
			flyAirport->accept(*m_cFinder);
			if (m_cFinder->_am.valid())
			{
				flyAirport->addUpdateCallback(m_cFinder->_am.get());
			}
			osgAnimation::AnimationList::const_iterator it = m_cFinder->_am->getAnimationList().begin();
			/*if (m_cFinder->_am->getAnimationList().size() == 0) {
				MessageBox(NULL, "Hi", "111", MB_OK);
			}*/
			std::string animationName = (*it)->getName();
			osgAnimation::Animation::PlayMode playMode = osgAnimation::Animation::LOOP;
			(*it)->setPlayMode(playMode);//���ò���ģʽ
			(*it)->setDuration(0.1);//���ò���ʱ��

			//�Ӷ����б���ѡ��һ������������
			m_cFinder->_am->playAnimation(*it);
			//===========================��ýڵ�Ķ����б�===========================

			gnodeboud0 = new osg::Geode;
			//���Բ�α߿�
			/*	
			osg::BoundingSphere bs = mtFlySelf->getBound();
			osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(bs.center(), bs.radius()));
			sd->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.2));
			gnodeboud0->addDrawable(sd);*/
			gnodeboud0->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			mtfly->addChild(gnodeboud0);

		}
		else
		{
			//mtFlySelf->setMatrix(osg::Matrixd::scale(3, 3, 3) * osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));// *osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f));// *osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));//*osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));
			
			/*osg::Matrix mtTemp;
			double out_haml;
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.620762, 44.238978, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			//=========�޸�Ϊ���˻����н�����λ��===========
			csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.238978), osg::DegreesToRadians(81.620762), out_haml + 90, mtTemp);
			//=========�޸�Ϊ���˻����н�����λ��===========
			tfly->setMatrix(mtTemp);
			*/
			mtfly->removeUpdateCallback(apcFly1);
			//em->setViewpoint(osgEarth::Viewpoint("", 81.620762, 44.238978, 1300, 24.261, -21.6, 1300), 1);
			mtfly->removeUpdateCallback(tcFly0);
			tcFly0 = 0;
			mRoot->removeChild(gnodeFly0);
			gnodeFly0 = 0;
		}
	}
}

//������·���ƶ�
void osgCoreLib::DoPreLineNow2(bool isStart)
{
	if (isStart != isCarStart)
	{
		isCarStart = isStart;
		if (isCarStart)
		{
			double out_haml = 0.0;
			/*query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.619053, 44.245049, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);*/

			mtCarSelf->setMatrix(osg::Matrixd::scale(2, 2, 2)* osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));
			mtCar->setUpdateCallback(apcCar);
			//em->setViewpoint(osgEarth::Viewpoint("", 81.619053, 44.245049, 1000, 24.261, -21.6, 4000), 1);
			//���ٳ�
			//em->setTetherNode(car);
			//mtCar->removeUpdateCallback(apcCar);
			apcCar->reset();
			//BuildTail(osg::Vec3(0, -10, 0), mtfly);
			//BuildTail(osg::Vec3(0, 10, 0), mtfly);
			//BuildRibbonCar(512, mtCar);

			

			gnodeboud3 = new osg::Geode;
			//���Բ�α߿�
			/*osg::BoundingSphere bs = mtCarSelf->getBound();
			osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(bs.center(), bs.radius()));
			sd->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.2));
			gnodeboud3->addDrawable(sd);*/
			gnodeboud3->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			mtCar->addChild(gnodeboud3);

		}
		else
		{
			//mtCarSelf->setMatrix(osg::Matrixd::scale(1, 1, 1) *osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));
			//mtCarSelf->setMatrix(osg::Matrixd::scale(2, 2, 2) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));//*osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));
			//���ݾ�γ�Ȼ�ȡ�߳�
			/*double out_haml = 0.0;
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.619053, 44.245049, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);*/
			
			/*
			osg::Matrix mtTemp;
			csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.245049), osg::DegreesToRadians(81.619053), out_haml + 5, mtTemp);
			mtCar->setMatrix(mtTemp);
			*/
			mtCar->removeUpdateCallback(apcCar);
			//em->setTetherNode(0);
			//em->setViewpoint(osgEarth::Viewpoint("", 81.619053, 44.245049, 1000, 24.261, -21.6, 4000), 1);
			mtCar->removeUpdateCallback(tcCar);
			tcCar = 0;
			mRoot->removeChild(gnodeCar);
			gnodeCar = 0;
		}
	}
}


//������·���ƶ�
void osgCoreLib::DoPreLineNow3(bool isStart)
{
	if (isStart != isPersonStart)
	{
		isPersonStart = isStart;
		if (isPersonStart)
		{
			mtPersonSelf->setMatrix(osg::Matrixd::scale(0.1, 0.1, 0.1) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f)*osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));//*osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f)*osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f));// *osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));// *osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 1.0f, 0.0f, 0.0f));
			mtPerson->addUpdateCallback(apcPerson);
			//em->setViewpoint(osgEarth::Viewpoint("", 81.622327, 44.232741, 1300, 24.261, -21.6, 1300), 1);
			
			//mtPerson->removeUpdateCallback(apcPerson);
			apcPerson->reset();

			
		}
		else
		{
			mtPersonSelf->setMatrix(osg::Matrixd::scale(0.1, 0.1, 0.1));
			//mtPersonSelf->setMatrix(osg::Matrixd::scale(0.1, 0.1, 0.1)*osg::Matrixd::rotate(osg::inDegrees(90.f), 1.0f, 0.0f, 0.0f)* osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 0.0f, 1.0f));//*osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));// *osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 1.0f, 0.0f, 0.0f));

			//���ݾ�γ�Ȼ�ȡ�߳�
			/*
			double out_haml = 0.0;
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.622327, 44.232741, 1000, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			osg::Matrix mtTemp;
			csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.232741), osg::DegreesToRadians(81.622327), out_haml + 5, mtTemp);
			mtPerson->setMatrix(mtTemp);
			*/
			mtPerson->removeUpdateCallback(apcPerson);
			//em->setTetherNode(0);
			//em->setViewpoint(osgEarth::Viewpoint("", 81.622327, 44.232741, 1300, 24.261, -21.6, 1000), 1);
			mtPerson->removeUpdateCallback(tcPerson);
			tcPerson = 0;
			mRoot->removeChild(gnodePerson);
			gnodePerson = 0;
		}
	}
}

void osgCoreLib::modifyPerson(int label) 
{
	if (label == 1) {
		person->setNodeMask(1);
	}
	else if (label == 2) {
		person2->setNodeMask(1);
	}
	else if (label == 3) {
		person->setNodeMask(1);
		person2->setNodeMask(0);
	}
	else if (label == 4) {
		person->setNodeMask(0);
		person2->setNodeMask(1);
	}
}

//�ɻ�β��
void osgCoreLib::BuildTail(osg::Vec3 &position, osg::MatrixTransform* scaler)
{
	osg::ref_ptr<osgParticle::FireEffect> fire = new osgParticle::FireEffect(position, 10.0f);
	fire->setUseLocalParticleSystem(false);
	fire->getEmitter()->setEndless(true);
	fire->getEmitter()->setLifeTime(1);

	fire->getParticleSystem()->getDefaultParticleTemplate().setLifeTime(fire->getParticleSystem()->getDefaultParticleTemplate().getLifeTime() * 10);
	scaler->addChild(fire);


	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(fire->getParticleSystem());
	mRoot->addChild(geode);
}

void osgCoreLib::BuildRibbonFly0(int size, osg::MatrixTransform* scalar)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//���ö���
	osg::ref_ptr<osg::Vec3Array> vectex = new osg::Vec3Array(size);
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(size);

	for (unsigned int i = 0; i<size - 1; i += 2)
	{
		(*vectex)[i] = osg::Vec3(0, 0, 0);
		(*vectex)[i + 1] = osg::Vec3(0, 0, 0);

		float alpha = sinf(osg::PI* (float)i / (float)size);

		(*colors)[i] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
		(*colors)[i + 1] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
	}

	geom->setDataVariance(osg::Object::DYNAMIC);
	geom->setUseDisplayList(false);
	geom->setUseVertexBufferObjects(true);

	geom->setVertexArray(vectex);

	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, size));

	gnodeFly0 = new osg::Geode;
	gnodeFly0->addDrawable(geom);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	tcFly0 = new TrailerCallback(geom, size);

	scalar->addUpdateCallback(tcFly0);

	mRoot->addChild(gnodeFly0);
}

//����β��
void osgCoreLib::BuildRibbonCar(int size, osg::MatrixTransform* scalar)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//���ö���
	osg::ref_ptr<osg::Vec3Array> vectex = new osg::Vec3Array(size);
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(size);

	for (unsigned int i = 0; i<size - 1; i += 2)
	{
		(*vectex)[i] = osg::Vec3(0, 0, 0);
		(*vectex)[i + 1] = osg::Vec3(0, 0, 0);

		float alpha = sinf(osg::PI* (float)i / (float)size);

		(*colors)[i] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
		(*colors)[i + 1] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
	}

	geom->setDataVariance(osg::Object::DYNAMIC);
	geom->setUseDisplayList(false);
	geom->setUseVertexBufferObjects(true);

	geom->setVertexArray(vectex);

	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, size));

	gnodeCar = new osg::Geode;
	gnodeCar->addDrawable(geom);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	tcCar = new TrailerCallback(geom, size);

	scalar->addUpdateCallback(tcCar);

	mRoot->addChild(gnodeCar);
}

//����β��
void osgCoreLib::BuildRibbonPerson(int size, osg::MatrixTransform* scalar)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//���ö���
	osg::ref_ptr<osg::Vec3Array> vectex = new osg::Vec3Array(size);
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(size);

	for (unsigned int i = 0; i<size - 1; i += 2)
	{
		(*vectex)[i] = osg::Vec3(0, 0, 0);
		(*vectex)[i + 1] = osg::Vec3(0, 0, 0);

		float alpha = sinf(osg::PI* (float)i / (float)size);

		(*colors)[i] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
		(*colors)[i + 1] = osg::Vec4(osg::Vec3(1.0, 0, 1.0), alpha);
	}

	geom->setDataVariance(osg::Object::DYNAMIC);
	geom->setUseDisplayList(false);
	geom->setUseVertexBufferObjects(true);

	geom->setVertexArray(vectex);

	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, size));

	gnodePerson = new osg::Geode;
	gnodePerson->addDrawable(geom);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	tcPerson = new TrailerCallback(geom, size);

	scalar->addUpdateCallback(tcPerson);

	mRoot->addChild(gnodePerson);
}
//���÷ɻ������������˵�·��
void osgCoreLib::DoAPreLine()
{
	//21.9483, 112.885
	//�ɻ�����·��
	{
		osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;
		vaTemp->push_back(osg::Vec4(112.885, 21.9483, 300, 50));
		
		vaTemp->push_back(osg::Vec4(112.840, 21.905, 300, 100));
		vaTemp->push_back(osg::Vec4(112.820, 21.930, 300, 100));
		vaTemp->push_back(osg::Vec4(112.820, 21.940, 300, 100));
		vaTemp->push_back(osg::Vec4(112.885, 21.9483, 300, 50));
		apcFly1 = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);
	}

	//�����ƶ�·��
	{
		//���ݾ�γ�Ȼ�ȡ�߳�
		double out_haml = 0.0;

		//��¼��һ�κ͵�ǰ��lon��lat
		double last_lon = 0.0;
		double last_lat = 0.0;
		double now_lon = 0.0;
		double now_lat = 0.0;
		double lon_mean = 0.0;
		double lat_mean = 0.0;

		osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.900, 21.950, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.900, 21.950, out_haml + 5, 50));

		last_lon = 112.900;
		last_lat = 21.950;
		now_lon = 112.880;
		now_lat = 21.910;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 5, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.880, 21.910, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.880, 21.910, out_haml + 5, 80));
		last_lon = 112.880;
		last_lat = 21.910;
		now_lon = 112.860;
		now_lat = 21.935;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {

				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 5, 50));

		}
		else {
			while (last_lon > now_lon) {

				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.860, 21.935, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.860, 21.935, out_haml + 5, 80));
		last_lon = 112.900;
		last_lat = 21.950;
		now_lon = 112.880;
		now_lat = 21.910;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 5, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.880, 21.910, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.860, 21.945, out_haml + 5, 80));
		last_lon = 112.880;
		last_lat = 21.945;
		now_lon = 112.900;
		now_lat = 21.950;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 5, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 5, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.900, 21.950, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.900, 21.950, out_haml + 5, 80));
		apcCar = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);
	}
	//�����ƶ�·��
	{
		//���ݾ�γ�Ȼ�ȡ�߳�
		double out_haml = 0.0;

		//��¼��һ�κ͵�ǰ��lon��lat
		double last_lon = 0.0;
		double last_lat = 0.0;
		double now_lon = 0.0;
		double now_lat = 0.0;
		double lon_mean = 0.0;
		double lat_mean = 0.0;

		osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.910, 21.960, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.910, 21.960, out_haml + 210, 50));
		last_lon = 112.910;
		last_lat = 21.960;
		now_lon = 112.890;
		now_lat = 21.920;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if(last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 210, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.890, 21.920, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.890, 21.920, out_haml + 210, 55));
		last_lon = 112.890;
		last_lat = 21.920;
		now_lon = 112.870;
		now_lat = 21.940;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 210, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.870, 21.940, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.870, 21.940, out_haml + 210, 55));
		last_lon = 112.870;
		last_lat = 21.940;
		now_lon = 112.870;
		now_lat = 21.950;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 210, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.870, 21.950, out_haml + 210, 55));
		last_lon = 112.870;
		last_lat = 21.950;
		now_lon = 112.910;
		now_lat = 21.960;
		lon_mean = (now_lon - last_lon) / 10;
		lat_mean = (now_lat - last_lat) / 10;

		if (last_lon < now_lon) {
			while (last_lon < now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;
			}
		}
		else if (last_lon - now_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), now_lon, now_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(now_lon, now_lat, out_haml + 210, 50));

		}
		else {
			while (last_lon > now_lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 210, 50));
				last_lon += lon_mean;
				last_lat += lat_mean;

			}
		}

		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.910, 21.960, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(112.910, 21.960, out_haml + 210, 55));
		apcPerson = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);
	}
}


//���ٷɻ�
void osgCoreLib::isTrackFly(bool btrack)
{



	if (btrack)
	{
		em->setTetherNode(flyAirport);

		gnodeboud0 = new osg::Geode;
		osg::BoundingSphere bs = mtFlySelf->getBound();
		osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(bs.center(), bs.radius()));
		sd->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.2));
		gnodeboud0->addDrawable(sd);
		gnodeboud0->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtfly->addChild(gnodeboud0);

	}
	else
	{

		em->setTetherNode(0);

		if (gnodeboud0 != 0)
		{
			mtfly->removeChild(gnodeboud0);
			gnodeboud0 = 0;
		}

	}


}

//���ٳ���
void osgCoreLib::isTrackCar(bool btrack)
{



	if (btrack)
	{
		em->setTetherNode(car);
		gnodeboud3 = new osg::Geode;
		osg::BoundingSphere bs = mtCarSelf->getBound();
		osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(bs.center(), bs.radius()));
		sd->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.2));
		gnodeboud3->addDrawable(sd);
		gnodeboud3->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtCar->addChild(gnodeboud3);

	}
	else
	{
		em->setTetherNode(0);
		mtCar->removeChild(gnodeboud3);
		gnodeboud3 = 0;
	}


}

//��������
void osgCoreLib::isTrackPerson(bool btrack)
{



	if (btrack)
	{
		em->setTetherNode(person);
		gnodeboud4 = new osg::Geode;
		osg::BoundingSphere bs = mtPersonSelf->getBound();
		osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(bs.center(), bs.radius()));
		sd->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.2));
		gnodeboud4->addDrawable(sd);
		gnodeboud4->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtPerson->addChild(gnodeboud4);

	}
	else
	{
		em->setTetherNode(0);
		mtPerson->removeChild(gnodeboud4);
		gnodeboud4 = 0;
	}


}

//��������Ŀ��Ƶ㣬���һ��·�������Ƶ�ĸ�ʽΪ������γ���ߣ��٣�
osg::AnimationPath* osgCoreLib::CreateAirLinePath(osg::Vec4Array* ctrl)
{
	osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath;
	animationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);

	double shuiPingAngle;
	double chuiZhiAngle;
	double time = 0;

	osg::Matrix matrix;
	osg::Quat _rotation;

	//��ǰ��
	osg::Vec3d positionCur;

	//��һ��
	osg::Vec3d positionNext;

	for (osg::Vec4Array::iterator iter = ctrl->begin();iter != ctrl->end(); iter++)
	{
		osg::Vec4Array::iterator iter2 = iter;
		iter2++;

		//��Ҫ�ж��ǲ����Ѿ�������
		//iter2++
		if (iter2 == ctrl->end())
		{
			break;
		}

		double x, y, z;
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter->y()), osg::DegreesToRadians(iter->x()), iter->z(), x, y, z);
		positionCur = osg::Vec3(x, y, z);
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter2->y()), osg::DegreesToRadians(iter2->x()), iter2->z(), x, y, z);
		positionNext = osg::Vec3(x, y, z);

		//���ˮƽ�н�
		if (iter->x() == iter2->x())
		{
			shuiPingAngle = osg::PI_2;
		}
		else {
			shuiPingAngle = atan((iter2->y() - iter->y()) / (iter2->x() - iter->x()));
			if (iter2->x() > iter->x())
			{
				shuiPingAngle += osg::PI;
			}
		}

		//��ֱ�н�
		if (iter->z() == iter2->z())
		{
			chuiZhiAngle = 0;
		}
		else {
			if (0 == sqrt(pow(GetDis(positionCur, positionNext), 2)) - pow((iter2->z() - iter->z()), 2))
			{
				chuiZhiAngle = osg::PI_2;
			}
			else {
				chuiZhiAngle = atan((iter2->z() - iter->z()) / sqrt(pow(GetDis(positionCur, positionNext), 2)) - pow((iter2->z() - iter->z()), 2));
			}

			if (chuiZhiAngle >= osg::PI_2)
				chuiZhiAngle = osg::PI_2;
			if (chuiZhiAngle <= -osg::PI_2)
			{
				chuiZhiAngle = -osg::PI_2;
			}
		}

		//��ɻ��ı任����
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(iter->y()),
			osg::DegreesToRadians(iter->x()), iter->z(), matrix);
		_rotation.makeRotate(0, osg::Vec3(1.0, 0.0, 0.0), chuiZhiAngle + osg::PI_2, osg::Vec3(0.0, 1.0, 0.0), shuiPingAngle, osg::Vec3(0.0, 0.0, 1.0));
		matrix.preMultRotate(_rotation);
		animationPath->insert(time, osg::AnimationPath::ControlPoint(positionCur, matrix.getRotate()));

		//����һ�����ʱ�������
		time += GetRunTime(positionCur, positionNext, iter2->w());
	}
	animationPath->insert(time, osg::AnimationPath::ControlPoint(positionNext, matrix.getRotate()));
	return animationPath.release();
}

osg::AnimationPath* osgCoreLib::CreateAirLinePath2(osg::Vec4Array* ctrl)
{
	osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath;
	animationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);

	double shuiPingAngle;
	double chuiZhiAngle;
	double time = 0;

	osg::Matrix matrix;
	osg::Quat _rotation;

	//��ǰ��
	osg::Vec3d positionCur;

	//��һ��
	osg::Vec3d positionNext;

	for (osg::Vec4Array::iterator iter = ctrl->begin();iter != ctrl->end(); iter++)
	{
		osg::Vec4Array::iterator iter2 = iter;
		iter2++;

		//��Ҫ�ж��ǲ����Ѿ�������
		//iter2++
		if (iter2 == ctrl->end())
		{
			break;
		}

		double x, y, z;
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter->y()), osg::DegreesToRadians(iter->x()), iter->z(), x, y, z);
		positionCur = osg::Vec3(x, y, z);
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter2->y()), osg::DegreesToRadians(iter2->x()), iter2->z(), x, y, z);
		positionNext = osg::Vec3(x, y, z);

		//�����ı任����
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(iter->y()),
			osg::DegreesToRadians(iter->x()), iter->z(), matrix);
		_rotation.makeRotate(0, osg::Vec3(1.0, 0.0, 0.0), 0, osg::Vec3(0.0, 1.0, 0.0), 0, osg::Vec3(0.0, 0.0, 1.0));
		matrix.preMultRotate(_rotation);
		animationPath->insert(time, osg::AnimationPath::ControlPoint(positionCur, matrix.getRotate()));

		//����һ�����ʱ�������
		time += GetRunTime(positionCur, positionNext, iter2->w());
	}
	animationPath->insert(time, osg::AnimationPath::ControlPoint(positionNext, matrix.getRotate()));
	return animationPath.release();
}


osg::AnimationPath* osgCoreLib::CreateAirLinePath3(osg::Vec4Array* ctrl)
{
	osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath;
	animationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);

	double shuiPingAngle;
	double chuiZhiAngle;
	double time = 0;

	osg::Matrix matrix;
	osg::Quat _rotation;

	//��ǰ��
	osg::Vec3d positionCur;

	//��һ��
	osg::Vec3d positionNext;

	for (osg::Vec4Array::iterator iter = ctrl->begin();iter != ctrl->end(); iter++)
	{
		osg::Vec4Array::iterator iter2 = iter;
		iter2++;

		//��Ҫ�ж��ǲ����Ѿ�������
		//iter2++
		if (iter2 == ctrl->end())
		{
			break;
		}

		double x, y, z;
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter->y()), osg::DegreesToRadians(iter->x()), iter->z(), x, y, z);
		positionCur = osg::Vec3(x, y, z);
		csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(iter2->y()), osg::DegreesToRadians(iter2->x()), iter2->z(), x, y, z);
		positionNext = osg::Vec3(x, y, z);

		//���ˮƽ�н�
		if (iter->x() == iter2->x())
		{
			shuiPingAngle = osg::PI_2;
		}
		else {
			shuiPingAngle = atan((iter2->y() - iter->y()) / (iter2->x() - iter->x()));
			if (iter2->x() > iter->x())
			{
				shuiPingAngle += osg::PI;
			}
		}

		//����Ա�ı任����
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(iter->y()),
			osg::DegreesToRadians(iter->x()), iter->z(), matrix);
		_rotation.makeRotate(0, osg::Vec3(1.0, 0.0, 0.0), 0, osg::Vec3(0.0, 1.0, 0.0), shuiPingAngle, osg::Vec3(0.0, 0.0, 1.0));
		matrix.preMultRotate(_rotation);
		animationPath->insert(time, osg::AnimationPath::ControlPoint(positionCur, matrix.getRotate()));

		//����һ�����ʱ�������
		time += GetRunTime(positionCur, positionNext, iter2->w());
	}
	animationPath->insert(time, osg::AnimationPath::ControlPoint(positionNext, matrix.getRotate()));
	return animationPath.release();
}

double osgCoreLib::GetDis(osg::Vec3 from, osg::Vec3 to)
{
	return sqrt((to.x() - from.x()) * (to.x() - from.x()) + (to.y() - from.y())*(to.y() - from.y()) + (to.z() - from.z())*(to.z() - from.z()));
}

double osgCoreLib::GetRunTime(osg::Vec3 from, osg::Vec3 to, double speed)
{
	double dist = GetDis(from, to);
	if (speed == 0)
		return 1000000000;
	return dist / speed;
}


//���
void osgCoreLib::isTestJu(bool isTest)
{

	if (isTest)
	{
		eh->isStartTest(true);
	}

}

void osgCoreLib::setModule(int module)
{
	if (module == 0) { stateSetMani->setPolygonMode(osg::PolygonMode::FILL); }
	else if (module == 1) { stateSetMani->setPolygonMode(osg::PolygonMode::LINE); }
	else if (module == 2) { stateSetMani->setPolygonMode(osg::PolygonMode::POINT); }

}

void osgCoreLib::swapStereo()
{
	osg::DisplaySettings::instance()->setStereo(!osg::DisplaySettings::instance()->getStereo());

}

osg::MatrixTransform* osgCoreLib::createCompressPart(const std::string & image, float radius, float height)
{
	osg::Vec3 center(-radius, -radius, height);
	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	gnode->addDrawable(createTexturedQuadGeometry(center, osg::Vec3(radius*2.0, 0.0f, 0.0f), osg::Vec3(0.0, radius*2.0, 0.0f)));

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setImage(osgDB::readImageFile(image));

	osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
	part->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
	part->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	part->addChild(gnode);
	return part.release();

}

void osgCoreLib::createCompress()
{
	_plate = createCompressPart("./label/compass_plate.PNG", 1.5, -1.0);
	_needle = createCompressPart("./label/compass_needle.PNG", 1.5, -1.0);

	osg::ref_ptr<osg::Camera> compass = new osg::Camera;
	compass->setViewport(0, 0, 128, 128);
	compass->setProjectionMatrix(osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10, 10));

	compass->setRenderOrder(osg::Camera::POST_RENDER);
	compass->setClearMask(GL_DEPTH_BUFFER_BIT);

	compass->setAllowEventFocus(false);
	compass->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	compass->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	compass->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	compass->addChild(_needle);
	compass->addChild(_plate);


	mRoot->addChild(compass);
}

void osgCoreLib::CreateRadar()
{
	radar = new osg::Camera;
	radar->setName("radar");

	radar->setClearColor(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	radar->setRenderOrder(osg::Camera::POST_RENDER);
	radar->setAllowEventFocus(false);
	radar->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	radar->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	radar->setViewport(0, 0, 256, 256);
	radar->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(256) / static_cast<double>(256), 1.0, 1000.0);

	osgEarth::Style styleair;
	osgEarth::Symbology::TextSymbol * textStyle = styleair.getOrCreateSymbol<osgEarth::Symbology::TextSymbol>();
	//������ɫ
	textStyle->fill()->color() = osg::Vec4f(1.0, 1.0, 1.0, 1.0);
	//���ñ߿�
	textStyle->halo()->color() = osg::Vec4f(0.0, 0.0, 0.0, 1.0);
	textStyle->font() = "simsun.ttc";
	textStyle->size() = 18.0;
	//textStyle->pixelOffset() = osg::Vec2s(0.1, 0.1);
	textStyle->alignment() = osgEarth::Symbology::TextSymbol::ALIGN_CENTER_TOP;
	textStyle->encoding() = osgEarth::Symbology::TextSymbol::ENCODING_UTF8;
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//osg::Image* china = osgDB::readImageFile("../../../builder/data/image/label/chinaIcon.jpg");
	airLabel = new osgEarth::Annotation::PlaceNode(mapNode, osgEarth::GeoPoint(geoSRS, 109.1263, 34.3762), 0, "����", styleair);

	osg::Image* flyImg = osgDB::readImageFile("./label/shi.png");

	osgEarth::Style styleairfly;
	textStyle = styleairfly.getOrCreateSymbol<osgEarth::Symbology::TextSymbol>();
	//������ɫ
	textStyle->fill()->color() = osg::Vec4f(1.0, 0.8, 0.8, 1.0);
	//���ñ߿�
	textStyle->halo()->color() = osg::Vec4f(0.0, 0.0, 0.0, 1.0);
	textStyle->font() = "simsun.ttc";
	textStyle->size() = 16.0;
	//textStyle->pixelOffset() = osg::Vec2s(0.1, 0.1);
	textStyle->alignment() = osgEarth::Symbology::TextSymbol::ALIGN_CENTER_BOTTOM;
	textStyle->encoding() = osgEarth::Symbology::TextSymbol::ENCODING_UTF8;

	//	osgEarth::Annotation::PlaceNode *pn = new osgEarth::Annotation::PlaceNode(mapNode, osgEarth::GeoPoint(geoSRS, 110, 34), china, "China", style);

	ffLabel = new osgEarth::Annotation::PlaceNode(mapNode, osgEarth::GeoPoint(geoSRS, 109.1347, 34.3834), 0, "����", styleairfly);

	radar->addChild(mapNode);
	radar->addChild(airLabel);
	radar->addChild(ffLabel);
	mRoot->addChild(radar);
}


void osgCoreLib::drawFlyLine()
{
	//��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//���˻�
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pFlyFeature = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_lineFlyStyle);
	m_pFlyFeatureNode = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pFlyFeature);


	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
	std::vector<osg::Vec3> m_vecPoint;
	m_vecPoint.push_back(osg::Vec3(112.885, 21.9483, 130));
	m_vecPoint.push_back(osg::Vec3(112.840, 21.905, 200));
	m_vecPoint.push_back(osg::Vec3(112.820, 21.930, 200));
	m_vecPoint.push_back(osg::Vec3(112.820, 21.940, 200));
	m_vecPoint.push_back(osg::Vec3(112.885, 21.9483, 200));

	mRoot->addChild(m_pFlyFeatureNode);

	m_pFlyFeature->getGeometry()->clear();
	m_pFlyFeatureNode->setStyle(m_lineFlyStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pFlyFeature->getGeometry()->push_back(m_vecPoint[i]);
	}

	m_pFlyFeatureNode->init();

}

void osgCoreLib::clearFlyLine()
{
	mRoot->removeChild(m_pFlyFeatureNode);
}

void osgCoreLib::drawCarLine()
{

	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Green;
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pCarFeature = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_lineCarStyle);
	m_pCarFeatureNode = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pCarFeature);


	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
	std::vector<osg::Vec3> m_vecPoint;
	m_vecPoint.push_back(osg::Vec3(112.900, 21.950, 50));
	m_vecPoint.push_back(osg::Vec3(112.880, 21.910, 130));
	m_vecPoint.push_back(osg::Vec3(112.860, 21.935, 130));
	m_vecPoint.push_back(osg::Vec3(112.860, 21.945, 130));
	m_vecPoint.push_back(osg::Vec3(112.900, 21.950, 50));

	mRoot->addChild(m_pCarFeatureNode);

	m_pCarFeature->getGeometry()->clear();
	m_pCarFeatureNode->setStyle(m_lineCarStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pCarFeature->getGeometry()->push_back(m_vecPoint[i]);
	}

	m_pCarFeatureNode->init();

}

void osgCoreLib::clearCarLine()
{
	mRoot->removeChild(m_pCarFeatureNode);
}

void osgCoreLib::drawPersonLine()
{
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Red;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pPersonFeature = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_linePersonStyle);
	m_pPersonFeatureNode = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pPersonFeature);

	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
	std::vector<osg::Vec3> m_vecPoint;
	m_vecPoint.push_back(osg::Vec3(112.910, 21.960, 80));
	m_vecPoint.push_back(osg::Vec3(112.890, 21.920, 80));
	m_vecPoint.push_back(osg::Vec3(112.870, 21.940, 80));
	m_vecPoint.push_back(osg::Vec3(112.870, 21.950, 80));
	m_vecPoint.push_back(osg::Vec3(112.910, 21.960, 80));
	mRoot->addChild(m_pPersonFeatureNode);

	m_pPersonFeature->getGeometry()->clear();
	m_pPersonFeatureNode->setStyle(m_linePersonStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pPersonFeature->getGeometry()->push_back(m_vecPoint[i]);
	}
	m_pPersonFeatureNode->init();
}

void osgCoreLib::clearPersonLine()
{
	mRoot->removeChild(m_pPersonFeatureNode);
}

//��ȡ���˻������ļ�
void osgCoreLib::readFlyCoords(char * filename) {
	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;
	std::vector<osg::Vec3> m_vecPoint;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.619053, 44.245049, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 100, 120));
		m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 100));
	}
	fin.close();

	////�������˻�·��
	//// ��ʼ����ͼ����
	//const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	////���˻�
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->stroke()->width() = 2.0;
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->tessellation() = 20.0;
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	//m_lineFlyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->verticalOffset() = 100;

	//m_pFlyFeature = new osgEarth::Features::Feature(
	//	new osgEarth::Annotation::LineString,
	//	geoSRS, m_lineFlyStyle);
	//m_pFlyFeatureNode = new osgEarth::Annotation::FeatureNode(
	//	mapNode, m_pFlyFeature);

	////�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	//mRoot->addChild(m_pFlyFeatureNode);

	//m_pFlyFeature->getGeometry()->clear();
	//m_pFlyFeatureNode->setStyle(m_lineFlyStyle);
	//for (int i = 0; i < m_vecPoint.size(); ++i)
	//{
	//	m_pFlyFeature->getGeometry()->push_back(m_vecPoint[i]);
	//}
	//m_pFlyFeatureNode->init();
	//���÷��й켣
	apcFly1 = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);

	//��ʼ����
	DoPreLineNow(true);
}


//��ȡ���������ļ�
void osgCoreLib::readCarCoords(char * filename) {

	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;

	//���ݾ�γ�Ȼ�ȡ�߳�
	double out_haml = 0.0;

	std::vector<osg::Vec3> m_vecCarPoint;
	osg::ref_ptr<osg::Vec4Array> vaCarTemp  = new osg::Vec4Array;;
	//��¼��һ�κ͵�ǰ��lon��lat
	double lon_mean = 0.0;
	double lat_mean = 0.0;

	int carLines = 0;
	double carLat = 0.0;
	double carLon = 0.0;
	int temp = 0;
	double lon, lat;
	fin >> lon >> lat;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 60));
	m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 15));
	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		double temp = 0.0;
	/*	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			temp, query_resolution, &out_resolution);*/
		/*if (abs(temp - out_haml) >= 3) {
			out_haml = temp;
		}*/
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 60));
		m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 15));
		
	}
	/*if (carLon < 0.000001) {
		while (getline(fin, line)) {
			double lon, lat;
			fin >> lon >> lat;
			if (temp == carLines) {
				carLines += 1;
				if (carLon < 0.000001) {
					query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
						out_haml, query_resolution, &out_resolution);
					vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 70));
					m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				}
				else {
					lon_mean = (lon - carLon) / 10;
					lat_mean = (lat - carLat) / 10;

					if (carLon < lon) {
						while (carLon < lon) {
							query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), carLon, carLat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
								out_haml, query_resolution, &out_resolution);
							vaCarTemp->push_back(osg::Vec4(carLon, carLat, out_haml + 1, 70));
							m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
							carLon += lon_mean;
							carLat += lat_mean;

						}
					}
					else if (carLon - lon < 0.000001) {
						query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
							out_haml, query_resolution, &out_resolution);
						vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 70));
						m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

					}
					else {
						while (carLon > lon) {
							query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), carLon, carLat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
								out_haml, query_resolution, &out_resolution);
							vaCarTemp->push_back(osg::Vec4(carLon, carLat, out_haml + 1, 70));
							m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
							carLon += lon_mean;
							carLat += lat_mean;
						}
					}
				}
			}
			temp += 1;
			carLon = lon;
			carLat = lat;
		}
	}
	else {
		vaCarTemp->clear();
		m_vecCarPoint.clear();
		while (getline(fin, line)) {
			double lon, lat;
			fin >> lon >> lat;
			if (temp == carLines) {
				carLines += 1;
				if (carLon < 0.000001) {
					query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
						out_haml, query_resolution, &out_resolution);
					vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 70));
					m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				}
				else {
					lon_mean = (lon - carLon) / 10;
					lat_mean = (lat - carLat) / 10;

					if (carLon < lon) {
						while (carLon < lon) {
							query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), carLon, carLat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
								out_haml, query_resolution, &out_resolution);
							vaCarTemp->push_back(osg::Vec4(carLon, carLat, out_haml + 1, 70));
							m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
							carLon += lon_mean;
							carLat += lat_mean;

						}
					}
					else if (carLon - lon < 0.000001) {
						query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
							out_haml, query_resolution, &out_resolution);
						vaCarTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 70));

					}
					else {
						while (carLon > lon) {
							query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), carLon, carLat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
								out_haml, query_resolution, &out_resolution);
							vaCarTemp->push_back(osg::Vec4(carLon, carLat, out_haml + 1, 70));
							m_vecCarPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
							carLon += lon_mean;
							carLat += lat_mean;
						}
					}
				}
			}
			temp += 1;
			carLon = lon;
			carLat = lat;
		}
	}*/

	fin.close();

	////���Ƴ���·��
	//// ��ʼ����ͼ����
	//const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	////����
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->stroke()->width() = 2.0;
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
	//	->tessellation() = 20.0;
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	//m_lineCarStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
	//	->verticalOffset() = 0.1;

	//m_pCarFeature = new osgEarth::Features::Feature(
	//	new osgEarth::Annotation::LineString,
	//	geoSRS, m_lineCarStyle);
	//m_pCarFeatureNode = new osgEarth::Annotation::FeatureNode(
	//	mapNode, m_pCarFeature);

	////�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	//mRoot->addChild(m_pCarFeatureNode);

	//m_pCarFeature->getGeometry()->clear();
	//m_pCarFeatureNode->setStyle(m_lineCarStyle);
	//for (int i = 0; i < m_vecCarPoint.size(); ++i)
	//{
	//	m_pCarFeature->getGeometry()->push_back(m_vecCarPoint[i]);
	//}
	//m_pCarFeatureNode->init();
	//���÷��й켣
	apcCar = new osg::AnimationPathCallback(CreateAirLinePath2(vaCarTemp), 0, 1);

	//��ʼ����
	DoPreLineNow2(true);
}

//��ȡ��Ա�����ļ�
void osgCoreLib::readPersonCoords(char * filename) {
	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;
	std::vector<osg::Vec3> m_vecPoint;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

	//���ݾ�γ�Ȼ�ȡ�߳�
	double out_haml = 0.0;

	//��¼��һ�κ͵�ǰ��lon��lat
	double last_lon = 0.0;
	double last_lat = 0.0;
	double lon_mean = 0.0;
	double lat_mean = 0.0;

	int temp = 0;
	
	double lon, lat;
	fin >> lon >> lat;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 40));
	m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 40));
		m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

	}
	/*while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		if (last_lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 40));
			m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
		}
		else {
			lon_mean = (lon - last_lon) / 10;
			lat_mean = (lat - last_lat) / 10;

			if (last_lon < lon) {
				while (last_lon < lon) {
					query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
						out_haml, query_resolution, &out_resolution);
					vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 1, 40));
					m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
					last_lon += lon_mean;
					last_lat += lat_mean;

				}
			}else if (last_lon - lon < 0.000001) {
					query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
						out_haml, query_resolution, &out_resolution);
					vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 1, 40));
					m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

				}
			else {
				while (last_lon > lon) {
					query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), last_lon, last_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
						out_haml, query_resolution, &out_resolution);
					vaTemp->push_back(osg::Vec4(last_lon, last_lat, out_haml + 1, 40));
					m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
					last_lon += lon_mean;
					last_lat += lat_mean;
				}
			}
		}
		last_lon = lon;
		last_lat = lat;
	}*/
	
	fin.close();
	/*
	//�������˻�·��
	// ��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//���˻�
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_linePersonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pPersonFeature = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_linePersonStyle);
	m_pPersonFeatureNode = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pPersonFeature);

	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	mRoot->addChild(m_pPersonFeatureNode);

	m_pPersonFeature->getGeometry()->clear();
	m_pPersonFeatureNode->setStyle(m_linePersonStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pPersonFeature->getGeometry()->push_back(m_vecPoint[i]);
	}
	m_pPersonFeatureNode->init();
	*/
	//���÷��й켣
	apcPerson = new osg::AnimationPathCallback(CreateAirLinePath3(vaTemp), 0, 1);

	//��ʼ����
	DoPreLineNow3(true);
}

//ͨ���������ģ�Ͳ����з���
void osgCoreLib::addFLyAndMove(char * filename, bool start) {
	//���˻�ģ��
	osg::ref_ptr<osg::Node> fly1;
	osg::ref_ptr<osg::MatrixTransform> mtFlySelf1;
	osg::ref_ptr<osg::MatrixTransform> mtfly1;

	//���˻�·��
	osgEarth::Symbology::Style m_lineFlyStyle1;
	osgEarth::Features::Feature* m_pFlyFeature1;
	osgEarth::Annotation::FeatureNode* m_pFlyFeatureNode1;
	osgEarth::Symbology::Style m_lineFlyStyle2;
	osgEarth::Features::Feature* m_pFlyFeature2;
	osgEarth::Annotation::FeatureNode* m_pFlyFeatureNode2;
	osgEarth::Symbology::Style m_lineFlyStyle3;
	osgEarth::Features::Feature* m_pFlyFeature3;
	osgEarth::Annotation::FeatureNode* m_pFlyFeatureNode3;

	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;
	std::vector<osg::Vec3> m_vecPoint;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

	if (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		//���ģ��
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());
		osg::Matrixd mtTemp;
		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		fly1 = osgDB::readNodeFile("./Module/fly/drone_costum.obj", a);
		fly1->setName("����");
		mtFlySelf1 = new osg::MatrixTransform;
		mtFlySelf1->setMatrix(osg::Matrixd::scale(20, 20, 20));
		mtFlySelf1->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		mtFlySelf1->addChild(fly1);

		mtfly1 = new osg::MatrixTransform;
		mtfly1->addChild(mtFlySelf1);
		mRoot->addChild(mtfly1);
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), 300, mtTemp);
		mtfly1->setMatrix(mtTemp);

		vaTemp->push_back(osg::Vec4(lon, lat, 300, 50));
		m_vecPoint.push_back(osg::Vec3(lon, lat, 300));

	}

	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		vaTemp->push_back(osg::Vec4(lon, lat, 300, 50));
		m_vecPoint.push_back(osg::Vec3(lon, lat, 300));
	}
	fin.close();

	//�������˻�·��
	// ��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//���˻�
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineFlyStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pFlyFeature1 = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_lineFlyStyle1);
	m_pFlyFeatureNode1 = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pFlyFeature1);

	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	mRoot->addChild(m_pFlyFeatureNode1);

	m_pFlyFeature1->getGeometry()->clear();
	m_pFlyFeatureNode1->setStyle(m_lineFlyStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pFlyFeature1->getGeometry()->push_back(m_vecPoint[i]);
	}
	m_pFlyFeatureNode1->init();
	//���÷��й켣
	//���˻�
	osg::ref_ptr<osg::AnimationPathCallback> apcFly2;
	apcFly2 = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);

	//��ʼ����
	if (start)
	{
		mtFlySelf1->setMatrix(osg::Matrixd::scale(10, 10, 10) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));
		mtfly1->setUpdateCallback(apcFly2);
		em->setViewpoint(osgEarth::Viewpoint("", 112.885, 21.9483, 0, 24.261, -21.6, 1000), 1);
		//���ٷɻ�
		apcFly2->reset();
		BuildRibbonFly0(512, mtfly1);

		gnodeboud0 = new osg::Geode;
		//���Բ�α߿�
		gnodeboud0->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtfly1->addChild(gnodeboud0);
		start = !start;

	}
	else
	{
		start = !start;
		mtFlySelf1->setMatrix(osg::Matrixd::scale(10, 10, 10) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 0.0f, 1.0f, 0.0f));

		osg::Matrix mtTemp;
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.947), osg::DegreesToRadians(112.874), 300, mtTemp);
		mtfly1->setMatrix(mtTemp);
		mtfly1->removeUpdateCallback(apcFly2);
		//em->setTetherNode(0);
		em->setViewpoint(osgEarth::Viewpoint("", 112.885, 21.9483, 0, 24.261, -21.6, 1000), 1);
		mtfly1->removeUpdateCallback(tcFly0);
		tcFly0 = 0;
		mRoot->removeChild(gnodeFly0);
		gnodeFly0 = 0;
	}
}


void osgCoreLib::addCarAndMove(char * filename, bool start) {
	//����ģ��
	osg::ref_ptr<osg::Node> car1;
	osg::ref_ptr<osg::MatrixTransform> mtCarSelf1;
	osg::ref_ptr<osg::MatrixTransform> mtCar1;

	//����·��
	osgEarth::Symbology::Style m_lineCarStyle1;
	osgEarth::Features::Feature* m_pCarFeature1;
	osgEarth::Annotation::FeatureNode* m_pCarFeatureNode1;
	osgEarth::Symbology::Style m_lineCarStyle2;
	osgEarth::Features::Feature* m_pCarFeature2;
	osgEarth::Annotation::FeatureNode* m_pCarFeatureNode2;
	osgEarth::Symbology::Style m_lineCarStyle3;
	osgEarth::Features::Feature* m_pCarFeature3;
	osgEarth::Annotation::FeatureNode* m_pCarFeatureNode3;
	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;
	std::vector<osg::Vec3> m_vecPoint;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

	//��¼��һ�κ͵�ǰ��lon��lat
	double car_lon = 0.0;
	double car_lat = 0.0;
	double lon_mean = 0.0;
	double lat_mean = 0.0;
	double out_haml = 0.0;

	//���ģ��
	if (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());

		osg::Matrixd mtTemp;
		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		car1 = osgDB::readNodeFile("./Module/car/van car.obj", a);

		car1->setName("Car");
		mtCarSelf1 = new osg::MatrixTransform;
		mtCarSelf1->setMatrix(osg::Matrixd::scale(15, 15, 15));
		mtCarSelf1->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		mtCarSelf1->addChild(car1);

		mtCar1 = new osg::MatrixTransform;
		mtCar1->addChild(mtCarSelf1);
		mRoot->addChild(mtCar1);
		//���ݾ�γ�Ȼ�ȡ�߳�
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), out_haml + 5, mtTemp);
		mtCar1->setMatrix(mtTemp);
		vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 50));
		m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
		car_lon = lon;
		car_lat = lat;
	}
	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		lon_mean = (lon - car_lon) / 20;
		lat_mean = (lat - car_lat) / 20;

		if (car_lon < lon) {
			while (car_lon < lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), car_lon, car_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(car_lon, car_lat, out_haml + 5, 50));
				m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				car_lon += lon_mean;
				car_lat += lat_mean;

			}
		}
		else if (car_lon - lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 50));
			m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		}
		else {
			while (car_lon > lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), car_lon, car_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(car_lon, car_lat, out_haml + 5, 50));
				m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				car_lon += lon_mean;
				car_lat += lat_mean;
			}
		}
		car_lon = lon;
		car_lat = lat;
	}
	fin.close();

	// ��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//����
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Green;
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineCarStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pCarFeature1 = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_lineCarStyle1);
	m_pCarFeatureNode1 = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pCarFeature1);

	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	mRoot->addChild(m_pCarFeatureNode1);

	m_pCarFeature1->getGeometry()->clear();
	m_pCarFeatureNode1->setStyle(m_lineCarStyle1);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pCarFeature1->getGeometry()->push_back(m_vecPoint[i]);
	}
	m_pCarFeatureNode1->init();
	//����
	osg::ref_ptr<osg::AnimationPathCallback> apcCar1;
	//���÷��й켣
	apcCar1 = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);

	//��ʼ����
	if (start)
	{
		start = !start;
		mtCarSelf1->setMatrix(osg::Matrixd::scale(15, 15, 15) * osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f));

		mtCar1->setUpdateCallback(apcCar1);
		em->setViewpoint(osgEarth::Viewpoint("", 81.619053, 44.245049, 0, 24.261, -21.6, 1000), 1);
		apcCar1->reset();
		BuildRibbonCar(512, mtCar1);

		gnodeboud3 = new osg::Geode;
		gnodeboud3->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtCar1->addChild(gnodeboud3);

	}
	else
	{
		start = !start;
		mtCarSelf1->setMatrix(osg::Matrixd::scale(15, 15, 15) * osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 0.0f, 1.0f));

		//���ݾ�γ�Ȼ�ȡ�߳�
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.900, 21.950, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		osg::Matrix mtTemp;
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.950), osg::DegreesToRadians(112.900), out_haml + 5, mtTemp);
		mtCar1->setMatrix(mtTemp);
		mtCar1->removeUpdateCallback(apcCar1);
		//em->setTetherNode(0);
		em->setViewpoint(osgEarth::Viewpoint("", 81.619053, 44.245049, 0, 24.261, -21.6, 1000), 1);
		mtCar1->removeUpdateCallback(tcCar);
		tcCar = 0;
		mRoot->removeChild(gnodeCar);
		gnodeCar = 0;
	}
}


void osgCoreLib::addPersonAndMove(char * filename, bool start) {

	//��Աģ��
	osg::ref_ptr<osg::Node> person1;
	osg::ref_ptr<osg::MatrixTransform> mtPersonSelf1;
	osg::ref_ptr<osg::MatrixTransform> mtPerson1;
	//��Ա·��
	osgEarth::Symbology::Style m_linePersonStyle1;
	osgEarth::Features::Feature* m_pPersonFeature1;
	osgEarth::Annotation::FeatureNode* m_pPersonFeatureNode1;
	osgEarth::Symbology::Style m_linePersonStyle2;
	osgEarth::Features::Feature* m_pPersonFeature2;
	osgEarth::Annotation::FeatureNode* m_pPersonFeatureNode2;
	osgEarth::Symbology::Style m_linePersonStyle3;
	osgEarth::Features::Feature* m_pPersonFeature3;
	osgEarth::Annotation::FeatureNode* m_pPersonFeatureNode3;
	//��ȡ�ļ�
	char tempChar[256];
	std::fstream fin(filename, std::ios::in);
	string line;
	std::vector<osg::Vec3> m_vecPoint;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;

	//��¼��һ�κ͵�ǰ��lon��lat
	double person_lon = 0.0;
	double person_lat = 0.0;
	double lon_mean = 0.0;
	double lat_mean = 0.0;
	double out_haml = 0.0;

	if (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;

		//���ģ��
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());
		osg::Matrixd mtTemp;
		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		person1 = osgDB::readNodeFile("./Module/person/c_zom_der_richtofen_cin_fb.obj", a);
		/*person1 = osgDB::readNodeFile("./Module/person2/Naruto.fbx");*/
		////��ýڵ�Ķ����б�
		//osgAnimation::BasicAnimationManager* anim =
		//	dynamic_cast<osgAnimation::BasicAnimationManager*>(person1->getUpdateCallback());
		//const osgAnimation::AnimationList& list = anim->getAnimationList();
		////�Ӷ����б���ѡ��һ������������
		//anim->playAnimation(list[0].get());
		//�Ż�ģ��
		person1->setName("Person");
		mtPersonSelf1 = new osg::MatrixTransform;
		mtPersonSelf1->setMatrix(osg::Matrixd::scale(2, 2, 2));
		mtPersonSelf1->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		mtPersonSelf1->addChild(person1);

		mtPerson1 = new osg::MatrixTransform;
		mtPerson1->addChild(mtPersonSelf1);
		mRoot->addChild(mtPerson1);
		//���ݾ�γ�Ȼ�ȡ�߳�
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), out_haml + 5, mtTemp);
		mtPerson1->setMatrix(mtTemp);
		vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 50));
		m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
		person_lon = lon;
		person_lat = lat;
	}
	while (getline(fin, line)) {
		double lon, lat;
		fin >> lon >> lat;
		lon_mean = (lon - person_lon) / 10;
		lat_mean = (lat - person_lat) / 10;

		if (person_lon < lon) {
			while (person_lon < lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), person_lon, person_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(person_lon, person_lat, out_haml + 5, 50));
				m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				person_lon += lon_mean;
				person_lat += lat_mean;

			}
		}
		else if (person_lon - lon < 0.000001) {
			query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
				out_haml, query_resolution, &out_resolution);
			vaTemp->push_back(osg::Vec4(lon, lat, out_haml + 5, 50));
			m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		}
		else {
			while (person_lon > lon) {
				query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), person_lon, person_lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
					out_haml, query_resolution, &out_resolution);
				vaTemp->push_back(osg::Vec4(person_lon, person_lat, out_haml + 5, 50));
				m_vecPoint.push_back(osg::Vec3(lon, lat, out_haml + 5));
				person_lon += lon_mean;
				person_lat += lat_mean;
			}
		}
		person_lon = lon;
		person_lat = lat;
	}
	fin.close();

	// ��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//���˻�
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Red;
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_linePersonStyle1.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_pPersonFeature1 = new osgEarth::Features::Feature(
		new osgEarth::Annotation::LineString,
		geoSRS, m_linePersonStyle1);
	m_pPersonFeatureNode1 = new osgEarth::Annotation::FeatureNode(
		mapNode, m_pPersonFeature1);

	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�


	mRoot->addChild(m_pPersonFeatureNode1);

	m_pPersonFeature1->getGeometry()->clear();
	m_pPersonFeatureNode1->setStyle(m_linePersonStyle1);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pPersonFeature1->getGeometry()->push_back(m_vecPoint[i]);
	}
	m_pPersonFeatureNode1->init();
	//���÷��й켣

	osg::ref_ptr<osg::AnimationPathCallback> apcPerson1;
	apcPerson1 = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);
	//��ʼ����
	if (start)
	{
		start = !start;
		mtPersonSelf1->setMatrix(osg::Matrixd::scale(2, 2, 2) * osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));
		mtPerson1->setUpdateCallback(apcPerson1);
		em->setViewpoint(osgEarth::Viewpoint("", 112.910, 21.960, 0, 24.261, -21.6, 1000), 1);
		
		apcPerson1->reset();
		//��Ӷ���
		struct AnimationManagerFinder : public osg::NodeVisitor
		{
			osg::ref_ptr<osgAnimation::BasicAnimationManager> _am;
			AnimationManagerFinder() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {}
			void apply(osg::Node* node) {
				if (_am.valid())
					return;
				if (node->getUpdateCallback()) {
					osgAnimation::AnimationManagerBase* b = dynamic_cast<osgAnimation::AnimationManagerBase*>(node->getUpdateCallback());
					if (b) {
						_am = new osgAnimation::BasicAnimationManager(*b);
						return;
					}
				}
				traverse(*node);
			}
		};

		//��ýڵ�Ķ����б�
		AnimationManagerFinder  *m_cFinder = new AnimationManagerFinder();
		m_cFinder->apply(person);
		person->accept(*m_cFinder);
		if (m_cFinder->_am.valid())
		{
			person->addUpdateCallback(m_cFinder->_am.get());
		}
		osgAnimation::AnimationList::const_iterator it = m_cFinder->_am->getAnimationList().begin();
		it++;
		it++;
		it++;
		std::string animationName = (*it)->getName();
		osgAnimation::Animation::PlayMode playMode = osgAnimation::Animation::LOOP;
		(*it)->setPlayMode(playMode);//���ò���ģʽ
		(*it)->setDuration(2.0);//���ò���ʱ��

								//�Ӷ����б���ѡ��һ������������
		m_cFinder->_am->playAnimation(*it);
		/*BuildRibbonPerson(512, mtPerson1);

		gnodeboud4 = new osg::Geode;
		gnodeboud4->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtPerson1->addChild(gnodeboud4);*/

	}
	else
	{
		start = !start;
		mtPersonSelf1->setMatrix(osg::Matrixd::scale(2, 2, 2) * osg::Matrixd::rotate(osg::inDegrees(180.f), 0.0f, 0.0f, 1.0f));
		//���ݾ�γ�Ȼ�ȡ�߳�
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 112.910, 21.960, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		osg::Matrix mtTemp;
		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.960), osg::DegreesToRadians(112.910), out_haml + 5, mtTemp);
		mtPerson1->setMatrix(mtTemp);
		mtPerson1->removeUpdateCallback(apcPerson1);
		em->setViewpoint(osgEarth::Viewpoint("", 112.910, 21.960, 0, 24.261, -21.6, 1000), 1);
		mtPerson1->removeUpdateCallback(tcPerson);
		tcPerson = 0;
		mRoot->removeChild(gnodePerson);
		gnodePerson = 0;
	}

}


//��������
void osgCoreLib::addSatellite() {
	//=============================================������������====================================================================
	csn = new osg::CoordinateSystemNode;
	osg::Matrixd mtTemp4;
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	satellite2 = osgDB::readNodeFile("./Module/satellite/satellite.ive");

	satellite2->setName("Satellite");
	mtSatelliteSelf2 = new osg::MatrixTransform;
	mtSatelliteSelf2->setMatrix(osg::Matrixd::scale(8000, 8000, 8000));
	mtSatelliteSelf2->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtSatelliteSelf2->addChild(satellite2);

	mtSatellite2 = new osg::MatrixTransform;
	mtSatellite2->addChild(mtSatelliteSelf2);
	mRoot->addChild(mtSatellite2);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.950), osg::DegreesToRadians(112.900), 3000000, mtTemp4);
	mtSatellite2->setMatrix(mtTemp4);
	//=============================================������������====================================================================


	//=============================================����Բ׶������====================================================================
	osg::ref_ptr<osg::Cone>  cone = new osg::Cone;
	osg::ref_ptr<osg::ShapeDrawable> shap = new osg::ShapeDrawable(cone);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(shap);

	//����Բ׶��
	cone->setHeight(2500000);
	//����Բ׶����뾶
	cone->setRadius(300000);

	//cone->setCenter(osg::Vec3(21.950, 112.900, 3000000));
	//����Բ׶����ɫ�����ĸ�����0.25��ʾ��͸���ȣ�0��ʾ��ȫ͸����1��ʾ��ȫ��͸��
	shap->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.5));

	//����Բ׶͸��Ч��
	osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	//����Բ׶����ģ��
	/*osg::ref_ptr<osg::PolygonMode> polyMode = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	stateset->setAttribute(polyMode);*/

	//���Բ׶���ĵ��λ�ã�Բ׶�����ĵ���Բ׶��1/3���ĵط�
	printf("center: %d,%d,%d\n", cone->getCenter()._v[0], cone->getCenter()._v[1], cone->getCenter()._v[2]);
	printf("radius:%f\n", cone->getRadius());
	printf("height:%f\n", cone->getHeight());
	//��������
	osg::ref_ptr<osg::Image> image1 = new osg::Image;
	osg::ref_ptr<osg::Image> image2 = new osg::Image;
	osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;

	image1 = osgDB::readImageFile("./pics/mat2.png");
	image2 = osgDB::readImageFile("./pics/mat3.png");


	texture2D->setImage(image1);

	stateset->setTextureAttributeAndModes(0, texture2D.get(), osg::StateAttribute::ON);
	bool entry = true;

	//ʹԲ׶��Ĭ�ϵ�z�᷽����ת��(1.0,1.0,1.0)����
	//osg::Quat quat;
	////������������������Ԫ��
	//quat.makeRotate(osg::Z_AXIS, osg::Vec3(1.0, 1.0, 1.0));
	//cone->setRotation(quat);
	osg::ref_ptr<osg::MatrixTransform> mtSatellite2 = new osg::MatrixTransform;
	mtSatellite2->addChild(geode);
	mRoot->addChild(mtSatellite2);

	osg::Matrixd mtTemp2;
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.950), osg::DegreesToRadians(112.900), 1100000, mtTemp2);
	mtSatellite2->setMatrix(mtTemp2);

	//=============================================����Բ׶������====================================================================
	
	//=============================================�����������====================================================================
	csn = new osg::CoordinateSystemNode;
	osg::Matrixd mtTemp;
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	satellite = osgDB::readNodeFile("./Module/satellite/satellite.ive");

	satellite->setName("Satellite2");
	mtSatelliteSelf = new osg::MatrixTransform;
	mtSatelliteSelf->setMatrix(osg::Matrixd::scale(12000, 12000, 12000));
	mtSatelliteSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtSatelliteSelf->addChild(satellite);

	mtSatellite = new osg::MatrixTransform;
	mtSatellite->addChild(mtSatelliteSelf);
	mRoot->addChild(mtSatellite);
	//csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(21.950), osg::DegreesToRadians(112.900), 3000000, mtTemp);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromXYZ(9371000 * sin(0.02), -0.0, 9371000 * cos(0.02), mtTemp);
	mtSatellite->setMatrix(mtTemp);
	//=============================================�����������====================================================================

	//=============================================����Բ====================================================================
	//�����߿�
	osg::ref_ptr<osg::LineWidth> lineSize = new osg::LineWidth;
	lineSize->setWidth(4.0);


	osg::ref_ptr<osg::StateSet> stateSet = mRoot->getOrCreateStateSet();
	//���߿�����
	stateSet->setAttributeAndModes(lineSize, osg::StateAttribute::ON);

	//Բ�ļ��νڵ�
	osg::ref_ptr<osg::Geode> clockGeode = new osg::Geode;
	//ԲȦ
	osg::ref_ptr<osg::Geometry> clockGeometry = new osg::Geometry;

	//clockGeode->addChild(clockGeometry);
	//clockGeode->addChild(numPoint);
	//mRoot->addChild(clockGeode);

	//�������Բ�ϵĵ㣬����Щ�����ӳ�ֱ�߻���Բ
	osg::ref_ptr<osg::Vec3Array> allPoints = new osg::Vec3Array;
	//Բ��ɫ
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec4Array> vaTemp = new osg::Vec4Array;
	
	//�õ��뾶Ϊ50���ӱ��314���㣬��Щ���γ����������
	//417
	for (double i = 0.0; i < 31.4;i += 0.02) {
		colors->push_back(osg::Vec4f(sin(i), cos(i), 0.5, 1.0));
		allPoints->push_back(osg::Vec3(9371000 * sin(i), -0.0, 9371000 * cos(i)));
		//vaTemp->push_back(osg::Vec4(lon, lat, 300, 50));
		double lat, lon, height;
		csn->getEllipsoidModel()->convertXYZToLatLongHeight(9371000 * sin(i), -0.0, 9371000 * cos(i), lat, lon, height);
		vaTemp->push_back(osg::Vec4(lat, lon, height, 300));
	}

	//���ö���  
	clockGeometry->setVertexArray(allPoints);

	//����
	clockGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, allPoints->size()));

	//clockGeometry->addPrimitiveSet(new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_LOOP, 0));
	//clockGeometry->setColorArray(colors);
	//clockGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	//osg::ref_ptr<osg::MatrixTransform> mtSatellite3 = new osg::MatrixTransform;
	//mtSatellite3->addChild(clockGeometry);

	//����
	osg::ref_ptr<osg::AnimationPathCallback> apcSatellite;
	//���÷��й켣
	apcSatellite = new osg::AnimationPathCallback(CreateAirLinePath(vaTemp), 0, 1);
	bool start = true;
	//��ʼ����
	if (start)
	{
		start = !start;
		mtSatelliteSelf->setMatrix(osg::Matrixd::scale(120000, 120000, 120000));

		mtSatellite->setUpdateCallback(apcSatellite);
		//em->setViewpoint(osgEarth::Viewpoint("", 112.900, 21.950, 0, 24.261, -21.6, 1000), 1);
		apcSatellite->reset();
		BuildRibbonCar(512, mtSatellite);

		gnodeboud3 = new osg::Geode;
		gnodeboud3->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		mtSatellite->addChild(gnodeboud3);

	}
	else
	{
		start = !start;
		mtSatelliteSelf->setMatrix(osg::Matrixd::scale(120000, 120000, 120000));

		//���ݾ�γ�Ȼ�ȡ�߳�
		osg::Matrix mtTemp;
		mtSatellite->setMatrix(mtTemp);
		mtSatellite->removeUpdateCallback(apcSatellite);
		//em->setTetherNode(0);
		//em->setViewpoint(osgEarth::Viewpoint("", 112.900, 21.950, 0, 24.261, -21.6, 1000), 1);
		mtSatellite->removeUpdateCallback(tcCar);
		tcCar = 0;
		mRoot->removeChild(gnodeCar);
		gnodeCar = 0;
	}
	//=============================================����Բ====================================================================
}


//�����������
void osgCoreLib::addDataCenter() {
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	osg::ref_ptr<osg::Node> center = osgDB::readNodeFile("./Module/data_center/globe.obj");

	center->setName("��������");
	osg::ref_ptr<osg::MatrixTransform> mtCenterSelf = new osg::MatrixTransform;
	mtCenterSelf->setMatrix(osg::Matrixd::scale(10, 10, 10));
	mtCenterSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtCenterSelf->addChild(center);

	osg::ref_ptr<osg::MatrixTransform> mtCenter = new osg::MatrixTransform;
	mtCenter->addChild(mtCenterSelf);
	mRoot->addChild(mtCenter);

	osg::Matrixd mtTemp;
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(30.533789), osg::DegreesToRadians(114.363194), 1000, mtTemp);
	mtCenter->setMatrix(mtTemp);
	
}



void osgCoreLib::drawFlood()
{
	//��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//���ƾ���
	osgEarth::Symbology::Style m_lakeStyle;
	osgEarth::Annotation::FeatureNode* m_pLakeNode;
	
	m_lakeStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color::Color(0.0, 0.27, 0.42, 1.0);
	m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
		new osgEarth::Symbology::Polygon,
		geoSRS, m_lakeStyle);
	m_pLakeNode = new osgEarth::Annotation::FeatureNode(
		mapNode, pFeature);


	//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
	std::vector<osg::Vec3> m_vecPoint;
	m_vecPoint.push_back(osg::Vec3(86.32, 44.36, 130));
	m_vecPoint.push_back(osg::Vec3(86.32, 46.50, 130));
	m_vecPoint.push_back(osg::Vec3(87.50, 46.50, 130));
	m_vecPoint.push_back(osg::Vec3(87.50, 44.36, 130));

	

	pFeature->getGeometry()->clear();
	m_pLakeNode->setStyle(m_lakeStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		pFeature->getGeometry()->push_back(m_vecPoint[i]);
	}

	m_pLakeNode->init();
	//m_pLakeNode->addUpdateCallback(new UpdateFlood());
	mRoot->addChild(m_pLakeNode);
}


void osgCoreLib::drawPollution() 
{
	osgEarth::Map *map = mapNode->getMap();
	{
		osgEarth::Drivers::OGRFeatureOptions featureOptions;
		featureOptions.url() = "./111/4.shp";

		osgEarth::Style style;
		osgEarth::PolygonSymbol* ps = style.getOrCreateSymbol<osgEarth::PolygonSymbol>();
		ps->fill()->color() = osgEarth::Symbology::Color::Color(0.20, 0.48, 0.12, 0.8);

		osgEarth::Drivers::AGGLiteOptions2 rasterOptions;
		rasterOptions.featureOptions() = featureOptions;
		rasterOptions.styles() = new osgEarth::StyleSheet();
		rasterOptions.styles()->addStyle(style);
		rasterOptions.borderColor() = osgEarth::Symbology::Color::Color(0.20, 0.48, 0.12, 0.8);//������ɫ
		rasterOptions.borderWidth() = 7.0f;//���߿�ȣ���λ���أ�
		map->addImageLayer(new osgEarth::ImageLayer("my features", rasterOptions));
	}
	{
		osgEarth::Drivers::OGRFeatureOptions featureOptions;
		featureOptions.url() = "./111/3.shp";

		osgEarth::Style style;
		osgEarth::PolygonSymbol* ps = style.getOrCreateSymbol<osgEarth::PolygonSymbol>();
		ps->fill()->color() = osgEarth::Symbology::Color::Color(0.10, 0.38, 0.12, 0.8);

		osgEarth::Drivers::AGGLiteOptions2 rasterOptions;
		rasterOptions.featureOptions() = featureOptions;
		rasterOptions.styles() = new osgEarth::StyleSheet();
		rasterOptions.styles()->addStyle(style);
		rasterOptions.borderColor() = osgEarth::Symbology::Color::Color(0.10, 0.38, 0.12, 0.8);//������ɫ
		rasterOptions.borderWidth() = 7.0f;//���߿�ȣ���λ���أ�
		map->addImageLayer(new osgEarth::ImageLayer("my features", rasterOptions));
	}
	{
		osgEarth::Drivers::OGRFeatureOptions featureOptions;
		featureOptions.url() = "./111/2.shp";

		osgEarth::Style style;
		osgEarth::PolygonSymbol* ps = style.getOrCreateSymbol<osgEarth::PolygonSymbol>();
		ps->fill()->color() = osgEarth::Symbology::Color::Color(0.59, 0.57, 0.09, 0.8);

		osgEarth::Drivers::AGGLiteOptions2 rasterOptions;
		rasterOptions.featureOptions() = featureOptions;
		rasterOptions.styles() = new osgEarth::StyleSheet();
		rasterOptions.styles()->addStyle(style);
		rasterOptions.borderColor() = osgEarth::Symbology::Color::Color(0.59, 0.57, 0.09, 0.8);//������ɫ
		rasterOptions.borderWidth() = 7.0f;//���߿�ȣ���λ���أ�
		map->addImageLayer(new osgEarth::ImageLayer("my features", rasterOptions));
	}
	{
		osgEarth::Drivers::OGRFeatureOptions featureOptions;
		featureOptions.url() = "./111/1.shp";

		osgEarth::Style style;
		osgEarth::PolygonSymbol* ps = style.getOrCreateSymbol<osgEarth::PolygonSymbol>();
		ps->fill()->color() = osgEarth::Symbology::Color::Color(0.58, 0.20, 0.22, 0.8);

		osgEarth::Drivers::AGGLiteOptions2 rasterOptions;
		rasterOptions.featureOptions() = featureOptions;
		rasterOptions.styles() = new osgEarth::StyleSheet();
		rasterOptions.styles()->addStyle(style);
		rasterOptions.borderColor() = osgEarth::Symbology::Color::Color(0.58, 0.20, 0.22, 0.8);//������ɫ
		rasterOptions.borderWidth() = 7.0f;//���߿�ȣ���λ���أ�
		map->addImageLayer(new osgEarth::ImageLayer("my features", rasterOptions));
	}
}


//�������ݴ�����·
void osgCoreLib::drawLink()
{
	//��ʼ����ͼ����
	const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	//��ȡcar�ڵ����ڵ���������// ��ʼ����ͼ����
	osgEarth::Symbology::Style m_lineLakeStyle;
	m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Blue;
	m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 4.0;
	m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineLakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
	m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->stipple() = 255;
	{	
		osgEarth::Features::Feature* m_pLakeFeature;
		std::vector<osg::Vec3> m_vecLakePoint;
		m_pLakeFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			geoSRS, m_lineLakeStyle);
		m_pLakeFeatureNode = new osgEarth::Annotation::FeatureNode(
			mapNode, m_pLakeFeature);
		osg::Vec3 center = car->getBound().center() * car->getWorldMatrices()[0];
		double lon, lat, height;
		//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
		csn->getEllipsoidModel()->convertXYZToLatLongHeight(center.x(), center.y(), center.z(), lat, lon, height);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon), osg::RadiansToDegrees(lat), height));

		//��ȡplane�ڵ����ڵ���������
		osg::Vec3 center1 = flyAirport->getBound().center() * flyAirport->getWorldMatrices()[0];
		double lon1, lat1, height1;
		//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
		csn->getEllipsoidModel()->convertXYZToLatLongHeight(center1.x(), center1.y(), center1.z(), lat1, lon1, height1);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon1), osg::RadiansToDegrees(lat1), height1));

		//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
		m_pLakeFeature->getGeometry()->clear();
		m_pLakeFeatureNode->setStyle(m_lineLakeStyle);
		for (int i = 0; i < m_vecLakePoint.size(); ++i)
		{
			m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
		}

		m_pLakeFeatureNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
		m_pLakeFeatureNode->init();
		m_pLakeFeatureNode->addUpdateCallback(new UpdateLink(flyAirport, car));
		mRoot->addChild(m_pLakeFeatureNode);
	}
	{

		osgEarth::Features::Feature* m_pLakeFeature;
		std::vector<osg::Vec3> m_vecLakePoint;
		m_pLakeFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			geoSRS, m_lineLakeStyle);
		m_pLakeFeatureNode2 = new osgEarth::Annotation::FeatureNode(
			mapNode, m_pLakeFeature);
		osg::Vec3 center = person->getBound().center() * person->getWorldMatrices()[0];
		double lon, lat, height;
		//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
		csn->getEllipsoidModel()->convertXYZToLatLongHeight(center.x(), center.y(), center.z(), lat, lon, height);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon), osg::RadiansToDegrees(lat), height));

		//��ȡplane�ڵ����ڵ���������
		osg::Vec3 center1 = flyAirport->getBound().center() * flyAirport->getWorldMatrices()[0];
		double lon1, lat1, height1;
		//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
		csn->getEllipsoidModel()->convertXYZToLatLongHeight(center1.x(), center1.y(), center1.z(), lat1, lon1, height1);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon1), osg::RadiansToDegrees(lat1), height1));

		//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
		m_pLakeFeature->getGeometry()->clear();
		m_pLakeFeatureNode2->setStyle(m_lineLakeStyle);
		for (int i = 0; i < m_vecLakePoint.size(); ++i)
		{
			m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
		}
		m_pLakeFeatureNode2->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
		m_pLakeFeatureNode2->init();
		m_pLakeFeatureNode2->addUpdateCallback(new UpdateLink(flyAirport, person));
		mRoot->addChild(m_pLakeFeatureNode2);
	}
}

void osgCoreLib::hideLink() {
	mRoot->removeChild(m_pLakeFeatureNode);
	mRoot->removeChild(m_pLakeFeatureNode2);
}

void osgCoreLib::showImageLayer2015() {
	imageLayer2015 = map->getImageLayerByName("2015Image");
	imageLayer2015->setVisible(true);
}

void osgCoreLib::hideImageLayer2015() {
	imageLayer2015 = map->getImageLayerByName("2015Image");
	imageLayer2015->setVisible(false);
}

void osgCoreLib::showImageLayer2017() {
	imageLayer2017 = map->getImageLayerByName("2017Image");
	imageLayer2017->setVisible(true);
}

void osgCoreLib::hideImageLayer2017()
{
	imageLayer2017 = map->getImageLayerByName("2017Image");
	imageLayer2017->setVisible(false);
}

void osgCoreLib::showCliassificationImageLayer2015() {
	cliassificationImage2015 = map->getImageLayerByName("2015classificationImage");
	cliassificationImage2015->setVisible(true);
}
void osgCoreLib::hideCliassificationImageLayer2015() {
	cliassificationImage2015 = map->getImageLayerByName("2015classificationImage");
	cliassificationImage2015->setVisible(false);
}

void osgCoreLib::showCliassificationImageLayer2017() {
	cliassificationImage2017 = map->getImageLayerByName("2017classificationImage");
	cliassificationImage2017->setVisible(true);
}
void osgCoreLib::hideCliassificationImageLayer2017() {
	cliassificationImage2017 = map->getImageLayerByName("2017classificationImage");
	cliassificationImage2017->setVisible(false);
}

void osgCoreLib::showTransferImage() {
	transferImage = map->getImageLayerByName("transferImage");
	transferImage->setVisible(true);
}
void osgCoreLib::hideTransferImage() {
	transferImage = map->getImageLayerByName("transferImage");
	transferImage->setVisible(false);
}

void osgCoreLib::showXinJiangImage() {
	xinJiangImage = map->getImageLayerByName("xinjiangImage");
	xinJiangImage->setVisible(true);
}
void osgCoreLib::hideXinJiangImage() {
	xinJiangImage = map->getImageLayerByName("xinjiangImage");
	xinJiangImage->setVisible(false);
}

void osgCoreLib::showPollutionImage() {
	pollutionImage = map->getImageLayerByName("pollution");
	pollutionImage->setVisible(true);
}
void osgCoreLib::hidePollutionImage() {
	pollutionImage = map->getImageLayerByName("pollution");
	pollutionImage->setVisible(false);
}

void osgCoreLib::showSpectrumImage2018() {
	spectrumImage2018 = map->getImageLayerByName("2018spectrumImage");
	spectrumImage2018->setVisible(true);
}

void osgCoreLib::hideSpectrumImage2018() {
	spectrumImage2018 = map->getImageLayerByName("2018spectrumImage");
	spectrumImage2018->setVisible(false);
}

void osgCoreLib::showSpectrumImage2019() {
	spectrumImage2019 = map->getImageLayerByName("2019spectrumImage");
	spectrumImage2019->setVisible(true);
}
void osgCoreLib::hideSpectrumImage2019() {
	spectrumImage2019 = map->getImageLayerByName("2019spectrumImage");
	spectrumImage2019->setVisible(false);
}

void osgCoreLib::showSpectrumClassificationImage2018() {
	spectrumClassificationImage2018 = map->getImageLayerByName("2018spectrumClassificationImage");
	spectrumClassificationImage2018->setVisible(true);
}
void osgCoreLib::hideSpectrumClassificationImage2018() {
	spectrumClassificationImage2018 = map->getImageLayerByName("2018spectrumClassificationImage");
	spectrumClassificationImage2018->setVisible(false);
}

void osgCoreLib::showSpectrumClassificationImage2019() {
	spectrumClassificationImage2019 = map->getImageLayerByName("2019spectrumClassificationImage");
	spectrumClassificationImage2019->setVisible(true);
}
void osgCoreLib::hideSpectrumClassificationImage2019() {
	spectrumClassificationImage2019 = map->getImageLayerByName("2019spectrumClassificationImage");
	spectrumClassificationImage2019->setVisible(false);
}

void osgCoreLib::showSpectrumTransferImage() {
	spectrumTransferImage = map->getImageLayerByName("2018To2019spectrumTransferImage");
	spectrumTransferImage->setVisible(true);
}
void osgCoreLib::hideSpectrumTransferImage() {
	spectrumTransferImage = map->getImageLayerByName("2018To2019spectrumTransferImage");
	spectrumTransferImage->setVisible(false);
}

void osgCoreLib::showSlopeImage() {
	SlopeImage = map->getImageLayerByName("slopeImage");
	SlopeImage->setVisible(true);
}

void osgCoreLib::hideSlopeImage() {
	SlopeImage = map->getImageLayerByName("slopeImage");
	SlopeImage->setVisible(false);
}

void osgCoreLib::showAspectImage() {
	AspectImage = map->getImageLayerByName("aspectImage");
	AspectImage->setVisible(true);
}

void osgCoreLib::hideAspectImage() {
	AspectImage = map->getImageLayerByName("aspectImage");
	AspectImage->setVisible(false);
}


void osgCoreLib::addTerrain()
{
	std::fstream fin("./Module/landmark/position.txt", std::ios::in);

	for (int index = 0; index<18; index++)
	{
		//��ȡ���ơ����ȡ�γ��
		string name;
		double lat, lon;
		fin >> name >> lon >> lat;
		osg::ref_ptr<osg::Node> terrain;
		osg::ref_ptr<osg::MatrixTransform> mtTerrainSelf; //mtFlySelf
		osg::ref_ptr<osg::MatrixTransform> mtTerrain; //mtfly
		terrain = osgDB::readNodeFile("./Module/landmark/yellowqipao.3DS");//, a);
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());


		osg::Matrixd mtTemp;
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);

		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	

		terrain->setName(name);
		
		mtTerrainSelf = new osg::MatrixTransform;
		mtTerrainSelf->setMatrix(osg::Matrixd::scale(0.06, 0.06, 0.06));
		mtTerrainSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		//mtTerrainSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		mtTerrainSelf->addChild(terrain);

		mtTerrain = new osg::MatrixTransform;
		mtTerrain->addChild(mtTerrainSelf);
		mRoot->addChild(mtTerrain);

		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), out_haml + 3, mtTemp);
		mtTerrain->setMatrix(mtTemp);
	}
	fin.close();
}

std::wstring osgCoreLib::String2WString(const std::string& s)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[]wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;
}

void osgCoreLib::addPositionName()
{

	//��������
	osgEarth::Style style;
	osgEarth::Symbology::TextSymbol * textStyle = style.getOrCreateSymbol<osgEarth::Symbology::TextSymbol>();
	//������ɫ
	textStyle->fill()->color() = osg::Vec4f(1.0, 1.0, 1.0, 1.0);
	//���ñ߿�
	textStyle->halo()->color() = osg::Vec4f(0.0, 0.0, 1.0, 1.0);
	textStyle->font() = "simkai.ttf";
	textStyle->size() = 13.0;
	textStyle->encoding() = osgEarth::Symbology::TextSymbol::ENCODING_UTF8;
	
	//��ȡ�ļ�
	//std::fstream fin("./place/place.txt", std::ios::in);, ,
	string name[] = { "ϴ����", "ϴ����", "������", "����", "������", "С��ϣ��","ָ�Ӽ���������" };//, "��ϣ���"};
	double lon[] = { 81.617947, 81.623095, 81.623418, 81.622755, 81.614893, 81.622220 ,81.634278 };//, 81.629543 };
	double lat[] = { 44.237668, 44.245067 , 44.227526 , 44.230978 , 44.239895 , 44.225495, 44.236071 };//, 44.239629 };
	for (int i = 0; i < 7; i ++)
	{
		//��ӵ���
		const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
		std::string _strWideName;
		unicodeToUTF8(String2WString(name[i]), _strWideName);
		//test
		//MessageBox(NULL, "Hi", _strWideName.c_str(), MB_OK);
		osgEarth::Annotation::PlaceNode *pn = new osgEarth::Annotation::PlaceNode(mapNode, osgEarth::GeoPoint(geoSRS, lon[i], lat[i]), NULL, _strWideName, style);
		//pn->setScale(osg::Vec3(1, 1, 1));
		earthLabel->addChild(pn);
	}
	
}

/*
void osgCoreLib::addPersonPoint() {
	double lon[] = { 81.622013 , 81.622851 , 81.624221 , 81.625002 , 81.624431, 81.623420 };
	double lat[] = { 44.233347, 44.231234 ,44.231367 ,44.232738 ,44.235879, 44.227528 };
	string name[] = { "point1", "point2", "point3", "point4", "point5", "point6"};
	for (int i = 0; i < 6; i++) {
		osg::ref_ptr<osg::Node> point; //flyAirport
		osg::ref_ptr<osg::MatrixTransform> mtPointSelf; //mtFlySelf
		osg::ref_ptr<osg::MatrixTransform> mtPoint; //mtfly

		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());


		osg::Matrixd mtTemp;
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon[i], lat[i], 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);

		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		point = osgDB::readNodeFile("./Module/landmark/blueqipao.3DS");//, a);

		//point = new osg::Node;
		
		point->setName(name[i]);

		mtPointSelf = new osg::MatrixTransform;
		mtPointSelf->setMatrix(osg::Matrixd::scale(0.06, 0.06, 0.06));
		mtPointSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		//mtPointSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		mtPointSelf->addChild(point);

		mtPoint = new osg::MatrixTransform;
		mtPoint->addChild(mtPointSelf);
		mRoot->addChild(mtPoint);

		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat[i]), osg::DegreesToRadians(lon[i]), out_haml + 3, mtTemp);
		mtPoint->setMatrix(mtTemp);
	}
}
*/

void osgCoreLib::addPersonPoint() {
	double lon[] = { 81.622013 , 81.622851 , 81.624221 , 81.625002 , 81.624431, 81.623420 };
	double lat[] = { 44.233347, 44.231234 ,44.231367 ,44.232738 ,44.235879, 44.227528 };
	string name[] = { "point1", "point2", "point3", "point4", "point5", "point6" };
	
	
	for (int i = 0; i < 6; i++) {
		osg::ref_ptr<osg::Node> point;
		osg::ref_ptr<osg::MatrixTransform> mtPointSelf; //mtFlySelf
		osg::ref_ptr<osg::MatrixTransform> mtPoint; //mtfly

		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());


		osg::Matrixd mtTemp;
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon[i], lat[i], 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);

		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		
		point = osgDB::readNodeFile("./Module/landmark/blueqipao.3DS");//, a);
		point->setName(name[i]);

		mtPointSelf = new osg::MatrixTransform;
		mtPointSelf->setMatrix(osg::Matrixd::scale(0.06, 0.06, 0.06));
		mtPointSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		//mtPointSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		mtPointSelf->addChild(point);

		mtPoint = new osg::MatrixTransform;
		mtPoint->addChild(mtPointSelf);
		mRoot->addChild(mtPoint);

		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat[i]), osg::DegreesToRadians(lon[i]), out_haml + 3, mtTemp);
		mtPoint->setMatrix(mtTemp);
	}
}


void osgCoreLib::showClassLabel()
{
	//��ʾ����
	const char *srcImageName = ".\\tif\\ͼ��.png";
	cv::Mat img = cv::imread(srcImageName);

	cv::namedWindow("ͼ��", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL������ʾ�û����Ըı䴰�ڴ�С
	cv::resizeWindow("ͼ��", img.cols, img.rows);
	cv::imshow("ͼ��", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//��Ӵ�����
void osgCoreLib::addSensor() 
{
	{
		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		sensor = osgDB::readNodeFile("./Module/sensor/13492_Antenna_V1_L3.obj", a);
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());


		osg::Matrixd mtTemp;
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.624057, 44.227523, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);

		sensor->setName("dam");

		mtSensorSelf = new osg::MatrixTransform;
		mtSensorSelf->setMatrix(osg::Matrixd::scale(0.8, 0.8, 0.8) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 1.0f, 0.0f, 0.0f));
		mtSensorSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		mtSensorSelf->addChild(sensor);

		mtSensor = new osg::MatrixTransform;
		mtSensor->addChild(mtSensorSelf);
		mRoot->addChild(mtSensor);

		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.227523), osg::DegreesToRadians(81.624057), out_haml + 1, mtTemp);
		mtSensor->setMatrix(mtTemp);
	}
	std::fstream fin("./Module/sensor/position.txt", std::ios::in);
	
	for (int index = 0; index<4; index++)
	{
		//��ȡ���ơ����ȡ�γ��
		string name;
		double lat, lon;
		fin >> name >> lon >> lat;
		osg::ref_ptr<osg::Node> terrain;
		osg::ref_ptr<osg::MatrixTransform> mtTerrainSelf; //mtFlySelf
		osg::ref_ptr<osg::MatrixTransform> mtTerrain; //mtfly
		osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
		terrain = osgDB::readNodeFile("./Module/sensor/13492_Antenna_V1_L3.obj", a);
		csn = new osg::CoordinateSystemNode;
		csn->setEllipsoidModel(new osg::EllipsoidModel());


		osg::Matrixd mtTemp;
		double out_haml = 0.0;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);

		terrain->setName(name);

		mtTerrainSelf = new osg::MatrixTransform;
		mtTerrainSelf->setMatrix(osg::Matrixd::scale(0.8, 0.8, 0.8) * osg::Matrixd::rotate(osg::inDegrees(-90.f), 1.0f, 0.0f, 0.0f));
		mtTerrainSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		//mtTerrainSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		mtTerrainSelf->addChild(terrain);

		mtTerrain = new osg::MatrixTransform;
		mtTerrain->addChild(mtTerrainSelf);
		mRoot->addChild(mtTerrain);

		csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), out_haml + 1, mtTemp);
		mtTerrain->setMatrix(mtTemp);
	}
	fin.close();
}

//��Ӵ���������
void  osgCoreLib::addSensorNetwork()
{
	{
		const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
		// ��ʼ����ͼ����
		osgEarth::Symbology::Style m_lineLakeStyle;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->color() = osgEarth::Symbology::Color::Red;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->width() = 2.0;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->tessellation() = 20.0;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
			->verticalOffset() = 0.1;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->stipple() = 255;
		osgEarth::Features::Feature* m_pLakeFeature;
		std::vector<osg::Vec3> m_vecLakePoint;
		m_pLakeFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			geoSRS, m_lineLakeStyle);
		m_pStippleFeatureNode = new osgEarth::Annotation::FeatureNode(
			mapNode, m_pLakeFeature);

		double out_haml = 0.0;
		//std::fstream fin("./Module/sensor/position.txt", std::ios::in);

		double lat, lon;

		lat = 44.227523;
		lon = 81.624970;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.227523;
		lon = 81.624057;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.227102;
		lon = 81.624364;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.227523;
		lon = 81.624057;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.226859;
		lon = 81.623650;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.227523;
		lon = 81.624057;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		lat = 44.226452;
		lon = 81.622972;
		query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), lon, lat, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			out_haml, query_resolution, &out_resolution);
		//�洢��ǰ��
		m_vecLakePoint.push_back(osg::Vec3(lon, lat, out_haml + 5));

		mRoot->addChild(m_pStippleFeatureNode);
		m_pLakeFeature->getGeometry()->clear();
		m_pStippleFeatureNode->setStyle(m_lineLakeStyle);
		for (int i = 0; i < m_vecLakePoint.size(); ++i)
		{
			m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
		}
		m_pStippleFeatureNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
		m_pStippleFeatureNode->init();
	}
	{
		//��ʼ����ͼ����
		const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
		//��ȡcar�ڵ����ڵ���������// ��ʼ����ͼ����
		osgEarth::Symbology::Style m_lineLakeStyle;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->color() = osgEarth::Symbology::Color::Blue;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->width() = 4.0;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->tessellation() = 20.0;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
			->verticalOffset() = 0.1;
		m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
			->stroke()->stipple() = 255;
		{
			osgEarth::Features::Feature* m_pLakeFeature;
			std::vector<osg::Vec3> m_vecLakePoint;
			m_pLakeFeature = new osgEarth::Features::Feature(
				new osgEarth::Annotation::LineString,
				geoSRS, m_lineLakeStyle);
			m_pStippleFeatureNode2 = new osgEarth::Annotation::FeatureNode(
				mapNode, m_pLakeFeature);
			osg::Vec3 center = car->getBound().center() * car->getWorldMatrices()[0];
			double lon, lat, height;
			//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
			csn->getEllipsoidModel()->convertXYZToLatLongHeight(center.x(), center.y(), center.z(), lat, lon, height);
			//�洢��ǰ��
			m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon), osg::RadiansToDegrees(lat), height));

			//��ȡplane�ڵ����ڵ���������
			osg::Vec3 center1 = sensor->getBound().center() * sensor->getWorldMatrices()[0];
			double lon1, lat1, height1;
			//����������XYZת���ɾ��ȡ�γ�ȡ��߶���Ϣ
			csn->getEllipsoidModel()->convertXYZToLatLongHeight(center1.x(), center1.y(), center1.z(), lat1, lon1, height1);
			//�洢��ǰ��
			m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon1), osg::RadiansToDegrees(lat1), height1));

			//�����Ҫ���ӵĵ�ľ�γ�Ⱥ͸߶�
			m_pLakeFeature->getGeometry()->clear();
			m_pStippleFeatureNode2->setStyle(m_lineLakeStyle);
			for (int i = 0; i < m_vecLakePoint.size(); ++i)
			{
				m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
			}

			m_pStippleFeatureNode2->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
			m_pStippleFeatureNode2->init();
			m_pStippleFeatureNode2->addUpdateCallback(new UpdateLink(sensor, car));
			mRoot->addChild(m_pStippleFeatureNode2);
		}
	}
}


void osgCoreLib::hideSensorNetwork()
{
	mRoot->removeChild(m_pStippleFeatureNode);
	mRoot->removeChild(m_pStippleFeatureNode2);
}


//���Ӧ��ָ������
void osgCoreLib::addCommandCenter()
{
	csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());

	mtCommandCenter = new osg::MatrixTransform;
	mRoot->addChild(mtCommandCenter);

	osg::Matrixd mtTemp;
	double out_haml = 0.0;
	query->getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), 81.634278, 44.236071, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
		out_haml, query_resolution, &out_resolution);
	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.236071), osg::DegreesToRadians(81.634278), out_haml + 1, mtTemp);
	mtCommandCenter->setMatrix(mtTemp);

	//osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
	commandCenter = osgDB::readNodeFile("./Module/command_center/Glass House.3DS");//, a);
	mtCommandCenterSelf = new osg::MatrixTransform;
	mtCommandCenterSelf->setMatrix(osg::Matrixd::scale(0.3, 0.3, 0.3)
		/** osg::Matrixd::rotate(osg::inDegrees(55.0f), 0.0f, 0.0f, 1.0f)
		* osg::Matrixd::rotate(osg::inDegrees(90.f), 0.0f, 1.0f, 0.0f)
		* osg::Matrixd::rotate(osg::inDegrees(10.f), 1.0f, 0.0f, 0.0f)*/
	);

	commandCenter->setName("Command Center");
	mtCommandCenterSelf->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	mtCommandCenterSelf->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	mtCommandCenterSelf->addChild(commandCenter);


	mtCenter = new osg::MatrixTransform;
	mtCenter->addChild(mtCommandCenterSelf);
	mRoot->addChild(mtCenter);

	csn->getEllipsoidModel()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(44.236071), osg::DegreesToRadians(81.634278), out_haml + 1, mtTemp);
	mtCenter->setMatrix(mtTemp);

}