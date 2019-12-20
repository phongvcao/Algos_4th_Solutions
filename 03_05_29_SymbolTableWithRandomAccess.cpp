//
// Created by Phong Cao on 2019-02-09.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
using std::time;
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

template< typename Key, typename Value >
class RandomAccessST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        const Key* key = NULL;
        const Value* value = NULL;
        NodePtr next = NULL;
        int count = 1;

        Node( const Key& key, const Value& value ) {
            this->key = &key;
            this->value = &value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key ) << " : " << *( h.value );
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
    vector< NodePtr > st;
    deque< Key > randomQueue;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:

    RandomAccessST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    RandomAccessST()
        : RandomAccessST( 17 )
    {
        // not implemented
    }

    virtual ~RandomAccessST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            if ( key == *( ptr->key ) ) {
                ptr->value = &value;
                return;
            }

            while ( ptr->next ) {
                if ( key == *( ptr->key ) ) {
                    ptr->value = &value;
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = newNode( key, value );
        } else {
            st[ hash( key ) ] = newNode( key, value );
        }
        randomQueue.push_back( key );
        ++N;
    }

    const Value* get( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    Key getRandom() {
        return randomQueue[ (unsigned long)rand() % randomQueue.size() ];
    }

    Key deleteRandom() {
        Key key = randomQueue[ (unsigned long)rand() % randomQueue.size() ];
        return key;
    }

    void deleteKey( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    st[ hash( key ) ] = NULL;
                }
                randomQueue.erase( key );
                --N;
                return;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    bool contains( const Key& key ) {
        return get( key ) != NULL;
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
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };
    srand( time( NULL ) );
    RandomAccessST< string, string > randomST;

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        randomST.put( keyArr[ i ], keyArr[ i ] );
    }

    cout << "DEBUG: randomST.toString(): \n" << randomST.toString() << endl;

    cout << "DEBUG: randomST.getRandom(): \n" << randomST.getRandom() << endl;
    cout << "DEBUG: randomST.getRandom(): \n" << randomST.getRandom() << endl;
    cout << "DEBUG: randomST.getRandom(): \n" << randomST.getRandom() << endl;

    randomST.deleteRandom();
    cout << "DEBUG: randomST.deleteRandom(): " << randomST.deleteRandom() << "\n" << randomST.toString() << endl;

    randomST.deleteRandom();
    cout << "DEBUG: randomST.deleteRandom(): " << randomST.deleteRandom() << "\n" << randomST.toString() << endl;

    return 0;
}
