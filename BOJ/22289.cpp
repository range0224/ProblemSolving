#define _USE_MATH_DEFINES
#include<iostream>
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

vector<int> multiply(vector<int>& a, vector<int>& b)
{
	vec aa(a.begin(), a.end()), bb(b.begin(), b.end());
	int n = 1; while (n <= max(a.size(), b.size())) n <<= 1;
	aa.resize(n), bb.resize(n);
	fft(aa, 0), fft(bb, 0);
	for (int i = 0; i < n; i++) aa[i] *= bb[i];
	fft(aa, 1);
	vector<int> ret(n);
	for (int i = 0; i < n; i++) {
		ret[i] = round(aa[i].real());
	}
	//while(ret.size() > 10 && ret.back() == 0) ret.pop_back();
	return ret;
}

int main()
{
	vector<int> a;
	vector<int> b;
	vector<int> v;
	char arr1[1000010];
	char arr2[1000010];
	int i;
	int size;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio("false");

	cin >> arr1 >> arr2;

	for (i = 0; arr1[i]; i++);

	size = 1;
	while (size < i) size *= 2;

	idx = 0;
	a.resize(size, 0);
	for (i--; i >= 0; i--)
	{
		a[idx++] = arr1[i] - '0';
	}

	for (i = 0; arr2[i]; i++);

	size = 1;
	while (size < i) size *= 2;

	idx = 0;
	b.resize(size, 0);
	for (i--; i >= 0; i--)
	{
		b[idx++] = arr2[i] - '0';
	}

	v = multiply(a, b);

	idx = 0;
	for (i = 0; i < v.size() - 1; i++)
	{
		v[i + 1] += v[i] / 10;
		v[i] %= 10;

		if (v[i]) idx = i;
	}

	if (v[v.size() - 1]) idx = v.size() - 1;

	for (; idx >= 0; idx--)
	{
		cout << v[idx];
	}
}
