package com.company;
import edu.princeton.cs.algs4.*;

public class MyHeapSort3 {

    public static boolean less( Comparable[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static void sink( Comparable[] a, int i, int size ) {
        while ( 2 * i <= size ) {
            int j = 2 * i;
            if ( j < size && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, i, j ) ) break;
            exchange( a, i, j );
            i = j;
        }
    }

    public static void sort( Comparable[] a, int size ) {
        for ( int i = size / 2; i >= 1; --i ) {
            sink( a, i, size );
        }

        while ( size > 1 ) {
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
