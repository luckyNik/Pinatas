#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    int size = 0;
    do
    {
        cout << "Enter the amount of pinatas (>= 1): ";
        cin >> size;
    } while (size < 1);

    vector<int> pinataValues(size, 1);

    for (int i = 0; i < size; i++)
    {
        cout << "Enter the amount of candies for pinata number " << i << ": ";
        cin >> pinataValues[i];
    }

    if (size == 1)
    {
        cout << "Max candies you can get: " << pinataValues[0];
        return 0;
    }

    // dynamic programming array, where subproblem solutions will be stored
    // rangeMax[i][j] corresponds to maximum value you could get by smashing pinatas i to j inclusive
    vector<vector <int>> rangeMax(size, vector<int>(size, 0)); 
    
    // for all ranges with length 1 we have no variation, just assign values
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            rangeMax[i][i] = pinataValues[i] * pinataValues[i + 1];
        }
        else if (i == (size - 1))
        {
            rangeMax[i][i] = pinataValues[i] * pinataValues[i - 1];
        }
        else
        {
            rangeMax[i][i] = pinataValues[i - 1] * pinataValues[i] * pinataValues[i + 1];
        }
    }

    // then calculate for all ranges of length 2, 3, ..., size
    for (int lenIncr = 1; lenIncr < size; lenIncr++)
    {
        int length = lenIncr + 1;
        pair <int, int> currentRange = make_pair(0, lenIncr);
        for (int i = 0; i < size - lenIncr; i++)
        {
            int boundaryLeft = 1;
            int boundaryRight = 1;
            if (currentRange.first != 0)
            {
                boundaryLeft = pinataValues[currentRange.first - 1];
            }
            if (currentRange.second != (size - 1))
            {
                boundaryRight = pinataValues[currentRange.second + 1];
            }

            // try every k as element we will pick last
            for (int k = currentRange.first; k <= currentRange.second; k++)
            {
                int rightMax = 0;
                int leftMax = 0;
                int possibleValue = 0;
                if (k > 0)
                {
                    leftMax = rangeMax[currentRange.first][k - 1];
                }
                if (k < (size - 1))
                {
                    rightMax = rangeMax[k + 1][currentRange.second];
                }
                possibleValue = rightMax + leftMax + pinataValues[k] * boundaryRight * boundaryLeft;
                if (possibleValue > rangeMax[currentRange.first][currentRange.second])
                {
                    rangeMax[currentRange.first][currentRange.second] = possibleValue;
                }
            }
            currentRange.first++;
            currentRange.second++;
        }
    }

    cout << "Maximum possible candies: " << rangeMax[0][size - 1];
    return 0;
}