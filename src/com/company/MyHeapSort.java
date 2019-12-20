package com.company;
import edu.princeton.cs.algs4.*;

public class MyHeapSort {

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sink( Comparable[] a, int i, int size ) {
        while ( 2 * i <= size ) {
            int j = 2 * i;
            if ( j < size && less( a[ j - 1 ], a[ j ] ) ) ++j;
            if ( ! less( a[ i - 1 ], a[ j - 1 ] ) ) break;
            exchange( a, i, j );
            i = j;
        }
    }

    public static void sort( Comparable[] a, int size ) {
        for ( int k = size / 2; k >= 1; k-- ) {
            // Construct max-heap by looping in reverse & sink down elements
            sink( a, k, size );
        }

        while ( size > 1 ) {
            // Remove the maximum & put it at the end
            exchange( a, 1, size-- );
            sink( a, 1, size );
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr, intArr.length );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
