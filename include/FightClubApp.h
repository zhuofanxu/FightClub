#pragma once
/*
Ogre win32�������࣬�̳д����¼������࣬֡�����࣬���̣���������
�Լ�����ģ����
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
	
	inline Ogre::RenderWindow* getRenderWindow(){return mWindow;}    //��ȡ��Ⱦ����
	inline Ogre::SceneManager *getGameSceneMgr() {return mGameSceneMgr;}// ��Ϸ����������, ��Ϸ״̬ʹ��
		
    inline Ogre::SceneManager *getAideSceneMgr() {return mAideSceneMgr;}// ������������������, ����ʹ��, ��Menu��
		
	inline void shutDown() { mShutDown = true; }         // ������Ϸ
	void release();                                      // ��Ϸ���������Դ��������       
	void startGame();                                  // ��ʼ��Ϸѭ��
	void update(float timeSinceLastFrame);      //���º���
	void instantState(void);                           //��Ϸ������״̬��ʵ����
	void instantManager(void);                         //��Ϸ�����й�����ʵ����

    bool setup();                                     //��������
    bool configure(void);                            //��������
    void chooseSceneManager(void);                   //��������������
    void createCamera(void);                        //�������
    void createFrameListener(void);                  //����֡����
	void createScene(void);                         //��������
    void destroyScene(void);                         //���ٳ���
    void createViewports(void);                     //�����ӿ�
    void setupResources(void);                      //��Դ��λ
    void createResourceListener(void);              
    void loadResources(void);                      //������Դ

    // ֡�����ӿں���
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
    //���̼����ӿں���
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // ����������
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    //�����¼�����
    //���������Ч����
    virtual void windowResized(Ogre::RenderWindow* rw);
    //�ڴ��ڹر�ǰж��OIS�豸
    virtual void windowClosed(Ogre::RenderWindow* rw);
protected:
	Ogre::SceneManager		*mGameSceneMgr;	// ��Ϸʹ�õĳ���������
	Ogre::SceneManager		*mAideSceneMgr; // ��������������, ����������;
	AudioManager         *mAudioMgr;            //��Ƶ������
	StateManager         *mStateMgr;            //״̬������
	GUIManager           *mGUIMgr;             //GUI������
	CMenuState           *mMenuState;          //�˵�״̬
	CLoadResourceState   *mLoadState;           //������Դ״̬
	CSingleGameState     *mSingleState;         //������Ϸ״̬
	CPauseState          *mPauseState;         //��Ϸ��ͣ״̬

	//Ogre::SceneManager* mSceneMgr;            //����������
	Ogre::RenderWindow* mWindow;             //win32����(��Ⱦ����)
    Ogre::String mResourcesCfg;              //��Դ�����ļ�
    Ogre::String mPluginsCfg;               //Ogre��������ļ�
	   // OgreBites
	OgreBites::SdkTrayManager* mTrayMgr;   //Ogre�Դ����������
    bool mCursorWasVisible;                  // ����Ƿ�ɼ�
    bool mShutDown;                          //�����Ƿ�ر�
	bool mFpsShow;                          //��ʾfps
	int  mFps;
public:
    Ogre::Root *mRoot;                     //Ogre��
    Ogre::Camera* mCamera;                //���
    Ogre::Log*				mLog;         //Ogre������־������bug��
	Ogre::Timer*			mTimer1;       //��ʱ��1
	Ogre::Timer*			mTimer2;
	Ogre::Timer*			mTimer3;
	//OIS Input devices
    OIS::InputManager* mInputManager;         //���������
    OIS::Mouse*    mMouse;                    //���
    OIS::Keyboard* mKeyboard;                 //����

	
};
#endif // #ifndef __FightClub_h_
}