package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortFasterMerge {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        sort( a, aux, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return;
        int mid = ( low + high ) / 2;

        sort( a, aux, low, mid );
        sort( a, aux, mid + 1, high );
        merge( a, aux, low, mid, high );
    }

    public static void merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        for ( int k = low; k <= mid; ++k ) {
            aux[ k ] = a[ k ];
        }

        for ( int k = mid + 1; k <= high ; ++k ) {
            aux[ mid + 1 + high - k ] = a[ k ];
        }

        int i = low;
        int j = high;

        for ( int k = low; k <= high; ++k ) {
            if ( i > j ) break;
            if ( less( aux[ j ], aux[ i ] ) ) {
                a[ k ] = aux[ j-- ];
            } else {
                a[ k ] = aux[ i++ ];
            }
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        sort( intArr );

        StdOut.println( "DEBUG: " + java.util.Arrays.toString( intArr ) );
    }
}
