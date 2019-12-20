package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;

public class SeparateChainingHashSTKeys< Key, Value > {

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
            rv += " | \n";
            return rv;
        }
    }

    private ArrayList< Node > st;
    private int M;
    private int N;

    public SeparateChainingHashSTKeys() {
        this( 997 );
    }

    public SeparateChainingHashSTKeys( int M ) {
        this.M = M;
        st = new ArrayList< Node >( M );
        for ( int i = 0; i < M; ++i ) {
            st.add( i, null );
        }
    }

    public void put( Key key, Value value ) {
        Node ptr = st.get( hash( key ) );
        if ( ptr != null ) {
            while ( ptr.next != null ) {
                if ( ptr.key.equals( key ) ) {
                    ptr.value = value;
                }
                ptr = ptr.next;
            }
            ptr.next = new Node( key, value );
        } else {
            st.set( hash( key ), new Node( key, value ) );
            ++N;
        }
    }

    private int hash( Key key ) {
        return ( key.hashCode() & 0x7fffffff ) % M;
    }

    public Value get( Key key ) {
        Node ptr = st.get( hash( key ) );
        while ( ptr != null ) {
            if ( ptr.key.equals( key ) ) {
                return ptr.value;
            }
            ptr = ptr.next;
        }
        return null;
    }

    public void delete( Key key ) {
        Node ptr = st.get( hash( key ) );
        Node beforePtr = null;
        while ( ptr != null ) {
            if ( ptr.key.equals( key ) ) {
                if ( beforePtr != null ) {
                    beforePtr.next = ptr.next;
                } else {
                    st.set( hash( key ), null );
                }
            }
            beforePtr = ptr;
            ptr = ptr.next;
        }
    }

    public Iterable< Key > keys() {
        Queue< Key > queue = new Queue< Key >();
        for ( int i = 0; i < M; ++i ) {
            Node ptr = st.get( i );
            while ( ptr != null ) {
                queue.enqueue( ptr.key );
                ptr = ptr.next;
            }
        }
        return queue;
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
        SeparateChainingHashSTKeys< String, String > hashST = new SeparateChainingHashSTKeys< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
        StdOut.println( "DEBUG: hashST.keys(): " + hashST.keys() );
        hashST.delete( "A" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( A )): " + hashST.toString() );
        hashST.delete( "S" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( S )): " + hashST.toString() );
        hashST.delete( "X" );
        StdOut.println( "DEBUG: hashST: (AFTER delete( X )): " + hashST.toString() );
    }
}
