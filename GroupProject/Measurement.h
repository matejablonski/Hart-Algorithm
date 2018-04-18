#include <iostream>

class Measurement
{
private:
	int index_;
	int class_;
	int valueQuantity_;
	double* tab_;
	double distance_;

public:
	Measurement();
	Measurement(int _index, int _class, int _valueQuantity, double* _tab);
	~Measurement();
	void printMsrm() const;

	double getValue(int _id) const;
	double getClass() const;
	int getIndex();
	void distanceToPoint(Measurement _m);
	double GetDistanceToPoint(Measurement _m);

	bool operator>(Measurement second) const;
	bool operator<(Measurement second) const;
	bool operator==(Measurement second) const;
};

