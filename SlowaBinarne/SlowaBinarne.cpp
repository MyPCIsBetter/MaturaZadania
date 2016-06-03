// SlowaBinarne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include<vector>
using namespace std;

int main()
{
	string pathToDirectory = _getcwd(NULL, 0);
	ifstream slowa(pathToDirectory+"\\slowa.txt");
	if (slowa) {
		vector<string> linesWithMaxSizeBlock;
		string line;
		int countWordsWithMoreZeros = 0;
		int countWordsWithTwoBlocks = 0;
		int maxSizeOfZeroBlock = 0;
		while (getline(slowa, line)) {
			int numberOfZeros = 0;
			int numberOfOnes = 0;
			int numberOfBlocks = 1;
			int zeroBlockSize = 0;
			char previousCharacter = NULL;

			for (int x = 0; x < line.size(); x++) {
				//cout << line.size() << ", " << x << endl;
				if (line[x] == '0')
				{
					zeroBlockSize++;
				}

				if (line[x] == '0') {
					numberOfZeros++;
				} 
				else if(line[x] == '1')
				{
					numberOfOnes++;
				}

				if (previousCharacter == NULL) {
					previousCharacter = line[x];
				}
				else
				{
					if (previousCharacter != line[x]) {
						zeroBlockSize = 0;
						numberOfBlocks++;
						previousCharacter = line[x];
					}

					if (zeroBlockSize == maxSizeOfZeroBlock) {
						linesWithMaxSizeBlock.push_back(line);
					}
					else if (zeroBlockSize > maxSizeOfZeroBlock) {
						maxSizeOfZeroBlock = zeroBlockSize;
						linesWithMaxSizeBlock.clear();
						linesWithMaxSizeBlock.push_back(line);
					}
				}
			}

			if (numberOfZeros > numberOfOnes) {
				countWordsWithMoreZeros++;
			}

			if (numberOfBlocks == 2) {
				countWordsWithTwoBlocks++;
				//cout << line << endl;
			}

		}

		cout << "4.1: " << countWordsWithMoreZeros << endl << endl;
		cout << "4.2: " << countWordsWithTwoBlocks << endl << endl;

		cout << "4.3: \n" << maxSizeOfZeroBlock << endl;
		for (int a = 0; a < linesWithMaxSizeBlock.size(); a++) {
			cout << linesWithMaxSizeBlock[a] << endl;
		}
		/*while (getline(slowa, line)) {
			int zeroBlockSize = 0;
			for (int x = 0; x < line.size(); x++) {
				if (line[x] == '0')
				{
					zeroBlockSize++;
				}
				else {
					zeroBlockSize = 0;
				}

				if (zeroBlockSize == maxSizeOfZeroBlock) {
					cout << line << "\n";
				}
			}
		}*/
	}

	system("pause");
    return 0;
}

