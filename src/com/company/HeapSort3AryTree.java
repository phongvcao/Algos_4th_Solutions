package com.company;
import edu.princeton.cs.algs4.*;

public class HeapSort3AryTree {

    public static boolean less( Comparable[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static void swim( Comparable[] a, int k ) {
        while ( k > 1 && less( a, k / 2, k ) ) {
            exchange( a, k / 2, k );
            k /= 2;
        }
    }

    public static void sink( Comparable[] a, int k, int N ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, k, j ) ) break;
            exchange( a, k, j );
            k = j;
        }
    }

    public static int getMaxChildIndex( Comparable[] a, int k, int N ) {
        int maxChildIndex = 3 * k - 1;

        if ( ( 3 * k < N ) && ( less( a, maxChildIndex, 3 * k ) ) ) {
            maxChildIndex = 3 * k;
        }

        if ( ( 3 * k + 1 < N ) && ( less( a, maxChildIndex, 3 * k + 1 ) ) ) {
            maxChildIndex = 3 * k + 1;
        }
        return maxChildIndex;
    }

    public static void sink3Ary( Comparable[] a, int k, int N ) {
        while ( 3 * k - 1 <= N ) {
            int maxChildIndex = getMaxChildIndex( a, k, N );
            if ( ! less( a, k, maxChildIndex ) ) break;
            exchange( a, k, maxChildIndex );
            k = maxChildIndex;
        }
    }

    public static void sort3Ary( Comparable[] a ) {
        for ( int i = a.length / 3; i >= 1; --i ) {
            sink3Ary( a, i, a.length );
        }

        int N = a.length;
        while ( N > 1 ) {
            exchange( a, 1, N-- );
            sink3Ary( a, 1, N );
        }
    }

    public static void sort( Comparable[] a ) {
        for ( int i = a.length / 2; i >= 1; --i ) {
            sink( a, i, a.length );
        }

        int N = a.length;
        while ( N > 1 ) {
            exchange( a, 1, N-- );
            sink( a, 1, N );
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        // sort( intArr );
        sort3Ary( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
