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

    static const int R;
    class Node {
    public:
        unique_ptr< Value > val;
        vector< Node * > next;
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

    Node * getNode( const string& key ) const {
        int d = 0;
        Node * h = root;
        char c = key[ d ];

        while ( h && d < key.size() ) {
            h = h->next[ c ];
            ++d;
            c = key[ d ];
        }
        return h;
    }

    vector< unique_ptr< Node > > nodes;
    Node * root = NULL;
    int N = 0;

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
        Node * rv = getNode( key );
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
        Node * h = getNode( prefix );
        if ( ! h ) return results;
        // getKeysWithPrefix( h, prefix, results );
        queue< Node * > nodeQueue;
        queue< string > prefixQueue;
        nodeQueue.push( h );
        prefixQueue.push( prefix );

        while ( ! nodeQueue.empty() ) {
            Node * node = nodeQueue.front();
            nodeQueue.pop();
            string prefixStr = prefixQueue.front();
            prefixQueue.pop();

            for ( int c = 0; c < R; c++ ) {
                if ( node->next[ c ] ) {
                    nodeQueue.push( node->next[ c ] );
                    prefixQueue.push( prefixStr + ( char ) c );
                    if ( node->next[ c ]->val ) {
                        results.push( prefixStr + ( char ) c );
                    }
                }
            }
        }
        return results;
    }

    queue< string > getKeysThatMatch( const string& pattern ) const {
        queue< string > results;
        // getKeysThatMatch( root, "", pattern, results );
        Node * h = root;
        queue< Node * > nodeQueue;
        queue< string > prefixQueue;
        nodeQueue.push( h );
        prefixQueue.push( "" );

        while ( ! nodeQueue.empty() ) {
            Node * node = nodeQueue.front();
            nodeQueue.pop();
            string prefix = prefixQueue.front();
            prefixQueue.pop();

            int d = prefix.size();
            char c = pattern[ d ];

            if ( node->val && d == pattern.size() ) results.push( prefix );
            if ( d == pattern.size() ) continue;

            if ( c == '.' ) {
                for ( int ch = 0; ch < R; ch++ ) {
                    if ( node->next[ ch ] ) {
                        nodeQueue.push( node->next[ ch ] );
                        prefixQueue.push( prefix + ( char ) ch );
                    }
                }
            } else {
                if ( node->next[ c ] ) {
                    nodeQueue.push( node->next[ c ] );
                    prefixQueue.push( prefix + ( char ) c );
                }
            }
        }

        return results;
    }

    string getLongestPrefixOf( const string& query ) const {
        // int length = getLongestPrefixOf( root, query, 0, -1 );
        Node * h = root;
        int length = -1;
        int d = 0;

        while ( h ) {
            if ( h->val && d > length ) length = d;

            char c = query[ d ];
            h = h->next[ c ];
            ++d;
        }

        if ( length == -1 ) { 
            return "";
        } else {
            return query.substr( 0, length );
        }
    }

    void put( string key, Value val ) {
        // root = put( root, key, val, 0 );
        if ( ! root ) {
            root = newNode();
        }
        Node * h = root;
        int d = 0;
        
        while ( d < key.size() ) {
            char c = key[ d ];
            if ( ! h->next[ c ] ) {
                h->next[ c ] = newNode();
            }

            if ( d == key.size() - 1 ) {
                if ( ! h->next[ c ]->val ) ++N;
                h->next[ c ]->val = make_unique< Value >( val );
                break;
            }
            h = h->next[ c ];
            ++d;

        }
    }

    void deleteKey( const string& key ) {
        // root = deleteKey( root, key, 0 );
        Node * h = root;
        int d = 0;
        stack< Node * > nodeStack;

        while ( d < key.size() ) {
            char c = key[ d ];

            if ( h->next[ c ] ) {
                nodeStack.push( h->next[ c ] );
            } else {
                break;
            }
            h = h->next[ c ];
            ++d;
        }

        char prevChar;
        while ( ! nodeStack.empty() ) {
            Node * node = nodeStack.top();
            nodeStack.pop();

            if ( d == key.size() ) {
                if ( node->val ) --N;
                node->val = NULL;
            }

            --d;
            char c = key[ d ];
            bool isContinue = false;

            if ( node->val ) isContinue = true;
            for ( int c = 0; c < R; c++ ) {
                if ( node->next[ c ] ) {
                    isContinue = true;
                    break;
                }
            }

            if ( isContinue ) continue;

            freeNode( node );
            nodeStack.top()->next[ c ] = NULL;
        }
    }

    string toString() const {
        ostringstream oss;
        queue< Node * > nodeQueue;
        nodeQueue.push( root );
        Node * h = root;
        oss << "index : " << root->index << " ; char : '' ; val : ";
        if ( root->val ) {
            oss << *( root->val );
        } else {
            oss << "NULL";
        }
        oss << " ; children : ";
        for ( int c = 0; c < R; c++ ) {
            if ( h->next[ c ] )  {
                oss << ( char ) c << ", ";
            }
        }
        oss << endl;
        
        while ( ! nodeQueue.empty() ) {
            Node * h = nodeQueue.front();
            nodeQueue.pop();

            for ( int c = 0; c < R; c++ ) {
                if ( h->next[ c ] ) {
                    oss << "index : " << h->next[ c ]->index << " ; char : "
                        << ( char ) c << " ; val : ";
                    if ( h->next[ c ]->val ) {
                        oss << *( h->next[ c ]->val );
                    } else {
                        oss << "NULL";
                    }

                    oss << " ; children : ";
                    for ( int ch = 0; ch < R; ch++ ) {
                        if ( h->next[ c ]->next[ ch ] ) {
                            oss << ( char ) ch << ", ";
                        }
                    }
                    oss << endl;
                    nodeQueue.push( h->next[ c ] );
                }
            }
        }
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const TrieST< Value >& st ) {
        out << "\nst:\n";
        out << st.toString() << endl;
        return out;
    }

};

template< typename Value >
const int TrieST< Value >::R = 256;

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

    Node * newNode( char c ) {
        nodes.push_back( make_unique< Node >( c ) );
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

    Node * getNode( const string& key ) const {
        Node * h = root;
        if ( ! h ) return NULL;
        int d = 0;

        while ( d < key.size() ) {
            char c = key[ d ];

            if ( c < h->c && h->left ) {
                if ( h->left ) {
                    h = h->left;
                } else {
                    return NULL;
                }
            } else if ( c > h->c ) {
                if ( h->right ) {
                    h = h->right;
                } else {
                    return NULL;
                }
            } else if ( d < key.size() - 1 ) {
                if ( h->mid ) {
                    h = h->mid;
                    ++d;
                } else {
                    return NULL;
                }
            } else {
                if ( d == key.size() - 1 ) {
                    break;
                } else {
                    if ( h->mid ) {
                        h = h->mid;
                        ++d;
                    } else {
                        return NULL;
                    }
                }
            }
        }
        return h;
    }

    void getKeysWithPrefix( Node * h, string prefix, queue< string >& results ) const {
        if ( ! h ) return;
        stack< Node * > nodeStack;
        stack< string > prefixStack;
        nodeStack.push( h );
        prefixStack.push( prefix );

        while ( ! nodeStack.empty() ) {
            Node * node = nodeStack.top();
            nodeStack.pop();
            string prefixStr = prefixStack.top();
            prefixStack.pop();

            if ( node->left ) {
                nodeStack.push( node->left );
                prefixStack.push( prefixStr );
            }

            if ( node->val ) results.push( prefixStr + node->c );

            if ( node->mid ) {
                nodeStack.push( node->mid );
                prefixStack.push( prefixStr + node->c );
            }

            if ( node->right ) {
                nodeStack.push( node->right );
                prefixStack.push( prefixStr );
            }
        }
    }

    vector< unique_ptr< Node > > nodes;
    Node * root = NULL;
    int N = 0;

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

    bool contains( const string& key ) const {
        try {
            Value val = get( key );
        } catch ( const runtime_error& e ) {
            return false;
        }
        return true;
    }

    Value get( const string& key ) const {
        Node * rv = getNode( key );
        if ( ! rv || ! rv->val ) {
            throw runtime_error( "Key not exist : " + key );
        } else {
            return *( rv->val );
        }
    }

    queue< string > getKeys() const {
        queue< string > results;
        getKeysWithPrefix( root, "", results );
        return results;
    }

    queue< string > getKeysWithPrefix( const string& prefix ) const {
        queue< string > results;
        Node * h = getNode( prefix );
        if ( ! h ) return results;
        if ( h->val ) results.push( prefix );
        getKeysWithPrefix( h->mid, prefix, results );
        return results;
    }

    queue< string > getKeysThatMatch( const string& pattern ) const {
        queue< string > results;
        // getKeysThatMatch( root, "", 0, pattern, results );
        stack< Node * > nodeStack;
        stack< string > prefixStack;
        nodeStack.push( root );
        prefixStack.push( "" );

        while ( ! nodeStack.empty() ) {
            Node * h = nodeStack.top();
            nodeStack.pop();
            string prefixStr = prefixStack.top();
            prefixStack.pop();

            int d = prefixStr.size();
            char c = pattern[ d ];

            if ( c == '.' || c < h->c ) {
                if ( h->left ) {
                    nodeStack.push( h->left );
                    prefixStack.push( prefixStr );
                }
            }

            if ( c == '.' || c == h->c ) {
                if ( h->val && d == pattern.size() - 1 ) results.push( prefixStr + h->c );
                if ( d < pattern.size() - 1 ) {
                    if ( h->mid ) {
                        nodeStack.push( h->mid );
                        prefixStack.push( prefixStr + h->c );
                    }
                }
            }

            if ( c == '.' || c > h->c ) {
                if ( h->right ) {
                    nodeStack.push( h->right );
                    prefixStack.push( prefixStr );
                }
            }
        }
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

    void put( string key, Value val ) {
        if ( ! contains( key ) ) {
            cout << "DEBUG: KEY NOT EXIST : " << key << endl;
            ++N;
        }
        // root = put( root, key, val, 0 );
        int d = 0;
        char c = key[ d ];

        if ( ! root ) {
            root = newNode( c );
        }

        Node * h = root;

        while ( h ) {
            c = key[ d ];

            if ( c < h->c ) {
                if ( h->left ) {
                    h = h->left;
                } else {
                    h->left = newNode( c );
                    // ++d;
                }
            } else if ( c > h->c ) {
                if ( h->right ) {
                    h = h->right;
                } else {
                    h->right = newNode( c );
                    // ++d;
                }
            } else if ( c == h->c ) {
                if ( ! h->mid ) {
                    if ( d < key.size() - 1 ) {
                        h->mid = newNode( key[ d + 1 ] );
                    } else {
                        h->val = make_unique< Value >( val );
                        break;
                    }
                }
                h = h->mid;
                ++d;
            }
        }
    }

    void deleteKey( const string& key ) {
        if ( contains( key ) ) --N;
        
        stack< Node * > nodeStack;
        int d = 0;
        char c = key[ d ];

        if ( ! root ) {
            return;
        }

        Node * h = root;

        while ( h && d < key.size() ) {
            c = key[ d ];

            if ( c < h->c ) {
                if ( h->left ) {
                    h = h->left;
                }
            } else if ( c > h->c ) {
                if ( h->right ) {
                    h = h->right;
                }
            } else if ( c == h->c ) {
                nodeStack.push( h );
                h = h->mid;
                ++d;
            }
        }

        while ( ! nodeStack.empty() ) {
            Node * node = nodeStack.top();
            nodeStack.pop();

            node->val = NULL;
        }
    }

    string toString() const {
        ostringstream oss;
        queue< Node * > nodeQueue;
        cout << "DEBUG: nodes.size() : " << nodes.size() << endl;
        nodeQueue.push( root );

        while ( ! nodeQueue.empty() ) {
            Node * h = nodeQueue.front();
            nodeQueue.pop();

            if ( h->left ) {
                nodeQueue.push( h->left );
            }

            if ( h->right ) {
                nodeQueue.push( h->right );
            }

            if ( h->mid ) {
                nodeQueue.push( h->mid );
            }

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
            }
            oss << endl;
        }

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
