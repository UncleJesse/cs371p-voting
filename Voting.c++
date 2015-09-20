#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

struct Candidate {

	string name;
	vector <int> count_rows;


};
struct Ballot {
	string line;
	int counter;
};
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
		new_cad.name = candidate;
		cand_names.push_back(new_cad);
	}
	// read ballots
	string next_line;
	bool check = getline(s,next_line);
	while (check &&  (next_line.size()>0)) {
		Ballot new_ballot;
		new_ballot.line = next_line;
		new_ballot.counter =0;
		ballot_lines.push_back(new_ballot);
		check = getline(s,next_line);
	}

	string vote;
	int next_vote = atoi(vote.c_str());



	for(int j =0; j < ballot_lines.size();j++) {
		cout << ballot_lines.at(j).line.size() << endl;
	}



}

void eval_ballots(vector<Candidate> cand_names, vector<Ballot> ballot_lines){
		
		for (int k=0; k < ballot_lines.size(); k++){
			cand_names.at(ballot_lines.at(k).line.at(ballot_lines.at(k).counter)-48-1).count_rows.push_back(k);
			ballot_lines.at(k).counter+=2;
		}
		int still_running_cad = cand_names.size();
		unordered_map<string,int> loser_name;
		
		bool found_winner = false;
		// check for winner 
		while (!found_winner) {
			int min = ballot_lines.size();
			for  (int 	m=0; m<cand_names.size(); m++){
			 	if (cand_names.at(m).count_rows.size() > ballot_lines.size()/2){
					cout << cand_names.at(m).count_rows.size() << endl;
					cout <<	cand_names.at(m).name << endl;	
			 		found_winner= true;
			 		break;
			 	}
			 	if (cand_names.at(m).count_rows.size() < min) {
			 		if (loser_name[cand_names.at(m).name] != 1)
			 			min = cand_names.at(m).count_rows.size();
			 	}
			 	
	     	}
	  
	     	if ((ballot_lines.size()%still_running_cad==0)&&(ballot_lines.size()/still_running_cad==min)){
	     		//check for the tie
	     		cout << "may be tie " << endl;
	     	}
			// go next
			if (found_winner) {
	     		break;
	     	}
	     	vector<int> this_round_losers;
	     	for (int i = 0; i < cand_names.size();i++) {
	     		// find all the loser for this round
	     		if (cand_names.at(i).count_rows.size()==min) {
	     			pair <string,int > new_pair(cand_names.at(i).name,1);
	     			// save the name of the loser into the list of losers
	     			loser_name.insert(new_pair);	
	     			// reduce number of still running cadidate
	     			--still_running_cad;
	     			this_round_losers.push_back(i);
	     		}
	     	}
	     	for (int k =0; k < this_round_losers.size();k++){
	     		for (int j=0; j < cand_names.at(this_round_losers.at(k)).count_rows.size();j++) {
	     			
	     			int row = cand_names.at(this_round_losers.at(k)).count_rows.at(j);
	     			// take out the name of the next ballot in the row
	     			string next_in_line = cand_names.at(ballot_lines.at(row).line.at(ballot_lines.at(row).counter)-48-1).name;
	     			// if the name of the next ballot is already in the loser list, dicard it until find the name that
	     			// is not in the loser list
	     			while (loser_name[next_in_line]==1) {
	     				ballot_lines.at(row).counter+=2;
	     				next_in_line = cand_names.at(ballot_lines.at(row).line.at(ballot_lines.at(row).counter)-48-1).name;
					}
					//add the row to the the vector of rows for the name 
					cand_names.at(ballot_lines.at(row).line.at(ballot_lines.at(row).counter)-48-1).count_rows.push_back(row);
					ballot_lines.at(row).counter+=2;
						
	     		}
	     	}
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
		vector<Candidate> Cadidates;
		vector<Ballot> ballot_lines;
		read_case(s,Cadidates,ballot_lines);
		
		eval_ballots(Cadidates, ballot_lines);
		cout << endl;
	}
	
}

