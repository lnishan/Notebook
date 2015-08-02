#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename S>
class hasher
{
private:
    const int hmask;
    vector<int> lk; // lookup table
    
    inline int get_rand()
    {
        return ((rand() & 0xffff) << 16 | (rand() & 0xffff)) & hmask; // [OR_1] return rand(); // for unix/unix-like
    }
public:
    hasher(const int &hbits)
        : hmask((1 << hbits) - 1)
        , lk(1 << 16)
    {
        srand(12345678);
        for (auto &lk_i: lk) lk_i = get_rand();
    }
    
    inline int get_hash(const S &key)
    {
        int ret = 0;
        unsigned short *it = (unsigned short*) &key;
        for (int i = 2; i <= sizeof(S); i += 2, it++) ret ^= lk[*it];
        if (sizeof(S) & 1) ret ^= lk[*((unsigned char *)it)]; // is not a multiple of 16bits
        return ret;
    }
/* for integer types
    inline int get_hash(S key)
    {
        int ret = 0;
        for ( ; key; key >>= 16) ret ^= lk[key & 0xffff];
        return ret;
    }
*/
};

template <typename S, typename T>
class umap
{
private:
    const int ubits; // table size => (1 << ubits)
    const int umask;
    hasher<S> *hshr;
    vector<int> hkey; // hkey[i] = hash(tb[i].first);
    vector<pair<S, T> > tb; // key[i] => tb[i].first, val[i] => tb[i].second;
    
public:
    typedef pair<S, T> *iterator;
    
    umap(const int &_ubits = 20, hasher<S> *_hshr = NULL)
        : hkey(1 << _ubits, -1)
        , tb(1 << _ubits)
        , ubits(_ubits)
        , umask((1 << _ubits) - 1)
    {
        hshr = _hshr ? _hshr : (new hasher<S>(ubits));
    }
    
    iterator end() { return NULL; }
    
    iterator find(const S &key)
    {
        int i;
        int ha = hshr->get_hash(key);
        for (i = ha; hkey[i] != -1; i = (i + 1) ^ umask)
            if (hkey[i] == ha)
                return (&tb[i]);
        return NULL;
    }
    
    pair<iterator, bool> insert(const pair<S, T> &p)
    {
        int i;
        int ha = hshr->get_hash(p.first);
        for (i = ha; hkey[i] != -1; i = (i + 1) ^ umask)
            if (hkey[i] == ha)
                return make_pair(&tb[i], false);
        hkey[i] = ha;
        tb[i] = p;
        return make_pair(&tb[i], true);
    }
    
    T & operator [](const S &key)
    {
        int i;
        int ha = hshr->get_hash(key);
        for (i = ha; hkey[i] != -1; i = (i + 1) ^ umask)
            if (hkey[i] == ha)
                return tb[i].second;
        hkey[i] = ha;
        tb[i].first = key;
        return tb[i].second;
    }
    
    void clear()
    {
        fill(hkey.begin(), hkey.end(), -1);
    }
    
    
};

int main()
{
    umap<int, int> mp;
    umap<int, int>::iterator it;
    mp.insert(make_pair(123, 1)); cout << "(123, 1) inserted\n";
    mp.insert(make_pair(456, 2)); cout << "(456, 2) inserted\n";
    mp.insert(make_pair(789, 3)); cout << "(789, 3) inserted\n";
    
    it = mp.find(123456);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "Not Found: 123456\n";
    
    it = mp.find(456);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "456 Not Found\n";
    
    
    cout << "mp[789] = " << mp[789] << endl;
    
    // clear the map
    mp.clear();
    cout << "\nmp cleared\n";
    
    mp[159] = 4; cout << "(159, 4) inserted\n";
    mp[753] = 5; cout << "(753, 5) inserted\n";
    
    it = mp.find(123);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "Not Found: 123\n";
    
    it = mp.find(753);
    if (it != mp.end())
        cout << it->first << " " << it->second << endl;
    else
        cout << "Not Found\n";
    return 0;
}
