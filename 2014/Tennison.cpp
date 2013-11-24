#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_WINS 100
#define MAX_PROBABILITY 1000

// dp[i][j][k] = probability that Tennison wins j out of i % 2 sets when the sun appears with 
//               probability k / 1000.
double dp[2][MAX_WINS + 1][MAX_PROBABILITY + 1];

int main() 
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) 
    {
        fill(**dp, **dp + 2 * (MAX_WINS + 1) * (MAX_PROBABILITY + 1), 0);
        int K;
        double ps, pr, pi, pu, pw, pd, pl;
        cin >> K >> ps >> pr >> pi >> pu >> pw >> pd >> pl;
        int sun_increase = int(pu * 1000 + 0.5), sun_decrease = int(pd * 1000 + 0.5);
        double prob_winning = 0;
        dp[0][0][int(pi * 1000 + 0.5)] = 1;
        // There can be up to 2 * K - 1 sets played before a winner is determined.
        for (int i = 0; i < 2 * K; i++)
        {
            int cur_set = i % 2, next_set = (i + 1) % 2;
            fill(*dp[next_set], *dp[next_set] + (MAX_WINS + 1) * (MAX_PROBABILITY + 1), 0);
            for (int j = 0; j <= min(i, K); j++)
            {
                // Skip all cases when Tennison's opponent wins K sets.
                if (i - j >= K)
                    continue;
                for (int k = 0; k <= MAX_PROBABILITY; k++)
                    if (dp[cur_set][j][k] > 0)
                    {
                        // Case when Tennison wins K matches.
                        if (j == K)
                        {
                            prob_winning += dp[cur_set][j][k];
                            continue;
                        }
                        double prob_sun = k / 1000.;
                        double prob_win_set = prob_sun * ps + (1 - prob_sun) * pr;
                        double prob_win = dp[cur_set][j][k] * prob_win_set;
                        double prob_lose = dp[cur_set][j][k] * (1 - prob_win_set);


                        // Case when Tennison wins current set and probability of sun appearing
                        // increases.
                        int sun_increase_prob = min(k + sun_increase, MAX_PROBABILITY);
                        dp[next_set][j + 1][sun_increase_prob] += prob_win * pw;

                        // Case when Tennison wins current set and probability of sun appearing 
                        // does not increase.
                        dp[next_set][j + 1][k] += prob_win * (1 - pw);

                        // Case when Tennison loses current set and probability of sun appearing
                        // does not decrease.
                        dp[next_set][j][k] += prob_lose * (1 - pl);

                        // Case when Tennison loses current set and probability of sun appearing
                        // decreases.
                        int sun_decrease_prob = max(k - sun_decrease, 0);
                        dp[next_set][j][sun_decrease_prob] += prob_lose * pl;
                    }
            }
        }
        printf("Case #%d: %.6f\n", t, prob_winning);
    }
    return 0;
}