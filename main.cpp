#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>


using namespace std;

const int ALPHABET_SIZE = 3;

char randomChar() {
    return 'a' + rand() % ALPHABET_SIZE;
}

string generateString(int stringSize) {
    string result;
    for (int i = 0; i < stringSize; i++) {
        result += randomChar();
    }
    return result;
}

//Naiwne wyszukiwanie

vector <int> naiveSearch(string& pattern, string& text) {
    vector <int> found;

    cout << endl;
    cout << "Naiwne wyszukiwanie" << endl;
    if(pattern.length() > text.length()) {
        return found;
    }
    for(int i = 0; i<= (text.length() - pattern.length()); i++) {
        if (pattern == text.substr(i, pattern.length())){
            found.push_back(i);
            // cout << "Mamy wzorzec na i = " + to_string(i) + " tekstu" << endl;
        }
    }
    return found;
}


// Rabin karp

int getCharNumber(char& ch) {
    return ch - 'a' + 1;
}

int horner(int wsp[],int st, int x)
{
    if(st==0)
        return wsp[0];

    return x*horner(wsp,st-1,x)+wsp[st];
}

int calculateHash(string& x, int patternLen)
{
    vector <int> wsp;

    for(int i = 0; i< patternLen; i++) {
        wsp.push_back(getCharNumber(x[i]));
    }
    int* wspArr = &wsp[0];

    return horner(wspArr, patternLen - 1, ALPHABET_SIZE) % (RAND_MAX / 11);
}

int calculateAlphabetSizePowerPatternLength(int patternLen) {
    int result = ALPHABET_SIZE;
    for(int i = 0; i < patternLen -1; i++) {
        result *= ALPHABET_SIZE;
    }
    return result;
}

int recalculateHashForText(string& text, int oldHash, int patternLen, int oldS) {
    int result = oldHash * ALPHABET_SIZE;
    result += getCharNumber(text[oldS + patternLen]);
    result -= (calculateAlphabetSizePowerPatternLength(patternLen) * getCharNumber(text[oldS ]));
    return result  % (RAND_MAX / 11);
}

vector <int> rabinKarpSearch(string& pattern, string& text) {
    vector <int> found;

    cout << endl;
    cout << "Karpa Rabina wyszukiwanie" << endl;
    if(pattern.length() > text.length()) {
        return found;
    }

    int patternHash = calculateHash(pattern, pattern.length());
    int textHash = calculateHash(text, pattern.length());
    for(int i = 0; i<= (text.length() - pattern.length()); i++) {
        if(patternHash == textHash){
            found.push_back(i);
        }
        textHash = recalculateHashForText(text, textHash, pattern.length(), i);
    }
    return found;
}

void testAlgorithm() {
    srand(time(NULL));
    string pattern = "ab";
    string text = "abacab";

    cout << "Pattern: " + pattern << endl;
    cout << "Text: " + text << endl;

    vector <int> found = rabinKarpSearch(pattern, text);

    cout << endl;
    cout << "Znalezione na i rownym: " << endl;
    for( size_t i = 0; i < found.size(); i++ )
        cout << found[i] << endl;
}

int main() {
    string pattern = "ab";
    string text = "abac";
    testAlgorithm();

    //cout << calculateAlphabetSizePowerPatternLength(pattern.length()) << endl;
}

