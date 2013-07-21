#pragma once
/*游戏暂停状态类，继承自State,并继承单例模板，现实单例模式，
此状态全局唯一
*/
#include "state.h"
#include "SingletonT.h"
#include "GUIManager.h"
#include "StateManager.h"
#include "MenuState.h"
namespace FightClub
{
class CPauseState :public State,public SingletonT<CPauseState>
	
{
	SINGLETON_DEFINE(CPauseState)   //友员宏定义CSingleGameState作为SingletonT的友员类
public:
	CPauseState(void);
	~CPauseState(void);
	
	virtual void enter(void);                          //进入单机游戏状态
	virtual void pause(void);                         //单机版游戏暂停状态
	virtual void resume(void);                       //恢复单机游戏状态
	virtual void exit(void);                        //离开单机游戏状态
	void subscribeGUIEvent(void);                   //定制(注册)cegui事件
	bool OnClikedContinue(const CEGUI::EventArgs& e);   //继续游戏 
	bool OnClikedToMenu(const CEGUI::EventArgs& e);    //返回主菜单
	bool MouseOver(const CEGUI::EventArgs& e);

	virtual void update(float timeSinceLastFrame); //更新
	void         createScene(void);
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

	

	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;
	Ogre::RenderWindow* mWindow;

	
	bool  mQuit;                          //是否要退出暂停状态
};
}