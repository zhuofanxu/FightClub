/*������ҽ�ɫ����*/
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

	/*�����������������Ϊ��ҽ�ɫ����Ա��
	ǰ�߿��Է��ʺ��ߵ�˽�г�Ա�ͱ�����Ա*/
	friend class CObjectManager;            
	//��ɫ��ͨ�õ�һЩ����
	CPlayer(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	virtual ~CPlayer(){}
	/*
	@evt          ֡�¼�
	@mGoalTowards ��ɫ��Ŀ�귽��
	*/
	virtual void  Walk(Ogre::Vector3 mGoalTowards);                       //��ɫ����
    virtual void  Attack();                                      
	virtual void  Die(const Ogre::FrameEvent& evt);                       //��ɫ����  
	virtual void  Ready();
	void          InitTowards();
	virtual void  Beat(CPlayer* mPlayer){mPlayer->mLife-=0.01;}                     //��һ��жԷ������ֵ����
	virtual void  BeBeat(CPlayer* mPlayer){mPlayer->mLife+=0.01;}                   //��ұ��Է�����к����ֵ����
	//void Run();                                               //��ɫ�ܶ�
	void Destroy();                                            //��ɫ����
	void  addWinRound(){mWinRound=mWinRound+1;}
	int   getWinRound(){return mWinRound;}
	void  initWinRound(){mWinRound=0;}
	void  initLife(){mLife=100;}
	float GetLife(){return mLife;}                            //��ȡ��ɫ����ֵ
	Ogre::Vector3& getInitPosition(){return mInitPosition;}
	Ogre::SceneNode* getSightNode(){return mSightNode;}
	Ogre::SceneNode* getCameraNode(){return mCameraNode;}
	CLifeBar* getLifeBar(){return mLifeBar;}
	virtual void upadate(unsigned long timeSiceLastFrame){}  //��Ҹ���
	virtual void InjectKeyDown(const OIS::KeyEvent& arg){}
	virtual void InjectKeyUp(const OIS::KeyEvent& arg){}

	virtual bool processUnbufferInput(OIS::Keyboard* mKeyboard,const Ogre::FrameEvent& evt){return true;}//�ǻ��������߼�����
    bool mMove;
protected:
	
	//��ɫ�Ĺ��е�һЩ����
	Ogre::SceneNode* mSightNode;              //����ڵ�
	Ogre::SceneNode* mCameraNode;             //׷������ڵ�
	Ogre::Vector3 mCurrentTowards;           //��ɫ�ĵ�ǰ����
	Ogre::Quaternion mQuat;                 //�����ɫת���������Ԫ��
	Ogre::Vector3 mInitPosition;            //��ҳ�ʼλ��
	int   mWinRound;                        //ÿ�������Ļ�ʤ����
	float  mLife;                         //��ɫ������ֵ����ӦѪ���Ľ���
	CLifeBar* mLifeBar;                    //��Ӧ��UI������
	CAction* mActionWalk;                 //��ɫ���߶���
	CAction* mActionAttack;              //������������
	CAction* mActionReady;              //׼������
	CAction* mActionDie;                //��������
	std::string mPlayerName;            //��ɫ��
	AnimationBlender *mBlender;        //���������
	std::map<Player_Action_Type,CAction*>mPlayerAction;  //�ֱ��ö������ͺͶ�����ָ�������Զ�����������ʹ���map����
};
}
#endif //_CPlayer_h_