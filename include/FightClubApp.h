#pragma once
/*
Ogre win32程序框架类，继承窗口事件监听类，帧监听类，键盘，鼠标监听类
以及单例模版类
*/
#ifndef __FightClubApp_h_
#define __FightClubApp_h_

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
#include"SingleGameState.h"
#include"PauseState.h"

namespace FightClub{
class FightClubApp : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener,public SingletonT<FightClubApp>
{
	SINGLETON_DEFINE(FightClubApp);
public:
    FightClubApp(void);
    virtual ~FightClubApp(void);
    bool mHasgotoGame;
	bool mHasgotoMenu;
	bool mIsSingleState;
	bool mIsMenuState;
	
	
public:
	
	inline Ogre::RenderWindow* getRenderWindow(){return mWindow;}    //获取渲染窗口
	inline Ogre::SceneManager *getGameSceneMgr() {return mGameSceneMgr;}// 游戏场景管理器, 游戏状态使用
		
    inline Ogre::SceneManager *getAideSceneMgr() {return mAideSceneMgr;}// 其他辅助场景管理器, 辅助使用, 如Menu等
		
	inline void shutDown() { mShutDown = true; }         // 结束游戏
	void release();                                      // 游戏结束后对资源进行清理       
	void startGame();                                  // 开始游戏循环
	void update(float timeSinceLastFrame);      //更新函数
	void instantState(void);                           //游戏中所有状态的实例化
	void instantManager(void);                         //游戏中所有管理器实例化

    bool setup();                                     //程序配置
    bool configure(void);                            //窗口配置
    void chooseSceneManager(void);                   //创建场景管理器
    void createCamera(void);                        //创建相机
    void createFrameListener(void);                  //创建帧监听
	void createScene(void);                         //创建场景
    void destroyScene(void);                         //销毁场景
    void createViewports(void);                     //创建视口
    void setupResources(void);                      //资源定位
    void createResourceListener(void);              
    void loadResources(void);                      //载入资源

    // 帧监听接口函数
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
    //键盘监听接口函数
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // 鼠标监听函数
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    //窗口事件监听
    //调整鼠标有效区域
    virtual void windowResized(Ogre::RenderWindow* rw);
    //在窗口关闭前卸载OIS设备
    virtual void windowClosed(Ogre::RenderWindow* rw);
protected:
	Ogre::SceneManager		*mGameSceneMgr;	// 游戏使用的场景管理器
	Ogre::SceneManager		*mAideSceneMgr; // 辅助场景管理器, 用于其它用途
	AudioManager         *mAudioMgr;            //音频管理器
	StateManager         *mStateMgr;            //状态管理器
	GUIManager           *mGUIMgr;             //GUI管理器
	CMenuState           *mMenuState;          //菜单状态
	CLoadResourceState   *mLoadState;           //载入资源状态
	CSingleGameState     *mSingleState;         //单机游戏状态
	CPauseState          *mPauseState;         //游戏暂停状态

	//Ogre::SceneManager* mSceneMgr;            //场景管理器
	Ogre::RenderWindow* mWindow;             //win32窗口(渲染窗口)
    Ogre::String mResourcesCfg;              //资源配置文件
    Ogre::String mPluginsCfg;               //Ogre插件配置文件
	   // OgreBites
	OgreBites::SdkTrayManager* mTrayMgr;   //Ogre自带界面管理器
    bool mCursorWasVisible;                  // 鼠标是否可见
    bool mShutDown;                          //窗口是否关闭
	bool mFpsShow;                          //显示fps
	int  mFps;
public:
    Ogre::Root *mRoot;                     //Ogre根
    Ogre::Camera* mCamera;                //相机
    Ogre::Log*				mLog;         //Ogre程序日志，跟踪bug用
	Ogre::Timer*			mTimer1;       //计时器1
	Ogre::Timer*			mTimer2;
	Ogre::Timer*			mTimer3;
	//OIS Input devices
    OIS::InputManager* mInputManager;         //输入管理器
    OIS::Mouse*    mMouse;                    //鼠标
    OIS::Keyboard* mKeyboard;                 //键盘

	
};
#endif // #ifndef __FightClub_h_
}