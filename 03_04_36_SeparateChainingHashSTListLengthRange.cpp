//
// Created by Phong Cao on 2019-02-03.
//


#include <iostream>
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
using std::make_shared;
using std::shared_ptr;

template< typename Key, typename Value >
class SeparateChainingHashST {
private:

    class Node {
    public:
        const Key * key = NULL;
        const Value * value = NULL;
        shared_ptr< Node > next = NULL;

        Node( const Key& key, const Value& value ) {
            this->key = &key;
            this->value = &value;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            return " | " + *key + " : " + *value + " | ";
        }
    };

    int M = 17;
    int N = 0;
    vector< shared_ptr< Node > > st;
    vector< int > listSizes;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:

    SeparateChainingHashST( int M )
        : M( M )
    {
        st.resize( M );
        listSizes.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
            listSizes[ i ] = 0;
        }
    }

    SeparateChainingHashST()
        : SeparateChainingHashST( 997 )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        shared_ptr< Node > ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                if ( *( ptr->key ) == key ) {
                    ptr->value = &value;
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = make_shared< Node >( key, value );
        } else {
            st[ hash( key ) ] = make_shared< Node >( key, value );
        }
        ++listSizes[ hash( key ) ];
        ++N;
    }

    const Value * get( const Key& key ) {
        shared_ptr< Node > ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    void deleteKey( const Key& key ) {
        shared_ptr< Node > ptr = st[ hash( key ) ];
        shared_ptr< Node > beforePtr = NULL;
        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    st[ hash( key ) ] = NULL;
                }
                --listSizes[ hash( key ) ];
                --N;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    queue< Key > getKeys() {
        queue< Key > queue;
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            while ( ptr ) {
                queue.push( *( ptr->key ) );
                ptr = ptr->next;
            }
        }
        return queue;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            while ( ptr ) {
                rv += "\n" + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    int shortestListLength() {
        int rv = -1;
        for ( int i = 0; i < M; ++i ) {
            if ( rv == -1 || rv > listSizes[ i ] ) {
                rv = listSizes[ i ];
            }
        }
        return rv;
    }

    int longestListLength() {
        int rv = -1;
        for ( int i = 0; i < M; ++i ) {
            if ( rv == -1 || rv < listSizes[ i ] ) {
                rv = listSizes[ i ];
            }
        }
        return rv;
    }
};


int main( int argc, char ** argv ) {
    string keyArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    string valueArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    SeparateChainingHashST< string, string > hashST( 17 );

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
        cout << " | " << keysQueue.front() << " : " << *hashST.get( keysQueue.front() ) << " | ";
        keysQueue.pop();
    }

    cout << "\nDEBUG: hashST.get( L ) : " << hashST.get( "L" ) << endl;
    cout << "\nDEBUG: hashST.shortestListLength() : " << hashST.shortestListLength() << endl;
    cout << "\nDEBUG: hashST.longestListLength() : " << hashST.longestListLength() << endl;

    return 0;
}
