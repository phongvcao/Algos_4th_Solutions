package com.company;
import edu.princeton.cs.algs4.*;

public class HeapSort4AryTree {

    public static boolean less( Comparable[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static void sort4Ary( Comparable[] a ) {
        for ( int i = a.length / 4; i >= 1; --i ) {
            sink4Ary( a, i, a.length );
        }

        int N = a.length;
        while ( N > 1 ) {
            exchange( a, 1, N-- );
            sink4Ary( a, 1, N );
        }
    }

    public static void swim( Comparable[] a, int k ) {

    }

    public static void sink4Ary( Comparable[] a, int k, int N ) {
        while ( 4 * k - 2 <= N ) {
            int maxChildIndex = getMaxChildIndex( a, k, N );
            if ( ! less( a, k, maxChildIndex ) ) break;
            exchange( a, k, maxChildIndex );
            k = maxChildIndex;
        }
    }

    public static int getMaxChildIndex( Comparable[] a, int i, int N ) {
        int maxChildIndex = 4 * i - 2;
        if ( 4 * i - 2 < N && less( a, maxChildIndex, 4 * i - 1 ) ) {
            maxChildIndex = 4 * i - 1;
        }

        if ( 4 * i - 1 < N && less( a, maxChildIndex, 4 * i ) ) {
            maxChildIndex = 4 * i;
        }

        if ( 4 * i < N && less( a, maxChildIndex, 4 * i + 1 ) ) {
            maxChildIndex = 4 * i + 1;
        }

        return maxChildIndex;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort4Ary( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
