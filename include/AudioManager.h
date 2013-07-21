#pragma once
/*声音库Fmod的简单封装,游戏中所有的声音都都通过次音频管理器管理*/
#include "SingletonT.h"
#include "Common.h"
#include "fmod.h"
#include "fmod.hpp"
#include <vector>
#include <list>

namespace FightClub
{
	// 声音枚举
	enum AUDIO_TYPE
	{
		AUDIO_INIT = 0,
		AUDIO_BACKGROUND,	// 背景音乐
		AUDIO_BEGIN,			// 游戏开始
		AUDIO_WALK,          //行走声
		AUDIO_WIND,          //出拳声
		AUDIO_GAME,          //游戏中声音
		AUDIO_ROBOT,        //AI角色惨叫声
		
		AUDIO_MOUSE_CLICK,		// 鼠标点击
		AUDIO_MOUSE_OVER,		// 鼠标移动到控件之上
		AUDIO_SCORE_ADD,		// 添加分数
		AUDIO_TRUBA,			// 胜利
		AUDIO_SIZE
	};
	
	const static float FADE_VOLUME = 0.1f;

	class AudioManager:public IFrameListener,public SingletonT<AudioManager> 
	{
	                              
		SINGLETON_DEFINE(AudioManager)    //声明为SingletonT的友员类
		/** 音频元素简单封装 */
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
			
			// 播放当前音乐
			void play() { mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, &mChannel); }
			// 停止当前音乐
			void stop() { if (mChannel) mChannel->stop(); }
			/**
				设置音乐循环
				@loop 是否循环
			*/
			void setLoop(bool loop) 
			{ 
				setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
				mChannel->setLoopCount(loop ? -1 : 1); 
			}
			// 设置模式
			void setMode(FMOD_MODE mode){	mSound->setMode(mode); }
			// 设置音量 [0~1]
			void setVolume(float volume){ if (mChannel) mChannel->setVolume(volume); }
			// 设置音量的上限(0~1]
			void setFadeInVolume(float fadeInVolume) { mFadeInVolume = fadeInVolume; }
			// 获取当前音频的上限
			float getFadeInVolume() { return mFadeInVolume; }
			// 获取当前音频
			float getVolume() 
			{ 
				float volume = 0; 
				mChannel->getVolume(&volume); 
				return volume; 
			}
		};

	public:
		~AudioManager();
		
		// 释放资源
		void destroy();
		
		// 更新音频系统
		inline void update( float timeSinceLastFrame )
		{
			updateFade();
			mSystem->update(); 
		}

		/**
			播放指定音乐
			@audio	要播放的音乐类型
			@volume	播放音量
			@loop		是否循环
			@fadeIn	是否执行渐入效果
		*/
		static void play(AUDIO_TYPE audio, float volume = 0.75f, bool loop = false, bool fadeIn = true);
		
		/**
			停止指定音乐
			@audio		要播放的音乐类型
			@fadeOut	是否要执行渐出效果
		*/
		static void stop(AUDIO_TYPE audio, bool fadeOut = true);

	protected:
		AudioManager();
		
		// 更新音频渐变
		void updateFade();
		// 加载音频文件
		void loadAudios();

	protected:
		std::vector<AudioElem*>	mAudios;		// 音频集合
		FMOD::System					*mSystem;

		std::list<AudioElem*>		mFadeIns;		// 渐入队列
		std::list<AudioElem*>		mFadeOuts;	// 渐出队列
	};
	}