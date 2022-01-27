// Datei: unit_tests.cpp
#include "catch.h"
#include "suchen.h"

TEST_CASE("Zeichenkette suchen, Text mit Laenge groesser 1, Zeichenkette mit Laenge groesser 1") 
{
    REQUIRE(zeichenkette_suchen("abcdabcde", "cda") == 2);
    REQUIRE(zeichenkette_suchen("abcdabcde", "de") == 7);
    REQUIRE(zeichenkette_suchen("abcdabcde", "dex") == -1);
    REQUIRE(zeichenkette_suchen("abcdabcde", "xyz") == -1);
    REQUIRE(zeichenkette_suchen("abcdabcde", "abcdabcd") == 0);
    REQUIRE(zeichenkette_suchen("abcdabcde", "abcdabcdx") == -1);
}
TEST_CASE("Zeichenkette suchen, Text mit Laenge groesser 1, Zeichenkette mit Laenge 1") 
{
    REQUIRE(zeichenkette_suchen("abcdabcde", "a") == 0);
    REQUIRE(zeichenkette_suchen("abcdabcde", "c") == 2);
    REQUIRE(zeichenkette_suchen("abcdabcde", "e") == 8);
    REQUIRE(zeichenkette_suchen("abcdabcde", "x") == -1);
}

TEST_CASE("Zeichenkette suchen, Text mit Laenge 1") 
{
    REQUIRE(zeichenkette_suchen("a", "a") == 0);
    REQUIRE(zeichenkette_suchen("a", "c") == -1);
    REQUIRE(zeichenkette_suchen("a", "xy") == -1);
    REQUIRE(zeichenkette_suchen("a", "aa") == -1);
}

TEST_CASE("Zeichenkette suchen, leerer Text") 
{
    REQUIRE(zeichenkette_suchen("", "") == -1);
    REQUIRE(zeichenkette_suchen("", "a") == -1);
    REQUIRE(zeichenkette_suchen("", "abc") == -1);
}

TEST_CASE("Testfaelle Ergaenzung")
{
    REQUIRE(zeichenkette_suchen("abcdefg", "bcd99") == -1);
    REQUIRE(zeichenkette_suchen("abcdefg", "efg") == 4);
    REQUIRE(zeichenkette_suchen("abc", "abcde") == -1);
    REQUIRE(zeichenkette_suchen("012 abc abc 89", "abc") == 4);
    REQUIRE(zeichenkette_suchen("xy abc abcdefgh", "abcde") == 7);
    REQUIRE(zeichenkette_suchen("xyz 123 456 abc", "123 4") == 4);
    REQUIRE(zeichenkette_suchen("abc defg", "abc d") == 0);
}

TEST_CASE("Eigene Testfaelle")
{
    REQUIRE(zeichenkette_suchen("......................................", ".") == 0);
    REQUIRE(zeichenkette_suchen("!!=)&8&%?!", ".") == -1);
    REQUIRE(zeichenkette_suchen("!!)&8&%?!=", "=") == 9);
    REQUIRE(zeichenkette_suchen("abcde", "d") == 3);
    REQUIRE(zeichenkette_suchen("abcdef G", "G") == 7);
    REQUIRE(zeichenkette_suchen("abcd3e", "3") == 4);
    REQUIRE(zeichenkette_suchen("Dies, mein Text.", "x") == 13);
    REQUIRE(zeichenkette_suchen("Mein Text, hier. Thx-", "-") == -1); // Über der Laenge
    REQUIRE(zeichenkette_suchen("abcde de", " ") == 5);
    REQUIRE(zeichenkette_suchen("12 ab cde de", " ") == 2);
    REQUIRE(zeichenkette_suchen("Hallo Welt!", "!") == 10);
    REQUIRE(zeichenkette_suchen("1 2 3 45 66!", "66") == 9);
}