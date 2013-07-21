/*
	-----------------------------------------------------------------------------
	��Ϸ״̬����
	������Ϸ״̬��˵�״̬,��Ϸ״̬�Ⱦ���Ҫ�ɴ˼̳в�ʵ�־������.
	-----------------------------------------------------------------------------
*/

#pragma once

#include <Ogre.h>
#include "Common.h"

namespace FightClub
{
	
		
	
	class State : public IFrameListener, public IKeyMouseListener
	{
	public:
		virtual ~State(){}

		// ����״̬
		virtual void enter( void )  = 0;
		// �˳�״̬
		virtual void exit( void )   = 0;

		// ��ͣ״̬
		virtual void pause( void ) {}
		// �ظ�״̬
		virtual void resume( void ) {}
		
		/**
			���Ĵ��ڴ�С֮�����, ����״̬�Դ��ڸ��ĺ�Ĵ���
			@width	���Ĵ��ڴ�С�����Ⱦ���ڿ��
			@height	���Ĵ��ڴ�С�����Ⱦ���ڸ߶�
		*/
		virtual void changeSize(int width, int height) = 0;

		/** 
			����״̬,��ջ��״̬����,����״̬ѹջ
			@newState ��״̬
		*/
		void changeState( State *newState );

		/**
			��ջ״̬,�Ƚ�ջ��״̬pause()��ѹջ
			@newState	��״̬
		*/
		void pushState( State *newState );

		// ����״̬
		void popState( void );

	protected:
		State(){}
		State(const State&);
		State& operator=(const State&);
	};
}