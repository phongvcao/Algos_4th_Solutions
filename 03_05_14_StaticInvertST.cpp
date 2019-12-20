//
// Created by Phong Cao on 2019-02-06.
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

// Implement ST using SeparateChainingHashST
template< typename Key, typename Value >
class ST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;
    typedef shared_ptr< Value > ValuePtr;

    NodePtr newNode( const Key& key, const Value& value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        const Key* key = NULL;
        ValuePtr value = NULL;
        NodePtr next = NULL;

        Node( const Key& key, const Value& value ) {
            this->key = &key;
            this->value = make_shared< Value >( value );
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key ) << " : ";
            for ( int i = 0; i < h.value->size(); ++i ) {
                out << h.value->at( i ) << ", ";
            }
            if ( h.next ) {
                out << " ; next : " << *( h.next->key );
            } else {
                out << " ; next : null";
            }

            out << " | \n";
            return out;
        }

        string toString() {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

    vector< NodePtr > st;
    int M = 17;
    int N = 0;

public:

    ST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    ST()
        : ST( 97 )
    {
        // not implemented
    }

    virtual ~ST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                if ( *( ptr->key ) == key ) {
                    ptr->value = make_shared< Value >( value );
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = newNode( key, value );
        } else {
            st[ hash( key ) ] = newNode( key, value );
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
                return;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    int size() {
        return N;
    }

    int capacity() {
        return M;
    }

    bool empty() {
        return size() == 0;
    }

    ValuePtr get( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
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

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += "i : " + to_string( i ) + " : " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
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
};

ST< string, vector< string > > invert( ST< string, vector< string > >& st ) {
    ST< string, vector< string > > rv( st.capacity() );
    queue< string > q = st.getKeys();
    while ( ! q.empty() ) {
        shared_ptr< vector< string > > valueVec = st.get( q.front() );
        for ( int i = 0; i < valueVec->size(); ++i ) {
            if ( rv.contains( valueVec->at( i ) ) ) {
                shared_ptr< vector< string > > rvValueVec = rv.get( valueVec->at( i ) );
                rvValueVec->push_back( q.front() );
            } else {
                shared_ptr< vector< string > > rvValueVec = make_shared< vector< string > >( 1 );
                rvValueVec->push_back( q.front() );
                rv.put( valueVec->at( i ), *rvValueVec );
            }
        }
        q.pop();
    }
    return rv;
}

int main( int argc, char ** argv ) {
    // Test ST
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };

    ST< string, string > st;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        st.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << "DEBUG: st.toString(): \n" << st.toString() << endl;

    // Test invert
    string keyArr1[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr1[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    ST< string, vector< string > > st1;
    for ( int i = 0; i < sizeof( keyArr1 ) / sizeof( string ); ++i ) {
        shared_ptr< vector< string > > valueVec = make_shared< vector< string > >();
        for ( int j = 0; j < sizeof( valueArr1 ) / sizeof( string ); ++j ) {
            valueVec->push_back( valueArr1[ j ] );
        }
        st1.put( keyArr1[ i ], *valueVec );
    }

    cout << "DEBUG: st1.toString(): \n" << st1.toString() << endl;

    ST< string, vector< string > > st1Inverted = invert( st1 );
    cout << "DEBUG: st1Inverted.toString(): \n" << st1Inverted.toString() << endl;

    return 0;
}
