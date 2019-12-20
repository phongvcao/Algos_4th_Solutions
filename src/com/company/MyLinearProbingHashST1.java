package com.company;
import edu.princeton.cs.algs4.*;

public class MyLinearProbingHashST1< Key, Value > {

    private int N;
    private int M = 16;
    private Key[] keys;
    private Value[] values;

    public MyLinearProbingHashST1() {
        this( 16 );
    }

    public MyLinearProbingHashST1( int M ) {
        this.M = M;
        keys = ( Key[] ) new Object[ M ];
        values = ( Value[] ) new Object[ M ];
    }

    private int hash( Key key ) {
        return ( key.hashCode() & 0x7fffffff ) % M;
    }

    private void resize( int cap ) {
        MyLinearProbingHashST1< Key, Value > t;
        t = new MyLinearProbingHashST1< Key, Value >( cap );
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != null ) {
                t.put( keys[ i ], values[ i ] );
            }
        }
        keys = t.keys;
        values = t.values;
        M = t.M;
    }

    public void put( Key key, Value value ) {
        if ( N >= M / 2 ) resize( 2 * M );
        int i;
        for ( i = hash( key ); keys[ i ] != null; i = ( i + 1 ) % M ) {
            if ( keys[ i ].equals( key ) ) {
                values[ i ] = value;
                return;
            }
        }
        keys[ i ] = key;
        values[ i ] = value;
        ++N;
    }

    public Value get( Key key ) {
        for ( int i = hash( key ); keys[ i ] != null; i = ( i + 1 ) % M ) {
            if ( keys[ i ].equals( key ) ) {
                return values[ i ];
            }
        }
        return null;
    }

    public String toString() {
        String rv = "";
        for ( int i = 0; i < M; ++i ) {
            if ( keys[ i ] != null ) {
                rv += "\n" + i + " : | " + keys[ i ] + " : " + values[ i ] + " | ";
            }
        }
        return rv;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        MyLinearProbingHashST1< String, String > hashST = new MyLinearProbingHashST1< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }
        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
    }
}
