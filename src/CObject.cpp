#include"CObject.h"

namespace FightClub
{
CObject::CObject():mSceneManager(0),mBodyEntity(0),mBodyNode(0),mCollision(true){}

CObject::CObject(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName):
mSceneManager(sceneMgr),mName(name),mMeshName(meshName)
{
	mBodyEntity=mSceneManager->createEntity(mName,mMeshName);
	mBodyNode=mSceneManager->getRootSceneNode()->createChildSceneNode();
	mBodyNode->attachObject(mBodyEntity);
}

CObject::~CObject()
{
	if(mSceneManager)
	{
		mSceneManager->destroySceneNode(mBodyNode);
		mSceneManager->destroyEntity(mBodyEntity);
	}
}
}