#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

class Gate;

typedef pair<char, char> tuple;
typedef map<tuple, tuple> gate_map;
typedef vector<Gate*> gate_list;

gate_map gate;

void init_gate(gate_map& gate)
{
	gate[make_pair('0', '0')] = make_pair('0', '2');
	gate[make_pair('0', '1')] = make_pair('2', '2');
	gate[make_pair('0', '2')] = make_pair('1', '2');
	gate[make_pair('1', '0')] = make_pair('1', '2');
	gate[make_pair('1', '1')] = make_pair('0', '0');
	gate[make_pair('1', '2')] = make_pair('2', '1');
	gate[make_pair('2', '0')] = make_pair('2', '2');
	gate[make_pair('2', '1')] = make_pair('1', '1');
	gate[make_pair('2', '2')] = make_pair('0', '0');
}

class Gate
{
public:
	Gate(): left_val('0'), right_val('0') {};

	void eval(gate_list& gates, char ext);

	int left_in_ix;
	int right_in_ix;
	char left_in_port;
	char right_in_port;
	int left_out_ix;
	int right_out_ix;
	char left_out_port;
	char right_out_port;
	char left_val;
	char right_val;
};

void Gate::eval(gate_list& gates, char ext)
{
	char left_in;
	char right_in;

	if(left_in_port == 'L')
	{
		left_in = gates[left_in_ix]->left_val;
	}
	else if(left_in_port == 'R')
	{
		left_in = gates[left_in_ix]->right_val;
	}
	else
	{
		left_in = ext;
	}

	if(right_in_port == 'L')
	{
		right_in = gates[right_in_ix]->left_val;
	}
	else if(right_in_port == 'R')
	{
		right_in = gates[right_in_ix]->right_val;
	}
	else
	{
		right_in = ext;
	}

	tuple output = gate[make_pair(left_in, right_in)];
	left_val = output.first;
	right_val = output.second;
}

class Circuit
{
public:
	~Circuit();

	void eval(string& in, string& out);
	void add_gate(int li_ix, char li_p, int ri_ix, char ri_p, int lo_ix, char lo_p, int ro_ix, char ro_p);
	void set_external(int out_ix, char out_p, int in_ix, char in_p);

	gate_list gates;
	int ext_in_ix;
	int ext_out_ix;
	char ext_in_port;
	char ext_out_port;
};

Circuit::~Circuit()
{
	for(gate_list::iterator gate = gates.begin(); gate != gates.end(); ++gate)
	{
		delete *gate;
	}
}

void Circuit::eval(string& in, string& out)
{
	out.clear();
	out.reserve(in.size());

	for(string::iterator ch = in.begin(); ch != in.end(); ++ch)
	{
		for(gate_list::iterator gate = gates.begin(); gate != gates.end(); ++gate)
		{
			(*gate)->eval(gates, *ch);
		}

		if(ext_in_port == 'L')
		{
			out.push_back(gates[ext_in_ix]->left_val);
		}
		else
		{
			out.push_back(gates[ext_in_ix]->right_val);
		}
	}
}

void Circuit::add_gate(int li_ix, char li_p, int ri_ix, char ri_p, int lo_ix, char lo_p, int ro_ix, char ro_p)
{
	Gate* gate = new Gate();
	gate->left_in_ix = li_ix;
	gate->left_in_port = li_p;
	gate->right_in_ix = ri_ix;
	gate->right_in_port = ri_p;
	gate->left_out_ix = lo_ix;
	gate->left_out_port = lo_p;
	gate->right_out_ix = ro_ix;
	gate->right_out_port = ro_p;
	gates.push_back(gate);
}

void Circuit::set_external(int out_ix, char out_p, int in_ix, char in_p)
{
	ext_in_ix = in_ix;
	ext_out_ix = out_ix;
	ext_in_port = in_p;
	ext_out_port = out_p;
}

int main(int argc, char** argv)
{
	init_gate(gate);
	Circuit c;
	c.add_gate(0, 'X', 2, 'L', 0, 'X', 1, 'L');
	c.add_gate(0, 'R', 2, 'R', 2, 'L', 2, 'R');
	c.add_gate(1, 'L', 1, 'R', 0, 'R', 1, 'R');
	c.set_external(0, 'L', 0, 'L');
	string in("01202101210201202");
	string out;
	c.eval(in, out);

	cout << out;

	return 0;
}
