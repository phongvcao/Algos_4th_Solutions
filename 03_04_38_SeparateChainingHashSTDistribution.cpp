//
// Created by Phong Cao on 2019-02-04.
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

    class Node;
    typedef shared_ptr< Node > NodePtr;

    class Node {
    public:
        const Key * key = NULL;
        const Value * value = NULL;
        NodePtr next = NULL;

        Node( const Key& key, const Value& value ) {
            this->key = &key;
            this->value = &value;
        }

        virtual ~Node() {

        }

        string toString() {
            string rv = " | " + *key + " : " + *value;
            if ( next ) {
                rv += " ; next : " + *( next->key );
            } else {
                rv += " ; next : null";
            }
            rv += " | ";
            return rv;
        }
    };

    NodePtr newNode( const Key& key, const Value& value ) {
        return make_shared< Node >( key, value );
    }

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

    int M = 17;
    int N = 0;
    vector< NodePtr > st;

public:

    SeparateChainingHashST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
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
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                if ( key == *( ptr->key ) ) {
                    ptr->value = &value;
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = make_shared< Node >( key, value );
        } else {
            st[ hash( key ) ] = make_shared< Node >( key, value );
        }
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    st[ hash( key ) ] = NULL;
                }
                --N;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    const Value* get( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }

    bool contains( const Key& key ) {
        return get( key ) == NULL;
    }

    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                q.push( *( ptr->key ) );
                ptr = ptr->next;
            }
        }
        return q;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += "\n" + to_string( i ) + " : " + st[ i ]->toString();
                ptr = ptr->next;
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
        cout << " | " << keysQueue.front() << " : " << *( hashST.get( keysQueue.front() ) ) << " | ";
        keysQueue.pop();
    }

    cout << "\nDEBUG: hashST.get( L ) : " << hashST.get( "L" ) << endl;

    return 0;
}
