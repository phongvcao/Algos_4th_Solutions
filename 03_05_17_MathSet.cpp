//
// Created by Phong Cao on 2019-02-07.
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
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::deque;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

template< typename Key >
class MathSet {

private:

    // Implement SeparateChainingHashST
    class SeparateChainingHashST {
    private:
        class Node;
        typedef shared_ptr< Node > NodePtr;

        NodePtr newNode( const Key& key ) {
            return make_shared< Node >( key );
        }

        class Node {
        public:
            const Key* key = NULL;
            NodePtr next = NULL;

            Node( const Key& key ) {
                this->key = &key;
            }

            virtual ~Node() {
                // not implemented
            }

            friend ostream& operator <<( ostream& out, const Node& h ) {
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

        vector< NodePtr > st;
        int M = 17;
        int N = 0;

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
            : SeparateChainingHashST( 17 )
        {
            // not implemented
        }

        virtual ~SeparateChainingHashST() {
            // not implemented
        }

        void put( const Key& key ) {
            NodePtr ptr = st[ hash( key ) ];
            if ( ptr ) {
                while ( ptr->next ) {
                    if ( key == *( ptr->key ) ) {
                        return;
                    }
                    ptr = ptr->next;
                }
                ptr->next = newNode( key );
            } else {
                st[ hash( key ) ] = newNode( key );
            }
            ++N;
        }

        bool contains( const Key& key ) {
            NodePtr ptr = st[ hash( key ) ];
            while ( ptr ) {
                if ( key == *( ptr->key ) ) {
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
                    --N;
                }

                beforePtr = ptr;
                ptr = ptr->next;
            }
        }

        queue< Key > getKeys() {
            queue< Key > q;
            for ( int i = 0; i < M; ++i ) {
                NodePtr ptr = st[ i ];
                while ( ptr ) {
                    q.push( *( ptr->key ) );
                    ptr = ptr->next;
                }
            }
            return q;
        }

        string toString() {
            string rv = "\n";
            for ( int i = 0; i < M; ++i ) {
                NodePtr ptr = st[ i ];
                while ( ptr ) {
                    rv += "i : " + to_string( i ) + ptr->toString();
                    ptr = ptr->next;
                }
            }
            return rv;
        }
    };

    unordered_map< Key, bool > universe;

public:
    SeparateChainingHashST hashST;

    MathSet( const vector< Key >& uni ) {
        for ( int i = 0; i < uni.size(); ++i ) {
            this->universe.insert( pair< Key, bool >( uni[ i ], true ) );
        }
    }

    virtual ~MathSet() {
        // not implemented
    }

    void add( const Key& key ) {
        hashST.put( key );
        if ( universe.find( key ) == universe.end() ) {
            universe.insert( pair< Key, bool >( key, true ) );
        }
    }

    shared_ptr< MathSet > complement() {
        vector< Key > universeVec;
        for ( typename unordered_map< Key, bool >::iterator iter = universe.begin(); iter != universe.end(); ++iter ) {
            universeVec.push_back( iter->first );
        }
        shared_ptr< MathSet > rv = make_shared< MathSet >( universeVec );
        for ( typename unordered_map< Key, bool >::iterator iter = universe.begin(); iter != universe.end(); ++iter ) {
            if ( ! hashST.contains( iter->first ) ) {
                rv->add( iter->first );
            }
        }
        return rv;
    }

    void unionWith( MathSet& a ) {
        queue< Key > aKeys = a.hashST.getKeys();
        while ( ! aKeys.empty() ) {
            if ( ! hashST.contains( aKeys.front() ) ) {
                hashST.put( aKeys.front() );
                if ( universe.find( aKeys.front() ) == universe.end() ) {
                    universe.insert( pair< Key, bool >( aKeys.front(), true ) );
                }
            }
            aKeys.pop();
        }
    }

    void intersection( MathSet& a ) {
        queue< Key > q = hashST.getKeys();
        while ( ! q.empty() ) {
            if ( ! a.contains( q.front() ) ) {
                deleteKey( q.front() );
            }
            q.pop();
        }
    }

    void deleteKey( const Key& key ) {
        hashST.deleteKey( key );
    }

    bool contains( const Key& key ) {
        return hashST.contains( key );
    }

    bool isEmpty() {
        return size() == 0;
    }

    int size() {
        return hashST.size();
    }

    string toString() {
        ostringstream oss;
        // Output universe
        oss << "DEBUG: universe: \n";
        for ( typename unordered_map< Key, bool >::iterator iter = universe.begin(); iter != universe.end() ; ++iter ) {
            oss << iter->first << " ";
        }
        oss << "\nDEBUG: ST : \n";
        // Output hashST
        oss << hashST.toString();
        return oss.str();
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string testArr[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };

    vector< string > keyVec;
    vector< string > testVec;

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        keyVec.push_back( keyArr[ i ] );
    }
    for ( int i = 0; i < sizeof( testArr ) / sizeof( string ); ++i ) {
        testVec.push_back( testArr[ i ] );
    }

    // Initialize mathSet
    MathSet< string > mathSet( keyVec );
    for ( int i = 0; i < keyVec.size() - 4; ++i ) {
        mathSet.add( keyVec[ i ] );
    }

    cout << "DEBUG: mathSet: \n" << mathSet.toString() << endl;
    
    shared_ptr< MathSet< string > > rv = mathSet.complement();
    cout << "DEBUG: mathSet.complement(): \n" << rv->toString() << endl;

    // Initialize mathSet1
    MathSet< string > mathSet1( testVec );
    for ( int i = 0; i < testVec.size(); ++i ) {
        mathSet1.add( testVec[ i ] );
    }

    cout << "DEBUG: mathSet1: \n" << mathSet1.toString() << endl;

    mathSet.intersection( mathSet1 );
    cout << "DEBUG: mathSet.intersection( mathSet1 ): " << mathSet.toString() << endl;

    mathSet.unionWith( mathSet1 );
    cout << "DEBUG: mathSet.unionWith( mathSet1 ): " << mathSet.toString() << endl;

    return 0;
}
