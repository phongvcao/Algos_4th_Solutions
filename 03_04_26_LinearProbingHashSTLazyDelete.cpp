//
// Created by Phong Cao on 2019-02-02.
//


#include <iostream>
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
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::vector;
using std::map;
using std::queue;
using std::stack;
using std::fill;
using std::make_shared;
using std::shared_ptr;

template< typename Key, typename Value >

class LinearProbingHashST {

private:
    int M = 16;
    int N = 0;
    vector< const Key * > keys;
    vector< const Value * > values;

    int hash( const Key key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:
    LinearProbingHashST( int M )
        : M( M )
    {
        keys.resize( M );
        values.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
            values[ i ] = NULL;
        }
    }

    LinearProbingHashST()
        : LinearProbingHashST( 997 )
    {
        // not implemented
    }

    virtual ~LinearProbingHashST() {
        // not implemented
    }

    void resize( int cap ) {
        LinearProbingHashST temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL && values[ i ] != NULL ) {
                temp.put( *keys[ i ], *values[ i ] );
            }
        }
        this->keys = temp.keys;
        this->values = temp.values;
        this->M = temp.M;
    }

    void put( const Key& key, const Value& value ) {
        if ( N > M / 2 ) resize( M * 2 );
        int i;
        for ( i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                // Let's try this out
                values[ i ] = &value;
                return;
            }
        }
        keys[ i ] = &key;
        values[ i ] = &value;
        ++N;
    }

    const Value * get( const Key& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                return values[ i ];
            }
        }
        return NULL;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        int i = hash( key );
        while ( *keys[ i ] != key ) {
            i = ( i + 1 ) % M;
        }
        keys[ i ] = NULL;
        values[ i ] = NULL;
        i = ( i + 1 ) % M;
        while ( keys[ i ] != NULL ) {
            const Key * keyToRedo = keys[ i ];
            const Value * valueToRedo = values[ i ];
            --N;
            put( *keyToRedo, *valueToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    void deleteKeyLazy( const Key& key ) {
        if ( ! contains( key ) ) return;
        int i = hash( key );
        while ( *keys[ i ] != key ) {
            i = ( i + 1 ) % M;
        }
        values[ i ] = NULL;
        i = ( i + 1 ) % M;
        while ( keys[ i ] != NULL ) {
            const Key * keyToRedo = keys[ i ];
            const Value * valueToRedo = values[ i ];
            --N;
            put( *keyToRedo, *valueToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    queue< Key > getKeys() {
        queue< Key > queue;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                queue.push( *keys[ i ] );
            }
        }
        return queue;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                if ( values[ i ] != NULL ) {
                    rv += "\n" + to_string( i ) + " : | " + *keys[ i ] + " : " + *values[ i ] + " | ";
                } else {
                    rv += "\n" + to_string( i ) + " : | " + *keys[ i ] + " : NULL | ";
                }
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    LinearProbingHashST< string, string > hashST( 17 );

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << hashST.toString() << endl;

    queue< string > keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << keysQueue.front() << " ";
        keysQueue.pop();
    }

    hashST.deleteKeyLazy( "L" );
    cout << "\nDEBUG: hashST (AFTER delete( L )) :\n" << hashST.toString() << endl;

    hashST.resize( 997 );
    cout << "\nDEBUG: hashST (AFTER resize( 997 )) :\n" << hashST.toString() << endl;

    keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << " | " << keysQueue.front() << " : " << *hashST.get( keysQueue.front() ) << " | ";
        keysQueue.pop();
    }

    return 0;
}
