#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

TEST(VotingFixture, read_case){
	istringstream s("1\n\n3\nA\nB\nC\n1 2 3\n1 3 2\n2 3 1");
	vector<Candidate> cand_names;
	vector<Ballot> ballot_lines;
	read_case(s, cand_names, ballot_lines);
	ASSERT_EQ(A, cand_names.at(0).name);
	ASSERT_EQ(1, cand_names.at(0).cand_code);
	ASSERT_EQ(false, cand_names.at(0).eliminated);
	ASSERT_EQ()
	

}