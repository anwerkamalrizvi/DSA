#include <iostream>
using namespace std;

class BoyerMoore {
private:
    static const int CHAR_SIZE = 256;
    
    int stringLength(const char* str) {
        int len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
    
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    void badCharHeuristic(const char* pattern, int patLen, int badChar[]) {
        for(int i = 0; i < CHAR_SIZE; i++) {
            badChar[i] = -1;
        }
        
        for(int i = 0; i < patLen; i++) {
            badChar[(int)pattern[i]] = i;
        }
    }
    
    void computeSuffixes(const char* pattern, int patLen, int* suffix) {
        suffix[patLen - 1] = patLen;
        int g = patLen - 1;
        int f = 0;
        
        for(int i = patLen - 2; i >= 0; i--) {
            if(i > g && suffix[i + patLen - 1 - f] < i - g) {
                suffix[i] = suffix[i + patLen - 1 - f];
            } else {
                if(i < g) {
                    g = i;
                }
                f = i;
                while(g >= 0 && pattern[g] == pattern[g + patLen - 1 - f]) {
                    g--;
                }
                suffix[i] = f - g;
            }
        }
    }
    
    void goodSuffixHeuristic(const char* pattern, int patLen, int* shift) {
        int* suffix = new int[patLen];
        computeSuffixes(pattern, patLen, suffix);
        
        for(int i = 0; i < patLen; i++) {
            shift[i] = patLen;
        }
        
        int j = 0;
        for(int i = patLen - 1; i >= 0; i--) {
            if(suffix[i] == i + 1) {
                for(; j < patLen - 1 - i; j++) {
                    if(shift[j] == patLen) {
                        shift[j] = patLen - 1 - i;
                    }
                }
            }
        }
        
        for(int i = 0; i <= patLen - 2; i++) {
            shift[patLen - 1 - suffix[i]] = patLen - 1 - i;
        }
        
        delete[] suffix;
    }
    
public:
    void search(const char* text, const char* pattern) {
        int textLen = stringLength(text);
        int patLen = stringLength(pattern);
        
        int* badChar = new int[CHAR_SIZE];
        int* goodSuffix = new int[patLen];
        
        badCharHeuristic(pattern, patLen, badChar);
        goodSuffixHeuristic(pattern, patLen, goodSuffix);
        
        cout << "Positions found: [";
        bool first = true;
        int shift = 0;
        
        while(shift <= textLen - patLen) {
            int j = patLen - 1;
            
            while(j >= 0 && pattern[j] == text[shift + j]) {
                j--;
            }
            
            if(j < 0) {
                if(!first) cout << ", ";
                cout << shift;
                first = false;
                shift += goodSuffix[0];
            } else {
                int badCharShift = j - badChar[(int)text[shift + j]];
                int goodSuffixShift = goodSuffix[j];
                shift += max(badCharShift, goodSuffixShift);
            }
        }
        
        cout << "]" << endl;
        
        delete[] badChar;
        delete[] goodSuffix;
    }
};

int main() {
    BoyerMoore bm;
    const char* dna = "ACGTACGTGACG";
    const char* pattern = "ACG";
    
    cout << "DNA: " << dna << " " << endl;
    cout << "Pattern: " << pattern << " " << endl;
    
    bm.search(dna, pattern);
    
    return 0;
}