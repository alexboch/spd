#pragma once
/*Базовый класс потока ошибок*/
class ErrorStream
{

protected:
	ErrorStream()
	{
		
	}


public:
	/*Вероятность, что произойдет k и больше ошибок*/
	virtual double ProbThatGTE(int k,int n) = 0;
	/*Вероятность ровно k ошибок*/
	virtual double ProbThatEqual(int k,int n) = 0;
	

	virtual ~ErrorStream()
	{
	}
};

