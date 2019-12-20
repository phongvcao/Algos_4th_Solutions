package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQOrderedLinkedList< Key extends Comparable< Key > > {

    private class Node {
        Key value = null;
        Node next = null;
    }

    private Node head = null;
    private int N = 0;

    public MaxPQOrderedLinkedList() {
        // Not implemented
    }

    public void insert( Key k ) {
        Node newNode = new Node();
        newNode.value = k;

        if ( head == null ) {
            head = newNode;
        } else {
            // Insert k at appropriate position
            Node ptr = head;
            Node beforePtr = null;
            while ( ptr != null && less( k, ptr.value ) ) {
                beforePtr = ptr;
                ptr = ptr.next;
            }
            newNode.next = beforePtr.next;
            beforePtr.next = newNode;
        }
        ++N;
    }

    private boolean less( Key a, Key b ) {
        return a.compareTo( b ) == -1;
    }

    public Key max() {
        Node ptr = head;
        while ( ptr.next != null ) {
            ptr = ptr.next;
        }
        return ptr.value;
    }

    public Key delMax() {
        Node ptr = head;
        Node beforePtr = null;

        while ( ptr.next != null ) {
            beforePtr = ptr;
            ptr = ptr.next;
        }

        Key max = ptr.value;

        if ( beforePtr != null ) {
            beforePtr.next = null;
        } else {
            head = null;
        }
        --N;
        return max;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
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

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQOrderedLinkedList< Integer > maxPQ = new MaxPQOrderedLinkedList< Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
