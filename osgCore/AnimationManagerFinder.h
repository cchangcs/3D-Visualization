#pragma once

/*

¶¯»­²¥·Å

*/
#include <osg\NodeVisitor>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/AnimationManagerBase>
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
