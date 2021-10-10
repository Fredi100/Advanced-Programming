// Quick Find.cpp
// Union Find Page 14

#include <iostream>
using namespace std;

int main()
{
    int p, q, id[10], N = 10;

    for (int i = 0; i < N; i++)
        id[i] = i;

    while (1) {

        cin >> p;<
        if (!cin)
            break;
        cin >> q;
        if (!cin)
            break;

        int pid = id[p];
        int qid = id[q];

        if (pid == qid)
            continue;

        for (int i = 0; i < N; i++) {
            if (id[i] == pid) {
                id[i] = qid;
            }
        }

        // Print the array
        for (int i = 0; i < N; i++) {
            cout << id[i];
            if (i != N - 1)
                cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
