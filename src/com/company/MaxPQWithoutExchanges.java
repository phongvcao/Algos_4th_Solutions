package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQWithoutExchanges< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MaxPQWithoutExchanges( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swimWithoutExchanges( N );
    }

    public Key max() {
        return pq[ 1 ];
    }

    public Key delMax() {
        Key max = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sinkWithoutExchanges( 1 );
        return max;
    }

    public void swim( int k ) {
        while ( k > 1 && less( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public boolean less( Key a, Key b ) {
        return a.compareTo( b ) == -1;
    }

    public void swimWithoutExchanges( int k ) {
        Key aux = pq[ k ];
        boolean exchangeRequired = false;
        while ( k > 1 && less( pq[ k / 2 ], aux ) ) {
            pq[ k ] = pq[ k / 2 ];
            k /= 2;
            exchangeRequired = true;
        }
        if ( exchangeRequired ) {
            pq[ k ] = aux;
        }
    }

    public void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j, j + 1 ) ) ++j;
            if ( ! less( k, j ) ) break;
            exchange( k, j );
            k = j;
        }
    }

    public void sinkWithoutExchanges( int k ) {
        Key aux = pq[ k ];
        boolean exchangeRequired = false;
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j, j + 1 ) ) ++j;
            if ( ! less( aux, pq[ j ] ) ) break;
            pq[ k ] = pq [ j ];
            exchangeRequired = true;
            k = j;
        }

        if ( exchangeRequired ) {
            pq[ k ] = aux;
        }
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }

        rv += "}";
        return rv;
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQWithoutExchanges< Integer > maxPQ = new MaxPQWithoutExchanges< Integer >( intArr.length + 1 );

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
