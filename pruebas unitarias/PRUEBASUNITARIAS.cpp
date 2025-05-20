#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <utility>
#include <string>
#include <vector>

using namespace std;

// Declaración de funciones externas
int kmpSearch(const string& text, const string& pattern);
pair<int, int> longestPalindrome(const string& s);
pair<int, int> findLongestCommonSubstring(const string& text1, const string& text2);

// -------------------- Pruebas --------------------

TEST_CASE("Prueba KMP") {
    CHECK(kmpSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") == 16);
    CHECK(kmpSearch("aaaaab", "aab") == 4);
    CHECK(kmpSearch("abc", "xyz") == -1);
    CHECK(kmpSearch("", "abc") == -1);
}

TEST_CASE("Prueba Palíndromo más largo") {
    CHECK(longestPalindrome("babad") == pair<int, int>{1, 3}); // "bab" o "aba"
    CHECK(longestPalindrome("cbbd") == pair<int, int>{2, 3}); // "bb"
    CHECK(longestPalindrome("a") == pair<int, int>{1, 1});
    CHECK(longestPalindrome("") == pair<int, int>{0, 0});
}

TEST_CASE("Prueba Substring Común Más Largo") {
    CHECK(findLongestCommonSubstring("abcdef", "zcdemf") == pair<int, int>{3, 5}); // "cde"
    CHECK(findLongestCommonSubstring("abc", "xyz") == pair<int, int>{0, 0});
    CHECK(findLongestCommonSubstring("abc", "abc") == pair<int, int>{1, 3});
}

