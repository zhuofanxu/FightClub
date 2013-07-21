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

#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Util.h"
namespace FightClub
{
	/**
	配置文件

	格式
	# comment
	[section1]
	key=value

	[section2]
	key1=value
	key2=value
	key3=value
	*/
	class Config
	{
		typedef std::map<std::string, std::string> StringMap;
		typedef std::map<std::string, StringMap> StringStringMap;

		typedef StringMap::iterator SItr;
		typedef StringStringMap::iterator SSItr;

	public:
		Config(const std::string &filename);

		~Config();

		// section是否存在
		bool sectionExsit(const std::string &section);

		// 指定section的key值是否存在
		bool keyExsit(const std::string &section, const std::string &key);

		// 获取指定的Secion的key值--字符串形式
		std::string getString(const std::string &section, const std::string &key);
		// 获取指定的Secion的key值--浮点型式
		float getFloat(const std::string &section, const std::string &key);
		// 获取指定的Secion的key值--Bool形式
		bool getBoolean(const std::string &section, const std::string &key);

		// 指定section所有的key键
		std::vector<std::string> getKeyIterator(const std::string &section);

		bool hasError();
	private:
		StringStringMap mParams;

		bool						mError;
	};
}