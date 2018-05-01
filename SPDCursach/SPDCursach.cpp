// SPDCursach.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "Chain.h"

using namespace std;

double logbase(double a, double base) // нашЄл где-то эту функцию, проверил на log2(8), получилось 3
{
	return log(a) / log(base);
}


int main()
{



	double n = 1600.0;
	double p = 0.006;
	double P = 0.0;
	double alpha = 0.35;
	double normal_recieve = 0.0;
	double errorp = 0.0; //веро€тность ошибки
	double r = 0.0;
	double m = 0.0;
	double tennine = 0.0; // 10 в минус дев€той

	while (normal_recieve < 0.75)
	{
		P = p * pow(n, 1 - alpha);
		normal_recieve = 1 - P;
		n--;

		//cout << normal_recieve << "----" << n << endl;
	}

	n = 200.0; // в цикле получилось 309, но мы с тобой вы€снили, что нужно 200

	tennine = pow(10.0, -9.0);

	errorp = n / 8.0 * tennine;

	r = logbase(pow((n + 1.0) / 2.0, 1.0 - alpha) * p / errorp, 2.0);

	cout << "r = " << r << endl;

	m = logbase(n + r + 1, 2.0);

	cout << "m = " << m << endl;

	int m_int = (int)(round(m));
	int r_int = (int)(round(r));
	int powers[] = { 1,3,17,85 };
	Chain chain;
	for (int i = 0; i < 4; i++)
	{
		Chain c2(powers[i], round(m));
		cout<<powers[i]<<":"<< c2;
		chain = chain + c2;
	}
	cout << chain;
	system("PAUSE");
	int module = pow(2, (round(m))) - 1;

	vector<vector<int>> root_chains;

	for (int i = 1; i <= 51; i += 2)
	{
		int a = i;
		vector<int> root_chain;
		root_chain.push_back(a);
		while (true)
		{
			a = (a * 2) % module;
			if (a == i) break;
			root_chain.push_back(a);
		}
		root_chains.push_back(root_chain);
	}
	
	for (int i = 0; i < root_chains.size(); i++)
	{
		cout << i + 1 << ":";
		for (int j = 0; j < root_chains[i].size(); j++)
		{
			cout << root_chains[i][j] << " ";
		}
		cout << endl;
	}

	double address = 8.0;
	double upravlenie = 8.0;
	double info = 200.0;
	double izbit = 223.0;
	double all = address + upravlenie + info + izbit;

	double p_recieved = 0.0;
	double p_recieved_with_error = 0.0;
	double p_system_error = 0.0;
	double a = 0.0;
	double t0 = 0.0;
	double tp = 0.0;
	double L = 12500.0;
	double C = 250000.0;
	double tdk = 0.0;
	double tdkos = 0.0;
	double t_ex_op = 0.0;
	double t_os = 0.0;
	double t_wait = 0.0;
	double delta = 0.0;
	double R = 0.0;
	double S = 0.0;
	double tmin = 0.0;
	double t_pr = 0.0;
	double gamma = 0.0;
	double t_send = 0.0;
	double t_sleeping = 0.0;
	double mm = 8.0;


	p_recieved_with_error = 1.0 - p_recieved;
	a = 1.0 / p_recieved;
	//p_system_error = 

	while (true)
	{
		if (mm == 21.0)
		{
			break;
		}

		p_recieved = pow(mm / (mm + all), 1.064 - 1.0);
		t0 = 1.0 / 2400.0;
		tp = L / C;
		t_ex_op = 1.0 / 1700000000.0;
		tdk = 4 * t_ex_op * (address + upravlenie + info);
		t_os = (address + upravlenie + info) * t0;
		tdkos = (address + upravlenie) * t_ex_op;
		t_wait = 2.0 * tp + tdk + t_os + tdkos;
		delta = t_wait / t0;
		R = info * p_recieved / (all + delta);
		S = 3200 / 400;
		t_send = S * all * t0;
		t_sleeping = (S - 1) * delta * t0;
		tmin = t_send + t_sleeping + tp + tdk;
		gamma = (info + delta) * t0;
		t_pr = tmin + (mm - S) * gamma;

		cout << "m = " << mm << " | t_pr = " << t_pr << endl;

		mm = mm + 1.0;
	}

	system("pause");
}

