#ifndef VOTING_H
#define VOTING_H
#include <istream>
#include <string>
#include <vector>

using namespace std;

void read_case(istream& s,vector<Candidate> &cand_names,vector<Ballot>& ballot_lines);

void eval_ballots(vector<Candidate> cand_names, vector<Ballot> ballot_lines);

void voting_read(istream& s);

#endif
