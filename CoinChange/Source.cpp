#include <iostream>
#include <vector>

using namespace std;

int printWaysRec(vector<int> coins, int numCoins, int totalSum, vector<int>& track)
{
    // if total sum is zero, then there's one (more) way for coins exchange
    // that's the way not to include other coins
    if (totalSum == 0) {
        for (auto& coin : track) {
            cout << coin << ' ';
        }

        cout << endl;

        return 1;
    }

    // if total sum is negative or there are no coins then there's no way for coins exchange
    if (totalSum < 0 || numCoins <= 0) {
        return 0;
    }

    // here we exclude last coin
    int waysWithoutLastCoin = printWaysRec(coins, numCoins - 1, totalSum, track);

    // here we DO NOT exclude last coin and thus we're including it once,
    // subtracting it's value from total sum
    track.push_back(coins[numCoins - 1]);
    int waysWithLastCoin = printWaysRec(coins, numCoins, totalSum - coins[numCoins - 1], track);
    track.pop_back();

    return waysWithoutLastCoin + waysWithLastCoin;
}

int printWaysIterative(vector<int>& coins, int totalSum)
{
    vector<int> track;
    vector<vector<int>> matrix(totalSum + 1, vector<int>(coins.size()));

    // Initially entire matrix is filled with zeros.
    // Base case - for sum = 0 for any set of coins - is 1 way
    for (auto &zeroAmountRowItem : matrix[0]) {
        zeroAmountRowItem = 1;
    }

    for (int sum = 1; sum <= totalSum; sum++) {
        for (size_t numCoins = 0; numCoins < coins.size(); numCoins++) {
            // ways without current coin are stored in the same row in previous column
            int waysWithoutCurrentCoin = numCoins > 0 ? matrix[sum][numCoins - 1] : 0;

            // ways with current coin can be considered as long as amount of current coin
            // is less than or equal to current sum amount, and then in this case
            // ways with current coin
            int waysWithCurrentCoin = sum >= coins[numCoins]
                ? matrix[sum - coins[numCoins]][numCoins]
                : 0;

            matrix[sum][numCoins] += waysWithoutCurrentCoin + waysWithCurrentCoin;
        }
    }

    return matrix[totalSum][coins.size() - 1];
}

int countMinChange(vector<int>& coins, int totalSum)
{
    vector<int> minCounts(totalSum + 1, INT_MAX);
    minCounts[0] = 0;

    for (size_t c = 1; c <= coins.size(); c++) {
        for (int sum = coins[c - 1]; sum <= totalSum; sum++) {
            if (minCounts[sum - coins[c - 1]] != INT_MAX) {
                if (minCounts[sum] > minCounts[sum - coins[c - 1]] + 1) {
                    minCounts[sum] = minCounts[sum - coins[c - 1]] + 1;
                }
            }
        }
    }

    return minCounts[totalSum];
}

int printAllChanges(vector<int>& coins, int totalSum, bool iteratively)
{
    return (iteratively
        ? printWaysIterative(coins, totalSum)
        : printWaysRec(coins, coins.size(), totalSum, vector<int>())
    );
}

int main()
{
    vector<int> coins{ 25, 10, 5 };
    int totalSum = 30;

    cout << "Recursively:\n";
    int totalWays = printAllChanges(coins, totalSum, false);
    cout << "Total ways: " << totalWays << endl;

    cout << "\nIteratively:\n";
    totalWays = printAllChanges(coins, totalSum, false);
    cout << "Total ways: " << totalWays << endl;

    int minCount = countMinChange(coins, totalSum);
    cout << "\nMin count: " << minCount << endl;

    return 0;
}