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
	
	void AddAnimationTime(const Ogre::FrameEvent& evt,CPlayer* mObject); //Ϊ�������ʱ��
	/*
	@sceneMgr �����˶���ĳ���������
	@name     �˶�����Զ��������
	@meshName �˶������õ�ģ���� 
	*/
	CObject* CreateObject(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	void DestroyObject(Ogre::SceneManager* sceneMgr);
	void InjectKeyDown(const OIS::KeyEvent& arg,CPlayer* mObject);              //��������(����ʽ)
	void InjectKeyUp(const OIS::KeyEvent& arg,CPlayer* mObject);                //��������
	void UpdateAction(CPlayer* mObject);
};
}
#endif  //_CObjectManager_h_