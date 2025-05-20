#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// -------------------- Funciones --------------------

string readFileContent(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return "";
    }

    string content, line;
    while (getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }
    return content;
}

vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0, i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
    return lps;
}

int kmpSearch(const string& text, const string& pattern) {
    int n = text.length(), m = pattern.length();
    if (m == 0) return -1;

    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
            if (j == m) return (i - j) + 1;
        }
        else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return -1;
}

pair<int, int> longestPalindrome(const string& s) {
    if (s.empty()) return { 0, 0 };
    int n = s.length(), maxLength = 1, start = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) dp[i][i] = true;

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (int k = 3; k <= n; k++) {
        for (int i = 0; i < n - k + 1; i++) {
            int j = i + k - 1;
            if (dp[i + 1][j - 1] && s[i] == s[j]) {
                dp[i][j] = true;
                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }

    return { start + 1, start + maxLength };
}

pair<int, int> findLongestPalindromeInFile(const string& fileName) {
    return longestPalindrome(readFileContent(fileName));
}

pair<int, int> findLongestCommonSubstring(const string& text1, const string& text2) {
    int m = text1.length(), n = text2.length(), maxLength = 0, endIndex = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
        }
    }

    if (maxLength == 0) return { 0, 0 };
    return { endIndex - maxLength + 2, endIndex + 1 };
}

// -------------------- Main --------------------

int main() {
    string transmissions[2] = { "transmission1.txt", "transmission2.txt" };
    string maliciousCodes[3] = { "mcode1.txt", "mcode2.txt", "mcode3.txt" };

    // Parte 1: KMP búsqueda de patrones
    for (int i = 0; i < 2; i++) {
        string transmission = readFileContent(transmissions[i]);
        if (transmission.empty()) continue;

        for (int j = 0; j < 3; j++) {
            string pattern = readFileContent(maliciousCodes[j]);
            if (pattern.empty()) continue;

            int pos = kmpSearch(transmission, pattern);
            if (pos != -1) cout << "true " << pos << endl;
            else cout << "false" << endl;
        }
    }

    // Parte 2: Palíndromos más largos
    for (const auto& file : transmissions) {
        auto result = findLongestPalindromeInFile(file);
        cout << result.first << " " << result.second << endl;
    }

    // Parte 3: Substring común más largo
    string t1 = readFileContent(transmissions[0]);
    string t2 = readFileContent(transmissions[1]);
    if (!t1.empty() && !t2.empty()) {
        auto lcs = findLongestCommonSubstring(t1, t2);
        cout << lcs.first << " " << lcs.second << endl;
    }

    return 0;
}

