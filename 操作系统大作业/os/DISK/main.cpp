/*************************************************************************
    > File Name:     main.cpp
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013年05月14日 星期二 22时12分51秒
 ************************************************************************/
#include <iostream>
#include "Block.h"
#include "DiskManager.h"

#include <vector>
#include <stdio.h>
using namespace std;
int getOpt();

int main(void) {

	int size, groupS = 8;
	cout << "Please enter disk size and group size"
		"ctrl-D to commit\n" ;
	cin >> size >> groupS;

	cout << "disk inited with size of " << size << " and group size of " << groupS << endl;

	DiskManager dm(size, groupS);
	char opt;
	dm.showStatus();
	cout << "r for request, f for free, q for quit\n";
	while (cin >> opt) {
		switch (opt) {
			case 'r':
				cin >> size;
				delete dm.request(size);
				dm.showStatus();
				break;
			case 'f':
				cin >> size;
				dm.free(size);
				dm.showStatus();
				break;
			case 'q':
				goto end;
				break;
			default:
				cout << "Ty again or Ctrl-D to exit" << endl;
		}

		cout << "r for request, f for free, q for quit\n";

	}
end:
	cout << "thank you" << endl;


	/*
	cout << "--------------------------\n";
	DiskManager dm(128);
	dm.showStatus();
	int len = dm.request(100)->size();
	cout << "request " << len << endl;
	dm.showStatus();
	vector<int> *r = new vector<int>();
	for(int i = 0; i < 50; i++) {
		r->push_back(i);
	}

	cout << "free 0-49\n";
	dm.free(r);
	dm.showStatus();
	*/
	

	return 0;
}
