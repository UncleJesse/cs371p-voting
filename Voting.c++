#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <vector>

using namespace std;

// read in istream& s, parse into number of candidates, candidates as strings, and ballots as ints
void read_case(istream& s,vector<string> &cand_names,vector<string>& ballot_lines) {
	
	// determine number of candidates
	string num_candidates;
	getline(s, num_candidates);
	int num_cand = atoi(num_candidates.c_str());

	// parse candidate names
	for (int i =0;i < num_cand;i++) {
		string candidate;
		getline(s,candidate);
		cand_names.push_back(candidate);
	}
	// read ballots
	string next_line;
	bool check = getline(s,next_line);
	while (check &&  (next_line.size()>0)) {
		ballot_lines.push_back(next_line);
		check = getline(s,next_line);
	}

	string vote;
	int next_vote = atoi(vote.c_str());



	for(int j =0; j < ballot_lines.size();j++) {
		cout << ballot_lines.at(j).size() << endl;
	}



}

// read in istream& s, determine number of test cases and call read_case for each test case
void voting_read(istream& s){
	string test_cases;
	getline(s, test_cases);
	cout << test_cases << endl << endl;
	string blank_line;
	int t_cases = atoi(test_cases.c_str());
	getline(s,blank_line);
	for (int i =0 ; i < t_cases; i++) {
		vector<string> cand_names;
		vector<string> ballot_lines;
		read_case(s,cand_names,ballot_lines);
		
		int vote_count[cand_names.size()];
		int* temp = vote_count;
		for (int j=0; j < cand_names.size(); j++) {
			*temp =0;
			++temp;
		}
		for (int k=0; k < ballot_lines.size(); k++){
			vote_count[ballot_lines.at(k).at(0)-48-1]++;
		}
		for (int t = 0; t < cand_names.size(); t++) {
			cout << vote_count[t] << endl; 
		}
		cout << endl;
	}
	
}

