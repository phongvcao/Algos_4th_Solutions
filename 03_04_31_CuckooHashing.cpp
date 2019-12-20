//
// Created by Phong Cao on 2019-02-03.
//


#include <iostream>
#include <cmath>
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
using std::sqrt;
using std::pow;
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

class HashSTCuckooHashing {

private:
    // First Hash Table
    int M1 = 17;
    int N1 = 0;
    vector< const Key * > keys1;
    vector< const Value * > values1;

    int hash1( const Key& key ) {
        return std::hash< Key >{}( key ) % M1;
    }

    // Second Hash Table
    int M2 = 31;
    int N2 = 0;
    vector< const Key * > keys2;
    vector< const Value * > values2;

    int hash2( const Key& key ) {
        return std::hash< Key >{}( key ) % M2;
    }

public:

    HashSTCuckooHashing( int M1, int M2 )
        : M1( M1 ),
          M2( M2 )
    {
        keys1.resize( M1 );
        values1.resize( M1 );
        for ( int i = 0; i < M1; ++i ) {
            keys1[ i ] = NULL;
            values1[ i ] = NULL;
        }

        keys2.resize( M2 );
        values2.resize( M2 );
        for ( int i = 0; i < M2; ++i ) {
            keys2[ i ] = NULL;
            values2[ i ] = NULL;
        }
    }

    HashSTCuckooHashing()
        : HashSTCuckooHashing( 97, 101 )
    {
        // not implemented
    }


    virtual ~HashSTCuckooHashing() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        if ( N1 > M1 / 2 ) resize( M1 * 2, true );
        if ( N2 > M2 / 2 ) resize( M2 * 2, false );

        const Key * keyFirst = keys1[ hash1( key ) ];
        if ( keyFirst == NULL ) {
            keys1[ hash1( key ) ] = &key;
            values1[ hash1( key ) ] = &value;
            ++N1;
        } else {
            const Key * oldKey1 = &*keys1[ hash1( key ) ];
            const Value * oldValue1 = &*values1[ hash1( key ) ];
            keys1[ hash1( key ) ] = &key;
            values1[ hash1( key ) ] = &value;

            const Key * keySecond = keys2[ hash2( key ) ];
            if ( keySecond == NULL ) {
                keys2[ hash2( key ) ] = &*oldKey1;
                values2[ hash2( key ) ] = &*oldValue1;
                ++N2;
            } else {
                const Key * oldKey2 = &*keys2[ hash2( key ) ];
                const Value * oldValue2 = &*values2[ hash2( key ) ];
                keys2[ hash2( key ) ] = &*oldKey1;
                values2[ hash2( key ) ] = &*oldValue1;

                if ( keys1.size() <= keys2.size() ) {
                    resize( M1 * 2, true );
                } else {
                    resize( M2 * 2, false );
                }

                put( *oldKey2, *oldValue2 );
            }
        }
    }

    const Value * get( const Key& key ) {
        const Key * keyFirst = keys1[ hash1( key ) ];
        if ( keyFirst != NULL && *keyFirst == key ) {
            return values1[ hash1( key ) ];
        }

        const Key * keySecond = keys2[ hash2( key ) ];
        if ( keySecond != NULL && *keySecond == key ) {
            return values2[ hash2( key ) ];
        }
        return NULL;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        const Key * keyFirst = keys1[ hash1( key ) ];
        if ( *keyFirst == key ) {
            keys1[ hash1( key ) ] = NULL;
            values1[ hash1( key ) ] = NULL;
            --N1;
            return;
        }

        const Key * keySecond = keys2[ hash2( key ) ];
        if ( *keySecond == key ) {
            keys2[ hash2( key ) ] = NULL;
            values2[ hash2( key ) ] = NULL;
            --N2;
            return;
        }
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    void resize( int cap, bool isFirst = true ) {
        if ( isFirst ) {
            HashSTCuckooHashing temp( cap, M2 );
            for ( int i = 0; i < M1; ++i ) {
                if ( keys1[ i ] != NULL ) {
                    temp.put( *keys1[ i ], *values1[ i ] );
                }
            }
            for ( int i = 0; i < M2; ++i ) {
                if ( keys2[ i ] != NULL ) {
                    temp.put( *keys2[ i ], *values2[ i ] );
                }
            }
            this->keys1 = temp.keys1;
            this->values1 = temp.values1;
            this->keys2 = temp.keys2;
            this->values2 = temp.values2;
            this->M1 = temp.M1;
            this->M2 = temp.M2;
        } else {
            HashSTCuckooHashing temp( M1, cap );
            for ( int i = 0; i < M1; ++i ) {
                if ( keys1[ i ] != NULL ) {
                    temp.put( *keys1[ i ], *values1[ i ] );
                }
            }
            for ( int i = 0; i < M2; ++i ) {
                if ( keys2[ i ] != NULL ) {
                    temp.put( *keys2[ i ], *values2[ i ] );
                }
            }
            this->keys1 = temp.keys1;
            this->values1 = temp.values1;
            this->keys2 = temp.keys2;
            this->values2 = temp.values2;
            this->M1 = temp.M1;
            this->M2 = temp.M2;
        }
    }

    int size() {
        return M1 + M2;
    }

    queue< Key > getKeys() {
        queue< Key > queue;
        for ( int i = 0; i < M1; ++i ) {
            if ( keys1[ i ] != NULL ) {
                queue.push( *keys1[ i ] );
            }
        }

        for ( int i = 0; i < M2; ++i ) {
            if ( keys2[ i ] != NULL ) {
                queue.push( *keys2[ i ] );
            }
        }
        return queue;
    }

    string toString() {
        string rv = "\nM1 : " + to_string( M1 ) + " | M2 : " + to_string( M2 ) + "\n";
        rv += "\nM1 : \n";
        for ( int i = 0; i < M1; ++i ) {
            if ( keys1[ i ] != NULL ) {
                rv += "\ni : " + to_string( i ) + " | " + *keys1[ i ] + " : " + *values1[ i ] + " | ";
            }
        }
        rv += "\nM2 : \n";
        for ( int i = 0; i < M2; ++i ) {
            if ( keys2[ i ] != NULL ) {
                rv += "\ni : " + to_string( i ) + " | " + *keys2[ i ] + " : " + *values2[ i ] + " | ";
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    string valueArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    HashSTCuckooHashing< string, string > hashST( 7, 11 );

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << hashST.toString() << endl;

    queue< string > keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << keysQueue.front() << " ";
        keysQueue.pop();
    }

    hashST.deleteKey( "L" );
    cout << "\nDEBUG: hashST (AFTER delete( L )) :\n" << hashST.toString() << endl;

    hashST.deleteKey( "E" );
    cout << "\nDEBUG: hashST (AFTER delete( E )) :\n" << hashST.toString() << endl;

    keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << " | " << keysQueue.front() << " : " << *( hashST.get( keysQueue.front() ) ) << " | ";
        keysQueue.pop();
    }

    cout << "\nDEBUG: hashST.get( L ) : " << hashST.get( "L" ) << endl;

    return 0;
}
