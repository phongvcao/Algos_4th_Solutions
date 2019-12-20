//
// Created by Phong Cao on 2019-02-03.
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
using std::make_shared;
using std::shared_ptr;

template< typename Key, typename Value >
class SeparateChainingHashST {
private:

    class RedBlackBST {
    private:
        static const bool RED = true;
        static const bool BLACK = false;

        class Node {
        public:
            const Key * key = NULL;
            const Value * value = NULL;
            shared_ptr< Node > left = NULL;
            shared_ptr< Node > right = NULL;
            int N = 0;
            bool color = RED;

            Node( const Key & key, const Value & value, int N, bool color ) {
                this->key = &key;
                this->value = &value;
                this->N = N;
                this->color = color;
            }

            virtual ~Node( ) {
                // not implemented
            }

            string toString() {
                string rv = " | " + *key + " : " + *value + " ; size : " + to_string( N ) + " ; color : " +
                            to_string( color );
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

        shared_ptr< Node > root = NULL;

        bool isRed( shared_ptr< Node > h ) {
            if ( ! h ) return false;
            return h->color == RED;
        }

        shared_ptr< Node > rotateLeft( shared_ptr< Node > h ) {
            shared_ptr< Node > x = h->right;
            h->right = x->left;
            x->left = h;
            x->N = h->N;
            h->N = size( h->left ) + size( h->right ) + 1;
            x->color = h->color;
            h->color = RED;
            return x;
        }

        shared_ptr< Node > rotateRight( shared_ptr< Node > h ) {
            shared_ptr< Node > x = h->left;
            h->left = x->right;
            x->right = h;
            x->N = h->N;
            h->N = size( h->left ) + size( h->right ) + 1;
            x->color = h->color;
            h->color = RED;
            return x;
        }

        void flipColors( shared_ptr< Node > h ) {
            h->color = ! h->color;
            h->left->color = ! h->left->color;
            h->right->color = ! h->right->color;
        }

        shared_ptr< Node > moveRedLeft( shared_ptr< Node > h ) {
            flipColors( h );
            if ( isRed( h->right->left ) ) {
                h->right = rotateRight( h->right );
                h = rotateLeft( h );
                flipColors( h );
            }
            return h;
        }

        shared_ptr< Node > moveRedRight( shared_ptr< Node > h ) {
            flipColors( h );
            if ( isRed( h->left->left ) ) {
                h = rotateRight( h );
                flipColors( h );
            }
            return h;
        }

        shared_ptr< Node > balance( shared_ptr< Node > h ) {
            if ( isRed( h->right ) ) h = rotateLeft( h );
            if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
            if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );

            h->N = size( h->left ) + size( h->right ) + 1;
            return h;
        }

    public:

        RedBlackBST() {
            // not implemented
        }

        virtual ~RedBlackBST() {
            // not implemented
        }

        int size() {
            return size( root );
        }

        int size( shared_ptr< Node > h ) {
            if ( ! h ) {
                return 0;
            } else {
                return h->N;
            }
        }

        bool empty() {
            return size() == 0;
        }

        int height() {
            return height( root, -1 );
        }

        int height( shared_ptr< Node > h, int count ) {
            if ( ! h ) return count;
            int leftHeight = height( h->left, count + 1 );
            int rightHeight = height( h->right, count + 1 );
            return leftHeight < rightHeight ? rightHeight : leftHeight;
        }

        string toString() {
            if ( ! root ) return "";
            string rv = "\nROOT : " + *( root->key ) + "\n";
            rv += toString( root );
            return rv;
        }

        string toString( shared_ptr< Node > h ) {
            if ( ! h ) return "";
            string rv = toString( h->left );
            rv += h->toString();
            rv += toString( h->right );
            return rv;
        }

        void put( const Key& key, const Value& value ) {
            root = put( root, key, value );
            root->color = BLACK;
        }

        shared_ptr< Node > put( shared_ptr< Node > h, const Key& key, const Value& value ) {
            if ( ! h ) return make_shared< Node >( key, value, 1, RED );
            if ( key < *( h->key ) ) {
                h->left = put( h->left, key, value );
            } else if ( key > *( h->key ) ) {
                h->right = put( h->right, key, value );
            } else {
                h->value = &value;
            }

            if ( isRed( h->right ) && ! isRed( h->left ) ) h = rotateLeft( h );
            if ( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
            if ( isRed( h->left ) && isRed( h->right ) ) flipColors( h );

            h->N = size( h->left ) + size( h->right ) + 1;
            return h;
        }

        const Key * min() {
            shared_ptr< Node > rv = min( root );
            if ( rv ) {
                return rv->key;
            } else {
                return NULL;
            }
        }

        shared_ptr< Node > min( shared_ptr< Node > h ) {
            if ( ! h ) return h;
            if ( ! h->left ) return h;
            return min( h->left );
        }

        const Key * max() {
            shared_ptr< Node > rv = max( root );
            if ( rv ) {
                return rv->key;
            } else {
                return NULL;
            }
        }

        shared_ptr< Node > max( shared_ptr< Node > h) {
            if ( ! h ) return h;
            if ( ! h->right ) return h;
            return max( h->right );
        }

        const Value * get( const Key& key ) {
            shared_ptr< Node > rv = get( root, key );
            if ( rv ) {
                return rv->value;
            } else {
                return NULL;
            }
        }

        shared_ptr< Node > get( shared_ptr< Node > h, const Key& key ) {
            if ( ! h ) return h;
            if ( h == NULL ) return h;

            if ( key < *( h->key ) ) {
                return get( h->left, key );
            } else if ( key > *( h->key ) ) {
                return get( h->right, key );
            } else {
                return h;
            }
        }

        bool contains( const Key& key ) {
            const Value * rv = get( key );
            return rv != NULL;
        }

        const Key& floor( const Key& key ) {
            return *( floor( root, key )->key );
        }

        shared_ptr< Node > floor( shared_ptr< Node > h, const Key& key ) {
            if ( ! h ) return h;
            if ( key < *( h->key ) ) {
                return floor( h->left, key );
            } else if ( key == *( h->key ) ) {
                return h;
            }

            shared_ptr< Node > temp = floor( h->right, key );
            if ( temp ) {
                return temp;
            }
            return h;
        }

        const Key& ceiling( const Key& key ) {
            return *( ceiling( root, key )->key );
        }

        shared_ptr< Node > ceiling( shared_ptr< Node > h, const Key& key ) {
            if ( ! h ) return h;
            if ( key > *( h->key ) ) {
                return ceiling( h->right, key );
            } else if ( key == *( h->key ) ) {
                return h;
            }

            shared_ptr< Node > temp = ceiling( h->left, key );
            if ( temp ) {
                return temp;
            }
            return h;
        }

        void deleteMin() {
            if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
                root->color = RED;
            }
            root = deleteMin( root );
            if ( ! empty() ) root->color = BLACK;
        }

        shared_ptr< Node > deleteMin( shared_ptr< Node > h ) {
            if ( ! h->left ) return NULL;
            if ( ! isRed( h->left ) && ! isRed( h->left->left ) ) {
                h = moveRedLeft( h );
            }
            h->left = deleteMin( h->left );
            return balance( h );
        }

        void deleteMax() {
            if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
                root->color = RED;
            }
            root = deleteMax( root );
            if ( ! empty() ) root->color = BLACK;
        }

        shared_ptr< Node > deleteMax( shared_ptr< Node > h ) {
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

        void deleteKey( const Key& key ) {
            if ( ! contains( key ) ) return;
            if ( ! isRed( root->left ) && ! isRed( root->right ) ) {
                root->color = RED;
            }
            root = deleteKey( root, key );
            if ( ! empty() ) root->color = BLACK;
        }

        shared_ptr< Node > deleteKey( shared_ptr< Node > h, const Key& key ) {
            if ( ! h ) return h;
            if ( key < *( h->key ) ) {
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
                    shared_ptr< Node > x = h;
                    h = min( x->right );
                    h->right = deleteMin( x->right );
                    h->left = x->left;
                } else {
                    h->right = deleteKey( h->right, key );
                }
            }

            return balance( h );
        }

        int rank( const Key& key ) {
            return rank( root, key );
        }

        int rank( shared_ptr< Node > h, const Key& key ) {
            if ( ! h ) return 0;
            if ( key < *( h->key ) ) {
                return rank( h->left, key );
            } else if ( key > *( h->key ) ) {
                return rank( h->right, key ) + 1 + size( h->left );
            } else {
                return size( h->left );
            }
        }

        const Key* select( int k ) {
            shared_ptr< Node > rv = select( root, k );
            if ( rv ) {
                return rv->key;
            } else {
                return NULL;
            }
        }

        shared_ptr< Node > select( shared_ptr< Node > h, int k ) {
            if ( ! h ) return NULL;
            int s = size( h->left );
            if ( k < s ) {
                return select( h->left, k );
            } else if ( k > s ) {
                return select( h->right, k - 1 - s );
            } else {
                return h;
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

        void getKeys( shared_ptr< Node > h, queue< Key >& q, const Key& low, const Key& high ) {
            if ( ! h ) return;
            if ( *( h->key ) < low ) return;
            if ( *( h->key ) > high ) return;
            getKeys( h->left, q, low, high );
            q.push( *( h->key ) );
            getKeys( h->right, q, low, high );
        }
    };

    int M = 17;
    int N = 0;
    vector< shared_ptr< RedBlackBST > > st;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

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
        : SeparateChainingHashST( 997 )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        shared_ptr< RedBlackBST > ptr = st[ hash( key ) ];
        if ( ! ptr ) {
            st[ hash( key ) ] = make_shared< RedBlackBST >();
            ptr = st[ hash( key ) ];
        }
        N -= ptr->size();
        ptr->put( key, value );
        N += ptr->size();
    }

    const Value * get( const Key& key ) {
        shared_ptr< RedBlackBST > ptr = st[ hash( key ) ];
        if ( ! ptr ) {
            st[ hash( key ) ] = make_shared< RedBlackBST >();
            ptr = st[ hash( key ) ];
        }
        return ptr->get( key );
    }

    void deleteKey( const Key& key ) {
        shared_ptr< RedBlackBST > ptr = st[ hash( key ) ];
        if ( ptr ) {
            N -= ptr->size();
            ptr->deleteKey( key );
            N += ptr->size();
        }
    }

    int size() {
        return M;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< RedBlackBST > ptr = st[ i ];
            if ( ptr ) {
                rv += ptr->toString();
            }
        }
        return rv;
    }

    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< RedBlackBST > ptr = st[ i ];
            if ( ptr && ! ptr->empty() ) {
                queue< Key > temp = ptr->getKeys();
                while ( ! temp.empty() ) {
                    q.push( temp.front() );
                    temp.pop();
                }
            }
        }
        return q;
    }

    void testRedBlackBST( const vector< Key >& keyVec, const vector< Value >& valueVec ) {
        RedBlackBST bst;
        for ( int i = 0; i < keyVec.size(); ++i ) {
            bst.put( keyVec[ i ], valueVec[ i ] );
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
        queue< Key > q = bst.getKeys();
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

        bst.deleteKey( "E" );
        cout << "DEBUG: bst.delete( E ): " << bst.toString() << endl;

        cout << "DEBUG: bst.rank( S ): " << bst.rank( "S" ) << endl;
        cout << "DEBUG: bst.select( 5 ): " << *( bst.select( 5 ) ) << endl;
    }
};

template< typename Key, typename Value >
const bool SeparateChainingHashST< Key, Value >::RedBlackBST::RED;

template< typename Key, typename Value >
const bool SeparateChainingHashST< Key, Value >::RedBlackBST::BLACK;

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    vector< string > keyVec;
    vector< string > valueVec;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        keyVec.push_back( keyArr[ i ] );
        valueVec.push_back( valueArr[ i ] );
    }

    SeparateChainingHashST< string, string > hashST( 997 );

    // Test RedBlackBST
    // hashST.testRedBlackBST( keyVec, valueVec );

    // Test SeparateChainingHashST
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        hashST.put( keyArr[ i ], valueArr[ i ] );
    }

    cout << hashST.toString() << endl;

    queue< string > keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << keysQueue.front() << " ";
        keysQueue.pop();
    }

    hashST.deleteKey( "L" );
    cout << "\nDEBUG: hashST (AFTER delete( L )) :\n" << hashST.toString() << endl;

    hashST.deleteKey( "E" );
    cout << "\nDEBUG: hashST (AFTER delete( E )) :\n" << hashST.toString() << endl;

    keysQueue = hashST.getKeys();
    while ( ! keysQueue.empty() ) {
        cout << " | " << keysQueue.front() << " : " << *( hashST.get( keysQueue.front() ) ) << " | ";
        keysQueue.pop();
    }

    cout << "\nDEBUG: hashST.contains( L ) : " << hashST.contains( "L" ) << endl;

    return 0;
}
