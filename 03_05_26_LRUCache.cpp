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
class LRUCache {
private:

    class DoubleNode;
    typedef shared_ptr< DoubleNode > DoubleNodePtr;

    static DoubleNodePtr newDoubleNode( const Item& item ) {
        return make_shared< DoubleNode >( item );
    }

    class DoubleNode {
    public:
        const Item* item = NULL;
        DoubleNodePtr prev = NULL;
        DoubleNodePtr next = NULL;

        DoubleNode( const Item& item ) {
            this->item = &item;
        }

        virtual ~DoubleNode() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const DoubleNode& h ) {
            out << " | " << *( h.item );
            if ( h.prev ) {
                out << " ; prev : " << *( h.prev->item );
            } else {
                out << " ; prev : null";
            }

            if ( h.next ) {
                out << " ; next : " << *( h.next->item );
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

    class HashNode;
    typedef shared_ptr< HashNode > HashNodePtr;

    static HashNodePtr newHashNode( DoubleNodePtr node ) {
        return make_shared< HashNode >( node );
    }

    class HashNode {
    public:
        const Item* key = NULL;
        DoubleNodePtr node;
        HashNodePtr next;

        HashNode( DoubleNodePtr node ) {
            this->key = node->item;
            this->node = node;
        }

        virtual ~HashNode() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const HashNode& h ) {
            out << " | " << *( h.node->item );
            if ( h.next ) {
                out << " ; next : " << *( h.next->node->item );
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

    class DoublyLinkedList {
    public:

        DoubleNodePtr head = NULL;
        DoubleNodePtr tail = NULL;
        int doublyN;

        DoublyLinkedList() {
            // not implemented
        }

        virtual ~DoublyLinkedList() {
            // not implemented
        }

        DoubleNodePtr deleteTail() {
            if ( ! tail ) return NULL;
            DoubleNodePtr rv = NULL;
            if ( ! tail->prev ) {
                rv = tail;
                tail = NULL;
                head = NULL;
                --doublyN;
                return rv;
            }
            rv = tail;
            tail->prev->next = NULL;
            tail = tail->prev;
            --doublyN;
            return rv;
        }

        void insertHead( const Item& item ) {
            if ( ! head ) {
                head = LRUCache::newDoubleNode( item );
                return;
            }
            DoubleNodePtr oldHead = head;
            head = LRUCache::newDoubleNode( item );
            head->next = oldHead;
            oldHead->prev = head;
            if ( ! tail ) {
                tail = oldHead;
            }
            ++doublyN;
        }

        int size() {
            return doublyN;
        }

        bool empty() {
            return size() == 0;
        }

        string toString() {
            string rv = "\n";
            DoubleNodePtr ptr = head;
            while ( ptr ) {
                rv += ptr->toString();
                ptr = ptr->next;
            }
            return rv;
        }
    };

    int hash( const Item& item ) {
        return std::hash< Item >{}( item ) % M;
    }

    int M = 0;
    int N = 0;
    vector< HashNodePtr > st;
    DoublyLinkedList dList;

public:

    LRUCache( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    LRUCache()
        : LRUCache( 17 )
    {
        // not implemented
    }

    virtual ~LRUCache() {
        // not implemented
    }

    bool contains( const Item& item ) {
        HashNodePtr ptr = st[ hash( item ) ];
        while ( ptr ) {
            if ( *( ptr->key ) == item ) {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    void access( const Item& item ) {
        if ( contains( item ) ) return;

        // Insert into dList
        dList.insertHead( item );

        // Insert dList.head into st
        HashNodePtr ptr = st[ hash( item ) ];
        if ( ptr ) {
            while ( ptr->next ) {
                ptr = ptr->next;
            }
            ptr->next = newHashNode( dList.head );
        } else {
            st[ hash( item ) ] = newHashNode( dList.head );
        }
    }

    const Item removeLeastRecentlyAccessed() {
        // Remove from dList
        DoubleNodePtr tail = dList.deleteTail();
        if ( ! tail ) return NULL;

        // Remove from st
        HashNodePtr ptr = st[ hash( *( tail->item ) ) ];
        HashNodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( *( ptr->key ) == *( tail->item ) ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    st[ hash( *( tail->item ) ) ] = NULL;
                    break;
                }
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }

        return *( tail->item );
    }

    string toString() {
        string rv = "";
        // Output dList
        rv += "\ndList:\n";
        rv += dList.toString();

        // Output vector< HashNodePtr > st
        rv += "\nst:\n";
        for ( int i = 0; i < M; ++i ) {
            HashNodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    LRUCache< string > lruCache;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        lruCache.access( keyArr[ i ] );
    }

    cout << "DEBUG: lruCache.toString(): \n" << lruCache.toString() << endl;

    lruCache.removeLeastRecentlyAccessed();
    cout << "DEBUG: lruCache.removeLeastRecentlyAccessed(): \n" << lruCache.toString() << endl;

    return 0;
}
