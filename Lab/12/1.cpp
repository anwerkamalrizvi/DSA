#include <iostream>
using namespace std;

class StringSearch {
private:
    int comparisons;
    
public:
    StringSearch() : comparisons(0) {}
    
    void bruteForceSearch(const char* text, const char* pattern) {
        comparisons = 0;
        int textLen = 0, patternLen = 0;
        
        while(text[textLen] != '\0') textLen++;
        while(pattern[patternLen] != '\0') patternLen++;
        
        cout << "Positions found: ";
        bool first = true;
        
        for(int i = 0; i <= textLen - patternLen; i++) {
            int j;
            for(j = 0; j < patternLen; j++) {
                comparisons++;
                if(text[i + j] != pattern[j]) {
                    break;
                }
            }
            
            if(j == patternLen) {
                if(!first) cout << ", ";
                cout << i;
                first = false;
            }
        }
        
        cout << "\nTotal comparisons: " << comparisons << endl;
    }
};

int main() {
    StringSearch searcher;
    const char* text = "the quick brown fox jumps over the lazy dog";
    const char* pattern = "the";
    
    cout << "Text: " << text << " " << endl;
    cout << "Pattern: " << pattern << " " << endl;
    
    searcher.bruteForceSearch(text, pattern);
    
    return 0;
}