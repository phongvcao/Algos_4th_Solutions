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

template< typename Key, typename Value >
class RedBlackBST {
private:

    static const bool RED = true;
    static const bool BLACK = false;

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value, int N, bool color ) {
        return make_shared< Node >( key, value, N, color );
    }

    class Node {
    public:
        const Key* key = NULL;
        const Value* value = NULL;
        int N = 0;
        bool color = RED;
        NodePtr left = NULL;
        NodePtr right = NULL;

        Node( const Key& key, const Value& value, int N, bool color ) {
            this->key = &key;
            this->value = &value;
            this->N = N;
            this->color = color;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key ) << " : " << *( h.value ) << " ; size : " << h.N << " ; color : " << h.color;
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
            return out;
        }
    };

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

    NodePtr put( NodePtr h, const Key& key, const Value& value ) {
        if ( ! h ) return newNode( key, value, 1, RED );
        if ( key <= *( h->key ) ) {
            h->left = put( h->left, key, value );
        } else {
            h->right = put( h->right, key, value );
        }

        if ( isRed( h->right ) && ! isRed( h->left ) ) h = rotateLeft( h );
        if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
        if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );
        h->N = size( h->left ) + size( h->right ) + 1;
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

    NodePtr deleteKey( NodePtr h, const Key& key ) {
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

            if ( ! isRed( h->right ) && ! isRed( h->right->left) ) {
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

    void getKeys( NodePtr h, queue< Key >& q, const Key& low, const Key& high ) {
        if ( ! h ) return;
        if ( *( h->key ) < low ) return;
        if ( *( h->key ) > high ) return;
        getKeys( h->left, q, low, high );
        q.push( *( h->key ) );
        getKeys( h->right, q, low, high );
    }

    NodePtr root = NULL;

public:

    RedBlackBST() {
        // not implemented
    }

    virtual ~RedBlackBST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        root = put( root, key, value );
        root->color = BLACK;
    }

    int size() {
        return size( root );
    }

    bool empty() {
        return size() == 0;
    }

    int height() {
        return height( root, -1 );
    }

    string toString() {
        if ( ! root ) return "";
        string rv = "\nROOT : " + root->toString() + "\n";
        rv += toString( root );
        return rv;
    }

    const Value* get( const Key& key ) {
        NodePtr rv = get( root, key );
        if ( rv ) {
            return rv->value;
        } else {
            return NULL;
        }
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
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
        if ( ! root ) return;
        if ( ! isRed( root->left) && ! isRed( root->right ) ) {
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

    void deleteKey( const Key& key ) {
        if ( ! root ) return;
        if ( ! contains( key ) ) return;

        while ( contains( key ) ) {
            if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
                root->color = RED;
            }
            root = deleteKey( root, key );
            if ( ! empty() ) root->color = BLACK;
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

template< typename Key, typename Value >
const bool RedBlackBST< Key, Value >::RED;

template< typename Key, typename Value >
const bool RedBlackBST< Key, Value >::BLACK;

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };

    RedBlackBST< string, string > bst;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        bst.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << "DEBUG: bst: " << endl;
    cout << bst.toString() << endl;

    cout << "DEUBG: bst.size(): ";
    cout << bst.size() << endl;

    cout << "DEBUG: bst.height(): ";
    cout << bst.height() << endl;

    cout << "DEBUG: bst.min(): ";
    cout << *( bst.min() ) << endl;

    cout << "DEBUG: bst.max(): ";
    cout << *( bst.max() ) << endl;

    cout << "DEBUG: bst.get( L ): ";
    cout << bst.get( "L" ) << endl;

    cout << "DEBUG: bst.floor( C ): ";
    cout << bst.floor( "C" ) << endl;

    cout << "DEBUG: bst.ceiling( C ): ";
    cout << bst.ceiling( "C" ) << endl;

    cout << "DEBUG: bst.getKeys(): ";
    queue< string > q = bst.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    bst.deleteMin();
    cout << "DEBUG: bst.getKeys() (AFTER deleteMin()): ";
    q = bst.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    bst.deleteMax();
    cout << "DEBUG: bst.getKeys() (AFTER deleteMax()): ";
    q = bst.getKeys();
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    cout << "DEBUG: bst.floor( C ): " << bst.floor( "C" ) << endl;
    cout << "DEBUG: bst.floor( D ): " << bst.floor( "D" ) << endl;

    cout << "DEBUG: bst.contains( C ): " << bst.contains( "C" ) << endl;
    cout << "DEBUG: bst.contains( D ): " << bst.contains( "D" ) << endl;

    bst.deleteKey( "L" );
    cout << "DEBUG: bst.delete( L ): " << bst.toString() << endl;

    cout << "DEBUG: bst.rank( S ): " << bst.rank( "S" ) << endl;
    cout << "DEBUG: bst.select( 5 ): " << *( bst.select( 5 ) ) << endl;

    return 0;
}
