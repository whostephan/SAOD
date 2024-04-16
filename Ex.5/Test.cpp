#include "Test.h"

int Test::nCount = 0;

Test::Test() {
	nCount++;
	cout << "Test created. Count: " << nCount << endl;
}

Test::Test(Test* test) {
	nCount++;
	cout << "Test created. Count: " << nCount << endl;
}

void Test::Foo(Test test) {
	cout << "Foo called" << endl;
}

Test::~Test() {
	nCount--;
	cout << "Test destroyed. Count: " << nCount << endl;
}

Child::Child() {
	cout << "Child created" << endl;
}

Child::~Child() {
	cout << "Child destroyed" << endl;
}

Aggregate::Aggregate() {
	cout << "Aggregate created" << endl;
}

Aggregate::~Aggregate() {
	cout << "Aggregate destroyed" << endl;
}