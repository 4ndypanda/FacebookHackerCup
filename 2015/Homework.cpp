#include <algorithm>
#include <iostream>

using namespace std;

#define MAX_SIZE 10000001

bool is_prime[MAX_SIZE];
int primacity[MAX_SIZE];

/**
 * By using a simpler version of the Sieve of Eratosthenes, we can compute the
 * primacity for all numbers by looping through all multiples of a prime number
 * and incrementing a counter for each multiple.
 */
void precompute_primacity()
{
  fill(is_prime + 2, is_prime + MAX_SIZE, true);
  for (int i = 2; i < MAX_SIZE; i++)
    if (is_prime[i])
    {
      primacity[i] = 1;
      for (int j = i * 2; j < MAX_SIZE; j += i)
      {
        is_prime[j] = false;
        primacity[j]++;
      }
    }
}

int main()
{
  precompute_primacity();
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int A, B, K;
    cin >> A >> B >> K;
    int count = 0;
    for (int j = A; j <= B; j++)
      count += primacity[j] == K;
    printf("Case #%d: %d\n", t, count);
  }
  return 0;
}
