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

#include "Config.h"

namespace FightClub
{


	Config::Config(const std::string &filename) : mError(false)
	{
		std::ifstream in;
		in.open(filename.c_str());

		if (in.good())
		{
			std::string line;
			std::string section = "";
			StringMap setting;

			while (in.good())
			{
				std::getline(in, line);
				line = Util::trim(line);

				// 删除空行和注释行
				if (line.size() == 0 || line[0] == '#')
					continue;

				if (line[0] == '[')	// 新section
				{
					mParams[section] = setting;
					section = line.substr(1, line.size() - 2);
					setting.clear();
				}
				else
				{
					std::size_t index = line.find('=');
					std::string key = line.substr(0, index);
					std::string value = line.substr(index + 1);
					setting[key] = value;
				}
			}

			mParams.erase("");
			mParams[section] = setting;

			in.close();
		}
		else
			mError = true;
	}



	Config::~Config()
	{
		mParams.clear();
	}



	bool Config::sectionExsit(const std::string &section)
	{
		return mParams.count(section) > 0;
	}



	bool Config::keyExsit(const std::string &secion, const std::string &key)
	{
		if (!sectionExsit(secion))
			return false;

		return mParams[secion].count(key) > 0;
	}



	std::string Config::getString(const std::string &secion, const std::string &key)
	{
		return (mParams[secion])[key];
	}



	float Config::getFloat(const std::string &secion, const std::string &key)
	{
		return atof(getString(secion, key).c_str());
	}



	bool Config::getBoolean(const std::string &secion, const std::string &key)
	{
		std::string result = getString(secion, key);

		if (Util::equal(result, "True"))
			return true;
		else
			return false;
	}



	bool Config::hasError()
	{
		return mError;
	}



	std::vector<std::string> Config::getKeyIterator(const std::string &section)
	{
		std::vector<std::string> keys;

		for (SItr itr = mParams[section].begin(); itr != mParams[section].end(); ++itr)
			keys.push_back(itr->first);

		return keys;
	}
}