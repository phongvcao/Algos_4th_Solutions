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

class RabinKarpTwoDimensional {
private:

    // string pat = "";
    vector< vector< char > > pat;
    int R = 256;
    int M = 0;
    long RM = 1;
    vector< long > patHashVec;
    long Q = 0;
    bool useMonteCarlo = false;

    vector< long > getHashVec( const vector< vector< char > >& key, int iBegin = 0, int jBegin = 0 ) const {
        vector< long > h( pat.size(), 0 );

        for ( int i = 0; i < pat.size(); i++ ) {
            for ( int j = 0; j < pat.back().size(); j++ ) {
                h[ i ] = ( h[ i ] * R + key[ i + iBegin ][ j + jBegin ] ) % Q;
            }
        }

        return h;
    }

    bool check( const vector< vector< char > >& txt, int i, int j ) const {
        if ( useMonteCarlo ) return true;

        for ( int k = 0; k < M; k++ ) {
            if ( pat[ k / pat.size() ][ k % pat.size() ] != txt[ k / pat.size() + i ][ k % pat.size() + j ] ) {
                return false;
            }
        }
        return true;
    }
    
    bool isEqual( const vector< long >& hashVec1, const vector< long >& hashVec2 ) const {
        for ( int i = 0; i < hashVec1.size(); i++ ) {
            if ( hashVec1[ i ] != hashVec2[ i ] ) {
                return false;
            }
        }
        return true;
    }

public:

    RabinKarpTwoDimensional( const vector< vector< char > >& pat, bool useMonteCarlo=false )
        : pat( pat ),
          M( pat.size() * pat.back().size() ),
          RM( 1 ),
          Q( ( long )( pow( 2, 31 ) - 1 ) ),
          useMonteCarlo( useMonteCarlo )
    {
        for ( int i = 1; i < pat.back().size(); i++ ) {
            RM = ( RM * R ) % Q;
        }
        patHashVec = getHashVec( pat );
    }

    virtual ~RabinKarpTwoDimensional() {
        // not implemented
    }

    vector< int > search( const vector< vector< char > >& txt ) const {
        int iN = txt.size();
        int jN = txt.back().size();

        int iM = pat.size();
        int jM = pat.back().size();

        vector< int > rv;

        if ( iN < iM || jN < jM ) return rv;

        for ( int i = iM - 1; i < iN; i++ ) {

            vector< long > txtHashVec = getHashVec( txt, i - iM + 1, 0 );

            if ( isEqual( patHashVec, txtHashVec ) && check( txt, i - iM + 1, 0 ) ) {
                rv = { i - iM + 1, 0 };
                return rv;
            }

            for ( int j = jM; j < jN; j++ ) {
                for ( int k = i - iM + 1; k < i - iM + iM + 1; k++ ) {
                    txtHashVec[ k ] = ( txtHashVec[ k ] + Q - RM * txt[ k ][ j - jM ] % Q ) % Q;
                    txtHashVec[ k ] = ( txtHashVec[ k ] * R + txt[ k ][ j ] ) % Q;

                    int iOffset = i - iM + 1;
                    int jOffset = j - jM + 1;

                    if ( isEqual( patHashVec, txtHashVec ) && check( txt, iOffset, jOffset ) ) {
                        rv.push_back( iOffset );
                        rv.push_back( jOffset );
                        return rv;
                    }
                }
            }
        }

        return rv;
    }

};

int main( int argc, char ** argv ) {

    vector< vector< char > > s = {
        { 'a', 'b', 'a', 'c', 'a', 'd', 'a', 'b' },
        { 'r', 'a', 'b', 'r', 'a', 'c', 'a', 'b' },
        { 'r', 'a', 'c', 'a', 'd', 'a', 'b', 'r' }, 
        { 'a', 'b', 'r', 'a', 'b', 'r', 'a', 'c' },
    };
    vector< vector< vector< char > > > queryVec = {
        {
            { 'a', 'b', 'a' },
            { 'r', 'a', 'b' },
            { 'r', 'a', 'c' }
        },
        {
            { 'b', 'a', 'c' },
            { 'a', 'b', 'r' },
            { 'a', 'c', 'a' }
        },
        {
            { 'r', 'a', 'b' },
            { 'r', 'a', 'c' },
            { 'a', 'b', 'r' }
        },
        {
            { 'a', 'b', 'a' },
            { 'r', 'e', 'b' },
            { 'r', 'a', 'c' }
        },
        {
            { 'd', 'a', 'b' },
            { 'c', 'a', 'b' },
            { 'a', 'b', 'r' }
        },
    };

    cout << "DEBUG: Monte-Carlo : " << endl;
    for ( int i = 0; i < queryVec.size(); i++ ) {
        cout << endl;
        cout << "DEBUG: WORKING ON PATTERN : " << endl;
        for ( int j = 0; j < queryVec[ i ].size(); j++ ) {
            for ( int k = 0; k < queryVec[ i ].back().size(); k++ ) {
                cout << queryVec[ i ][ j ][ k ] << ", ";
            }
            cout << endl;
        }

        RabinKarpTwoDimensional rk( queryVec[ i ], true );
        vector< int > index = rk.search( s );

        if ( ! index.empty() ) {
            printf( "FOUND : s[ %d ][ %d ]\n", index[ 0 ], index[ 1 ] );
        } else {
            printf( "NOT FOUND : !!!\n" );
        }
    }

    cout << endl;
    cout << endl;
    cout << "DEBUG: Las Vegas : " << endl;
    for ( int i = 0; i < queryVec.size(); i++ ) {
        cout << endl;
        cout << "DEBUG: WORKING ON PATTERN : " << endl;
        for ( int j = 0; j < queryVec[ i ].size(); j++ ) {
            for ( int k = 0; k < queryVec[ i ].back().size(); k++ ) {
                cout << queryVec[ i ][ j ][ k ] << ", ";
            }
            cout << endl;
        }

        RabinKarpTwoDimensional rk( queryVec[ i ] );
        vector< int > index = rk.search( s );

        if ( ! index.empty() ) {
            printf( "FOUND : s[ %d ][ %d ]\n", index[ 0 ], index[ 1 ] );
        } else {
            printf( "NOT FOUND : !!!\n" );
        }
    }

    return 0;
}
