package com.company;
import edu.princeton.cs.algs4.*;
import edu.princeton.cs.algs4.SequentialSearchST;

import java.util.Iterator;

public class MySeparateChainingHashST1< Key, Value > {

    private int N;
    private int M;
    private SequentialSearchST< Key, Value >[] st;

    public MySeparateChainingHashST1() {
        this( 997 );
    }

    public MySeparateChainingHashST1( int M ) {
        this.M = M;
        st = ( SequentialSearchST< Key, Value >[] ) new SequentialSearchST[ M ];
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = new SequentialSearchST();
        }
    }

    private int hash( Key key ) {
        return ( key.hashCode() & 0x7fffffff ) % M;
    }

    public Value get( Key key ) {
        return ( Value ) st[ hash( key ) ].get( key );
    }

    public void put( Key key, Value value ) {
        st[ hash( key ) ].put( key, value );
    }

    public String toString() {
        String rv = "";
        for ( int i = 0; i < M; ++i ) {
            if ( ! st[ i ].isEmpty() ) {
                rv += "\n" + i + " : ";
                Iterator< Key > iter = st[ i ].keys().iterator();
                while ( iter.hasNext() ) {
                    Key iterKey = iter.next();
                    rv += " | " + iterKey + " : " + st[ i ].get( iterKey ) + " | ";
                }
            }
        }
        return rv;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        MySeparateChainingHashST1< String, String > hashST = new MySeparateChainingHashST1< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
    }
}
