#pragma once
#include <vector>
#include "ErrorStream.hpp"
#include <random>
#include <map>

struct BroadcastResult
{
	double pp;//¬еро€тность правильного приема
	int numRepeats;// оличество переспросов
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
public:



	std::map<int,double> SimulateBroadcast(int blockLength,int numBlocks,int numBroadcasts=10000)
	{
		std::random_device rd;
		std::uniform_real_distribution<> dist;
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
				double rand_num = dist(rd);
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
		//ѕеревести количество в веро€тность
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

