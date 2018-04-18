#include "stdafx.h"
#include "Hart.h"

int main()
{
	bool x = true;
	while (x) {
		Hart hart("epj_s.txt");
		int wybor = 0;
		std::cout << "\nChoose algorithm:\n1 - Sam Mut\n2 - Hart\n3 - Mut + Hart\n4 - Tomek\n5 - GK\n6 - Exit\n";
		std::cin >> wybor;

		switch (wybor) {
		case 1:
			hart.samMut();
			break;
		case 2:
			hart.calculate();
			break;
		case 3:
			hart.samMut();
			hart.calculate();
			break;
		case 4:
			hart.samMut();
			hart.calculate();
			break;
		case 5:
			hart.samMut();
			hart.calculate();
			break;
		case 6:
			x = false;
			break;
		default:
			std::cout << "Wrong decision!";
			break;
		}
	}
	
	system("pause");
	return 0;
}