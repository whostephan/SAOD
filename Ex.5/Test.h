#pragma once
#include <iostream>
using namespace std;

class Test {
public:
	static int nCount;
	Test();
	Test(Test* test);
	~Test();
	void Foo(Test test);
};

class Child : public Test {
public:
	Child();
	~Child();
};

class Aggregate {
public:
	Test objTest;
	Aggregate();
	~Aggregate();
};

template<typename T>
class AggregateT {
public:
	T objT;
	AggregateT() {
		cout << "AggregateT created" << endl;
	}
	~AggregateT() {
		cout << "AggregateT destroyed" << endl;
	}
};