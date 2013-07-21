#pragma once
/*将Ogre自带的Camera进行扩展，以达到格斗类游戏中第三人称摄像机跟踪目标节点的目的*/
#ifndef _ExtendedCamera_h_
#define _ExtendedCamera_h_
#include<Ogre.h>
namespace FightClub
{
class ExtendedCamera
{
protected:

    Ogre::SceneNode *mTargetNode; // 追踪的目标节点
    Ogre::SceneNode *mCameraNode; // 摄像机自身节点
    Ogre::Camera *mCamera;        // Ogre 自带camera
    int   mCameraMode;             //视角模式
    Ogre::SceneManager *mSceneMgr;
    Ogre::String mName;
    bool mOwnCamera; //ogre 自带camera是否在此类内以创建
	Ogre::Real mTightness; // 确定camera的运动，1紧贴运动，0不运动
public:
	ExtendedCamera (const Ogre::String& name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera = 0) 
	{
             mName = name;                              //基本成员初始化
             mSceneMgr = sceneMgr;
 
             // 创建相机节点以及目标节点
             mCameraNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName);
             mTargetNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName + "_target");
             mCameraNode->setAutoTracking (true, mTargetNode); //自动跟踪启动
             mCameraNode->setFixedYawAxis (true); 
 
             // 如果Camera不是作为参数传递 就创建ogre camera
             if (camera == 0) 
			 {
				 mCamera=mSceneMgr->createCamera("OgreCamera");
                // mCamera->setAspectRatio((float)mViewport->getActualWidth() / (float)mViewport->getActualHeight());
		        // mCamera->setNearClipDistance(0.1);
                 mOwnCamera = true;
             }
             else 
			 {
                 mCamera = camera;           
                 mCamera->setPosition(0.0,0.0,0.0);          //让camera与cameranode位置一致
                 mOwnCamera = false;
             }
      
             mCameraNode->attachObject (mCamera);             //挂接camera到cameraNode
 
           
             mTightness = 0.01f;                             // 默认值为0.01
			 mCameraMode=0;                                  //默认为0
         }
         ~ExtendedCamera () 
		 {
            mCameraNode->detachAllObjects ();
          
             mSceneMgr->destroySceneNode (mName);
             mSceneMgr->destroySceneNode (mName + "_target");
         }

	   Ogre::Camera* getCamera(){return mCamera;}
	   int getCameraMode(){return mCameraMode;}
       void setCameraMode(int mode){mCameraMode=mode;}
	   void setTightness (Ogre::Real tightness) 
	     {
			 mTightness = tightness;
         }
 
         Ogre::Real getTightness () 
		 {
             return mTightness;
         }
 
         Ogre::Vector3 getCameraPosition () 
		 {
             return mCameraNode->getPosition ();
         }
 
		 void rest(Ogre::Vector3 cameraInitPosition, Ogre::Vector3 targetInitPosition)
		 {
			 mCameraNode->setPosition (cameraInitPosition);
             mTargetNode->setPosition (targetInitPosition);
		 }
         void instantUpdate (Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition) 
		 {
             mCameraNode->setPosition (cameraPosition);
             mTargetNode->setPosition (targetPosition);
         }
 
         void update (Ogre::Real elapsedTime,Ogre::Vector3 cameraPosition,Ogre::Vector3 targetPosition)
		 {
             // 处理移动
             Ogre::Vector3 displacement;
 
             displacement = (cameraPosition - mCameraNode->getPosition ()) * mTightness;
             mCameraNode->translate (displacement);
 
             displacement = (targetPosition - mTargetNode->getPosition ()) * mTightness;
             mTargetNode->translate (displacement);
         }
 };
}
#endif //_ExtendedCamera_h_
