#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<algorithm>
using namespace std;

const double pi = acos(-1);
typedef complex<double> cpx;
typedef vector<cpx> vec;

void fft(vec& a, bool inv) {
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; bit <= j; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len;
		if (inv) ang = -ang;
		cpx w(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			cpx wp(1, 0);
			for (int j = 0; j < len / 2; j++) {
				cpx u = a[i + j], v = a[i + j + len / 2] * wp;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				wp *= w;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; i++) {
			a[i] /= n;
			a[i] = cpx(round(a[i].real()), round(a[i].imag())); //result is integer
		}
	}
}

vector<long long> multiply(vector<long long>& a, vector<long long>& b)
{
	vec aa(a.begin(), a.end()), bb(b.begin(), b.end());
	int n = 1; while (n <= max(a.size(), b.size())) n <<= 1;
	aa.resize(n), bb.resize(n);
	fft(aa, 0), fft(bb, 0);
	for (int i = 0; i < n; i++) aa[i] *= bb[i];
	fft(aa, 1);
	vector<long long> ret(n);
	for (int i = 0; i < n; i++) {
		ret[i] = round(aa[i].real());
	}
	//while(ret.size() > 10 && ret.back() == 0) ret.pop_back();
	return ret;
}

int main()
{
	long long n;
	vector<long long> a;
	vector<long long> b;
	vector<long long> v;
	int i, j;
	int size = 1;
	int x;
	int q;
	int cnt = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;

	while (size < 2 * 200000) size *= 2;

	a.resize(size, 0);
	b.resize(size, 0);

	for (i = 0; i < n; i++)
	{
		cin >> x;

		a[x] = 1;
		b[x] = 1;
	}

	v = multiply(a, b);

	cin >> q;
	while (q--)
	{
		cin >> x;

		if (v[x] || a[x]) cnt++;
	}

	cout << cnt;
}
