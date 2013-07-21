/*-----------------------------------------------------------------
所有在3d世界中可渲染对象的基类，静态的动态的渲染对象都由此衍生实现
------------------------------------------------------------------*/
#pragma once
#ifndef _CObject_h_
#define _CObject_h_
#include<Ogre.h>
namespace FightClub
{
class CObject
{
public:
	//对象的通用的一些操作

	CObject();
	/*
	@sceneMgr 创建此对象的场景管理器
	@name     此对象的自定义的命名
	@meshName 此对象所用的模型名 
	*/
	CObject(Ogre::SceneManager* sceneMgr,const std::string& name,const std::string& meshName);
	
	virtual ~CObject();
	//virtual void CreateObject(Ogre::SceneManager* mSceneMgr)=0;
	inline  std::string        getName(){return mName;}                      // 获取此对象的名称         
	inline  Ogre::SceneManager *getSceneManager(){return mSceneManager;}    // 创建此对象的场景管理器
	inline  Ogre::Entity       *getBodyEntity(){return mBodyEntity;}       // 获取主实体
	inline  Ogre::SceneNode    *getBodyNode(){return mBodyNode;}          // 此对象绑定的节点
	inline  bool               isCollision(){return mCollision;}         //是否需要碰撞检测
	/*设置坐标,缩放，方位，此处都用虚函数，便于子类的扩展*/
	virtual void setPosition(Ogre::Vector3& pos){mBodyNode->setPosition(pos);}
	virtual void setScale(Ogre::Vector3& scale){mBodyNode->setScale(scale);}
	virtual void setOrientation(Ogre::Quaternion& qut){mBodyNode->setOrientation(qut);}
	virtual Ogre::Vector3 getPosition() { return mBodyNode->_getDerivedPosition(); }
	virtual Ogre::Vector3 getScale() const { return mBodyNode->getScale(); }
	virtual Ogre::Quaternion getOrientation() const { return mBodyNode->getOrientation(); }

	//void DestroyObject();
protected:
	//对象共有的一些属性

	Ogre::SceneManager* mSceneManager;    //创建对象的场景管理器
	Ogre::Entity* mBodyEntity;          //主Entity
	Ogre::SceneNode* mBodyNode;   //主节点

	std::string mName;                  //对象名 
	std::string mMeshName;             //模型名
	std::string mNormalMat;           //正常的材质名
	std::string mDamageMat;          //遭受攻击的材质名

	bool        mCollision;        //是否检测碰撞
};
}
#endif //_CObject_h_