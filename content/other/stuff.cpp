// Setzt deutsche Tastaturlayout / toggle mit alt + space
setxkbmap de
setxkbmap de,us -option grp:alt_space_toggle

// Set mit eigener Sortierfunktion.
set<point2, decltype(comp)> set1(comp);

// STL-Debugging, Compiler flags.
-D_GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG

// 128-Bit Integer/Float. Muss zum Einlesen/Ausgeben
// in einen int oder long long gecastet werden.
__int128, __float128

// float mit Decimaldarstellung
#include <decimal/decimal>
std::decimal::decimal128

// 1e18 < INF < Max_Value / 2
constexpr ll INF = 0x3FFF'FFFF'FFFF'FFFFll;
// 1e9 < INF < Max_Value / 2
constexpr int INF = 0x3FFF'FFFF;
