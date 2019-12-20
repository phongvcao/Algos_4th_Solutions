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
class UniQueue {
private:

    // Implement SeparateChainingHashST for Item
    // to keep track of what was inserted & what not
    class HashSet {
    private:

        class HashNode;
        typedef shared_ptr< HashNode > HashNodePtr;

        HashNodePtr newHashNode( const Item& item ) {
            return make_shared< HashNode >( item );
        }

        class HashNode {
        public:
            const Item* key = NULL;
            HashNodePtr next = NULL;

            HashNode( const Item& key ) {
                this->key = &key;
            }

            virtual ~HashNode() {
                // not implemented
            }

            friend ostream& operator <<( ostream& out, const HashNode& h ) {
                out << " | " << *( h.key );
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

        int hash( const Item& key ) {
            return std::hash< Item >{}( key ) % M;
        }

        int M = 17;
        int N = 0;
        vector< HashNodePtr > st;

    public:

        HashSet( int M )
            : M( M )
        {
            st.resize( M );
            for ( int i = 0; i < M; ++i ) {
                st[ i ] = NULL;
            }
        }

        HashSet()
            : HashSet( 17 )
        {
            // not implemented
        }

        virtual ~HashSet() {
            // not implemented
        }

        void put( const Item& item ) {
            HashNodePtr ptr = st[ hash( item ) ];
            if ( ptr ) {
                if ( item == *( ptr->key ) ) {
                    return;
                }
                while ( ptr->next ) {
                    if ( item == *( ptr->key ) ) {
                        return;
                    }
                    ptr = ptr->next;
                }
                ptr->next = newHashNode( item );
            } else {
                st[ hash( item ) ] = newHashNode( item );
            }
            ++N;
        }

        void deleteKey( const Item& item ) {
            HashNodePtr ptr = st[ hash( item ) ];
            HashNodePtr beforePtr = NULL;
            while ( ptr ) {
                if ( item == *( ptr->key ) ) {
                    if ( beforePtr ) {
                        beforePtr->next = ptr->next;
                    } else {
                        st[ hash( item ) ] = NULL;
                    }
                    --N;
                }

                beforePtr = ptr;
                ptr = ptr->next;
            }
        }

        bool contains( const Item& item ) {
            HashNodePtr ptr = st[ hash( item ) ];
            while ( ptr ) {
                if ( item == *( ptr->key ) ) {
                    return true;
                }
                ptr = ptr->next;
            }
            return false;
        }

        int size() {
            return N;
        }

        bool empty() {
            return size() == 0;
        }

        string toString() {
            string rv = "\n";
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

    // Implement DoubleNode to represent UniQueue as doubly-linked list underneath
    // to easily enqueue() & dequeue()
    class DoubleNode;
    typedef shared_ptr< DoubleNode > DoubleNodePtr;

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

    DoubleNodePtr newDoubleNode( const Item& item ) {
        return make_shared< DoubleNode >( item );
    }

    DoubleNodePtr head = NULL;
    DoubleNodePtr tail = NULL;

    void insertToTail( const Item& item ) {
        if ( head == NULL ) {
            head = newDoubleNode( item );
            tail = head;
            return;
        }

        tail->next = newDoubleNode( item );
        tail->next->prev = tail;
        tail = tail->next;
    }

    DoubleNodePtr removeFromHead() {
        if ( head == NULL ) return NULL;
        if ( ! head->next ) {
            tail = NULL;
        }
        DoubleNodePtr rv = head;
        head = head->next;
        head->prev = NULL;
        return head;
    }

    HashSet hashSet;

public:

    UniQueue() {
        // not implemented
    }

    virtual ~UniQueue() {
        // not implemented
    }

    void enqueue( const Item& item ) {
        // Check whether item is already in hashSet
        // If it is, return
        if ( hashSet.contains( item ) ) return;

        // Insert item into hashSet
        hashSet.put( item );

        // Insert into tail of linked list
        insertToTail( item );
    }

    Item dequeue() {
        if ( empty() ) return NULL;

        // Remove from head
        DoubleNodePtr rv = removeFromHead();
        if ( rv ) {
            hashSet.deleteKey( *( rv->item ) );
        }
        return *( rv->item );
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return hashSet.size();
    }

    string toString() {
        // print out doubly linked list
        string rv = "\nlinkedList:\n";
        DoubleNodePtr ptr = head;
        while ( ptr ) {
            rv += ptr->toString();
            ptr = ptr->next;
        }

        // print out hashSet
        rv += "\nhashSet:\n";
        rv += hashSet.toString();
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    UniQueue< string > uq;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        uq.enqueue( keyArr[ i ] );
    }

    cout << "DEBUG: uq: \n" << uq.toString() << endl;

    while ( ! uq.empty() ) {
        cout << "DEBUG: uq.dequeue(): " << uq.dequeue() << endl;
    }

    return 0;
}
