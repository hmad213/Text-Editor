#include <Autocomplete.h>

Autocomplete::Autocomplete(){
    wordTrie = new Trie();
    insertFromFile("dictionary.txt");
}

Autocomplete::~Autocomplete(){
    delete wordTrie;
}

void Autocomplete::insertString(const string& value){
    wordTrie->insert(value);
}

void Autocomplete::insertFromFile(const string& fileName){
    ifstream file(fileName);

    if (!file.is_open()) throw invalid_argument("File does not exist");

    string line;
    while (getline(file, line)) {
        insertString(line);
    }

    file.close();
}

DynamicArray<string> Autocomplete::findClosestWords(const string& prefix, int n){
    return wordTrie->findClosestWord(prefix, n);
}