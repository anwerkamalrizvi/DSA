#include <iostream>
using namespace std;

class KMP {
private:
    int stringLength(const char* str) {
        int len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
    
    void computeLPSArray(const char* pattern, int patLen, int* lps) {
        int len = 0;
        lps[0] = 0;
        int i = 1;
        
        while(i < patLen) {
            if(pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if(len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
    
public:
    void search(const char* text, const char* pattern) {
        int textLen = stringLength(text);
        int patLen = stringLength(pattern);
        
        int* lps = new int[patLen];
        computeLPSArray(pattern, patLen, lps);
        
        cout << "LPS Array: [";
        for(int i = 0; i < patLen; i++) {
            if(i > 0) cout << ", ";
            cout << lps[i];
        }
        cout << "]" << endl<<endl;
        
        cout << "Positions found: ";
        bool first = true;
        int i = 0;
        int j = 0;
        
        while(i < textLen) {
            if(pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if(j == patLen) {
                if(!first) cout << ", ";
                cout << (i - j);
                first = false;
                j = lps[j - 1];
            } else if(i < textLen && pattern[j] != text[i]) {
                if(j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        cout<< endl;
        
        delete[] lps;
    }
};

int main() {
    KMP kmp;
    const char* text = "ababababc";
    const char* pattern = "abab";
    
    cout << "Text: " << text << " " << endl;
    cout << "Pattern: " << pattern << " " << endl;
    
    kmp.search(text, pattern);
    
    return 0;
}