#include "Encrypt.h"
#include <fstream>
using namespace std;

int main() {
	string infilename;
	getline(cin, infilename);
	ifstream in(infilename, ios::binary);
	if (!in) {
		cout << infilename << "²»´æÔÚ!" << endl;
	}
	string outfilename;
	getline(cin, outfilename);
	EncryptData data;
	in >> data;
	data.Decrypt("abc");
	ofstream out(outfilename, ios::binary);
	out << data;
	return 0;
}

