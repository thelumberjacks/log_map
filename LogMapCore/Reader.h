#ifndef __READER_H_
#define __READER_H_

#pragma once

#include "LogMap.h"
#include <string>
#include <vector>


namespace LogMapCore {

	class LOGMAPCORE_ImpExp Reader
	{
	public: ////////////////////////////////////////////////////////////////////////////////////////
	
		Reader();
		~Reader();

		void AddLog(std::wstring filename);
		void AddRegex(std::wstring regex);
		LogMap ScanAll();
	
	private: ////////////////////////////////////////////////////////////////////////////////////////

	#pragma warning (disable : 4251)
		std::vector<std::wstring> _filenameArray;
		std::vector<std::wstring> _regexArray;
	#pragma warning (default : 4251)

		void readFileFast(std::ifstream &file, void(*lineHandler)(char*str, int length, __int64 absPos));
		void loadFile(std::wstring& str);
		static void lineHandler(char*buf, int l, __int64 pos);
	};
}

#endif //__READER_H_