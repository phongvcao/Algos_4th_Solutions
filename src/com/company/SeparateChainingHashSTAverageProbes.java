package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;

public class SeparateChainingHashSTAverageProbes< Key, Value > {

    private class Node {
        public Key key = null;
        public Value value = null;
        public Node next = null;

        public Node( Key key, Value value ) {
            this.key = key;
            this.value = value;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value;
            if ( this.next != null ) {
                rv += " ; next : " + this.next.key;
            } else {
                rv += " ; next : null";
            }
            rv += " | ";
            return rv;
        }
    }

    private ArrayList< Node > st;
    private int M;
    private int N;
    private int probesLimit;
    private int logM;

    private final int[] PRIMES = {
            1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
            32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
            8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
            536870909, 1073741789, 2147483647
    };

    public SeparateChainingHashSTAverageProbes() {
        this( 997 );
    }

    public SeparateChainingHashSTAverageProbes( int M ) {
        this.M = M;
        this.logM = ( int ) ( Math.log( M ) / Math.log( 2 ) );
        st = new ArrayList< Node >( M );
        for ( int i = 0; i < M; ++i ) {
            st.add( i, null );
        }
    }

    public SeparateChainingHashSTAverageProbes( int M, int probesLimit ) {
        this( 997 );
        this.probesLimit = probesLimit;
    }

    public void put( Key key, Value value ) {
        Node ptr = st.get( hash( key ) );
        if ( ptr != null ) {
            while ( ptr.next != null ) {
                if ( key.equals( ptr.key ) ) {
                    ptr.value = value;
                }
                ptr = ptr.next;
            }
            ptr.next = new Node( key, value );
            ++N;
        } else {
            st.set( hash( key ), new Node( key, value ) );
            ++N;
        }

        if ( getActualAverageSize() > probesLimit ) {
            resize( M * 2 );
            ++this.logM;
        }
    }

    public Value get( Key key ) {
        Node ptr = st.get( hash( key ) );
        while ( ptr != null ) {
            if ( key.equals( ptr.key ) ) {
                return ptr.value;
            }
            ptr = ptr.next;
        }
        return null;
    }

    private double getActualAverageSize() {
        return ( double ) N / ( double ) M;
    }

    private void resize( int cap ) {
        SeparateChainingHashSTAverageProbes< Key, Value > temp;
        temp = new SeparateChainingHashSTAverageProbes< Key, Value >( cap, probesLimit );
        for ( int i = 0; i < M; ++i ) {
            Node ptr = st.get( i );
            while ( ptr != null ) {
                temp.put( ptr.key, ptr.value );
                ptr = ptr.next;
            }
        }
        this.st = temp.st;
        this.M = temp.M;
    }

    public void delete( Key key ) {
        Node ptr = st.get( hash( key ) );
        Node beforePtr = null;
        while ( ptr != null ) {
            if ( ptr.key.equals( key ) ) {
                if ( beforePtr != null ) {
                    beforePtr.next = ptr.next;
                    --N;
                } else {
                    st.set( hash( key ), null );
                    --N;
                }
            }
            beforePtr = ptr;
            ptr = ptr.next;
        }

        if ( getActualAverageSize() < probesLimit ) {
            resize( M / 2 );
            --this.logM;
        }
    }

    private int hash( Key key ) {
        int hash = key.hashCode() & 0x7fffffff;
        if ( logM < 26 ) {
            hash = hash % PRIMES[ logM + 5 ];
        }
        return hash % M;
    }

    public String toString() {
        String rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            Node ptr = st.get( i );
            while ( ptr != null ) {
                rv += "\n" + i + " : " + ptr.toString();
                ptr = ptr.next;
            }
        }
        return rv;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        SeparateChainingHashSTAverageProbes< String, String > hashST = new SeparateChainingHashSTAverageProbes< String, String >( 997, 4 );
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
        hashST.delete( "A" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( A )): " + hashST.toString() );
        hashST.delete( "S" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( S )): " + hashST.toString() );
        hashST.delete( "X" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( X )): " + hashST.toString() );

    }
}
