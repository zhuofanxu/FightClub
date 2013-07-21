#include"CAnimationBlender.h"
namespace FightClub
{
void AnimationBlender::init(const Ogre::String& animation,bool l)
{
	Ogre::AnimationStateSet* set=mEntity->getAllAnimationStates();
	Ogre::AnimationStateIterator it=set->getAnimationStateIterator();
	
	while(it.hasMoreElements())
	{
		Ogre::AnimationState* ani=it.getNext();
		ani->setEnabled(false);
		ani->setWeight(0);
		ani->setTimePosition(0);
	}
	mSource=mEntity->getAnimationState(animation);
	mSource->setEnabled(true);
	mSource->setWeight(1);
	mTimeleft=0;
	mDuration=1;
	loop=l;
	complete=false;
}

 void AnimationBlender::blend( const Ogre::String &animation, BlendingTransition transition, Ogre::Real duration, bool l )
 {
   loop = l;
   if( transition == AnimationBlender::BlendSwitch)                  //直切切换方式，只需更新mSource
   {
      if(mSource != 0)
          mSource->setEnabled(false);
          mSource = mEntity->getAnimationState(animation);
          mSource->setEnabled(true);
          mSource->setWeight(1);
          mSource->setTimePosition(0);
          mTimeleft = 0;
   } 
   else 
   { 
      Ogre::AnimationState *newTarget = mEntity->getAnimationState(animation);
 
      if(mTimeleft > 0)
      {
        
         if( newTarget == mTarget )                // 新目标为正在混合中的目标
         {
            // 不做任何事情
         }
         else if( newTarget == mSource )          //新目标为原动画
         {
                                                // 返回 
            mSource = mTarget;
            mTarget = newTarget;               //更新正在混合的目标
            mTimeleft = mDuration - mTimeleft; //
         }
         else                                //新目标为真正的新动画
         {
           
            if( mTimeleft < mDuration * 0.5 )
            {
               // 替换正在混合的目标
               mTarget->setEnabled(false);
               mTarget->setWeight(0);
            }
            else
            {
               // 旧的混合目标成为新的原动画
               mSource->setEnabled(false);
               mSource->setWeight(0);
               mSource = mTarget;
 
            } 
            mTarget = newTarget;
            mTarget->setEnabled(true);
            mTarget->setWeight( 1.0 - mTimeleft / mDuration );
            mTarget->setTimePosition(0);
         }
      }
      else                    //上次的混合已经结束，当前未处于混合状态中
      {
          
         mTransition = transition;
         mTimeleft = mDuration = duration;
         mTarget = newTarget;
         mTarget->setEnabled(true);
         mTarget->setWeight(0);
         mTarget->setTimePosition(0);
      }
   }
 }
 

 void AnimationBlender::addTime(Ogre::Real time )
 {
   if(mSource!= 0)
   {
      if(mTimeleft > 0)                         //混合未完成
      {
         mTimeleft -= time;                     //更新混合剩余时间
 
         if( mTimeleft < 0)                     //完成混合
         {
            mSource->setEnabled(false);
            mSource->setWeight(0);
            mSource = mTarget;                //更新原动画
            mSource->setEnabled(true);
            mSource->setWeight(1);
            mTarget = 0;
         }
         else                                  //依然在混合，设置动画权值
         {
                                                  
            mSource->setWeight(mTimeleft / mDuration);
            mTarget->setWeight(1.0 - mTimeleft / mDuration);
 
            if(mTransition == AnimationBlender::BlendWhileAnimating)
               mTarget->addTime(time);
         }
      }
 
      if (mSource->getTimePosition() >= mSource->getLength())
      {
         complete=true;
      }
      else
      {
        complete=false;
      }
 
      mSource->addTime(time);
      mSource->setLoop(loop);
   }
 }
 
 AnimationBlender::AnimationBlender( Ogre::Entity *entity ) : mEntity(entity) 
 {
 }
 }