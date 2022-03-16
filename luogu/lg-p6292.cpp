#include <bits/stdc++.h>
/*
* @ legendgod
* 纵使前路是无底深渊，下去了也是前程万里
*/
using namespace std;

//#define Fread
//#define Getmod

#ifdef Fread
char buf[1 << 21], *iS, *iT;
#define gc() (iS == iT ? (iT = (iS = buf) + fread (buf, 1, 1 << 21, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
	for(; '0' <= c && c <= '9';c = getchar()) x = (x * 10) + (c ^ 48);
	x *= f;
}

#ifdef Getmod
const int mod  = 51061;
template <int mod>
struct typemod {
    int z;
    typemod(int a = 0) : z(a) {}
    inline int inc(int a,int b) const {return a += b - mod, a + ((a >> 31) & mod);}
    inline int dec(int a,int b) const {return a -= b, a + ((a >> 31) & mod);}
    inline int mul(int a,int b) const {return 1ll * a * b % mod;}
    typemod<mod> operator + (const typemod<mod> &x) const {return typemod(inc(z, x.z));}
    typemod<mod> operator - (const typemod<mod> &x) const {return typemod(dec(z, x.z));}
    typemod<mod> operator * (const typemod<mod> &x) const {return typemod(mul(z, x.z));}
    typemod<mod>& operator += (const typemod<mod> &x) {*this = *this + x; return *this;}
    typemod<mod>& operator -= (const typemod<mod> &x) {*this = *this - x; return *this;}
    typemod<mod>& operator *= (const typemod<mod> &x) {*this = *this * x; return *this;}
    int operator == (const typemod<mod> &x) const {return x.z == z;}
    int operator != (const typemod<mod> &x) const {return x.z != z;}
};
typedef typemod<mod> Tm;
#endif

template <typename T,typename... Args> inline void r1(T& t, Args&... args) {
    r1(t);  r1(args...);
}

//#define int long long
const int maxn = 4e5 + 5;
const int maxm = maxn << 1;
int n;
namespace SAM {
    int pos[maxn];
    struct Node {
        int fa, len;
        int c[26];
        Node(void) {
            memset(c, 0, sizeof(c));
            fa = len = 0;
        }
    };
    Node d[maxn << 1];
    int las = 1, tot = 1;
    void Insert(int c,int id) {
        int p = las, np = las = ++ tot;
        pos[id] = np;
        d[np].len = d[p].len + 1;
        for(; p && !d[p].c[c]; p = d[p].fa) d[p].c[c] = np;
        if(!p) d[np].fa = 1;
        else {
            int q = d[p].c[c];
            if(d[q].len == d[p].len + 1) d[np].fa = q;
            else {
                int nq = ++ tot; d[nq] = d[q];
                d[nq].len = d[p].len + 1;
                d[q].fa = d[np].fa = nq;
                for(; p && d[p].c[c] == q; p = d[p].fa) d[p].c[c] = nq;
            }
        }
    }
};

char s[maxn];
struct Query {
    int id, l, r;
    int operator < (const Query &z) const {
        return r == z.r ? l < z.l : r < z.r;
    }
}q[maxn];
long long ans[maxn];

namespace Seg {
    typedef long long ll;
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    #define mid ((l + r) >> 1)
    ll val[maxn << 2], tag[maxn << 2], len[maxn];
    void pushup(int p) {
        val[p] = val[ls] + val[rs];
    }
    void up(int p,int c) {
        val[p] += c * len[p], tag[p] += c;
    }
    void pushdown(int p) {
        if(tag[p]) {
            up(ls, tag[p]), up(rs, tag[p]);
            tag[p] = 0;
        }
    }

    void build(int p,int l,int r) {
        len[p] = r - l + 1;
        if(l == r) return ;
        build(ls, l, mid), build(rs, mid + 1, r);
    }

    void change(int p,int l,int r,int ll,int rr,int c) {
        if(ll <= l && r <= rr) {
            val[p] += 1ll * c * len[p];
            tag[p] += c;
            return ;
        }
        pushdown(p);
        if(ll <= mid) change(ls, l, mid, ll, rr, c);
        if(mid < rr) change(rs, mid + 1, r, ll, rr, c);
        pushup(p);
    }

    ll Ask(int p,int l,int r,int ll,int rr) {
        if(ll <= l && r <= rr) return val[p];
        pushdown(p);
        long long res(0);
        if(ll <= mid) res += Ask(ls, l, mid, ll, rr);
        if(mid < rr) res += Ask(rs, mid + 1, r, ll, rr);
//        pushup(p);
        return res;
    }

    #undef ls
    #undef rs
    #undef mid
};

namespace LCT {
    int ch[maxn << 1][2], fa[maxn << 1], tag[maxn << 1];
    int ed[maxn << 1], val[maxn << 1];
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    int pd(int x) {
        return rs(fa[x]) == x;
    }
    int nrt(int x) {
        return ls(fa[x]) == x || rs(fa[x]) == x;
    }
    void change(int p,int c) {
        if(!p) return ;
        tag[p] = ed[p] = c;
    }
    void pushdown(int p) {
        if(tag[p]) {
            change(ls(p), tag[p]), change(rs(p), tag[p]);
            tag[p] = 0;
        }
    }
    void Rotate(int p) {
        int f = fa[p], ff = fa[f], k = pd(p);
        fa[p] = ff;
        if(nrt(f)) ch[ff][pd(f)] = p;
        fa[ch[p][!k]] = f, ch[f][k] = ch[p][!k];
        ch[p][!k] = f;
        fa[f] = p;
    }
    int sta[maxn];
    void Splay(int p) {
        int t1 = 0;
        int now(p);
        sta[++ t1] = now;
        while(nrt(now)) sta[++ t1] = (now = fa[now]);
        while(t1) pushdown(sta[t1 --]);
        for(int f; f = fa[p], nrt(p); Rotate(p)) {
            if(nrt(f)) Rotate(pd(f) == pd(p) ? f : p);
        }
    }
    void access(int p) {
        int pos = p; p = SAM::pos[pos];
//        printf("pos = %d\n", pos);
        int to(0);
        for(; p; to = p, p = fa[p]) {
            Splay(p), ch[p][1] = to;
//            int a = ed[p] - SAM::d[p].len + 1, b = ed[p] - SAM::d[fa[p]].len;
            if(ed[p]) {
//            printf("a = %d, b = %d\n", a, b);
                Seg::change(1, 1, n, ed[p] - SAM::d[p].len + 1, ed[p] - SAM::d[fa[p]].len, -1);
            }
        }
        Seg::change(1, 1, n, 1, pos, 1);
//        printf("ls = %d\n", to);
        change(to, pos);
    }
};

void Bef() {
    int i;
    for(i = 1; i <= n; ++ i) SAM::Insert(s[i] - 'a', i);
    for(i = 2; i <= SAM::tot; ++ i) LCT::fa[i] = SAM::d[i].fa;
    Seg::build(1, 1, n);
}
//#define degbug_Seg
signed main() {
//    freopen("S.in", "r", stdin);
//    freopen("S.out", "w", stdout);
	int i, j;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    Bef();
    int Q;
    r1(Q);
    #ifdef degbug_Seg
    for(i = 1; i <= Q; ++ i) {
        int opt, l, r, c;
        r1(opt, l, r);
        if(opt == 1) r1(c), Seg::change(1, 1, n, l, r, c);
        else printf("%lld\n", Seg::Ask(1, 1, n, l, r));
    }
    return 0;
    #endif // degbug_Seg
    for(i = 1; i <= Q; ++ i) {
        r1(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + Q + 1);
    for(int r = 1, i = 1; r <= n; ++ r) {
        LCT::access(r);
        for(; q[i].r <= r && i <= Q; ++ i)
            ans[q[i].id] = Seg::Ask(1, 1, n, q[i].l, q[i].r);
    }
//    for(i = 1; i <= Q; ++ i) {
//        while(q[i].r > r) LCT::access(++ r);
//        ans[q[i].id] = Seg::Ask(1, 1, n, q[i].l, q[i].r);
//    }
    for(i = 1; i <= Q; ++ i) printf("%lld\n", ans[i]);
	return 0;
}

/*
aaccccfses
3
1 4
3 5
8 8
*/
