#pragma once

using namespace std;

class Pile {
public:
	//constructor
	Pile(int size = 0);
	
	//getters
	int		getSize();
	bool	isEmpty();

	//overloaded operators for comparision
	friend bool operator<(const Pile&, const Pile&);
	friend bool operator>(const Pile&, const Pile&);
	bool		operator==(const Pile& other) const;
	bool		operator!=(const Pile& other) const;
	friend Pile operator-(const Pile&, const Pile&);

private:
	int size;
};

