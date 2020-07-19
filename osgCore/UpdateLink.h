#pragma once
class UpdateLink :public osg::NodeCallback
{
public:
	osg::Node *plane;
	osg::Node *car;
public:
	UpdateLink(osg::Node *p, osg::Node *c)
	{
		plane = p;
		car = c;
	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_pLakeFeatureNode =
			dynamic_cast<osgEarth::Annotation::FeatureNode*>(node);
		
		if (m_pLakeFeatureNode.get()) {
			std::vector<osg::Vec3> m_vecLakePoint;
			//获取car节点所在的世界坐标
			osgEarth::Features::Feature* m_pLakeFeature = m_pLakeFeatureNode->getFeature();//删除所有的geomertry对象

			osgEarth::Symbology::Style m_lineLakeStyle;
			osg::Vec3 center = car->getBound().center() * car->getWorldMatrices()[0];
			double lon, lat, height;
			//将世界坐标XYZ转换成经度、纬度、高度信息
			osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
			emodel->convertXYZToLatLongHeight(center.x(), center.y(), center.z(), lat, lon, height);
			//存储当前点
			m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon), osg::RadiansToDegrees(lat), height));

			//获取plane节点所在的世界坐标
			osg::Vec3 center1 = plane->getBound().center() * plane->getWorldMatrices()[0];
			double lon1, lat1, height1;
			//将世界坐标XYZ转换成经度、纬度、高度信息
			emodel->convertXYZToLatLongHeight(center1.x(), center1.y(), center1.z(), lat1, lon1, height1);
			//存储当前点
			m_vecLakePoint.push_back(osg::Vec3(osg::RadiansToDegrees(lon1), osg::RadiansToDegrees(lat1), height1));
			// 初始化绘图参数
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
			//添加所要连接的点的经纬度和高度
			m_pLakeFeature->getGeometry()->clear();
			m_pLakeFeatureNode->setStyle(m_lineLakeStyle);
			for (int i = 0; i < m_vecLakePoint.size(); ++i)
			{

				m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
			}
			m_pLakeFeatureNode->init();

		}
		traverse(node, nv);
	}
};


//线闪烁效果
/*
class UpdateLink :public osg::NodeCallback
{
public:
	std::vector<osg::Vec3> m_vecLakePoint;
	UpdateLink(double out) :entry(0)
	{
		////===========================测试获取坐标===========================
		//osg::Vec3 center = flyAirport->getBound().center() * flyAirport->getWorldMatrices()[0];

		//double lon, lat, height;
		//csn->getEllipsoidModel()->convertXYZToLatLongHeight(center.x(), center.y(), center.z(), lat, lon, height);
		//std::string output = DoubleToStringByStringStream(osg::RadiansToDegrees(lat)) + "  " + DoubleToStringByStringStream(osg::RadiansToDegrees(lon));
		//MessageBox(NULL, "Hi", output.c_str(), MB_OK);
		//===========================测试获取坐标===========================

		m_vecLakePoint.push_back(osg::Vec3(81.619747, 44.238428, out_haml + 5));
		m_vecLakePoint.push_back(osg::Vec3(81.619747, 44.238428, out_haml + 120));
		out_haml = out;
	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_pLakeFeatureNode =
			dynamic_cast<osgEarth::Annotation::FeatureNode*>(node);

		if (m_pLakeFeatureNode.get()) {
			entry += 1;
			if (entry == 10) {
				//MessageBox(NULL, "Hi", "111", MB_OK);

				osgEarth::Features::Feature* m_pLakeFeature = m_pLakeFeatureNode->getFeature();//删除所有的geomertry对象
				osgEarth::Symbology::Style m_lineLakeStyle;
				// 初始化绘图参数
				m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					->stroke()->color() = osgEarth::Symbology::Color::Green;
				m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					->stroke()->width() = 4.0;
				m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					->tessellation() = 20.0;
				m_lineLakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
					->verticalOffset() = 0.1;
				m_lineLakeStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					->stroke()->stipple() = 255;
				//添加所要连接的点的经纬度和高度
				m_pLakeFeature->getGeometry()->clear();
				m_pLakeFeatureNode->setStyle(m_lineLakeStyle);
				for (int i = 0; i < m_vecLakePoint.size(); ++i)
				{

					m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
				}
				m_pLakeFeatureNode->init();
			}
			else if (entry == 20) {
				entry = 0;
				//MessageBox(NULL, "Hi", "222", MB_OK);
				osgEarth::Features::Feature* m_pLakeFeature = m_pLakeFeatureNode->getFeature();//删除所有的geomertry对象
				std::vector<osg::Vec3> m_vecLakePoint;
				osgEarth::Symbology::Style m_lineLakeStyle;
				m_vecLakePoint.push_back(osg::Vec3(81.619747, 44.238428, out_haml + 5));
				m_vecLakePoint.push_back(osg::Vec3(81.619511, 44.237952, out_haml + 120));

				// 初始化绘图参数
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
				//添加所要连接的点的经纬度和高度
				m_pLakeFeature->getGeometry()->clear();
				m_pLakeFeatureNode->setStyle(m_lineLakeStyle);
				for (int i = 0; i < m_vecLakePoint.size(); ++i)
				{
					m_pLakeFeature->getGeometry()->push_back(m_vecLakePoint[i]);
				}
				m_pLakeFeatureNode->init();
			}

		}
		traverse(node, nv);
	}
public:
	double out_haml;
	int entry;
};
*/
