package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortImproved {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static String toString( Comparable[] a, int low, int high ) {
        String rv = "{ ";

        for ( int i = low; i <= high; ++i ) {
            rv += " " + a[ i ] + ",";
        }

        rv += " }";
        return rv;
    }

    public static void insertionSort( Comparable[] a, int low, int high ) {

        // StdOut.println( "DEBUG: insertionSort (BEFORE): " + toString( a, low, high ) );

        for ( int i = low; i <= high; ++i ) {
            for ( int j = i; j > low && less( a[ j ], a[ j - 1 ] ); --j ) {
                exchange( a, j, j - 1);
            }
        }

        // StdOut.println( "DEBUG: insertionSort (AFTER): " + toString( a, low, high ) );
    }

    public static void sort( Comparable[] a ) {
        // Improvement #3 - Eliminate the copy to the auxiliary array on merge
        Comparable[] aux = a.clone();
        sort( aux, a, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return;

        // Improvement #1 - InsertionSort() for small array
        if ( high - low <= 5 ) {
            insertionSort( aux, low, high );
            return;
        }

        int mid = ( low + high ) / 2;

        // Improvement #3 - Eliminate the copy to the auxiliary array on merge
        // StdOut.println( "DEBUG: sort (BEFORE): " + toString( aux, low, mid ) );
        sort( aux, a, low, mid );
        // StdOut.println( "DEBUG: sort (AFTER): " + toString( aux, low, mid ) );
        sort( aux, a, mid + 1, high );

        // Improvement #2 - Skip the merge if the array is already in order
        if ( a[ mid ].compareTo( a[ mid + 1 ] ) <= 0 ) {
            System.arraycopy( a, low, aux, low, high - low + 1 );
            return;
        }

        merge( a, aux, low, mid, high );
    }

    public static void merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                aux[ k ] = a[ j++ ];
            } else if ( j > high ) {
                aux[ k ] = a[ i++ ];
            } else if ( less( a[ j ], a[ i ] ) ) {
                aux[ k ] = a[ j++ ];
            } else {
                aux[ k ] = a[ i++ ];
            }
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11 };

        sort( intArr );
        // insertionSort( intArr, 0, intArr.length - 1 );

        // StdOut.println( "DEBUG: " + java.util.Arrays.toString( intArr ) );
    }
}
