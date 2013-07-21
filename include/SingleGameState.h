#pragma once
/*单机游戏状态类，继承自State,并继承单例模板，现实单例模式，
此状态全局唯一
*/
#include"state.h"
#include"PauseState.h"
#include"SingletonT.h"
#include"CPlayerMySelf.h"
#include"CPlayerOther.h"
#include"AudioManager.h"
#include"ExtendedCamera.h"
#include"LifeBar.h"
class CollisionDetector;
namespace FightClub
{
class CSingleGameState :public State,public SingletonT<CSingleGameState>
	
{
	SINGLETON_DEFINE(CSingleGameState)   //友员宏定义CSingleGameState作为SingletonT的友员类
public:
	CSingleGameState(void);
	~CSingleGameState(void);
	
    void    createLight(void);
	void    createCamera(void);
	virtual void enter(void);                          //进入单机游戏状态
	virtual void pause(void);                         //单机版游戏暂停状态
	virtual void resume(void);                       //恢复单机游戏状态
	virtual void exit(void);                        //离开单机游戏状态

	virtual void update( float timeSinceLastFrame); //更新格斗过程的一切
	void         startRound();                              //每一局格斗前的初始化
	void         createScene(void);
	void         createUI(void);                 //创建游戏状态UI
	//键盘监听
	virtual bool keyPressed(const OIS::KeyEvent &e);
	virtual bool keyReleased(const OIS::KeyEvent &e);
	//鼠标监听
	virtual bool mouseMoved(const OIS::MouseEvent &e);
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);

	/*更改窗口大小之后调用, 负责本状态对窗口更改后的处理
			@width	更改窗口大小后的渲染窗口宽度
			@height	更改窗口大小后的渲染窗口高度*/
	virtual void changeSize(int width, int height);
protected:
	CLifeBar*            mLifeBar1;
	CLifeBar*            mLifeBar2;
	CPlayerMySelf*       mPlayer1;                          //玩家1
	CPlayerOther*        mPlayer2;                          //玩家2
	CObject*             mStaticScene;                      //静态场景
	ExtendedCamera*      mExCamera;                         //扩展相机

	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;
	Ogre::RenderWindow* mWindow;
	Ogre::Timer*        mTimer;

	//int   mCameraMode;                    //视角模式
	int   mRoundTime;                       //每局比赛时间
	int   mRound;                          //记录格斗局数
	bool  mPause;                          //是否处于暂停状态
	//ColiisionDetector mColiisionDetector;   //碰撞检测器
};
}