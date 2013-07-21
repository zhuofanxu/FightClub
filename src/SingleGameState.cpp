#include "SingleGameState.h"
#include"FightClubApp.h"
namespace FightClub
{
CSingleGameState::CSingleGameState(void):mRound(1),mPause(false)
{
	mPlayer1=0;
	mPlayer2=0;
	mStaticScene=0;                      //��̬����
	mExCamera=0;                         //��չ���

	mRoot=0;
	mSceneMgr=0;
	mCamera=0;
    mViewport;
    mWindow=0;
    mTimer=0;
	mLifeBar1=new CLifeBar();
	mLifeBar2=new CLifeBar();
}


CSingleGameState::~CSingleGameState(void)
{
	//if(mPlayer1)delete mPlayer1;
	//if(mPlayer2)delete mPlayer2;
	//if(mExCamera)delete mExCamera;
	//if(mStaticScene)delete mStaticScene;
}

void  CSingleGameState::createLight(void)
	{
		mRoot=FightClubApp::getSingletonPtr()->mRoot;
		mSceneMgr = mRoot->getSceneManager("FightClubGame");
		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
		Ogre::Light *light = mSceneMgr->createLight("SingleLight");
		light->setPosition(Ogre::Vector3(100, 100, 100));
	}
	void CSingleGameState::createCamera(void)
	{
		
		mWindow=FightClubApp::getSingletonPtr()->getRenderWindow();
		mSceneMgr->destroyAllCameras();
		mWindow->removeAllViewports();
		mCamera=mSceneMgr->createCamera("GameCamera");
		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(Ogre::ColourValue(1.0,0.4,0.4));
		
	    mCamera->setAspectRatio((float)mViewport->getActualWidth() / (float)mViewport->getActualHeight());
		//mCamera->setPosition(Ogre::Vector3(0,100,100));
	    mCamera->setNearClipDistance(0.1);
		mExCamera=new ExtendedCamera("ExtendeCamera",mSceneMgr,mCamera);
	}

void CSingleGameState::enter(void)
{
	//�������ֲ���
	AudioManager::getSingletonPtr()->play(AUDIO_BACKGROUND,0.75,true,false);
	FightClubApp::getSingletonPtr()->mLog->logMessage("���ڽ��뵥����Ϸ.......");
	createLight();
	createCamera();
	createScene();
	createUI();
	startRound();

}

void CSingleGameState::pause(void)
{

	AudioManager::getSingletonPtr()->stop(AUDIO_BACKGROUND,false); //ֹͣ��������
	
}
void CSingleGameState::exit(void)
{
	AudioManager::getSingletonPtr()->stop(AUDIO_BACKGROUND,false);  //ͣ�ڲ�������
	/*�˳���״̬ʱ��������� �ӿ� �ƹ�*/
	if(mExCamera)
	delete mExCamera;
	mSceneMgr->destroyAllCameras();
	mWindow->removeAllViewports();
	mSceneMgr->destroyAllLights();
	
	//delete mPlayer1;
	//delete mPlayer2;
	GUIManager::getWindow("FightClub/GameUISL")->hide();         
	GUIManager::getWindow("FightClub/GameUISR")->hide(); 
	GUIManager::getWindow("FightClub/GameUIPL")->hide(); 
	GUIManager::getWindow("FightClub/GameUIPR")->hide(); 
	GUIManager::getWindow("FightClub/GameUITL")->hide(); 
	GUIManager::getWindow("FightClub/GameUITR")->hide(); 
	GUIManager::getWindow("FightClub/GameUIRound")->hide();
	GUIManager::getWindow("FightClub/GameUIWin")->hide();
	//if(mExCamera)delete mExCamera;
	
}
void CSingleGameState::resume(void)
{
	//mPause=false;
	AudioManager::play(AUDIO_BACKGROUND,0.5f,true,false);    //������Ϸ��������
}
void CSingleGameState::changeSize(int width, int height)
{

}
bool CSingleGameState:: keyPressed(const OIS::KeyEvent &e)
{
	
    if(e.key==OIS::KC_ESCAPE)
	   {
		   
		  StateManager::getSingletonPtr()->pushState(CPauseState::getSingletonPtr());
	   }
	
	if(e.key==OIS::KC_LWIN)
		::ShowWindow(GetActiveWindow(),SW_MINIMIZE);                //��win�������򴰿���С���л�������
	
	if(e.key==OIS::KC_C&&mExCamera)
	{
		switch(mExCamera->getCameraMode())
		{
		case 0:
			mExCamera->setCameraMode(1);
			if(mPlayer1&&mPlayer2)
			{
                mExCamera->instantUpdate(Ogre::Vector3(0, 300, 400),
					0.5*(mPlayer1->getSightNode()->_getDerivedPosition()+mPlayer2->getSightNode()->_getDerivedPosition()));
		    }
			break;
		case 1:
			mExCamera->setCameraMode(0);
			if(mPlayer1&&mPlayer2)
			{
                mExCamera->instantUpdate(0.5*(mPlayer1->getCameraNode()->_getDerivedPosition()
					+mPlayer2->getCameraNode()->_getDerivedPosition()),
					0.5*(mPlayer1->getSightNode()->_getDerivedPosition()+mPlayer2->getSightNode()->_getDerivedPosition()));
		    }
			break;
	
         }
	}
	if(mPlayer1)
		mPlayer1->InjectKeyDown(e);
	if(mPlayer2)
		mPlayer2->InjectKeyDown(e);
    if (e.key == OIS::KC_R)               //�л���������Ⱦģ��
     {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
	}
	return true;
}
bool CSingleGameState:: keyReleased( const OIS::KeyEvent &e )
{
	if(mPlayer1)
		mPlayer1->InjectKeyUp(e);
	if(mPlayer2)
		mPlayer2->InjectKeyUp(e);
	return true;
}

bool CSingleGameState:: mouseMoved(const OIS::MouseEvent &e)
{
	return true;
}
bool CSingleGameState:: mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}
bool CSingleGameState:: mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}

void CSingleGameState::createScene(void)
{   
	/*.....................��һ������......................*/
	static bool isCreate=false;
	if(!isCreate)
	{

	    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
        Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
        Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	    Ogre::SceneNode *groundNode=mSceneMgr->getRootSceneNode()->createChildSceneNode();
	    groundNode->attachObject(entGround);
        entGround->setMaterialName("Examples/Rockwall"); 
	    mPlayer1=new CPlayerMySelf("JACK",mSceneMgr,"NinJaObject1","ninja.mesh");
	    mPlayer2=new CPlayerOther("ANDY",mSceneMgr,"NinJaObject2","ninja.mesh"); 
	    
		isCreate=true;
      }
	 
		//mPlayer1->setPosition(-mPlayer1->getInitPosition());
        //mPlayer2->setPosition(mPlayer2->getInitPosition());
	  
	
	 
      // mStaticScene=new CObject(mSceneMgr,"Leitai","quanguan.mesh");
	
	//��Ϸ״̬UI
	//mPlayer1->getLifeBar()->initProgressBar("��Ӧ��Ѫ��UI������");
	//mPlayer2->getLifeBar()->initProgressBar("��Ӧ��Ѫ��UI������");
}
void CSingleGameState::createUI(void)
{
	GUIManager::getWindow("FightClub/GameUISL")->show();         
	GUIManager::getWindow("FightClub/GameUISR")->show(); 
	GUIManager::getWindow("FightClub/GameUIPL")->show(); 
	GUIManager::getWindow("FightClub/GameUIPR")->show(); 
	GUIManager::getWindow("FightClub/GameUITL")->show(); 
	GUIManager::getWindow("FightClub/GameUITR")->show(); 
	GUIManager::getWindow("FightClub/GameUIRound")->show();
	GUIManager::createImageset("PlaayerImage","ninja.png");
	GUIManager::getWindow("FightClub/GameUISL")->setProperty("Image","set:PlaayerImage image:full_image");
	GUIManager::getWindow("FightClub/GameUISR")->setProperty("Image","set:PlaayerImage image:full_image");
	//GUIManager::getWindow("FightClub/GameUIWin")->show();
	mLifeBar1->initProgressBar("FightClub/GameUIPL");
	mLifeBar2->initProgressBar("FightClub/GameUIPR");
	//mLifeBar1->updateProgress(0.5);

}
void CSingleGameState::startRound()
{
	mRoundTime=99;
	
	//�������λ
	//if(!mExCamera)
	mPlayer1->InitTowards();
	mPlayer2->InitTowards();
	mPlayer1->setPosition(-mPlayer1->getInitPosition());                 //��Ҹ�λ
	mPlayer2->setPosition(mPlayer2->getInitPosition());
	mPlayer1->initWinRound();
	mPlayer2->initWinRound();
	GUIManager::getWindow("FightClub/GameUIRound")->setProperty("Text","ROUND-"+Ogre::StringConverter
			::toString(mRound)+"-"+Ogre::StringConverter::toString(mRoundTime));
	//mPlayer1->initLife();                                               //��ʼ������ֵ
	//mPlayer2->initLife();
}

void CSingleGameState::update( float timeSinceLastFrame)
{
	//mLifeBar1->updateProgress();
	 //���������
	if(mExCamera&&mPlayer1&&mPlayer2&&mExCamera->getCameraMode()==0)
		 mExCamera->update(timeSinceLastFrame,
			 0.5*(mPlayer1->getCameraNode()->_getDerivedPosition()+
			 mPlayer2->getCameraNode()->_getDerivedPosition()),
			 0.5*(mPlayer1->getSightNode()->_getDerivedPosition()+
			 mPlayer2->getSightNode()->_getDerivedPosition()));
	 if(mPlayer1)
	 {
		    mPlayer1->processUnbufferInput(FightClubApp::getSingletonPtr()->mKeyboard,timeSinceLastFrame);
			
	 }
	 if(mPlayer2)
	 {
		    mPlayer2->processUnbufferInput(FightClubApp::getSingletonPtr()->mKeyboard,timeSinceLastFrame);
			
	 }
	 if(mPlayer1&&mPlayer2)
	 {
		 mPlayer1->mMove=!(mPlayer1->getBodyNode()->_getWorldAABB().intersects(mPlayer2->getBodyNode()->_getWorldAABB()));
		 mPlayer2->mMove=!(mPlayer1->getBodyNode()->_getWorldAABB().intersects(mPlayer2->getBodyNode()->_getWorldAABB()));
		 if(mPlayer1->getBodyNode()->_getWorldAABB().intersects(mPlayer2->getBodyNode()->_getWorldAABB()))
		 {
			 if(mPlayer1->getBodyEntity()->getAnimationState("Attack3")->getEnabled()||mPlayer1->getBodyEntity()->getAnimationState("Spin")->getEnabled())
			 {
				 mPlayer1->Beat(mPlayer2);
				 mPlayer2->BeBeat(mPlayer1);
			 }
			 if(mPlayer2->getBodyEntity()->getAnimationState("Attack3")->getEnabled()||mPlayer2->getBodyEntity()->getAnimationState("Spin")->getEnabled())
			 {
				 mPlayer2->Beat(mPlayer1);
				 mPlayer1->BeBeat(mPlayer2);
			 }
			 mLifeBar1->updateProgress((100-mPlayer1->GetLife())/100);
			 mLifeBar2->updateProgress((100-mPlayer2->GetLife())/100);
		 }
		
	 }

	if(!mTimer)                                                                      //��ʱ��
	{
		mTimer=new Ogre::Timer();
	    mTimer->reset();
	}
	//����ÿ�ֱ���ʱ��
	if(mTimer->getMilliseconds()*0.001>=1&&mRoundTime>=1)
	{
		mRoundTime--;
		GUIManager::getWindow("FightClub/GameUIRound")->setProperty("Text","ROUND-"+Ogre::StringConverter
			::toString(mRound)+"-"+Ogre::StringConverter::toString(mRoundTime));
		mTimer->reset();
	}

	if(mRoundTime==0&&mRound<3)                            //ÿ������3��
	{
		startRound();
		mRound++;
	}
	if(mPlayer1&&mPlayer2&&mRoundTime>0)                 //ÿ��ֻҪ���˹���,����ǰ������һ��
	{
		if(mPlayer1->GetLife()<=0)
		{
			mPlayer2->addWinRound();
			startRound();
		}
		else if(mPlayer2->GetLife()<=0)
		{
			mPlayer1->addWinRound();
			startRound();
		}
	}
	if(mRoundTime==0&&mPlayer1->GetLife()>0&&mPlayer2->GetLife()>0)  //һ�ֽ�����˫����δ��
	{
		if(mPlayer1->GetLife()>mPlayer2->GetLife())
		{
			mPlayer1->addWinRound();
		}
		else
		{
			mPlayer2->addWinRound();
		}
	}
	if(mRoundTime==0&&mRound==3)                                      //ÿ��������,��¼һ���������
	{
		if(mPlayer1->getWinRound()>mPlayer2->getWinRound())
		{
			//mPlayer1->win();
		}
		else
		{
			//mPlayer2->win();
		}
	}
	/*for(int i=1;i<=mRound;i++)
	{
		int result=0;                                      //������ײ���
	 
	//�ж�˭��˭����
	 while(mRoundTime<0)
	 {
		
          
			
		//int result=mColiisionDetector->isColiision(mPlayer1,mPlayer2);
	   if(result>0)                                   //player1����mplayer2
	     {
		  mPlayer1->Beat(mPlayer2);
		  mPlayer2->BeBeat(mPlayer1);
	     }
	   else if(result<0)                             //player2����mplayer1
	     {
		  mPlayer2->Beat(mPlayer1);
		  mPlayer1->BeBeat(mPlayer2);
	     }
	   mPlayer1->getLifeBar()->updateProgress(mPlayer1->GetLife()/100);//���1Ѫ������
	   mPlayer2->getLifeBar()->updateProgress(mPlayer2->GetLife()/100);//���2Ѫ������
	   mRoundTime=mRoundTime-int(mTimer->getMilliseconds()*0.001);//����RoundTime

	//��Ч����ƵЧ������
	

	 
	//mRoundTime ��UI����ʾ
	//ÿһ����;���˹��� �Է�Ӯ ��¼˫�������Ӯ
	if(mPlayer1->GetLife()<=0&&mPlayer2->GetLife()>0)
	{
		//mPlayer2->win();
		//mPlayer1->lose();
	}
	else if(mPlayer2->GetLife()<=0&&mPlayer1->GetLife()>0)
	{
		//mPlayer1->win();
		//mPlayer2->lose();
	}
	if(mRoundTime=0)
	{

		if(mPlayer1->GetLife()-mPlayer2->GetLife()>0)
		{
			//mPlayer1->win();
		    //mPlayer2->lose();
		}
		else if(mPlayer1->GetLife()-mPlayer2->GetLife()<0)
		{
			//mPlayer2->win();
		    //mPlayer1->lose();
		}
		else
		{
			mRound=mRound+1;                                   //����һ��
			//ƽ��
		}
		startRound();                                            //��ʼ��һ��
		mTimer->reset();                                         //���¼�ʱ

	}
	 }
	}*/

}


}