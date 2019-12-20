package com.company;
import edu.princeton.cs.algs4.*;

public class MultidimensionalSort {

    private static class Vector implements Comparable< Vector > {

        public Integer[] coordinates = null;

        public Vector( Integer[] coordinates ) {
            this.coordinates = coordinates;
        }

        public int compareTo( Vector other ) {
            int i = 0;

            while ( i < this.coordinates.length ) {
                int cmp = this.coordinates[ i ].compareTo( other.coordinates[ i ] );
                if ( cmp != 0 ) {
                    return cmp;
                }

                ++i;
            }

            return 0;
        }

        public String toString() {
            return java.util.Arrays.toString( this.coordinates );
        }
    }

    public static void quickSort( Vector[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Vector[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static int partition( Vector[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Vector pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static boolean less( Vector a, Vector b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Vector[] a, int i, int j ) {
        Vector temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void main( String[] args ) {
        Integer[][] intArr = {
                { 14, 14, 14 }, { 14, 14, 12 }, { 14, 12, 10 }, { 14, 16, 18 },
                { 12, 12, 12 }, { 12, 12, 10 }, { 12, 10, 8 }, { 12, 14, 16 },
                { 10, 10, 10 }, { 10, 10, 8 }, { 10, 8, 6 }, { 10, 12, 14 },
                { 8, 8, 8 }, { 8, 8, 6 }, { 8, 6, 4 }, { 8, 10, 12 },
        };
        Vector[] vArr = new Vector[ intArr.length ];

        for ( int i = 0; i < intArr.length; ++i ) {
            vArr[ i ] = new Vector( intArr[ i ] );
        }

        StdOut.println( "DEBUG: vArr (BEFORE): " + java.util.Arrays.toString( vArr ) );

        quickSort( vArr );

        StdOut.println( "DEBUG: vArr (AFTER): " + java.util.Arrays.toString( vArr ) );
    }
}
