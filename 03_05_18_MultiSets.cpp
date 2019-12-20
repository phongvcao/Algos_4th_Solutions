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

// MultiHashSet API
template< typename Key >
class MultiHashSet {
public:
    MultiHashSet() {}
    virtual ~MultiHashSet() {}
    virtual void add( const Key& key ) = 0;
    virtual void deleteKey( const Key& key ) = 0;
    virtual bool contains( const Key& key ) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual queue< Key > getKeys() = 0;
    virtual string toString() = 0;
};

// MultiSet API
template< typename Key >
class MultiSet {
public:
    MultiSet() {}
    virtual ~MultiSet() {}
    virtual void put( const Key& key ) = 0;
    virtual int size() = 0;
    virtual bool empty() = 0;
    virtual string toString() = 0;
    virtual bool contains( const Key& key ) = 0;
    virtual const Key* min() = 0;
    virtual const Key* max() = 0;
    virtual void deleteMin() = 0;
    virtual void deleteMax() = 0;
    virtual void deleteKey( const Key& key ) = 0;
    virtual int rank( const Key& key ) = 0;
    virtual const Key* select( int k ) = 0;
    virtual const Key* floor( const Key& key ) = 0;
    virtual const Key* ceiling( const Key& key ) = 0;
    virtual queue< Key > getKeys() = 0;
    virtual queue< Key > getKeys( const Key& low, const Key& high ) = 0;
};

// SeparateChainingMultiSet
template< typename Key >
class SeparateChainingMultiSet : public MultiHashSet< Key > {
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

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key );
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

    SeparateChainingMultiSet( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    SeparateChainingMultiSet()
        : SeparateChainingMultiSet( 17 )
    {
        // not implemented
    }

    virtual ~SeparateChainingMultiSet() {
        // not implemented
    }

    void add( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
//                if ( key == *( ptr->key ) ) {
//                    return;
//                }
                ptr = ptr->next;
            }
            ptr->next = newNode( key );
        } else {
            st[ hash( key ) ] = newNode( key );
        }
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;

        while ( contains( key ) ) {
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
    }

    bool contains( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];

        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
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
                rv += "i : " + to_string( i ) + " " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }
};

// BinarySearchMultiSet
template< typename Key >
class BinarySearchMultiSet : public MultiSet< Key > {
private:
    vector< const Key* > keys;
    int N = 0;
    int M = 0;

    void resize( int cap ) {
        // to be implemented
    }

public:
    BinarySearchMultiSet( int M )
        : M( M )
    {
        keys.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
        }
    }

    BinarySearchMultiSet()
        : BinarySearchMultiSet( 17 )
    {
        // not implemented
    }

    virtual ~BinarySearchMultiSet() {
        // not implemented
    }

    void put( const Key& key ) {
        if ( N > M / 2 ) resize( 2 * M );
        int i = rank( key );
        for ( int j = N - 1; j >= i; --j ) {
            keys[ j + 1 ] = keys[ j ];
        }
        keys[ i ] = &key;
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
        oss << "\n";
        for ( int i = 0; i < N; ++i ) {
            oss << *( keys[ i ] ) << " ";
        }
        return oss.str();
    }

    bool contains( const Key& key ) {
        return rank( key ) != -1;
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
        }
        keys[ N - 1 ] = NULL;
        --N;
    }

    void deleteMax() {
        if ( empty() ) return;
        keys[ N - 1 ] = NULL;
        --N;
    }

    void deleteKey( const Key& key ) {
        int i = rank( key );
        if ( *( keys[ i ] ) != key ) return;
        while ( *( keys[ i ] ) == key ) {
            for ( int j = i; j < N - 1; ++j ) {
                keys[ j ] = keys[ j + 1 ];
            }
            keys[ N - 1 ] = NULL;
            --N;
            i = rank( key );
        }
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
        if ( k >= N ) return NULL;
        return keys[ k ];
    }

    const Key* floor( const Key& key ) {
        int i = rank( key );
        if ( *( keys[ i ] ) == key ) return keys[ i ];
        return keys[ i - 1 ];
    }

    const Key* ceiling( const Key& key ) {
        int i = rank( key );
        if ( *( keys[ i ] ) == key ) return keys[ i ];
        return keys[ i ];
    }

    queue< Key > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    queue< Key > getKeys( const Key& low, const Key& high ) {
        queue< Key > q;
        if ( low > high ) return q;
        if ( low < *( keys[ 0 ] ) ) return q;
        if ( high > *( keys[ N - 1 ] ) ) return q;
        int lowIdx = rank( low );
        int highIdx = rank( high );
        for ( int i = lowIdx; i <= highIdx; ++i ) {
            q.push( *( keys[ i ] ) );
        }
        return q;
    }
};


int main( int argc, char ** argv ) {
    // Test SeparateChainingMultiSet
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    SeparateChainingMultiSet< string > hashST;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.add( keyArr[ i ] );
    }

    cout << "DEBUG: hashST.toString(): \n" << hashST.toString() << endl;

    hashST.deleteKey( "L" );
    cout << "DEBUG: hashST.deleteKey( L ): \n" << hashST.toString() << endl;

    // Test BinarySearchMultiSet
    string keyArr1[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    BinarySearchMultiSet< string > bsSet;
    for ( int i = 0; i < sizeof( keyArr1 ) / sizeof( string ); ++i ) {
        bsSet.put( keyArr1[ i ] );
    }

    cout << "DEBUG: bsSet.toString(): \n" << bsSet.toString() << endl;

    bsSet.deleteKey( "L" );
    cout << "DEBUG: bsSet.deleteKey( L ): \n" << bsSet.toString() << endl;

    cout << "DEBUG: bsSet.floor( C ): " << *( bsSet.floor( "C" ) ) << endl;
    cout << "DEBUG: bsSet.floor( D ): " << *( bsSet.floor( "D" ) ) << endl;
    cout << "DEBUG: bsSet.ceiling( C ): " << *( bsSet.ceiling( "C" ) ) << endl;
    cout << "DEBUG: bsSet.ceiling( D ): " << *( bsSet.ceiling( "D" ) ) << endl;

    return 0;
}
