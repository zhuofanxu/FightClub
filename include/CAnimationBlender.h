#pragma once
/*游戏角色的动作混合器类 ，使得角色在某一时间内动作切换的流畅*/
#ifndef AnimationBlender_h_
#define AnimationBlender_h_
#include <Ogre.h>
namespace FightClub
{
class AnimationBlender
{
public:

    enum BlendingTransition    //不同的混合方式
       {
         BlendSwitch,            //直接切换到目标动画
         BlendWhileAnimating,   // 交叉淡入淡出（源动画比例缩小，同时目标动画比例增大）
         BlendThenAnimate      // 淡出源动画到目标动画第一帧，然后开始目标动画 
       };
private:


    Ogre::Entity *mEntity;
    Ogre::AnimationState *mSource;
    Ogre::AnimationState *mTarget;
    BlendingTransition mTransition;
    bool loop;                            //是否循环
    ~AnimationBlender() {}
public: 
     Ogre::Real mTimeleft, mDuration;           //持续时间
     bool complete;
	 /*@animation 动画名
	   @transition 混合方式
	   @duration   混合时间
	 */
     void blend( const Ogre::String &animation, BlendingTransition transition, Ogre::Real duration, bool l );
     void addTime( Ogre::Real );
     Ogre::Real getProgress() { return mTimeleft/ mDuration; }
     Ogre::AnimationState *getSource() { return mSource; }
     Ogre::AnimationState *getTarget() { return mTarget; }
	 void setAnimationSource(Ogre::AnimationState* animationstate){mSource=animationstate;}
     AnimationBlender(Ogre::Entity *entity);
     void init( const Ogre::String &animation,bool l);
};
}
#endif