#include <math.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "dynamicalsystem.hpp"

#define DT 0.001
#define TIME 100

// Prandtl Number
#define SIGMA 10
// Rayleigh Number
#define RHO 28.0
// Related to the physical dimensions
#define BETA 2.67

using namespace std;

void main() {
	int dimension = 3;
	vector<double> initialConditions = { 10, 10, 10 };

	// LORENZ SYSTEM

	// x_i = f_i(x; t)
	vector<FundamentalFunction> functions = {
	  [&](vector<double> vars, double t) {
			// sigma(y-x)
			return SIGMA * (vars[1] - vars[0]);
		  },
		  [&](vector<double> vars, double t) {
			// x(rho-z)-y
			return vars[0] * (RHO - vars[2]) - vars[1];
		  },
		  [&](vector<double> vars, double t) {
			// xy-beta*z
			return vars[0] * vars[1] - BETA * vars[2];
		  },
	};

	DynamicalSystem system(DT, TIME, initialConditions, functions);

	// Create csv file with header row
	ofstream csv("data.csv");
	ostringstream row;
	for (int i = 0; i < dimension; ++i) {
		row << "x" << i << ",";
	}
	row << "t\n";
	csv << row.str();

	while (!system.getComplete()) {
		vector<double> state = system.getState();
		row.str("");

		// Add variable columns
		for (int i = 0; i < dimension; ++i) {
			row << state[i] << ",";
		}
		// Add time column (last element in state vector)
		row << state[dimension] << "\n";

		csv << row.str();
		cout << row.str();

		system.step();
	}

	csv.close();
}