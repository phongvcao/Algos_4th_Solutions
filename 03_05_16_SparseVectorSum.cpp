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
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

// Implement SeparateChainingHashST
template< typename Key, typename Value >
class SeparateChainingHashST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( Key key, Value value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        Key key = NULL;
        Value value = NULL;
        NodePtr next = NULL;

        Node( Key key, Value value ) {
            this->key = key;
            this->value = value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << h.key << " : " << h.value;
            if ( h.next ) {
                out << " ; next : " << h.next->key;
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

    SeparateChainingHashST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    SeparateChainingHashST()
        : SeparateChainingHashST( 17 )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( Key key, Value value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr ) {
                if ( key == ptr->key ) {
                    ptr->value = value;
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

    void deleteKey( Key key ) {
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( ptr->key == key ) {
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

    bool contains( Key key ) {
        return (bool)get( key );
    }

    Value get( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( key == ptr->key ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return (Value)NULL;
    }

    int size() {
        return N;
    }

    int empty() {
        return size() == 0;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += "i : " + to_string( i ) + ptr->toString();
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
                q.push( ptr->key );
                ptr = ptr->next;
            }
        }
        return q;
    }

};

// Implement SparseVector
class SparseVector {

public:

    SeparateChainingHashST< int, double > st;

    SparseVector() {
        // not implemented
    }

    virtual ~SparseVector() {
        // not implemented
    }

    int size() {
        return st.size();
    }

    void put( int i, double x ) {
        st.put( i, x );
    }

    double get( int i ) {
        if ( ! st.contains( i ) ) return 0.0;
        else return st.get( i );
    }

    double dot( vector< double > that ) {
        double sum = 0.0;
        queue< int > q = st.getKeys();
        int i = 0;
        while ( ! q.empty() ) {
            sum += that[ i ] * q.front();
            q.pop();
            ++i;
        }
        return sum;
    }

    SparseVector& sum( SparseVector& other ) {
        // Get keys of both vectors
        // Loop through first SparseVector key
        // Add all elements of index i to the other sparseVector's index-i element
        //     If the other vector doesn't have this element, just hash this queue< Key > element to rv
        //     If sum becomes zero, don't hash this element at all to rv
        // As we add, we remove from both queue< Key > of both SparseVectors
        // In the end, if queue< Key > of others still have elements left, just hash them into rv.
        queue< int > thisQueue = st.getKeys();
        queue< int > otherQueue = other.st.getKeys();

        int oldMaxKey = thisQueue.front();
        int maxKey = oldMaxKey;
        thisQueue.push( maxKey );
        thisQueue.pop();

        while ( thisQueue.front() != oldMaxKey ) {
            if ( maxKey < thisQueue.front() ) {
                maxKey = thisQueue.front();
            }
            thisQueue.pop();
        }

        oldMaxKey = otherQueue.front();
        otherQueue.push( oldMaxKey );
        otherQueue.pop();
        while ( otherQueue.front() != oldMaxKey ) {
            if ( maxKey < otherQueue.front() ) {
                maxKey = otherQueue.front();
            }
            otherQueue.pop();
        }

        for ( int i = 0; i < maxKey + 1; ++i ) {
            double sum = st.get( i ) + other.st.get( i );
            if ( sum != 0 ) {
                st.put( i, sum );
            } else {
                st.deleteKey( i );
            }
        }

        return *this;
    }
};

int main( int argc, char ** argv ) {
    // Test SparseVectorSum
    int keyArr[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    double valueArr[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    SparseVector sv;
    SparseVector sv1;

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( int ); ++i ) {
        sv.put( keyArr[ i ], valueArr[ i ] );
        sv1.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << "BEFORE: " << sv.st.toString() << endl;

    SparseVector* svPtr = &( sv.sum( sv1 ) );
    cout << "AFTER: " << svPtr->st.toString() << endl;

    return 0;
}
