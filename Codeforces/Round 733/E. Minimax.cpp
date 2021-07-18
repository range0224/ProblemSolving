#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
 
string str;
int cnt[30];
vector<int> v;
 
int main()
{
	int t;
	int i;
	int idx, idx2;
	int sum;
 
	cin >> t;
	while (t--)
	{
		memset(cnt, 0, sizeof(cnt));
 
		cin >> str;
		
		for (i = 0; i < str.length(); i++)
		{
			cnt[str[i] - 'a']++;
		}
 
		v.clear();
		for (i = 0; i < 26; i++)
		{
			if (cnt[i]) v.push_back(cnt[i]);
		}
 
		if (v.size() == 1)
		{
			cout << str << '\n';
			continue;
		}
 
		sort(v.begin(), v.end());
 
		if (v[0] == 1)
		{
			for (i = 0; i < 26; i++)
			{
				if (cnt[i] == 1) break;
			}
 
			cout << (char)(i + 'a');
			cnt[i] = 0;
 
			for (i = 0; i < 26; i++)
			{
				while(cnt[i]--)
				{
					cout << (char)(i + 'a');
				}
			}
			cout << '\n';
 
			continue;
		}
 
		for (i = 0; i < 26; i++)
		{
			if (cnt[i]) break;
		}
 
		idx = i;
 
		for (i = idx + 1; i < 26; i++)
		{
			if (cnt[i]) break;
		}
 
		idx2 = i;
 
		if (cnt[idx] <= str.length() - cnt[idx] + 2)
		{
			cnt[idx] -= 2;
			cout << (char)(idx + 'a');
			cout << (char)(idx + 'a');
 
			for (i = idx2; i < 26; i++)
			{
				while (cnt[i]--)
				{
					cout << (char)(i + 'a');
					if (cnt[idx])
					{
						cnt[idx]--;
						cout << (char)(idx + 'a');
					}
				}
			}
		}
		else
		{
			sum = str.length() - cnt[idx] - cnt[idx2];
 
			if (sum == 0)
			{
				cnt[idx]--;
				cout << (char)(idx + 'a');
 
				while (cnt[idx2]--)
				{
					cout << (char)(idx2 + 'a');
				}
 
				while (cnt[idx]--)
				{
					cout << (char)(idx + 'a');
				}
			}
			else
			{
				cnt[idx]--;
				cout << (char)(idx + 'a');
 
				cnt[idx2]--;
				cout << (char)(idx2 + 'a');
 
				while (cnt[idx]--)
				{
					cout << (char)(idx + 'a');
				}
 
				for (i = idx2 + 1; i < 26; i++)
				{
					if (cnt[i]) break;
				}
 
				cnt[i]--;
				cout << (char)(i + 'a');
 
				while (cnt[idx2]--)
				{
					cout << (char)(idx2 + 'a');
				}
 
				for (i = idx2 + 1; i < 26; i++)
				{
					while (cnt[i]--)
					{
						cout << (char)(i + 'a');
					}
				}
			}
		}
 
		cout << '\n';
	}
}
