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

// Implement BST using AVLTree
template< typename Key, typename Value >
class BST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value, int N, int height ) {
        return make_shared< Node >( key, value, N, height );
    }

    class Node {
    public:
        const Key* key = NULL;
        vector< const Value* > values;
        int N = 0;
        int height = 0;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const Key& key, const Value& value, int N, int height ) {
            this->key = &key;
            this->values.resize( 1 );
            this->values[ 0 ] = &value;
            this->N = N;
            this->height = height;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            for ( int i = 0; i < h.values.size(); ++i ) {
                out << " | " << *( h.key ) << " : " << *( h.values[ i ] ) << " ; size " << h.N << " ; height : " << h.height;
                if ( h.left ) {
                    out << " ; left : " << *( h.left->key );
                } else {
                    out << " ; left : null";
                }

                if ( h.right ) {
                    out << " ; right : " << *( h.right->key );
                } else {
                    out << " ; right : null";
                }
                out << " | \n";
            }
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

    NodePtr put( NodePtr h, const Key& key, const Value& value ) {
        if ( ! h ) return newNode( key, value, 1, 0 );
        if ( key < *( h->key ) ) {
            h->left = put( h->left, key, value );
        } else if ( key > *( h->key ) ) {
            h->right = put( h->right, key, value );
        } else {
            h->values.push_back( &value );
            return h;
        }

        h->N = size( h->left ) + size( h->right ) + 1;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    int rank( NodePtr h, const Key& key ) {
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

    NodePtr get( NodePtr h, const Key& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return get( h->left, key );
        } else if ( key > *( h->key ) ) {
            return get( h->right, key );
        } else {
            return h;
        }
    }

    NodePtr floor( NodePtr h, const Key& key ) {
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

    NodePtr ceiling( NodePtr h, const Key& key ) {
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

    NodePtr deleteMin( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return h->right;
        h->left = deleteMin( h->left );
        h->N = 1 + size( h->left ) + size( h->right );
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr deleteMax( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->right ) return h->left;
        h->right = deleteMax( h->right );
        h->N = 1 + size( h->left ) + size( h->right );
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr deleteKey( NodePtr h, const Key& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            h->left = deleteKey( h->left, key );
        } else if ( key > *( h->key ) ) {
            h->right = deleteKey( h->right, key );
        } else {
            if ( ! h->left ) return h->right;
            if ( ! h->right ) return h->left;

            NodePtr temp = h;
            h = min( temp->right );
            h->right = deleteMin( temp->right );
            h->left = h->left;
        }
        h->N = 1 + size( h->left ) + size( h->right );
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    void getKeys( NodePtr h, queue< Key >& q, const Key& low, const Key& high ) {
        if ( ! h ) return;
        if ( *( h->key ) < low ) return;
        if ( *( h->key ) > high ) return;
        getKeys( h->left, q, low, high );
        q.push( *( h->key ) );
        getKeys( h->right, q, low, high );
    }


public:

    BST() {
        // not implemented
    }

    virtual ~BST() {
        // not implemented
    }

    int size() {
        return size( root );
    }

    int height() {
        return height( root );
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + root->toString() + "\n";
        rv += toString( root );
        return rv;
    }

    bool empty() {
        return size() == 0;
    }

    void put( const Key& key, const Value& value ) {
        root = put( root, key, value );
    }

    int rank( const Key& key ) {
        return rank( root, key );
    }

    const Key* select( int k ) {
        NodePtr rv = select( root, k );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const Key* min() {
        NodePtr rv = min( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const Key* max() {
        NodePtr rv = max( root );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const Value* get( const Key& key ) {
        NodePtr rv = get( root, key );
        if ( rv ) {
            return rv->values[ 0 ];
        } else {
            return NULL;
        }
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    const Key* floor( const Key& key ) {
        NodePtr rv = floor( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const Key* ceiling( const Key& key ) {
        NodePtr rv = ceiling( root, key );
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

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        while ( contains( key ) ) {
            root = deleteKey( root, key );
        }
    }

    queue< Key > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }

    queue< Key > getKeys( const Key& low, const Key& high ) {
        queue< Key > q;
        if ( low > high ) return q;
        getKeys( root, q, low, high );
        return q;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };

    // Test BST
    BST< string, string > bst;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        bst.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << "DEBUG: bst: \n" << bst.toString() << endl;
    cout << "DEBUG: bst.get( L ): " << *( bst.get( "L" ) ) << endl;
    cout << "DEBUG: bst.rank( E ): " << bst.rank( "E" ) << endl;
    cout << "DEBUG: bst.select( E ): " << *( bst.select( 4 ) ) << endl;
    cout << "DEBUG: bst.min(): " << *( bst.min() ) << endl;
    cout << "DEBUG: bst.max(): " << *( bst.max() ) << endl;
    cout << "DEBUG: bst.floor( C ): " << *( bst.floor( "C" ) ) << endl;
    cout << "DEBUG: bst.floor( D ): " << *( bst.floor( "D" ) ) << endl;
    cout << "DEBUG: bst.ceiling( C ): " << *( bst.ceiling( "C" ) ) << endl;
    cout << "DEBUG: bst.ceiling( D ): " << *( bst.ceiling( "D" ) ) << endl;

    bst.deleteMin();
    cout << "DEBUG: bst (AFTER deleteMin()): " << bst.toString() << endl;

    bst.deleteMax();
    cout << "DEBUG: bst (AFTER deleteMax()): " << bst.toString() << endl;

    queue< string > q = bst.getKeys();
    cout << "DEBUG: bst.getKeys(): ";
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    bst.deleteKey( "L" );
    cout << "DEBUG: bst (AFTER deleteKey( L )): " << bst.toString() << endl;

    return 0;
}
