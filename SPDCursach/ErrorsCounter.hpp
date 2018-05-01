#pragma once
#include <vector>
#include "ErrorStream.hpp"

struct BroadcastResult {
	double pp;//¬еро€тность правильного приема
	int numRepeats;// оличество переспросов
};

class ErrorsCounter
{
private:
	ErrorStream* _errorStream;
	int _rowLength;
public:

	BroadcastResult SimulateBroadcast(int numCanCorrect,int maxRepeats,int numRows)
	{
		int blockLength = numRows*_rowLength;
		double pErr = _errorStream->ProbThatGTE(numCanCorrect + 1, blockLength);//¬еро€тность, что будет больше ошибок, чем можно исправить
		for (int i = 0; i < maxRepeats; i++)
		{

		}
	}

	ErrorsCounter(ErrorStream* errorStream)
	{
		_errorStream = errorStream;
		
	}

	~ErrorsCounter()
	{
	}
};

