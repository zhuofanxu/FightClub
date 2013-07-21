/*
-----------------------------------------------------------------------------
Filename:    FightClub.cpp
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
*/
#include "FightClubApp.h"

namespace FightClub{

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


//-------------------------------------------------------------------------------------
FightClubApp::FightClubApp(void)
    : mRoot(0),
    mCamera(0),
    mGameSceneMgr(0),
	mAudioMgr(0),
	mStateMgr(0),
	mGUIMgr(0),
	mMenuState(0),
	mLoadState(0),
	mSingleState(0),
	mPauseState(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
	mIsSingleState(false),
	mIsMenuState(false),
	mHasgotoGame(false),
	mHasgotoMenu(false),
	mFpsShow(true),
	mFps(0)
{
	mTimer1=new Ogre::Timer;
	mTimer2=new Ogre::Timer;
	mTimer1->reset();
	
}

//-------------------------------------------------------------------------------------
FightClubApp::~FightClubApp(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if(mTimer1)   delete mTimer1;
	if(mTimer2)   delete mTimer2;
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//-------------------------------------------------------------------------------------
bool FightClubApp::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
	if(mRoot->restoreConfig())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "FightClub");

        // Let's add a nice window icon
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        HWND hwnd;
        mWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
        LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
        SetClassLong( hwnd, GCL_HICON, iconID );
#endif
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void FightClubApp::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
   mAideSceneMgr = mRoot->createSceneManager(ST_GENERIC, "FightClubGame-Aide");
   mGameSceneMgr = mRoot->createSceneManager(ST_GENERIC, "FightClubGame");
   mGameSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
}
//-------------------------------------------------------------------------------------
void FightClubApp::createCamera(void)
{
    
}
//-------------------------------------------------------------------------------------
void FightClubApp::createFrameListener(void)
{
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
	//mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMRIGHT);;
   // mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();
    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void FightClubApp::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void FightClubApp::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void FightClubApp::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void FightClubApp::createResourceListener(void)
{

}
void FightClubApp::instantState(void)
{

	mLoadState=CLoadResourceState::getSingletonPtr();
	mMenuState=CMenuState::getSingletonPtr();
	mSingleState=CSingleGameState::getSingletonPtr();
	mPauseState=CPauseState::getSingletonPtr();
}
void FightClubApp::instantManager(void)
{
	mAudioMgr=AudioManager::getSingletonPtr();
	mStateMgr=StateManager::getSingletonPtr();
	mGUIMgr=GUIManager::getSingletonPtr();
}
void FightClubApp::update(float timeSinceLastFrame)
{
	if(mStateMgr)
			mStateMgr->update(timeSinceLastFrame);
}
//-------------------------------------------------------------------------------------
void FightClubApp::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void FightClubApp::startGame(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;
	
  
	  mRoot->startRendering();
	   
       release();                      //清理资源
}
//-------------------------------------------------------------------------------------
void FightClubApp::release()
{
	
	mStateMgr->destroy();
	mGUIMgr->destroy();
	mAudioMgr->destroy();
	mGameSceneMgr->clearScene();	
	mAideSceneMgr->clearScene();
    mRoot->destroySceneManager(mGameSceneMgr);	
	mRoot->destroySceneManager(mAideSceneMgr);

	mWindow->destroy();
	mRoot->shutdown();
}
bool FightClubApp::setup(void)
{
	Ogre::LogManager* mLogMgr=new Ogre::LogManager();
	instantState();
	instantManager();
	mLog=Ogre::LogManager::getSingletonPtr()->createLog("FightClubApp.log", true, true, false);
    mRoot = new Ogre::Root(mPluginsCfg);
    setupResources();
	
    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
	//createCamera();
	//createViewports();
	mStateMgr->pushState(mLoadState);
    loadResources();
	mStateMgr->changeState(mMenuState);
	mHasgotoMenu=true;
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

   
    createResourceListener();
    // Load resources
	
	// Create the scene
   // createScene();

	createFrameListener();

    return true;
};
//-------------------------------------------------------------------------------------
void FightClubApp::createScene(void)
{
	
}
//-------------------------------------------------------------------------------------
bool FightClubApp::frameStarted(const Ogre::FrameEvent& evt)
{
	mTimer2->reset();
	return true;
}
bool FightClubApp::frameEnded(const Ogre::FrameEvent& evt)
{
	mFps=1.0/(float(mTimer2->getMilliseconds())/1000);
	return true;
}
bool FightClubApp::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(evt.timeSinceLastFrame<1.0/60)
		::Sleep((1.0/60-evt.timeSinceLastFrame)*1000);
	//GUIManager::getWindow("FightClub/FPS")->setProperty("Text","FPS:"+Ogre::StringConverter::toString(mFps));
	if(mTimer1->getMilliseconds()/1000>=1)
	{
		//mFps=1/evt.timeSinceLastFrame;
		GUIManager::getWindow("FightClub/FPS")->setProperty("Text","FPS:"+Ogre::StringConverter::toString(mFps));
		mTimer1->reset();
	}
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

   
	update(evt.timeSinceLastFrame);
    return true;
}
//-------------------------------------------------------------------------------------
bool FightClubApp::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
		if(mFpsShow)
		{
			GUIManager::getWindow("FightClub/FPS")->hide();
			mFpsShow=false;
		}
		else
		{
			GUIManager::getWindow("FightClub/FPS")->show();
			mFpsShow=true;
		}
        //mTrayMgr->toggleAdvancedFrameStats();
    }
  
   
    else if(arg.key == OIS::KC_F5)             //刷新所有纹理
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
	else if (arg.key == OIS::KC_F10)   //F10键游戏截图
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
 

  if(mStateMgr)
	  mStateMgr->keyPressed(arg);
    return true;
}

bool FightClubApp::keyReleased( const OIS::KeyEvent &arg )
{
   if(mStateMgr)
	   mStateMgr->keyReleased(arg);
    return true;
}

bool FightClubApp::mouseMoved( const OIS::MouseEvent &arg )
{
	if(mStateMgr)
		 mStateMgr->mouseMoved(arg);
    if (mTrayMgr->injectMouseMove(arg)) return true;
    return true;
}

bool FightClubApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if(mStateMgr)
		mStateMgr->mousePressed(arg,id);
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    return true;
}

bool FightClubApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if(mStateMgr)
		mStateMgr->mouseReleased(arg,id);
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    return true;
}

//Adjust mouse clipping area
void FightClubApp::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void FightClubApp::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        FightClubApp *FightApp;
		FightApp=FightClubApp::getSingletonPtr();

        try {
            FightApp->startGame();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
}