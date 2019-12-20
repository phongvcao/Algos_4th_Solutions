package com.company;
import edu.princeton.cs.algs4.*;

public class MyQuickSort1 {

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

        int left = low;
        int right = high;
        int mid = ( left + right ) / 2;
        Comparable pivot = a[ mid ];

        do {
            while ( less( a[ left ], pivot ) ) ++left;
            while ( less( pivot, a[ right ] ) ) --right;

            if ( left <= right ) {
                exchange( a, left, right );
                ++left;
                --right;
            }
        } while ( left <= right );

        sort( a, low, right );
        sort( a, left, high );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEUBG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEUBG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
