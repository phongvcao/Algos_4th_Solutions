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

template< typename Key >
class SequentialSearchSet {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key ) {
        return make_shared< Node >( key );
    }

    class Node {
    public:
        const Key* key = NULL;
        NodePtr next = NULL;

        Node( const Key& key ) {
            this->key = &key;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    friend ostream & operator << ( ostream & out, const Node & h ) {
        out << " | " << *( h.key );
        if ( h.next ) {
            out << " ; next : " << *( h.next->key );
        } else {
            out << " ; next : null";
        }
        out << " | ";
        return out;
    }

    vector< NodePtr > st;
    int M = 17;
    int N = 0;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:

    SequentialSearchSet( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    SequentialSearchSet()
        : SequentialSearchSet( 997 )
    {
        // not implemented
    }

    virtual ~SequentialSearchSet() {
        // not implemented
    }

    void add( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                if ( *( ptr->key ) == key ) {
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = newNode( key );
        } else {
            st[ hash( key ) ] = newNode( key );
        }
        ++N;
    }

    void deleteKey( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
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

    bool contains( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return N;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += "\n" + to_string( i ) + " : " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    SequentialSearchSet< string > set( 17 );

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        set.add( keyArr[ i ] );
    }

    cout << "DEBUG: set: \n" << set.toString() << endl;

    set.deleteKey( "L" );
    cout << "DEBUG: set (AFTER deleteKey( L )): \n" << set.toString() << endl;

    return 0;
}
