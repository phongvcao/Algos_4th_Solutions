package com.company;
import edu.princeton.cs.algs4.*;

public class SequentialSearchST< Key extends Comparable< Key >, Value > {

    private class Node {
        Key key = null;
        Value value = null;
        Node next = null;
    }

    private Node head = null;
    private int N = 0;

    public SequentialSearchST() {
        // Not implemented
    }

    public int rank( Key key ) {
        int rankCount = 0;
        Node ptr = head;
        while ( ptr != null ) {
            if ( less( ptr.key, key ) ) {
                ++rankCount;
            }
            ptr = ptr.next;
        }
        return rankCount;
    }

    private boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public void put( Key key, Value value ) {
        Node ptr = head;
        Node beforePtr = null;
        Node newNode = new Node();
        newNode.key = key;
        newNode.value = value;

        while ( ptr != null ) {
            beforePtr = ptr;
            ptr = ptr.next;
        }

        if ( beforePtr != null ) {
            newNode.next = ptr;
            beforePtr.next = newNode;
        } else {
            newNode.next = head;
            head = newNode;
        }
        ++N;
    }

    public int size() {
        return N;
    }

    public int size( Key low, Key high ) {
        if ( low.compareTo( high ) == 1 ) return 0;
        Node ptr = head;
        int size = 0;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( low ) >= 0 && ptr.key.compareTo( high ) <= 0 ) {
                ++size;
            }
            ptr = ptr.next;
        }
        return size;
    }

    public Value get( Key key ) {
        Node ptr = head;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( key ) == 0 ) {
                return ptr.value;
            }
            ptr = ptr.next;
        }
        return null;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public void delete( Key key ) {
        Node ptr = head;
        Node beforePtr = null;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( key ) == 0 ) {
                break;
            }
            beforePtr = ptr;
            ptr = ptr.next;
        }

        if ( beforePtr != null ) {
            if ( ptr != null ) {
                beforePtr.next = ptr.next;
                --N;
            }
        } else {
            if ( ptr != null && ptr.key.compareTo( key ) == 0 ) {
                head = null;
                --N;
            }
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) == 1 ) return q;
        Node ptr = head;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( low ) >= 0 && ptr.key.compareTo( high ) <= 0 ) {
                q.enqueue( ptr.key );
            }
            ptr = ptr.next;
        }
        return q;
    }

    Iterable< Key > keys() {
        Queue< Key > q = new Queue< Key >();
        Node ptr = head;
        while ( ptr != null ) {
            q.enqueue( ptr.key );
            ptr = ptr.next;
        }
        return q;
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        SequentialSearchST< Integer, Integer > seqST = new SequentialSearchST< Integer, Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            seqST.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: seqST: \n" + seqST.toString() );
        StdOut.println( "DEBUG: seqST.size(): \n" + seqST.size() );
        StdOut.println( "DEBUG: seqST.size( 8, 12 ): \n" + seqST.size( 8, 12 ) );
        seqST.delete( 10 );
        StdOut.println( "DEBUG: seqST.size( 8, 12 ): \n" + seqST.size( 8, 12 ) );
        StdOut.println( "DEBUG: seqST.keys( 8, 12 ): \n" + seqST.keys( 8, 12 ) );
        StdOut.println( "DEBUG: seqST.keys(): \n" + seqST.keys() );
    }
}
