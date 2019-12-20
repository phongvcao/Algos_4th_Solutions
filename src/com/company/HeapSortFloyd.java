package com.company;
import edu.princeton.cs.algs4.*;

public class HeapSortFloyd {

    public static void sink( Comparable[] a, int k, int N ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, k, j ) ) break;
            exchange( a, k, j );
            k = j;
        }
    }

    public static void sinkToTheBottomAndSwim( Comparable[] a, int k, int N ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, k, j ) ) break;
            exchange( a, k, j );
            k = j;
        }
        swim( a, k );
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static boolean less( Comparable[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void swim( Comparable[] a, int k ) {
        while ( k > 1 && less( a, k / 2, k ) ) {
            exchange( a, k / 2, k );
            k /= 2;
        }
    }

    public static void sort( Comparable[] a ) {
        int N = a.length;
        // Construct max heap
        for ( int i = N / 2; i >= 1; --i ) {
            sink( a, i, a.length );
        }

        StdOut.println( "DEBUG: intArr (DURING): " + java.util.Arrays.toString( a ) );

        // delMax() & insert() at the end
        // delMax()
        while ( N > 1 ) {
            /* exchange( a, 1, N-- );
            sink( a, 1, N ); */
            exchange( a, 1, N-- );
            sinkToTheBottomAndSwim( a, 1, N );
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
