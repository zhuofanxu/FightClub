#include"PauseState.h"

namespace FightClub
{
CPauseState::CPauseState(void):mQuit(false)
{
	
}


CPauseState::~CPauseState(void)
{
	
}

void CPauseState::enter(void)
{
	
	createScene();
}

void CPauseState::pause(void)
{
	
	
}
void CPauseState::exit(void)
{
	GUIManager::getWindow("FightClub/PauseUI")->hide();
	GUIManager::showGUICursor(false);
}
void CPauseState::resume(void)
{

}
void CPauseState::changeSize(int width, int height)
{

}
bool CPauseState:: keyPressed(const OIS::KeyEvent &e)
{
	if(e.key==OIS::KC_LWIN)
		::ShowWindow(GetActiveWindow(),SW_MINIMIZE);                //左win键，程序窗口最小化切换到桌面
	if(e.key==OIS::KC_ESCAPE)  //ESC键触发退出游戏暂停
	{
		//GUIManager::setCursorType(CURSOR_FIRE);
		//mQuit=true;
	}
		//StateManager::getSingletonPtr()->changeState(CSingleGameState::getSingletonPtr());
	
	return true;
}
bool CPauseState:: keyReleased( const OIS::KeyEvent &e )
{
	return true;
}

bool CPauseState:: mouseMoved(const OIS::MouseEvent &e)
{
	GUIManager::getSingletonPtr()->injectMouseMove(e.state.X.rel,e.state.Y.rel,e.state.X.abs,e.state.Y.abs);
	return true;
}
bool CPauseState:: mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	if(!GUIManager::getSingletonPtr()->injectMouseButtonDown(MB_OISToCEGUI(id)))
		return false;
	return true;
}
bool CPauseState:: mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	if(!GUIManager::getSingletonPtr()->injectMouseButtonUp(MB_OISToCEGUI(id)))
		return false;
	return true;
}
bool CPauseState::OnClikedContinue(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);
	mQuit=true;
	return true;
}
bool CPauseState::OnClikedToMenu(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_CLICK, 0.5f, false, false);
	StateManager::getSingletonPtr()->popState();
	StateManager::getSingletonPtr()->changeState(CMenuState::getSingletonPtr());
	return true;
}
bool CPauseState::MouseOver(const CEGUI::EventArgs& e)
{
	AudioManager::play(AUDIO_MOUSE_OVER, 1.0f, false, false);
	return true;
}
void CPauseState::subscribeGUIEvent(void)
{
	GUIManager::subscribeEvent("FightClub/PauseUI/GN" ,CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CPauseState::OnClikedContinue,this));
	GUIManager::subscribeEvent("FightClub/PauseUI/MU",CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CPauseState::OnClikedToMenu,this));
	GUIManager::subscribeEvent("FightClub/PauseUI/GN" ,CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&CPauseState::MouseOver,this));
	GUIManager::subscribeEvent("FightClub/PauseUI/MU",CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&CPauseState::MouseOver,this));
}
void CPauseState::createScene(void)
{
	//mRoot=Ogre::Root::getSingletonPtr();
	//mSceneMgr = mRoot->getSceneManager("Generic");
	
	//摄像机实例化
	//.......
	// GUIManager::loadWindow("PauseUI");  
	GUIManager::getWindow("FightClub/PauseUI")->show();
	GUIManager::showGUICursor(true);
	subscribeGUIEvent();
}

void CPauseState::update(float timeSinceLastFrame)
{
	if(mQuit)
	{
		mQuit=false;
	    popState();

	}
	GUIManager::getSingletonPtr()->update(timeSinceLastFrame);

}


}