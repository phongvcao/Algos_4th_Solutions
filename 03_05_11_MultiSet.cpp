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

// Implement MultiSet using AVLTree
template< typename Key >
class MultiSet {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, int N, int height ) {
        return make_shared< Node >( key, N, height );
    }

    class Node {
    public:
        const Key* key = NULL;
        int N = 0;
        int height = 0;
        int count = 1;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const Key& key, int N, int height ) {
            this->key = &key;
            this->N = N;
            this->height = height;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            for ( int i = 0; i < h.count; ++i ) {
                out << " | " << *( h.key ) << " ; size : " << h.N << " ; height : " << h.height;
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

    int height( NodePtr h ) {
        if ( ! h ) {
            return 0;
        } else {
            return h->height;
        }
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

    NodePtr add( NodePtr h, const Key& key ) {
        if ( ! h ) return newNode( key, 1, 0 );
        if ( key < *( h->key ) ) {
            h->left = add( h->left, key );
        } else if ( key > *( h->key ) ) {
            h->right = add( h->right, key );
        } else {
            h->count = h->count + 1;
            return h;
        }

        h->N = size( h->left ) + size( h->right ) + h->count;
        h->height = 1 + std::max( height( h->left ), height( h->right ) );
        return balance( h );
    }

    NodePtr deleteMin( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return h->right;
        h->left = deleteMin( h->left );
        h->N = size( h->left ) + size( h->right ) + h->count;
        return balance( h );
    }

    NodePtr min( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->left ) return h;
        return min( h->left );
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
            h->left = temp->left;
        }
        return balance( h );
    }

    NodePtr contains( NodePtr h, const Key& key ) {
        if ( ! h ) return NULL;
        if ( key < *( h->key ) ) {
            return contains( h->left, key );
        } else if ( key > *( h->key ) ) {
            return contains( h->right, key );
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

public:

    MultiSet() {
        // not implemented
    }

    virtual ~MultiSet() {
        // not implemented
    }

    void add( const Key& key ) {
        root = add( root, key );
    }

    void deleteKey( const Key& key ) {
        root = deleteKey( root, key );
    }

    bool contains( const Key& key ) {
        return contains( root, key ) != NULL;
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return size( root );
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + root->toString() + "\n";
        rv += toString( root );
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    MultiSet< string > set;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        set.add( keyArr[ i ] );
    }

    cout << "DEBUG: set: \n" << set.toString() << endl;

    set.deleteKey( "L" );
    cout << "DEBUG: set (AFTER deleteKey( L )): \n" << set.toString() << endl;

    return 0;
}
