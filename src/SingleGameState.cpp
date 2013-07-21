#include "SingleGameState.h"
#include"FightClubApp.h"
namespace FightClub
{
CSingleGameState::CSingleGameState(void):mRound(1),mPause(false)
{
	mPlayer1=0;
	mPlayer2=0;
	mStaticScene=0;                      //静态场景
	mExCamera=0;                         //扩展相机

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
	//背景音乐播放
	AudioManager::getSingletonPtr()->play(AUDIO_BACKGROUND,0.75,true,false);
	FightClubApp::getSingletonPtr()->mLog->logMessage("正在进入单机游戏.......");
	createLight();
	createCamera();
	createScene();
	createUI();
	startRound();

}

void CSingleGameState::pause(void)
{

	AudioManager::getSingletonPtr()->stop(AUDIO_BACKGROUND,false); //停止背景音乐
	
}
void CSingleGameState::exit(void)
{
	AudioManager::getSingletonPtr()->stop(AUDIO_BACKGROUND,false);  //停在播放音乐
	/*退出该状态时清理创建相机 视口 灯光*/
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
	AudioManager::play(AUDIO_BACKGROUND,0.5f,true,false);    //播放游戏背景音乐
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
		::ShowWindow(GetActiveWindow(),SW_MINIMIZE);                //左win键，程序窗口最小化切换到桌面
	
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
    if (e.key == OIS::KC_R)               //切换几何体渲染模型
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
	/*.....................加一个地面......................*/
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
	
	//游戏状态UI
	//mPlayer1->getLifeBar()->initProgressBar("对应的血条UI窗口名");
	//mPlayer2->getLifeBar()->initProgressBar("对应的血条UI窗口名");
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
	
	//摄像机复位
	//if(!mExCamera)
	mPlayer1->InitTowards();
	mPlayer2->InitTowards();
	mPlayer1->setPosition(-mPlayer1->getInitPosition());                 //玩家复位
	mPlayer2->setPosition(mPlayer2->getInitPosition());
	mPlayer1->initWinRound();
	mPlayer2->initWinRound();
	GUIManager::getWindow("FightClub/GameUIRound")->setProperty("Text","ROUND-"+Ogre::StringConverter
			::toString(mRound)+"-"+Ogre::StringConverter::toString(mRoundTime));
	//mPlayer1->initLife();                                               //初始化生命值
	//mPlayer2->initLife();
}

void CSingleGameState::update( float timeSinceLastFrame)
{
	//mLifeBar1->updateProgress();
	 //摄像机更新
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

	if(!mTimer)                                                                      //计时器
	{
		mTimer=new Ogre::Timer();
	    mTimer->reset();
	}
	//更新每局比赛时间
	if(mTimer->getMilliseconds()*0.001>=1&&mRoundTime>=1)
	{
		mRoundTime--;
		GUIManager::getWindow("FightClub/GameUIRound")->setProperty("Text","ROUND-"+Ogre::StringConverter
			::toString(mRound)+"-"+Ogre::StringConverter::toString(mRoundTime));
		mTimer->reset();
	}

	if(mRoundTime==0&&mRound<3)                            //每场比赛3局
	{
		startRound();
		mRound++;
	}
	if(mPlayer1&&mPlayer2&&mRoundTime>0)                 //每局只要有人挂了,就提前进入下一局
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
	if(mRoundTime==0&&mPlayer1->GetLife()>0&&mPlayer2->GetLife()>0)  //一局结束，双方都未挂
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
	if(mRoundTime==0&&mRound==3)                                      //每结束三局,记录一场比赛结果
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
		int result=0;                                      //计算碰撞结果
	 
	//判断谁被谁击中
	 while(mRoundTime<0)
	 {
		
          
			
		//int result=mColiisionDetector->isColiision(mPlayer1,mPlayer2);
	   if(result>0)                                   //player1击中mplayer2
	     {
		  mPlayer1->Beat(mPlayer2);
		  mPlayer2->BeBeat(mPlayer1);
	     }
	   else if(result<0)                             //player2击中mplayer1
	     {
		  mPlayer2->Beat(mPlayer1);
		  mPlayer1->BeBeat(mPlayer2);
	     }
	   mPlayer1->getLifeBar()->updateProgress(mPlayer1->GetLife()/100);//玩家1血条更新
	   mPlayer2->getLifeBar()->updateProgress(mPlayer2->GetLife()/100);//玩家2血条更新
	   mRoundTime=mRoundTime-int(mTimer->getMilliseconds()*0.001);//更新RoundTime

	//音效跟视频效果更新
	

	 
	//mRoundTime 在UI中显示
	//每一局中途有人挂了 对方赢 记录双方玩家输赢
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
			mRound=mRound+1;                                   //加赛一局
			//平局
		}
		startRound();                                            //开始下一局
		mTimer->reset();                                         //重新计时

	}
	 }
	}*/

}


}