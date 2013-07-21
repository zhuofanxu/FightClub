/*
	-----------------------------------------------------------------------------
	������ģ��
	�̳�֮����Ҫ��ʵ�ֵ������ڵ��� SINGLETON_DEFINE(class) ��
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
		//��ȡʵ��ָ��
		static T* getSingletonPtr()
		{
			static T instance;
			return &instance;
		}
		//��ȡʵ��
		static T& getSingleton() { return *getSingletonPtr(); }

	protected:
		SingletonT(){}
		SingletonT(const SingletonT&);
		SingletonT& operator=(const SingletonT&);
	};

	// ��������Ԫ��궨��,ÿ���̳еĵ�������Ϊ��������ĵ���Ա�࣬�ﵽ���ʻ��ౣ��Ȩ��
	//�Ĺ��캯����Ŀ��
	#define SINGLETON_DEFINE(classname) friend class SingletonT<classname>;
}
