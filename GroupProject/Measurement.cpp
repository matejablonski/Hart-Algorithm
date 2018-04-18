#include "stdafx.h"
#include "Measurement.h"


void Measurement::printMsrm() const
{
	std::cout << index_ << " " << distance_ << " " << class_ << " ";
	for (int i=0; i<valueQuantity_; i++)
	{
		std::cout << tab_[i] << " ";
	}
	std::cout << std::endl;
}

double Measurement::getValue(int _id) const
{
	return tab_[_id];
}

double Measurement::getClass() const
{
	return class_;
}

int Measurement::getIndex()
{
	return index_;
}

void Measurement::distanceToPoint(Measurement _m)
{
	double distance = 0;
	for (int i = 0; i < valueQuantity_; i++) {
		distance += (tab_[i] - _m.getValue(i)) * (tab_[i] - _m.getValue(i));
	}
	distance_ = distance;
}

double Measurement::GetDistanceToPoint(Measurement _m)
{
	double distance = 0;
	for (int i = 0; i < valueQuantity_; i++) {
		distance += (tab_[i] - _m.getValue(i)) * (tab_[i] - _m.getValue(i));
	}
	distance_ = distance;
	return distance_;
}

Measurement::Measurement()
:
	index_(0),
	class_(0),
	valueQuantity_(0),
	tab_(nullptr),
	distance_(0)
{
}

Measurement::Measurement(int _index, int _class, int _valueQuantity, double* _tab)
:
	index_(_index),
	class_(_class),
	valueQuantity_(_valueQuantity),
	distance_(0)
{
	tab_ = new double[valueQuantity_];
	for (int i = 0; i < valueQuantity_; i++)
	{
		tab_[i] = _tab[i];
	}
}

Measurement::~Measurement()
{
	//delete[] tab_;
}

bool Measurement::operator>(Measurement second) const
{
	return distance_ > second.distance_;
}

bool Measurement::operator<(Measurement second) const
{
	return distance_ < second.distance_;
}

bool Measurement::operator==(Measurement second) const
{
	return distance_ == second.distance_;
}