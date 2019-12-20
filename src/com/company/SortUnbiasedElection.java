package com.company;
import edu.princeton.cs.algs4.*;
import java.util.HashMap;

public class SortUnbiasedElection {

    public static int[] charOrderArr = {};
    public static char[] charArr = { 'R', 'W', 'Q', 'O', 'J', 'M', 'V', 'A',
                                     'H', 'B', 'S', 'G', 'Z', 'X', 'N', 'T',
                                     'C', 'I', 'E', 'K', 'U', 'P', 'D', 'Y',
                                     'F', 'L' };

    public static void initializeCharOrder() {
        charOrderArr = new int[ charArr.length ];

        for ( int i = 0; i < charArr.length; ++i ) {
            charOrderArr[ charArr[ i ] - 'A' ] = i;
        }
    }

    public static int getCharOrder( char c ) {
        return charOrderArr[ c - 'A' ];
    }

    private static class Candidate implements Comparable< Candidate > {

        public String name = null;

        public Candidate( String name ) {
            this.name = name.toUpperCase();
        }

        public int compareTo( Candidate other ) {
            int index = 0;
            while ( index < this.name.length() && index < other.name.length() ) {
                 int thisCharOrder = getCharOrder( this.name.charAt( index ) );
                 int otherCharOrder = getCharOrder( other.name.charAt( index ) );

                 if ( thisCharOrder < otherCharOrder ) {
                     return -1;
                 } else if ( thisCharOrder > otherCharOrder ) {
                     return 1;
                 }

                 ++index;
            }

            int rv = 0;
            if ( index == this.name.length() && index == other.name.length() ) {
                // This and Other have same lengths & chars
                rv = 0;
            } else if ( index < this.name.length() ) {
                // This is longer than Other
                rv = 1;
            } else if ( index < other.name.length() ) {
                // Other is longer than This
                rv = -1;
            }
            return rv;
        }

        public String toString() {
            return this.name;
        }
    }

    public static void quickSort( Candidate[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Candidate[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static int partition( Candidate[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Candidate pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static boolean less( Candidate a, Candidate b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Candidate[] a, int i, int j ) {
        Candidate temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void main( String[] args ) {
        initializeCharOrder();
        Candidate[] candArr = new Candidate[ charOrderArr.length * 2 ];

        for ( int i = 0; i < charOrderArr.length; ++i ) {
            candArr[ 2 * i ] = new Candidate( (char)( 'A' + i ) + "O" );
            candArr[ 2 * i + 1 ] = new Candidate( (char)( 'A' + i ) + "OO" );
        }

        StdOut.println( "DEBUG: candArr (BEFORE): " + java.util.Arrays.toString( candArr ) );

        quickSort( candArr );

        StdOut.println( "DEBUG: candArr (AFTER): " + java.util.Arrays.toString( candArr ) );
    }
}
