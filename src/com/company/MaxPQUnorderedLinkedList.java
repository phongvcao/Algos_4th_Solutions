package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQUnorderedLinkedList< Key extends Comparable< Key > > {

    private class Node {
        public Key value = null;
        public Node next = null;
    }

    private Node head = null;
    private int N = 0;

    public MaxPQUnorderedLinkedList() {
        // Not implemented
    }

    public void insert( Key k ) {
        Node newNode = new Node();
        newNode.value = k;

        if ( head == null ) {
            head = newNode;
        } else {
            Node ptr = head;
            while ( ptr.next != null ) {
                ptr = ptr.next;
            }
            ptr.next = newNode;
        }
        ++N;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
   }

    public String toString() {
        String rv = "{ ";
        Node ptr = head;
        while ( ptr != null ) {
            rv += ptr.value + ", ";
            ptr = ptr.next;
        }
        rv += "}";
        return rv;
    }

    public String toStringDelMax() {
        String rv = "{ ";
        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }
        rv += "}";
        return rv;
    }

    public Key delMax() {
        Key max = head.value;
        Node ptr = head;
        Node maxPtr = head;
        Node maxBeforePtr = null;

        while ( ptr.next != null ) {
            if ( less( max, ptr.next.value ) ) {
                max = ptr.next.value;
                maxBeforePtr = ptr;
                maxPtr = ptr.next;
            }
            ptr = ptr.next;
        }

        if ( maxBeforePtr != null ) {
            maxBeforePtr.next = maxPtr.next;
        } else {
            head = maxPtr.next;
        }
        --N;
        return max;
    }

    private boolean less( Key a, Key b ) {
        return a.compareTo( b ) == -1;
    }

    public Key max() {
        Key max = head.value;
        Node ptr = head;

        while ( ptr != null ) {
            if ( less( max, ptr.value ) ) {
                max = ptr.value;
            }
            ptr = ptr.next;
        }
        return max;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQUnorderedLinkedList< Integer > maxPQ = new MaxPQUnorderedLinkedList< Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
