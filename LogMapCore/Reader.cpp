#include "stdafx.h"
#include "Reader.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace LogMapCore {

	Reader::Reader()
	{
	}


	Reader::~Reader()
	{
	}


	void Reader::AddLog(std::wstring filename)
	{
		_filenameArray.push_back(filename);
	}


	void Reader::AddRegex(std::wstring regex)
	{
		_regexArray.push_back(regex);
	}

	void Reader::readFileFast(ifstream &file, void(*lineHandler)(char*str, int length, __int64 absPos)){
		int BUF_SIZE = 40000;

		file.seekg(0, ios::end);
		ifstream::pos_type p = file.tellg();
#ifdef WIN32
		__int64 fileSize = *(__int64*)(((char*)&p)+8);
#else
		__int64 fileSize = p;
#endif
		file.seekg(0, ios::beg);
		BUF_SIZE = (int) min(BUF_SIZE, fileSize);
		char* buf = new char[BUF_SIZE];

		int bufLength = BUF_SIZE;
		file.read(buf, bufLength);

		int strEnd = -1;
		int strStart;
		__int64 bufPosInFile = 0;
		while (bufLength > 0) {
			int i = strEnd + 1;
			strStart = strEnd;
			strEnd = -1;
			for (; i < bufLength && i + bufPosInFile < fileSize; i++) {
				if (buf[i] == '\n') {
					strEnd = i;
					break;
				}
			}

			if (strEnd == -1) { // scroll buffer
				if (strStart == -1) {
					lineHandler(buf + strStart + 1, bufLength, bufPosInFile + strStart + 1);
					bufPosInFile += bufLength;
					bufLength = (int) min(bufLength, fileSize - bufPosInFile);
					delete[]buf;
					buf = new char[bufLength];
					file.read(buf, bufLength);
				}
				else {
					int movedLength = bufLength - strStart - 1;
					memmove(buf, buf + strStart + 1, movedLength);
					bufPosInFile += strStart + 1;
					int readSize = (int) min(bufLength - movedLength, fileSize - bufPosInFile - movedLength);

					if (readSize != 0)
						file.read(buf + movedLength, readSize);
					if (movedLength + readSize < bufLength) {
						char *tmpbuf = new char[movedLength + readSize];
						memmove(tmpbuf, buf, movedLength + readSize);
						delete[]buf;
						buf = tmpbuf;
						bufLength = movedLength + readSize;
					}
					strEnd = -1;
				}
			}
			else {
				lineHandler(buf + strStart + 1, strEnd - strStart, bufPosInFile + strStart + 1);
			}
		}
		lineHandler(0, 0, 0);//eof
	}

	void Reader::lineHandler(char*buf, int l, __int64 pos){
		if (buf == 0) return;
		string s = string(buf, l);
		printf(s.c_str());
	}

	void Reader::loadFile(std::wstring& str){
		ifstream infile(str, ios_base::in | ios_base::binary);
		if (infile.is_open())
		{
			readFileFast(infile, lineHandler);
		}
	}
	

	LogMap Reader::ScanAll()
	{
		LogMap logmap;

		wstring line;

		for (auto file = _filenameArray.begin(); file != _filenameArray.end(); ++file)
		{
			// scan file with all _regex and add to logmap, which will be rendeered by client		
			loadFile(*file);
		}

		return logmap;
	}
	
}