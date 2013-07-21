#pragma once
#include "state.h"
namespace FightClub
{
class COlGameState :
	public State
{
public:

	void    createLight(void);
	void    createCamera(void);
	COlGameState(void);
	~COlGameState(void);
	virtual void enter(void);                          //����������Ϸ״̬
	virtual void pause(void);                         //�������Ϸ��ͣ״̬
	virtual void resume(void);                       //�ָ�������Ϸ״̬
	virtual void exit(void);                        //�뿪������Ϸ״̬

	/*���Ĵ��ڴ�С֮�����, ����״̬�Դ��ڸ��ĺ�Ĵ���
			@width	���Ĵ��ڴ�С�����Ⱦ���ڿ��
			@height	���Ĵ��ڴ�С�����Ⱦ���ڸ߶�*/
	virtual void changeSize(int width, int height);
};
}
