/*所有动作状态类*/
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
	@mEntity         绑定动画的实体
	@pat             枚举动作类型
	@mAnimationState 与动作对的动画状态
	*/
	CAction(Ogre::Entity *mEntity,Player_Action_Type pat);
	~CAction(){}
	inline bool getisEnabled(){return isEnabled;}                           //获取动画状态
	inline bool getLooped(){return isLooped;}                               //获取动画循环状态
	inline bool IsAnimationOver(){return mAnimationState->hasEnded();}      //动画是否播放完毕
	void setEnabled(bool mEnable);                                         //激活动画
	void setLoop(bool mEnable);                                               //设置动画循环
	void setInitAnimation(){mAnimationState->setTimePosition(0.0f);}        //将动画设为起点
	void addTime(const Ogre::FrameEvent& evt);                                     //为动画添加时间
	const Ogre::String getAnimationName(Player_Action_Type pat);

	Ogre::AnimationState* getAnimationSt(){return mAnimationState;}         //获取动画状态指针
	//void setCurAction(CAction* mAction);
	//CAction* getCurAction(){return }
	private:
		//CAction* mCurAction;
	    Ogre::AnimationState *mAnimationState;    //对应的动画状态
	    std::string          mAnimationName;     //模型的动画名
	    bool                 isEnabled;         //是否激活
	    bool                 isLooped;         //是否循环
};
}
#endif//_CAction_h_