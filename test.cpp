#include "util.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main ()
{
	set<string> s1;
	s1.insert("A");
	s1.insert("B");
	s1.insert("C");
	s1.insert("D");

	set<string> s2;
	s2.insert("E");
	s2.insert("F");
	s2.insert("C");
	s2.insert("D");

	set<string> interSet = setIntersection(s1, s2);
	
	cout << "size of intersect set is " << interSet.size() << endl;

	for(set<string>::iterator it = interSet.begin(); it != interSet.end(); it++)
	{
		cout << *it << endl;
	}

	set<string> unionSet = setUnion(s1, s2);
	
	cout << "size of union set is " << unionSet.size() << endl;

	for(set<string>::iterator it = unionSet.begin(); it != unionSet.end(); it++)
	{
		cout << *it << endl;
	}





	return 0;
}