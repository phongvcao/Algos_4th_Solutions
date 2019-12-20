package com.company;
import edu.princeton.cs.algs4.*;

public class FixedCapacityStackOfInts {

    private int[] a;
    private int N;

    public FixedCapacityStackOfInts( int cap ) {
        a = new int[ cap ];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void push( int item ) {
        a[ N++ ] = item;
    }

    public int pop() {
        return a[ --N ];
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        FixedCapacityStackOfInts stack = new FixedCapacityStackOfInts( 20 );

        for ( int i = 0; i < intArr.length; ++i ) {
            stack.push( intArr[ i ] );
        }

        while ( ! stack.isEmpty() ) {
            StdOut.println( "DEBUG: " + stack.pop() );
        }
    }
}
