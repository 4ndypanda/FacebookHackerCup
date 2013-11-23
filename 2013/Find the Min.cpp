#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int m[100000], next[100001], indexof[100001];

void compute_next(int k)
{
    fill(indexof, indexof + k + 1, -1);
    fill(next, next + k + 1, -1);
    for (int i = 0; i < k; i++)
        if (m[i] <= k)
            indexof[m[i]] = i;
    int ind = 0;
    for (int i = 0; i <= k; i++)
    {
        while (next[ind] != -1)
            ind++;
        if (indexof[i] == -1)
            next[ind] = i;
        else
            next[max(ind, indexof[i] + 1)] = i;
    }
}

int main()
{
    fstream input("input.txt", fstream::in);
    fstream output("output.txt", fstream::out);
    int T;
    input >> T;
    for (int t = 1; t <= T; t++)
    {
        int n, k;
        input >> n >> k;
        int a, b, c, r;
        input >> a >> b >> c >> r;        
        m[0] = a;
        for (int i = 1; i < k; i++)
            m[i] = (1LL * b * m[i - 1] + c) % r;
        compute_next(k);
        output << "Case #" << t << ": " << next[(n - k - 1) % (k + 1)] << endl;
    }
    input.close();
    output.close();
    return 0;
}