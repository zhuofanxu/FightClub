#pragma once
/*��Ϸ��ɫ�Ķ���������� ��ʹ�ý�ɫ��ĳһʱ���ڶ����л�������*/
#ifndef AnimationBlender_h_
#define AnimationBlender_h_
#include <Ogre.h>
namespace FightClub
{
class AnimationBlender
{
public:

    enum BlendingTransition    //��ͬ�Ļ�Ϸ�ʽ
       {
         BlendSwitch,            //ֱ���л���Ŀ�궯��
         BlendWhileAnimating,   // ���浭�뵭����Դ����������С��ͬʱĿ�궯����������
         BlendThenAnimate      // ����Դ������Ŀ�궯����һ֡��Ȼ��ʼĿ�궯�� 
       };
private:


    Ogre::Entity *mEntity;
    Ogre::AnimationState *mSource;
    Ogre::AnimationState *mTarget;
    BlendingTransition mTransition;
    bool loop;                            //�Ƿ�ѭ��
    ~AnimationBlender() {}
public: 
     Ogre::Real mTimeleft, mDuration;           //����ʱ��
     bool complete;
	 /*@animation ������
	   @transition ��Ϸ�ʽ
	   @duration   ���ʱ��
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