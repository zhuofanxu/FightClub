#pragma once
/*��Ogre�Դ���Camera������չ���Դﵽ������Ϸ�е����˳����������Ŀ��ڵ��Ŀ��*/
#ifndef _ExtendedCamera_h_
#define _ExtendedCamera_h_
#include<Ogre.h>
namespace FightClub
{
class ExtendedCamera
{
protected:

    Ogre::SceneNode *mTargetNode; // ׷�ٵ�Ŀ��ڵ�
    Ogre::SceneNode *mCameraNode; // ���������ڵ�
    Ogre::Camera *mCamera;        // Ogre �Դ�camera
    int   mCameraMode;             //�ӽ�ģʽ
    Ogre::SceneManager *mSceneMgr;
    Ogre::String mName;
    bool mOwnCamera; //ogre �Դ�camera�Ƿ��ڴ������Դ���
	Ogre::Real mTightness; // ȷ��camera���˶���1�����˶���0���˶�
public:
	ExtendedCamera (const Ogre::String& name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera = 0) 
	{
             mName = name;                              //������Ա��ʼ��
             mSceneMgr = sceneMgr;
 
             // ��������ڵ��Լ�Ŀ��ڵ�
             mCameraNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName);
             mTargetNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName + "_target");
             mCameraNode->setAutoTracking (true, mTargetNode); //�Զ���������
             mCameraNode->setFixedYawAxis (true); 
 
             // ���Camera������Ϊ�������� �ʹ���ogre camera
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
                 mCamera->setPosition(0.0,0.0,0.0);          //��camera��cameranodeλ��һ��
                 mOwnCamera = false;
             }
      
             mCameraNode->attachObject (mCamera);             //�ҽ�camera��cameraNode
 
           
             mTightness = 0.01f;                             // Ĭ��ֵΪ0.01
			 mCameraMode=0;                                  //Ĭ��Ϊ0
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
             // �����ƶ�
             Ogre::Vector3 displacement;
 
             displacement = (cameraPosition - mCameraNode->getPosition ()) * mTightness;
             mCameraNode->translate (displacement);
 
             displacement = (targetPosition - mTargetNode->getPosition ()) * mTightness;
             mTargetNode->translate (displacement);
         }
 };
}
#endif //_ExtendedCamera_h_
