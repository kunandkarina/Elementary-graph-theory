#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int n, m;
        cin >> n >> m;
        vector<int> road(n + 1, 0), sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            cin >> road[i];
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            road[u]--;
            road[v]--;
        }
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            if (road[i] < 0)
            {
                flag = false;
                break;
            }
        }
        if (flag == false)
        {
            cout << "No\n";
            continue;
        }
        sort(road.begin() + 1, road.end(), greater<int>());
        // for(int i=1;i<=n;i++) cout << road[i] << " ";
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + road[i];
        // for(int i=1;i<=n;i++) cout << sum[i] << " ";
        if (sum[n] % 2 != 0)
        {
            cout << "No\n";
            continue;
        }

        int index = n;
        bool check = true;
        for (int i = 1; i <= n; i++)
        {
            for (int j = index; j > 0; j--) // avoid TLE, use index as fpr loop boarder
            {
                if (road[j] > i && i < index)
                {
                    index = j;
                    break;
                }
                else if (i > index)
                {
                    while (i >= index)
                    {
                        index++;
                        break;
                    }
                    break;
                }
            }
            // while (i > road[index] && i < index)
            // {
            //     index--;
            // }
            // while (i > index)
            // {
            //     index++;
            // }
            int s = i * (index - i) + sum[n] - sum[index] + i * (i - 1);
            // cout << s << " " << sum[i] << "\n";
            if (s - sum[i] < 0)
            {
                check = false;
                break;
            }
        }
        if (check == true)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}