#include <bits/stdc++.h>
using namespace std;
namespace Legendgod {
	namespace Read {
//		#define Fread
		#ifdef Fread
		const int Siz = (1 << 21) + 5;
		char *iS, *iT, buf[Siz];
		#define gc() ( iS == iT ? (iT = (iS = buf) + fread(buf, 1, Siz, stdin), iS == iT ? EOF : *iS ++) : *iS ++ )
		#define getchar gc
		#endif
		template <typename T>
		void r1(T &x) {
		    x = 0;
			char c(getchar());
			int f(1);
			for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
			for(; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
			x *= f;
		}
		template <typename T, typename...Args>
		void r1(T &x, Args&...arg) {
			r1(x), r1(arg...);
		}
		#undef getchar
	}

using namespace Read;

const int maxn = 2e6 + 5;
int n, m;
char s[maxn];

int fa[maxn], ln[maxn], ch[maxn][26];
int tot(1);
int Insert(int c,int las) {
    if(ch[las][c]) {
        int p = las, q = ch[p][c];
        if(ln[p] + 1 == ln[q]) return q;
        else {
            int nq = ++ tot; ln[nq] = ln[p] + 1;
            fa[nq] = fa[q], fa[q] = nq;
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            return nq;
        }
    }
    int p = las, np = ++ tot;
    ln[np] = ln[p] + 1;
    for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if(!p) fa[np] = 1;
    else {
        int q = ch[p][c];
        if(ln[p] + 1 == ln[q]) fa[np] = q;
        else {
            int nq = ++ tot; ln[nq] = ln[p] + 1;
            fa[nq] = fa[q], fa[q] = fa[np] = nq;
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }
    }
    return np;
}

signed main() {
	int i, j;
    r1(n);
    for(int _ = 1; _ <= n; ++ _) {
        scanf("%s", s + 1);
        m = strlen(s + 1);
        int las = 1;
        for(i = 1; i <= m; ++ i) {
            las = Insert(s[i] - 'a', las);
        }
    }
    long long ans(0);
    for(i = 2; i <= tot; ++ i) ans += ln[i] - ln[fa[i]];
    printf("%lld\n", ans);
	return 0;
}

}


signed main() { return Legendgod::main(), 0; }//

