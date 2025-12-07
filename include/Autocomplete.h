#pragma once
#include <Trie.hpp>
#include <iostream>
#include <fstream>
#include "DynamicArray.hpp"
using namespace std;

class Autocomplete{
    private:
        Trie* wordTrie;
    public:
        Autocomplete();
        ~Autocomplete();

        void insertString(const string& value);
        void insertFromFile(const string& fileName);
        DynamicArray<string> findClosestWords(const string& prefix, int n);
};