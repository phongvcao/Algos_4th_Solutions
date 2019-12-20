package com.company;
import edu.princeton.cs.algs4.*;

import java.util.ArrayList;

public class SeparateChainingHashSTEagerDelete< Key, Value > {

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

    private int M;
    private int N;
    private ArrayList< Node > st;

    public SeparateChainingHashSTEagerDelete() {
        this( 997 );
    }

    public SeparateChainingHashSTEagerDelete( int M ) {
        this.M = M;
        this.st = new ArrayList< Node >();
        for ( int i = 0; i < M; ++i ) {
            this.st.add( i, null );
        }
    }

    public void put( Key key, Value value ) {
        Node ptr = this.st.get( hash( key ) );
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
            st.set( hash( key ), new Node( key, value ) );
        }
    }

    public Value get( Key key ) {
        Node ptr = this.st.get( hash( key ) );
        while ( ptr != null ) {
            if ( ptr.key.hashCode() == key.hashCode() )  {
                return ptr.value;
            }
            ptr = ptr.next;
        }
        return null;
    }

    private int hash( Key key ) {
        return ( key.hashCode() % 0x7fffffff ) % M;
    }

    public String toString() {
        String rv = "";
        for ( int i = 0; i < M; ++i ) {
            Node ptr = this.st.get( i );
            if ( ptr != null ) {
                rv += "\n" + i + " : ";
            }
            while ( ptr != null ) {
                rv += ptr.toString();
                ptr = ptr.next;
            }
        }
        return rv;
    }

    public void delete( Key key ) {
        Node ptr = this.st.get( hash( key ) );
        Node beforePtr = null;
        while ( ptr != null ) {
            if ( ptr.key.hashCode() == key.hashCode() ) {
                if ( beforePtr != null ) {
                    beforePtr.next = ptr.next;
                    break;
                } else {
                    this.st.set( hash( key ), null );
                    break;
                }
            }

            beforePtr = ptr;
            ptr = ptr.next;
        }
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        SeparateChainingHashSTEagerDelete< String, String > hashST = new SeparateChainingHashSTEagerDelete< String, String >();
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
