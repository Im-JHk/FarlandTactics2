#pragma once
#include "SingletonBase.h"
/*
FILE* file;
#include <fstream>
Text, XML, INI, JSON
*/
#define SAVE_BUFFER 128
#define LOAD_BUFFER 128

class TextDataManager : public SingletonBase <TextDataManager>
{
public:
	HRESULT init(void);
	void release(void);

	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArry);

	vector<string> load(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	TextDataManager();
	~TextDataManager();
};

