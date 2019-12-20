package com.company;
import edu.princeton.cs.algs4.*;

public class GeneralizedQueueLinkedList< Item > {

    private int N = 0;

    private class Node {
        Item item = null;
        Node next = null;
    }

    private Node first = null;
    private Node last = null;

    public GeneralizedQueueLinkedList() {

    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void insert( Item x ) {
        Node newNode = new Node();
        newNode.item = x;

        if ( isEmpty() ) {
            first = newNode;
            last = newNode;
        } else {
            newNode.next = null;
            last.next = newNode;
            last = newNode;
        }

        ++N;
    }

    public Item delete( int k ) {
        Item rv = null;
        Node ptr = first;
        Node beforePtr = null;

        while ( ( ptr != null ) && ( k > 0 ) ) {
            beforePtr = ptr;
            ptr = ptr.next;
            --k;
        }

        if ( beforePtr == null ) {
            rv = ptr.item;
            ptr = null;
        } else {
            rv = ptr.item;
            beforePtr.next = ptr.next;
        }

        return rv;
    }

    public String toString() {
        String rv = "{";
        Node ptr = first;

        while ( ptr != null ) {
            rv += " " + ptr.item + ",";
            ptr = ptr.next;
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        GeneralizedQueueLinkedList< String > queue = new GeneralizedQueueLinkedList< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            queue.insert( strArr[ i ] );
        }

        StdOut.println( "DEBUG (BEFORE): " + queue.toString() );

        queue.delete( 2 );

        StdOut.println( "DEBUG (AFTER): " + queue.toString() );
    }
}
