#pragma once
#ifndef _CPlayerMySelf_h_
#define _CPlayerMySelf_h_
#include"CPlayer.h"
namespace FightClub
{
class CPlayerMySelf:public CPlayer
{
public:
	CPlayerMySelf(const std::string& PlayerName,Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	~CPlayerMySelf();
	void Walk(Ogre::Vector3 mGoalTowards);  
	void Die(const Ogre::FrameEvent& evt){}
	void Attack(void);
	void SpinAttack(void);
	void Jump(void);
	void upadate(unsigned long timeSiceLastFrame);
	void InjectKeyDown(const OIS::KeyEvent& arg);
	void InjectKeyUp(const OIS::KeyEvent& arg);
	bool processUnbufferInput(OIS::Keyboard* mKeyboard,float timeSinceLastFrame);
	Ogre::Vector3 getInitSightPos(){return mInitSightNodePos;}
	Ogre::Vector3 getInitCameraPos(){return mInitCameraNodePos;}
protected:
	Ogre::Timer *mTimer;
	CAction* mActionSpinAttack;
	CAction* mActionJump;
	Ogre::Vector3 mInitSightNodePos;
	Ogre::Vector3 mInitCameraNodePos;
};
}
#endif //_CPlayerMySelf_h_