#pragma once
#include "state.h"
#include "ExampleLoadingBar.h"
#include"SingletonT.h"
namespace FightClub
{
class CLoadResourceState :public State,public SingletonT<CLoadResourceState>
	
{
	SINGLETON_DEFINE(CLoadResourceState)
public:
	CLoadResourceState(void);
	~CLoadResourceState(void);
	bool getIsLoadEnd(void){return mIsLoadEnd;}
	void    createLight(void);
	void    createCamera(void);
	virtual void enter(void);                         
	virtual void pause(void){}                      
	virtual void resume(void){}                    
	virtual void exit(void);    
	virtual bool keyPressed(const OIS::KeyEvent &e);
	/*更改窗口大小之后调用, 负责本状态对窗口更改后的处理
			@width	更改窗口大小后的渲染窗口宽度
			@height	更改窗口大小后的渲染窗口高度*/
	virtual void changeSize(int width, int height){/*暂时啥也不做*/}
protected:
	bool mIsLoadEnd;
	ExampleLoadingBar* mLoadBar;
	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;
	Ogre::RenderWindow* mWindow;
};
}