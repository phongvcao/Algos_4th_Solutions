package com.company;
import edu.princeton.cs.algs4.*;

public class OrderedSequentialSearchST< Key extends Comparable< Key >, Value > {

    private class Node {
        Key key = null;
        Value value = null;
        Node next = null;
    }

    private Node head = null;
    private int N = 0;

    public OrderedSequentialSearchST() {
        // Do nothing
    }

    public int rank( Key key ) {
        Node ptr = head;
        int rankCount = 0;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( key ) < 0 ) {
                ++rankCount;
            }
            ptr = ptr.next;
        }
        return rankCount;
    }

    public Value get( Key key ) {
        Value rv = null;
        Node ptr = head;
        while ( ptr != null ) {
            if ( ptr.key.compareTo( key ) == 0 ) {
                return ptr.value;
            }
            ptr = ptr.next;
        }

        return rv;
    }

    public void put( Key key, Value value ) {
        Node ptr = head;
        Node beforePtr = null;
        Node newNode = new Node();
        newNode.key = key;
        newNode.value = value;

        while ( ( ptr != null ) && ( ptr.key.compareTo( key ) < 0 ) ) {
            beforePtr = ptr;
            ptr = ptr.next;
        }

        if ( beforePtr != null ) {
            beforePtr.next = newNode;
            newNode.next = ptr;
        } else {
            newNode.next = head;
            head = newNode;
        }
        ++N;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toString() {
        Node ptr = head;
        String rv = "";

        while ( ptr != null ) {
            rv += " | " + ptr.key + " : " + ptr.value + " | ";
            ptr = ptr.next;
        }

        return rv;
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5 };
        Double[] doubleArr = { 4.33, 4.00, 3.67, 3.33, 3.00, 2.67, 2.33, 2.00, 1.67, 1.00, 0.00 };
        OrderedSequentialSearchST< Integer, Double > st = new OrderedSequentialSearchST< Integer, Double >();
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], doubleArr[ i ] );
        }

        StdOut.println( "DEBUG: st (BEFORE): " + st.toString() );
    }
}
