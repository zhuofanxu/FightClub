#include "ObjectManager.h"
#include<iostream>
namespace FightClub
{
using namespace std;
CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
}

CObject* CObjectManager::CreateObject(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName)
{
	return new CObject(sceneMgr,name,meshName);
}

void CObjectManager::DestroyObject(Ogre::SceneManager* sceneMgr)
{
	sceneMgr->destroyAllEntities();
}

void CObjectManager::InjectKeyDown(const OIS::KeyEvent& arg,CPlayer* mObject)
{
	if(mObject->mPlayerAction[ATTACK]&&!mObject->mPlayerAction[ATTACK]->getisEnabled())
	{
	    if(arg.key==OIS::KC_J)
		     mObject->mPlayerAction[ATTACK]->setEnabled(true);
	}
}

void CObjectManager::InjectKeyUp(const OIS::KeyEvent& arg,CPlayer* mObject)
{
	bool mDebugWalkEnable=true;                                     //用于调试的局部变量
	bool mDebugAttackEnable=true;                                   //用于调试的局部变量
	if(mObject->mPlayerAction[ATTACK]&&mObject->mPlayerAction[ATTACK]->getisEnabled())
	{
	   if(arg.key==OIS::KC_J)
	   {
		    mObject->mPlayerAction[ATTACK]->setEnabled(false);
			mDebugAttackEnable=false;
	   }
	}
}

void CObjectManager::AddAnimationTime(const Ogre::FrameEvent& evt,CPlayer* mObject)
{
	if(mObject->mPlayerAction[WALK])
	    mObject->mPlayerAction[WALK]->addTime(evt);
	if(mObject->mPlayerAction[DIE])
	    mObject->mPlayerAction[DIE]->addTime(evt);
	if(mObject->mPlayerAction[ATTACK])
	    mObject->mPlayerAction[ATTACK]->addTime(evt);
	if(mObject->mPlayerAction[READY])
		mObject->mPlayerAction[READY]->addTime(evt);

}

void CObjectManager::UpdateAction(CPlayer* mObject)
{
	
	

}

}