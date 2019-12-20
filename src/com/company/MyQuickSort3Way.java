package com.company;
import edu.princeton.cs.algs4.*;

public class MyQuickSort3Way {

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
        int lt = low;
        int gt = high;
        int i = low + 1;
        Comparable v = a[ low ];

        while ( i <= gt ) {
            int cmp = a[ i ].compareTo( v );

            if ( cmp < 0 ) {
                exchange( a, lt++, i++ );
            } else if ( cmp > 0 ) {
                exchange( a, i, gt-- );
            } else {
                i++;
            }
        }
        sort( a, low, lt - 1 );
        sort( a, gt + 1, high );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
