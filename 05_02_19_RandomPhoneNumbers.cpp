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

template< typename Value >
class TrieST {
private:

    static const int R = 10;

    class Node {
    public:
        vector< Node * > next;
        unique_ptr< Value > val;
        int index = -1;

        Node()
            : next( R, NULL )
        {
            // not implemented
        }

        virtual ~Node() {
            // not implemented
        }
    };

    Node * newNode() {
        nodes.push_back( make_unique< Node >() );
        nodes.back()->index = nodes.size() - 1;
        return nodes.back().get();
    }

    void freeNode( Node * h ) {
        if ( h->index < nodes.size() - 1 ) {
            nodes[ h->index ].swap( nodes.back() );
            nodes[ h->index ]->index = h->index;
        }
        nodes.pop_back();
    }

    Node * get( Node * h, const string& key, int d ) const {
        if ( ! h ) return NULL;
        if ( d == key.size() ) return h;
        int c = key[ d ] - '0';
        return get( h->next[ c ], key, d + 1 );
    }

    void getKeysWithPrefix( Node * h, string prefix, queue< string >& results ) const {
        if ( ! h ) return;
        if ( h->val ) results.push( prefix );
        for ( int c = 0; c < R; c++ ) {
            getKeysWithPrefix( h->next[ c ], prefix + ( char ) ( '0' + c ), results );
        }
    }

    void getKeysThatMatch( Node * h, string prefix, const string& pattern, queue< string >& results ) const {
        if ( ! h ) return;
        int d = prefix.size();
        if ( h->val && d == pattern.size() ) results.push( prefix );

        char c = pattern[ d ];

        if ( c == '.' ) {
            for ( int ch = 0; ch < R; ch++ ) {
                getKeysThatMatch( h->next[ ch ], prefix + ( char ) ( '0' + ch ), results );
            }
        } else {
            getKeysThatMatch( h->next[ c - '0' ], prefix + ( char ) ( c ), results );
        }
    }

    int getLongestPrefixOf( Node * h, const string& query, int d, int length ) const {
        if ( ! h ) return length;
        if ( h->val ) length = d;
        if ( d == query.size() ) return length;

        char c = query[ d ];
        return getLongestPrefixOf( h->next[ c - '0' ], query, d + 1, length );
    }

    Node * put( Node * h, string key, Value val, int d ) {
        if ( ! h ) {
            h = newNode();
        }

        if ( d == key.size() ) {
            if ( ! h->val ) ++N;
            h->val = make_unique< Value >( val );
            return h;
        }

        char c = key[ d ];
        h->next[ c - '0' ] = put( h->next[ c - '0' ], key, val, d + 1 );
        return h;
    }

    Node * deleteKey( Node * h, const string& key, int d ) {
        if ( ! h ) return NULL;

        if ( d == key.size() ) {
            if ( h->val ) --N;
            h->val = NULL;
        } else {
            char c = key[ d ];
            h->next[ c - '0' ] = deleteKey( h->next[ c - '0' ], key, d + 1 );
        }

        if ( h->val ) return h;
        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) return h;
        }

        freeNode( h );
        return NULL;
    }

    string toString( Node * h ) const {
        ostringstream oss;
        oss << " ; children : ";
        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) {
                oss << ( char ) ( '0' + c ) << ", ";
            }
        }
        oss << endl;

        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) {
                oss << "index : " << h->next[ c ]->index << " ; char : "
                    << c << " ; val : ";
                if ( h->next[ c ]->val ) {
                    oss << *( h->next[ c ]->val );
                } else {
                    oss << "NULL";
                }
                oss << toString( h->next[ c ] );
            }
        }
        return oss.str();
    }

    vector< unique_ptr< Node > > nodes;
    int N = 0;
    Node * root = NULL;

public:

    TrieST() {
        // not implemented
    }

    virtual ~TrieST() {
        // not implemented
    }

    int size() const {
        return N;
    }

    bool empty() const {
        return size() == 0;
    }

    Value get( const string& key ) const {
        Node * rv = get( root, key, 0 );
        if ( ! rv || ! rv->val ) {
            throw runtime_error( "Key not exist : " + key );
        } else {
            return *( rv->val );
        }
    }

    bool contains( const string& key ) const {
        try {
            Value val = get( key );
        } catch ( const runtime_error& e ) {
            return false;
        }
        return true;
    }

    queue< string > getKeys() const {
        return getKeysWithPrefix( "" );
    }

    queue< string > getKeysWithPrefix( const string& prefix ) const {
        queue< string > results;
        Node * h = get( root, prefix, 0 );
        getKeysWithPrefix( h, prefix, results );
        return results;
    }

    queue< string > getKeysThatMatch( const string& pattern ) const {
        queue< string > results;
        getKeysThatMatch( root, "", pattern, results );
        return results;
    }

    string getLongestPrefixOf( const string& query ) const {
        int length = getLongestPrefixOf( root, query, 0, -1 );
        if ( length == -1 ) {
            return "";
        } else {
            return query.substr( 0, length );
        }
    }

    void put( string key, Value val ) {
        root = put( root, key, val, 0 );
    }

    void deleteKey( const string& key ) {
        root = deleteKey( root, key, 0 );
    }

    string toString() const {
        ostringstream oss;
        oss << "index : " << root->index << " ; char : '' ; val : ";
        if ( root->val ) {
            oss << *( root->val );
        } else {
            oss << "NULL";
        }
        oss << toString( root ) << endl;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const TrieST< Value >& st ) {
        out << "\nst:\n";
        out << st.toString() << endl;
        return out;
    }
};

int main( int argc, char ** argv ) {
    srand( time( NULL ) );
    TrieST< int > trieST;
    int N = 10;
    for ( int i = 0; i < N; i++ ) {
        string numStr = "";
        for ( int j = 0; j < 10; j++ ) {
            int digit = ( unsigned long ) rand() % 10;
            if ( trieST.contains( numStr + ( char ) ( '0' + digit ) ) ) {
                --j;
            } else {
                numStr += ( char ) ( '0' + digit );
            }
        }
        trieST.put( numStr, i );
    }

    cout << "DEBUG : List of Numbers : " << endl;
    queue< string > q = trieST.getKeys();
    while ( ! q.empty() ) {
        string s = q.front();
        cout << "(" << s.substr( 0, 3 ) << ") " << s.substr( 3, 3 ) << "-" << s.substr( 6 ) << endl;
        q.pop();
    }

    return 0;
}
