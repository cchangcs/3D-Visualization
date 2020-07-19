#include "stdafx.h"
#include "LabelControlEventHandler.h"

CLabelControlEventHandler::CLabelControlEventHandler(osgEarth::Util::Controls::LabelControl* viewLabel,
	osgEarth::Util::Controls::LabelControl* mouseLabel, osgEarth::MapNode* mn) {
	viewCoords = viewLabel;
	mouseCoords = mouseLabel;
	mapNode = mn;
	// 相较原项目文件做了修改
	/*
	nodePath.push_back(mapNode->getTerrainEngine());

	nodePath.push_back(mapNode);
	*/
	nodePath.push_back(mapNode);
}

CLabelControlEventHandler::~CLabelControlEventHandler(void) {}

bool CLabelControlEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
	osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (viewer)
	{
		if (ea.getEventType() == ea.FRAME)
		{
			osgUtil::LineSegmentIntersector::Intersections results;
			if (viewer->computeIntersections(ea.getX(), ea.getY(), nodePath, results)) {
				osgUtil::LineSegmentIntersector::Intersection first = *(results.begin());
				/*
				//将经纬度转换为全球坐标点
				osg::Vec3d center;
				osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
				emodel->convertLatLongHeightToXYZ(osg::DegreesToRadians(lon), osg::DegreesToRadians(lat), 0, center.x(), center.y(), center.z());

				*/
				//取出交点坐标
				osg::Vec3d point = first.getWorldIntersectPoint();
				osg::Vec3d lla;
				osg::EllipsoidModel* emodel = new osg::EllipsoidModel();
				emodel->convertLatLongHeightToXYZ(point.x(), point.y(), point.z(), lla.x(), lla.y(), lla.z());

				char wsrc[512];
				sprintf(wsrc, "经度:%.2f 纬度:%.2f 海拔:%.2f", lla.x(), lla.y(), lla.z());
				/*
				wchar_t wcontent[512];
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, wsrc, 512, wcontent, 512);
				*/
				mouseCoords->setText(wsrc);
			}

			osgEarth::Util::EarthManipulator* em = dynamic_cast<osgEarth::Util::EarthManipulator*>(viewer->getCameraManipulator());
			if (em)
			{
				osgEarth::Viewpoint vp = em->getViewpoint();
				char wsrc[512];
				sprintf(wsrc, "视点经度:%.2f 纬度:%.2f 高度:%.2f", vp.getHeading(), vp.getPitch(), vp.getRange());
				//sprintf(wsrc, "(%.2f, %.2f, %.2f), %.2f, %.2f, %.2f", vp.x(), vp.y(), vp.z(), vp.getHeading(), vp.getPitch(), vp.getRange());
				/*wchar_t wcontent[512];
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, wsrc, 512, wcontent, 512);*/
				viewCoords->setText(wsrc);
			}

		}
		if (ea.getEventType() == ea.KEYDOWN)
		{
			//osgEarth::Util::EarthManipulator * em = dynamic_cast<osgEarth::Util::EarthManipulator*>(viewer->getCameraManipulator());
			//osgEarth::Viewpoint vm = em ->getViewpoint();
			//double fx = vm.getFocalPoint().x();
			//double fy = vm.getFocalPoint().y();
			//double fz = vm.getFocalPoint().z();
			//double heading_deg = vm.getHeading();
			//double pitch_deg = vm.getPitch();
			//double range = vm.getRange();


			//if(ea.getKey() == 'P')
			//{
			//    fx ++;
			//}
			//else if(ea.getKey() == 'p')
			//{
			//    fx --;
			//}
			//else if(ea.getKey() == 'O')
			//{
			//    fy ++;
			//}
			//else if(ea.getKey() == 'o')
			//{
			//    fy ++;
			//}
			//else if(ea.getKey() == 'I')
			//{
			//    fz ++;
			//}
			//else if(ea.getKey() == 'i')
			//{
			//    fz --;
			//}
			//else if(ea.getKey() == 'U')
			//{
			//    heading_deg ++;
			//}
			//else if(ea.getKey() == 'u')
			//{
			//    heading_deg --;
			//}
			//else if(ea.getKey() == 'Y')
			//{
			//    pitch_deg ++;
			//}
			//else if(ea.getKey() == 'y')
			//{
			//    pitch_deg --;
			//}
			//else if(ea.getKey() == 'T')
			//{
			//    range += 1000;
			//}
			//else if(ea.getKey() == 't')
			//{
			//    range -= 1000;
			//}

			//em->setViewpoint(osgEarth::Viewpoint(fx, fy, fz, heading_deg, pitch_deg, range));
		}
	}
	return false;
}

