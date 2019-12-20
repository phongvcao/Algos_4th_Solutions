package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortNonStaticAux {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        sort( a, 0, a.length - 1, aux );
    }

    public static void sort( Comparable[] a, int low, int high, Comparable[] aux ) {
        if ( low >= high ) return;
        int mid = ( low + high ) / 2;

        sort( a, low, mid, aux );
        sort( a, mid + 1, high, aux );
        merge( a, low, mid, high, aux );
    }

    public static void merge( Comparable[] a, int low, int mid, int high, Comparable[] aux ) {
        int i = low;
        int j = mid + 1;

        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
            } else if ( less( aux[ j ], aux[ i ] ) ) {
                a[ k ] = aux[ j++ ];
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
