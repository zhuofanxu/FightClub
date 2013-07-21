/*���ж���״̬��*/
#pragma once
#ifndef _CAction_h_
#define _CAction_h_
#include<Ogre.h>
namespace FightClub
{
enum Player_Action_Type
{
  WALK,
  ATTACK,
  DIE,
  READY,
  SPINATTACK,
  JUMP,
};

class CAction
{

public:
	/*
	@mEntity         �󶨶�����ʵ��
	@pat             ö�ٶ�������
	@mAnimationState �붯���ԵĶ���״̬
	*/
	CAction(Ogre::Entity *mEntity,Player_Action_Type pat);
	~CAction(){}
	inline bool getisEnabled(){return isEnabled;}                           //��ȡ����״̬
	inline bool getLooped(){return isLooped;}                               //��ȡ����ѭ��״̬
	inline bool IsAnimationOver(){return mAnimationState->hasEnded();}      //�����Ƿ񲥷����
	void setEnabled(bool mEnable);                                         //�����
	void setLoop(bool mEnable);                                               //���ö���ѭ��
	void setInitAnimation(){mAnimationState->setTimePosition(0.0f);}        //��������Ϊ���
	void addTime(const Ogre::FrameEvent& evt);                                     //Ϊ�������ʱ��
	const Ogre::String getAnimationName(Player_Action_Type pat);

	Ogre::AnimationState* getAnimationSt(){return mAnimationState;}         //��ȡ����״ָ̬��
	//void setCurAction(CAction* mAction);
	//CAction* getCurAction(){return }
	private:
		//CAction* mCurAction;
	    Ogre::AnimationState *mAnimationState;    //��Ӧ�Ķ���״̬
	    std::string          mAnimationName;     //ģ�͵Ķ�����
	    bool                 isEnabled;         //�Ƿ񼤻�
	    bool                 isLooped;         //�Ƿ�ѭ��
};
}
#endif//_CAction_h_