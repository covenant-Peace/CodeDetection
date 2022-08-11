#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_CODE_SIZE = 250;

void readCode(ifstream& infile, int list[], int& length, bool& lenCodeOk);
void compareCode(ifstream& infile, ofstream& outfile, const int list[], int length);

int main()
{
	int codeArray[MAX_CODE_SIZE];
	int codeLength;
	bool lengthCodeOk;

	ifstream incode;
	ofstream outcode;

	char inputFile[51];
	char outputFile[51];

	cout << "Enter the input file name: " << endl;
	cin >> inputFile;

	incode.open(inputFile, fstream::in);
	if (!incode)
	{
		cout << "Cannot Open the input file." << endl;
		return 1;
	}

	cout << "Enter the output file name: " << endl;
	cin >> outputFile;

	outcode.open(outputFile);

	readCode(incode, codeArray, codeLength, lengthCodeOk);

	if (lengthCodeOk)
		compareCode(incode, outcode, codeArray, codeLength);
	else
		cout << "Length of the secret code must be " << MAX_CODE_SIZE << endl;

	incode.close();
	outcode.close();

	return 0;
}

void readCode(ifstream& infile, int list[], int& length, bool& lenCodeOk)
{

	lenCodeOk = true;

	infile >> length;

	if (length > MAX_CODE_SIZE)
	{
		lenCodeOk = false;
		return;
	}

	for (int i = 0; i < length; i++)
		infile >> list[i];
}

void compareCode(ifstream& infile, ofstream& outfile, const int list[], int length)
{
	int length2;
	int digit;
	bool codeOk;

	codeOk = true;

	infile >> length2;

	if (length != length2)
	{
		cout << "The original code and its copy are not of the same length." << endl;
		return;
	}
	outfile << "Code Digit      Code Digit Copy" << endl;

	for (int i = 0; i < length; i++)
	{
		infile >> digit;
		outfile << setw(5) << list[i] << setw(17) << digit;

		if (digit != list[i])
		{
			outfile << " Code digits are not the same" << endl;
			codeOk = false;
		}
		else
			outfile << endl;
	}

	if (codeOk)
		outfile << "Message transmitted OK." << endl;
	else
		outfile << "Error in transmission. " << "retransmit!!" << endl;

}