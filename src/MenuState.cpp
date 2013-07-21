#include"MenuState.h"
#include"FightClubApp.h"
namespace FightClub
{

CMenuState::CMenuState()
{
	mRoot=0;
	mSceneMgr=0;
	mCamera=0;
    mViewport=0;
    mWindow=0;
    mTimer=0;
}

CMenuState::~CMenuState()
{
}
    void   CMenuState::createLight(void)
	  {
		mSceneMgr = mRoot->getSceneManager("FightClubGame-Aide");
		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
		Ogre::Light *light = mSceneMgr->createLight("MainLight");
		light->setPosition(Ogre::Vector3(100, 100, 100));
	  }
	void  CMenuState::createCamera(void)
	{
		mWindow=FightClubApp::getSingletonPtr()->getRenderWindow();
		mSceneMgr->destroyAllCameras();
		mWindow->removeAllViewports();
		mCamera=mSceneMgr->createCamera("MenuCamera");
		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(Ogre::ColourValue(1.0,0.4,0.4));
		//mSceneMgr->setFog(Ogre::FOG_LINEAR, ColourValue(1.0f, 1.0f, 0.8f), 0, 15, 100);
		mCamera->setAspectRatio((float)mViewport->getActualWidth() / (float)mViewport->getActualHeight());
		mCamera->setNearClipDistance(0.1);
	}

void CMenuState::enter(void)
{
	FightClubApp::getSingletonPtr()->mLog->logMessage("正在进入菜单......");
	mRoot=FightClubApp::getSingletonPtr()->mRoot;
	createLight();
	FightClubApp::getSingletonPtr()->mLog->logMessage("创建灯光完毕......");
	createCamera();
	FightClubApp::getSingletonPtr()->mLog->logMessage("创建相机完毕......");
	createScene();
}

void CMenuState::pause(void)
{

}
void CMenuState::exit(void)
{
	/*退出该状态时清理创建相机 视口 灯光*/
		mSceneMgr->destroyAllCameras();
		mWindow->removeAllViewports();
		mSceneMgr->destroyAllLights();
		
		//AudioManager::stop(AUDIO_MENU,false);           //停止菜单音乐
}
void CMenuState::resume(void)
{
	
}
void CMenuState::changeSize(int width, int height)
{

}
bool CMenuState:: keyPressed(const OIS::KeyEvent &e)
{
	if(e.key==OIS::KC_LWIN)
		::ShowWindow(GetActiveWindow(),SW_MINIMIZE);                //左win键，程序窗口最小化切换到桌面
	return true;
}
bool CMenuState:: keyReleased( const OIS::KeyEvent &e)
{
	return true;
}

bool CMenuState:: mouseMoved(const OIS::MouseEvent &e)
{
	GUIManager::getSingletonPtr()->injectMouseMove(e.state.X.rel,e.state.Y.rel,e.state.X.abs,e.state.Y.abs);
	return true;
}
bool CMenuState:: mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if(!GUIManager::getSingletonPtr()->injectMouseButtonDown(MB_OISToCEGUI(id)))
		return false;
	return true;
}
bool CMenuState:: mouseReleased(const OIS::MouseEvent &e,OIS::MouseButtonID id)
{
	if(!GUIManager::getSingletonPtr()->injectMouseButtonUp(MB_OISToCEGUI(id)))
		return false;
	return true;
}

bool CMenuState::OnClikedSingle(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);//鼠标点击控件对应声音系统的响应
	//进入单机游戏状态
	GUIManager::getWindow("FightClub/MenuS")->hide();
	GUIManager::showGUICursor(false);
	//FightClubApp::getSingletonPtr()->mIsSingleState=true;
	//FightClubApp::getSingletonPtr()->mIsMenuState=false;
	StateManager::getSingletonPtr()->changeState(CSingleGameState::getSingletonPtr());
	
	return true;
}

bool CMenuState::OnClikedOnLine(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);
	return true;
}

bool CMenuState::OnClikedOption(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);
	return true;
}

bool CMenuState::OnClikedExit(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);
	GUIManager::getWindow("FightClub/MenuS/SG")->hide();
	GUIManager::getWindow("FightClub/MenuS/OG")->hide();
	GUIManager::getWindow("FightClub/MenuS/OP")->hide();
	GUIManager::getWindow("FightClub/MenuS/GE")->hide();
	//GUIManager::getWindow("MenuUI")->setAlpha(GUIManager::getWindow("MenuUI")->getAlpha()/2);//主菜单变暗
	GUIManager::getWindow("FightClub/MenuS/SureExit")->show();                
	return true;
}

bool CMenuState::OnClikedYes(const CEGUI::EventArgs& e)
{
	//::exit(0);
	FightClubApp::getSingletonPtr()->shutDown();
	
	return true;
}

bool CMenuState::OnClikedNo(const CEGUI::EventArgs& e)
{
	//GUIManager::getWindow("SureExitDialogUI")->hide();
	GUIManager::getWindow("FightClub/MenuS/SG")->show();
	GUIManager::getWindow("FightClub/MenuS/OG")->show();
	GUIManager::getWindow("FightClub/MenuS/OP")->show();
	GUIManager::getWindow("FightClub/MenuS/GE")->show();
	GUIManager::getWindow("FightClub/MenuS/SureExit")->hide();  
	//GUIManager::getWindow("MenuUI")->setAlpha(GUIManager::getWindow("MenuUI")->getAlpha()*2);
	return true;
}
bool CMenuState::MouseOver(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_OVER, 1.0f, false, false);
	return true;
}
//bool OnCliked(const CEGUI::EventArgs& e){return true;}
void CMenuState::subscribeGUIEvent(void)
{

	//GUIManager::subscribeEvent("FightClub/MenuS/SG" ,CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(OnCliked));
	GUIManager::subscribeEvent("FightClub/MenuS/SG" ,CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedSingle,this));
	GUIManager::subscribeEvent("FightClub/MenuS/OG" ,CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedOnLine,this));
	GUIManager::subscribeEvent("FightClub/MenuS/OP" ,CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedOption,this));
	GUIManager::subscribeEvent("FightClub/MenuS/GE",CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedExit,this));

	GUIManager::subscribeEvent("FightClub/MenuS/SureExit/Yes",CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedYes,this));
	GUIManager::subscribeEvent("FightClub/MenuS/SureExit/No",CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CMenuState::OnClikedNo,this));

	GUIManager::subscribeEvent("FightClub/MenuS/SG" , CEGUI::DefaultWindow::EventMouseEntersArea, CEGUI::Event::Subscriber(&CMenuState::MouseOver,this));
	GUIManager::subscribeEvent("FightClub/MenuS/OG" , CEGUI::DefaultWindow::EventMouseEntersArea, CEGUI::Event::Subscriber(&CMenuState::MouseOver,this));
	GUIManager::subscribeEvent("FightClub/MenuS/OP" , CEGUI::DefaultWindow::EventMouseEntersArea, CEGUI::Event::Subscriber(&CMenuState::MouseOver,this));
	GUIManager::subscribeEvent("FightClub/MenuS/GE", CEGUI::DefaultWindow::EventMouseEntersArea,CEGUI::Event::Subscriber(&CMenuState::MouseOver,this));
}
void CMenuState::createScene(void)
{
	static bool isLoad=false;                             //静态变量的只定义一次
	if(!isLoad)
	{
	    GUIManager::getSingletonPtr()->init();                //CEGUI主题初始化
	    FightClubApp::getSingletonPtr()->mLog->logMessage("CEGUI初始化完毕......");
	    GUIManager::loadWindow("FightClub");                        //加载菜单布局文件
		FightClubApp::getSingletonPtr()->mLog->logMessage("载入cegui布局完毕......");
		isLoad=true;
	}
	GUIManager::getWindow("FightClub/MenuS")->show();
	GUIManager::showGUICursor(true);
	GUIManager::getWindow("FightClub/MenuS/SureExit")->hide();  //隐藏退出子对话框   
     /*.....隐藏游戏进行中的界面.........*/
	GUIManager::getWindow("FightClub/GameUISL")->hide();         
	GUIManager::getWindow("FightClub/GameUISR")->hide(); 
	GUIManager::getWindow("FightClub/GameUIPL")->hide(); 
	GUIManager::getWindow("FightClub/GameUIPR")->hide(); 
	GUIManager::getWindow("FightClub/GameUITL")->hide(); 
	GUIManager::getWindow("FightClub/GameUITR")->hide(); 
	GUIManager::getWindow("FightClub/GameUIRound")->hide();
	GUIManager::getWindow("FightClub/GameUIWin")->hide();
	GUIManager::getWindow("FightClub/PauseUI")->hide();
	GUIManager::createImageset("MenuUIImage","FightClub.jpg");
	GUIManager::getWindow("FightClub/MenuS")->setProperty("Image","set:MenuUIImage image:full_image");
	//GUIManager::showGUICursor(true);
	subscribeGUIEvent();
	

}

void CMenuState::update(unsigned long timeSinceLastFrame)
{
	GUIManager::getSingletonPtr()->update(timeSinceLastFrame);
}
}