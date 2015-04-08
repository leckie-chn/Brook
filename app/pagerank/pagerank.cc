// Copyright PKU-Cloud 2015
// Author: Yan Ni (leckie.dove@gmail.com)

// This is a benchmark program
// A Serialize version of pagerank algorithm, based on wikipedia: http://en.wikipedia.org/wiki/PageRank

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "src/util/common.h"

using namespace std;

vector<vector<double> > M;
vector<double> v;
vector<double> v0;
int n, m;
int MaxIter;
const double d = 0.85;
// first parameter for input filename
// second parameter for max iteration time

inline double normL2(const vector<double> &x){
	double resl = 0.0;
	for (int i = 0; i < m; i++)
		resl += x[i] * x[i];

	return sqrt(resl);
}

int main(int argc, char* argv[]){
	ifstream fin(argv[1]);
	MaxIter = strtol(argv[2], NULL, 10);
	// n == m in a single node
	fin >> n >> m;

	CHECK_LE(m, n);

	M.resize(n);
	for (int i = 0; i < n; i++){
		M[i].resize(m);
		for (int j = 0; j < m; j++)
			fin >> M[i][j];
	}

	srand(time(NULL));
	v.resize(m);
	for (int i = 0; i < m; i++)
		v[i] = (double)rand() / (double)RAND_MAX;


	double norm = normL2(v);
	for (int i = 0; i < m; i++)
		v[i] /= norm;


	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i][j] = d * M[i][j] + (1 - d) / m;

	v0.resize(m);
	for (int k = 0; k < MaxIter; k++){
		for (int i = 0; i < n; i++){
			v0[i] = 0;
			for (int j = 0; j < m; j++)
				v0[i] += v[j] * M[i][j];
		}
		norm = normL2(v0);
		for (int i = 0; i < m; i++)
			v[i] = v0[i] / norm;

	}

	for (int i = 0; i < m; i++)
		cout << v[i] << ' ' << endl;

	return 0;

}

