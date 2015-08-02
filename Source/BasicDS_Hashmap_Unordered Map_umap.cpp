#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

const static int umap_bits = 20;
const static int umap_mask = 0xfffff; // = (1 << umap_bits) - 1
template <typename S, typename T>
class umap
{
private:
    int kbyt; // sizeof keys in bytes
    vector<int> hkey; // hkey[i] = hash(tb[i].first);
    vector<pair<S, T> > tb; // key[i] => tb[i].first, val[i] => tb[i].second;
    
    vector<int> lk; // lookup table
    inline int get_rand()
    {
        return ((rand() & 0xffff) << 16 | (rand() & 0xffff)) & umap_mask; // [OR_1] return rand(); // for unix/unix-like
    }
    int get_hash(const S &key)
    {
        int ret = 0;
        unsigned short *it = (unsigned short*) &key;
        for (int i = 2; i <= kbyt; i += 2, it++) ret ^= lk[*it];
        if (kbyt & 1) ret ^= lk[*((unsigned char *)it)]; // is not a multiple of 16bits
        return ret;
    }
/* for integer types
    int get_hash(S key)
    {
        int ret = 0;
        for ( ; key; key >>= 16) ret ^= lk[key & 0xffff];
        return ret;
    }
*/
public:
    typedef pair<S, T> *iterator;
    
    umap(const int &_kbyt = -1) // [OR_2] umap();
        : hkey(1 << umap_bits, -1)
        , tb(1 << umap_bits)
        , lk(1 << 16)
    {
        kbyt = _kbyt == -1 ? sizeof(S) : _kbyt; // [OR_2] kbyt = sizeof(S);
        srand(12345678);
        for (auto &lk_i: lk) lk_i = get_rand();
    }
    
    iterator end() { return NULL; }
    
    iterator find(const S &key)
    {
        int i;
        int ha = get_hash(key);
        for (i = ha; hkey[i] != -1; i = (i + 1) ^ umap_mask)
            if (hkey[i] == ha)
                return (&tb[i]);
        return NULL;
    }
    
    pair<iterator, bool> insert(const pair<S, T> &p)
    {
        int i;
        int ha = get_hash(p.first);
        for (i = ha; hkey[i] != -1; i = (i + 1) ^ umap_mask)
            if (hkey[i] == ha)
                return make_pair(&tb[i], false);
        hkey[i] = ha;
        tb[i] = p;
        return make_pair(&tb[i], true);
    }
};

int main()
{
    umap<int, int> mp;
    umap<int, int>::iterator it;
    mp.insert(make_pair(123, 1));
    mp.insert(make_pair(456, 2));
    mp.insert(make_pair(789, 3));
    
    it = mp.find(456);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "Not Found\n";
    
    it = mp.find(123456);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "Not Found\n";
    
/* Place umap::get_hash() in public to test the following code
    umap<double, int> mp;
    double l = 0, h = 10000000, m;
    for (int i = 0; i < 50; i++)
    {
        m = (l + h) / 2;
        printf("%f %u\n", m, mp.get_hash(m));
        if (rand() & 1)
            l = m;
        else
            h = m;
    }
    
    umap<string, int> mp2;
    string s ="abc123";
    cout << mp2.get_hash(s) << endl;
    s = "lnishanaaaaaaaaaaaaaaa";
    cout << mp2.get_hash(s) << endl; */
    return 0;
}
