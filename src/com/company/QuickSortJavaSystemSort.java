package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortJavaSystemSort {

    public static final int INSERTION_SORT_CUTOFF = 4;
    public static final int MEDIAN_MIN_SIZE = 9;

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sort( Comparable[] a ) {
        sort( a, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        if ( high - low + 1 <= INSERTION_SORT_CUTOFF ) {
            Insertion.sort( a, low, high + 1 );
            return;
        }

        int j = partition( a, low, high );
        sort( a, low, j - 1 );
        sort( a, j + 1, high );
    }

    public static int median3( Comparable[] a, int i, int j, int k ) {
        if ( less( a[ i ], a[ j ] ) ) {
            if ( less( a[ j ], a[ k ] ) ) {
                return j;
            } else if ( less( a[ k ], a[ i ] ) ) {
                return i;
            } else {
                return k;
            }
        } else {
            if ( less( a[ i ], a[ k ] ) ) {
                return i;
            } else if ( less( a[ k ], a[ j ] ) ) {
                return j;
            } else {
                return k;
            }
        }
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;

        if ( high - low + 1 >= MEDIAN_MIN_SIZE ) {
            int pivotIdx = median3( a,
                                    median3( a, low, low + 1, low + 2 ),
                                    median3( a, low + 3, low + 4, low + 5 ),
                                    median3( a, low + 6, low + 7, low + 8 ) );
            exchange( a, low, pivotIdx );
        }
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }

        exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
