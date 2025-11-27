#include <Trie.hpp>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Autocomplete{
    private:
        Trie* wordTrie;
    public:
        Autocomplete();
        ~Autocomplete();

        void insertString(const string& value);
        void insertFromFile(const string& fileName);
        vector<string> findClosestWords(const string& prefix, int n);
};