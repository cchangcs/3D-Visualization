#include "StdAfx.h"
#include "AnimationEventHandle.h"


AnimationEventHandle::AnimationEventHandle(osgViewer::Viewer* vr)
{
	 viewer=vr;
}
AnimationEventHandle::AnimationEventHandle(void)
{
}

AnimationEventHandle::~AnimationEventHandle(void)
{
}
bool AnimationEventHandle::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
 {
  //�����������»ص�����
  osg::ref_ptr<osg::AnimationPathCallback> animationPathCallback=new osg::AnimationPathCallback();
  osg::ref_ptr<osg::Group> group=dynamic_cast<osg::Group*>(viewer->getSceneData());

  //ȡ�ýڵ�Ķ�������
  animationPathCallback=dynamic_cast<osg::AnimationPathCallback*>(group->getChild(2)->getUpdateCallback());

  switch (ea.getEventType())
  {
  case osgGA::GUIEventAdapter::KEYDOWN:
   {
    //��ͣ
    if (ea.getKey()=='p')
    {
     animationPathCallback->setPause(true);
     return true;
    }
    //��ʼ
    if (ea.getKey()=='s')
    {
     animationPathCallback->setPause(false);
     return true;
    }
    //���¿�ʼ
    if (ea.getKey()=='r')
    {
     animationPathCallback->reset();
     return true;
    }
       break;
   }
  case osgGA::GUIEventAdapter::DOUBLECLICK:
  {
		  // do we need to do something special here to handle double click???  Will just assume button down for now.
 

	if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
	{
		if(animationPathCallback->getPause()==true)
		{
			animationPathCallback->setPause(false);
		}
		else
		{
			animationPathCallback->setPause(true);
		}
		}          
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
		{
			animationPathCallback->reset();
		}

		return true;
	}
  default:
   break;
  }
  return false;
 }