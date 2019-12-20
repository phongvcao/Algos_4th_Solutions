//
// Created by Phong Cao on 2019-02-08.
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
#include <iterator>
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
using std::stoi;
using std::stol;
using std::vector;           // Unordered Array
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::deque;
using std::queue;
using std::stack;
using std::next;             // Return an advanced iter without changing original iter
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

// Implement AVLTreeST, then use this AVLTreeST to insert the non-overlapping intervals
class IntervalAVLTreeST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( int key, int value, int N, int height ) {
        return make_shared< Node >( key, value, N, height );
    }

    class Node {
    public:
        int key = -1;
        int value = 0;
        int N = 1;
        int height = 0;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( int key, int value, int N, int height ) {
            this->key = key;
            this->value = value;
            this->N = N;
            this->height = height;
        }

        virtual ~Node() {
            // not implemented
        }

        bool contains( int key ) {
            return ( key >= this->key ) && ( key <= this->value );
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << h.key << " : " << h.value << " ; size : " << h.N << " ; height : " << h.height;
            if ( h.left ) {
                out << " ; left : " << h.left->key;
            } else {
                out << " ; left : null";
            }

            if ( h.right ) {
                out << " ; right : " << h.right->key;
            } else {
                out << " ; right : null";
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

    NodePtr root = NULL;

    int balanceFactor( NodePtr h ) {
        if ( ! h ) return 0;
        return height( h->left ) - height( h->right );
    }

    NodePtr rotateLeft( NodePtr h ) {
        NodePtr x = h->right;
        h->right = x->left;
        x->left = h;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        x->height = 1 + std::max( height( x->left ), height( x->right ) );
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return x;
    }

    NodePtr rotateRight( NodePtr h ) {
        NodePtr x = h->left;
        h->left = x->right;
        x->right = h;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        x->height = 1 + std::max( height( x->left ), height( x->right ) );
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return x;
    }

    NodePtr balance( NodePtr h ) {
        if ( balanceFactor( h ) < -1 ) {
            if ( balanceFactor( h->right ) > 0 ) {
                h->right = rotateRight( h->right );
            }
            h = rotateLeft( h );
        } else if ( balanceFactor( h ) > 1 ) {
            if ( balanceFactor( h->left ) < 0 ) {
                h->left = rotateLeft( h->left );
            }
            h = rotateRight( h );
        }
        return h;
    }

    int size( NodePtr h ) {
        if ( ! h ) {
            return 0;
        } else {
            return h->N;
        }
    }

    int height( NodePtr h ) {
        if ( ! h ) {
            return 0;
        } else {
            return h->N;
        }
    }

    string toString( NodePtr h ) {
        if ( ! h ) return "";
        string rv = toString( h->left );
        rv += h->toString();
        rv += toString( h->right );
        return rv;
    }

    NodePtr put( NodePtr h, int key, int value ) {
        if ( ! h ) return newNode( key, value, 1, 0 );
        if ( key < h->key ) {
            h->left = put( h->left, key, value );
        } else if ( key > h->key ) {
            h->right = put( h->right, key, value );
        } else {
            h->value = value;
            return h;
        }

        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr get( NodePtr h, int key ) {
        if ( ! h ) return NULL;
        if ( key < h->key ) {
            return get( h->left, key );
        } else if ( key > h->key ) {
            if ( h->value > key ) {
                return h;
            }
            return get( h->right, key );
        } else {
            return h;
        }
    }

    int rank( NodePtr h, int key ) {
        if ( ! h ) return 0;
        if ( key < h->key ) {
            return rank( h->left, key );
        } else if ( key > h->key ) {
            return rank( h->right, key ) + 1 + size( h->left );
        } else {
            return size( h->left );
        }
    }

    NodePtr select( NodePtr h, int k ) {
        if ( ! h ) return NULL;
        int sz = size( h->left );
        if ( k < sz ) {
            return select( h->left, k );
        } else if ( k > sz ) {
            return select( h->right, k - 1 - sz );
        } else {
            return h;
        }
    }

    NodePtr min( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return h;
        return min( h->left );
    }

    NodePtr max( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->right ) return h;
        return max( h->right );
    }

    NodePtr floor( NodePtr h, int key ) {
        if ( ! h ) return NULL;
        if ( key < h->key ) {
            return floor( h->left, key );
        } else if ( key == h->key ) {
            return h;
        }

        NodePtr temp = floor( h->right, key );
        if ( temp ) {
            return temp;
        }
        return h;
    }

    NodePtr ceiling( NodePtr h, int key ) {
        if ( ! h ) return NULL;
        if ( key > h->key ) {
            return ceiling( h->right, key );
        } else if ( key == h->key ) {
            return h;
        }

        NodePtr temp = ceiling( h->left, key );
        if ( temp ) {
            return temp;
        }
        return h;
    }

    NodePtr deleteMin( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return h->right;
        h->left = deleteMin( h->left );
        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr deleteMax( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->right ) return h->left;
        h->right = deleteMax( h->right );
        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr deleteKey( NodePtr h, int key ) {
        if ( ! h ) return NULL;
        if ( key < h->key ) {
            h->left = deleteKey( h->left, key );
        } else if ( key > h->key ) {
            h->right = deleteKey( h->right, key );
        } else {
            if ( ! h->left ) return h->right;
            if ( ! h->right ) return h->left;

            NodePtr temp = h;
            h = min( temp->right );
            h->right = deleteMin( temp->right );
            h->left = temp->left;
        }

        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    void getKeys( NodePtr h, deque< int >& dq, int low, int high ) {
        if ( ! h ) return;
        if ( h->key < low ) return;
        if ( h->key > high ) return;
        getKeys( h->left, dq, low, high );
        dq.push_back( h->key );
        getKeys( h->right, dq, low, high );
    }

public:

    IntervalAVLTreeST() {
        // not immplemented
    }

    virtual ~IntervalAVLTreeST() {
        // not immplemented
    }

    int size() {
        return size( root );
    }

    int height() {
        return height( root );
    }

    bool empty() {
        return size() == 0;
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + to_string( root->key ) + "\n";
        rv += toString( root );
        return rv;
    }

    void put( int key, int value ) {
        root = put( root, key, value );
    }

    const int* get( int key ) {
        NodePtr rv = get( root, key );
        if ( rv ) {
            return &( rv->value );
        } else {
            return NULL;
        }
    }

    vector< int > getInterval( int key ) {
        NodePtr rv = get( root, key );
        vector< int > rvVec;
        if ( rv ) {
            rvVec.push_back( rv->key );
            rvVec.push_back( rv->value );
        }
        return rvVec;
    }

    int rank( int key ) {
        return rank( root, key );
    }

    const int* select( int key ) {
        NodePtr rv = select( root, key );
        if ( rv ) {
            return &( rv->key );
        } else {
            return NULL;
        }
    }

    const int* min() {
        NodePtr rv = min( root );
        if ( rv ) {
            return &( rv->key );
        } else {
            return NULL;
        }
    }

    const int* max() {
        NodePtr rv = max( root );
        if ( rv ) {
            return &( rv->key );
        } else {
            return NULL;
        }
    }

    const int* floor( int key ) {
        NodePtr rv = floor( root, key );
        if ( rv ) {
            return &( rv->key );
        } else {
            return NULL;
        }
    }

    const int* ceiling( int key ) {
        NodePtr rv = ceiling( root, key );
        if ( rv ) {
            return &( rv->key );
        } else {
            return NULL;
        }

    }

    void deleteMin() {
        root = deleteMin( root );
    }

    void deleteMax() {
        root = deleteMax( root );
    }

    bool contains( int key ) {
        return get( key ) != NULL;
    }

    void deleteKey( int key ) {
        if ( ! contains( key ) ) return;
        root = deleteKey( root, key );
    }

    deque< int > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    deque< int > getKeys( int low, int high ) {
        deque< int > dq;
        if ( low > high ) return dq;
        getKeys( root, dq, low, high );
        return dq;
    }
};

// 2nd Solution: Use comparator function for std::map.
class Interval {
public:
    int begin = 0;
    int end = 0;

    Interval() {
        // not implemented
    }

    Interval( int begin, int end )
        : begin( begin ),
          end( end )
    {
        // not implemented
    }

    friend bool operator <( const Interval& first, const Interval& second ) {
        return first.begin < second.begin;
    }

    string toString() {
        string rv = " | " + to_string( begin ) + " : " + to_string( end ) + " | ";
        return rv;
    }

    bool contains( int key ) {
        return ( key >= begin ) && ( key <= end );
    }
};

vector< int > binarySearch( const set< Interval >& intervalSet, int key ) {
    int low = 0;
    int high = intervalSet.size() - 1;
    int foundIndex = 0;
    while ( low <= high ) {
        int mid = low + ( high - low ) / 2;
        if ( key < next( intervalSet.begin(), mid )->begin ) {
            high = mid - 1;
        } else if ( key > next( intervalSet.begin(), mid )->begin ) {
            if ( key <= next( intervalSet.begin(), mid )->end ) {
                foundIndex = mid;
                break;
            }
            low = mid + 1;
        } else {
            foundIndex = mid;
            break;
        }
    }
    vector< int > rv;
    if ( key < next( intervalSet.begin(), foundIndex )->begin || key > next( intervalSet.begin(), foundIndex )->end ) {
        return rv;
    }
    rv.push_back( next( intervalSet.begin(), foundIndex )->begin );
    rv.push_back( next( intervalSet.begin(), foundIndex )->end );
    return rv;
}

int main( int argc, char ** argv ) {
    // Test 1st solution - IntervalAVLTreeST
    int intervalArr1[ 10 ][ 2 ] = {
            { 0, 2 },
            { 3, 5 },
            { 6, 8 },
            { 9, 11 },
            { 12, 14 },
            { 15, 17 },
            { 18, 20 },
            { 21, 23 },
            { 24, 26 },
            { 27, 29 },
    };
    IntervalAVLTreeST st;

    for ( int i = 0; i < 10; ++i ) {
        st.put( intervalArr1[ i ][ 0 ], intervalArr1[ i ][ 1 ] );
    }

    cout << "DEBUG: st.toString(): \n" << st.toString() << endl;

    vector< int > rvVec = st.getInterval( 13 );
    cout << "DEBUG: st.getInterval( 13 ): \n" << rvVec[ 0 ] << " : " << rvVec[ 1 ] << endl;

    rvVec = st.getInterval( 30 );
    if ( rvVec.empty() ) {
        cout << "DEBUG: st.getInterval( 30 ): null\n" << endl;
    } else {
        cout << "DEBUG: st.getInterval( 30 ): \n" << rvVec[ 0 ] << " : " << rvVec[ 1 ] << endl;
    }

    // Test 2nd solution - binary search through std::map
    int intervalArr2[ 10 ][ 2 ] = {
            { 0, 2 },
            { 3, 5 },
            { 6, 8 },
            { 9, 11 },
            { 12, 14 },
            { 15, 17 },
            { 18, 20 },
            { 21, 23 },
            { 24, 26 },
            { 27, 29 },
    };
    set< Interval > intervalSet;
    for ( int i = 0; i < 10; ++i ) {
        Interval interval( intervalArr2[ i ][ 0 ], intervalArr2[ i ][ 1 ] );
        intervalSet.insert( interval );
    }

    cout << "DEBUG: intervalSet: \n" << endl;
    for ( set< Interval >::iterator iter = intervalSet.begin(); iter != intervalSet.end(); ++iter ) {
        cout << " | " << iter->begin << " : " << iter->end << " | \n";
    }

    rvVec = binarySearch( intervalSet, 13 );
    cout << "DEBUG: st.getInterval( 13 ): \n" << rvVec[ 0 ] << " : " << rvVec[ 1 ] << endl;

    rvVec = binarySearch( intervalSet, 30 );
    if ( rvVec.empty() ) {
        cout << "DEBUG: st.getInterval( 30 ): null\n" << endl;
    } else {
        cout << "DEBUG: st.getInterval( 30 ): \n" << rvVec[ 0 ] << " : " << rvVec[ 1 ] << endl;
    }


    return 0;
}
