/*Ogre 程序高级框架，基于教程 有修改*/
#pragma once
#ifndef _AppFrameWork_h_
#define _AppFrameWork_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include"SingletonT.h"
#include"AudioManager.h"
#include"StateManager.h"
#include"LoadResourceState.h"
#include"MenuState.h"
#include"OlGameState.h"
#include"SingleGameState.h"
#include"PauseState.h"
namespace FightClub
{
class AppFrameWork : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener,
	public SingletonT<AppFrameWork>
{
	SINGLETON_DEFINE(AppFrameWork);
public:
	Ogre::Root*				mRoot;
	Ogre::RenderWindow*		mWindow;
	Ogre::Viewport*			mViewport;
	Ogre::Log*				mLog;
	Ogre::Timer*			mTimer;
	
	OIS::InputManager*		mInputMgr;
	OIS::Keyboard*			mKeyboard;
	OIS::Mouse*				mMouse;
 
    OgreBites::SdkTrayManager*  mTrayMgr;


	void go(void);
	void update(unsigned long timeSinceLastFrame);
	void instantState(void);
	void instantManager(void);
	AppFrameWork(void);
	~AppFrameWork(void);
	bool initOgre(void);
	bool setup(void);
    bool configure(void);
   // void chooseSceneManager(void);
    //void createCamera(void);
    void createFrameListener(void);
	//void createScene(void);
    void destroyScene(void);
    void createViewports(void);
    void locationResources(void);
    //void createResourceListener(void);
	void loadResources(void);
	 /* Ogre::FrameListener*/
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	 /*OIS::KeyListener*/
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    /* OIS::MouseListener*/
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	 // Ogre::WindowEventListener
    //调整鼠标移动区域
    virtual void windowResized(Ogre::RenderWindow* rw);
    //在窗口关闭前卸载OIS输入设备
    virtual void windowClosed(Ogre::RenderWindow* rw);
protected:
	Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
	OgreBites::TrayLocation mFpsMode;

	AudioManager         *mAudioMgr;
	StateManager         *mStateMgr;
	CMenuState           *mMenuState;
	CLoadResourceState   *mLoadState;
	CSingleGameState     *mSingleState;
	COlGameState         *mOlState;
	CPauseState          *mPauseState;
};
#endif //_AppFrameWork_h_
}
	
 