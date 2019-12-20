package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQUnorderedArray< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MaxPQUnorderedArray( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    private boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    private void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public void insert( Key k ) {
        pq[ N++ ] = k;
    }

    private int getMaxIndex() {
        int maxIdx = -1;

        for ( int i = 0; i < N; ++i ) {
            if ( maxIdx == -1 || less( maxIdx, i ) ) {
                maxIdx = i;
            }
        }

        return maxIdx;
    }

    public Key max() {
        Key max = null;
        int maxIdx = getMaxIndex();
        if ( maxIdx != -1 ) {
            max = pq[ maxIdx ];
        }
        return max;
    }

    public Key delMax() {
        Key max = null;
        int maxIdx = getMaxIndex();
        if ( maxIdx != -1 ) {
            exchange( maxIdx, --N );
        }
        max = pq[ N ];
        pq[ N ] = null;
        return max;
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
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
        MaxPQUnorderedArray< Integer > maxPQ = new MaxPQUnorderedArray< Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
