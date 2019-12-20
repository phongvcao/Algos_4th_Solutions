//
// Created by Phong Cao on 2019-02-09.
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
#include <iterator>
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
using std::find;
using std::make_shared;
using std::shared_ptr;

template< typename Item >
class List {
private:

    class AVLTree {
    private:
        class TreeNode;
        typedef shared_ptr< TreeNode > TreeNodePtr;

        TreeNodePtr newTreeNode( int key, const Item& value, int N, int height ) {
            return make_shared< TreeNode >( key, value, N, height );
        }

        class TreeNode {
        public:
            int key = 0;
            const Item* value = NULL;
            int N = 0;
            int height = 0;
            TreeNodePtr left = NULL;
            TreeNodePtr right = NULL;

            TreeNode( int key, const Item& value, int N, int height ) {
                this->key = key;
                this->value = &value;
                this->N = N;
                this->height = height;
            }

            virtual ~TreeNode() {
                // not implemented
            }

            friend ostream& operator <<( ostream& out, const TreeNode& h ) {
                out << " | " << h.key << " : " << *( h.value ) << " ; size : " << h.N << " ; height : " << h.height;
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

        int balanceFactor( TreeNodePtr h ) {
            if ( ! h ) return 0;
            return height( h->left ) - height( h->right );
        }

        TreeNodePtr balance( TreeNodePtr h ) {
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

        TreeNodePtr rotateLeft( TreeNodePtr h ) {
            TreeNodePtr x = h->right;
            h->right = x->left;
            x->left = h;
            x->N = h->N;
            h->N = size( h->left ) + size( h->right ) + 1;
            x->height = 1 + std::max( height( x->left ), height( x->right ) );
            h->height = 1 + std::max( height( h->left ), height( h->right ) );
            return x;
        }

        TreeNodePtr rotateRight( TreeNodePtr h ) {
            TreeNodePtr x = h->left;
            h->left = x->right;
            x->right = h;
            x->N = h->N;
            h->N = size( h->left ) + size( h->right ) + 1;
            x->height = 1 + std::max( height( x->left ), height( x->right ) );
            h->height = 1 + std::max( height( h->left ), height( h->right ) );
            return x;
        }

        int size( TreeNodePtr h ) {
            if ( ! h ) return 0;
            return h->N;
        }

        string toString( TreeNodePtr h ) {
            if ( ! h ) return "";
            string rv = toString( h->left );
            rv += h->toString();
            rv += toString( h->right );
            return rv;
        }

        int height( TreeNodePtr h ) {
            if ( ! h ) return 0;
            return h->height;
        }

        TreeNodePtr put( TreeNodePtr h, int key, const Item& value ) {
            if ( ! h ) {
                return newTreeNode( key, value, 1, 0 );
            }
            if ( key < h->key ) {
                h->left = put( h->left, key, value );
            } else if ( key > h->key ) {
                h->right = put( h->right, key, value );
            } else {
                h->value = &value;
                return h;
            }

            h->N = size( h->left ) + size( h->right ) + 1;
            h->height = 1 + std::max( height( h->left ), height( h->right) );
            return balance( h );
        }

        TreeNodePtr get( TreeNodePtr h, int key ) {
            if ( ! h ) return NULL;
            if ( key < h->key ) {
                return get( h->left, key );
            } else if ( key > h->key ) {
                return get( h->right, key );
            } else {
                return h;
            }
        }

        TreeNodePtr min( TreeNodePtr h ) {
            if ( ! h ) return NULL;
            if ( ! h->left ) return h;
            return min( h->left );
        }

        TreeNodePtr max( TreeNodePtr h ) {
            if ( ! h ) return NULL;
            if ( ! h->right ) return h;
            return max( h->right );
        }

        TreeNodePtr floor( TreeNodePtr h, int key ) {
            if ( ! h ) return NULL;
            if ( key < h->key ) {
                return floor( h->left, key );
            } else if ( key == h->key ) {
                return h;
            }

            TreeNodePtr temp = floor( h->right, key );
            if ( temp ) {
                return temp;
            }
            return h;
        }

        TreeNodePtr ceiling( TreeNodePtr h, int key ) {
            if ( ! h ) return NULL;
            if ( key > h->key ) {
                return ceiling( h->right, key );
            } else if ( key == h->key ) {
                return h;
            }

            TreeNodePtr temp = ceiling( h->left, key );
            if ( temp ) {
                return temp;
            }
            return h;
        }

        TreeNodePtr deleteMin( TreeNodePtr h ) {
            if ( ! h ) return NULL;
            if ( ! h->left ) {
                return h->right;
            }
            h->left = deleteMin( h->left );
            h->N = size( h->left ) + size( h->right ) + 1;
            h->height = 1 + std::max( height( h->left ), height( h->right ) );
            return balance( h );
        }

        TreeNodePtr deleteMax( TreeNodePtr h ) {
            if ( ! h ) return NULL;
            if ( ! h->right ) {
                return h->left;
            }
            h->right = deleteMax( h->right );
            h->N = size( h->left ) + size( h->right ) + 1;
            h->height = 1 + std::max( height( h->left ), height( h->right ) );
            return balance( h );
        }

        TreeNodePtr deleteKey( TreeNodePtr h, int key ) {
            if ( ! h ) return NULL;
            if ( key < h->key ) {
                h->left = deleteKey( h->left, key );
            } else if ( key > h->key ) {
                h->right = deleteKey( h->right, key );
            } else {
                if ( ! h->left ) {
                    return h->right;
                }
                if ( ! h->right ) {
                    return h->left;
                }

                TreeNodePtr temp = h;
                h = min( temp->right );
                h->right = deleteMin( temp->right );
                h->left = temp->left;
            }
            h->N = size( h->left ) + size( h->right ) + 1;
            h->height = 1 + std::max( height( h->left ), height( h->right ) );
            return balance( h );
        }

        void getKeys( TreeNodePtr h, deque< int >& dq, int low, int high ) {
            if ( ! h ) return;
            if ( h->key < low ) return;
            if ( h->key > low ) return;
            getKeys( h->left, dq, low, high );
            dq.push_back( h->key );
            getKeys( h->right, dq, low, high );
        }

        TreeNodePtr root = NULL;

    public:

        // DEBUG
        int minKey = 0;
        int maxKey = 0;

        AVLTree() {
            // not implemented
        }

        virtual ~AVLTree() {
            // not implemented
        }

        int size() {
            return size( root );
        }

        bool empty() {
            return size() == 0;
        }

        string toString() {
            if ( ! root ) return "";
            string rv = "\nROOT : " + root->toString() + "\n";
            rv += toString( root );
            return rv;
        }

        int height() {
            return height( root );
        }

        void put( int key, const Item& value ) {
            root = put( root, key, value );
            minKey = min( root )->key;
            maxKey = max( root )->key;
        }

        const Item* get( int key ) {
            TreeNodePtr rv = get( root, key );
            if ( rv ) {
                return rv->value;
            } else {
                return NULL;
            }
        }

        bool contains( int key ) {
            return get( key ) != NULL;
        }

        const int* min() {
            TreeNodePtr rv = min( root );
            if ( rv ) {
                return &( rv->key );
            } else {
                return NULL;
            }
        }

        const int* max() {
            TreeNodePtr rv = max( root );
            if ( rv ) {
                return &( rv->key );
            } else {
                return NULL;
            }
        }

        const int* ceiling( int key ) {
            TreeNodePtr rv = ceiling( root, key );
            if ( rv ) {
                return &( rv->key );
            } else {
                return NULL;
            }
        }

        const int* floor( int key ) {
            TreeNodePtr rv = floor( root, key );
            if ( rv ) {
                return &( rv->key );
            } else {
                return NULL;
            }
        }

        void deleteMin() {
            root = deleteMin( root );
            minKey = min( root )->key;
        }

        void deleteMax() {
            root = deleteMax( root );
            maxKey = max( root )->key;
        }

        void deleteKey( int key ) {
            root = deleteKey( root, key );
            minKey = min( root )->key;
            maxKey = max( root )->key;
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

    class SeparateChainingHashST {
    private:

        class HashNode;
        typedef shared_ptr< HashNode > HashNodePtr;

        HashNodePtr newHashNode( const Item& key, int value ) {
            return make_shared< HashNode >( key, value );
        }

        class HashNode {
        public:
            const Item* key = NULL;
            int value = 0;
            HashNodePtr next = NULL;

            HashNode( const Item& key, int value ) {
                this->key = &key;
                this->value = value;
            }

            virtual ~HashNode() {
                // not implemented
            }

            friend ostream& operator <<( ostream& out, const HashNode& h ) {
                out << " | " << *( h.key ) << " : " << h.value;
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

        int M = 17;
        int N = 0;
        vector< HashNodePtr > st;

        int hash( const Item& item ) {
            return std::hash< Item >{}( item ) % M;
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
            : SeparateChainingHashST( 17 )
        {
            // not implemented
        }

        virtual ~SeparateChainingHashST() {
            // not implemented
        }

        void put( const Item& key, int value ) {
            HashNodePtr ptr = st[ hash( key ) ];
            if ( ptr ) {
                if ( key == *( ptr->key ) ) {
                    ptr->value = value;
                    return;
                }

                while ( ptr->next ) {
                    if ( key == *( ptr->key ) ) {
                        ptr->value = value;
                        return;
                    }
                    ptr = ptr->next;
                }
                ptr->next = newHashNode( key, value );
            } else {
                st[ hash( key ) ] = newHashNode( key, value );
            }
            ++N;
        }

        const int* get( const Item& key ) {
            HashNodePtr ptr = st[ hash( key ) ];
            while ( ptr ) {
                if ( *( ptr->key ) == key ) {
                    return &( ptr->value );
                }
                ptr = ptr->next;
            }
            return NULL;
        }

        bool contains( const Item& key ) {
            return get( key ) != NULL;
        }

        void deleteKey( const Item& key ) {
            if ( ! this->contains( key ) ) return;
            HashNodePtr ptr = st[ hash( key ) ];
            HashNodePtr beforePtr = NULL;

            while ( ptr ) {
                if ( key == *( ptr->key ) ) {
                    if ( beforePtr ) {
                        beforePtr->next = ptr->next;
                    } else {
                        st[ hash( key ) ] = NULL;
                    }
                    --N;
                    return;
                }
                beforePtr = ptr;
                ptr = ptr->next;
            }
        }

        int size() {
            return N;
        }

        bool empty() {
            return size() == 0;
        }

        deque< Item > getKeys() {
            deque< Item > dq;
            for ( int i = 0; i < M; ++i ) {
                HashNodePtr ptr = st[ i ];
                while ( ptr ) {
                    dq.push_back( *( ptr->key ) );
                    ptr = ptr->next;
                }
            }
            return dq;
        }

        string toString() {
            string rv = "\n";
            for ( int i = 0; i < M; ++i ) {
                HashNodePtr ptr = st[ i ];
                while ( ptr ) {
                    rv += "\n" + ptr->toString();
                    ptr = ptr->next;
                }
            }
            return rv;
        }
    };

    // avlTree contains index key, Item value
    AVLTree avlTree;

    // hashST contains Item key, (Relative) index value
    SeparateChainingHashST hashST;

public:

    List() {
        // not implemented
    }

    virtual ~List() {
        // not implemented
    }

    void addFront( Item item ) {
        // avlTree: put into minKey - 1
        // Then get minKey from avlTree
        // Then hash this Item - key pair into hashST
        avlTree.put( avlTree.minKey - 1, item );
        hashST.put( item, avlTree.minKey );
    }

    void addBack( Item item ) {
        // avlTree: put into maxKey + 1
        // Then get maxKey from avlTree
        // Then hash this Item - key pair into hashST
        avlTree.put( avlTree.maxKey + 1, item );
        hashST.put( item, avlTree.maxKey );
    }

    Item deleteFront() {
        // avlTree: get the Item that is minKey
        // avlTree.deleteMin()
        // hashST.deleteKey( Item that has minKey )
        Item item = *( avlTree.get( avlTree.minKey ) );
        avlTree.deleteMin();
        hashST.deleteKey( item );
        return item;
    }

    Item deleteBack() {
        // avlTree: get the Item that is maxKey
        // avlTree.deleteMax()
        // hashST.deleteKey( Item that has maxKey )
        Item item = *( avlTree.get( avlTree.maxKey ) );
        avlTree.deleteMax();
        hashST.deleteKey( item );
        return item;
    }

    void deleteItem( Item item ) {
        // hashST: get the key of this Item
        // avlTree.deleteKey( the key of this Item )
        // hashST.deleteKey( item )
        int key = *( hashST.get( item ) );
        avlTree.deleteKey( key );
        avlTree.deleteKey( item );
    }

    void add( int i, Item item ) {
        // avlTree.put( minKey + i, Item )
        // hashST.put( Item, minKey + i )
        const Item* existingItem = avlTree.get( avlTree.minKey + i );
        if ( existingItem != NULL ) {
            hashST.deleteKey( *existingItem );
        }
        avlTree.put( avlTree.minKey + i, item );
        hashST.put( item, avlTree.minKey + i );
    }

    Item deleteAt( int i ) {
        // Item = avlTree.get( i )
        // avlTree.deleteKey( i )
        // hashST.deleteKey( Item )
        Item item = *( avlTree.get( avlTree.minKey + i ) );
        avlTree.deleteKey( avlTree.minKey + i );
        hashST.deleteKey( item );
        return item;
    }

    bool contains( Item item ) {
        return hashST.contains( item );
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return hashST.size();
    }

    void testAVLTree() {
        AVLTree testTree;
        string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
            testTree.put( i, keyArr[ i ] );
        }

        cout << "DEBUG: testTree.toString(): \n" << testTree.toString() << endl;
        cout << "DEBUG: testTree.minKey: \n" << testTree.minKey << endl;
        cout << "DEBUG: testTree.maxKey: \n" << testTree.maxKey << endl;

        int myIdx = 9;
        while ( ! testTree.empty() ) {
            cout << "DEBUG: testTree.deleteKey( " << myIdx << " ): \n";
            testTree.deleteKey( myIdx );
            cout << "DEBUG: testTree.toString(): \n" << testTree.toString() << endl;
            cout << "DEBUG: testTree.minKey: \n" << testTree.minKey << endl;
            cout << "DEBUG: testTree.maxKey: \n" << testTree.maxKey << endl;
            --myIdx;
        }
    }

    string toString() {
        string rv = "\navlTree:\n";
        rv += avlTree.toString();
        rv += "\nhashST:\n";
        rv += hashST.toString();
        return rv;
    }
};


int main( int argc, char ** argv ) {
    string keyArr1[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string keyArr2[] = { "W", "V", "Z", "Y", "Q", "U", "T", "I", "O", "N" };
    List< string > list;
    // list.testAVLTree();

    list.addFront( keyArr1[ 0 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.addFront( keyArr1[ 1 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.addFront( keyArr1[ 2 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.addBack( keyArr1[ 3 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.addBack( keyArr1[ 4 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.addBack( keyArr1[ 5 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.add( 0, keyArr1[ 6 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.add( 0, keyArr1[ 7 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.add( 0, keyArr1[ 8 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;
    list.add( 0, keyArr1[ 9 ] );
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;

    // Expected: L P M X A E S R C H
    cout << "DEBUG: list.toString(): \n" << list.toString() << endl;

    return 0;
}
