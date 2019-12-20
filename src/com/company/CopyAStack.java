package com.company;
import edu.princeton.cs.algs4.*;

public class CopyAStack< Item > {

    private Item[] array;
    private int N = 0;
    private int limit = 10;

    public CopyAStack() {
        array = ( Item[] )new Object[ limit ];
    }

    public CopyAStack( CopyAStack< Item > s ) {
        array = ( Item[] )new Object[ limit ];
        Item[] newArray = ( Item[] )new Object[ limit ];
        int idx = 0;

        while ( ! s.isEmpty() ) {
            // StdOut.println( "DEBUG: popping: " + idx );
            newArray[ idx++ ] = s.pop();
        }

        // StdOut.println( "DEBUG: N: " + N );
        // StdOut.println( "DEBUG: s.size(): " + s.size() );

        for ( int i = idx - 1; i >= 0; --i ) {
            push( newArray[ i ] );
            s.push( newArray[ i ] );
        }
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void push( Item item ) {
        if ( N < limit ) {
            array[ N++ ] = item;
        }
    }

    public Item pop() {
        Item rv = null;
        if ( ! isEmpty() ) {
            rv = array[ --N ];
            array[ N ] = null;
        }
        return rv;
    }

    public String toString() {
        String rv = "{";
        for ( int i = N - 1; i >= 0; --i ) {
            rv += " " + array[ i ] + ",";
        }
        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        CopyAStack< String > stack = new CopyAStack< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            stack.push( strArr[ i ] );
        }

        StdOut.println( "DEBUG: stack: " + stack.toString() );

        CopyAStack< String > s = new CopyAStack< String >( stack );

        StdOut.println( "DEBUG (AFTER): stack: " + stack.toString() );
        StdOut.println( "DEBUG (AFTER): s: " + s.toString() );

    }
}
