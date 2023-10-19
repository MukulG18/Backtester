#ifndef Debugging
#define Debugging
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(x) std::cerr << #x <<" "; _print(x); std::cerr << endl;
#define deb(x,n) std::cerr << #x <<" "; _print(x,n); std::cerr << endl;
#else
#define debug(x)
#define deb(x,n)
#endif

template<class T>void _print(T t) {std::cerr << t;}

template <class T> void _print(T v[], int n);
template <class T, class V> void _print(std::pair <T, V> p);
template <class T> void _print(std::vector <T> v);
template <class T> void _print(std::set <T> v);
template <class T> void _print(std::unordered_set <T> v);
template <class T, class V> void _print(std::map <T, V> v);
template <class T, class V> void _print(std::unordered_map <T, V> v);
template <class T> void _print(std::multiset <T> v);
template <class T, class V> void _print(std::pair <T, V> p) {std::cerr << "{"; _print(p.first); std::cerr << ","; _print(p.second); std::cerr << "}";}
template <class T> void _print(T v[], int n){std::cerr << "[ ";for (int i = 0; i < n; i++){_print(v[i]);std::cerr << " ";}std::cerr << "]";}
template <class T> void _print(std::vector <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
template <class T> void _print(std::set <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
template <class T> void _print(std::unordered_set <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
template <class T> void _print(std::multiset <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
template <class T, class V> void _print(std::map <T, V> v) {std::cerr << "[ "; for (auto i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
template <class T, class V> void _print(std::unordered_map <T, V> v) {std::cerr << "[ "; for (auto i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}

#endif