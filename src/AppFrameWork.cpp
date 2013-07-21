#include"AppFrameWork.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif
namespace FightClub
{
	AppFrameWork::AppFrameWork(void)
	{
		mFpsMode=OgreBites::TL_RIGHT;
		mAudioMgr=0;
	    mStateMgr=0;
        mMenuState=0;
	    mLoadState=0;
	    mSingleState=0;
	    mOlState=0;
        mPauseState=0;
	}

	AppFrameWork::~AppFrameWork(void)
	{
		//if (mTrayMgr) delete mTrayMgr;
        Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
        windowClosed(mWindow);
		delete mRoot;
	}

	void AppFrameWork::instantState(void)
	{
		mLoadState=CLoadResourceState::getSingletonPtr();
		mMenuState=CMenuState::getSingletonPtr();
		mSingleState=CSingleGameState::getSingletonPtr();
		mPauseState=CPauseState::getSingletonPtr();
		//mOlState=COlGameState::getSingletonPtr();
	}

	void AppFrameWork::instantManager(void)
	{
		mAudioMgr=AudioManager::getSingletonPtr();
		mStateMgr=StateManager::getSingletonPtr();
	}
	bool AppFrameWork::configure(void)
	{
		if(mRoot->restoreConfig())
            {
                mWindow=mRoot->initialise(true,"FightClub Window");
        /*添加一个窗口图标*/
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
	void AppFrameWork::locationResources(void)
	{
		Ogre::ConfigFile cf;
        cf.load(mResourcesCfg);
              /*遍历配置文件中所有资源组*/
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
	void AppFrameWork::loadResources(void)
	{ 
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	void AppFrameWork::createFrameListener(void)
	{
		//mLog->logMessage("创建帧监听");
		OIS::ParamList pl;
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;

        mWindow->getCustomAttribute("WINDOW", &windowHnd);
        windowHndStr << windowHnd;
        pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

        mInputMgr= OIS::InputManager::createInputSystem(pl);

        mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject( OIS::OISKeyboard, true ));
        mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject( OIS::OISMouse, true ));

        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
        windowResized(mWindow);

    //Register as a Window listener
        Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

        mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
		//mTrayMgr->showFrameStats(mFpsMode);
        //mTrayMgr->showLogo(OgreB);
		mTrayMgr->hideCursor();
		mRoot->addFrameListener(this);
	}


	bool AppFrameWork::initOgre(void)
	{
		Ogre::LogManager* mLogMgr=new Ogre::LogManager();
		mLog=Ogre::LogManager::getSingletonPtr()->createLog("FightClubAppfile.log", true, true, false);
#ifdef _DEBUG
        mResourcesCfg = "resources_d.cfg";
        mPluginsCfg = "plugins_d.cfg";
#else
        mResourcesCfg = "resources.cfg";
        mPluginsCfg = "plugins.cfg";
#endif
		 mRoot = new Ogre::Root(mPluginsCfg);
         if (!configure())
			 return false;
		 instantState();
		 instantManager();
		 mViewport=mWindow->addViewport(0);
		 //createFrameListener();
		 locationResources();
		 mLog->logMessage("到达此处.........");
		 mLog->logMessage("Coming here......");
		 //loadResources();
		 
		 Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		 return true;
	}

	void AppFrameWork::go(void)
	{
		if(!initOgre())
		{
			mLog->logMessage("Iinting is over.......");
			mStateMgr->changeState(mLoadState);
			loadResources();
			createFrameListener();
			mStateMgr->changeState(mMenuState);
			mLog->logMessage("开始渲染");
			mRoot->startRendering();
		}
	}
	void AppFrameWork::update(unsigned long timeSinceLastFrame)
	{
		/*if(mLoadState&&mMenuState)
		{
			if(mLoadState->getIsLoadEnd())
				mStateMgr->changeState(mMenuState);
		}*/
		if(mStateMgr)
			mStateMgr->update(timeSinceLastFrame);
	}
	void AppFrameWork::windowResized(Ogre::RenderWindow* rw)
       {
            unsigned int width, height, depth;
            int left, top;
            rw->getMetrics(width, height, depth, left, top);

            const OIS::MouseState &ms = mMouse->getMouseState();
            ms.width = width;
            ms.height = height;
       }
   void AppFrameWork::windowClosed(Ogre::RenderWindow* rw)
      {
         if( rw == mWindow )
             {
                if( mInputMgr )
                 {
                    mInputMgr->destroyInputObject( mMouse );
                    mInputMgr->destroyInputObject( mKeyboard );

                    OIS::InputManager::destroyInputSystem( mInputMgr);
                    mInputMgr = 0;
        }
    }
}

    bool AppFrameWork::frameStarted(const Ogre::FrameEvent& evt)
	{
		return true;
	}
    bool AppFrameWork::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		mKeyboard->capture();
        mMouse->capture();
        mTrayMgr->frameRenderingQueued(evt);
		update(evt.timeSinceLastFrame);
		return true;
	}
	bool AppFrameWork::keyPressed(const OIS::KeyEvent& e)
	{
		if(e.key==OIS::KC_F)
		{
			if(mFpsMode==OgreBites::TL_RIGHT)
				mFpsMode=OgreBites::TL_NONE;
		
		else
			mFpsMode=OgreBites::TL_RIGHT;
		}
		else if(e.key==OIS::KC_F10)
			  mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
		return true;
	}

	bool AppFrameWork::keyReleased(const OIS::KeyEvent &arg)
	{
		return true;
	}
	bool AppFrameWork::mouseMoved(const OIS::MouseEvent &arg)
	{
		return true;
	}
	bool AppFrameWork::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
	{
		return true;
	}

	bool AppFrameWork::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)

	{
		return true;
	}







}