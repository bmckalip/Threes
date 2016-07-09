#pragma once

using namespace std;

class Pile {
public:
	Pile(int size = 0);
	int getSize();
	bool isEmpty();
	friend bool operator<(const Pile&, const Pile&);
	friend Pile operator-(const Pile&, const Pile&);
	bool operator==(const Pile& other) const;
private:
	int size;
};

