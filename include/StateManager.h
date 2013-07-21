/*
	-----------------------------------------------------------------------------
	状态管理器,用于对游戏中所有的状态进行管理和更新.
	-----------------------------------------------------------------------------
*/

#ifndef __STATESYSTEM_H__
#define __STATESYSTEM_H__

#include <vector>
#include <assert.h>

#include "State.h"
#include "SingletonT.h"

namespace FightClub
{
	
	class StateManager : public State, public SingletonT<StateManager>
	{
		SINGLETON_DEFINE(StateManager)

	public:
		virtual ~StateManager();

		// 销毁设备
		void destroy();

		// 更换状态,将栈顶状态弹出,将此状态压栈
		void changeState( State *newState );
		// 入栈状态,先将栈顶状态pause()后压栈
		void pushState( State *newState );
		// 弹出状态
		void popState( void );

		// 获取最顶状态
		inline State* peekTop() 
		{ 
			assert(!mStates.empty()); 
			return mStates.back(); 
		}

		// 当前入栈状态数
		inline int size() const { return (int)mStates.size(); }
		inline bool empty() const { return mStates.empty(); }

	public:
		// 可自包含State
		inline void update( float timeSinceLastFrame ) { peekTop()->update(timeSinceLastFrame); }
		// 渲染后更新状态
		inline void updateAfterRender( float timeSinceLastFrame) { peekTop()->updateAfterRender(timeSinceLastFrame); }

		inline bool keyPressed( const OIS::KeyEvent &e ){ return peekTop()->keyPressed(e); }
		inline bool keyReleased( const OIS::KeyEvent &e ){ return peekTop()->keyReleased(e); }

		inline bool mouseMoved(const OIS::MouseEvent &e){ return peekTop()->mouseMoved(e); }
		inline bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {return peekTop()->mousePressed(e, id); 	}
		inline bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return peekTop()->mouseReleased(e, id);}

		// 更改窗口大小之后调用, 负责本状态对窗口更改后的处理
		inline void changeSize(int width, int height) { peekTop()->changeSize(width, height); }

		virtual void enter( void ){}
		// 退出状态
		virtual void exit( void ) {}

		State* getCurrentState();



	protected:
		StateManager(){}

		std::vector<State*> mStates;
	};
}

#endif