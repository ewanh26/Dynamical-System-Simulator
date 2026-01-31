#include "dynamicalsystem.hpp"
#include <functional>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * @brief Construct a new Dynamical System object
 *
 * @param dt_ The size of each timestep
 * @param time_ The total time the dynamical system will run for
 * @param variables_ x, The initial conditions of the dynamical variable vector
 * @param f_ f(x; t) The fundamental form functions corresponding to each component of the dynamical variable vector's time derivative
 */
DynamicalSystem::DynamicalSystem(double dt_, double time_, std::vector<double> variables_, std::vector<FundamentalFunction> f_) {
	if (variables_.size() != f_.size()) {
		throw std::invalid_argument("Dimensions of variable vector and function vector do not match");
	}
	else if (time_ < 0 || dt_ < 0) {
		throw std::invalid_argument("Time parameters cannot be negative");
	}
	else {
		dimension = variables_.size();
		dt = dt_;
		time = time_;
		variables = variables_;
		f = f_;

		curr_time = 0;
		complete = false;
	}
};

/**
 * @brief Moves the dynamical system one timestep (dt) forward synchronously.
 * Does not execute the step if the system's time has fully elapsed; in that case,
 * the system is complete.
 */
void DynamicalSystem::step() {
	if (curr_time >= time) {
		complete = true;
		return;
	}

	std::vector<double> xdot(dimension);
	std::vector<double> new_x = variables;

	for (int i = 0; i < dimension; ++i) {
		xdot[i] = f[i](variables, curr_time);
		// std::cout << xdot[i] << std::endl;
		new_x[i] += xdot[i] * dt;
	}

	curr_time += dt;
	variables = new_x;
}

/**
 * @brief Returns the current state of the system as a vector containing
 * all of the dynamical variables and time
 *
 * @return std::vector<double> (x1, x2, ..., xd, t),
 * where d is the number of dimensions. It is of length d+1
 */
std::vector<double> DynamicalSystem::getState() {
	// TODO: Optimise this
	std::vector<double> vars_time = variables;
	vars_time.push_back(curr_time);
	return vars_time;
}

bool DynamicalSystem::getComplete() {
	return complete;
}