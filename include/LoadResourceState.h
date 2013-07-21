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
	/*���Ĵ��ڴ�С֮�����, ����״̬�Դ��ڸ��ĺ�Ĵ���
			@width	���Ĵ��ڴ�С�����Ⱦ���ڿ��
			@height	���Ĵ��ڴ�С�����Ⱦ���ڸ߶�*/
	virtual void changeSize(int width, int height){/*��ʱɶҲ����*/}
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