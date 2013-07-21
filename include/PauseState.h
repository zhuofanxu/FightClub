#pragma once
/*��Ϸ��ͣ״̬�࣬�̳���State,���̳е���ģ�壬��ʵ����ģʽ��
��״̬ȫ��Ψһ
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
	SINGLETON_DEFINE(CPauseState)   //��Ա�궨��CSingleGameState��ΪSingletonT����Ա��
public:
	CPauseState(void);
	~CPauseState(void);
	
	virtual void enter(void);                          //���뵥����Ϸ״̬
	virtual void pause(void);                         //��������Ϸ��ͣ״̬
	virtual void resume(void);                       //�ָ�������Ϸ״̬
	virtual void exit(void);                        //�뿪������Ϸ״̬
	void subscribeGUIEvent(void);                   //����(ע��)cegui�¼�
	bool OnClikedContinue(const CEGUI::EventArgs& e);   //������Ϸ 
	bool OnClikedToMenu(const CEGUI::EventArgs& e);    //�������˵�
	bool MouseOver(const CEGUI::EventArgs& e);

	virtual void update(float timeSinceLastFrame); //����
	void         createScene(void);
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

	
	bool  mQuit;                          //�Ƿ�Ҫ�˳���ͣ״̬
};
}