//
// Created by Phong Cao.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
#include <iterator>
#include <utility>
#include <algorithm>
#include <memory>
#include <cctype>
#include <stdexcept>
#include <limits>
#include <numeric>

//----< iostream >----------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----< cstdio >------------//
using std::printf;
using std::fprintf;
using std::sprintf;
using std::snprintf;

//----< iomanip >-----------//
using std::setprecision;
using std::setw;

//----< ios >---------------//
using std::hex;
using std::dec;
using std::oct;
using std::fixed;

//----< sstream >-----------//
using std::ostringstream;
using std::istringstream;

//----< fstream >-----------//
using std::ofstream;
using std::ifstream;

//----< string >------------//
using std::getline;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

//----< cmath >-------------//
using std::sqrt;
using std::pow;
using std::log;             // log( <arg> )
using std::exp;             // e ^ <arg>
using std::abs;
using std::floor;           // Round down to nearest integer double
using std::ceil;            // Round up to nearest integer double
using std::trunc;           // Truncate the fractional part to get the integer part
using std::round;           // Round to nearest integer double

//----< cstdlib >-----------//
using std::rand;
using std::srand;

//----< ctime >-------------//
using std::time;

//----< functional >--------//
using std::hash;
using std::greater;         // lhs > rhs. Used for MinPQ
using std::less;            // lhs < rhs. Used for MaxPQ. Default for priority_queue<>
using std::less_equal;
using std::greater_equal;

//----< array >-------------//
using std::array;           // Fixed & Unordered Array

//----< vector >------------//
using std::vector;          // Resizable & Unordered Array

//----< map >---------------//
using std::map;             // Ordered Map (Red-Black Tree)

//----< unordered_map >-----//
using std::unordered_map;   // HashMap (SeparateChainingHashST)

//----< set >---------------//
using std::set;             // Ordered Set (Red-Black Tree)

//----< unordered_set >-----//
using std::unordered_set;   // HashSet (SeparateChainingHashST)

//----< list >--------------//
using std::list;            // Doubly-Linked List with size() ( O( 1 ) )

//----< forward_list >------//
using std::forward_list;    // Singly-Linked List without size() function ( so O( N ) if we need to get size() )

//----< deque >-------------//
using std::deque;           // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque

//----< queue >-------------//
using std::queue;           // Non-Iterable & Use std::deque as underlying data structure
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

//----< stack >-------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----< iterator >----------//
using std::next;            // Return an advanced iter without changing original iter
using std::prev;            // Return an decremented iter without changing original iter
using std::distance;        // Calculate distance between 2 iterators

//----< utility >-----------//
using std::pair;
using std::make_pair;
using std::move;            // Move resources between objects - typically used with std::unique_ptr<T>

//----< algorithm >---------//
using std::fill;
using std::max;
using std::min;
using std::find;
using std::reverse;
using std::sort;
using std::remove;

//----< memory >------------//
using std::make_unique;
using std::unique_ptr;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

//----< cctype >------------//
using std::isalnum;
using std::isalpha;
using std::islower;
using std::isupper;
using std::isdigit;
using std::isspace;         // Check whether char is whitespace character (space, newline, tab, etc. )
using std::isblank;         // Check whether char is blank character ( space or tab )
using std::tolower;
using std::toupper;

//----< stdexcept >---------//
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----< limits >------------//
using std::numeric_limits;

//----< numeric >-----------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

class Alphabet {
private:

    string alphabet;
    unordered_map< char, int > indices;

public:

    Alphabet( string s )
        : alphabet( s )
    {
        for ( int i = 0; i < s.size(); ++i ) {
            indices.insert( { s[ i ], i } );
        }
    }

    char toChar( int index ) const {
        return alphabet[ index ];
    }

    int toIndex( char c ) {
        return indices[ c ];
    }

    bool contains( char c ) const {
        return indices.find( c ) != indices.end();
    }

    int R() const {
        return alphabet.size();
    }

    int lgR() const {
        return log( alphabet.size() ) / log( 2 );
    }

    vector< int > toIndices( const string& s ) {
        vector< int > rvVec;
        for ( char c : s ) {
            rvVec.push_back( indices[ c ] );
        }
        return rvVec;
    }

    string toChars( vector< int > indices ) const {
        string rv = "";
        for ( int idx : indices ) {
            string cStr( 1, alphabet[ indices[ idx ] ] );
            rv += cStr;
        }
        return rv;
    }

};

class RadixLSDString {
public:

    static void sort( vector< string >& a, int W, string alphabetStr ) {
        Alphabet alphabet( alphabetStr );

        int N = a.size();
        int R = alphabet.R();
        vector< string > aux( N );

        for ( int d = W - 1; d >= 0; d-- ) {
            vector< int > count( R + 1, 0 );

            for ( int i = 0; i < N; i++ ) {
                ++count[ alphabet.toIndex( a[ i ][ d ] ) + 1 ];
            }

            for ( int r = 0; r < R; r++ ) {
                count[ r + 1 ] += count[ r ];
            }

            for ( int i = 0; i < N; i++ ) {
                aux[ count[ alphabet.toIndex( a[ i ][ d ] ) ]++ ] = a[ i ];
            }

            for ( int i = 0; i < N; i++ ) {
                a[ i ] = aux[ i ];
            }
        }

    }

};

class RadixMSDString {
private:

    static int R;
    static int M;
    static Alphabet * alphabet;
    static vector< string > aux;

    static bool isLess( const string& s1, const string& s2, int d ) {
        int minLength = min( s1.size(), s2.size() );
        for ( int i = d; i < minLength; i++ ) {
            if ( alphabet->toIndex( s1[ i ] ) < alphabet->toIndex( s2[ i ] ) ) {
                return true;
            }
        }

        if ( s1.size() < s2.size() ) return true;
        return false;
    }

    static void exchange( vector< string >& a, int i, int j ) {
        string temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    static void insertionSort( vector< string >& a, int low, int high, int d ) {
        for ( int i = low; i <= high; i++ ) {
            for ( int j = i; j > low && isLess( a[ j ], a[ j - 1 ], d ); j-- ) {
                exchange( a, j, j - 1 );
            }
        }
    }

    static int charAt( const string& s, int d ) {
        return d < s.size() ? s[ d ] : -1;
    }

    static void sort( vector< string >& a, int low, int high, int d ) {
        if ( high <= low + M ) {
            insertionSort( a, low, high, d );
            return;
        }

        vector< int > count( R + 2, 0 );

        for ( int i = low; i <= high; i++ ) {
            ++count[ alphabet->toIndex( charAt( a[ i ], d ) ) + 2 ];
        }

        for ( int r = 0; r < R + 1; r++ ) {
            count[ r + 1 ] += count[ r ];
        }

        for ( int i = low; i <= high; i++ ) {
            aux[ count[ alphabet->toIndex( charAt( a[ i ], d ) ) + 1 ]++ ] = a[ i ];
        }

        for ( int i = low; i <= high; i++ ) {
            a[ i ] = aux[ i - low ];
        }

        for ( int r = 0; r < R; r++ ) {
            sort( a, low + count[ r ], low + count[ r + 1 ] - 1, d + 1 );
        }
    }

public:

    static void sort( vector< string >& a, string alphabetStr ) {
        Alphabet abc( alphabetStr );
        R = abc.R();
        alphabet = &abc;
        aux.resize( a.size() );
        sort( a, 0, a.size() - 1, 0 );
    }

};

int RadixMSDString::R = 256;
int RadixMSDString::M = 5;
vector< string > RadixMSDString::aux;
Alphabet * RadixMSDString::alphabet;

int main( int argc, char ** argv ) {

    // LSD String Sort
    vector< string > strVec = {
        "4PGC938",
        "2IYE230",
        "3CIO720",
        "1ICK750",
        "1OHV845",
        "4JZY524",
        "1ICK750",
        "3CIO720",
        "1OHV845",
        "1OHV845",
        "2RLA629",
        "2RLA629",
        "3ATW723",
    };

    // Calculate alphabet
    set< char > uniqueChars;
    string alphabetStr = "";

    for ( string s : strVec ) {
        for ( char c : s ) {
            if ( uniqueChars.find( c ) == uniqueChars.end() ) {
                uniqueChars.insert( c );
            }
        }
    }
    for ( char c : uniqueChars ) {
        string cStr( 1, c );
        alphabetStr += cStr;
    }

    RadixLSDString::sort( strVec, strVec[ 0 ].size(), alphabetStr );

    cout << endl;
    for ( const string& s : strVec ) {
        cout << s << endl;
    }
    cout << endl;
    
    // MSD String Sort
    vector< string > strVec1 = {
        "she",
        "sells",
        "seashells",
        "by",
        "the",
        "seashore",
        "the",
        "shells",
        "she",
        "sells",
        "are",
        "surely",
        "seashells",
    };
    
    // Calculate alphabet
    uniqueChars.clear();
    alphabetStr = "";

    for ( string s : strVec1 ) {
        for ( char c : s ) {
            if ( uniqueChars.find( c ) == uniqueChars.end() ) {
                uniqueChars.insert( c );
            }
        }
    }
    for ( char c : uniqueChars ) {
        string cStr( 1, c );
        alphabetStr += cStr;
    }
    
    RadixMSDString::sort( strVec1, alphabetStr );

    cout << endl;
    for ( const string& s : strVec1 ) {
        cout << s << endl;
    }
    cout << endl;

    return 0;
}
