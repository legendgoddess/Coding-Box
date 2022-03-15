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
//#define int long long
const int maxn = 2e6 + 5;
int n, m;
struct Trie {
    int ch[maxn][26], cl[maxn], fa[maxn];
    int tot;
    Trie(void) : tot(1) {}
    void Insert(char *s,const int& n) {
        int p = 1;
//        printf("n = %d\n", n);
        for(int i = 1; i <= n; ++ i) {
            int& rs = ch[p][s[i] - 'a'];
//            printf("c  = %c, ", s[i]);
//            printf("rs = %d\n", rs);
            if(!rs) rs = ++ tot, fa[rs] = p, cl[rs] = s[i] - 'a';
            p = rs;
        }
    }
}Tr;
struct SAM {
    int fa[maxn], ch[maxn][26], ln[maxn], tot;
    SAM(void) : tot(1) {}

    int Insert(int c,int las) {
    //    puts("SSS");
        int p = las, np = ++ tot;
        ln[np] = ln[p] + 1;
        for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if(!p) fa[np] = 1;
        else {
            int q = ch[p][c];
            if(ln[q] == ln[p] + 1) fa[np] = q;
            else {
                int nq = ++ tot; ln[nq] = ln[p] + 1;
                fa[nq] = fa[q], fa[q] = fa[np] = nq;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            }
        }
        return np;
    }
}T;
char s[maxn];
int pos[maxn];

void build() {
    static int q[maxn]; int ed(0), st(1);
    for(int i = 0; i < 26; ++ i) if(Tr.ch[1][i]) q[++ ed] = Tr.ch[1][i];
//    printf("ed = %d\n", ed);
    pos[1] = 1;
    while(st <= ed) {
        int p = q[st ++];
        pos[p] = T.Insert(Tr.cl[p], pos[Tr.fa[p]]);
        for(int j = 0; j < 26; ++ j) if(Tr.ch[p][j]) q[++ ed] = Tr.ch[p][j];
    }
}

signed main() {
	int i, j;
    r1(n);
    for(i = 1; i <= n; ++ i) {
        scanf("%s", s + 1), Tr.Insert(s, strlen(s + 1));
    }
//    printf("tott = %d\n", tott);
    build();
    long long ans(0);
    for(i = 2; i <= T.tot; ++ i) ans += T.ln[i] - T.ln[T.fa[i]];
    printf("%lld\n", ans);
	return 0;
}

}


signed main() { return Legendgod::main(), 0; }//

