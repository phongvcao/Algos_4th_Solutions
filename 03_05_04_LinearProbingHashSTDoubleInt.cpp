//
// Created by Phong Cao on 2019-02-04.
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

// Implement HashSTInt using LinearProbingHashST
class HashSTInt {
private:

    int M = 17;
    int N = 0;
    vector< const int * > keys;

    int hash( const int& key ) {
        return std::hash< int >{}( key ) % M;
    }

public:

    HashSTInt( int M )
        : M( M )
    {
        keys.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
        }
    }

    HashSTInt()
        : HashSTInt( 97 )
    {
        // not implemented
    }

    virtual ~HashSTInt() {
        // not implemented
    }

    void add( const int& key ) {
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
        i = ( i + 1 ) % M;
        while ( keys[ i ] != NULL ) {
            const int * keyToRedo = keys[ i ];
            --N;
            add( *keyToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    bool contains( const int& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return true;
            }
        }
        return false;
    }

    void resize( const int& cap ) {
        HashSTInt temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                temp.add( *keys[ i ] );
            }
        }
        this->keys = temp.keys;
        this->M = temp.M;
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return N;
    }

    queue< int > getKeys() {
        queue< int > q;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                q.push( *keys[ i ] );
            }
        }
        return q;
    }

    string toString() {
        ostringstream oss;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                oss << " " << *keys[ i ];
            }
        }
        oss << endl;
        return oss.str();
    }
};

// Implement HashSTInt using LinearProbingHashST
class HashSTDouble {
private:
    vector< const double* > keys;
    int M = 17;
    int N = 0;

    int hash( const double& key ) {
        return std::hash< double >{}( key ) % M;
    }

public:

    HashSTDouble( int M )
        : M( M )
    {
        keys.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
        }
    }

    HashSTDouble()
        : HashSTDouble( 97 )
    {
        // not implemented
    }

    virtual ~HashSTDouble() {
        // not implemented
    }

    void add( const double& key ) {
        if ( N > M / 2 ) resize( M * 2 );
        int i;
        for ( i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
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
            const double * keyToRedo = keys[ i ];
            --N;
            add( *keyToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    void resize( int cap ) {
        HashSTDouble temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                temp.add( *keys[ i ] );
            }
        }
        this->keys = temp.keys;
        this->M = temp.M;
    }

    bool contains( const double& key ) {
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
        ostringstream oss;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                oss << " " << *keys[ i ];
            }
        }
        oss << endl;
        return oss.str();
    }
};

int main( int argc, char ** argv ) {
    int keyArr[] = { 14, 12, 10, 8, 6, 4, 2 ,0, 1, 3, 5, 7, 9, 11 };

    // Test HashSTInt
    HashSTInt hashSTInt( 17 );
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( int ); ++i ) {
        hashSTInt.add( keyArr[ i ] );
    }

    cout << "DEBUG: hashSTInt: \n" << hashSTInt.toString() << endl;
    cout << "DEBUG: hashSTInt.contains( 17 ): " << hashSTInt.contains( 17 ) << endl;

    hashSTInt.deleteKey( 3 );
    cout << "DEBUG: hashSTInt.deleteKey( 3 ): " << hashSTInt.toString() << endl;

    // Test HashSTDouble
    double keyArr2[] = { 14, 12, 10, 8, 6, 4, 2 ,0, 1, 3, 5, 7, 9, 11 };
    HashSTDouble hashSTDouble( 17 );
    for ( int i = 0; i < sizeof( keyArr2 ) / sizeof( double ); ++i ) {
        hashSTDouble.add( keyArr2[ i ] );
    }

    cout << "DEBUG: hashSTDouble: \n" << hashSTDouble.toString() << endl;
    cout << "DEBUG: hashSTDouble.contains( 17 ): " << hashSTDouble.contains( 17 ) << endl;

    hashSTInt.deleteKey( 3 );
    cout << "DEBUG: hashSTDouble.deleteKey( 3 ): " << hashSTDouble.toString() << endl;

    return 0;
}
