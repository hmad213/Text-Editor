#include <Autocomplete.h>

Autocomplete::Autocomplete(){
    wordTrie = new Trie();
}

Autocomplete::~Autocomplete(){
    delete wordTrie;
}

void Autocomplete::insertString(const string& value){
    wordTrie->insert(value);
}

void Autocomplete::insertFromFile(const string& fileName){
    ifstream file("C:\\Users\\GIGABYTE\\Desktop\\dictionary.txt");

    if (!file.is_open()) throw invalid_argument("File does not exist");

    string line;
    while (getline(file, line)) {
        insertString(line);
    }

    file.close();
}

vector<string> Autocomplete::findClosestWords(const string& prefix, int n){
    return wordTrie->findClosestWord(prefix, n);
}