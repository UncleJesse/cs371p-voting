
#ifndef VOTING_H
#define VOTING_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Candidate {
	int cand_code;
	std::string name;
	vector <int> count_rows;
	bool eliminated;

};
struct Ballot {
	string line;
	queue<int>counter;
};

void read_case(istream& s,vector<Candidate> &cand_names,vector<Ballot>& ballot_lines);

void eval_ballots(vector<Candidate> cand_names, vector<Ballot> ballot_lines, ostream& o);

void voting_read(istream& s, ostream& o);

#endif
