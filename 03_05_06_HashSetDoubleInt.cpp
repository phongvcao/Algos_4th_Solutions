//
// Created by Phong Cao on 2019-02-05.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <map>
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
using std::map;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

// Implement HashSetInt using LinearProbingHashST
class HashSetInt {
private:

    vector< const int* > keys;
    int M = 17;
    int N = 0;

    int hash( const int& key ) {
        return std::hash< int >{}( key ) % M;
    }

    void resize( int cap ) {
        HashSetInt temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                temp.put( *keys[ i ] );
            }
        }
        this->keys = temp.keys;
        this->M = temp.M;
    }

public:

    HashSetInt( int M )
        : M( M )
    {
        keys.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
        }
    }

    HashSetInt()
        : HashSetInt( 17 )
    {
        // not implemented
    }

    virtual ~HashSetInt() {
        // not implemented
    }

    void put( const int& key ) {
        if ( N > M / 2 ) resize( 2 * M );
        int i;
        for ( i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return;
            }
        }
        keys[ i ] = &key;
        ++N;
    }

    void deleteKey( const int& key ) {
        if ( ! contains( key ) ) return;
        int i = hash( key );
        while ( *keys[ i ] != key ) {
            i = ( i + 1 ) % M;
        }
        keys[ i ] = NULL;
        while( keys[ i ] != NULL ) {
            const int* keyToRedo = keys[ i ];
            --N;
            put( *keyToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    int size() {
        return N;
    }

    bool contains( const int& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return true;
            }
        }
        return false;
    }

    bool empty() {
        return size() == 0;
    }

    queue< int > getkeys() {
        queue< int > q;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                q.push( *keys[ i ] );
            }
        }
        return q;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                rv += to_string( *keys[ i ] ) + " ";
            }
        }
        return rv;
    }
};

// Implement HashSetDouble using LinearProbingHashST
class HashSetDouble {
private:

    vector< const double* > keys;
    int M = 17;
    int N = 0;

    int hash( const double& key ) {
        return std::hash< double >{}( key ) % M;
    }

    void resize( int cap ) {
        HashSetDouble temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                temp.put( *keys[ i ] );
            }
        }
        this->keys = temp.keys;
        this->M = temp.M;
    }

public:

    HashSetDouble( int M )
        : M( M )
    {
        keys.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
        }
    }

    HashSetDouble()
        : HashSetDouble( 17 )
    {
        // not implemented
    }

    virtual ~HashSetDouble() {
        // not implemented
    }

    void put( const double& key ) {
        if ( N > M / 2 ) resize( 2 * M );
        int i;
        for ( i = hash( key ); keys[ i ] != NULL ; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return;
            }
        }
        keys[ i ] = &key;
        ++N;
    }

    void deleteKey( const double& key ) {
        if ( ! contains( key ) ) return;
        int i = hash( key );
        while ( *keys[ i ] != key ) {
            i = ( i + 1 ) % M;
        }
        keys[ i ] = NULL;
        i = ( i + 1 ) % M;
        while ( keys[ i ] != NULL ) {
            const double* keyToRedo = keys[ i ];
            --N;
            put( *keyToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    bool empty() {
        return size() == 0;
    }

    bool contains( const double& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return true;
            }
        }
        return false;
    }

    int size() {
        return N;
    }

    queue< double > getKeys() {
        queue< double > q;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                q.push( *keys[ i ] );
            }
        }
        return q;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                rv += " " + to_string( *keys[ i ] );
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    // Test HashSetInt
    int keyArr[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    HashSetInt hashSetInt( 17 );
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( int ); ++i ) {
        hashSetInt.put( keyArr[ i ] );
    }

    cout << "DEBUG: hashSetInt: \n" << hashSetInt.toString() << endl;
    cout << "DEBUG: hashSetInt.size(): " << hashSetInt.size() << endl;
    cout << "DEBUG: hashSetInt.empty(): " << hashSetInt.empty() << endl;
    cout << "DEBUG: hashSetInt.contains( 1 ): " << hashSetInt.contains( 1 ) << endl;
    cout << "DEBUG: hashSetInt.contains( 100 ): " << hashSetInt.contains( 100 ) << endl;

    hashSetInt.deleteKey( 1 );
    cout << "DEBUG: hashSetInt (AFTER deleteKey( 1 )): \n" << hashSetInt.toString() << endl;

    // Test HashSetDouble
    double keyArr1[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    HashSetDouble hashSetDouble( 17 );
    for ( int i = 0; i < sizeof( keyArr1 ) / sizeof( double ); ++i ) {
        hashSetDouble.put( keyArr1[ i ] );
    }

    cout << "DEBUG: hashSetDouble: \n" << hashSetDouble.toString() << endl;
    cout << "DEBUG: hashSetDouble.size(): " << hashSetDouble.size() << endl;
    cout << "DEBUG: hashSetDouble.empty(): " << hashSetDouble.empty() << endl;
    cout << "DEBUG: hashSetDouble.contains( 1 ): " << hashSetDouble.contains( 1 ) << endl;
    cout << "DEBUG: hashSetDouble.contains( 100 ): " << hashSetDouble.contains( 100 ) << endl;

    hashSetDouble.deleteKey( 1 );
    cout << "DEBUG: hashSetDouble (AFTER deleteKey( 1 )): \n" << hashSetDouble.toString() << endl;

    return 0;
}
