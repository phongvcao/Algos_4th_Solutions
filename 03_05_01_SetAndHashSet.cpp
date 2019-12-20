//
// Created by Phong Cao on 2019-02-04.
//

#include <iostream>
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

// Implement Set as AVL Tree
template< typename Key, typename Value >
class AVLTreeBST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value, int N, int height ) {
        return make_shared< Node >( key, value, N, height );
    }

    class Node {
    public:
        const Key* key = NULL;
        const Value* value = NULL;
        NodePtr left = NULL;
        NodePtr right = NULL;
        int N = 0;
        int height = 0;

        Node( const Key& key, const Value& value, int N, int height ) {
            this->key = &key;
            this->value = &value;
            this->N = N;
            this->height = height;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + *key + " : " + *value + " ; size : " + to_string( N ) + " ; height : " + to_string( height );
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

    int height( NodePtr h ) {
        if ( ! h ) {
            return 0;
        } else {
            return h->height;
        }
    }

    int balanceFactor( NodePtr h ) {
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

    NodePtr put( NodePtr h, const Key& key, const Value& value ) {
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
        return balance( h );
    }

    NodePtr deleteMax( NodePtr h ) {
        if ( ! h ) return NULL;
        if ( ! h->right ) return h->left;
        h->right = deleteMax( h->right );
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
            h->left = temp->left;
        }
        return balance( h );
    }

    queue< Key > getKeys( const Key& low, const Key& high ) {
        queue< Key > q;
        if ( low > high ) return q;
        getKeys( root, q, low, high );
        return q;
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

    AVLTreeBST() {
        // not implemented
    }

    virtual ~AVLTreeBST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        root = put( root, key, value );
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
        string rv = "\nROOT : " + *( root->key ) + "\n";
        rv += toString( root );
        return rv;
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

    void deleteMin() {
        root = deleteMin( root );
    }

    void deleteMax() {
        root = deleteMax( root );
    }

    void deleteKey( const Key& key ) {
        root = deleteKey( root, key );
    }

    const Key * floor( const Key& key ) {
        NodePtr rv = floor( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    const Key * ceiling( const Key& key ) {
        NodePtr rv = ceiling( root, key );
        if ( rv ) {
            return rv->key;
        } else {
            return NULL;
        }
    }

    queue< Key > getKeys() {
        return getKeys( *( min() ), *( max() ) );
    }
};

// Implement HashSet as LinearProbingHashST
template< typename Key, typename Value >
class LinearProbingHashST {
private:

    vector< const Key* > keys;
    vector< const Value* > values;
    int M = 17;
    int N = 0;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:

    LinearProbingHashST( int M )
        : M( M )
    {
        keys.resize( M );
        values.resize( M );
        for ( int i = 0; i < M; ++i ) {
            keys[ i ] = NULL;
            values[ i ] = NULL;
        }
    }

    LinearProbingHashST()
        : LinearProbingHashST( 997 )
    {
        // not implemented
    }

    virtual ~LinearProbingHashST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        if ( N > M / 2 ) resize( 2 * M );
        int i;
        for ( i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( *keys[ i ] == key ) {
                values[ i ] = &value;
                return;
            }
        }
        keys[ i ] = &key;
        values[ i ] = &value;
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        int i = hash( key );
        while ( *( keys[ i ] ) != key ) {
            i = ( i + 1 ) % M;
        }
        keys[ i ] = NULL;
        values[ i ] = NULL;
        i = ( i + 1 ) % M;
        while ( keys[ i ] != NULL ) {
            const Key* keyToRedo = keys[ i ];
            const Value* valueToRedo = values[ i ];
            --N;
            put( *keyToRedo, *valueToRedo );
            i = ( i + 1 ) % M;
        }
        --N;
        if ( N > 0 && N < M / 8 ) resize( M / 2 );
    }

    const Value* get( const Key& key ) {
        for ( int i = hash( key ); keys[ i ] != NULL; i = ( i + 1 ) % M ) {
            if ( key == *( keys[ i ] ) ) {
                return values[ i ];
            }
        }
        return NULL;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    void resize( int cap ) {
        LinearProbingHashST temp( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                temp.put( *keys[ i ], *values[ i ] );
            }
        }
        this->keys = temp.keys;
        this->values = temp.values;
        this->M = temp.M;
    }

    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                q.push( *( keys[ i ] ) );
            }
        }
        return q;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != NULL ) {
                rv += "\n i : " + to_string( i ) + " : | " + *keys[ i ] + " : " + *values[ i ] + " | ";
            }
        }
        return rv;
    }
};

// Implement Set using AVLTreeBST
template< typename Key >
class Set {
private:
    AVLTreeBST< Key, string > bst;

public:

    Set() {
        // not implemented
    }

    virtual ~Set() {
        // not implemented
    }

    void add( const Key& key ) {
        bst.put( key, "0" );
    }

    void deleteKey( const Key& key ) {
        bst.deleteKey( key );
    }

    bool contains( const Key& key ) {
        return bst.contains( key );
    }

    bool empty() {
        return bst.empty();
    }

    int size() {
        return bst.size();
    }

    string toString() {
        string rv = "\n";
        queue< Key > q = bst.getKeys();
        while ( ! q.empty() ) {
            rv += " " + q.front();
            q.pop();
        }
        rv += "\n";
        return rv;
    }
};

// Implement HashSet using LinearProbingHashST
template< typename Key >
class HashSet {
private:
    LinearProbingHashST< Key, string > hashST;

public:

    HashSet( int M )
        : hashST( M )
    {
        // not implemented
    }

    HashSet()
        : HashSet( 997 )
    {
        // not implemented
    }

    virtual ~HashSet() {
        // not implemented
    }

    void add( const Key& key ) {
        hashST.put( key, "0" );
    }

    void deleteKey( const Key& key ) {
        hashST.deleteKey( key );
    }

    bool contains( const Key& key ) {
        return hashST.contains( key );
    }

    bool empty() {
        return hashST.empty();
    }

    int size() {
        return hashST.size();
    }

    string toString() {
        string rv = "\n";
        queue< Key > q = hashST.getKeys();
        while ( ! q.empty() ) {
            rv += " " + q.front();
            q.pop();
        }
        rv += "\n";
        return rv;
    }
};


int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };

    // Test AVLTreeBST
    AVLTreeBST< string, string > bst;
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

    bst.deleteKey( "P" );
    cout << "DEBUG: bst (AFTER deleteKey( P )): " << bst.toString() << endl;

    // Test LinearProbingHashST
    LinearProbingHashST< string, string > hashST( 17 );
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }
    cout << "DEBUG: hashST: \n" << hashST.toString() << endl;
    cout << "DEBUG: hashST.get( L ): " << *( hashST.get( "L" ) ) << endl;

    q = hashST.getKeys();
    cout << "DEBUG: hashST.getKeys(): ";
    while ( ! q.empty() ) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    hashST.deleteKey( "L" );
    cout << "DEBUG: hashST: (AFTER deleteKey( L )): \n" << hashST.toString() << endl;

    // Test Set
    Set< string > set;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        set.add( keyArr[ i ] );
    }

    cout << "DEBUG: set: \n" << set.toString() << endl;
    cout << "DEBUG: set.contains( L ): " << set.contains( "L" ) << endl;
    set.deleteKey( "L" );
    cout << "DEBUG: set (AFTER deleteKey( L )): \n" << set.toString() << endl;
    cout << "DEBUG: set.contains( L ): " << set.contains( "L" ) << endl;

    // Test HashSet
    HashSet< string > hashSet;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashSet.add( keyArr[ i ] );
    }

    cout << "DEBUG: hashSet: \n" << hashSet.toString() << endl;
    cout << "DEBUG: hashSet.contains( L ): " << hashSet.contains( "L" ) << endl;
    hashSet.deleteKey( "L" );
    cout << "DEBUG: hashSet (AFTER deleteKey( L )): \n" << hashSet.toString() << endl;
    cout << "DEBUG: hashSet.contains( L ): " << hashSet.contains( "L" ) << endl;

    return 0;
}
