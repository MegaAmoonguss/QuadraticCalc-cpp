#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "quadratic.h"

using namespace std;

vector<int> factor(int n) {
	vector<int> factors;

	if (n < 0)
		n *= -1;

	for (int i = 1; i <= sqrt(n); i++) {
		if (n % i == 0) {
			factors.push_back(i);
			if (n / i != i)
				factors.push_back(n / i);
		}
	}

	sort(factors.begin(), factors.end());
	return factors;
}

static int findGCF(int num1, int num2) {
	vector<int> factors1 = factor(num1);
	vector<int> factors2 = factor(num2);

	int GCF = 1;

	for (unsigned int i = 0; i < factors1.size(); i++) {
		for (unsigned int j = 0; j < factors2.size(); j++) {
			if (factors1[i] == factors2[j])
				GCF = factors1[i];
		}
	}
	return GCF;
}

Quadratic::Quadratic(int a, int b, int c) {
	this->a = a;
	this->b = b;
	this->c = c;
	factors = factor(a * c);
}

void Quadratic::getWorkingFactors(int workingFactors[]) {

	if (c > 0) {
		for (unsigned int i = 0; i < factors.size(); i++) {
			if (factors[i] + factors[factors.size() - 1 - i] == b) {
				workingFactors[0] = factors[i];
				workingFactors[1] = factors[factors.size() - 1 - i];
			}
			else if ((factors[i] * -1) + (factors[factors.size() - 1 - i] * -1) == b) {
				workingFactors[0] = factors[i] * -1;
				workingFactors[1] = factors[factors.size() - 1 - i] * -1;
			}
		}
	}
	else {
		for (unsigned int i = 0; i < factors.size(); i++) {
			if (factors[i] + (factors[factors.size() - 1 - i] * -1) == b) {
				workingFactors[0] = factors[i];
				workingFactors[1] = factors[factors.size() - 1 - i] * -1;
			}
		}
	}
}

vector<int> Quadratic::factorEquation() {
	int workingFactors[2] = { 0, 0 };
	getWorkingFactors(workingFactors);

	if (workingFactors[0] == 0 && workingFactors[1] == 0) {
		vector<int> nullVec;
		nullVec.push_back(0);
		return nullVec;
	}

	int group1GCF = findGCF(a, workingFactors[0]);
	int group2GCF = findGCF(workingFactors[1], c);

	if ((a / group1GCF) != (workingFactors[1] / group2GCF) || (workingFactors[0] / group1GCF) != (c / group2GCF)) {
		group2GCF *= -1;
	}

	vector<int> finalEquation;
	finalEquation.push_back(group1GCF);
	finalEquation.push_back(group2GCF);
	finalEquation.push_back(a / group1GCF);
	finalEquation.push_back(workingFactors[0] / group1GCF);

	return finalEquation;
}

int Quadratic::getDiscriminant() {
	int discrim = (b * b) - (4 * a * c);
	return discrim;
}

vector<double> Quadratic::solve() {
	vector<double> solutions;
	if (getDiscriminant() > 0) {
		solutions.push_back(((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a));
		solutions.push_back(((-1 * b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a));
	}
	else if (getDiscriminant() == 0)
		solutions.push_back(((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a));

	return solutions;
}
