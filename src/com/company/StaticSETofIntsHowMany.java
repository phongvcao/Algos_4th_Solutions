package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class StaticSETofIntsHowMany {
    private int[] a;
    private int[] count;

    public StaticSETofIntsHowMany( int[] keys ) {
        a = new int[ keys.length ];
        count = new int[ keys.length ];
        Arrays.fill( count, 0 );

        for ( int i = 0; i < keys.length; ++i ) {
            a[ i ] = keys[ i ];
            ++count[ a[ i ] ];
        }
        Arrays.sort( a );
    }

    public boolean contains( int key ) {
        return rank( key ) != -1;
    }

    public int howMany( int key ) {
        int lo = 0;
        int hi = a.length - 1;

        while ( lo < hi ) {
            int mid = lo + ( hi - lo ) / 2;
            if ( key < a[ mid ] ) hi = mid - 1;
            else if ( key > a[ mid ] ) lo = mid + 1;
            else {
                // ++count;

                /* if ( a[ lo ] == key ) {
                    lo = mid + 1;
                } else if ( a[ hi ] == key ) {
                    hi = mid - 1;
                } */

                /* StdOut.println( "DEBUG: lo: " + lo + "; hi: " + hi + "; a[ lo ]: " + a[ lo ] + "; a[ hi ]: " + a[ hi ] );
                StdOut.println( "DEBUG: a: " + java.util.Arrays.toString( a ) ); */

                /* if ( ( hi == mid ) || ( lo == mid ) ) {
                    break;
                } */

                return count[ a[ mid ] ];
            }
        }

        return 0;
    }

    private int rank( int key ) {
        int lo = 0;
        int hi = a.length - 1;

        while ( lo < hi ) {
            int mid = lo + ( hi - lo ) / 2;
            if ( key < a[ mid ] ) hi = mid - 1;
            else if ( key > a[ mid ] ) lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 2, 3, 3 };

        StaticSETofIntsHowMany staticSet = new StaticSETofIntsHowMany( intArr );
        // StdOut.println( "DEBUG: howMany: " + staticSet.howMany( 0 ) );
        StdOut.println( "DEBUG: howMany: " + staticSet.howMany( 3 ) );
        // StdOut.println( "DEBUG: howMany: " + staticSet.rank( 0 ) );
    }
}
