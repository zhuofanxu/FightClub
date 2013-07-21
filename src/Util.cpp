/*
	-----------------------------------------------------------------------------
	This source file is part of TankWar
	This is a 3D tank war game, use ogre for render, support singleplayer and multiplayer.
	For the latest info, see http://flyingpig.isgreat.org or https://sourceforge.net/projects/tankwar3d

	Copyright (c) 2000-2010

	Usage of this program is free for non-commercial use and licensed under the
	the terms of the MIT License.

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
	-----------------------------------------------------------------------------
*/

#include "Util.h"


namespace FightClub
{
	// �հ��ַ�
	const static std::string BLOCK = " \t";



	std::string Util::format(int num, int digit)
	{
		std::string str = toString(num);
		if (digit > (int)str.length())
		{
			int length = digit - (int)str.length();
			for (int i = 0; i < length; i++)
				str = "0" + str;
		}

		return str;
	}



	std::string Util::trim(const std::string &line)
	{
		std::string result;
		std::size_t index = line.find_first_not_of(BLOCK);
		if (index != std::string::npos)
			result = line.substr(index);

		index = result.find_last_not_of(BLOCK);
		if (index != std::string::npos && index != result.size() - 1)
			result = result.substr(0, index + 1);

		return result;
	}



	// �ж��ַ����Ƿ����, ���Դ�Сд
	bool Util::equal(const std::string &left, const std::string &right)
	{
		if (left.size() != right.size())
			return false;

		for (unsigned int i = 0; i < left.size(); i++)
			if (tolower(left[i]) != tolower(right[i]))
				return false;

		return true;
	}



	void Util::loadResouse(const std::string &path, ResType type, const std::string &groupName, bool load, bool recursive)
	{
		std::string ty = (type == ZIP_TYPE ? "Zip" : "FileSystem");

		//�ֶ�������Դ
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path,ty,groupName,recursive);
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(groupName);

		if(load)	// ��Ҫֱ��ȫ������
			Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(groupName);
	}



	// ж����Դ
	void Util::unloadResouse(const std::string &GroupName)
	{
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(GroupName);
	}



	// ����.scene�ļ������ɶ�Ӧ����,����ǰ��Ҫ��֤ʹ��loadResouse()����.scene�����Դ
	// sceneName .scene�ļ�����, groupName��Դ��, pAttachNode = NULLΪ��root SceneNode������
	
}