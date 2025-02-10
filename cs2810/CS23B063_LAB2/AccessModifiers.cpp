#include <iostream>
#include <math.h>
class AccessCheck {
public:
	int pubvar;
	void pubfun() { std::cout << "in pubfun.\n"; }
	void checkFromClass() {
		pubfun();
		profun();
		prifun();
		pubvar = 10;
		provar = 11;
		privar = 12;
	}

protected:
	int provar;
	void profun() { std::cout << "in profun.\n"; };	

private:
	int privar;
	void prifun() { std::cout << "in prifun.\n"; };	
};

class DerivedAccessCheck: public AccessCheck {
public:
	void checkFromChild() {
		pubfun();
		profun();
		//prifun();
		pubvar = 0;
		provar = 1;
		//privar = 2;
	}
};

void checkFromRest() {
	AccessCheck ac;
	ac.pubvar = 4;
	//ac.provar = 5;
	//ac.privar = 6;
	ac.pubfun();
	//ac.profun();
	//ac.prifun();
}
int main() {
	AccessCheck ac;
	ac.checkFromClass();

	DerivedAccessCheck dac;
	dac.checkFromChild();

	checkFromRest();
	return 0;
}
