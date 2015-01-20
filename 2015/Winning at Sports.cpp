#include <algorithm>
#include <iostream>

using namespace std;

#define MODULO 1000000007
#define MAXIMUM_SCORE 2000

int dp_stressfree[MAXIMUM_SCORE + 1][MAXIMUM_SCORE * 2 + 1];
int dp_stressful[MAXIMUM_SCORE + 1][MAXIMUM_SCORE * 2 + 1];

/**
 * For a stress-free win, let dp[i][j] = number of ways to score your i'th score
 * as the j'th score s.t. (j - 1) - (i - 1) < i - 1. The left hand side of the
 * inequality is your opponent's score on the j - 1 turn. We can only achieve our
 * i'th score on the j'th turn when our previous score is greater than the
 * opponent's score. Thus dp[i][j] = dp[i - 1][i - 1] + ... + dp[i - 1][j - 1] =
 * dp[i][j - 1] + dp[i - 1][j - 1].
 */
void precompute_stressfree_win()
{
  dp_stressfree[1][1] = 1;
  for (int i = 2; i <= MAXIMUM_SCORE; i++)
    for (int j = i; j < i * 2 - 1; j++)
      dp_stressfree[i][j] = (dp_stressfree[i][j - 1] + dp_stressfree[i - 1][j - 1]) % MODULO;
}

int count_stressfree_wins(int our_score, int opponents_score)
{
  int count = 0;
  for (int j = our_score; j <= our_score + opponents_score; j++)
    count = (count + dp_stressfree[our_score][j]) % MODULO;
  return count;
}

/**
 * For a stressful win, let dp[i][j] = number of ways to score your i'th score
 * as the j'th score s.t. (j - 1) - (i - 1) > i - 1. We can only achieve our
 * i'th score on the j'th turn when our previous score is less than the
 * opponent's current score. Thus dp[i][j] = dp[i - 1][i * 2 - 2] + ... + dp[i - 1][j - 1]
 */
void precompute_stressful_win()
{
  fill(dp_stressful[1] + 2, dp_stressful[1] + MAXIMUM_SCORE * 2 + 1, 1);
  for (int i = 2; i <= MAXIMUM_SCORE; i++)
  {
    dp_stressful[i][i * 2] = (dp_stressful[i - 1][i * 2 - 2] + dp_stressful[i - 1][i * 2 - 1]) % MODULO;
    for (int j = i * 2 + 1; j <= MAXIMUM_SCORE * 2; j++)
      dp_stressful[i][j] = (dp_stressful[i][j - 1] + dp_stressful[i - 1][j - 1]) % MODULO;
  }
}

int count_stressful_wins(int our_score, int opponents_score)
{
  // This is equivalent to determining the number of ways for us to tie the
  // opponent's final score. If the opponent's score is 0, there is only 1 way to
  // get a stressful victory.
  return opponents_score ? dp_stressful[opponents_score][opponents_score * 2] : 1;
}

int main()
{
  precompute_stressfree_win();
  precompute_stressful_win();
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int our_score, opponents_score;
    scanf("%d-%d", &our_score, &opponents_score);
    printf("Case #%d: %d %d\n", t, count_stressfree_wins(our_score, opponents_score), count_stressful_wins(our_score, opponents_score));
  }
  return 0;
}
