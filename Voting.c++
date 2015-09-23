#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <queue>
#include "Voting.h"
using namespace std;


// read in istream& s, parse into number of candidates, candidates as strings, and ballots as ints
void read_case(istream& s,vector<Candidate> &cand_names,vector<Ballot>& ballot_lines) {
	// determine number of candidates
	string num_candidates;
	getline(s, num_candidates);
	int num_cand = atoi(num_candidates.c_str());

	// parse candidate names
	for (int i =0;i < num_cand;i++) {
		string candidate;
		getline(s,candidate);
		Candidate new_cad;
		new_cad.cand_code=i;
		new_cad.name = candidate.c_str();
		new_cad.eliminated = false;
		cand_names.push_back(new_cad);
	}
	// read ballots
	string next_line;
	bool check = !getline(s,next_line).eof();
	while (check &&  (!next_line.empty())) {
		Ballot new_ballot;
		new_ballot.line = next_line;
		istringstream sin(next_line);
		for (int i =0; i< num_cand;i++) {
			
			int k;
			sin >> k;
			new_ballot.counter.push(k);
		}
		ballot_lines.push_back(new_ballot);
		check = !getline(s,next_line).eof();
	}
}

void eval_ballots(vector<Candidate> cand_names, vector<Ballot> ballot_lines, ostream& o){
		for (unsigned int k=0; k < ballot_lines.size(); k++){
			cand_names.at(ballot_lines.at(k).counter.front()-1).count_rows.push_back(k);

		}
		
		//unordered_map<int,int> loser_name;
		bool found_winner = false;
		
		while (!found_winner) {
			int min = ballot_lines.size();
			int max = 0;
			// check for winner , also find the minimum vote 
			for  (unsigned int m=0; m<cand_names.size(); m++){
			 	if (cand_names.at(m).count_rows.size() > ballot_lines.size()/2){
					o <<	cand_names.at(m).name << endl;	
			 		found_winner= true;
			 		break;
			 	}
			 	if (cand_names.at(m).count_rows.size() < (unsigned)min) {
			 		if (!cand_names.at(m).eliminated) {
			 			min = cand_names.at(m).count_rows.size();
			 		}
			 		
			 	}
			 	if (cand_names.at(m).count_rows.size() > (unsigned)max) {
			 			max = cand_names.at(m).count_rows.size();
			 	}
			 	
			 	
	     	}
	  		
	     	
	     	if ((min==max)&&(!found_winner)){
	     		//check for the tie
	     		for ( unsigned int i =0; i <cand_names.size();i++) {
	     			if (!cand_names.at(i).eliminated){
	     				o << cand_names.at(i).name << endl;
	     			}
	     		}
	     		found_winner = true;
	     		
	     	}

			// go next
			if (found_winner) {
	     		break;
	     	}

	     	vector<int> this_round_losers;
	     	//cout << "this round lose size " << this_round_losers.size() << endl;
	     	for (unsigned int i = 0; i < cand_names.size();i++) {
	     		// find all the loser for this round
	     		if ((cand_names.at(i).count_rows.size()==(unsigned)min)&&(!cand_names.at(i).eliminated)) {
	     		// reduce number of still running cadidate
	     			cand_names.at(i).eliminated=true;

	     			this_round_losers.push_back(i);
	     		}
	     	}
	   
	      	// for (int k1 = 0; k1 < this_round_losers.size(); k1++) {
	     	// 	cout << "name of the loser " << cand_names.at(this_round_losers.at(k1)).name << endl;
	     	// }
	     	for (unsigned int k =0; k < this_round_losers.size();k++){

	     		for (unsigned int j=0; j < cand_names.at(this_round_losers.at(k)).count_rows.size();j++) {
	     		
	     			int row = cand_names.at(this_round_losers.at(k)).count_rows.at(j);
	     			// take out the name of the next ballot in the row
	     			ballot_lines.at(row).counter.pop();
	     			int next_in_line = cand_names.at(ballot_lines.at(row).counter.front()-1).cand_code;
	     			// if the name of the next ballot is already in the loser list, dicard it until find the name that
	     			// is not in the loser list
	     		
	     			while ((cand_names.at(next_in_line).eliminated)||(cand_names.at(next_in_line).count_rows.size()==(unsigned) min)) {
	     			//	ssin.at(row) >> ballot_lines.at(k).counter;
	     				ballot_lines.at(row).counter.pop();
	     				next_in_line = cand_names.at(ballot_lines.at(row).counter.front()-1).cand_code;

						
					}

					//add the row to the the vector of rows for the name 
					cand_names.at(next_in_line).count_rows.push_back(row);
					//ballot_lines.at(row).counter+=2;
						
	     		}
	     	}
	    }

}

// read in istream& s, determine number of test cases and call read_case for each test case
void voting_read(istream& s, ostream& o){
	string test_cases;
	getline(s, test_cases);
	string blank_line;
	int t_cases = atoi(test_cases.c_str());
	getline(s,blank_line);
	for (int i =0 ; (int)i < t_cases; i++) {
		vector<Candidate> Cadidates;
		vector<Ballot> ballot_lines;
		read_case(s,Cadidates,ballot_lines);
	    eval_ballots(Cadidates, ballot_lines, o);
		if ((int)i < t_cases -1)
			o << endl;
	}
	
}
