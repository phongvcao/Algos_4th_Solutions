//
// Created by Phong Cao on 2019-02-02.
//


#include <iostream>
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

    class Node {
    public:
        const Key * key = NULL;
        const Value * value = NULL;
        shared_ptr< Node > next = NULL;
        int N = 1;

        Node( const Key& key, const Value& value )
        {
            this->key = &key;
            this->value = &value;
        }

        virtual ~Node() {
            // not implemented
        }

        string toString() {
            string rv = " | " + *key + " : " + *value;
            if ( next ) {
                rv += " ; next : " + *( next->key );
            } else {
                rv += " ; next : NULL";
            }
            rv += " | ";
            return rv;
        }
    };

    int hashFirst( const Key& key ) {
        return 11 * ( key[ 0 ] - 'A' + 1 ) % M;
    }

    int hashSecond( const Key& key ) {
        return 17 * ( key[ 0 ] - 'A' + 1 ) % M;
    }

    int M = 17;
    int N = 0;
    vector< shared_ptr< Node > > st;
    int searchHitCount = 0;
    int searchMissCount = 0;
    int searchBeforeHitTotalCount = 0;
    int searchBeforeMissTotalCount = 0;

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
        shared_ptr< Node > ptrFirst = st[ hashFirst( key ) ];
        shared_ptr< Node > ptr1 = contains( key, ptrFirst );
        if ( ptr1 ) {
            ptr1->value = &value;
            return;
        }

        shared_ptr< Node > ptrSecond = st[ hashSecond( key ) ];
        shared_ptr< Node > ptr2 = contains( key, ptrSecond );
        if ( ptr2 ) {
            ptr2->value = &value;
            return;
        }

        shared_ptr< Node > finalPtr = chooseBestList( ptrFirst, ptrSecond );
        if ( finalPtr ) {
            while ( finalPtr->next ) {
                finalPtr = finalPtr->next;
            }
            finalPtr->next = make_shared< Node >( key, value );
        } else {
            if ( ! ptrFirst ) {
                st[ hashFirst( key ) ] = make_shared< Node >( key, value );
            } else {
                st[ hashSecond( key ) ] = make_shared< Node >( key, value );
            }
        }
        ++N;
    }

    const Value * get( const Key& key ) {
        shared_ptr< Node > ptrFirst = contains( key, st[ hashFirst( key ) ] );
        shared_ptr< Node > ptrSecond = contains( key, st[ hashSecond( key ) ] );
        if ( ptrFirst ) {
            return ptrFirst->value;
        }

        if ( ptrSecond ) {
            return ptrSecond->value;
        }
        return NULL;
    }

    int size() {
        return M;
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    shared_ptr< Node > chooseBestList( shared_ptr< Node > ptr1, shared_ptr< Node > ptr2 ) {
        if ( ! ptr1 ) {
            return ptr1;
        }

        if ( ! ptr2 ) {
            return ptr2;
        }

        return ptr1->N < ptr2->N ? ptr1 : ptr2;
    }

    shared_ptr< Node > contains( const Key& key, const shared_ptr< Node > & node ) {
        if ( node != NULL ) {
            shared_ptr< Node > ptr = node;
            while ( ptr != NULL ) {
                ++searchBeforeHitTotalCount;
                ++searchBeforeMissTotalCount;
                if ( *( ptr->key ) == key ) {
                    ++searchHitCount;
                    return ptr;
                }
                ptr = ptr->next;
            }
        }
        ++searchMissCount;
        return NULL;
    }

    void deleteKey( const Key& key ) {
        shared_ptr< Node > ptrFirst = st[ hashFirst( key ) ];
        shared_ptr< Node > beforePtrFirst = NULL;
        while ( ptrFirst ) {
            if ( *( ptrFirst->key ) == key ) {
                if ( beforePtrFirst ) {
                    beforePtrFirst->next = ptrFirst->next;
                } else {
                    st[ hashFirst( key ) ] = NULL;
                }
                --N;
                return;
            }

            beforePtrFirst = ptrFirst;
            ptrFirst = ptrFirst->next;
        }

        shared_ptr< Node > ptrSecond = st[ hashSecond( key ) ];
        shared_ptr< Node > beforePtrSecond = NULL;
        while ( ptrSecond ) {
            if ( *( ptrSecond->key ) == key ) {
                if ( beforePtrSecond ) {
                    beforePtrSecond->next = ptrSecond->next;
                } else {
                    st[ hashSecond( key ) ] = NULL;
                }
                --N;
                return;
            }

            beforePtrSecond = ptrSecond;
            ptrSecond = ptrSecond->next;
        }
    }

    queue< Key > getKeys() {
        queue< Key > queue;
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            if ( ptr ) {
                queue.push( *( ptr->key ) );
                ptr = ptr->next;
            }
        }
        return queue;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            shared_ptr< Node > ptr = st[ i ];
            while ( ptr ) {
                rv += "\n" + to_string( i ) + " : " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    int averageSearchHitProbes() {
        if ( searchHitCount > 0 ) {
            return searchBeforeHitTotalCount / searchHitCount;
        } else {
            return 0;
        }
    }

    int averageSearchMissProbes() {
        if ( searchMissCount > 0 ) {
            return searchBeforeMissTotalCount / searchMissCount;
        } else {
            return 0;
        }
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    string valueArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };
    SeparateChainingHashST< string, string > hashST( 3 );

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
        cout << " | " << keysQueue.front() << " : " << *hashST.get( keysQueue.front() ) << " | ";
        keysQueue.pop();
    }

    cout << "\nDEBUG: hashST.get( L ) : " << hashST.get( "L" ) << endl;
    cout << "\nDEBUG: averageSearchHitProbes() : " << hashST.averageSearchHitProbes() << endl;
    cout << "\nDEBUG: averageSearchMissProbes() : " << hashST.averageSearchMissProbes() << endl;

    return 0;
}
