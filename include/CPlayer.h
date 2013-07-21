/*所有玩家角色基类*/
#pragma once
#ifndef _CPlayer_h_
#define _CPlayer_h_
#include"CObject.h"
#include"CAction.h"
#include"CAnimationBlender.h"
#include"Common.h"
#include"LifeBar.h"
#include<map>
#define SPEED 1.5
namespace FightClub
{
class CPlayer : public CObject,public IFrameListener
{
public:

	/*将对象管理器类声明为玩家角色的友员类
	前者可以访问后者的私有成员和保护成员*/
	friend class CObjectManager;            
	//角色的通用的一些操作
	CPlayer(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	virtual ~CPlayer(){}
	/*
	@evt          帧事件
	@mGoalTowards 角色的目标方向
	*/
	virtual void  Walk(Ogre::Vector3 mGoalTowards);                       //角色行走
    virtual void  Attack();                                      
	virtual void  Die(const Ogre::FrameEvent& evt);                       //角色死亡  
	virtual void  Ready();
	void          InitTowards();
	virtual void  Beat(CPlayer* mPlayer){mPlayer->mLife-=0.01;}                     //玩家击中对方后的数值计算
	virtual void  BeBeat(CPlayer* mPlayer){mPlayer->mLife+=0.01;}                   //玩家被对方后击中后的数值计算
	//void Run();                                               //角色跑动
	void Destroy();                                            //角色销毁
	void  addWinRound(){mWinRound=mWinRound+1;}
	int   getWinRound(){return mWinRound;}
	void  initWinRound(){mWinRound=0;}
	void  initLife(){mLife=100;}
	float GetLife(){return mLife;}                            //获取角色生命值
	Ogre::Vector3& getInitPosition(){return mInitPosition;}
	Ogre::SceneNode* getSightNode(){return mSightNode;}
	Ogre::SceneNode* getCameraNode(){return mCameraNode;}
	CLifeBar* getLifeBar(){return mLifeBar;}
	virtual void upadate(unsigned long timeSiceLastFrame){}  //玩家更新
	virtual void InjectKeyDown(const OIS::KeyEvent& arg){}
	virtual void InjectKeyUp(const OIS::KeyEvent& arg){}

	virtual bool processUnbufferInput(OIS::Keyboard* mKeyboard,const Ogre::FrameEvent& evt){return true;}//非缓冲输入逻辑处理
    bool mMove;
protected:
	
	//角色的共有的一些属性
	Ogre::SceneNode* mSightNode;              //景象节点
	Ogre::SceneNode* mCameraNode;             //追踪相机节点
	Ogre::Vector3 mCurrentTowards;           //角色的当前朝向
	Ogre::Quaternion mQuat;                 //保存角色转向变量的四元数
	Ogre::Vector3 mInitPosition;            //玩家初始位置
	int   mWinRound;                        //每场比赛的获胜局数
	float  mLife;                         //角色的生命值，对应血条的进度
	CLifeBar* mLifeBar;                    //对应的UI生命条
	CAction* mActionWalk;                 //角色行走动作
	CAction* mActionAttack;              //基本攻击动作
	CAction* mActionReady;              //准备动作
	CAction* mActionDie;                //死亡动作
	std::string mPlayerName;            //角色名
	AnimationBlender *mBlender;        //动画混合器
	std::map<Player_Action_Type,CAction*>mPlayerAction;  //分别用动作类型和动作类指针两种自定义的数据类型创建map对象
};
}
#endif //_CPlayer_h_