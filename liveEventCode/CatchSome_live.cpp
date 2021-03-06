#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
#define TESTSETFILE "template.txt"

const bool debug = true;
vector<int> bucketColors(vector<int> dColors) {
    int lastColor = 0;
    vector<int> buckets(1000, 0); //There can only be 1000 colors: 1 <= A(i) <= 1000
    for(int i = 0; i < dColors.size(); ++i) {
        buckets[dColors[i]]++;
        if (dColors[i] > lastColor ) {
            lastColor = dColors[i];
        }
    }
    buckets.resize(lastColor + 1);
    return buckets;
}

int runTestCase(ifstream& inFile) {
    int numberOfDogs, dogsToObserve;
    int timeTaken = 0;
    inFile >> numberOfDogs >> dogsToObserve;
    vector<int> dogPositions, dogColors;
    dogPositions.reserve(numberOfDogs);
    dogColors.reserve(numberOfDogs);
    for(int i = 0; i < numberOfDogs; ++i) {
        int buffer;
        inFile >> buffer;
        dogPositions.push_back(buffer);
    }
    for(int j = 0; j < numberOfDogs; ++j) {
        int buffer;
        inFile >> buffer;
        dogColors.push_back(buffer);
    }
    vector<int> buckets = bucketColors(dogColors);
    vector<int> descendingColors;
    descendingColors.reserve(dogsToObserve);
    descendingColors.push_back(numberOfDogs + 1);
    int observeCount = 0;
    while (observeCount <= dogsToObserve) {
        int commonColor = 0;
        for(int j = 1; j < buckets.size(); ++j) {
            if ((buckets[j] > commonColor) && (buckets[j] < buckets[descendingColors.back()])) {
                commonColor = j;
            }
        }
        descendingColors.push_back(commonColor);
        observeCount += buckets[commonColor];
        if (observeCount == 1) {
            int maxPosition = 0;
            for(int m = 0; m < numberOfDogs; ++m) {
                timeTaken += 2*dogPositions[m];
                if (dogPositions[m] > maxPosition) {
                    maxPosition = dogPositions[m];
                }
            }
            timeTaken -= maxPosition;
            return timeTaken;
        }
    }
    descendingColors.erase(descendingColors.begin());
    int lastPosition = 0;
    for (int n = 0; n < numberOfDogs; ++n) {
        

    }
    return;
}

void main() {
    int totalTestCases;
    int testCase = 0;
    ifstream testSetInput;
    testSetInput.open(TESTSETFILE);
    if (testSetInput.is_open()) {
        testSetInput >> totalTestCases;
    }
    else {
        cout << "Unable to open file " << TESTSETFILE << endl;
        return;
    }
    while(testCase <= totalTestCases) {
        cout << "Case #" << testCase << ": " << runTestCase(testSetInput) << endl;
        ++testCase;
    }
    testSetInput.close();
    return;
}