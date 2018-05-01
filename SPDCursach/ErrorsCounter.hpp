#pragma once
#include <vector>
#include "ErrorStream.hpp"

struct BroadcastResult {
	double pp;//����������� ����������� ������
	int numRepeats;//���������� �����������
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
		double pErr = _errorStream->ProbThatGTE(numCanCorrect + 1, blockLength);//�����������, ��� ����� ������ ������, ��� ����� ���������
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

