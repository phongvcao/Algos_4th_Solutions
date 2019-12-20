//
// Created by Phong Cao.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <array>
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

//----< iostream >----------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----< cstdio >------------//
using std::printf;
using std::fprintf;
using std::sprintf;
using std::snprintf;

//----< iomanip >-----------//
using std::setprecision;
using std::setw;

//----< ios >---------------//
using std::hex;
using std::dec;
using std::oct;
using std::fixed;

//----< sstream >-----------//
using std::ostringstream;
using std::istringstream;

//----< fstream >-----------//
using std::ofstream;
using std::ifstream;

//----< string >------------//
using std::getline;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

//----< cmath >-------------//
using std::sqrt;
using std::pow;
using std::log;             // log( <arg> )
using std::exp;             // e ^ <arg>
using std::abs;
using std::floor;           // Round down to nearest integer double
using std::ceil;            // Round up to nearest integer double
using std::trunc;           // Truncate the fractional part to get the integer part
using std::round;           // Round to nearest integer double

//----< cstdlib >-----------//
using std::rand;
using std::srand;

//----< ctime >-------------//
using std::time;

//----< functional >--------//
using std::hash;
using std::greater;         // lhs > rhs. Used for MinPQ
using std::less;            // lhs < rhs. Used for MaxPQ. Default for priority_queue<>
using std::less_equal;
using std::greater_equal;

//----< array >-------------//
using std::array;           // Fixed & Unordered Array

//----< vector >------------//
using std::vector;          // Resizable & Unordered Array

//----< map >---------------//
using std::map;             // Ordered Map (Red-Black Tree)

//----< unordered_map >-----//
using std::unordered_map;   // HashMap (SeparateChainingHashST)

//----< set >---------------//
using std::set;             // Ordered Set (Red-Black Tree)

//----< unordered_set >-----//
using std::unordered_set;   // HashSet (SeparateChainingHashST)

//----< list >--------------//
using std::list;            // Doubly-Linked List with size() ( O( 1 ) )

//----< forward_list >------//
using std::forward_list;    // Singly-Linked List without size() function ( so O( N ) if we need to get size() )

//----< deque >-------------//
using std::deque;           // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque

//----< queue >-------------//
using std::queue;           // Non-Iterable & Use std::deque as underlying data structure
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

//----< stack >-------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----< iterator >----------//
using std::next;            // Return an advanced iter without changing original iter
using std::prev;            // Return an decremented iter without changing original iter
using std::distance;        // Calculate distance between 2 iterators

//----< utility >-----------//
using std::pair;
using std::make_pair;
using std::move;            // Move resources between objects - typically used with std::unique_ptr<T>

//----< algorithm >---------//
using std::fill;
using std::max;
using std::min;
using std::find;
using std::reverse;
using std::sort;
using std::remove;

//----< memory >------------//
using std::make_unique;
using std::unique_ptr;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

//----< cctype >------------//
using std::isalnum;
using std::isalpha;
using std::islower;
using std::isupper;
using std::isdigit;
using std::isspace;         // Check whether char is whitespace character (space, newline, tab, etc. )
using std::isblank;         // Check whether char is blank character ( space or tab )
using std::tolower;
using std::toupper;

//----< stdexcept >---------//
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----< limits >------------//
using std::numeric_limits;

//----< numeric >-----------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

template< typename Key >
class Node {
public:
    Key key;
    int index = -1;
    Node< Key > * next;
    Node< Key > * prev;

    Node( Key key, int index )
        : key( key ),
          index( index )
    {
        // not implemented
    }

    virtual ~Node() {
        // not implemented
    }
};

template< typename Key >
class DoublyLinkedList {
private:

    vector< unique_ptr< Node< Key > > > nodes;

    Node< Key > * head = NULL;
    Node< Key > * tail = NULL;
    int N = 0;

public:

    DoublyLinkedList() {
        // not implemented
    }

    virtual ~DoublyLinkedList() {
        // not implemented
    }

    void append( Key key, int index ) {
        nodes.push_back( make_unique< Node< Key > >( key, index ) );
        Node< Key > * newNode = nodes.back().get();
        if ( ! head ) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++N;
    }

    void exchange( Node< Key > * h1, Node< Key > * h2 ) {
        Key temp = h1->key;
        h1->key = h2->key;
        h2->key = temp;
    }

    Node< Key > * getHead() const {
        return head;
    }

    Node< Key > * getTail() const {
        return tail;
    }

    int size() const {
        return N;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DoublyLinkedList< Key >& dList ) {
        out << "\nN : " << dList.N << " ; list : \n";
        Node< Key > * ptr = dList.head;
        while ( ptr ) {
            out << ptr->key << endl;
            ptr = ptr->next;
        }
        out << endl;
        return out;
    }

};

class Quick3WayStringLinkedList {
private:

    static int charAt( const string& s, int d ) {
        return d < s.size() ? s[ d ] : -1;
    }

    static void sort( DoublyLinkedList< string >& dList, Node< string > * lowNode, Node< string > * highNode, int d ) {
        if ( ! highNode ) return;
        if ( ! lowNode ) return;
        if ( highNode->index <= lowNode->index ) return;

        Node< string > * lt = lowNode;
        Node< string > * gt = highNode;
        Node< string > * i = lt->next;
        int pivot = charAt( lt->key, d );

        while ( i && gt && i->index <= gt->index ) {
            int t = charAt( i->key, d );

            if ( t < pivot ) {
                dList.exchange( lt, i );
                lt = lt->next;
                i = i->next;
            } else if ( t > pivot ) {
                dList.exchange( gt, i );
                gt = gt->prev;
            } else {
                i = i->next;
            }
        }

        sort( dList, lowNode, lt->prev, d );
        if ( pivot >= 0 ) {
            sort( dList, lt, gt, d + 1 );
        }
        sort( dList, gt->next, highNode, d );
    }

public:

    static void sort( DoublyLinkedList< string >& dList ) {
        sort( dList, dList.getHead(), dList.getTail(), 0 );
    }

};

int main( int argc, char ** argv ) {

    vector< string > strVec = {
        "edu.princeton.cs",
        "com.apple",
        "edu.princeton.cs",
        "com.cnn",
        "com.google",
        "edu.uva.cs",
        "edu.princeton.cs",
        "edu.princeton.cs.www",
        "edu.uva.cs",
        "edu.uva.cs",
        "edu.uva.cs",
        "com.adobe",
        "edu.princeton.ee",
    };

    DoublyLinkedList< string > strList;
    for ( int i = 0; i < strVec.size(); ++i ) {
        strList.append( strVec[ i ], i );
    }
    
    Quick3WayStringLinkedList::sort( strList );

    cout << strList << endl;

    return 0;
}
