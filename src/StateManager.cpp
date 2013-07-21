/*
	-----------------------------------------------------------------------------
	
	-----------------------------------------------------------------------------
*/

#include "StateManager.h"
//#include "Util.h"

namespace FightClub
{


	StateManager::~StateManager()
	{

	}



	void StateManager::destroy()
	{
		/**
		ע��: ����vector��˵���ݵĸ��Ļᵼ�µ�������Ч, �����������
		*/
		while (!empty())
			popState();

		mStates.clear();
	}



	void StateManager::changeState( State *newState )
	{
		// ����ջ��״̬
		if (!mStates.empty())
		{
			mStates.back()->exit();    //ջ���˳�
			mStates.pop_back();       //�Ƴ�ջ��Ԫ��   
		}

		mStates.push_back(newState);  //ѹ���µ�Ԫ��(״̬)
		newState->enter();           //������״̬
	}



	void StateManager::pushState( State *newState )
	{
		// ��ջ��״̬��ͣ
		if (!mStates.empty())           
			mStates.back()->pause();       //��ͣ��ǰ״̬

		mStates.push_back(newState);
		newState->enter();
	}



	void StateManager::popState( void )
	{
		// ����ջ��״̬
		if (!mStates.empty())
		{
			mStates.back()->exit();
			mStates.pop_back();
		}

		// �ָ���һ��״̬
		if (!mStates.empty())
			mStates.back()->resume();
	}

	State* StateManager::getCurrentState()
	{
		if (!mStates.empty())
		{
			return mStates.back();;
		}
		else
		{
			return NULL;
		}


	}



}