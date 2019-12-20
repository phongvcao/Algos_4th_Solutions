package com.company;
import java.util.Arrays;
import java.math.BigInteger;

import edu.princeton.cs.algs4.*;

public class BigIntegerThreeSum {
    public static int count( int[] a ) {
        Arrays.sort( a );
        int N = a.length;
        int cnt = 0;
        for ( int i = 0; i < N; ++i ) {
            for ( int j = i + 1; j < N; ++j ) {
                if ( BinarySearch.rank( - a[ i ] - a[ j ], a ) > j ) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }

    public static int countBigInteger( int[] a ) {
        int N = a.length;
        int cnt = 0;
        BigInteger bigInt;

        for ( int i = 0; i < N; ++i ) {
            for ( int j = i + 1; j < N; ++j ) {
                for ( int k = j + 1; k < N; ++k ) {
                    bigInt = BigInteger.valueOf( a[ i ] );
                    bigInt = bigInt.add( BigInteger.valueOf( a[ j ] ) );
                    bigInt = bigInt.add( BigInteger.valueOf( a[ k ] ) );

                    if ( bigInt.intValue() == 0 ) {
                        ++cnt;
                    }
                }
            }
        }

        return cnt;
    }

    public static void main( String[] args ) {
        // int[] a = In.readInts( args[ 0 ] );
        int[] a = { -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
        StdOut.println( count( a ) );
        StdOut.println( countBigInteger( a ) );
    }
}
