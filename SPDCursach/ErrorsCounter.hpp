#pragma once
#include <vector>
#include "ErrorStream.hpp"
#include <random>
#include <map>
#include <string>

struct BroadcastResult
{
	double pp;//����������� ����������� ������
	int numRepeats;//���������� �����������
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
	int num_outputs = 3;
public:
	
	/*
	���������� ������, ��� ������--���-�� �����������, ����-�--����������� ����, ��� ��� ����� ���-�� ������� �����
	*/
	std::vector<double> GetBroadcastProbs(int blockLength, int numBlocks,int maxRepeats, int numBroadcasts = 10000)
	{
		std::vector<double> prob_vector;
		prob_vector.reserve(maxRepeats);
		for (int j = 0; j < maxRepeats; j++)
		{
			
			int success_count = 0;
			for (int i = 0; i < numBroadcasts; i++)
			{
				int block_success_count = 0;
				for (int k = 0; k < numBlocks+j; k++)//�������� ������� + ����������
				{
					
					double p_err = _errorStream->ProbThatGTE(1, blockLength);//���� ���� ������, �������, ��� �� �������
					double rand_num = _dist(_rd);
					if (rand_num > p_err)
					{
						block_success_count++;
					}
					if (block_success_count == numBlocks)
					{
						success_count++;//+1 �������� �������� ���������
						break;//�������� ��� ����� ���������
					}
				}
			}
			double p = success_count / (double)numBroadcasts;
			prob_vector.push_back(p);
		}
		return prob_vector;
	}

	/*
	���������� �������, ��� ����--���-�� ������, ����-�--����������� ����, ��� ���������� ����� ����������
	*/
	std::map<int,double> SimulateBroadcast(int blockLength,int numBlocks,int numBroadcasts=10000, bool output=true)
	{
		setlocale(LC_ALL, "rus");
		std::vector<BroadcastResult> broadcastResults;
		std::map<int, int> repeats_map;
		//broadcastResults.reserve(numBroadcasts);
		for (int i = 0; i < numBroadcasts; i++)
		{
			double time = 0;
			int numRepeats = 0;
			int blocksLeft = numBlocks;
			bool canOutput = output&&i<num_outputs;
			if(canOutput)
				cout << "�������� ��������� ����� " << i+1 << endl;
			for(int blockIndex=1;;blockIndex++)
			{
				//�������� ���� ����
				double p_err=_errorStream->ProbThatGTE(1, blockLength);//���� ���� ������, �������, ��� �� �������
				double rand_num = _dist(_rd);
				
				bool res = false;
				if (rand_num <= p_err)
				{
					numRepeats++;
				}
				else 
				{
					blocksLeft--;
					res = true;
				}
				if (canOutput)
				{
					string res_str = res ? " ������: 0" : " ������: >=1";
					cout<< "�����:" << blockIndex << res_str << endl;
				}
				if (blocksLeft == 0)
				{
					break;
				}
				
			}
			if (repeats_map.count(numRepeats))
			{
				repeats_map[numRepeats]++;
			}
			else 
			{
				repeats_map[numRepeats] = 1;
			}
		}
		std::map<int, double> probs_map;
		//��������� ���������� � �����������
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

