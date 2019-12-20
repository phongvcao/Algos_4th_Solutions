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
using std::pair;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

// Implement KGramsOfString as AVLTree
class KGramsOfStringAVLTree {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const string& key, const int& value, int N, int height ) {
        return make_shared< Node >( key, value, N, height );
    }

    class Node {
    public:
        const string* key = NULL;
        const int* value = NULL;
        int N = 0;
        int height = 1;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const string& key, const int& value, int N, int height ) {
            this->key = &key;
            this->value = &value;
            this->N = N;
            this->height = height;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + *key + " : " + to_string( *value ) + " ; size : " + to_string( N ) + " ; height : " + to_string( height );
            if ( left ) {
                rv += " ; left : " + *( left->key );
            } else {
                rv += " ; left : null";
            }

            if ( right ) {
                rv += " ; right : " + *( right->key );
            } else {
                rv += " ; right : null";
            }

            rv += " | \n";
            return rv;
        }
    };

    NodePtr root = NULL;

    int balanceFactor( NodePtr h ) {
        return height( h->left ) - height( h->right );
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
            return h->height;
        }
    }

    string toString( NodePtr h ) {
        if ( ! h ) return "";
        string rv = toString( h->left );
        rv += h->toString();
        rv += toString( h->right );
        return rv;
    }

    NodePtr put( NodePtr h, const string& key, const int& value ) {
        if ( ! h ) return newNode( key, value, 1, 0 );
        if ( key < *( h->key ) ) {
            h->left = put( h->left, key, value );
        } else if ( key > *( h->key ) ) {
            h->right = put( h->right, key, value );
        } else {
            h->value = &value;
            return h;
        }

        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    int rank( NodePtr h, const string& key ) {
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

    NodePtr get( NodePtr h, const string& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return get( h->left, key );
        } else if ( key > *( h->key ) ) {
            return get( h->right, key );
        } else {
            return h;
        }
    }

    NodePtr floor( NodePtr h, const string& key ) {
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

    NodePtr ceiling( NodePtr h, const string& key ) {
        if ( ! h ) return NULL;
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
        if ( ! h->left ) return h->right;
        h->left = deleteMin( h->right );
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

    NodePtr deleteKey( NodePtr h, const string& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            h->left = deleteKey( h->left, key );
        } else if ( key > *( h->key ) ) {
            h->right = deleteKey( h->right, key );
        } else {
            NodePtr temp = h;
            h = min( temp->right );
            h->right = deleteMin( temp->right );
            h->left = temp->left;
        }
        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    void getKeys( NodePtr h, queue< string >& q, const string& low, const string& high ) {
        if ( ! h ) return;
        if ( *( h->key ) < low ) return;
        if ( *( h->key ) > high ) return;
        getKeys( h->left, q, low, high );
        q.push( *( h->key ) );
        getKeys( h->right, q, low, high );
    }

public:

    KGramsOfStringAVLTree() {
        // not implemented
    }

    virtual ~KGramsOfStringAVLTree() {
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
        string rv = "\nROOT : " + *( root->key ) + "\n";
        rv += toString( root );
        return rv;
    }

    void put( const string& key, const int& value ) {
        root = put( root, key, value );
    }

    int rank( const string& key ) {
        return rank( root, key );
    }

    const string* select( int k ) {
        NodePtr rv = select( root, k );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const int* get( const string& key ) {
        NodePtr rv = get( root, key );
        if ( rv ) {
            return rv->value;
        } else {
            return NULL;
        }
    }

    bool contains( const string& key ) {
        return get( key ) != NULL;
    }

    const string* floor( const string& key ) {
        NodePtr rv = floor( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const string* ceiling( const string& key ) {
        NodePtr rv = ceiling( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const string* min() {
        NodePtr rv = min( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const string* max() {
        NodePtr rv = max( root );
        if ( rv ) {
            return rv->key;
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

    void deleteKey( const string& key ) {
        if ( ! contains( key ) ) return;
        root = deleteKey( root, key );
    }

    queue< string > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    queue< string > getKeys( const string& low, const string& high ) {
        queue< string > q;
        if ( low > high ) return q;
        getKeys( root, q, low, high );
        return q;
    }
};

int main( int argc, char ** argv ) {

    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };

    // Test AVLTreeBST
    KGramsOfStringAVLTree bst;
    map< string, int > kGrams;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ) - 2; ++i ) {
        string key = keyArr[ i ] + " , " + keyArr[ i + 1 ] + " , " + keyArr[ i + 2 ];
        kGrams.insert( pair< string, int >( key, i ) );
    }

    for ( map< string, int >::iterator iter = kGrams.begin(); iter != kGrams.end(); ++iter ) {
        bst.put( iter->first, iter->second );
    }

    cout << "DEBUG: bst: \n" << bst.toString() << endl;

    queue< string > q = bst.getKeys();
    cout << "DEBUG: bst.getKeys(): ";
    while ( ! q.empty() ) {
        cout << q.front() << " : " << to_string( *( bst.get( q.front()) ) ) << "\n";
        q.pop();
    }
    cout << endl;

    bst.deleteKey( "P" );
    cout << "DEBUG: bst (AFTER deleteKey( P )): " << bst.toString() << endl;

    return 0;
}
