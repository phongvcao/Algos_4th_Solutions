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

// Implement SeparateChainingMultiST
template< typename Key, typename Value >
class SeparateChainingMultiST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        const Key* key = NULL;
        const Value* value = NULL;
        NodePtr next = NULL;

        Node( const Key& key, const Value& value ) {
            this->key = &key;
            this->value = &value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key ) << " : " << *( h.value );
            if ( h.next ) {
                out << " ; next : " << *( h.next->key );
            } else {
                out << " ; next : null";
            }
            out << " | ";
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

    SeparateChainingMultiST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    SeparateChainingMultiST()
        : SeparateChainingMultiST( 17 )
    {
        // not implemented
    }

    virtual ~SeparateChainingMultiST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
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
            if ( key == *( ptr->next ) ) {
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

    queue< Value > getAll( const Key& key ) {
        queue< Value > q;
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                q.push( *( ptr->value ) );
            }
            ptr = ptr->next;
        }
        return q;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
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
                rv += "\ni : " + to_string( i ) + " " + ptr->toString();
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

// Implement BinarySearchMultiST
template< typename Key, typename Value >
class BinarySearchMultiST {
private:

    vector< const Key* > keys;
    vector< const Value* > values;
    int M = 0;
    int N = 0;

public:

    BinarySearchMultiST( int M )
        : M( M )
    {
        keys.resize( M );
        values.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
            values[ i ] = NULL;
        }
    }

    BinarySearchMultiST()
        : BinarySearchMultiST( 17 )
    {
        // not implemented
    }

    virtual ~BinarySearchMultiST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        int i = rank( key );
        for ( int j = N - 1; j >= i; --j ) {
            keys[ j + 1 ] = keys[ j ];
            values[ j + 1 ] = values[ j ];
        }
        keys[ i ] = &key;
        values[ i ] = &value;
        ++N;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }

    string toString() {
        ostringstream oss;
        oss << "\n\n";
        for ( int i = 0; i < N; ++i ) {
            oss << " | " << *( keys[ i ] ) << " : " << *( values[ i ] ) << " | \n";
        }
        return oss.str();
    }

    const Value* get( const Key& key ) {
        int i = rank( key );
        if ( key == *( keys[ i ] ) ) return values[ i ];
        return NULL;
    }

    queue< Value > getAll( const Key& key ) {
        queue< Value > q;
        int i = rank( key );
        if ( key != *( keys[ i ] ) ) return q;
        for ( int j = i; j >= 0; --j ) {
            if ( key == *( keys[ j ] ) ) {
                q.push( *( values[ i ] ) );
            } else {
                break;
            }
        }

        for ( int j = i + 1; j < N; ++j ) {
            if ( key == *( keys[ j ] ) ) {
                q.push( *( values[ i ] ) );
            } else {
                break;
            }
        }
        return q;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    const Key* min() {
        if ( empty() ) return NULL;
        return keys[ 0 ];
    }

    const Key* max() {
        if ( empty() ) return NULL;
        return keys[ N - 1 ];
    }

    void deleteMin() {
        if ( empty() ) return;
        for ( int i = 0; i < N - 1; ++i ) {
            keys[ i ] = keys[ i + 1 ];
            values[ i ] = values[ i + 1 ];
        }
        keys[ N - 1 ] = NULL;
        values[ N - 1 ] = NULL;
        --N;
    }

    void deleteMax() {
        if ( empty() ) return;
        keys[ N - 1 ] = NULL;
        values[ N - 1 ] = NULL;
        --N;
    }

    void deleteKey( const Key& key ) {
        int i = rank( key );
        if ( key != *( keys[ i ] ) ) return;
        for ( int j = i; j < N - 1; ++j ) {
            keys[ j ] = keys[ j + 1 ];
            values[ j ] = values[ j + 1 ];
        }
        keys[ N - 1 ] = NULL;
        values[ N - 1 ] = NULL;
        --N;
    }

    int rank( const Key& key ) {
        int low = 0;
        int high = N - 1;
        while ( low <= high ) {
            int mid = low + ( high - low ) / 2;
            if ( key < *( keys[ mid ] ) ) {
                high = mid - 1;
            } else if ( key > *( keys[ mid ] ) ) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        return low;
    }

    const Key* select( int k ) {
        if ( k < 0 || k >= N ) return NULL;
        return keys[ k ];
    }

    const Key* floor( const Key& key ) {
        int i = rank( key );
        if ( key == *( keys[ i ] ) ) return keys[ i ];
        return keys[ i - 1 ];
    }

    const Key* ceiling( const Key& key ) {
        int i = rank( key );
        if ( key == *( keys[ i ] ) ) return keys[ i ];
        return keys[ i ];
    }

    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < N; ++i ) {
            q.push( *( keys[ i ] ) );
        }
        return q;
    }
};

int main( int argc, char ** argv ) {
    // Test SeparateChainingMultiST
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    SeparateChainingMultiST< string, string > hashST;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << "DEBUG: hashST: \n" << hashST.toString() << endl;

    cout << "DEBUG: q: ";
    queue< string > q = hashST.getAll( "L" );
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    // Test BinarySearchMultiST
    string keyArr1[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    string valueArr1[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    BinarySearchMultiST< string, string > bsST;

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        bsST.put( keyArr1[ i ], valueArr1[ i ] );
    }

    cout << "\n\nDEBUG: bsST: \n" << bsST.toString() << endl;

    cout << "DEBUG: q1: ";
    queue< string > q1 = bsST.getAll( "L" );
    while ( ! q1.empty() ) {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << endl;

    return 0;
}
