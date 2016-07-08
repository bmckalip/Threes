#pragma once

using namespace std;

class Pile {
public:
	Pile(int size = 0);
	int getSize();
	friend bool operator<(const Pile&, const Pile&);
	friend Pile operator-(const Pile&, const Pile&);
private:
	int size;
};

