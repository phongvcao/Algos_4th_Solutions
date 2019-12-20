package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQOrderedArray< Key extends Comparable< Key > > {

    private int N = 0;
    private Key[] pq;

    public MaxPQOrderedArray( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public Key delMax() {
        Key max = pq[ --N ];
        pq[ N ] = null;
        return max;
    }

    public void insert( Key k ) {
        int index = 0;
        while ( pq[ index ] != null && k.compareTo( pq[ index ] ) == 1 ) {
            ++index;
        }

        for ( int i = N; i > index; --i ) {
            pq[ i ] = pq[ i - 1 ];
        }

        pq[ index ] = k;
        ++N;
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQOrderedArray< Integer > maxPQ = new MaxPQOrderedArray< Integer >( intArr.length );

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
