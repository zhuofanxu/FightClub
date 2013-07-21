#include"CAction.h"
namespace FightClub
{
CAction::CAction(Ogre::Entity *mEntity,Player_Action_Type pat):
isEnabled(false),isLooped(true),mAnimationState(0)
{
	mAnimationState=mEntity->getAnimationState(getAnimationName(pat));
}

const Ogre::String CAction::getAnimationName(Player_Action_Type pat)
{
	switch(pat)
	{
	case WALK:
		mAnimationName="Walk";
		break;
	case DIE:
		mAnimationName="Death1";
		break;
	case ATTACK:
		mAnimationName="Attack3";
		break;
	case READY:
		mAnimationName="Idle3";
		break;
	case SPINATTACK:
		mAnimationName="Spin";
		break;
	case JUMP:
		mAnimationName="Jump";
		break;
	}
	return mAnimationName;
}

void CAction::setEnabled(bool mEnable)
{
    mAnimationState->setEnabled(mEnable);
	isEnabled=mEnable;
}

void CAction::setLoop(bool mEnable)
{
	  mAnimationState->setLoop(mEnable);
	  isLooped=mEnable;
}

void CAction::addTime(const Ogre::FrameEvent& evt)
{
	mAnimationState->addTime(1.5*evt.timeSinceLastFrame);
}
}