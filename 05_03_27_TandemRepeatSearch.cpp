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

class KMPTandemRepeat {
private:

    vector< vector< int > > dfa;
    string pat = "";

public:

    KMPTandemRepeat( const string& pat )
        : pat( pat )
    {
        int R = 256;
        int M = pat.size();

        dfa.resize( R, vector< int >( M, 0 ) );
        dfa[ pat[ 0 ] ][ 0 ] = 1;

        for ( int j = 1, X = 0; j < M; j++ ) {
            for ( int c = 0; c < R; c++ ) {
                dfa[ c ][ j ] = dfa[ c ][ X ];
            }
            dfa[ pat[ j ] ][ j ] = j + 1;
            X = dfa[ pat[ j ] ][ X ];
        }
    }

    virtual ~KMPTandemRepeat() {
        // not implemented
    }

    int getLongestTandemIndex( const string& txt ) const {
        int N = txt.size();
        int M = pat.size();
        int i = 0;
        int j = 0;

        vector< int > orgPos( N, -1 );
        vector< int > count( N, 0 );

        cout << endl;

        for ( i = 0, j = 0; i < N; i++ ) {
            j = dfa[ txt[ i ] ][ j ];
            // If pattern found
            // - Check the previous position at i - M to see if it has further orgPos
            //   - If it does, increment count[ orgPos[ i - M ] ]++
            //   - If it doesn't, set orgPos[ i - M ] = i - M && count[ i - M ] = 1
            if ( j == M ) {
                // cout << "DEBUG: FOUND AT : i - M + 1 : " << i - M + 1 << endl;
                if ( i - M + 1 - M >= 0 && orgPos[ i - M + 1 - M ] != -1 ) {
                    ++count[ orgPos[ i - M + 1 - M ] ];
                    orgPos[ i - M + 1 ] = orgPos[ i - M + 1 - M ];
                } else {
                    orgPos[ i - M + 1 ] = i - M + 1;
                    count[ i - M + 1 ] = 1;
                }

                i = i - M + 1;
                j = 0;
            }
        }

        // Find out the longest tandem
        int longestTandemLength = 0;
        int longestTandemIndex = -1;
        for ( int i = 0; i < N; i++ ) {
            // cout << "DEBUG: i : " << i << " ; count : " << count[ i ] << " ; orgPos : " << orgPos[ i ] << endl;
            if ( count[ i ] > longestTandemLength ) {
                longestTandemLength = count[ i ];
                longestTandemIndex = i;
            }
        }

        return longestTandemIndex;
    }

};

int main( int argc, char ** argv ) {

    string s = "abcabcababcababcababcab";
    vector< string > queryVec = { "abcab", "abc" };

    for ( int i = 0; i < queryVec.size(); i++ ) {
        KMPTandemRepeat kmp( queryVec[ i ] );
        cout << "DEBUG : kmp.getLongestTandemIndex( " << queryVec[ i ] << " ) : " << kmp.getLongestTandemIndex( s ) << endl;
    }

    return 0;
}
