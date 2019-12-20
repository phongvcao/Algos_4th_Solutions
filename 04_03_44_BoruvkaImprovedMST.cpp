//
// Created by Phong Cao on 2019-03-22.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
#include <iterator>
#include <utility>
#include <algorithm>
#include <memory>
#include <cctype>
#include <stdexcept>
#include <limits>
#include <numeric>

//----<iostream>------------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----<iomanip>-------------//
using std::setprecision;
using std::setw;

//----<ios>-----------------//
using std::hex;
using std::dec;
using std::oct;
using std::fixed;

//----<sstream>-------------//
using std::ostringstream;
using std::istringstream;

//----<fstream>-------------//
using std::ofstream;
using std::ifstream;

//----<string>--------------//
using std::getline;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

//----<cmath>---------------//
using std::sqrt;
using std::pow;

//----<cstdlib>-------------//
using std::rand;
using std::srand;

//----<ctime>---------------//
using std::time;

//----<functional>----------//
using std::hash;
using std::greater;         // lhs > rhs. Used for MinPQ
using std::less;            // lhs < rhs. Used for MaxPQ. Default for priority_queue<>
using std::less_equal;
using std::greater_equal;

//----<vector>--------------//
using std::vector;          // Unordered Array

//----<map>-----------------//
using std::map;             // Ordered Map (Red-Black Tree)

//----<unordered_map>-------//
using std::unordered_map;   // HashMap (SeparateChainingHashST)

//----<set>-----------------//
using std::set;             // Ordered Set (Red-Black Tree)

//----<unordered_set>-------//
using std::unordered_set;   // HashSet (SeparateChainingHashST)

//----<list>----------------//
using std::list;            // Doubly-Linked List with size() ( O( 1 ) )

//----<forward_list>--------//
using std::forward_list;    // Singly-Linked List without size() function ( so O( N ) if we need to get size() )

//----<deque>---------------//
using std::deque;           // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque

//----<queue>---------------//
using std::queue;           // Non-Iterable & Use std::deque as underlying data structure
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

//----<stack>---------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----<iterator>------------//
using std::next;            // Return an advanced iter without changing original iter

//----<utility>-------------//
using std::pair;

//----<algorithm>-----------//
using std::fill;
using std::max;
using std::min;
using std::find;
using std::reverse;
using std::sort;

//----<memory>--------------//
using std::make_shared;
using std::shared_ptr;

//----<cctype>--------------//
using std::isalnum;
using std::isalpha;
using std::islower;
using std::isupper;
using std::isdigit;
using std::isspace;         // Check whether char is whitespace character (space, newline, tab, etc. )
using std::isblank;         // Check whether char is blank character ( space or tab )
using std::tolower;
using std::toupper;

//----<stdexcept>-----------//
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----<limits>--------------//
using std::numeric_limits;

//----<numeric>-------------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

class Edge {
private:

    int v = 0;
    int w = 0;
    double weight = numeric_limits< double >::infinity();

public:

    Edge() {
        // not implemented
    }

    Edge( int v, int w, double weight )
        : v( v ),
          w( w ),
          weight( weight )
    {
        // not implemented
    }

    Edge( const Edge& e )
        : v( e.v ),
          w( e.w ),
          weight( e.weight )
    {
        // not implemented
    }

    virtual ~Edge() {
        // not implemented
    }

    int getEither() const {
        return v;
    }

    int getOther( int vertex ) const {
        if ( vertex == v ) {
            return w;
        } else if ( vertex == w ) {
            return v;
        } else {
            throw invalid_argument( "Invalid vertex for edge : " + toString() );
        }
    }

    double getWeight() const {
        return weight;
    }

    friend bool operator <( const Edge& e1, const Edge& e2 ) {
        return e1.weight < e2.weight;
    }

    friend bool operator >( const Edge& e1, const Edge& e2 ) {
        return e1.weight > e2.weight;
    }

    operator bool() const {
        return weight != numeric_limits< double >::infinity();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Edge& e ) {
        out << fixed << setprecision( 2 );
        out << " | " << e.v << " : " << e.w << " : " << e.weight << " | ";
        return out;
    }

};

class EdgeWeightedGraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< Edge > > adj;

public:

    EdgeWeightedGraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~EdgeWeightedGraph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    forward_list< Edge > getAdj( int v ) const {
        return adj[ v ];
    }

    forward_list< Edge > getEdges() const {
        forward_list< Edge > all;
        for ( int v = 0; v < getV(); ++v ) {
            for ( Edge e : getAdj( v ) ) {
                if ( e.getOther( v ) > v ) {
                    all.push_front( e );
                }
            }
        }
        return all;
    }

    void addEdge( Edge e ) {
        int v = e.getEither();
        int w = e.getOther( v );
        adj[ v ].push_front( e );
        adj[ w ].push_front( e );
        ++E;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const EdgeWeightedGraph& G ) {
        out << "\n| V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n| v : " << v << " : ";
            for ( const Edge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }
};

template< typename Key >
class CircularDoublyLinkedList {
private:

    class DoubleNode;
    typedef shared_ptr< DoubleNode > DNodePtr;

    DNodePtr newDNode( Key key ) {
        return make_shared< DoubleNode >( key );
    }

    class DoubleNode {
    public:
        Key key;
        DNodePtr prev = NULL;
        DNodePtr next = NULL;

        DoubleNode( Key key )
            : key( key )
        {
            // not implemented
        }

        virtual ~DoubleNode() {
            // not implemented
        }

        string toString() const {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }

        friend ostream& operator <<( ostream& out, const DoubleNode& h ) {
            out << fixed << setprecision( 2 );
            out << "\n| key : " << h.key;

            if ( h.prev ) {
                out << " ; prev : " << h.prev->key;
            } else {
                out << " ; prev : NULL";
            }

            if ( h.next ) {
                out << " ; next : " << h.next->key;
            } else {
                out << " ; next : NULL";
            }
            out << " | ";
            return out;
        }
    };

    int N = 0;
    int id = 0;
    DNodePtr head = NULL;

public:

    CircularDoublyLinkedList() {
        // not implemented
    }

    CircularDoublyLinkedList( int id )
        : id( id )
    {
        // not implemented
    }

    virtual ~CircularDoublyLinkedList() {
        // not implemented
    }

    void setId( int newId ) {
        this->id = newId;
    }

    int getId() const {
        return id;
    }

    void addKey( Key key ) {
        DNodePtr ptr = head;
        if ( ! ptr ) {
            head = newDNode( key );
        } else {
            if ( ptr->key == key ) {
                return;
            }

            while ( ptr->next ) {
                if ( ptr->key == key ) {
                    return;
                }
                if ( ptr->next->key == head->key ) {
                    break;
                }
                ptr = ptr->next;
            }
            ptr->next = newDNode( key );
            ptr->next->next = head;
            ptr->next->prev = ptr;
            head->prev = ptr->next;
        }
        ++N;
    }

    vector< Key > getKeys() const {
        vector< Key > rvVec;
        DNodePtr ptr = head;
        while ( ptr ) {
            rvVec.push_back( ptr->key );
            ptr = ptr->next;
            if ( ptr->key == head->key ) {
                break;
            }
        }
        return rvVec;
    }

    bool contains( const Key& key ) const {
        DNodePtr ptr = head;
        while ( ptr ) {
            if ( ptr->key == key ) {
                return true;
            }
            ptr = ptr->next;
            if ( ptr->key == head->key ) {
                break;
            }
        }
        return false;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) throw runtime_error( "Invalid key" );
        DNodePtr ptr = head;
        while ( ptr ) {
            if ( ptr->key == key ) {
                if ( ptr->prev ) {
                    if ( ptr->prev->key == ptr->next->key ) {
                        head = ptr->prev;
                        ptr->next->prev = NULL;
                        ptr->prev->next = NULL;
                        ptr->next = NULL;
                        ptr->prev = NULL;
                    } else {
                        if ( ptr->prev->next->key != ptr->next->key ) {
                            ptr->prev->next = ptr->next;
                        } else {
                            ptr->prev->next = NULL;
                        }

                        if ( ptr->next->prev->key != ptr->prev->key ) {
                            ptr->next->prev = ptr->prev;
                        } else {
                            ptr->next->prev = NULL;
                        }

                        if ( head->key == ptr->key ) {
                            head = ptr->prev;
                        }
                    }
                } else {
                    // ptr is the only node in the list
                    head = NULL;
                }
                --N;
                break;
            }
            ptr = ptr->next;
            if ( ptr && ptr->key == head->key ) {
                break;
            }
        }
    }

    const Key * getHeadKey() const {
        if ( head ) {
            return &( head->key );
        } else {
            return NULL;
        }
    }

    int size() const {
        return N;
    }

    bool empty() const {
        return size() == 0;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const CircularDoublyLinkedList& cList ) {
        DNodePtr ptr = cList.head;
        out << "\n| size : " << cList.size() << " | " << endl;
        while ( ptr ) {
            out << *ptr << ", ";
            ptr = ptr->next;
            if ( ptr && ptr->key == cList.head->key ) {
                out << *ptr << ", ";
                break;
            }
        }
        return out;
    }

    static void test() {
        vector< int > intVec { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        CircularDoublyLinkedList< int > cList;
        for ( int i = 0; i < intVec.size(); ++i ) {
            cList.addKey( intVec[ i ] );
        }
        cout << "DEBUG : cList : test() : " << endl;
        cout << cList << endl;

        for ( int i = 0; i < intVec.size(); ++i ) {
            try {
                cList.deleteKey( intVec[ i ] );
                cout << "DEBUG: cList.deleteKey( " << intVec[ i ] << " ) : " << endl;
                cout << cList << endl;
            } catch ( const runtime_error& e ) {
                cout << e.what() << " : " << intVec[ i ] << endl;
                break;
            }
        }
    }
};

class BoruvkaImprovedMST {
private:

    queue< Edge > mst;
    double weight = 0;

public:

    BoruvkaImprovedMST( const EdgeWeightedGraph& G ) {
        forward_list< Edge > edges = G.getEdges();
        // Key is vertex, value is component Id
        vector< shared_ptr< CircularDoublyLinkedList< int > > > listVec( G.getV() );

        // WeightedQuickUnionUF uf( G.getV() );

        for ( int stage = 1; stage < G.getV() && mst.size() < G.getV() - 1; stage = stage + stage ) {
            vector< Edge > closestEdges( G.getV() );
            for ( Edge e : edges ) {
                int v = e.getEither();
                int w = e.getOther( v );

                int vId = listVec[ v ] ? listVec[ v ]->getId() : v;
                int wId = listVec[ w ] ? listVec[ w ]->getId() : w;
                // int vId = uf.find( v );
                // int wId = uf.find( w );

                if ( vId == wId ) {
                    continue;
                }

                if ( ! closestEdges[ vId ] || e < closestEdges[ vId ] ) {
                    closestEdges[ vId ] = e;
                }

                if ( ! closestEdges[ wId ] || e < closestEdges[ wId ] ) {
                    closestEdges[ wId ] = e;
                }
            }

            for ( int v = 0; v < G.getV(); ++v ) {
                Edge e = closestEdges[ v ];

                if ( e ) {
                    int v = e.getEither();
                    int w = e.getOther( v );

                    if ( ! listVec[ v ] || ! listVec[ w ] || listVec[ v ]->getId() != listVec[ w ]->getId() ) {
                        mst.push( e );
                        weight += e.getWeight();

                        if ( ! listVec[ v ] && ! listVec[ w ] ) {
                            listVec[ v ] = make_shared< CircularDoublyLinkedList< int > >( v );
                            listVec[ w ] = listVec[ v ];
                            listVec[ v ]->addKey( v );
                            listVec[ v ]->addKey( w );
                        } else if ( ! listVec[ v ] ) {
                            listVec[ v ] = listVec[ w ];
                            listVec[ w ]->addKey( v );
                        } else if ( ! listVec[ w ] ) {
                            listVec[ w ] = listVec[ v ];
                            listVec[ v ]->addKey( w );
                        } else {
                            vector< int > keyVec = listVec[ w ]->getKeys();
                            for ( int key : keyVec ) {
                                listVec[ v ]->addKey( key );
                            }
                            for ( int key : keyVec ) {
                                listVec[ key ] = listVec[ v ];
                            }
                        }

                        // uf.doUnion( v, w );
                    }
                }
            }
        }
    }

    virtual ~BoruvkaImprovedMST() {
        // not implemented
    }

    double getWeight() const {
        return weight;
    }

    queue< Edge > getEdges() const {
        return mst;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const BoruvkaImprovedMST& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

int main( int argc, char ** argv ) {

    double graphArr[ 16 ][ 3 ] = {
            { 4, 5, 0.35 },
            { 4, 7, 0.37 },
            { 5, 7, 0.28 },
            { 0, 7, 0.16 },
            { 1, 5, 0.32 },
            { 0, 4, 0.38 },
            { 2, 3, 0.17 },
            { 1, 7, 0.19 },
            { 0, 2, 0.26 },
            { 1, 2, 0.36 },
            { 1, 3, 0.29 },
            { 2, 7, 0.34 },
            { 6, 2, 0.40 },
            { 3, 6, 0.52 },
            { 6, 0, 0.58 },
            { 6, 4, 0.93 }
    };

    EdgeWeightedGraph ewGraph( 8 );

    for ( int i = 0; i < 16; ++i ) {
        Edge e( (int)graphArr[ i ][ 0 ], (int)graphArr[ i ][ 1 ], graphArr[ i ][ 2 ] );
        ewGraph.addEdge( e );
    }

    cout << "DEBUG: ewGraph: \n" << ewGraph.toString() << endl;

    // CircularDoublyLinkedList< int, int >::test();

    BoruvkaImprovedMST mst( ewGraph );
    cout << "DEBUG: BoruvkaImprovedMST: \n" << mst << endl;
    cout << "DEBUG: BoruvkaImprovedMST.getWeight(): \n" << mst.getWeight() << endl;

    return 0;
}
