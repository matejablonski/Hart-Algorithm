#include "stdafx.h"
#include "Hart.h"
#include <iostream>
#include <algorithm>


Hart::Hart()
:
	fileName_(""), 
	classCount_(0), 
	valueQuantity_(0), 
	msmtQuantity_(0),
	CoG(nullptr)

{
}

Hart::~Hart()
{
	File.close();
}

Hart::Hart(std::string _fileName)
:
	fileName_(_fileName),
	classCount_(0),
	valueQuantity_(0),
	msmtQuantity_(0),
	CoG(nullptr)
{
	File.open(fileName_, std::ios::in);
	readData();
}

void Hart::centerOfGravity()
{
	CoG = new double[valueQuantity_];
	for (int i = 0; i < valueQuantity_; i++) {
		CoG[i] = 0;
		for (int j = 0; j < msmtQuantity_; j++) {
			CoG[i] += measurements_[j].getValue(i);
		}
		CoG[i] /= msmtQuantity_;
	}
}

void Hart::samMut()
{
	for (int i = 0; i < measurements_.size(); i++) {
		double distance = 0;
		Measurement currentMsmr;
		for (int j = 0; j < measurements_.size(); j++) {
			if (i != j && measurements_[i].getClass() != measurements_[j].getClass()) {
				double tmp = measurements_[i].GetDistanceToPoint(measurements_[j]);
				if (distance == 0)
					distance = tmp;
				else if (tmp < distance) {
					distance = tmp;
					currentMsmr = measurements_[j];
				}	
			}
		}
		
		//############################################################################

		distance = 0; 
		Measurement MsmrToCompare;
		for (int j = 0; j < measurements_.size(); j++) {
			if (j != currentMsmr.getIndex() && currentMsmr.getClass() != measurements_[j].getClass()) {
				double tmp = currentMsmr.GetDistanceToPoint(measurements_[j]);
				if (distance == 0)
					distance = tmp;
				else if (tmp < distance) {
					distance = tmp;
					MsmrToCompare = measurements_[j];
				}
			}
		}

		if (MsmrToCompare == measurements_[i]) {
			bool tmp1 = false;
			bool tmp2 = false;
			for (int j = 0; j < reducedSet_.size(); j++) {
				if (currentMsmr.getIndex() == reducedSet_[j].getIndex())
					tmp1 = true;
				if (measurements_[i].getIndex() == reducedSet_[j].getIndex())
					tmp2 = true;
			}
			if(!tmp1)
				reducedSet_.push_back(currentMsmr);
			if(!tmp2)
				reducedSet_.push_back(measurements_[i]);
		}
	}

	std::cout << "Reduced set size using only mutually nearest objects: " << reducedSet_.size() << "\n\n";
	/*for (int i = 0; i<reducedSet_.size(); i++)
	{
		reducedSet_[i].printMsrm();
	}*/
}

void Hart::calculate()
{
	centerOfGravity();
	Measurement centerOfGravityPoint(0, 1, valueQuantity_, CoG);
	Measurement currentPoint = centerOfGravityPoint;

	for(int i=0; i<measurements_.size(); i++) {             // obliczenie odleg³oœci od wszystkich punktów do
		measurements_[i].distanceToPoint(currentPoint);     // œrodka ciê¿koœci
	}

	std::sort(measurements_.begin(), measurements_.end());
	reducedSet_.push_back(measurements_.front());
	measurements_.erase(measurements_.begin());

	bool isAdded = true;
	int licznik = 0;
	int dodanychElementow = 1;
	while (isAdded) {
		isAdded = false;
		licznik++;

		int j = 0;
		while(j < measurements_.size()) {
			currentPoint = measurements_[j];
			for (int i = 0; i < reducedSet_.size(); i++) {
				reducedSet_[i].distanceToPoint(currentPoint);
			}
			std::sort(reducedSet_.begin(), reducedSet_.end());
			Measurement tmp = reducedSet_.front();
			if (tmp.getClass() != currentPoint.getClass()) {
				reducedSet_.push_back(currentPoint);
				isAdded = true;
				dodanychElementow++;
			}
			j++;
		}
		//measurements_ = tmpMsrm;            // wype³enienie vectora measurements_ pomiarami które zosta³y pominiête 
										      // z powodu posiadania takies samej klasy jak rozpatrywany pomiar
		std::cout << "Reduced set size: " << reducedSet_.size() << std::endl;
		dodanychElementow = 0;
	}
	std::cout << "\nReduced set: \nSize: "<<reducedSet_.size();
	std::cout << "\nSeries: "<<licznik<< std::endl<<std::endl;

	for (int i=0; i<reducedSet_.size(); i++)
	{
		reducedSet_[i].printMsrm();
	}
}

void Hart::printReduceSet()
{
	for (Measurement m : reducedSet_)
	{
		m.printMsrm();
	}
}

void Hart::readData()
{
	if (File.good()) {
		File >> classCount_ >> valueQuantity_ >> msmtQuantity_;

		for (int i = 0; i < msmtQuantity_; i++) {
			int tmpclass = 0;
			File >> tmpclass;
			double* tmpTab = new double[valueQuantity_];

			for (int j = 0; j < valueQuantity_; j++) {
				File >> tmpTab[j];
			}
			Measurement tmpMeasurement(i, tmpclass, valueQuantity_, tmpTab);
			measurements_.push_back(tmpMeasurement);
			delete[] tmpTab;
		}
		std::cout << "There are " << classCount_ << " classes, " << valueQuantity_ << " features and " << msmtQuantity_ << " objects.\n";
	}
	else
		std::cerr << "Blad wczytania pliku" << std::endl;
}
