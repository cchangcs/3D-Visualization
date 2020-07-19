#include "stdafx.h"
#include "EventHandler.h"
#include <osg/LineWidth>
#include <osg/ShapeDrawable>

CEventHandler::CEventHandler(void) {
	mapNode = 0;
	computeIntersect = 0;
	geomLast = 0;
	isPickWorld = false;
	isTestJu = false;
	jieDuan = 0;
	vectex = new osg::Vec3Array;
	lineStrip = new osg::Geode;
	qiuqiu = new osg::Geode;
	flyLabel = 0;
	fmeNum = 0;
	_plate = 0;
	radar = 0;
	JQ = 0;
	ffLabel = 0;
}

CEventHandler::~CEventHandler(void) {

}

bool CEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (fmeNum < 10)
	{
		fmeNum++;
	}
	if (fmeNum >= 10)
	{
		if (stateSetMani)
		{
			if (stateSetMani->getLightingEnabled() == true)
			{
				stateSetMani->setLightingEnabled(false);
			}
		}
	}

	if (viewer&& _plate)
	{
		osgEarth::Util::EarthManipulator* em = dynamic_cast<osgEarth::Util::EarthManipulator*>(viewer->getCameraManipulator());
		if (em)
		{
			osgEarth::Viewpoint vm = em->getViewpoint();
			_plate->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(vm.getHeading()), osg::Vec3(0.0, 0.0, 1.0)));
		}
	}

	if (viewer&&radar)
	{
		osg::Vec3 eye, center, up;
		double lat, lon, hei;
		viewer->getCamera()->getViewMatrixAsLookAt(eye, center, up);
		mapNode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(eye.x(), eye.y(), eye.z(), lat, lon, hei);

		osg::Matrix mts;
		mapNode->getMap()->getProfile()->getSRS()->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(lat, lon, hei + 1500000, mts);
		osg::Matrix mts2;
		mts2 = osg::Matrixd::inverse(mts);
		radar->setViewMatrix(mts2);

		//列新飞机位置
		if (ffLabel&&JQ)
		{
			osg::Vec3d trans = JQ->getMatrix().getTrans();
			double llax, llay, llaz;
			mapNode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(trans.x(), trans.y(), trans.z(), llax, llay, llaz);
			const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
			ffLabel->setPosition(osgEarth::GeoPoint(geoSRS, osg::RadiansToDegrees(llay), osg::RadiansToDegrees(llax), 0));
		}
	}

	if (viewer && (ea.getEventType() == osgGA::GUIEventAdapter::MOVE) && mapNode && computeIntersect)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if (viewer->computeIntersections(ea.getX(), ea.getY(), intersections))
		{
			for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter = intersections.begin();
				hiter != intersections.end(); hiter++) {
				//取出结果集后，首先转换为经纬度
				osg::Vec3d point = hiter->getWorldIntersectPoint();
				osg::Vec3d lla;
				osg::Vec3d from;
				osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
				emodel->convertLatLongHeightToXYZ(point.x(), point.y(), point.z(), lla.x(), lla.y(), lla.z());
				emodel->convertXYZToLatLongHeight(lla.x(), lla.y(), lla.z() + 1000000, from.x(), from.y(), from.z());

				osg::Vec3d to = osg::Vec3(0, 0, 0);
				osg::Node* result = IntersectPoint(from, to, computeIntersect, "World");

				if (result)
				{
					osg::Geode* temp = dynamic_cast<osg::Geode*>(result);
					if (temp)
					{
						osg::Geometry* tempGeom = dynamic_cast<osg::Geometry*> (temp->getDrawable(0));
						if (tempGeom) {
							if (tempGeom == geomLast) {
								break;
							}

							if (geomLast) {
								RecoverGeom(geomLast, color);
							}

							geomLast = tempGeom;

							osg::Vec4Array* tempColorArray = dynamic_cast<osg::Vec4Array*>(tempGeom->getColorArray());
							if (tempColorArray)
							{
								osg::Vec4Array::iterator iter = tempColorArray->begin();
								for (iter; iter != tempColorArray->end(); iter++) {
									color = *iter;
									iter->set(1.0, 1.0, 1.0, 0.5);
								}
							}
						}
						tempGeom->dirtyDisplayList();
					}
				}
				break;
			}
		}
	}

	if (isTestJu&&viewer)
	{
		if (ea.getEventType() == osgGA::GUIEventAdapter::DOUBLECLICK)
		{
			osg::Vec3d point = osg::Vec3(0, 0, 0);
			osgUtil::LineSegmentIntersector::Intersections intersections;
			if (viewer->computeIntersections(ea.getX(), ea.getY(), intersections))
			{
				point = intersections.begin()->getWorldIntersectPoint();
				osg::Vec3d temp;
				osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
				emodel->convertXYZToLatLongHeight(point.x(), point.y(), point.z(), temp.x(), temp.y(), temp.z());
				emodel->convertLatLongHeightToXYZ(temp.x(), temp.y(), temp.z() + 100, point.x(), point.y(), point.z());

			}

			if (jieDuan == 0)
			{
				jieDuan = 1;
				vectex->push_back(point);
				startPoint = point;
				qiuqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(startPoint, 100.0)));
				if (viewer->getSceneData()->asGroup()->containsNode(qiuqiu) == false)
				{
					viewer->getSceneData()->asGroup()->addChild(qiuqiu);
				}
			}
			else if (jieDuan == 1)
			{
				endPoint = point;
				qiuqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(endPoint, 100.0)));
				qiuqiu->dirtyBound();


				jieDuan = 2;

				osg::Vec3d startlla;
				osg::Vec3d endlla;
				osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
				emodel->convertXYZToLatLongHeight(startPoint.x(), startPoint.y(), startPoint.z(), startlla.x(), startlla.y(), startlla.z());
				//emodel->convertLatLongHeightToXYZ(temp.x(), temp.y(), temp.z() + 100, point.x(), point.y(), point.z());
				emodel->convertXYZToLatLongHeight(endPoint.x(), endPoint.y(), endPoint.z(), endlla.x(), endlla.y(), endlla.z());

				int dis = GetDis(startPoint, endPoint);

				//先不考虑DIS是0的情况

				double deltaLat = (endlla.y() - startlla.y()) / (float)dis;
				double deltaLon = (endlla.x() - startlla.x()) / (float)dis;

				osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
				color->push_back(osg::Vec4(1.0, 1.0, 0.0, 1.0));

				for (int i = 1; i<dis; i++)
				{
					double tempLat = startlla.y() + i*deltaLat;
					double tempLon = startlla.x() + i*deltaLon;

					osg::Vec3d lowPoint, heightPoint;
					//emodel->convertXYZToLatLongHeight(startPoint.x(), startPoint.y(), startPoint.z(), startlla.x(), startlla.y(), startlla.z());
					emodel->convertLatLongHeightToXYZ(tempLon, tempLat, -1000, lowPoint.x(), lowPoint.y(), lowPoint.z());
					emodel->convertLatLongHeightToXYZ(tempLon, tempLat, 80000, heightPoint.x(), heightPoint.y(), heightPoint.z());
					//emodel->convertXYZToLatLongHeight(endPoint.x(), endPoint.y(), endPoint.z(), endlla.x(), endlla.y(), endlla.z());

					osg::Vec3d interSec = IntersectPoint(lowPoint, heightPoint, mapNode);
					if (interSec == osg::Vec3(0, 0, 0))
					{
						continue;
					}
					else
					{
						osg::Vec3d temp;
						osg::Vec3d lowPoint, heightPoint;
						emodel->convertXYZToLatLongHeight(interSec.x(), interSec.y(), interSec.z(), temp.x(), temp.y(), temp.z());
						emodel->convertLatLongHeightToXYZ(temp.x(), temp.y(), temp.z() + 100, interSec.x(), interSec.y(), interSec.z());
						vectex->push_back(interSec);
						color->push_back(osg::Vec4(1.0, 1.0, 0.0, 1.0));
					}
				}

				osg::ref_ptr<osg::Geometry> gemo = new osg::Geometry;
				lineStrip->addDrawable(gemo);

				gemo->setVertexArray(vectex);

				gemo->setColorArray(color);
				gemo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
				gemo->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vectex->size()));
				gemo->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::ON);
				gemo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

				viewer->getSceneData()->asGroup()->addChild(lineStrip);
				double dist = GetDis(vectex);

				if (flyLabel)
				{
					char wsrc[512];
					sprintf(wsrc, "测试的距离为：%.2f 米", dist);
					flyLabel->setText(wsrc);
				}

			}
			else if (jieDuan == 2)
			{
				jieDuan = 1;
				//清空之前的东东
				if (viewer->getSceneData()->asGroup()->containsNode(qiuqiu))
				{
					viewer->getSceneData()->asGroup()->removeChild(qiuqiu);
					qiuqiu = 0;
					qiuqiu = new osg::Geode;
				}

				if (viewer->getSceneData()->asGroup()->containsNode(lineStrip))
				{
					viewer->getSceneData()->asGroup()->removeChild(lineStrip);
					lineStrip = 0;
					lineStrip = new osg::Geode;
				}

				vectex->clear();

				vectex->push_back(point);
				startPoint = point;
				qiuqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(startPoint, 100.0)));

				if (viewer->getSceneData()->asGroup()->containsNode(qiuqiu) == false)
				{
					viewer->getSceneData()->asGroup()->addChild(qiuqiu);
				}
			}
		}
	}
	return false;
}

osg::Node* CEventHandler::IntersectPoint(osg::Vec3 XPosition, osg::Vec3 YPosition, osg::ref_ptr<osg::Node> Node, std::string name) {
	osgUtil::LineSegmentIntersector::Intersections intersections;
	osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(XPosition, YPosition);
	osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor(ls);

	if (Node) {
		Node->accept(*iv);
	}

	if (ls->containsIntersections())
	{
		intersections = ls->getIntersections();
		for (osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersections.begin();
			iter != intersections.end();iter++)
		{
			if (!iter->nodePath.empty())
			{
				osg::NodePath np = iter->nodePath;
				for (int i = np.size() - 1; i >= 0; --i)
				{
					if (np[i]->getName() == name)
					{
						return np[i];
					}
				}
			}
		}
	}
	return 0;
}

void CEventHandler::RecoverGeom(osg::Geometry* geom, osg::Vec4 color)
{
	if (geom)
	{
		osg::Vec4Array* tempColorArray = dynamic_cast<osg::Vec4Array*>(geom->getColorArray());

		if (tempColorArray)
		{
			osg::Vec4Array::iterator iter = tempColorArray->begin();
			for (iter; iter != tempColorArray->end(); iter++)
			{
				iter->set(color.x(), color.y(), color.z(), color.w());
			}
		}
	}
	geom->dirtyDisplayList();
}


void CEventHandler::isStartTest(bool isTest)
{
	isTestJu = isTest;
}

double CEventHandler::GetDis(osg::Vec3 from, osg::Vec3 to)
{
	return sqrt((to.x() - from.x())*(to.x() - from.x()) + (to.y() - from.y())*(to.y() - from.y()) + (to.z() - from.z())*(to.z() - from.z()));
}

osg::Vec3d CEventHandler::IntersectPoint(osg::Vec3 XPosition, osg::Vec3 YPosition, osg::ref_ptr<osg::Node> Node)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(XPosition, YPosition);
	osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor(ls);

	if (Node)
	{
		Node->accept(*iv);
	}

	if (ls->containsIntersections())
	{
		intersections = ls->getIntersections();
		return intersections.begin()->getWorldIntersectPoint();
	}
	return osg::Vec3(0, 0, 0);
}

double CEventHandler::GetDis(osg::Vec3Array * vec)
{
	double dis = 0;
	for (osg::Vec3Array::iterator iter = vec->begin(); iter != vec->end(); iter++)
	{
		osg::Vec3Array::iterator iter2 = iter;
		iter2++;
		if (iter2 == vec->end())
			break;
		else
		{
			dis = dis + GetDis(*iter, *iter2);
		}
	}

	return dis;
}