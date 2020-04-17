#include <iostream>
#include <sstream>
#include <vector>

struct Layer {
	double scale;
	unsigned char r, g, b;

	Layer(double scale_, unsigned char r_, unsigned char g_, unsigned char b_) {
		scale = scale_;
		r = r_;
		g = g_;
		b = b_;
	}
};

int main() {
	vector<Layer*> layers;

	// take input in form of: scale r g b
	string line;

	while (getline(cin, line)) {
		double scale;
		unsigned char r, g, b;
		stringstream ss(line);
		line >> scale >> r >> g >> b;
		Layer* layer = new Layer(scale, r, g, b);
		layers.push_back(layer);
	}

}