//solution to the problem https://www.codechef.com/INVS2013/problems/CDZ1303

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cctype>
#include <complex>

using namespace std;

#define ull unsigned long long
#define ill long long int
#define pii pair<int,int>
#define pb(x) push_back(x)
#define F(i,a,n) for(i=(a);i<(n);++i)
#define FD(i,a,n) for(i=(a);i>=(n);--i)
#define FE(it,x) for(it=x.begin();it!=x.end();++it)
#define V(x) vector<x>
#define S(x) scanf("%d",&x)
#define Sl(x) scanf("%I64d",&x)
#define debug(i,sz,x) F(i,0,sz){cout<<x[i]<<" ";}cout<<endl

const double PI = 4*atan(1);
typedef complex<double> base;

vector<base> omega;
int FFT_N;
void init_fft(int n)
{
     FFT_N  = n;
     omega.resize(n);
     double angle = 2 * PI / n;
     
     for(int i = 0; i < n; i++)
          omega[i] = base( cos(i * angle), sin(i * angle));
}

void fft (vector<base> & a)
{
     int n = (int) a.size();
     if (n == 1)  return;
     int half = n >> 1;
     
     vector<base> even (half),  odd (half);
     for (int i=0, j=0; i<n; i+=2, ++j)
     {
          even[j] = a[i];
          odd[j] = a[i+1];
     }
     fft (even), fft (odd);
     
     for (int i=0, fact = FFT_N/n; i < half; ++i)
     {
          base twiddle =  odd[i] * omega[i * fact] ;
          a[i] =  even[i] + twiddle;
          a[i+half] = even[i] - twiddle;
     }
}
void multiply (const vector<long long> & a, const vector<long long> & b, vector<long long> & res)
{
     vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
     int n = 1;
     while (n < 2*max (a.size(), b.size()))  n <<= 1;
     fa.resize (n),  fb.resize (n);
     
     init_fft(n);
     fft (fa),  fft (fb);
     for (size_t i=0; i<n; ++i)
          fa[i] = conj( fa[i] * fb[i]);
     fft (fa);

     res.resize (n);
     for (size_t i=0; i<n; ++i)
          res[i] = (long long) (fa[i].real() / n + 0.5);
}

int main() {
    int i,j,t;
    S(t);
    while(t--) {
    	int n1,n2;
    	vector<long long> v1,v2,res;
    	S(n1); S(n2);
    	F(i,0,n1+1) {
    		int x;
    		S(x);
    		v1.pb(x);
    	}
    	F(i,0,n2+1) {
    		int x;
    		S(x);
    		v2.pb(x);
    	}
    	multiply(v1,v2,res);
	while ( !res.empty() && *(res.end()-1) == 0 ) res.pop_back();
    	int n = res.size();
    	printf("%d\n", n-1);
    	F(i,0,n) printf("%d ", res[i]);
    	printf("\n");
    }
    return 0;
}
