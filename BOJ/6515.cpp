#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n;
int arr[100010];
vector<pair<pair<int, int>, int>> v;
int cnt[200010];
int cnt2[100010];
int ans[100010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

int main()
{
	int q;
	int i;
	int a, b;
	int answer;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	while (1)
	{
		cin >> n;

		if (!n) break;

		v.clear();
		answer = 0;

		cin >> q;

		for (i = 1; i <= n; i++)
		{
			cin >> arr[i];

			arr[i] += 100000;
		}

		for (i = 0; i < q; i++)
		{
			cin >> a >> b;

			v.push_back(make_pair(make_pair(a, b), i));
		}

		sort(v.begin(), v.end(), comp);

		cnt2[0] = 100010;

		a = v[0].first.first;
		b = v[0].first.second;
		for (i = a; i <= b; i++)
		{
			cnt2[cnt[arr[i]]]--;
			cnt[arr[i]]++;
			cnt2[cnt[arr[i]]]++;

			answer = max(answer, cnt[arr[i]]);
		}

		ans[v[0].second] = answer;

		for (i = 1; i < v.size(); i++)
		{
			while (a > v[i].first.first)
			{
				a--;
				cnt2[cnt[arr[a]]]--;
				cnt[arr[a]]++;
				cnt2[cnt[arr[a]]]++;

				answer = max(answer, cnt[arr[a]]);
			}
			while (b < v[i].first.second)
			{
				b++;
				cnt2[cnt[arr[b]]]--;
				cnt[arr[b]]++;
				cnt2[cnt[arr[b]]]++;

				answer = max(answer, cnt[arr[b]]);
			}
			while (a < v[i].first.first)
			{
				if (answer == cnt[arr[a]] && cnt2[cnt[arr[a]]] == 1) answer--;

				cnt2[cnt[arr[a]]]--;
				cnt[arr[a]]--;
				cnt2[cnt[arr[a]]]++;

				a++;
			}
			while (b > v[i].first.second)
			{
				if (answer == cnt[arr[b]] && cnt2[cnt[arr[b]]] == 1) answer--;

				cnt2[cnt[arr[b]]]--;
				cnt[arr[b]]--;
				cnt2[cnt[arr[b]]]++;

				b--;
			}

			ans[v[i].second] = answer;
		}

		for (i = 0; i < q; i++)
		{
			cout << ans[i] << '\n';
		}

		for (i = a; i <= b; i++)
		{
			cnt2[cnt[arr[i]]]--;
			cnt[arr[i]]--;
			cnt2[cnt[arr[i]]]++;
		}
	}
}
