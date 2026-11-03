#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <map>

namespace CyA {
	typedef std::pair<double,double> point;
	typedef std::pair<point, point> line;
	typedef std::vector<point> point_vector;

	enum side {
		LEFT = -1,	// Por encima
		CENTER,			// Por debajo
		RIGHT
	};

	class point_set : public point_vector {
	 public:
		point_set(const std::vector<point> &points);
		~point_set(void) {}

		void quickHull(void);

		void write_hull(std::ostream &os) const;
		void write(std::ostream &os) const;

		inline const point_vector& get_hull(void) const { return hull_; }
		inline const point_vector& get_points(void) const { return *this; }
		void set_d(void) {d_option = true;};

	 private:
	 	bool d_option;
		point_vector hull_;
		void quickHull(const line &l, int side);

		double distance(const line &l, const point &p) const;
		int find_side(const line &l, const point &p) const;
		void x_bounds(point &min_x, point &max_x) const;
		double point_2_line(const line &l, const point &p) const;
		bool farthest_point(const line &l, int side, point &farthest) const;
	};
}