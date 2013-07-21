/*
	-----------------------------------------------------------------------------
	单例类模板
	继承之后需要在实现单例类内调用 SINGLETON_DEFINE(class) 宏
	-----------------------------------------------------------------------------
*/

#pragma once

namespace FightClub
{
	
	template<typename T>
	class SingletonT
	{
	public:
		virtual ~SingletonT() { }
		//获取实例指针
		static T* getSingletonPtr()
		{
			static T instance;
			return &instance;
		}
		//获取实例
		static T& getSingleton() { return *getSingletonPtr(); }

	protected:
		SingletonT(){}
		SingletonT(const SingletonT&);
		SingletonT& operator=(const SingletonT&);
	};

	// 单例类友元类宏定义,每个继承的单例类作为单例基类的的友员类，达到访问基类保护权限
	//的构造函数的目的
	#define SINGLETON_DEFINE(classname) friend class SingletonT<classname>;
}
