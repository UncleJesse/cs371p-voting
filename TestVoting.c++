#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <queue>
#include "Voting.h"
#include "gtest/gtest.h"

using namespace std;

TEST(VotingFixture, read_case){
	istringstream s("3\nA\nB\nC\n1 2 3\n1 3 2\n2 3 1\n");
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	
	ASSERT_EQ(3, cand_names.size());
	ASSERT_EQ(3, ballot_lines.size());
	
	ASSERT_EQ("A", cand_names.at(0).name);
	ASSERT_EQ(0, cand_names.at(0).cand_code);
	ASSERT_EQ(false, cand_names.at(0).eliminated);
	ASSERT_EQ("B", cand_names.at(1).name);
	ASSERT_EQ(1, cand_names.at(1).cand_code);
	ASSERT_EQ(false, cand_names.at(1).eliminated);
	ASSERT_EQ("C", cand_names.at(2).name);
	ASSERT_EQ(2, cand_names.at(2).cand_code);
	ASSERT_EQ(false, cand_names.at(2).eliminated);

	ASSERT_EQ("1 2 3", ballot_lines.at(0).line);
	ASSERT_EQ(3,ballot_lines.at(0).counter.size());
	ASSERT_EQ(1,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(2,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(3,ballot_lines.at(0).counter.front());
	
	ASSERT_EQ("1 3 2", ballot_lines.at(1).line);
	ASSERT_EQ(3,ballot_lines.at(1).counter.size());
	ASSERT_EQ(1,ballot_lines.at(1).counter.front());
	ballot_lines.at(1).counter.pop();
	ASSERT_EQ(3,ballot_lines.at(1).counter.front());
	ballot_lines.at(1).counter.pop();
	ASSERT_EQ(2,ballot_lines.at(1).counter.front());

	ASSERT_EQ("2 3 1", ballot_lines.at(2).line);
	ASSERT_EQ(3,ballot_lines.at(2).counter.size());
	ASSERT_EQ(2,ballot_lines.at(2).counter.front());
	ballot_lines.at(2).counter.pop();
	ASSERT_EQ(3,ballot_lines.at(2).counter.front());
	ballot_lines.at(2).counter.pop();
	ASSERT_EQ(1,ballot_lines.at(2).counter.front());

}

TEST(VotingFixture, read_case_2){
	istringstream s("2\nA\nB\n1 2\n1 2\n2 1\n");
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);

	ASSERT_EQ(2, cand_names.size());
	ASSERT_EQ(3, ballot_lines.size());
	
	ASSERT_EQ("A", cand_names.at(0).name);
	ASSERT_EQ(0, cand_names.at(0).cand_code);
	ASSERT_EQ(false, cand_names.at(0).eliminated);

	ASSERT_EQ("B", cand_names.at(1).name);
	ASSERT_EQ(1, cand_names.at(1).cand_code);
	ASSERT_EQ(false, cand_names.at(1).eliminated);

	ASSERT_EQ("1 2", ballot_lines.at(0).line);
	ASSERT_EQ(2,ballot_lines.at(0).counter.size());
	ASSERT_EQ(1,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(2,ballot_lines.at(0).counter.front());

	ASSERT_EQ("1 2", ballot_lines.at(1).line);
	ASSERT_EQ(2,ballot_lines.at(1).counter.size());
	ASSERT_EQ(1,ballot_lines.at(1).counter.front());
	ballot_lines.at(1).counter.pop();
	ASSERT_EQ(2,ballot_lines.at(1).counter.front());

	ASSERT_EQ("2 1", ballot_lines.at(2).line);
	ASSERT_EQ(2,ballot_lines.at(2).counter.size());
	ASSERT_EQ(2,ballot_lines.at(2).counter.front());
	ballot_lines.at(2).counter.pop();
	ASSERT_EQ(1,ballot_lines.at(2).counter.front());
}

TEST(VotingFixture, read_case_3){
	istringstream s("5\nA\nB\nC\nD\nE\n1 2 3 4 5\n");
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	
	ASSERT_EQ(5, cand_names.size());
	ASSERT_EQ(1, ballot_lines.size());
	
	ASSERT_EQ("A", cand_names.at(0).name);
	ASSERT_EQ(0, cand_names.at(0).cand_code);
	ASSERT_EQ(false, cand_names.at(0).eliminated);

	ASSERT_EQ("B", cand_names.at(1).name);
	ASSERT_EQ(1, cand_names.at(1).cand_code);
	ASSERT_EQ(false, cand_names.at(1).eliminated);


	ASSERT_EQ("C", cand_names.at(2).name);
	ASSERT_EQ(2, cand_names.at(2).cand_code);
	ASSERT_EQ(false, cand_names.at(2).eliminated);


	ASSERT_EQ("D", cand_names.at(3).name);
	ASSERT_EQ(3, cand_names.at(3).cand_code);
	ASSERT_EQ(false, cand_names.at(3).eliminated);


	ASSERT_EQ("E", cand_names.at(4).name);
	ASSERT_EQ(4, cand_names.at(4).cand_code);
	ASSERT_EQ(false, cand_names.at(4).eliminated);

	ASSERT_EQ("1 2 3 4 5", ballot_lines.at(0).line);
	ASSERT_EQ(5,ballot_lines.at(0).counter.size());
	ASSERT_EQ(1,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();	
	ASSERT_EQ(2,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(3,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(4,ballot_lines.at(0).counter.front());
	ballot_lines.at(0).counter.pop();
	ASSERT_EQ(5,ballot_lines.at(0).counter.front());

	
}

TEST(VotingFixture, eval_ballots){
	istringstream s("4\nA\nB\nC\nD\n4 3 2 1\n3 2 4 1\n4 3 1 2\n1 2 4 3\n2 1 4 3\n2 3 4 1\n1 2 3 4\n");
	ostringstream o;
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	eval_ballots(cand_names, ballot_lines, o);
	ASSERT_EQ("B\n",o.str());
}

TEST(VotingFixture, eval_ballots2){
	istringstream s("4\nA\nB\nC\nD\n4 3 2 1\n4 2 1 3\n4 3 1 2\n4 2 1 3\n2 1 4 3\n2 3 4 1\n1 2 3 4\n");
	ostringstream o;
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	eval_ballots(cand_names, ballot_lines, o);
	ASSERT_EQ("D\n",o.str());
}

TEST(VotingFixture, eval_ballots3){
	istringstream s("5\nA\nB\nC\nD\nE\n4 3 2 1 5\n5 2 4 1 3\n5 3 1 2 4'\n");
	ostringstream o;
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	eval_ballots(cand_names, ballot_lines, o);
	ASSERT_EQ("E\n",o.str());
}

TEST(VotingFixture, voting_read){
	istringstream s("1\n\n4\nA\nB\nC\nD\n4 3 2 1\n3 2 4 1\n4 3 1 2\n1 2 4 3\n2 1 4 3\n2 3 4 1\n1 2 3 4\n");
	ostringstream o;
	voting_read(s,o);
	ASSERT_EQ("B\n",o.str());
}
TEST(VotingFixture, voting_read_2){
	istringstream s("2\n\n4\nA\nB\nC\nD\n4 3 2 1\n3 2 4 1\n4 3 1 2\n1 2 4 3\n2 1 4 3\n2 3 4 1\n1 2 3 4\n\n5\nA\nB\nC\nD\nE\n4 3 2 1 5\n5 2 4 1 3\n5 3 1 2 4'\n");
	ostringstream o;
	voting_read(s,o);
	ASSERT_EQ("B\n\nE\n",o.str());
}
TEST(VotingFixture, voting_read_3){
	istringstream s("3\n\n1\nA\n1\n\n4\nA\nB\nC\nD\n4 3 2 1\n4 2 1 3\n4 3 1 2\n4 2 1 3\n2 1 4 3\n2 3 4 1\n1 2 3 4\n\n2\nA\nB\n1 2\n2 1\n");
	ostringstream o;
	voting_read(s,o);
	ASSERT_EQ("A\n\nD\n\nA\nB\n",o.str());
}
