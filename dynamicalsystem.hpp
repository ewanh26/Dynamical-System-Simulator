#include <functional>
#include <vector>

#ifndef DYNAMICALSYSTEM_H
#define DYNAMICALSYSTEM_H

typedef std::function<double(std::vector<double>, double)> FundamentalFunction;

class DynamicalSystem {
private:
	double dt;
	double time;
	int dimension;
	std::vector<double> variables;
	std::vector<FundamentalFunction> f;

	double curr_time;
	bool complete;
public:
	DynamicalSystem(double, double, std::vector<double>, std::vector<FundamentalFunction>);
	void step();
	std::vector<double> getState();
	bool getComplete();
};

#endif