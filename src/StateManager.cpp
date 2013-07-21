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
		注意: 对于vector来说内容的更改会导致迭代器无效, 可能引起崩溃
		*/
		while (!empty())
			popState();

		mStates.clear();
	}



	void StateManager::changeState( State *newState )
	{
		// 弹出栈顶状态
		if (!mStates.empty())
		{
			mStates.back()->exit();    //栈顶退出
			mStates.pop_back();       //移除栈顶元素   
		}

		mStates.push_back(newState);  //压人新的元素(状态)
		newState->enter();           //进入新状态
	}



	void StateManager::pushState( State *newState )
	{
		// 将栈顶状态暂停
		if (!mStates.empty())           
			mStates.back()->pause();       //暂停当前状态

		mStates.push_back(newState);
		newState->enter();
	}



	void StateManager::popState( void )
	{
		// 弹出栈顶状态
		if (!mStates.empty())
		{
			mStates.back()->exit();
			mStates.pop_back();
		}

		// 恢复上一个状态
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