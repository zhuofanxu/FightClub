#include"CPlayerMySelf.h"
namespace FightClub
{
CPlayerMySelf::CPlayerMySelf(const std::string& PlayerName,Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName):CPlayer(
	sceneMgr,name,meshName)
{
	mInitSightNodePos=Ogre::Vector3(0,100,50);
	mInitCameraNodePos=Ogre::Vector3(0,100,500);
	mBodyNode->scale(Ogre::Vector3(0.5,0.5,0.5));
	mSightNode=mBodyNode->createChildSceneNode(mBodyNode->getName()+"_sight",mInitSightNodePos);
	mCameraNode=mBodyNode->createChildSceneNode(mBodyNode->getName()+"_camera",mInitCameraNodePos);
	mPlayerName=PlayerName;
	mTimer=0;
	mLifeBar=new CLifeBar();
	mBlender=new AnimationBlender(mBodyEntity);
	Ready();
	mBlender->init(mPlayerAction[READY]->getAnimationName(READY),true);
}

CPlayerMySelf::~CPlayerMySelf()
{
	if(mTimer)
		delete mTimer;
	if(mActionWalk)
		delete mActionWalk;
	if(mActionDie)
		delete mActionDie;
	if(mActionAttack)
		delete mActionAttack;
	if(mActionReady)
		delete mActionReady;
	if(mActionJump)
		delete mActionJump;
	if(mActionSpinAttack)
		delete mActionSpinAttack;
	//if(mBlender)
		//delete mBlender;
}


void CPlayerMySelf::Walk(Ogre::Vector3 mGoalTowards)
{
	CPlayer::Walk(mGoalTowards);
	//用于扩展walk方法
	//...........
}

void CPlayerMySelf::Attack()
{
	int mDebug=0;                    //调试变量
	CPlayer::Attack();
	mDebug=1;
	//用于扩展Attack()方法
	//...........

}

void CPlayerMySelf::SpinAttack(void)
{
	if(!mActionSpinAttack)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(SPINATTACK,mActionSpinAttack));
	mPlayerAction[SPINATTACK]=new CAction(mBodyEntity,SPINATTACK);
	}
}

void CPlayerMySelf::Jump(void)
{
	if(!mActionJump)
	{
	mPlayerAction.insert(std::pair<Player_Action_Type,CAction*>(JUMP,mActionJump));
	mPlayerAction[JUMP]=new CAction(mBodyEntity,JUMP);
	}
}

void CPlayerMySelf::InjectKeyDown(const OIS::KeyEvent& arg)       //处理缓冲输入交互
{
	
	if(arg.key==OIS::KC_W||arg.key==OIS::KC_A||arg.key==OIS::KC_S||arg.key==OIS::KC_D)
	{
		 if(mPlayerAction[WALK])
			 mBlender->blend(mBodyEntity->getAnimationState("Walk")->getAnimationName(),mBlender->BlendWhileAnimating,0.4,true);

	}
}

void CPlayerMySelf::InjectKeyUp(const OIS::KeyEvent& arg)
{
	if(arg.key==OIS::KC_W||arg.key==OIS::KC_A||arg.key==OIS::KC_S||arg.key==OIS::KC_D)
		mBlender->blend(mPlayerAction[READY]->getAnimationName(READY),mBlender->BlendWhileAnimating,0.4,false);
}

bool CPlayerMySelf:: processUnbufferInput(OIS::Keyboard* mKeyboard,float timeSinceLastFrame)
{
	Ogre::Vector3 mNewPosition=mBodyNode->getPosition();
	bool mIsWalked=false;
	bool mIsReadyed=true;
	
	if(mKeyboard->isKeyDown(OIS::KC_W))
	{
	    mIsWalked=true;
		mIsReadyed=false;
		
		
		mNewPosition.z-=SPEED;
		if(!mMove)
			mNewPosition.z+=SPEED;
		Walk(-Ogre::Vector3::UNIT_Z);
	}


	if(mKeyboard->isKeyDown(OIS::KC_A))
	{
		 mIsWalked=true;
		 mIsReadyed=false;
		 
		 mNewPosition.x-=SPEED;
		 if(!mMove)
			  mNewPosition.x+=SPEED;
		 Walk(-Ogre::Vector3::UNIT_X);

	}
	if(mKeyboard->isKeyDown(OIS::KC_S))
	{
		 mIsWalked=true;
		 mIsReadyed=false;
		
	     mNewPosition.z+=SPEED;	 
		  if(!mMove)
			   mNewPosition.z-=SPEED;	 
		 Walk(Ogre::Vector3::UNIT_Z);
	}
	if(mKeyboard->isKeyDown(OIS::KC_D))
	{
		 mIsWalked=true;
		 mIsReadyed=false;
		
		 mNewPosition.x+=SPEED;
		  if(!mMove)
			   mNewPosition.x-=SPEED;
		 Walk(Ogre::Vector3::UNIT_X);
	}
	if(mKeyboard->isKeyDown(OIS::KC_J))
	 {
	   Attack();
	   mBlender->blend(mBodyEntity->getAnimationState("Attack3")->getAnimationName(),mBlender->BlendThenAnimate,0.4,false);
	 }
	if(mKeyboard->isKeyDown(OIS::KC_K))
	{
		SpinAttack();
		mBlender->blend(mBodyEntity->getAnimationState("Spin")->getAnimationName(),mBlender->BlendThenAnimate,0.4,false);
	}

	if(mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		Jump();
		mBlender->blend(mBodyEntity->getAnimationState("Jump")->getAnimationName(),mBlender->BlendThenAnimate,0.4,false);
	}

	mBodyNode->setPosition(mNewPosition);
	mBlender->addTime(timeSinceLastFrame);

	return true;
}
void CPlayerMySelf::upadate(unsigned long timeSiceLastFrame)
{
	
}
}