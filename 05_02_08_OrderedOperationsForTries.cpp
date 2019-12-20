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

    static const int R = 256;

    class Node {
    public:
        vector< Node * > next;
        unique_ptr< Value > val = NULL;
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

    void freeNode( Node * h ) {
        if ( h->index < nodes.size() - 1 ) {
            nodes[ h->index ].swap( nodes.back() );
            nodes[ h->index ]->index = h->index;
        }
        nodes.pop_back();
    }

    Node * newNode() {
        nodes.push_back( make_unique< Node >() );
        nodes.back()->index = nodes.size() - 1;
        return nodes.back().get();
    }

    Node * get( Node * h, const string& key, int d ) const {
        if ( ! h ) return NULL;
        if ( d == key.size() ) return h;
        char c = key[ d ];
        return get( h->next[ c ], key, d + 1 );
    }

    void getKeysWithPrefix( Node * h, string prefix, queue< string >& results ) const {
        if ( ! h ) return;
        if ( h->val ) results.push( prefix );
        for ( int c = 0; c < R; c++ ) {
            prefix += ( char ) c;
            getKeysWithPrefix( h->next[ c ], prefix, results );
            prefix.pop_back();
        }
    }

    void getKeysThatMatch( Node * h, string prefix, const string& pattern, queue< string >& results ) const {
        if ( ! h ) return;
        int d = prefix.size();
        if ( h->val && d == pattern.size() ) results.push( prefix );
        if ( d == pattern.size() ) return;
        char c = pattern[ d ];
        if ( c == '.' ) {
            for ( int ch = 0; ch < R; ch++ ) {
                prefix += ( char ) ch;
                getKeysThatMatch( h->next[ ch ], prefix, pattern, results );
                prefix.pop_back();
            }
        } else {
            prefix += ( char ) c;
            getKeysThatMatch( h->next[ c ], prefix, pattern, results );
            prefix.pop_back();
        }
    }

    int getLongestPrefixOf( Node * h, const string& query, int d, int length ) const {
        if ( ! h ) return length;
        if ( h->val ) length = d;
        if ( d == query.size() ) return length;

        char c = query[ d ];
        return getLongestPrefixOf( h->next[ c ], query, d + 1, length );
    }

    string floor( Node * h, string prefix, int d, const string& key, bool mustBeEqual ) const {
        if ( ! h ) return "";

        if ( ! mustBeEqual && h->val ) {
            return prefix;
        }

        unsigned int c = key[ d ];
        if ( ! mustBeEqual ) {
            c = R - 1;
        }
        for ( int ch = c; ch >= 0; ch-- ) {
            if ( h->next[ ch ] ) {
                if ( ch == c ) {
                    mustBeEqual = true;
                } else {
                    mustBeEqual = false;
                }
                string prefixStr = floor( h->next[ ch ], prefix + ( char ) ch, d + 1, key, mustBeEqual );
                if ( ! prefixStr.empty() ) return prefixStr;
            }
        }
        if ( h->val ) return prefix;
        return "";
    }

    string ceiling( Node * h, string prefix, int d, const string& key, bool mustBeEqual ) const {
        if ( ! h ) return "";

        if ( ! mustBeEqual && h->val ) {
            return prefix;
        }
        
        unsigned int c = key[ d ];
        if ( ! mustBeEqual ) {
            c = 0;
        }
        for ( int ch = c; ch < R; ch++ ) {
            if ( h->next[ ch ] ) {
                if ( ch == c ) {
                    mustBeEqual = true;
                } else {
                    mustBeEqual = false;
                }
                string prefixStr = ceiling( h->next[ ch ], prefix + ( char ) ch, d + 1, key, mustBeEqual );
                // if ( ! prefixStr.empty() && ( d >= key.size() || ! mustBeEqual ) ) {
                if ( ! prefixStr.empty() ) {
                    // cout << "DEBUG: RETURN ( 0 ) prefixStr : " << prefixStr << endl;
                    return prefixStr;
                }
            }
        }
        if ( h->val && d >= key.size() ) {
            // cout << "DEBUG: RETURN ( 1 ) prefix : " << prefix << endl;
            return prefix;
        }
        return "";
    }

    int rank( Node * h, string prefix, int d, const string& key, bool mustBeEqual, bool previousCharEqual ) const {
        if ( ! h ) return 0;
        int rv = 0;

        unsigned int c = key[ d ];
        if ( ! mustBeEqual ) {
            c = R - 1;
        }

        for ( int ch = c; ch >= 0; ch-- ) {
            if ( h->next[ ch ] ) {
                if ( ch == c ) {
                    mustBeEqual = true;
                    if ( d == 0 ) {
                        previousCharEqual = true;
                    }
                } else {
                    mustBeEqual = false;
                    previousCharEqual = false;
                }

                rv += rank( h->next[ ch ], prefix + ( char ) ch, d + 1, key, mustBeEqual, previousCharEqual );
            }
        }

        if ( h->val && previousCharEqual && d == key.size() ) {
            return rv;
        }

        if ( h->val ) {
            ++rv;
        }
        return rv;
    }

    string select( Node * h, string prefix, int d, int& count, int k ) const {
        if ( ! h ) return "";
        if ( k + 1 == count ) return prefix;
        for ( int ch = 0; ch < R; ch++ ) {
            if ( h->next[ ch ] ) {
                if ( h->next[ ch ]->val ) ++count;
                string prefixStr = select( h->next[ ch ], prefix + ( char ) ch, d + 1, count, k );
                if ( ! prefixStr.empty() ) {
                    if ( k + 1 == count ) return prefixStr;
                }
            }
        }

        if ( h->val ) return prefix;
        else return "";
        return prefix;
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
        h->next[ c ] = put( h->next[ c ], key, val, d + 1 );
        return h;
    }

    Node * deleteKey( Node * h, const string& key, int d ) {
        if ( ! h ) return NULL;

        if ( d == key.size() ) {
            if ( h->val ) --N;
            h->val = NULL;
        } else {
            char c = key[ d ];
            h->next[ c ] = deleteKey( h->next[ c ], key, d + 1 );
        }

        if ( h->val ) return h;
        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) return h;
        }
        freeNode( h );
        return NULL;
    }

    string toString( Node * h ) const {
        if ( ! h ) return "";
        ostringstream oss;
        oss << " ; children : ";
        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) {
                oss << ( char ) c << ", ";
            }
        }
        oss << endl;

        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] ) {
                oss << "index : " << h->index << " ; char : " << ( char ) c
                    << " ; val : ";
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
        if ( ! h ) return results;
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

    string floor( const string& key ) const {
        return floor( root, "", 0, key, true );
    }

    string ceiling( const string& key ) const {
        return ceiling( root, "", 0, key, true );
    }

    int rank( const string& key ) const {
        return rank( root, "", 0, key, true, false );
    }

    string select( int k ) const {
        int count = 0;
        return select( root, "", 0, count, k );
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

template< typename Value >
class TST {
private:

    class Node {
    public:
        char c;
        Node * left = NULL;
        Node * mid = NULL;
        Node * right = NULL;
        unique_ptr< Value > val = NULL;
        int index = -1;

        Node( char c )
            : c( c )
        {
            // not implemented
        }

        virtual ~Node() {
            // not implemented
        }
    };

    void freeNode( Node * h ) {
        if ( h->index < nodes.size() - 1 ) {
            nodes[ h->index ].swap( nodes.back() );
            nodes[ h->index ]->index = h->index;
        }
        nodes.pop_back();
    }

    Node * newNode( char c ) {
        nodes.push_back( make_unique< Node >( c ) );
        nodes.back()->index = nodes.size() - 1;
        return nodes.back().get();
    }

    Node * get( Node * h, const string& key, int d ) const {
        if ( ! h ) return NULL;
        char c = key[ d ];

        if ( c < h->c ) {
            return get( h->left, key, d );
        } else if ( c > h->c ) {
            return get( h->right, key, d );
        } else if ( d < key.size() - 1 ) {
            return get( h->mid, key, d + 1 );
        } else {
            return h;
        }
    }

    void getKeysWithPrefix( Node * h, string prefix, queue< string >& results ) const {
        if ( ! h ) return;

        getKeysWithPrefix( h->left, prefix, results );

        if ( h->val ) results.push( prefix + h->c );
        getKeysWithPrefix( h->mid, prefix + h->c, results );

        getKeysWithPrefix( h->right, prefix, results );
    }

    void getKeysThatMatch( Node * h, string prefix, int d, const string& pattern, queue< string >& results ) const {
        if ( ! h ) return;

        char c = pattern[ d ];

        if ( c == '.' || c < h->c ) {
            getKeysThatMatch( h->left, prefix, d, pattern, results );
        }

        if ( c == '.' || c == h->c ) {
            if ( h->val && d == pattern.size() - 1 ) results.push( prefix + h->c );
            if ( d < pattern.size() - 1 ) {
                getKeysThatMatch( h->mid, prefix + h->c, d + 1, pattern, results );
            }
        }

        if ( c == '.' || c > h->c ) {
            getKeysThatMatch( h->right, prefix, d, pattern, results );
        }
    }

    string floor( Node * h, string prefix, int d, const string& key, bool mustBeEqual ) const {
        if ( ! h ) {
            return "";
        }

        char c = key[ d ];

        string prefixStr = "";
        if ( c < h->c && h->left ) {
            if ( h->left ) {
                prefixStr = floor( h->left, prefix, d, key, mustBeEqual );
            } else {
                mustBeEqual = false;
            }
        }

        if ( c > h->c ) {
            if ( h->right ) {
                prefixStr = floor( h->right, prefix, d, key, mustBeEqual );
            } else {
                mustBeEqual = false;
            }
        }

        if ( ! mustBeEqual ) {
            c = h->c;
        }

        if ( c == h->c ) {
            prefixStr = floor( h->mid, prefix + ( char ) c, d + 1, key, mustBeEqual );
        }

        if ( ! prefixStr.empty() ) {
            return prefixStr;
        }
        if ( h->val && c == h->c ) {
            return prefix + ( char ) h->c;
        }
        return "";
    }

    string ceiling( Node * h, string prefix, int d, const string& key, bool mustBeEqual ) const {
        if ( ! h ) {
            return "";
        }

        char c = key[ d ];
        string prefixStr = "";
        if ( c < h->c ) {
            if ( h->left ) {
                prefixStr = ceiling( h->left, prefix, d, key, mustBeEqual );
                if ( prefixStr.empty() ) {
                    c = h->c;
                    mustBeEqual = false;
                }
            } else {
                mustBeEqual = false;
            }
        }

        if ( c > h->c ) {
            if ( h->right ) {
                prefixStr = ceiling( h->right, prefix, d, key, mustBeEqual );
            } else {
                if ( d == key.size() - 1 ) return "";
                mustBeEqual = false;
            }
        }

        if ( ! mustBeEqual && prefixStr.empty() ) {
            c = h->c;
        }

        if ( c == h->c ) {
            prefixStr = ceiling( h->mid, prefix + ( char ) h->c, d + 1, key, mustBeEqual );
            if ( prefixStr.empty() && mustBeEqual && h->right ) {
                prefixStr = ceiling( h->right, prefix, d, key, false );
            }
        }

        if ( ! prefixStr.empty() ) {
            return prefixStr;
        }
        if ( h->val && c == h->c ) {
            if ( mustBeEqual && d != key.size() - 1 ) return "";
            return prefix + ( char ) h->c;
        }
        return "";
    }

    Node * put( Node * h, string key, Value val, int d ) {
        char c = key[ d ];
        if ( ! h ) {
            h = newNode( c );
        }

        if ( c < h->c ) {
            h->left = put( h->left, key, val, d );
        } else if ( c > h->c ) {
            h->right = put( h->right, key, val, d );
        } else if ( d < key.size() - 1 ) {
            h->mid = put( h->mid, key, val, d + 1 );
        } else {
            h->val = make_unique< Value >( val );
        }
        return h;
    }

    Node * deleteKey( Node * h, const string& key, int d ) {
        if ( ! h ) return NULL;
        
        char c = key[ d ];
        if ( c < h->c ) {
            h->left = deleteKey( h->left, key, d );
        } else if ( c > h->c ) {
            h->right = deleteKey( h->right, key, d );
        } else if ( d < key.size() - 1 ) {
            h->mid = deleteKey( h->mid, key, d + 1 );
        } else {
            h->val = NULL;
        }

        if ( ! h->left && ! h->mid && ! h->right ) {
            freeNode( h );
            return NULL;
        }
        return h;
    }

    string toString( Node * h ) const {
        if ( ! h ) return "";
        ostringstream oss;
        oss << toString( h->left );
        oss << toString( h->right );

        oss << "index : " << h->index << " ; char : " << h->c << " ; val : ";
        if ( h->val ) {
            oss << *( h->val );
        } else {
            oss << "NULL";
        }

        oss << " ; left : ";
        if ( h->left ) {
            oss << h->left->c;
        } else {
            oss << "NULL";
        }

        oss << " ; right : ";
        if ( h->right ) {
            oss << h->right->c;
        } else {
            oss << "NULL";
        }

        oss << " ; children : ";
        if ( h->mid ) {
            oss << h->mid->c;
        } else {
            oss << "NULL";
        }
        oss << endl;

        oss << toString( h->mid );
        return oss.str();
    }

    vector< unique_ptr< Node > > nodes;
    int N = 0;
    Node * root = NULL;

public:

    TST() {
        // not implemented
    }

    virtual ~TST() {
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
        queue< string > results;
        getKeysWithPrefix( root, "", results );
        return results;
    }

    queue< string > getKeysWithPrefix( const string& prefix ) const {
        queue< string > results;
        Node * h = get( root, prefix, 0 );
        if ( ! h ) return results;
        if ( h->val ) results.push( prefix );
        getKeysWithPrefix( h->mid, prefix, results );
        return results;
    }

    queue< string > getKeysThatMatch( const string& pattern ) const {
        queue< string > results;
        getKeysThatMatch( root, "", 0, pattern, results );
        return results;
    }

    string getLongestPrefixOf( const string& query ) const {
        int d = 0;
        int length = 0;
        Node * h = root;

        while ( h && d < query.size() ) {
            char c = query[ d ];
            if ( c < h->c ) {
                h = h->left;
            } else if ( c > h->c ) {
                h = h->right;
            } else {
                ++d;
                if ( h->val ) length = d;
                h = h->mid;
            }
        }
        return query.substr( 0, length );
    }

    string floor( const string& key ) const {
        return floor( root, "", 0, key, true );
    }

    string ceiling( const string& key ) const {
        return ceiling( root, "", 0, key, true );
    }

    void put( string key, Value val ) {
        if ( ! contains( key ) ) ++N;
        root = put( root, key, val, 0 );
    }

    void deleteKey( const string& key ) {
        if ( contains( key ) ) --N;
        root = deleteKey( root, key, 0 );
    }

    string toString() const {
        ostringstream oss;
        oss << toString( root ) << endl;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const TST< Value >& tst ) {
        out << "\ntst:\n";
        out << tst.toString() << endl;
        return out;
    }

};

void testTrieST() {
    vector< string > strVec = {
        "she",
        "sells",
        "sea",
        "shells",
        "by",
        "the",
        "sea",
        "shore",
    };
    
    TrieST< int > trieST;

    for ( int i = 0; i < strVec.size(); ++i ) {
        trieST.put( strVec[ i ], i );
    }
    
    cout << "DEBUG: trieST : \n" << trieST << endl;
    cout << "DEBUG: trieST.size() : " << trieST.size() << endl;

    try {
        cout << "DEBUG: trieST.get( sea ) : " << trieST.get( "sea" ) << endl;
    } catch ( const runtime_error& e ) {
        cout << e.what() << endl;
    }

    try {
        cout << "DEBUG: trieST.get( seashells ) : " << trieST.get( "seashells" ) << endl;
    } catch ( const runtime_error& e ) {
        cout << e.what() << endl;
    }
    cout << "DEBUG: trieST.contains( shells ) : " << trieST.contains( "shells" ) << endl;
    cout << "DEBUG: trieST.contains( phong ) : " << trieST.contains( "phong" ) << endl;

    cout << "DEBUG: trieST.getKeysWithPrefix( se ) : ";
    queue< string > q = trieST.getKeysWithPrefix( "se" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: trieST.getKeysThatMatch( t.e ) : ";
    q = trieST.getKeysThatMatch( "t.e" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: trieST.getLongestPrefixOf( shellsort ) : " << trieST.getLongestPrefixOf( "shellsort" ) << endl;
    cout << "DEBUG: trieST.getKeys() : ";
    q = trieST.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;
    cout << "DEBUG: trieST.floor( a ) : " << trieST.floor( "a" ) << endl;
    cout << "DEBUG: trieST.floor( bt ) : " << trieST.floor( "bt" ) << endl;
    cout << "DEBUG: trieST.floor( r ) : " << trieST.floor( "r" ) << endl;
    cout << "DEBUG: trieST.floor( shells ) : " << trieST.floor( "shells" ) << endl;
    cout << "DEBUG: trieST.floor( shellsort ) : " << trieST.floor( "shellsort" ) << endl;
    cout << "DEBUG: trieST.floor( shel ) : " << trieST.floor( "shel" ) << endl;
    cout << "DEBUG: trieST.floor( y ) : " << trieST.floor( "y" ) << endl;
    
    cout << "DEBUG: trieST.ceiling( a ) : " << trieST.ceiling( "a" ) << endl;
    cout << "DEBUG: trieST.ceiling( bt ) : " << trieST.ceiling( "bt" ) << endl;
    cout << "DEBUG: trieST.ceiling( r ) : " << trieST.ceiling( "r" ) << endl;
    cout << "DEBUG: trieST.ceiling( shells ) : " << trieST.ceiling( "shells" ) << endl;
    cout << "DEBUG: trieST.ceiling( shellsort ) : " << trieST.ceiling( "shellsort" ) << endl;
    cout << "DEBUG: trieST.ceiling( sell ) : " << trieST.ceiling( "sell" ) << endl;
    cout << "DEBUG: trieST.ceiling( sells ) : " << trieST.ceiling( "sells" ) << endl;
    cout << "DEBUG: trieST.ceiling( se ) : " << trieST.ceiling( "se" ) << endl;
    cout << "DEBUG: trieST.ceiling( shel ) : " << trieST.ceiling( "shel" ) << endl;
    cout << "DEBUG: trieST.ceiling( y ) : " << trieST.ceiling( "y" ) << endl;
    
    cout << "DEBUG: trieST.rank( shells ) : " << trieST.rank( "shells" ) << endl;
    cout << "DEBUG: trieST.rank( shellsort ) : " << trieST.rank( "shellsort" ) << endl;
    cout << "DEBUG: trieST.rank( shel ) : " << trieST.rank( "shel" ) << endl;
    cout << "DEBUG: trieST.rank( y ) : " << trieST.rank( "y" ) << endl;
    
    cout << "DEBUG: trieST.select( 0 ) : " << trieST.select( 0 ) << endl;
    cout << "DEBUG: trieST.select( 1 ) : " << trieST.select( 1 ) << endl;
    cout << "DEBUG: trieST.select( 2 ) : " << trieST.select( 2 ) << endl;
    cout << "DEBUG: trieST.select( 3 ) : " << trieST.select( 3 ) << endl;
    cout << "DEBUG: trieST.select( 4 ) : " << trieST.select( 4 ) << endl;
    cout << "DEBUG: trieST.select( 5 ) : " << trieST.select( 5 ) << endl;
    cout << "DEBUG: trieST.select( 6 ) : " << trieST.select( 6 ) << endl;
    cout << "DEBUG: trieST.select( 7 ) : " << trieST.select( 7 ) << endl;

    cout << "=============================================================" << endl;

    trieST.deleteKey( "sea" );
    cout << "DEBUG: trieST.deleteKey( sea ) : " << trieST << endl;

    trieST.deleteKey( "she" );
    cout << "DEBUG: trieST.deleteKey( she ) : " << trieST << endl;

    trieST.deleteKey( "sells" );
    cout << "DEBUG: trieST.deleteKey( sells ) : " << trieST << endl;

    cout << "DEBUG: trieST.size() : " << trieST.size() << endl;

    try {
        cout << "DEBUG: trieST.get( sea ) : " << trieST.get( "sea" ) << endl;
        cout << "DEBUG: trieST.get( seashells ) : " << trieST.get( "seashells" ) << endl;
    } catch ( const runtime_error& e ) {
        cout << e.what() << endl;
    }
    cout << "DEBUG: trieST.contains( sea ) : " << trieST.contains( "sea" ) << endl;
    cout << "DEBUG: trieST.contains( she ) : " << trieST.contains( "she" ) << endl;
    cout << "DEBUG: trieST.contains( sells ) : " << trieST.contains( "sells" ) << endl;
    cout << "DEBUG: trieST.contains( shells ) : " << trieST.contains( "shells" ) << endl;
    cout << "DEBUG: trieST.contains( phong ) : " << trieST.contains( "phong" ) << endl;

    cout << "DEBUG: trieST.getKeysWithPrefix( se ) : ";
    q = trieST.getKeysWithPrefix( "se" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: trieST.getKeysThatMatch( t.e ) : ";
    q = trieST.getKeysThatMatch( "t.e" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;
    cout << "DEBUG: trieST.getLongestPrefixOf( shellsort ) : " << trieST.getLongestPrefixOf( "shellsort" ) << endl;
    cout << "DEBUG: trieST.getKeys() : ";
    q = trieST.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;
}

void testTST() {

    vector< string > strVec = {
        "she",
        "sells",
        "sea",
        "shells",
        "by",
        "the",
        "sea",
        "shore",
    };

    TST< int > tst;

    for ( int i = 0; i < strVec.size(); ++i ) {
        tst.put( strVec[ i ], i );
    }

    cout << "DEBUG: tst : \n" << tst << endl;
    cout << "DEBUG: tst.size() : " << tst.size() << endl;

    try {
        cout << "DEBUG: tst.get( sea ) : " << tst.get( "sea" ) << endl;
        cout << "DEBUG: tst.get( seashells ) : " << tst.get( "seashells" ) << endl;
    } catch ( const runtime_error& e ) {
        cout << e.what() << endl;
    }
    cout << "DEBUG: tst.contains( shells ) : " << tst.contains( "shells" ) << endl;
    cout << "DEBUG: tst.contains( phong ) : " << tst.contains( "phong" ) << endl;

    cout << "DEBUG: tst.getKeys() : ";
    queue< string > q = tst.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: tst.getKeysWithPrefix( se ) : ";
    q = tst.getKeysWithPrefix( "se" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: tst.getKeysThatMatch( t.e ) : ";
    q = tst.getKeysThatMatch( "t.e" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: tst.floor( a ) : " << tst.floor( "a" ) << endl;
    cout << "DEBUG: tst.floor( bt ) : " << tst.floor( "bt" ) << endl;
    cout << "DEBUG: tst.floor( r ) : " << tst.floor( "r" ) << endl;
    cout << "DEBUG: tst.floor( shells ) : " << tst.floor( "shells" ) << endl;
    cout << "DEBUG: tst.floor( shellsort ) : " << tst.floor( "shellsort" ) << endl;
    cout << "DEBUG: tst.floor( shel ) : " << tst.floor( "shel" ) << endl;
    cout << "DEBUG: tst.floor( y ) : " << tst.floor( "y" ) << endl;
    
    cout << "DEBUG: tst.ceiling( a ) : " << tst.ceiling( "a" ) << endl;
    cout << "DEBUG: tst.ceiling( bt ) : " << tst.ceiling( "bt" ) << endl;
    cout << "DEBUG: tst.ceiling( r ) : " << tst.ceiling( "r" ) << endl;
    cout << "DEBUG: tst.ceiling( shells ) : " << tst.ceiling( "shells" ) << endl;
    cout << "DEBUG: tst.ceiling( shellsort ) : " << tst.ceiling( "shellsort" ) << endl;
    cout << "DEBUG: tst.ceiling( sell ) : " << tst.ceiling( "sell" ) << endl;
    cout << "DEBUG: tst.ceiling( sells ) : " << tst.ceiling( "sells" ) << endl;
    cout << "DEBUG: tst.ceiling( se ) : " << tst.ceiling( "se" ) << endl;
    cout << "DEBUG: tst.ceiling( shel ) : " << tst.ceiling( "shel" ) << endl;
    cout << "DEBUG: tst.ceiling( y ) : " << tst.ceiling( "y" ) << endl;

    // cout << "DEBUG: tst.rank( shells ) : " << tst.rank( "shells" ) << endl;
    // cout << "DEBUG: tst.rank( shellsort ) : " << tst.rank( "shellsort" ) << endl;
    // cout << "DEBUG: tst.rank( shel ) : " << tst.rank( "shel" ) << endl;
    // cout << "DEBUG: tst.rank( y ) : " << tst.rank( "y" ) << endl;

    // cout << "DEBUG: tst.select( 0 ) : " << tst.select( 0 ) << endl;
    // cout << "DEBUG: tst.select( 1 ) : " << tst.select( 1 ) << endl;
    // cout << "DEBUG: tst.select( 2 ) : " << tst.select( 2 ) << endl;
    // cout << "DEBUG: tst.select( 3 ) : " << tst.select( 3 ) << endl;
    // cout << "DEBUG: tst.select( 4 ) : " << tst.select( 4 ) << endl;
    // cout << "DEBUG: tst.select( 5 ) : " << tst.select( 5 ) << endl;
    // cout << "DEBUG: tst.select( 6 ) : " << tst.select( 6 ) << endl;
    // cout << "DEBUG: tst.select( 7 ) : " << tst.select( 7 ) << endl;

    cout << "DEBUG: tst.getLongestPrefixOf( shellsort ) : " << tst.getLongestPrefixOf( "shellsort" ) << endl;

    cout << "=============================================================" << endl;

    tst.deleteKey( "sea" );
    cout << "DEBUG: tst.deleteKey( sea ) : " << tst << endl;

    tst.deleteKey( "she" );
    cout << "DEBUG: tst.deleteKey( she ) : " << tst << endl;

    tst.deleteKey( "sells" );
    cout << "DEBUG: tst.deleteKey( sells ) : " << tst << endl;

    cout << "DEBUG: tst.size() : " << tst.size() << endl;

    try {
        cout << "DEBUG: tst.get( sea ) : " << tst.get( "sea" ) << endl;
        cout << "DEBUG: tst.get( seashells ) : " << tst.get( "seashells" ) << endl;
    } catch ( const runtime_error& e ) {
        cout << e.what() << endl;
    }
    cout << "DEBUG: tst.contains( sea ) : " << tst.contains( "sea" ) << endl;
    cout << "DEBUG: tst.contains( she ) : " << tst.contains( "she" ) << endl;
    cout << "DEBUG: tst.contains( sells ) : " << tst.contains( "sells" ) << endl;
    cout << "DEBUG: tst.contains( shells ) : " << tst.contains( "shells" ) << endl;
    cout << "DEBUG: tst.contains( phong ) : " << tst.contains( "phong" ) << endl;

    cout << "DEBUG: tst.getKeysWithPrefix( se ) : ";
    q = tst.getKeysWithPrefix( "se" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: tst.getKeysThatMatch( t.e ) : ";
    q = tst.getKeysThatMatch( "t.e" );
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;
    cout << "DEBUG: tst.getLongestPrefixOf( shellsort ) : " << tst.getLongestPrefixOf( "shellsort" ) << endl;
    cout << "DEBUG: tst.getKeys() : ";
    q = tst.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << ", ";
        q.pop();
    }
    cout << endl;

}

int main( int argc, char ** argv ) {

    testTrieST();
    testTST();

    return 0;
}
