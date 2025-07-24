#include <iostream>
#include <fstream>
using namespace std;


int main(){
	ifstream inPDF;
	string filename = "/home/aaron/Downloads/randomwords.pdf";
	string line;

	inPDF.open(filename);

	if(inPDF.is_open()){
		while(getline(inPDF, line)){
			cout << line << endl;
		}
	}
	else{
		exit(1);
	}

	return 0;
}
