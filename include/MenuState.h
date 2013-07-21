#pragma once
/*游戏菜单状态类，继承自State,并继承单例模板，现实单例模式，
此状态全局唯一
*/
#ifndef _CMenuState_h_
#define _CMenuState_h_
#include"state.h"
#include"SingletonT.h"
#include"GUIManager.h"
#include"AudioManager.h"
#include"SingleGameState.h"
#include"StateManager.h"
namespace FightClub
{
class CMenuState :public State,public SingletonT<CMenuState>
	
{
	SINGLETON_DEFINE(CMenuState)   //友员宏定义CSingleGameState作为SingletonT的友员类
public:
	CMenuState(void);
	~CMenuState(void);
	
	void    createLight(void);
	void    createCamera(void);
	virtual void enter(void);                          //进入游戏菜单状态
	virtual void pause(void);                         //暂停
	virtual void resume(void);                       //恢复
	virtual void exit(void);                        //离开单机游戏菜单
	void subscribeGUIEvent(void);                   //定制(注册)cegui事件
	virtual void update( unsigned long timeSinceLastFrame); //更新窗口
	void createScene(void); 
	/*鼠标点击主菜单各选项的事件响应函数*/
	bool OnClikedSingle(const CEGUI::EventArgs& e);    
	bool OnClikedOnLine(const CEGUI::EventArgs& e);
	bool OnClikedOption(const CEGUI::EventArgs& e);
	bool OnClikedExit(const CEGUI::EventArgs& e);
	/*鼠标点击(确定退出)子菜单各选项的事件响应*/
	bool OnClikedYes(const CEGUI::EventArgs& e);
	bool OnClikedNo(const CEGUI::EventArgs& e);
	/*鼠标滑过主菜单各选项的事件响应函数*/
	bool MouseOver(const CEGUI::EventArgs& e);
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
	Ogre::Timer*        mTimer;

	
};
#endif //_CMenuState_h_
}