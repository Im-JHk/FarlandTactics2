#pragma once
class jsonTest
{
private:
	string a;
	string b;
	string c;
	string d;
	string e;
public:
	void init(string a, string b, string c);

	string getA() { return this->a; }
	string getB() { return this->b; }
	string getC() { return this->c; }
	string getD() { return this->d; }
	string getE() { return this->e; }

	jsonTest() {}
	~jsonTest() {}
};

