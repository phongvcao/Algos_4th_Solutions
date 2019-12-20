package com.company;
import edu.princeton.cs.algs4.*;

public class RingBuffer< Item > {

    private int N = 0;
    Item[] array;
    private int limit = 5;
    private int headIdx = 0;
    private int tailIdx = 0;

    public RingBuffer() {
        array = ( Item[] )new Object[ limit ];
    }

    public RingBuffer( int cap ) {
        limit = cap;
        array = ( Item[] )new Object[ limit ];
    }

    public void enqueue( Item item ) {

        // StdOut.println( "DEBUG: enqueue(): " + java.util.Arrays.toString( array ) );

        if ( N < limit ) {
            // StdOut.println( "DEBUG: enqueue() ( 0 ): " + java.util.Arrays.toString( array ) );

            array[ ( tailIdx++ ) % limit ] = item;
            ++N;
        } else {
            // StdOut.println( "DEBUG: enqueue() ( 1 ): " + java.util.Arrays.toString( array ) );
        }
    }

    public Item dequeue() {
        Item rv = null;
        if ( N == limit ) {
            rv = array[ ( headIdx++ ) % limit ];
            --N;
        }
        return rv;
    }

    public String toString() {
        String rv = "{";

        for ( int i = headIdx % limit; i < limit; ++i ) {
            rv += " " + array[ i ] + ",";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        RingBuffer< String > ringBuffer = new RingBuffer< String >( 5 );

        for ( int i = 0; i < strArr.length; ++i ) {
            ringBuffer.enqueue( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + ringBuffer.toString() );

        StdOut.println( "DEBUG: " + ringBuffer.dequeue() );

        StdOut.println( "DEBUG: " + ringBuffer.toString() );
    }
}
