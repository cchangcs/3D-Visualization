#pragma once
#include <osg\NodeCallback>
#include <osg\Node>
#include <osg\NodeVisitor>
#include <osgEarthAnnotation\FeatureNode>
#include <osgEarthAnnotation/FeatureEditing>
#include <vector>
class UpdateFlood :public osg::NodeCallback
{

public:
	float mSteps;
	std::vector<osg::Vec3> m_vecPoint;
public:
	UpdateFlood() :mSteps(0.001)
	{
	}

	void setVecPoints(std::vector<osg::Vec3> vecPoint) {
		m_vecPoint = vecPoint;
	}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_pLakeNode =
			dynamic_cast<osgEarth::Annotation::FeatureNode*>(node);

		if (m_pLakeNode.get()) {
			osgEarth::Features::Feature* pFeature = m_pLakeNode->getFeature();//删除所有的geomertry对象
			mSteps += 1e-5;

			osgEarth::Symbology::Style m_lakeStyle;
			m_lakeStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
				->fill()->color() = osgEarth::Symbology::Color::Color(0.0, 0.27, 0.42, 1.0);
			m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
				->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
			m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
				->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
			m_lakeStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
				->verticalOffset() = 0.1;

			//添加所要连接的点的经纬度和高度
			m_vecPoint.push_back(osg::Vec3(112.885, 21.9483, 130));
			m_vecPoint.push_back(osg::Vec3(112.840, 21.905, 200));
			m_vecPoint.push_back(osg::Vec3(112.820, 21.930, 200));
			m_vecPoint.push_back(osg::Vec3(112.820 + mSteps, 21.940 + mSteps, 200));
			m_vecPoint.push_back(osg::Vec3(112.885 + mSteps, 21.9483 + mSteps, 200));
			pFeature->getGeometry()->clear();
			m_pLakeNode->setStyle(m_lakeStyle);
			for (int i = 0; i < m_vecPoint.size(); ++i)
			{
				pFeature->getGeometry()->push_back(m_vecPoint[i]);
			}
			m_pLakeNode->init();
		}
		traverse(node, nv);
	}
};