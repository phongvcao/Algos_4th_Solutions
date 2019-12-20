package com.company;
import edu.princeton.cs.algs4.*;

public class IndexMinPQ< Item extends Comparable< Item > > {

    // Hold the priorityQueue
    // This queue contains k
    private int[] pqIndex;

    // Hold the position of priorityQueue items in Item[] items
    // items map accordingly to qpIndex's indexes
    // qpIndex's values are pqIndex's indexes
    private int[] qpIndex;

    private Item[] items;
    private int N = 0;

    public IndexMinPQ( int minN ) {
        pqIndex = new int[ minN + 1 ];
        qpIndex = new int[ minN + 1 ];
        items = ( Item[] )new Comparable[ minN + 1 ];

        for ( int i = 0; i < minN + 1; ++i ) {
            pqIndex[ i ] = -1;
            qpIndex[ i ] = -1;
        }
    }

    public void insert( int k, Item item ) {
        N++;
        qpIndex[ k ] = N;
        pqIndex[ N ] = k;
        items[ k ] = item;
        swim( N );
    }

    public boolean less( int i, int j ) {
        return items[ pqIndex[ i ] ].compareTo( items[ pqIndex[ j ] ] ) < 0;
    }

    public void swim( int k ) {
        while ( k > 1 && less( k, k / 2 ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j + 1, j ) ) ++j;
            if ( pqIndex[ j ] >= pqIndex[ k ] ) break;
            exchange( k, j );
            k = j;
        }
    }

    public void change( int k, Item item ) {
        items[ k ] = item;
        swim( qpIndex[ k ] );
        sink( qpIndex[ k ] );
    }

    public boolean contains( int k ) {
        return qpIndex[ k ] != -1;
    }

    public void delete( int k ) {
        exchange( k, N-- );
        swim( qpIndex[ k ] );
        sink( qpIndex[ k ] );
        items[ pqIndex[ N + 1 ] ] = null;
        qpIndex[ pqIndex[ N + 1 ] ] = -1;
    }

    public Item min() {
        return items[ pqIndex[ 1 ] ];
    }

    public int minIndex() {
        return pqIndex[ 1 ];
    }

    public void exchange( int i, int j ) {
        int temp = pqIndex[ i ];
        pqIndex[ i ] = pqIndex[ j ];
        pqIndex[ j ] = temp;

        qpIndex[ pqIndex[ i ] ] = i;
        qpIndex[ pqIndex[ j ] ] = i;
    }

    public int delMin() {
        int indexOfMin = pqIndex[ 1 ];
        exchange( 1, N-- );
        sink( 1 );
        items[ indexOfMin ] = null;
        qpIndex[ indexOfMin ] = -1;
        pqIndex[ N + 1 ] = -1;
        return indexOfMin;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    public String toString() {
        return "===================" +
                " ; \npqIndex : " + java.util.Arrays.toString( pqIndex ) +
                " ; \nqpIndex : " + java.util.Arrays.toString( qpIndex ) +
                " ; \nitems : " + java.util.Arrays.toString( items );
    }

    public static void main( String[] args ) {
        Integer[] kArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        IndexMinPQ< Integer > indexMinPQ = new IndexMinPQ< Integer >( kArr.length );

        for ( int i = 0; i < kArr.length; ++i ) {
            indexMinPQ.insert( kArr[ i ], kArr[ i ] );
        }

        while ( ! indexMinPQ.isEmpty() ) {
            StdOut.println( "DEBUG: indexMinPQ (BEFORE): " + indexMinPQ.toString() );
            StdOut.println( "DEBUG: indexMinPQ.min(): " + indexMinPQ.min() );
            StdOut.println( "DEBUG: indexMinPQ.delMin(): " + indexMinPQ.delMin() );

        }
    }

}
