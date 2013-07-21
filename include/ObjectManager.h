#pragma once
#ifndef _CObjectManager_h_
#define _CObjectManager_h_
#include "Ogre.h"
#include "CPlayer.h"
namespace FightClub
{
class CObjectManager
{
public:
	CObjectManager(void);
	~CObjectManager(void);
	
	void AddAnimationTime(const Ogre::FrameEvent& evt,CPlayer* mObject); //为动画添加时间
	/*
	@sceneMgr 创建此对象的场景管理器
	@name     此对象的自定义的命名
	@meshName 此对象所用的模型名 
	*/
	CObject* CreateObject(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	void DestroyObject(Ogre::SceneManager* sceneMgr);
	void InjectKeyDown(const OIS::KeyEvent& arg,CPlayer* mObject);              //按键按下(触发式)
	void InjectKeyUp(const OIS::KeyEvent& arg,CPlayer* mObject);                //按键弹起
	void UpdateAction(CPlayer* mObject);
};
}
#endif  //_CObjectManager_h_