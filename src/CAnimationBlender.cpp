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
   if( transition == AnimationBlender::BlendSwitch)                  //ֱ���л���ʽ��ֻ�����mSource
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
        
         if( newTarget == mTarget )                // ��Ŀ��Ϊ���ڻ���е�Ŀ��
         {
            // �����κ�����
         }
         else if( newTarget == mSource )          //��Ŀ��Ϊԭ����
         {
                                                // ���� 
            mSource = mTarget;
            mTarget = newTarget;               //�������ڻ�ϵ�Ŀ��
            mTimeleft = mDuration - mTimeleft; //
         }
         else                                //��Ŀ��Ϊ�������¶���
         {
           
            if( mTimeleft < mDuration * 0.5 )
            {
               // �滻���ڻ�ϵ�Ŀ��
               mTarget->setEnabled(false);
               mTarget->setWeight(0);
            }
            else
            {
               // �ɵĻ��Ŀ���Ϊ�µ�ԭ����
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
      else                    //�ϴεĻ���Ѿ���������ǰδ���ڻ��״̬��
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
      if(mTimeleft > 0)                         //���δ���
      {
         mTimeleft -= time;                     //���»��ʣ��ʱ��
 
         if( mTimeleft < 0)                     //��ɻ��
         {
            mSource->setEnabled(false);
            mSource->setWeight(0);
            mSource = mTarget;                //����ԭ����
            mSource->setEnabled(true);
            mSource->setWeight(1);
            mTarget = 0;
         }
         else                                  //��Ȼ�ڻ�ϣ����ö���Ȩֵ
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