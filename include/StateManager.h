/*
	-----------------------------------------------------------------------------
	״̬������,���ڶ���Ϸ�����е�״̬���й���͸���.
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

		// �����豸
		void destroy();

		// ����״̬,��ջ��״̬����,����״̬ѹջ
		void changeState( State *newState );
		// ��ջ״̬,�Ƚ�ջ��״̬pause()��ѹջ
		void pushState( State *newState );
		// ����״̬
		void popState( void );

		// ��ȡ�״̬
		inline State* peekTop() 
		{ 
			assert(!mStates.empty()); 
			return mStates.back(); 
		}

		// ��ǰ��ջ״̬��
		inline int size() const { return (int)mStates.size(); }
		inline bool empty() const { return mStates.empty(); }

	public:
		// ���԰���State
		inline void update( float timeSinceLastFrame ) { peekTop()->update(timeSinceLastFrame); }
		// ��Ⱦ�����״̬
		inline void updateAfterRender( float timeSinceLastFrame) { peekTop()->updateAfterRender(timeSinceLastFrame); }

		inline bool keyPressed( const OIS::KeyEvent &e ){ return peekTop()->keyPressed(e); }
		inline bool keyReleased( const OIS::KeyEvent &e ){ return peekTop()->keyReleased(e); }

		inline bool mouseMoved(const OIS::MouseEvent &e){ return peekTop()->mouseMoved(e); }
		inline bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {return peekTop()->mousePressed(e, id); 	}
		inline bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return peekTop()->mouseReleased(e, id);}

		// ���Ĵ��ڴ�С֮�����, ����״̬�Դ��ڸ��ĺ�Ĵ���
		inline void changeSize(int width, int height) { peekTop()->changeSize(width, height); }

		virtual void enter( void ){}
		// �˳�״̬
		virtual void exit( void ) {}

		State* getCurrentState();



	protected:
		StateManager(){}

		std::vector<State*> mStates;
	};
}

#endif