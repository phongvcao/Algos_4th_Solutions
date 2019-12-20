package com.company;
import edu.princeton.cs.algs4.*;

public class GeneralizedQueue< Item > {
    private int N = 0;
    private Item[] array;
    private int cap = 5;

    public GeneralizedQueue() {
        array = ( Item[] )new Object[ cap ];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    private void doubleArraySizeLeft() {
        Item[] newArray = ( Item[] )new Object[ cap * 2 ];

        for ( int i = 0; i < array.length; ++i ) {
            newArray[ i + cap ] = array[ i ];
        }

        array = newArray;
        cap *= 2;
    }

    private void doubleArraySizeRight() {
        Item[] newArray = ( Item[] )new Object[ cap * 2 ];

        for ( int i = 0; i < array.length; ++i ) {
            newArray[ i ] = array[ i ];
        }

        array = newArray;
        cap *= 2;
    }

    private void moveItemsLeft( int k ) {
        for ( int i = k; i < N; ++i ) {
            array[ k ] = array[ k + 1 ];
        }
        array[ N - 1 ] = null;
    }

    public void insert( Item x ) {
        if ( N == array.length - 1 ) {
            doubleArraySizeRight();
        }

        array[ N++ ] = x;
    }

    public Item delete( int k ) {
        Item rv = array[ k ];
        moveItemsLeft( k );
        --N;
        return rv;
    }

    public String toString() {
        String rv = "{";

        for ( int i = 0; i < N; ++i ) {
            rv += " " + array[ i ] + ",";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        GeneralizedQueue< String > queue = new GeneralizedQueue< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            queue.insert( strArr[ i ] );
        }

        StdOut.println( "DEBUG (BEFORE): " + queue.toString() );
        queue.delete( 3 );
        StdOut.println( "DEBUG (AFTER): " + queue.toString() );

    }
}
