#include <iostream>
#include "CTrainer.h"
#include "CRoad.h"
#include "CHelper.h"
#include "Types.h"

#include <ctime>

using namespace std;

int main(void) {
	CHelper::getRoadID();
	CMidFileHandler c;
	CTrainer *trainer = new CTrainer();
	Date_t date = {2012,11,04};
	//trainer->addResultFileToBeMerged("D:/Hello/dat/0_result_weekday_good_weather-2013_11_01...2013_11-01.resd");
	trainer->setPreDataPath(string("D:/Hello/dat/"));
	trainer->setDumpFilePath("../");
	trainer->addDayToBeTrained(date);
	trainer->start();
	trainer->getDaysToBeTrained(cout);
	time_t start = clock();
	trainer->start();

	cout << " Total Time Consumed:"
		<< (clock() - start) / (CLOCKS_PER_SEC/1000)
		<<"ms."
		<< endl;

	cout << "Press Enter to free memory." << endl;
	cin.get();
	cout << "start free memory..." << endl;
	start = clock();
	delete trainer;
	cout << " Total Time Consumed:"
		<< (clock() - start) / (CLOCKS_PER_SEC/1000)
		<<"ms."
		<< endl;
	cout << "Press Enter to quit." << endl;
	cin.get();
	return 0;
}

/*
//test memory

#include <vector>
using namespace std;
class T {
public:
	vector<long long int>  iv;
	T() {
	}
	void push(long long int num) {
		for(long long int i = 0; i < num;i++)
		iv.push_back(i);
	}
	void clear() {
		iv = vector<long long int>();
	}
};


int main(void) {

	cout <<
		sizeof(char) << endl << //1
		sizeof(short) << endl << //2
		sizeof(int) << endl << //4 
		sizeof(long int) << endl << //4 
		sizeof(long long int) << endl << //8
		sizeof(float) << endl << //4
		sizeof(double) << endl << //8
		sizeof(__int16) << endl << //
		sizeof(__int32) << endl << //
		sizeof(__int64) << endl << //
		sizeof(void *)  //8 in amd64 but 4 in x86_32bit
		<< endl;

	bool testVM = false;
	if(testVM) {
		T t;
		long long int M = 128*1024;
		long long int G = 1024*M;
		long long int d_size = 1*G;
		t.push(d_size);
		cout << "D_size " << d_size << " o_size " << t.iv.size() << endl;
		std::cout << "it works" << std::endl;
		getchar();
		t.clear();
		cout << "Memory freed." << endl;
	}

	getchar();
	return 0;
}


*/
