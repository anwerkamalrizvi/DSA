#include <iostream>
using namespace std;

class RabinKarp {
private:
    static const int d = 256;
    static const int q = 101;
    
    int stringLength(const char* str) {
        int len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
    
    bool matchStrings(const char* text, const char* pattern, int start, int patLen) {
        for(int i = 0; i < patLen; i++) {
            if(text[start + i] != pattern[i]) {
                return false;
            }
        }
        return true;
    }
    
public:
    void search(const char* text, const char* pattern) {
        int textLen = stringLength(text);
        int patLen = stringLength(pattern);
        int h = 1;
        int patHash = 0;
        int textHash = 0;
        
        for(int i = 0; i < patLen - 1; i++) {
            h = (h * d) % q;
        }
        
        for(int i = 0; i < patLen; i++) {
            patHash = (d * patHash + pattern[i]) % q;
            textHash = (d * textHash + text[i]) % q;
        }
        
        cout << "Positions found: ";
        bool first = true;
        int falsePositives = 0;
        
        for(int i = 0; i <= textLen - patLen; i++) {
            if(patHash == textHash) {
                if(matchStrings(text, pattern, i, patLen)) {
                    if(!first) cout << ", ";
                    cout << i;
                    first = false;
                } else {
                    falsePositives++;
                }
            }
            
            if(i < textLen - patLen) {
                textHash = (d * (textHash - text[i] * h) + text[i + patLen]) % q;
                if(textHash < 0) {
                    textHash = textHash + q;
                }
            }
        }
        
        cout << "\nFalse positive hash matches: " << falsePositives << endl;
    }
};

int main() {
    RabinKarp rk;
    const char* text = "Data structures and algorithms are fun. Algorithms make tasks easier.";
    const char* pattern = "Algorithms";
    
    cout << "Text: " << text << " " << endl;
    cout << "Pattern: " << pattern << " " << endl;
    
    rk.search(text, pattern);
    
    return 0;
}