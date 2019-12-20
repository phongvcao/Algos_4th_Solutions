package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortBestCase {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void bestCase( Comparable[] a ) {
        bestCase( a, 0, a.length - 1 );
    }

    public static void bestCase( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;
        int mid = low + ( high - low ) / 2;

        bestCase( a, low, mid - 1 );
        bestCase( a, mid + 1, high );
        exchange( a, low, mid );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };


        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        bestCase( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
