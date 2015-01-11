#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
 * Make string n as lexicographically close to string goal using a single swap.
 * Note that goal is either the lexicographically largest or smallest string
 * comprised of characters from n.
 */
string get_closest(string n, string goal)
{
  // Find the first index where string n differs from string goal.
  int i = 0;
  for (; i < n.length() && n[i] == goal[i]; i++);

  // Both n and goal are the same.
  if (i == n.length())
    return n;

  // Replace n[i] with a character in n.substr(i + 1) that is equal to goal[i].
  // Because goal is either the lexicographically largest or smallest string, we
  // need to select from the end of string n. Here is the proof for when goal
  // is the lexicographically largest string:
  //
  //   Suppose there exists j, k s.t. i < j < k and goal[i] = n[j] = n[k]. Let
  //   n_1 be the string created by swapping n[i] and n[j] and n_2 be the string
  //   created by swapping n[i] and n[k]. Thus, n_1.substr(0, j) = n_2.substr(0, j).
  //
  //   By definition, n[l] <= goal[l] for 0 < l < n.length(). We also have that
  //   n_1[j] = n[i] < goal[i] = n[j] = n_2[j] because goal[i] != n[i] by
  //   definition of i. Therefore n_1.substr(j) < n_2.substr(j). Combined with
  //   n_1.substr(0, j) = n_2.substr(0, j), we have that n_1 < n_2 <= goal.
  //
  // The same proof works for goal being lexicographically smallest. The loop
  // below is guaranteed to break early since n and goal contain the same set of
  // characters.
  int j = n.length() - 1;
  for (; n[j] != goal[i]; j--);
  swap(n[i], n[j]);
  return n;
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    string N;
    cin >> N;

    string largest_possible_number = N;
    sort(largest_possible_number.rbegin(), largest_possible_number.rend());
    string largest_number = get_closest(N, largest_possible_number);

    string smallest_possible_number = largest_possible_number;
    reverse(smallest_possible_number.begin(), smallest_possible_number.end());
    // Need to make sure that '0' is not the first character. Replace with the
    // next smallest digit. The loop below is guaranteed to break since a number
    // cannot contain all '0' digits unless N = 0.
    if (N != "0")
    {
      int i = 0;
      for (; smallest_possible_number[i] == '0'; i++);
      swap(smallest_possible_number[0], smallest_possible_number[i]);
    }
    string smallest_number = get_closest(N, smallest_possible_number);

    printf("Case #%d: %s %s\n", t, smallest_number.c_str(), largest_number.c_str());
  }
  return 0;
}
