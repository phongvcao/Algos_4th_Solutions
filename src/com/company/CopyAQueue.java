package com.company;
import edu.princeton.cs.algs4.*;

public class CopyAQueue< Item > {

    private int N = 0;
    private Item[] array;
    private int headIdx = 0;
    private int cap = 10;

    public CopyAQueue() {
        array = ( Item[] )new Object[ cap ];
    }

    public CopyAQueue( CopyAQueue< Item > q ) {
        array = ( Item[] )new Object[ cap ];
        Item[] tempArr = ( Item[] )new Object[ cap ];
        int idx = 0;
        while ( ! q.isEmpty() ) {
            tempArr[ idx++ ] = q.dequeue();
        }

        // StdOut.println( "DEBUG: tempArr: " + java.util.Arrays.toString( tempArr ) );
        // StdOut.println( "DEBUG: array: " + java.util.Arrays.toString( array ) );

        for ( int i = 0; i < tempArr.length; ++i ) {
            // StdOut.println( "DEBUG: Looping through i: " + i );
            array[ i ] = tempArr[ i ];
            q.enqueue( tempArr[ i ] );
        }

        // StdOut.println( "DEBUG: ( 3 ): " + q.toString() );
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void enqueue( Item item ) {
        array[ N++ ] = item;
    }

    public Item dequeue() {
        Item rv = null;

        if ( ( ! isEmpty() ) && ( headIdx < cap ) ) {
            // StdOut.println( "DEBUG: headIdx: " + headIdx );
            rv = array[ headIdx ];
            array[ headIdx++ ] = null;
            --N;
        }

        if ( N == 0 ) {
            headIdx = 0;
        }

        return rv;
    }

    public String toString() {
        String rv = "{";

        for ( int i = headIdx; i < array.length; ++i ) {
            rv += " " + array[ i ] + ",";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        CopyAQueue< String > queue = new CopyAQueue< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            queue.enqueue( strArr[ i ] );
        }

        StdOut.println( "DEBUG: ( 0 ): " + queue.toString() );

        CopyAQueue< String > q = new CopyAQueue< String >( queue );

        StdOut.println( "DEBUG: ( 0 ): " + queue.toString() );
        StdOut.println( "DEBUG: ( 1 ): " + q.toString() );

        queue.dequeue();

        StdOut.println( "DEBUG: ( 0 ): " + queue.toString() );
        StdOut.println( "DEBUG: ( 1 ): " + q.toString() );
    }
}
