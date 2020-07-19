#pragma once
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/AnimationPath>
class AnimationEventHandle:public osgGA::GUIEventHandler
{
public:
	~AnimationEventHandle(void);
	AnimationEventHandle(void);
	AnimationEventHandle(osgViewer::Viewer* vr);
 osgViewer::Viewer* viewer;
 bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};

