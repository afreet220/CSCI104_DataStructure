#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

struct stu {
	string stuName;
	int stuSkill;
};

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << endl << "plz provide input" << endl;
		return 1;
	}
	
	ifstream mData;
	mData.open(argv[1]);
	if (mData.fail()) {
		cout << endl << "Can't open target file plz start over" << endl;
		return 1;
	}
	
	int number_of_student = 0;
	int total_skill = 0;
	unordered_multimap<int,string> storage;
	queue<stu> orderQ;    
	
	mData >> number_of_student;
	mData.ignore(256,'\n');
	
	while (true) {
		string line;
		getline(mData,line,'\n');
		if (mData.fail()) {
			break;
		}
		string name;
		int skill;
		stringstream lstream;
		lstream << line;
		getline(lstream,name,' ');
		lstream >> skill;
		total_skill += skill;
		pair<int,string> toInsert (skill,name) ;
		stu stuInsert;
		stuInsert.stuName = name;
		stuInsert.stuSkill = skill;
		storage.insert(toInsert);
		orderQ.push(stuInsert);		
	}
	
	const int avg_team_skill = total_skill / (number_of_student/2);
	
	while (!orderQ.empty()) {
		string sName = orderQ.front().stuName;
		if (storage.find(avg_team_skill-orderQ.front().stuSkill) == storage.end()) {
			cout<<"It's impossible to assign"<<endl;
			break;
		}
		cout<<sName<<" "<<storage.find(avg_team_skill - orderQ.front().stuSkill)->second<<endl;		
		orderQ.pop();
	}
	
	return 0;	
}