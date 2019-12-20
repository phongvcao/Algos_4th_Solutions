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

class Brute {
public:

    static int search( const string& pat, const string& txt ) {
        int N = txt.size();
        int M = pat.size();
        int i = 0;
        int j = 0;

        for ( i = 0, j = 0; i < N && j < M; i++ ) {
            if ( pat[ j ] == txt[ i ] ) {
                ++j;
            } else {
                i -= j;
                j = 0;
            }
        }

        if ( j == M ) return i - M;
        else return N;
    }

    static vector< int > findAll( const string& pat, const string& txt ) {
        vector< int > all;

        int N = txt.size();
        int M = pat.size();
        int i = 0;
        int j = 0;

        for ( i = 0, j = 0; i < N; i++ ) {
            if ( pat[ j ] == txt[ i ] ) {
                ++j;
            } else {
                i -= j;
                j = 0;
            }

            if ( j == M ) all.push_back( i - M + 1 );
        }

        return all;
    }

    static void test() {
        string s = "abacadabrabracabracadabrabrabracad";
        vector< string > queryVec = {
            "abracadabra", "rab", "bcara", "rabrabracad", "abacad",
        };

        for ( int i = 0; i < queryVec.size(); i++ ) {
            int index = Brute::search( queryVec[ i ], s );
            if ( index < s.size() ) {
                printf( "FOUND : %-20s : %d\n", queryVec[ i ].c_str(), index );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
        
        for ( int i = 0; i < queryVec.size(); i++ ) {
            vector< int > indexVec = Brute::findAll( queryVec[ i ], s );
            if ( ! indexVec.empty() ) {
                printf( "FOUND : %-20s : ", queryVec[ i ].c_str() );
                for ( int idx : indexVec ) {
                    printf( "%d, ", idx );
                }
                printf( "\n" );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
    }
};

class KMP {
private:

    vector< vector< int > > dfa;
    string pat = "";

public:

    KMP( const string& pat )
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

    virtual ~KMP() {
        // not implemented
    }

    int search( const string& txt ) {
        int N = txt.size();
        int M = pat.size();
        int i = 0;
        int j = 0;

        for ( i = 0, j = 0; i < N && j < M; i++ ) {
            j = dfa[ txt[ i ] ][ j ];
        }

        if ( j == M ) return i - M;
        else return N;
    }

    vector< int > findAll( const string& txt ) const {
        vector< int > all;

        int N = txt.size();
        int M = pat.size();
        int i = 0;
        int j = 0;

        for ( i = 0, j = 0; i < N; i++ ) {
            j = dfa[ txt[ i ] ][ j ];

            if ( j == M ) {
                all.push_back( i - M + 1 );
                j = 0;
            }
        }

        return all;
    }

    static void test() {
        string s = "abacadabrabracabracadabrabrabracad";
        vector< string > queryVec = {
            "abracadabra", "rab", "bcara", "rabrabracad", "abacad",
        };

        for ( int i = 0; i < queryVec.size(); i++ ) {
            KMP kmp( queryVec[ i ] );
            int index = kmp.search( s );
            if ( index < s.size() ) {
                printf( "FOUND : %-20s : %d\n", queryVec[ i ].c_str(), index );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
        
        for ( int i = 0; i < queryVec.size(); i++ ) {
            KMP kmp( queryVec[ i ] );
            vector< int > indexVec = kmp.findAll( s );
            if ( ! indexVec.empty() ) {
                printf( "FOUND : %-20s : ", queryVec[ i ].c_str() );
                for ( int idx : indexVec ) {
                    printf( "%d, ", idx );
                }
                printf( "\n" );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
    }
};

class BoyerMoore {
private:

    vector< int > right;
    string pat = "";

public:

    BoyerMoore( const string& pat )
        : pat( pat )
    {
        int M = pat.size();
        int R = 256;

        right.resize( R, -1 );
        for ( int j = 0; j < M; j++ ) {
            right[ pat[ j ] ] = j;
        }
    }

    virtual ~BoyerMoore() {
        // not implemented
    }

    int search( const string& txt ) const {
        int N = txt.size();
        int M = pat.size();
        int skip = 0;

        for ( int i = 0; i <= N - M; i += skip ) {
            skip = 0;
            for ( int j = M - 1; j >= 0; j-- ) {
                if ( pat[ j ] != txt[ i + j ] ) {
                    skip = j - right[ txt[ i + j ] ];
                    if ( skip < 1 ) skip = 1;
                    break;
                }
            }

            if ( skip == 0 ) return i;
        }
        return N;
    }

    vector< int > findAll( const string& txt ) const {
        vector< int > all;

        int N = txt.size();
        int M = pat.size();
        int skip = 0;

        for ( int i = 0; i <= N - M; i += skip ) {
            skip = 0;
            for ( int j = M - 1; j >= 0; j-- ) {
                if ( pat[ j ] != txt[ i + j ] ) {
                    skip = j - right[ txt[ i + j ] ];
                    if ( skip < 1 ) skip = 1;
                    break;
                }
            }

            if ( skip == 0 ) {
                all.push_back( i );
                skip = 1;
            }
        }
        return all;
    }

    static void test() {
        string s = "abacadabrabracabracadabrabrabracad";
        vector< string > queryVec = {
            "abracadabra", "rab", "bcara", "rabrabracad", "abacad",
        };

        for ( int i = 0; i < queryVec.size(); i++ ) {
            BoyerMoore bm( queryVec[ i ] );
            int index = bm.search( s );
            if ( index < s.size() ) {
                printf( "FOUND : %-20s : %d\n", queryVec[ i ].c_str(), index );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
        for ( int i = 0; i < queryVec.size(); i++ ) {
            BoyerMoore bm( queryVec[ i ] );
            vector< int > indexVec = bm.findAll( s );
            if ( ! indexVec.empty() ) {
                printf( "FOUND : %-20s : ", queryVec[ i ].c_str() );
                for ( int idx : indexVec ) {
                    printf( "%d, ", idx );
                }
                printf( "\n" );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
    }
};

class RabinKarp {
private:

    string pat = "";
    int R = 256;
    int M = 0;
    long RM = 1;
    long Q = 0;
    long patHash = 0;
    bool useMonteCarlo = false;

    long getHash( const string& key ) const {
        long h = 0;
        for ( int i = 0; i < M; i++ ) {
            h = ( h * R + key[ i ] ) % Q;
        }
        return h;
    }

    bool check( const string& txt, int i ) const {
        if ( useMonteCarlo ) return true;

        for ( int j = 0; j < M; j++ ) {
            if ( pat[ j ] != txt[ i + j ] ) {
                return false;
            }
        }
        return true;
    }

public:

    RabinKarp( const string& pat, bool useMonteCarlo=false )
        : pat( pat ),
          M( pat.size() ),
          RM( 1 ),
          Q( ( long )( pow( 2, 31 ) - 1 ) ),
          useMonteCarlo( useMonteCarlo )
    {
        for ( int i = 1; i < M; i++ ) {
            RM = ( RM * R ) % Q;
        }
        patHash = getHash( pat );
    }

    virtual ~RabinKarp() {
        // not implemented
    }

    int search( const string& txt ) const {
        int N = txt.size();
        if ( N < M ) return N;
        long txtHash = getHash( txt );

        if ( patHash == txtHash && check( txt, 0 ) ) {
            return 0;
        }

        for ( int i = M; i < N; i++ ) {
            txtHash = ( txtHash + Q - RM * txt[ i - M ] % Q ) % Q;
            txtHash = ( txtHash * R + txt[ i ] ) % Q;

            int offset = i - M + 1;
            if ( patHash == txtHash && check( txt, offset ) ) {
                return offset;
            }
        }
        return N;
    }

    vector< int > findAll( const string& txt ) const {
        vector< int > all;

        int N = txt.size();
        if ( N < M ) return all;
        long txtHash = getHash( txt );

        if ( patHash == txtHash && check( txt, 0 ) ) {
            all.push_back( 0 );
        }

        for ( int i = M; i < N; i++ ) {
            txtHash = ( txtHash + Q - RM * txt[ i - M ] % Q ) % Q;
            txtHash = ( txtHash * R + txt[ i ] ) % Q;

            int offset = i - M + 1;
            if ( patHash == txtHash && check( txt, offset ) ) {
                all.push_back( offset );
            }
        }

        return all;
    }

    static void test() {
        string s = "abacadabrabracabracadabrabrabracad";
        vector< string > queryVec = {
            "abracadabra", "rab", "bcara", "rabrabracad", "abacad",
        };

        cout << "DEBUG: Monte-Carlo : " << endl;
        for ( int i = 0; i < queryVec.size(); i++ ) {
            RabinKarp rk( queryVec[ i ], true );
            int index = rk.search( s );
            if ( index < s.size() ) {
                printf( "FOUND : %-20s : %d\n", queryVec[ i ].c_str(), index );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }

        cout << endl;
        cout << endl;
        cout << "DEBUG: Las Vegas : " << endl;
        for ( int i = 0; i < queryVec.size(); i++ ) {
            RabinKarp rk( queryVec[ i ] );
            int index = rk.search( s );
            if ( index < s.size() ) {
                printf( "FOUND : %-20s : %d\n", queryVec[ i ].c_str(), index );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }

        cout << "DEBUG: Monte-Carlo : " << endl;
        for ( int i = 0; i < queryVec.size(); i++ ) {
            RabinKarp rk( queryVec[ i ], true );
            vector< int > indexVec = rk.findAll( s );
            if ( ! indexVec.empty() ) {
                printf( "FOUND : %-20s : ", queryVec[ i ].c_str() );
                for ( int idx : indexVec ) {
                    printf( "%d, ", idx );
                }
                printf( "\n" );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }

        cout << endl;
        cout << endl;
        cout << "DEBUG: Las Vegas : " << endl;
        for ( int i = 0; i < queryVec.size(); i++ ) {
            RabinKarp rk( queryVec[ i ] );
            vector< int > indexVec = rk.findAll( s );
            if ( ! indexVec.empty() ) {
                printf( "FOUND : %-20s : ", queryVec[ i ].c_str() );
                for ( int idx : indexVec ) {
                    printf( "%d, ", idx );
                }
                printf( "\n" );
            } else {
                printf( "NOT FOUND : %s!!!\n", queryVec[ i ].c_str() );
            }
        }
    }
};

int main( int argc, char ** argv ) {

    Brute::test();
    KMP::test();
    BoyerMoore::test();
    RabinKarp::test();

    return 0;
}
