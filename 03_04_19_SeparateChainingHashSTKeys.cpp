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
using std::make_shared;
using std::shared_ptr;

template< typename Key, typename Value >
class SeparateChainingHashST {

private:
    class Node {
    public:
        Key key = NULL;
        Value value = NULL;
        shared_ptr< Node > next = NULL;

        Node( Key key, Value value )
            : key( key ),
              value( value )
        {
            // not implemented
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + key + " : " + value;
            if ( next ) {
                rv += " ; next : " + next->key;
            } else {
                rv += " ; next : null";
            }
            rv += " | ";
            return rv;
        }
    };

    int hash( Key key ) {
        return std::hash< Key >{}( key ) % M;
    }

    int M;
    int N;
    vector< shared_ptr< Node > > st;

public:
    SeparateChainingHashST( int M )
        : M( M )
    {
        for ( int i = 0; i < M; ++i ) {
            st.push_back( NULL );
        }
    }

    SeparateChainingHashST() {
        SeparateChainingHashST( 997 );
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( Key key, Value value ) {
        shared_ptr< Node > ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                if ( std::hash< Key >{}( key ) == std::hash< Key >{}( ptr->key ) ) {
                    ptr->value = value;
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = make_shared< Node >( key, value );
            ++N;
        } else {
            st[ hash( key ) ] = make_shared< Node >( key, value );
            ++N;
        }
    }

    void deleteKey( Key key ) {

    }

    Value get( Key key ) {
        shared_ptr< Node > ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( std::hash< Key >{}( key ) != std::hash< Key >{}( ptr->key ) ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            while ( ptr ) {
                rv += "\n" + to_string( i ) + " : " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    queue< Key > keys() {
        queue< Key > queue;
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            while ( ptr ) {
                queue.push( ptr->key );
                ptr = ptr->next;
            }
        }
        return queue;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    SeparateChainingHashST< string, string > hashST( 997 );

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << hashST.toString() << endl;

    queue< string > keysQueue = hashST.keys();
    while ( ! keysQueue.empty() ) {
        cout << keysQueue.front() << " ";
        keysQueue.pop();
    }

    return 0;
}
