#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

#include "point_set.h"

int main(int argc, char* argv[]) {
	CyA::point_vector points;
	
	int n;

	std::cin >> n;
	// std::cout << n << std::endl;

	for (int i{0}; i < n; i++) {
		double x, y;
		std::cin >> x >> y;
		// std::cout << x << " " << y << std::endl;
		points.emplace_back(x, y);
	}
		
	CyA::point_set pointSet(points);
	// std::cout << "Hola" << std::endl;
	if (argc > 1) {
		if (std::string(argv[1]) == "-d") {
			pointSet.set_d();
		}
	}
	// std::cout << "Hola2" << std::endl;
	pointSet.quickHull();

	pointSet.write_hull(std::cout);

	return 0;
}