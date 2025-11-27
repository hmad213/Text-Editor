#include <iostream>
#include <vector>
#include "Queue.hpp"
using namespace std;

struct TrieNode{
    bool isWord;
    TrieNode* nodes[26];

    TrieNode(){
        for(int i = 0; i < 26; i++) nodes[i] = nullptr;
        isWord = false;
    }
};

class Trie{
    private:
        TrieNode* root;
    public:
        Trie(){
            root = new TrieNode();
        }

        void insert(const string& key){
            TrieNode* cur = root;

            for(int i = 0; i < key.size(); i++){
                char letter = key[i];
                if(letter < 'a' && letter > 'z') return;
                if(cur->nodes[letter - 'a'] == nullptr){
                    cur->nodes[letter - 'a'] = new TrieNode();
                }

                cur = cur->nodes[letter - 'a'];
            }

            cur->isWord = true;
        }

        vector<string> findClosestWord(const string& prefix, int n){
            vector<string> words;
            TrieNode* cur = root;

            for(int i = 0; i < prefix.size(); i++){
                char letter = prefix[i];
                if(cur->nodes[letter - 'a'] == nullptr) return words;
                cur = cur->nodes[letter - 'a'];
            }

            Queue<pair<TrieNode*, string>> q;
            q.enqueue({cur, prefix});
            int i = 0;
            while(!q.isEmpty() && i < n){
                pair<TrieNode*, string> temp = q.peek();
                q.dequeue();
                if(temp.first->isWord){
                    words.push_back(temp.second);
                    i++;
                }

                for(int i = 0; i < 26; i++){
                    if(temp.first->nodes[i] != nullptr){
                        q.enqueue({temp.first->nodes[i], temp.second + char(i + 'a')});
                    }
                }
            }
            return words;
        }
};