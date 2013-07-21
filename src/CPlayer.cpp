#include"CPlayer.h"

namespace FightClub
{
CPlayer::CPlayer(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName):CObject(sceneMgr,
	name,meshName)
{
	mLife=100;
    mActionWalk=0;
	mActionDie=0;
	mActionReady=0;
	mActionAttack=0;
	mBlender=0;
	mLifeBar=0;
	mInitPosition=Ogre::Vector3(100,0,0);
	mMove=true;
}

void CPlayer::InitTowards()
{
	mCurrentTowards=getOrientation()*(-Ogre::Vector3::UNIT_Z);  //四元数乘以标准朝向（单位向量）得到角色当前朝向(单位向量）
	if(1.0f+mCurrentTowards.dotProduct(-Ogre::Vector3::UNIT_Z)<0.0001f)
		mBodyNode->yaw(Ogre::Degree(180));
	else
		mQuat=mCurrentTowards.getRotationTo(-Ogre::Vector3::UNIT_Z);
	 
	mBodyNode->rotate(mQuat);
}
void CPlayer::Walk(Ogre::Vector3 mGoalTowards)
{
	if(!mActionWalk)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(WALK,mActionWalk));
	mPlayerAction[WALK]=new CAction(mBodyEntity,WALK);                           //动作实例化
	}
	mCurrentTowards=getOrientation()*(-Ogre::Vector3::UNIT_Z);  //四元数乘以标准朝向（单位向量）得到角色当前朝向(单位向量）
	if(1.0f+mCurrentTowards.dotProduct(mGoalTowards)<0.0001f)
		mBodyNode->yaw(Ogre::Degree(180));
	else
		mQuat=mCurrentTowards.getRotationTo(mGoalTowards);
	 
	mBodyNode->rotate(mQuat);
	
}
void CPlayer::Attack()
{
	if(!mActionAttack)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(ATTACK,mActionAttack));
	mPlayerAction[ATTACK]=new CAction(mBodyEntity,ATTACK);
	}
	
}
void CPlayer::Ready()
{
	if(!mActionReady)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(READY,mActionReady));
	mPlayerAction[READY]=new CAction(mBodyEntity,READY);
	}
}
void CPlayer::Die(const Ogre::FrameEvent& evt)
{
	if(!mActionDie)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(DIE,mActionDie));
	mPlayerAction[DIE]=new CAction(mBodyEntity,DIE);
	}
}



}