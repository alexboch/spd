#pragma once
#include <vector>
#include "ErrorStream.hpp"
#include <random>
#include <map>

struct BroadcastResult
{
	double pp;//Вероятность правильного приема
	int numRepeats;//Количество переспросов
	BroadcastResult(double pp, int numRepeats)
	{
		this->pp = pp;
		this->numRepeats = numRepeats;
	}
	BroadcastResult()
	{

	}
};



class ErrorsCounter
{
private:
	ErrorStream* _errorStream;
	std::random_device _rd;
	std::uniform_real_distribution<> _dist;
public:

	/*
	Возвращает словарь, где ключ--кол-во переспросов, знач-е--вероятность того, что при таком кол-ве принято верно
	*/
	std::map<int, double> GetBroadcastProbs(int blockLength, int numBlocks,int maxRepeats, int numBroadcasts = 10000)
	{
		std::map<int, double> repeats_map;
		for (int j = 0; j < maxRepeats; j++)
		{
			
			int success_count = 0;
			for (int i = 0; i < numBroadcasts; i++)
			{
				int block_success_count = 0;
				for (int k = 0; k < numBlocks+j; k++)//передача пакетов + переспросы
				{
					
					double p_err = _errorStream->ProbThatGTE(1, blockLength);//если есть ошибки, считаем, что не передан
					double rand_num = _dist(_rd);
					if (rand_num > p_err)
					{
						block_success_count++;
					}
					if (block_success_count == numBlocks)
					{
						success_count++;//+1 успешная передача сообщения
						break;//передали все блоки сообщения
					}
				}
			}
			double p = success_count / (double)numBroadcasts;
			repeats_map[j] = p;
		}
		return repeats_map;
	}

	/*
	Возвращает словарь, где ключ--кол-во ошибок, знач-е--вероятность того, что произойдет такое количество
	*/
	std::map<int,double> SimulateBroadcast(int blockLength,int numBlocks,int numBroadcasts=10000)
	{
		
		std::vector<BroadcastResult> broadcastResults;
		std::map<int, int> repeats_map;
		//broadcastResults.reserve(numBroadcasts);
		for (int i = 0; i < numBroadcasts; i++)
		{
			double time = 0;
			int numRepeats = 0;
			int blocksLeft = numBlocks;
			
			while (true)
			{
				//передать один блок
				double p_err=_errorStream->ProbThatGTE(1, blockLength);//если есть ошибки, считаем, что не передан
				double rand_num = _dist(_rd);
				if (rand_num <= p_err)
				{
					numRepeats++;
				}
				else 
				{
					blocksLeft--;
				}
				if (blocksLeft == 0) break;
			}
			if (repeats_map.count(numRepeats))
			{
				repeats_map[numRepeats]++;
			}
			else 
			{
				repeats_map[numRepeats] = 1;
			}
			//BroadcastResult br(0, numRepeats);
			//broadcastResults.push_back(br);
		}
		std::map<int, double> probs_map;
		//Перевести количество в вероятность
		for (auto const& m : repeats_map)
		{
			double p = (double)m.second / numBroadcasts;
			probs_map[m.first] = p;
		}
		return probs_map;
	}

	ErrorsCounter(ErrorStream* errorStream)
	{
		_errorStream = errorStream;
		
	}

	~ErrorsCounter()
	{
	}
};

