//
// Created by Phong Cao on 2019-02-07.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::sqrt;
using std::pow;
using std::rand;
using std::srand;
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::vector;
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::deque;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

// Implement LinearProbingHashST to use as Concordance
// The Key is string, the Value is int
class LinearProbingHashST {
private:

    int M = 17;
    int N = 0;
    vector< const string* > keys;
    vector< int > values;

    int hash( const string& key ) {
        return std::hash< string >{}( key ) % M;
    }

    void resize( int cap ) {
        // to be implemented
    }

public:

    LinearProbingHashST( int M )
        : M( M )
    {
        keys.resize( M );
        values.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
            values[ i ] = 0;
        }
    }

    LinearProbingHashST()
        : LinearProbingHashST( 17 )
    {
        // not implemented
    }

    virtual ~LinearProbingHashST() {
        // not implemented
    }

    void put( const string& key, const int value ) {
        if ( N > M / 2 ) resize( 2 * M );
        int i = hash( key );
        while ( keys[ i ] != NULL ) {
            i = ( i + 1 ) % M;
        }
        keys[ i ] = &key;
        values[ i ] = value;
        ++N;
    }

    void deleteKey( const string& key ) {
        if ( ! contains( key ) ) return;

        while ( contains( key ) ) {
            int i = hash( key );
            while ( *( keys[ i ] ) != key ) {
                i = ( i + 1 ) % M;
            }
            keys[ i ] = NULL;
            i = ( i + 1 ) % M;
            while ( keys[ i ] != NULL ) {
                const string* keyToRedo = keys[ i ];
                const int valueToRedo = values[ i ];
                --N;
                put( *keyToRedo, valueToRedo );
                i = ( i + 1 ) % M;
            }
            --N;
        }
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    const int* get( const string& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( key == *( keys[ i ] ) ) {
                return &( values[ i ] );
            }
        }
        return NULL;
    }

    const vector< int > getAll( const string& key ) {
        vector< int > rv;
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( key == *( keys[ i ] ) ) {
                rv.push_back( values[ i ] );
            }
        }
        return rv;
    }

    bool contains( const string& key ) {
        return get( key ) != NULL;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                rv += " | " + *( keys[ i ] ) + " : " + to_string( values[ i ] ) + " | \n";
            }
        }
        return rv;
    }

    queue< string > getKeys() {
        queue< string > q;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                q.push( *( keys[ i ] ) );
            }
        }
        return q;
    }
};

int main( int argc, char ** argv ) {
    // Test LinearProbingHashST
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    LinearProbingHashST hashST;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], i );
    }

    cout << "DEBUG: hashST.toString(): \n" << hashST.toString() << endl;

    cout << "DEBUG: hashST.getAll( L ): \n";
    vector< int > valueVec = hashST.getAll( "L" );
    for ( int i = 0; i < valueVec.size(); ++i ) {
        cout << " " << valueVec[ i ];
    }

    return 0;
}
