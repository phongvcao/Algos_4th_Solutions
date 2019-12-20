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

static const int HASH_TABLE_SIZE = 997;

class Date {
private:
    int month = 1;
    int day = 1;
    int year = 2018;

public:
    Date() {
        // not implemented
    }

    Date( int month, int day, int year )
            : month( month ),
              day( day ),
              year( year )
    {
        // not implemented
    }

    virtual ~Date() {
        // not implemented
    }

    int hashCode() {
        int R = 31;
        size_t hash = day;
        hash = ( hash * R + month ) % HASH_TABLE_SIZE;
        hash = ( hash * R + year ) % HASH_TABLE_SIZE;
        return hash;
    }
};

class Transaction {
private:
    string who = "";
    Date when;
    double amount;
    int hashCache = 0;

public:
    Transaction( string who, const Date& when, double amount )
        : who( who ),
          amount( amount )
    {
        this->when = when;
    }

    virtual ~Transaction() {
        // not implemented
    }

    int hashCode() {
        int hash = 17;
        int R = R;
        hash = ( R * hash + std::hash< string >{}( who ) ) % HASH_TABLE_SIZE;
        hash = ( R * hash + when.hashCode() ) % HASH_TABLE_SIZE;
        hash = ( R * hash + std::hash< double >{}( amount ) ) % HASH_TABLE_SIZE;
        hashCache = hash;
        return hash;
    }
};

int main( int argc, char ** argv ) {
    Date date( 2, 2, 2019 );
    Transaction trans( "Phong", date, 10 );
    cout << trans.hashCode() << endl;

    return 0;
}
