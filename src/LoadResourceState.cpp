#pragma once
#include "LoadResourceState.h"
#include "FightClubApp.h"
namespace FightClub
{
	void  CLoadResourceState::createLight(void)
	{
		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
		Ogre::Light *light = mSceneMgr->createLight("MainLight");
		light->setPosition(Ogre::Vector3(100, 100, 100));
	}
	void CLoadResourceState::createCamera(void)
	{
		mWindow=FightClubApp::getSingletonPtr()->getRenderWindow();
		mSceneMgr->destroyAllCameras();
		mWindow->removeAllViewports();
		mCamera = mSceneMgr->createCamera("LoadCamera");
		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(Ogre::ColourValue(0.3f, 0.3f, 0.4f));
		//mSceneMgr->setFog(Ogre::FOG_LINEAR, ColourValue(1.0f, 1.0f, 0.8f), 0, 15, 100);
		mCamera->setAspectRatio((float)mViewport->getActualWidth() / (float)mViewport->getActualHeight());
		mCamera->setNearClipDistance(0.1);
	}
	void CLoadResourceState::enter(void)
	{
		FightClubApp::getSingletonPtr()->mLog->logMessage("正在进入资源载入......");
		if(!mLoadBar)
			mLoadBar=new ExampleLoadingBar();
		mRoot=FightClubApp::getSingletonPtr()->mRoot;
		//mSceneMgr=AppFrameWork::getSingletonPtr()->
		mSceneMgr = mRoot->getSceneManager("FightClubGame-Aide");
		createLight();
		createCamera();

       // mViewport->setBackgroundColour(ColourValue(0.0, 0.0, 0.0));
        mLoadBar->start(mWindow, 2, 2, 1.0);

		//关闭所有除界面层的渲染外的其他渲染
        mSceneMgr->clearSpecialCaseRenderQueues();
        mSceneMgr->addSpecialCaseRenderQueue(RENDER_QUEUE_OVERLAY);
        mSceneMgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_INCLUDE);

		ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
		
		 // 返回完整渲染
        mSceneMgr->clearSpecialCaseRenderQueues();
        mSceneMgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_EXCLUDE);
		
		mIsLoadEnd=true;
      }

	void CLoadResourceState::exit(void)
	{
		mLoadBar->finish();
		/*退出该状态时清理创建相机 视口 灯光*/
		mSceneMgr->destroyAllCameras();
		mWindow->removeAllViewports();
		mSceneMgr->destroyAllLights();
	}
	CLoadResourceState::CLoadResourceState()
	{

          mLoadBar=0;
	      mRoot=0;
	      mSceneMgr=0;
	      mCamera=0;
          mViewport=0;
	      mWindow=0;
		  mIsLoadEnd=false;
	}

	bool CLoadResourceState::keyPressed(const OIS::KeyEvent& e)
	{
		if(e.key==OIS::KC_LWIN)
		::ShowWindow(GetActiveWindow(),SW_MINIMIZE);                //左win键，程序窗口最小化切换到桌面
		return true;
	}
	CLoadResourceState::~CLoadResourceState()
	{
		if(mLoadBar)
			delete mLoadBar;
	}
	
}