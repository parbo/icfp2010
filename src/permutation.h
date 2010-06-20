#include <list>
#include <utility>

using namespace std;

#ifndef _PERMUTATION_H
#define _PERMUTATION_H

typedef pair<int, char> element;
//typedef int element;
typedef list<element> elist;

class Permutation
{
public:
	Permutation(elist::iterator seg_begin, elist::iterator seg_end);	
	~Permutation();

	elist* next();	

private:
	Permutation(elist::iterator seg_1_begin, elist::iterator seg_1_end, elist::iterator seg_2_begin, elist::iterator seg_2_end);
	void init();

	elist elements;
	elist::iterator current;

	Permutation* permutation;
};

#endif _PERMUTATION_H
