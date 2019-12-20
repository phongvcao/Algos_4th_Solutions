package com.company;
import edu.princeton.cs.algs4.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Frequency {

    private static class Number {
        public Integer value = null;
        public int frequency = 0;

        public Number( Integer value ) {
            this.value = value;
        }

        public int compareTo( Number other ) {
            int rv = 0;
            if ( this.frequency < other.frequency ) {
                rv = -1;
            } else if ( this.frequency > other.frequency ) {
                rv = 1;
            } else {
                rv = 0;
            }

            return rv;
        }

        public String toString() {
            return " | " + value + " : " + frequency + " | ";
        }
    }

    public static void quickSort( Number[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Number[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static int partition( Number[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Number pivot = a[ low ];

        while ( true ) {
            while ( less( pivot, a[ ++i ] ) ) if ( i == high ) break;
            while ( less( a[ --j ], pivot ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }

        exchange( a, low, j );
        return j;
    }

    public static boolean less( Number a, Number b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Number[] a, int i, int j ) {
        Number temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 14, 12, 12, 10, 10, 8, 8, 6, 6, 4, 4, 2, 2, 0, 0, 1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13 };
        HashMap< Integer, Integer > hashMap = new HashMap< Integer, Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            if ( hashMap.containsKey( intArr[ i ] ) ) {
                hashMap.put( intArr[ i ], hashMap.get( intArr[ i ] ) + intArr[ i ] );
            } else {
                hashMap.put( intArr[ i ], intArr[ i ] );
            }
        }

        Number[] numArr = new Number[ hashMap.size() ];

        Iterator iter = hashMap.entrySet().iterator();
        int i = 0;
        while ( iter.hasNext() ) {
            Map.Entry< Integer, Integer > pair = ( Map.Entry< Integer, Integer > )iter.next();
            numArr[ i ] = new Number( pair.getKey() );
            numArr[ i ].frequency = pair.getValue();
            ++i;
        }

        StdOut.println( "DEBUG: numArr (BEFORE): " + java.util.Arrays.toString( numArr ) );

        quickSort( numArr );

        StdOut.println( "DEBUG: numArr (AFTER): " + java.util.Arrays.toString( numArr ) );
    }
}
