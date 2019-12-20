package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortByMe {

    public static void sortByMe( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        int mid = ( low + high ) / 2;

        StdOut.println( "DEBUG: low: " + low + " ; mid: " + mid + " ; high: " + high );

        sortByMe( a, low, mid );
        sortByMe( a, mid + 1, high );
        mergeByMe( a, low, mid, high );
    }

    public static void mergeByMe( Comparable[] a, int low, int mid, int high ) {
        int index = 0;
        Comparable[] aux = new Comparable[ a.length ];

        StdOut.println( "DEBUG: mergeByMe(): low: " + low + " ; mid: " + mid + "; high: " + high );
        StdOut.println( "DEBUG: mergeByMe(): aux.length: " + aux.length + " ; a.length: " + a.length );

        // Copy a to aux
        for ( int i = low; i <= high; ++i ) {
            StdOut.println( "DEBUG: mergeByMe(): i: " + i + " ; low: " + low + "; i - low: " + ( i - low ) );
            aux[ i ] = a[ i ];
        }

        StdOut.println( "DEBUG: mergeByMe() ( 1 ): aux.length: " + aux.length + " ; a.length: " + a.length );

        int leftIndex = low;
        int rightIndex = mid;

        while ( ( leftIndex < mid ) && ( rightIndex < high ) ) {
            StdOut.println( "DEBUG: mergeByMe() WHILE: index: " + index + " ; leftIndex: " + leftIndex +
                            "; rightIndex: " + rightIndex );
            if ( aux[ leftIndex ].compareTo( aux[ rightIndex ] ) <= 0 ) {
                a[ index++ ] = aux[ leftIndex++ ];
            } else if ( aux[ leftIndex ].compareTo( aux[ rightIndex ] ) > 0 ) {
                a[ index++ ] = aux[ rightIndex++ ];
            }
        }
        StdOut.println( "DEBUG: mergeByMe() ( 2 ): aux.length: " + aux.length + " ; a.length: " + a.length );

        if ( leftIndex == mid ) {
            // Move the rest of right part to aux
            while ( rightIndex <= high ) {
                a[ index++ ] = aux[ rightIndex++ ];
            }
        }
        StdOut.println( "DEBUG: mergeByMe() ( 3 ): aux.length: " + aux.length + " ; a.length: " + a.length );

        if ( rightIndex == high ) {
            // Move the rest of
            // Move the rest of right part to aux
            while ( leftIndex <= mid ) {
                a[ index++ ] = aux[ leftIndex++ ];
            }
        }
    }

    public static String toString( Comparable[] a ) {
        String rv = "{ ";

        for ( int i = 0; i < a.length; ++i ) {
            rv += a[ i ] + " ; ";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11 };
        sortByMe( intArr, 0, intArr.length - 1 );

        StdOut.println( "DEBUG: " + toString( intArr ) );
    }
}
