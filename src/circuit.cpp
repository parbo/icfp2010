#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <cstdlib>
#include "permutation.h"

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

	void reset();
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

void Gate::reset()
{
	left_val = '0';
	right_val = '0';
}

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

	void reset();
	void eval(string& in, string& out);
	void add_gate(int li_ix, char li_p, int ri_ix, char ri_p, int lo_ix, char lo_p, int ro_ix, char ro_p);
	void set_gate(int ix, int li_ix, char li_p, int ri_ix, char ri_p, int lo_ix, char lo_p, int ro_ix, char ro_p);
	void set_external(int out_ix, char out_p, int in_ix, char in_p);
	void print();
	void print(int ix, char port);

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

void Circuit::reset()
{
	for(gate_list::iterator gate = gates.begin(); gate != gates.end(); ++gate)
	{
		(*gate)->reset();
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

void Circuit::set_gate(int ix, int li_ix, char li_p, int ri_ix, char ri_p, int lo_ix, char lo_p, int ro_ix, char ro_p)
{
	Gate* gate = gates[ix];
	gate->left_in_ix = li_ix;
	gate->left_in_port = li_p;
	gate->right_in_ix = ri_ix;
	gate->right_in_port = ri_p;
	gate->left_out_ix = lo_ix;
	gate->left_out_port = lo_p;
	gate->right_out_ix = ro_ix;
	gate->right_out_port = ro_p;
}

void Circuit::set_external(int out_ix, char out_p, int in_ix, char in_p)
{
	ext_in_ix = in_ix;
	ext_out_ix = out_ix;
	ext_in_port = in_p;
	ext_out_port = out_p;
}

void Circuit::print()
{
	cout << ext_out_ix << ext_out_port << ":" << endl;

	for(gate_list::iterator gate = gates.begin(); gate != gates.end(); ++gate)
	{
		print((*gate)->left_in_ix, (*gate)->left_in_port);
		print((*gate)->right_in_ix, (*gate)->right_in_port);
		cout << "0#";
		print((*gate)->left_out_ix, (*gate)->left_out_port);
		print((*gate)->right_out_ix, (*gate)->right_out_port);

		if(gate + 1 != gates.end())
		{
			cout << ',';
		}
		else
		{
			cout << ':';
		}

		cout << endl;
	}

	cout << ext_in_ix << ext_in_port << endl;
}

void Circuit::print(int ix, char port)
{
	if(port != 'X')
	{
		cout << ix;
	}

	cout << port;
}

void init_port_list(elist& port_list, int size)
{
	port_list.push_back(make_pair(0, 'X'));

	for(int ix = 0; ix < size; ++ix)
	{
		port_list.push_back(make_pair(ix, 'L'));
		port_list.push_back(make_pair(ix, 'R'));
	}
}

bool cfg_circuit(Circuit& circuit, elist& output_list)
{
	bool result = true;
	gate_list& gates = circuit.gates;
	elist::iterator port = output_list.begin();

	int out_ix = port->first;
	char out_side = port->second;

	// External gate
	if(out_side != 'X')
	{
		circuit.ext_in_ix = out_ix;
		circuit.ext_in_port = out_side;

		if(out_side == 'L')
		{
			gates[out_ix]->left_out_port = 'X';
		}
		else
		{
			gates[out_ix]->right_out_port = 'X';
		}
	}
	else
	{
		result = false;
	}

	++port;

	for(int gate_ix = 0; gate_ix < gates.size(); ++gate_ix)
	{
		// Left input
		out_ix = port->first;
		out_side = port->second;
		gates[gate_ix]->left_in_ix = out_ix;
		gates[gate_ix]->left_in_port = out_side;

		if(out_side == 'L')
		{
			gates[out_ix]->left_out_ix = gate_ix;
			gates[out_ix]->left_out_port = 'L';
		}
		else if(out_side == 'R')
		{
			gates[out_ix]->right_out_ix = gate_ix;
			gates[out_ix]->right_out_port = 'L';
		}
		else
		{
			circuit.ext_out_ix = gate_ix;
			circuit.ext_out_port = 'L';
		}

		++port;

		// Right input
		out_ix = port->first;
		out_side = port->second;
		gates[gate_ix]->right_in_ix = out_ix;
		gates[gate_ix]->right_in_port = out_side;

		if(out_side == 'L')
		{
			gates[out_ix]->left_out_ix = gate_ix;
			gates[out_ix]->left_out_port = 'R';
		}
		else if(out_side == 'R')
		{
			gates[out_ix]->right_out_ix = gate_ix;
			gates[out_ix]->right_out_port = 'R';
		}
		else
		{
			circuit.ext_out_ix = gate_ix;
			circuit.ext_out_port = 'R';
		}

		++port;
	}

	return result;
}

void search(int max_size, string& input, string& target)
{
	for(int size = 1; size <= max_size; ++size)
	{
		cout << "Start search with circuit size " << size << endl;

		long long count = 0;
		Circuit circuit;

		for(int gate_count = 0; gate_count < size; ++gate_count)
		{
			circuit.add_gate(0, '-', 0, '-', 0, '-', 0, '-');
		}

		elist input_list;
		init_port_list(input_list, size);

		Permutation permutation(input_list.begin(), input_list.end());

		elist* output_list = permutation.next();

		while(output_list != 0)
		{
			bool valid = cfg_circuit(circuit, *output_list);
			delete output_list;

			if(valid)
			{
				string output;
				circuit.reset();
				circuit.eval(input, output);

				if(output == target)
				{
					cout << "Found solution:" << endl << endl;
					circuit.print();
					return;
				}

				++count;

				if(count % 10000 == 0)
				{
					cout << "Evaluated " << count << " circuits." << endl;
				}
			}

			output_list = permutation.next();
		}

		cout << "No solution found." << endl;
	}
}

void test()
{
	Circuit c;
	c.add_gate(0, 'X', 2, 'L', 0, 'X', 1, 'L');
	c.add_gate(0, 'R', 2, 'R', 2, 'L', 2, 'R');
	c.add_gate(1, 'L', 1, 'R', 0, 'R', 1, 'R');
	c.set_external(0, 'L', 0, 'L');
	string in("01202101210201202");
	string out;
	c.eval(in, out);

	c.print();
	cout << endl;
	cout << in << endl;
	cout << out << endl;
}

int main(int argc, char** argv)
{
	init_gate(gate);

	if(argc >= 4)
	{
		int max_size = atoi(argv[1]);
		string input(argv[2]);
		string target(argv[3]);
		search(max_size, input, target);
	}
	else
	{
		cout << "usage: max_size in_string out_string" << endl;
	}

	return 0;
}
