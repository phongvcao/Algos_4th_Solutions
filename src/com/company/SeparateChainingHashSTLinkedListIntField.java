package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;

public class SeparateChainingHashSTLinkedListIntField< Key, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private Node next = null;
        private int N = 0;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N;
            if ( this.next != null ) {
                rv += " ; next : " + this.next.key;
            } else {
                rv += " ; next : null";
            }
            rv += " | ";
            return rv;
        }
    }

    private int M;
    private int N;
    private ArrayList< Node > st;

    public SeparateChainingHashSTLinkedListIntField() {
        this( 997 );
    }

    public SeparateChainingHashSTLinkedListIntField( int M ) {
        this.M = M;
        this.st = new ArrayList< Node >( M );
        for ( int i = 0; i < M; ++i ) {
            this.st.add( i, null );
        }
    }

    public void put( Key key, Value value ) {
        Node ptr = this.st.get( hash( key ) );
        if ( ptr != null ) {
            int nodesCount = 0;
            while ( ptr.next != null ) {
                if ( ptr.key.hashCode() == key.hashCode() ) {
                    ptr.value = value;
                    return;
                }
                ptr = ptr.next;
                ++nodesCount;
            }
            ptr.next = new Node( key, value, nodesCount + 1 );
        } else {
            this.st.add( hash( key ), new Node( key, value, 0 ) );
        }
    }

    public Value get( Key key ) {
        Node ptr = this.st.get( hash( key ) );
        while ( ptr != null ) {
            if ( ptr.key.hashCode() == key.hashCode() ) {
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
        for ( int i = 0; i < this.st.size(); ++i ) {
            Node ptr = this.st.get( i );
            if ( ptr != null ) {
                rv += "\n" + i + " : ";
                while ( ptr != null ) {
                    rv += ptr.toString();
                    ptr = ptr.next;
                }
            }
        }
        return rv;
    }

    public void deleteKeySizeLargerThan( int k ) {
        for ( int i = 0; i < M; ++i ) {
            Node ptr = this.st.get( i );
            while ( ptr != null && ptr.N < k ) {
                ptr = ptr.next;
            }
            if ( ptr == null ) continue;
            while ( ptr.next != null ) {
                ptr.next = ptr.next.next;
            }
        }
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        SeparateChainingHashSTLinkedListIntField< String, String > hashST = new SeparateChainingHashSTLinkedListIntField< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            hashST.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: hashST: " + hashST.toString() );
        hashST.deleteKeySizeLargerThan( 2 );
        StdOut.println( "DEBUG: hashST (AFTER deleteKeySizeLargerThan( 2 ): " + hashST.toString() );
        hashST.deleteKeySizeLargerThan( 0 );
        StdOut.println( "DEBUG: hashST (AFTER deleteKeySizeLargerThan( 0 ): " + hashST.toString() );
    }
}
