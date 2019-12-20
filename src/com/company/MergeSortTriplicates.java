package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortTriplicates {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static boolean equals( Comparable a, Comparable b ) {
        return a.compareTo( b ) == 0;
    }

    public static Comparable[] join( Comparable[] arr1, Comparable[] arr2 ) {
        Comparable[] rv = new Comparable[ arr1.length + arr2.length ];

        System.arraycopy( arr1, 0, rv, 0, arr1.length );
        System.arraycopy( arr2, 0, rv, arr1.length, arr2.length );
        return rv;
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

    public static Comparable[] merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;
        Comparable[] dup = new Comparable[ a.length ];
        int dupIdx = 0;

        for ( int k = low; k <= high; ++k ) {
            aux [ k ] = a[ k ];
        }

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
            } else if ( less( aux[ j ], aux[ i ] ) ) {
                a[ k ] = aux[ j++ ];
            } else if ( equals( aux[ j ], aux[ i ] ) ) {
                dup[ dupIdx++ ] = aux[ i ];
                a[ k ] = aux[ i++ ];
            } else {
                a[ k ] = aux[ i++ ];
            }
        }

        Comparable[] newDup = new Comparable[ dupIdx ];
        System.arraycopy( dup, 0, newDup, 0, dupIdx );

        return newDup;
    }

    public static void main( String[] args ) {
        /* String[] strArr1 = { "24", "22", "20", "18", "16", "14", "12", "10", "11", "13", "15", "17", "19", "21", "23" };
        String[] strArr2 = { "43", "41", "39", "37", "35", "33", "31", "30", "32", "34", "36", "38", "40", "24", "22" };
        String[] strArr3 = { "53", "51", "49", "47", "45", "43", "41", "40", "42", "44", "46", "48", "50", "24", "22" }; */

        Integer[] strArr1 = { 24, 22, 20, 18, 16, 14, 12, 10, 11, 13, 15, 17, 19, 21, 23 };
        Integer[] strArr2 = { 43, 41, 39, 37, 35, 33, 31, 30, 32, 34, 36, 38, 40, 24, 22 };
        Integer[] strArr3 = { 53, 51, 49, 47, 45, 43, 41, 40, 42, 44, 46, 48, 50, 24, 22 };

        // StdOut.println( "DEBUG: Joint strArr1 & strArr2: " + java.util.Arrays.toString( join( strArr1, strArr2 ) ) );

        // TODO: Sort each strArr, then:
        // - Merge strArr1 & strArr2, return duplicated elements (dupArr1)
        // - Merge strArr3 & dupArr1, return duplicated elements (dupArr2)
        // - Print out dupArr2

        StdOut.println( "DEBUG: strArr1 (BEFORE): " + java.util.Arrays.toString( strArr1 ) );
        StdOut.println( "DEBUG: strArr2 (BEFORE): " + java.util.Arrays.toString( strArr2 ) );
        StdOut.println( "DEBUG: strArr3 (BEFORE): " + java.util.Arrays.toString( strArr3 ) );

        sort( strArr1 );
        sort( strArr2 );
        sort( strArr3 );

        StdOut.println( "DEBUG: strArr1 (AFTER): " + java.util.Arrays.toString( strArr1 ) );
        StdOut.println( "DEBUG: strArr2 (AFTER): " + java.util.Arrays.toString( strArr2 ) );
        StdOut.println( "DEBUG: strArr3 (AFTER): " + java.util.Arrays.toString( strArr3 ) );

        Comparable[] aux = new Comparable[ strArr1.length + strArr2.length ];
        Comparable[] dupArr1 = merge( join( strArr1, strArr2 ), aux, 0, strArr1.length - 1, strArr1.length + strArr2.length - 1 );

        StdOut.println( "DEBUG: dupArr1 (AFTER): " + java.util.Arrays.toString( dupArr1 ) );

        aux = new Comparable[ dupArr1.length + strArr3.length ];
        Comparable[] dupArr2 = merge( join( dupArr1, strArr3 ), aux, 0, dupArr1.length - 1, dupArr1.length + strArr3.length - 1 );

        StdOut.println( "DEBUG: dupArr2 (AFTER): " + java.util.Arrays.toString( dupArr2 ) );
    }
}
