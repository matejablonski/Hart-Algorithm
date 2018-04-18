#pragma once

#include "Measurement.h"
#include <string>
#include <fstream>
#include <vector>

class Hart
{
private:
	std::fstream File;
	std::string fileName_;
	std::vector<Measurement> measurements_;
	std::vector<Measurement> reducedSet_;
	int classCount_;
	int valueQuantity_;
	int msmtQuantity_;
	double* CoG;

	void readData();
	void centerOfGravity();

public:
	Hart();
	~Hart();
	Hart(std::string fileName_);
	void samMut();
	void calculate();
	void printReduceSet();
};

