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

// Implement HashMap
class HashMap {
private:

    // Implement HashSet
    class HashSet {
    private:
        class SNode;
        typedef shared_ptr< SNode > SNodePtr;

        SNodePtr newSNode( int key ) {
            return make_shared< SNode >( key );
        }

        class SNode {
        public:
            int key = 0;
            SNodePtr next = NULL;

            SNode( int key )
                : key( key )
            {
                // not implemented
            }

            virtual ~SNode() {
                // not implemented
            }

            friend ostream& operator <<( ostream& out, const SNode& h ) {
                out << " | " << h.key;
                if ( h.next ) {
                    out << " ; next : " << h.next->key;
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
        vector< SNodePtr > st;

        int hash( int key ) const {
            return std::hash< int >{}( key ) % M;
        }

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

        void put( int key ) {
            SNodePtr ptr = st[ hash( key ) ];
            if ( ptr ) {
                if ( ptr->key == key ) {
                    return;
                }
                while ( ptr->next ) {
                    if ( ptr->key == key ) {
                        return;
                    }
                    ptr = ptr->next;
                }
                ptr->next = newSNode( key );
            } else {
                st[ hash( key ) ] = newSNode( key );
            }
            ++N;
        }

        bool contains( int key ) const {
            SNodePtr ptr = st[ hash( key ) ];
            while ( ptr ) {
                if ( ptr->key == key ) {
                    return true;
                }
                ptr = ptr->next;
            }
            return false;
        }

        void deleteKey( int key ) {
            SNodePtr ptr = st[ hash( key ) ];
            SNodePtr beforePtr = NULL;
            while ( ptr ) {
                if ( ptr->key == key ) {
                    if ( beforePtr ) {
                        beforePtr->next = ptr->next;
                    } else {
                        st[ hash( key ) ] = NULL;
                    }
                }

                beforePtr = ptr->next;
                ptr = ptr->next;
            }
        }

        string toString() {
            string rv = "\n";
            for ( int i = 0; i < M; ++i ) {
                SNodePtr ptr = st[ i ];
                while ( ptr ) {
                    rv += "i : " + to_string( i ) + " " + to_string( ptr->key ) + "\n";
                    ptr = ptr->next;
                }
            }
            return rv;
        }

        int size() {
            return N;
        }

        bool empty() {
            return size() == 0;
        }

        deque< int > getKeys() {
            deque< int > dq;
            for ( int i = 0; i < M; ++i ) {
                SNodePtr ptr = st[ i ];
                while ( ptr ) {
                    dq.push_back( ptr->key );
                }
            }
            return dq;
        }
    };

    class MNode;
    typedef shared_ptr< MNode > MNodePtr;

    MNodePtr newMNode( int instructor, int classId ) {
        return make_shared< MNode >( instructor, classId );
    }

    class MNode {
    public:
        int instructor = 0;
        HashSet classSet;
        MNodePtr next = NULL;

        MNode( int instructor, int classId )
            : instructor( instructor )
        {
            classSet.put( classId );
        }

        virtual ~MNode() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, MNode& h ) {
            out << " | " << h.instructor << " : " << h.classSet.toString();
            if ( h.next ) {
                out << " ; next : " << h.next->instructor;
            } else {
                out << " ; next : null";
            }
            out << " | ";
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
    vector< MNodePtr > mapST;

    int hash( int key ) {
        return std::hash< int >{}( key ) % M;
    }

public:

    HashMap( int M )
        : M( M )
    {
        mapST.resize( M );
        for ( int i = 0; i < M; ++i ) {
            mapST[ i ] = NULL;
        }
    }

    HashMap()
        : HashMap( 17 )
    {
        // not implemented
    }

    virtual ~HashMap() {
        // not implemented
    }

    void put( int instructor, int classId ) {
        MNodePtr ptr = mapST[ hash( instructor ) ];
        if ( ptr ) {
            if ( ptr->instructor == instructor ) {
                ptr->classSet.put( classId );
                return;
            }

            while ( ptr->next ) {
                if ( ptr->instructor == instructor ) {
                    ptr->classSet.put( classId );
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = newMNode( instructor, classId );
        } else {
            mapST[ hash( instructor ) ] = newMNode( instructor, classId );
        }
        ++N;
    }

    void deleteKey( int instructor ) {
        MNodePtr ptr = mapST[ hash( instructor ) ];
        MNodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( ptr->instructor == instructor ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    mapST[ hash( instructor ) ] = NULL;
                }
                --N;
                return;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    deque< int > getClassIds( int instructor ) {
        deque< int > dq;
        MNodePtr ptr = mapST[ hash( instructor ) ];
        while ( ptr ) {
            if ( ptr->instructor == instructor ) {
                dq = ptr->classSet.getKeys();
                return dq;
            }
            ptr = ptr->next;
        }
        return dq;
    }

    const HashSet* getClassSet( int instructor ) {
        MNodePtr ptr = mapST[ hash( instructor ) ];
        while ( ptr ) {
            if ( ptr->instructor == instructor ) {
                return &( ptr->classSet );
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    bool contains( int instructor ) {
        return getClassSet( instructor ) != NULL;
    }

    bool contains( int instructor, int classId ) {
        if ( ! contains( instructor ) ) return false;
        return getClassSet( instructor )->contains( classId );
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
            MNodePtr ptr = mapST[ i ];
            while ( ptr ) {
                rv += "\n" + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    deque< int > getKeys() {
        deque< int > dq;
        for ( int i = 0; i < M; ++i ) {
            MNodePtr ptr = mapST[ i ];
            while ( ptr ) {
                dq.push_back( ptr->instructor );
                ptr = ptr->next;
            }
        }
        return dq;
    }
};


int main( int argc, char ** argv ) {
    // Collection of instructors & classes
    // There are 3 instructors: 0, 1, 2
    // There are 6 classes: 9, 10, 11, 13, 14, 15
    int keyValueArr[ 9 ][ 2 ] = {
            { 0, 9 },
            { 0, 10 },
            { 0, 13 },
            { 1, 11 },
            { 1, 14 },
            { 1, 15 },
            { 2, 9 },
            { 2, 11 },
            { 2, 13 }
    };
    HashMap hashMap;

    for ( int i = 0; i < 9; ++i ) {
        hashMap.put( keyValueArr[ i ][ 0 ], keyValueArr[ i ][ 1 ] );
    }

    cout << hashMap.toString() << endl;

    return 0;
}
