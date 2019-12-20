package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class SortByReverseDomain {

    private static class Domain implements Comparable< Domain > {
        private String value = null;
        private String valueReversed = null;

        public Domain( String domainStr ) {
            this.value = domainStr;
            String[] domainArr = domainStr.split( "\\." );
            this.valueReversed = domainArr[ domainArr.length - 1 ];
            for ( int i = domainArr.length - 2; i >= 0; --i ) {
                this.valueReversed += "." + domainArr[ i ];
            }
        }

        public int compareTo( Domain other ) {
            return this.valueReversed.compareTo( other.valueReversed );
        }

        public String toString() {
            return this.valueReversed + " " + this.value;
        }
    }

    public static void quickSort( Domain[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Domain[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static int partition( Domain[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Domain pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static boolean less( Domain a, Domain b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Domain[] a, int i, int j ) {
        Domain temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void main( String[] args ) {
        String[] strArr = { "toi", "la", "phong", "abc", "cdb", "aco", "cs", "edu", "princeton", "com", "google" };
        ArrayList< Domain > domainList = new ArrayList< Domain >();

        for ( int i = 0; i < strArr.length - 2; ++i ) {
            domainList.add( new Domain( strArr[ i ] + "." + strArr[ i + 1 ] + "." + strArr[ i + 2 ] ) );
        }

        Domain[] domainArr = new Domain[ domainList.size() ];
        for ( int i = 0; i < domainArr.length; ++i ) {
            domainArr[ i ] = domainList.get( i );
        }

        StdOut.println( "DEBUG: domainArr (BEFORE): " + java.util.Arrays.toString( domainArr ) );

        quickSort( domainArr );

        StdOut.println( "DEBUG: domainArr (AFTER): " + java.util.Arrays.toString( domainArr ) );
    }
}
