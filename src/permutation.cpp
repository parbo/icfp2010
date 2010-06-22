#include <algorithm>
#include "permutation.h"

Permutation::Permutation(elist::iterator seg_begin, elist::iterator seg_end)
:	permutation(0)
{
	copy(seg_begin, seg_end, back_inserter(elements));
	init();
}

Permutation::Permutation(elist::iterator seg_1_begin, elist::iterator seg_1_end, elist::iterator seg_2_begin, elist::iterator seg_2_end)
:	permutation(0)
{
	copy(seg_1_begin, seg_1_end, back_inserter(elements));
	copy(seg_2_begin, seg_2_end, back_inserter(elements));
	init();
}

Permutation::~Permutation()
{
	delete permutation;
}

void Permutation::init()
{
	current = elements.begin();

	if(elements.size() > 1)
	{
		permutation = new Permutation(++elements.begin(), elements.end());
	}
}

elist* Permutation::next()
{
	elist* result = 0;

	while((current != elements.end()) && (result == 0))
	{
		if(permutation != 0)
		{
			result = permutation->next();

			if(result != 0)
			{
				result->push_front(*current);
			}
			else
			{
				++current;
				delete permutation;
				permutation = 0;

				if(current != elements.end())
				{
					elist::iterator next_e = current;
					++next_e;
					permutation = new Permutation(elements.begin(), current, next_e, elements.end());
				}
			}
		}
		else
		{
			result = new elist;
			result->push_back(*current);
			++current;
		}
	}

	return result;
}
