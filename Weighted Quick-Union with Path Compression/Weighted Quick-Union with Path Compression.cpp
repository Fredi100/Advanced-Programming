// Weighted Quick-Union with Path Compression.cpp
// Union Find Page 30

#include <iostream>
#include <string>
using namespace std;

int main() {
    std::string p, q;
    int N = 10;
    int i, j;
    int* id = new int[N];
    int* sz = new int[N];

    // Initialize both arrays
    for (i = 0; i < N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
    while (true)
    {
        cin >> p;

        // Check for exit to stop the programm
        if (p.compare("exit") == 0)
            break;

        cin >> q;

        for (i = stoi(p); i != id[i]; i = id[i])
            id[i] = id[id[i]];
        for (j = stoi(q); j != id[j]; j = id[j])
            id[j] = id[id[j]];
        if (i == j)
            continue;
        if (sz[i] < sz[j])
        {
            id[i] = j;
            sz[j] += sz[i];
        }
        else
        {
            id[j] = i;
            sz[i] += sz[j];
        }

        // Print the array
        for (i = 0; i < N; i++) {
            if (i != N - 1)
            {
                cout << id[i] << " ";
            }
            else cout << id[i];
        }
        cout << "\n";
    }
    return 0;
}