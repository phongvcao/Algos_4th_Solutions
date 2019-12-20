//
// Created by Phong Cao on 2019-02-05.
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

// Implement SetInt using RedBlackBST
class SetInt {
private:

    static const bool RED = true;
    static const bool BLACK = false;

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const int& key, int N, bool color ) {
        return make_shared< Node >( key, N, color );
    }

    class Node {
    public:
        const int* key = NULL;
        int N = 0;
        bool color = RED;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const int& key, int N, bool color ) {
            this->key = &key;
            this->N = N;
            this->color = color;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + to_string( *key ) + " ; size : " + to_string( N ) + " ; color : " + to_string( color );
            if ( left ) {
                rv += " ; left : " + to_string( *( left->key ) );
            } else {
                rv += " ; left : null";
            }

            if ( right ) {
                rv += " ; right : " + to_string( *( right->key ) );
            } else {
                rv += " ; right : null";
            }
            rv += " | \n";
            return rv;
        }
    };

    NodePtr root = NULL;

    bool isRed( NodePtr h ) {
        if ( ! h ) return false;
        return h->color == RED;
    }

    NodePtr rotateLeft( NodePtr h ) {
        NodePtr x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        return x;
    }

    NodePtr rotateRight( NodePtr h ) {
        NodePtr x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        return x;
    }

    void flipColors( NodePtr h ) {
        h->color = ! h->color;
        h->left->color = ! h->left->color;
        h->right->color = ! h->right->color;
    }

    NodePtr balance( NodePtr h ) {
        if ( isRed( h->right ) ) h = rotateLeft( h );
        if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
        if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );

        h->N = size( h->left ) + size( h->right ) + 1;
        return h;
    }

    NodePtr moveRedLeft( NodePtr h ) {
        flipColors( h );
        if ( isRed( h->right->left ) ) {
            h->right = rotateRight( h->right );
            h = rotateLeft( h );
            flipColors( h );
        }
        return h;
    }

    NodePtr moveRedRight( NodePtr h ) {
        flipColors( h );
        if ( isRed( h->left->left ) ) {
            h = rotateRight( h );
            flipColors( h );
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

    int height( NodePtr h, int count ) {
        if ( ! h ) return count;
        int leftHeight = height( h->left, count + 1 );
        int rightHeight = height( h->right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    string toString( NodePtr h ) {
        if ( ! h ) return "";
        string rv = toString( h->left );
        rv += h->toString();
        rv += toString( h->right );
        return rv;
    }

    NodePtr put( NodePtr h, const int& key ) {
        if ( ! h ) return newNode( key, 1, RED );
        if ( key < *( h->key ) ) {
            h->left = put( h->left, key );
        } else if ( key > *( h->key ) ) {
            h->right = put( h->right, key );
        } else {
            return h;
        }

        if ( isRed( h->right ) && ! isRed( h->left ) ) h = rotateLeft( h );
        if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
        if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );
        h->N = size( h->left ) + size( h->right ) + 1;
        return h;
    }

    int rank( NodePtr h, const int& key ) {
        if ( ! h ) return 0;
        if ( key < *( h->key ) ) {
            return rank( h->left, key );
        } else if ( key > *( h->key ) ) {
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

    NodePtr contains( NodePtr h, const int& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return contains( h->left, key );
        } else if ( key > *( h->key ) ) {
            return contains( h->right, key );
        } else {
            return h;
        }
    }

    NodePtr floor( NodePtr h, const int& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return floor( h->left, key );
        } else if ( key == *( h->key ) ) {
            return h;
        }

        NodePtr temp = floor( h->right, key );
        if ( temp ) {
            return temp;
        }
        return h;
    }

    NodePtr ceiling( NodePtr h, const int& key ) {
        if ( !h ) return NULL;
        if ( key > *( h->key ) ) {
            return ceiling( h->right, key );
        } else if ( key == *( h->key ) ) {
            return h;
        }

        NodePtr temp = ceiling( h->left, key );
        if ( temp ) {
            return temp;
        }
        return h;
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

    NodePtr deleteMin( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return NULL;

        if ( ! isRed( h->left ) && ! isRed( h->left->left ) ) {
            h = moveRedLeft( h );
        }
        h->left = deleteMin( h->left );
        return balance( h );
    }

    NodePtr deleteMax( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( isRed( h->left ) ) {
            h = rotateRight( h );
        }
        if ( ! h->right ) return NULL;

        if ( ! isRed( h->right ) && ! isRed( h->right->left ) ) {
            h = moveRedRight( h );
        }
        h->right = deleteMax( h->right );
        return balance( h );

    }

    NodePtr deleteKey( NodePtr h, const int& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            if ( ! h->left ) return NULL;

            if ( ! isRed( h->left ) && ! isRed( h->left->left ) ) {
                h = moveRedLeft( h );
            }
            h->left = deleteKey( h->left, key );
        } else {
            if ( isRed( h->left ) ) {
                h = rotateRight( h );
            }

            if ( key == *( h->key ) && ! h->right ) return NULL;

            if ( ! isRed( h->right ) && ! isRed( h->right->left ) ) {
                h = moveRedRight( h );
            }

            if ( key == *( h->key ) ) {
                NodePtr temp = h;
                h = min( temp->right );
                h->right = deleteMin( temp->right );
                h->left = temp->left;
            } else {
                h->right = deleteMax( h->right );
            }
        }
        return balance( h );
    }

    void getKeys( NodePtr h, queue< int >& q, const int& low, const int& high ) {
        if ( ! h ) return;
        if ( *( h->key ) < low ) return;
        if ( *( h->key ) > high ) return;
        getKeys( h->left, q, low, high );
        q.push( *( h->key ) );
        getKeys( h->right, q, low, high );
    }

public:

    SetInt() {
        // not implemented
    }

    virtual ~SetInt() {
        // not implemented
    }

    void put( const int& key ) {
        root = put( root, key );
        root->color = BLACK;
    }

    int size() {
        return size( root );
    }

    int height() {
        return height( root, -1 );
    }

    bool empty() {
        return size() == 0;
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + to_string( *( root->key ) ) + "\n";
        rv += toString( root );
        return rv;
    }

    int rank( const int& key ) {
        return rank( root, key );
    }

    const int* select( int k ) {
        NodePtr rv = select( root, k );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    bool contains( const int& key ) {
        return contains( root, key ) != NULL;
    }

    const int* floor( const int& key ) {
        NodePtr rv = floor( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const int* ceiling( const int& key ) {
        NodePtr rv = ceiling( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const int* min() {
        NodePtr rv = min( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const int* max() {
        NodePtr rv = max( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    void deleteMin() {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteMin( root );
        if ( ! empty() ) root->color = BLACK;
    }

    void deleteMax() {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteMax( root );
        if ( ! empty() ) root->color = BLACK;
    }

    void deleteKey( const int& key ) {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteKey( root, key );
        if ( ! empty() ) root->color = BLACK;
    }

    queue< int > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    queue< int > getKeys( const int& low, const int& high ) {
        queue< int > q;
        if ( low > high ) return q;
        getKeys( root, q, low, high );
        return q;
    }
};

const bool SetInt::RED;
const bool SetInt::BLACK;


// Implement SetDouble using RedBlackBST
class SetDouble {
private:

    static const bool RED = true;
    static const bool BLACK = false;

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const double& key, int N, bool color ) {
        return make_shared< Node >( key, N, color );
    }

    class Node {
    public:
        const double* key = NULL;
        int N = 0;
        bool color = RED;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const double& key, int N, bool color ) {
            this->key = &key;
            this->N = N;
            this->color = color;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + to_string( *key ) + " ; size : " + to_string( N ) + " ; color : " + to_string( color );
            if ( left ) {
                rv += " ; left : " + to_string( *( left->key ) );
            } else {
                rv += " ; left : null";
            }

            if ( right ) {
                rv += " ; right : " + to_string( *( right->key ) );
            } else {
                rv += " ; right : null";
            }

            rv += " | \n";
            return rv;
        }
    };

    NodePtr root = NULL;

    bool isRed( NodePtr h ) {
        if ( ! h ) return false;
        return h->color == RED;
    }

    NodePtr rotateLeft( NodePtr h ) {
        NodePtr x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        return x;
    }

    NodePtr rotateRight( NodePtr h ) {
        NodePtr x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = size( h->left ) + size( h->right ) + 1;
        return x;
    }

    void flipColors( NodePtr h ) {
        h->color = ! h->color;
        h->left->color = ! h->left->color;
        h->right->color = ! h->right->color;
    }

    NodePtr balance( NodePtr h ) {
        if ( isRed( h->right ) ) h = rotateLeft( h );
        if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
        if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );

        h->N = size( h->left ) + size( h->right ) + 1;
        return h;
    }

    NodePtr moveRedLeft( NodePtr h ) {
        flipColors( h );
        if ( isRed( h->right->left ) ) {
            h->right = rotateRight( h->right );
            h = rotateLeft( h );
            flipColors( h );
        }
        return h;
    }

    NodePtr moveRedRight( NodePtr h ) {
        flipColors( h );
        if ( isRed( h->left->left ) ) {
            h = rotateRight( h );
            flipColors( h );
        }
        return h;
    }

    NodePtr put( NodePtr h, const double& key ) {
        if ( ! h ) return newNode( key, 1, RED );
        if ( key < *( h->key ) ) {
            h->left = put( h->left, key );
        } else if ( key > *( h->key ) ) {
            h->right = put( h->right, key );
        } else {
            return h;
        }

        if ( isRed( h->right ) && ! isRed( h->left ) ) h = rotateLeft( h );
        if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
        if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );

        h->N = size( h->left ) + size( h->right ) + 1;
        return h;
    }

    int rank( NodePtr h, const double& key ) {
        if ( ! h ) return 0;
        if ( key < *( h->key ) ) {
            return rank( h->left, key );
        } else if ( key > *( h->key ) ) {
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

    int size( NodePtr h ) {
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

    int height( NodePtr h, int count ) {
        if ( ! h ) return count;
        int leftHeight = height( h->left, count + 1 );
        int rightHeight = height( h->right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    NodePtr contains( NodePtr h, const double& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return contains( h->left, key );
        } else if ( key > *( h->key ) ) {
            return contains( h->right, key );
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

    NodePtr deleteMin( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return NULL;
        if ( ! isRed( h->left ) && ! isRed( h->left->left ) ) {
            h = moveRedLeft( h );
        }
        h->left = deleteMin( h->left );
        return balance( h );
    }

    NodePtr deleteMax( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( isRed( h->left ) ) {
            h = rotateRight( h );
        }
        if ( ! h->right ) return NULL;
        if ( ! isRed( h->right ) && ! isRed( h->right->left ) ) {
            h = moveRedRight( h );
        }
        h->right = deleteMax( h->right );
        return balance( h );
    }

    NodePtr deleteKey( NodePtr h, const double& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            if ( ! h->left ) return NULL;
            if ( ! isRed( h->left ) && ! isRed( h->left->left ) ) {
                h = moveRedLeft( h );
            }
            h->left = deleteKey( h->left, key );
        } else {
            if ( isRed( h->left ) ) {
                h = rotateRight( h );
            }
            if ( key == *( h->key ) && ! h->right ) return NULL;

            if ( ! isRed( h->right ) && ! isRed( h->right->left ) ) {
                h = moveRedRight( h );
            }

            if ( key == *( h->key ) ) {
                NodePtr temp = h;
                h = min( temp->right );
                h->right = deleteMin( temp->right );
                h->left = temp->left;
            } else {
                h->right = deleteKey( h->right, key );
            }
        }
        return balance( h );
    }

    void getKeys( NodePtr h, queue< double >& q, const double& low, const double& high ) {
        if ( ! h ) return;
        if ( *( h->key ) < low ) return;
        if ( *( h->key ) > high ) return;
        getKeys( h->left, q, low, high );
        q.push( *( h->key ) );
        getKeys( h->right, q, low, high );
    }

public:

    SetDouble() {
        // not implemented
    }

    virtual ~SetDouble() {
        // not implemented
    }

    void put( const double& key ) {
        root = put( root, key );
        root->color = BLACK;
    }

    int rank( const double& key ) {
        return rank( root, key );
    }

    const double* select( int k ) {
        NodePtr rv = select( root, k );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    int size() {
        return size( root );
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + to_string( *( root->key ) ) + "\n";
        rv += toString( root );
        return rv;
    }

    int height() {
        return height( root, -1 );
    }

    bool empty() {
        return size() == 0;
    }

    bool contains( const double& key ) {
        return contains( root, key ) != NULL;
    }

    const double* min() {
        NodePtr rv = min( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const double* max() {
        NodePtr rv = max( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    void deleteMin() {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteMin( root );
        if ( ! empty() ) root->color = BLACK;
    }

    void deleteMax() {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteMax( root );
        if ( ! empty() ) root->color = BLACK;
    }

    void deleteKey( const double& key ) {
        if ( ! root ) return;
        if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
            root->color = RED;
        }
        root = deleteKey( root, key );
        if ( ! empty() ) root->color = BLACK;
    }

    queue< double > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    queue< double > getKeys( const double& low, const double& high ) {
        queue< double > q;
        if ( low > high ) return q;
        getKeys( root, q, low, high );
        return q;
    }
};

const bool SetDouble::RED;
const bool SetDouble::BLACK;

int main( int argc, char ** argv ) {

    // Test SetInt
    int keyArr[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    SetInt stInt;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( int ); ++i ) {
        stInt.put( keyArr[ i ] );
    }
    cout << "DEBUG: stInt.toString(): \n" << stInt.toString() << endl;
    cout << "DEBUG: stInt.size(): " << stInt.size() << endl;
    cout << "DEBUG: stInt.height(): " << stInt.height() << endl;
    cout << "DEBUG: stInt.contains( 30 ): " << stInt.contains( 30 ) << endl;
    cout << "DEBUG: stInt.contains( 6 ): " << stInt.contains( 6 ) << endl;
    cout << "DEBUG: stInt.select( 6 ): " << *( stInt.select( 6 ) ) << endl;
    cout << "DEBUG: stInt.min(): " << *( stInt.min() ) << endl;
    cout << "DEBUG: stInt.max(): " << *( stInt.max() ) << endl;

    stInt.deleteMin();
    cout << "DEBUG: stInt.deleteMin(): " << stInt.toString() << endl;

    stInt.deleteMax();
    cout << "DEBUG: stInt.deleteMax(): " << stInt.toString() << endl;

    stInt.deleteKey( 8 );
    cout << "DEBUG: stInt.deleteKey( 8 ): " << stInt.toString() << endl;

    queue< int > q = stInt.getKeys();
    cout << "DEBUG: stInt.getKeys(): ";
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }

    // Test SetDouble
    double keyArr1[] = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };
    SetDouble stDouble;
    for ( int i = 0; i < sizeof( keyArr1 ) / sizeof( double ); ++i ) {
        stDouble.put( keyArr1[ i ] );
    }
    cout << "DEBUG: stDouble.toString(): \n" << stDouble.toString() << endl;
    cout << "DEBUG: stDouble.size(): " << stDouble.size() << endl;
    cout << "DEBUG: stDouble.height(): " << stDouble.height() << endl;
    cout << "DEBUG: stDouble.contains( 30 ): " << stDouble.contains( 30 ) << endl;
    cout << "DEBUG: stDouble.contains( 6 ): " << stDouble.contains( 6 ) << endl;
    cout << "DEBUG: stDouble.select( 6 ): " << *( stDouble.select( 6 ) ) << endl;
    cout << "DEBUG: stDouble.min(): " << *( stDouble.min() ) << endl;
    cout << "DEBUG: stDouble.max(): " << *( stDouble.max() ) << endl;

    stDouble.deleteMin();
    cout << "DEBUG: stDouble.deleteMin(): " << stDouble.toString() << endl;

    stDouble.deleteMax();
    cout << "DEBUG: stDouble.deleteMax(): " << stDouble.toString() << endl;

    stDouble.deleteKey( 8 );
    cout << "DEBUG: stDouble.deleteKey( 8 ): " << stDouble.toString() << endl;

    queue< double > q1 = stDouble.getKeys();
    cout << "DEBUG: stDouble.getKeys(): ";
    while ( ! q1.empty() ) {
        cout << q1.front() << " ";
        q1.pop();
    }

    return 0;
}
