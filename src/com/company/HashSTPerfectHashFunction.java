package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;
import java.util.HashSet;

public class HashSTPerfectHashFunction {

    public int hash( int k, int a, int M ) {
        return ( a * k ) % M;
    }

    public int keyToInt( char c ) {
        return c - 'A' + 1;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        HashSTPerfectHashFunction st = new HashSTPerfectHashFunction();
        for ( int m = 1; m < 100; ++m ) {
            for ( int a = 1; a < 1000; ++a ) {
                HashSet< Integer > hashSet = new HashSet< Integer >();
                for ( int i = 0; i < keyArr.length; ++i ) {
                    hashSet.add( st.hash( st.keyToInt( keyArr[ i ].charAt( 0 ) ), a, m ) );
                }
                if ( hashSet.size() == 10 ) {
                    StdOut.println( "DEBUG: m : " + m );
                    StdOut.println( "DEBUG: a : " + a );
                    return;
                }
            }
        }
    }
}
