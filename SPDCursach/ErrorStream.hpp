#pragma once
/*������� ����� ������ ������*/
class ErrorStream
{

protected:
	ErrorStream()
	{
		
	}


public:
	/*�����������, ��� ���������� k � ������ ������*/
	virtual double ProbThatGTE(int k,int n) = 0;
	/*����������� ����� k ������*/
	virtual double ProbThatEqual(int k,int n) = 0;
	

	virtual ~ErrorStream()
	{
	}
};

