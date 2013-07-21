#pragma once
/*��Ϸ�˵�״̬�࣬�̳���State,���̳е���ģ�壬��ʵ����ģʽ��
��״̬ȫ��Ψһ
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
	SINGLETON_DEFINE(CMenuState)   //��Ա�궨��CSingleGameState��ΪSingletonT����Ա��
public:
	CMenuState(void);
	~CMenuState(void);
	
	void    createLight(void);
	void    createCamera(void);
	virtual void enter(void);                          //������Ϸ�˵�״̬
	virtual void pause(void);                         //��ͣ
	virtual void resume(void);                       //�ָ�
	virtual void exit(void);                        //�뿪������Ϸ�˵�
	void subscribeGUIEvent(void);                   //����(ע��)cegui�¼�
	virtual void update( unsigned long timeSinceLastFrame); //���´���
	void createScene(void); 
	/*��������˵���ѡ����¼���Ӧ����*/
	bool OnClikedSingle(const CEGUI::EventArgs& e);    
	bool OnClikedOnLine(const CEGUI::EventArgs& e);
	bool OnClikedOption(const CEGUI::EventArgs& e);
	bool OnClikedExit(const CEGUI::EventArgs& e);
	/*�����(ȷ���˳�)�Ӳ˵���ѡ����¼���Ӧ*/
	bool OnClikedYes(const CEGUI::EventArgs& e);
	bool OnClikedNo(const CEGUI::EventArgs& e);
	/*��껬�����˵���ѡ����¼���Ӧ����*/
	bool MouseOver(const CEGUI::EventArgs& e);
	//���̼���
	virtual bool keyPressed(const OIS::KeyEvent &e);
	virtual bool keyReleased(const OIS::KeyEvent &e);
	//������
	virtual bool mouseMoved(const OIS::MouseEvent &e);
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);

	/*���Ĵ��ڴ�С֮�����, ����״̬�Դ��ڸ��ĺ�Ĵ���
			@width	���Ĵ��ڴ�С�����Ⱦ���ڿ��
			@height	���Ĵ��ڴ�С�����Ⱦ���ڸ߶�*/
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