#pragma once
/*������Ϸ״̬�࣬�̳���State,���̳е���ģ�壬��ʵ����ģʽ��
��״̬ȫ��Ψһ
*/
#include"state.h"
#include"PauseState.h"
#include"SingletonT.h"
#include"CPlayerMySelf.h"
#include"CPlayerOther.h"
#include"AudioManager.h"
#include"ExtendedCamera.h"
#include"LifeBar.h"
class CollisionDetector;
namespace FightClub
{
class CSingleGameState :public State,public SingletonT<CSingleGameState>
	
{
	SINGLETON_DEFINE(CSingleGameState)   //��Ա�궨��CSingleGameState��ΪSingletonT����Ա��
public:
	CSingleGameState(void);
	~CSingleGameState(void);
	
    void    createLight(void);
	void    createCamera(void);
	virtual void enter(void);                          //���뵥����Ϸ״̬
	virtual void pause(void);                         //��������Ϸ��ͣ״̬
	virtual void resume(void);                       //�ָ�������Ϸ״̬
	virtual void exit(void);                        //�뿪������Ϸ״̬

	virtual void update( float timeSinceLastFrame); //���¸񶷹��̵�һ��
	void         startRound();                              //ÿһ�ָ�ǰ�ĳ�ʼ��
	void         createScene(void);
	void         createUI(void);                 //������Ϸ״̬UI
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
	CLifeBar*            mLifeBar1;
	CLifeBar*            mLifeBar2;
	CPlayerMySelf*       mPlayer1;                          //���1
	CPlayerOther*        mPlayer2;                          //���2
	CObject*             mStaticScene;                      //��̬����
	ExtendedCamera*      mExCamera;                         //��չ���

	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;
	Ogre::RenderWindow* mWindow;
	Ogre::Timer*        mTimer;

	//int   mCameraMode;                    //�ӽ�ģʽ
	int   mRoundTime;                       //ÿ�ֱ���ʱ��
	int   mRound;                          //��¼�񶷾���
	bool  mPause;                          //�Ƿ�����ͣ״̬
	//ColiisionDetector mColiisionDetector;   //��ײ�����
};
}