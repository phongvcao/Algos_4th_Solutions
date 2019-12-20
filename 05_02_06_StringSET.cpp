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

class StringSet {
public:
    virtual void add( string key ) = 0;
    virtual void deleteKey( const string& key ) = 0;
    virtual bool contains( const string& key ) const = 0;
    bool empty() const { return size() == 0; }
    virtual int size() const = 0;
    virtual string toString() const = 0;
};

class StringTrieSTSet : public StringSet {
private:

    static const int R;
    class Node {
    public:
        vector< Node * > next;
        unique_ptr< int > val = NULL;
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
        char c = key[ d ];
        return get( h->next[ c ], key, d + 1 );
    }

    Node * add( Node * h, string key, int val, int d ) {
        if ( ! h ) {
            h = newNode();
        }

        if ( d == key.size() ) {
            if ( ! h->val ) ++N;
            h->val = make_unique< int >( val );
            return h;
        }

        char c = key[ d ];
        h->next[ c ] = add( h->next[ c ], key, val, d + 1 );
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
                oss << "index : " << h->next[ c ]->index << " ; char : "
                    << ( char ) c << " ; val : ";
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

    StringTrieSTSet() {
        // not implemented
    }

    virtual ~StringTrieSTSet() {
        // not implemented
    }

    virtual int size() const override {
        return N;
    }

    virtual bool contains( const string& key ) const override {
        Node * rv = get( root, key, 0 );
        if ( ! rv || ! rv->val ) {
            return false;
        } else {
            return true;
        }
    }

    virtual void add( string key ) override {
        root = add( root, key, 1, 0 );
    }

    virtual void deleteKey( const string& key ) override {
        root = deleteKey( root, key, 0 );
    }

    virtual string toString() const override {
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

    friend ostream& operator <<( ostream& out, const StringTrieSTSet& st ) {
        out << "\nst:\n";
        out << st.toString() << endl;
        return out;
    }

};

const int StringTrieSTSet::R = 256;

class StringTSTSet : public StringSet {
private:

    class Node {
    public:
        char c;
        Node * left = NULL;
        Node * mid = NULL;
        Node * right = NULL;
        unique_ptr< int > val = NULL;
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

    Node * add( Node * h, string key, int val, int d ) {
        char c = key[ d ];
        if ( ! h ) {
            h = newNode( c );
        }

        if ( c < h->c ) {
            h->left = add( h->left, key, val, d );
        } else if ( c > h->c ) {
            h->right = add( h->right, key, val, d );
        } else if ( d < key.size() - 1 ) {
            h->mid = add( h->mid, key, val, d + 1 );
        } else {
            h->val = make_unique< int >( val );
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

    StringTSTSet() {
        // not implemented
    }

    virtual ~StringTSTSet() {
        // not implemented
    }

    virtual int size() const override {
        return N;
    }

    virtual bool contains( const string& key ) const override {
        Node * rv = get( root, key, 0 );
        if ( ! rv || ! rv->val ) {
            return false;
        } else {
            return true;
        }
    }

    virtual void add( string key ) override {
        if ( ! contains( key ) ) ++N;
        root = add( root, key, 1, 0 );
    }

    virtual void deleteKey( const string& key ) override {
        if ( contains( key ) ) --N;
        root = deleteKey( root, key, 0 );
    }

    virtual string toString() const override {
        ostringstream oss;
        oss << toString( root ) << endl;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const StringTSTSet& st ) {
        out << "\nst:\n";
        out << st.toString() << endl;
        return out;
    }
};

void testStringTrieSTSet() {

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

    StringTrieSTSet trieST;
    for (int i = 0; i < strVec.size(); i++) {
        trieST.add( strVec[ i ] );
    }

    cout << "DEBUG: trieST : \n" << trieST << endl;
    cout << "DEBUG: trieST.size() : " << trieST.size() << endl;
    
    cout << "DEBUG: trieST.contains( shells ) : " << trieST.contains( "shells" ) << endl;
    cout << "DEBUG: trieST.contains( phong ) : " << trieST.contains( "phong" ) << endl;
    
    trieST.deleteKey( "sea" );
    cout << "DEBUG: trieST.deleteKey( sea ) : " << trieST << endl;

    trieST.deleteKey( "she" );
    cout << "DEBUG: trieST.deleteKey( she ) : " << trieST << endl;
    
    trieST.deleteKey( "sells" );
    cout << "DEBUG: trieST.deleteKey( sells ) : " << trieST << endl;
    
    cout << "DEBUG: trieST.size() : " << trieST.size() << endl;
}

void testStringTSTSet() {
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
    
    StringTSTSet tst;
    for (int i = 0; i < strVec.size(); i++) {
        tst.add( strVec[ i ] );
    }

    cout << "DEBUG: tst : \n" << tst << endl;
    cout << "DEBUG: tst.size() : " << tst.size() << endl;
    
    cout << "DEBUG: tst.contains( shells ) : " << tst.contains( "shells" ) << endl;
    cout << "DEBUG: tst.contains( phong ) : " << tst.contains( "phong" ) << endl;
    
    tst.deleteKey( "sea" );
    cout << "DEBUG: tst.deleteKey( sea ) : " << tst << endl;

    tst.deleteKey( "she" );
    cout << "DEBUG: tst.deleteKey( she ) : " << tst << endl;
    
    tst.deleteKey( "sells" );
    cout << "DEBUG: tst.deleteKey( sells ) : " << tst << endl;
    
    cout << "DEBUG: tst.size() : " << tst.size() << endl;
}

int main( int argc, char ** argv ) {

    testStringTrieSTSet();
    testStringTSTSet();

    return 0;
}
