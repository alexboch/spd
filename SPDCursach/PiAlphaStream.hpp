#pragma once
#include "ErrorStream.hpp"
#include <cmath>
#include <stdexcept>


class PiAlphaStream :
	public ErrorStream
{
private:
	/*Вероятность ошибки символа*/
	double _p;
	/*Показатель группировки*/
	double _alpha;

public:

	double GetP()
	{
		return _p;
	}

	double GetAlpha()
	{
		return _alpha;
	}

	PiAlphaStream(double p,double alpha):ErrorStream()
	{
		this->_p = p;
		_alpha = alpha;
	}

	double ProbThatGTE(int k,int n)
	{
		if (k > n)
			throw std::runtime_error("k must be less than or equal to n!");
		if (k == 0)
		{
			return 1;
		}
		double t = k;
		return _p*pow(n / t, 1 - _alpha);
	}

	double ProbThatEqual(int k,int n)
	{
		return ProbThatGTE(k,n) - ProbThatGTE(k + 1,n);
	}

	~PiAlphaStream()
	{
	}
};

