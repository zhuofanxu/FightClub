#pragma once
/*������Fmod�ļ򵥷�װ,��Ϸ�����е���������ͨ������Ƶ����������*/
#include "SingletonT.h"
#include "Common.h"
#include "fmod.h"
#include "fmod.hpp"
#include <vector>
#include <list>

namespace FightClub
{
	// ����ö��
	enum AUDIO_TYPE
	{
		AUDIO_INIT = 0,
		AUDIO_BACKGROUND,	// ��������
		AUDIO_BEGIN,			// ��Ϸ��ʼ
		AUDIO_WALK,          //������
		AUDIO_WIND,          //��ȭ��
		AUDIO_GAME,          //��Ϸ������
		AUDIO_ROBOT,        //AI��ɫ�ҽ���
		
		AUDIO_MOUSE_CLICK,		// �����
		AUDIO_MOUSE_OVER,		// ����ƶ����ؼ�֮��
		AUDIO_SCORE_ADD,		// ��ӷ���
		AUDIO_TRUBA,			// ʤ��
		AUDIO_SIZE
	};
	
	const static float FADE_VOLUME = 0.1f;

	class AudioManager:public IFrameListener,public SingletonT<AudioManager> 
	{
	                              
		SINGLETON_DEFINE(AudioManager)    //����ΪSingletonT����Ա��
		/** ��ƵԪ�ؼ򵥷�װ */
		class AudioElem
		{
		public:
			FMOD::Sound		*mSound;
			FMOD::Channel	*mChannel;
			FMOD::System		*mSystem;
			float						mFadeInVolume;

			AudioElem(FMOD::System *system, const std::string &musicName) 
				: mSystem(system), mChannel(0), mFadeInVolume(1)
			{
				system->createSound(musicName.c_str(), FMOD_HARDWARE, 0, &mSound);
			}

			~AudioElem() { mSound->release(); }
			
			// ���ŵ�ǰ����
			void play() { mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, &mChannel); }
			// ֹͣ��ǰ����
			void stop() { if (mChannel) mChannel->stop(); }
			/**
				��������ѭ��
				@loop �Ƿ�ѭ��
			*/
			void setLoop(bool loop) 
			{ 
				setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
				mChannel->setLoopCount(loop ? -1 : 1); 
			}
			// ����ģʽ
			void setMode(FMOD_MODE mode){	mSound->setMode(mode); }
			// �������� [0~1]
			void setVolume(float volume){ if (mChannel) mChannel->setVolume(volume); }
			// ��������������(0~1]
			void setFadeInVolume(float fadeInVolume) { mFadeInVolume = fadeInVolume; }
			// ��ȡ��ǰ��Ƶ������
			float getFadeInVolume() { return mFadeInVolume; }
			// ��ȡ��ǰ��Ƶ
			float getVolume() 
			{ 
				float volume = 0; 
				mChannel->getVolume(&volume); 
				return volume; 
			}
		};

	public:
		~AudioManager();
		
		// �ͷ���Դ
		void destroy();
		
		// ������Ƶϵͳ
		inline void update( float timeSinceLastFrame )
		{
			updateFade();
			mSystem->update(); 
		}

		/**
			����ָ������
			@audio	Ҫ���ŵ���������
			@volume	��������
			@loop		�Ƿ�ѭ��
			@fadeIn	�Ƿ�ִ�н���Ч��
		*/
		static void play(AUDIO_TYPE audio, float volume = 0.75f, bool loop = false, bool fadeIn = true);
		
		/**
			ָֹͣ������
			@audio		Ҫ���ŵ���������
			@fadeOut	�Ƿ�Ҫִ�н���Ч��
		*/
		static void stop(AUDIO_TYPE audio, bool fadeOut = true);

	protected:
		AudioManager();
		
		// ������Ƶ����
		void updateFade();
		// ������Ƶ�ļ�
		void loadAudios();

	protected:
		std::vector<AudioElem*>	mAudios;		// ��Ƶ����
		FMOD::System					*mSystem;

		std::list<AudioElem*>		mFadeIns;		// �������
		std::list<AudioElem*>		mFadeOuts;	// ��������
	};
	}