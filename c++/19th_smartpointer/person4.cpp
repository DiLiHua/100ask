
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Person {
public:

	Person() {
		cout <<"Pserson()"<<endl;
	}
	

	~Person()
	{
		cout << "~Person()"<<endl;
	}

	
	void printInfo(void)
	{
		cout << "Just a test function " << endl;
	}
};

class sp{
private:
	Person *p;
public:
	sp():p(0){}

	sp(Person *other)
	{
		cout << "sp(Person *other)" << endl;
		p = other;
	}
	sp(sp &other)
	{
		cout << "sp(Person &other)" << endl;
		p = other.p;
	}
	~sp()
	{
		cout << "~sp()" << endl;
		if(p)
			delete p;
	}

	Person *operator->()
	{
		return p;
	}

};

void test_func(sp &other)
{
	sp s = other;

	s->printInfo();
}


int main(int argc, char **argv)
{
	int i;

	sp other = new Person();

	for (i = 0;i < 2;i ++)
		test_func(other);
	
	return 0;
}

