package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class EqualPairsValues {

    public static int numberEqualPairsValues( int[] arr ) {
        Arrays.sort( arr );
        int count = 0;
        for ( int i = 0; i < arr.length; i++ ) {
            if ( BinarySearch.rank( arr[ i ], Arrays.copyOfRange( arr, i + 1, arr.length ) ) > -1 ) {
                ++count;
            }
        }
        return count;
    }

    public static void main( String[] args ) {
        int[] intArr = { -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 9 };

        Arrays.sort( intArr );
        StdOut.println( "DEBUG: intArr: " + java.util.Arrays.toString( intArr ) );
        StdOut.println( "DEBUG: count: " + numberEqualPairsValues( intArr ) );
    }
}
