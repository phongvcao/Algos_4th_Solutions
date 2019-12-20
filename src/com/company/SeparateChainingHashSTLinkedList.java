package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;

public class SeparateChainingHashSTLinkedList< Key, Value > {

    private int N;
    private int M;
    private ArrayList< Node > st;

    private class Node {
        private Key key = null;
        private Value value = null;
        private Node next = null;

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

    public SeparateChainingHashSTLinkedList() {
        this( 997 );
    }

    public SeparateChainingHashSTLinkedList( int M ) {
        this.M = M;
        this.st = new ArrayList< Node >( M );
        for ( int i = 0; i < M; ++i ) {
            st.add( i, null );
        }
    }

    public void put( Key key, Value value ) {
        Node ptr = st.get( hash( key ) );
        if ( ptr != null ) {
            while ( ptr.next != null ) {
                if ( ptr.key.hashCode() == key.hashCode() ) {
                    ptr.value = value;
                    return;
                }
                ptr = ptr.next;
            }
            ptr.next = new Node( key, value );
        } else {
            st.add( hash( key ), new Node( key, value ) );
        }
    }

    public Value get( Key key ) {
        Node ptr = st.get( hash( key ) );
        while ( ptr != null ) {
            if ( key.hashCode() == ptr.key.hashCode() ) {
                return ptr.value;
            }
            ptr = ptr.next;
        }
        return null;
    }

    public int hash( Key key ) {
        return ( key.hashCode() & 0x7fffffff ) % M;
    }

    public String toString() {
        String rv = "";
        for ( int i = 0; i < M; ++i ) {
            if ( st.get( i ) != null ) {
                rv += "\n" + i + " : ";
                Node ptr = st.get( i );
                while ( ptr != null ) {
                    rv += ptr.toString();
                    ptr = ptr.next;
                }
            }
        }
        return rv;
    }

    public Iterable< Key > keys() {
        Queue< Key > queue = new Queue< Key >();
        return queue;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        SeparateChainingHashSTLinkedList< String, String > hashST = new SeparateChainingHashSTLinkedList< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
    }
}
