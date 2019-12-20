package com.company;
import edu.princeton.cs.algs4.*;

public class QueueCircularLinkedList< Item > {
    private Node last;

    // size of linked list
    private int N = 0;

    private class Node {
        Item item = null;
        Node next = null;
    }

    public void add( Item item ) {
        if ( isEmpty() ) {
            last = new Node();
            last.item = item;
        } else {
            // First create the new node
            Node newNode = new Node();
            newNode.item = item;
            Node first = last.next;

            if ( first != null ) {
                newNode.next = first;
                last.next = newNode;
            } else {
                last.next = newNode;
                newNode.next = last;
            }
            // last = newNode;
            // if ( first != null ) {
            //    last.next = first;
            // }
        }
        ++N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public String toString( int count ) {
        String rv = "{";

        Node ptr = last;
        while ( ( ptr != null ) && ( count >= 1 ) ) {
            // DEBUG
            // StdOut.println( "DEBUG: " + ptr.item );
            // END OF DEBUG

            rv += " " + ptr.item + ",";
            ptr = ptr.next;
            --count;
        }
        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        QueueCircularLinkedList< String > linkedList = new QueueCircularLinkedList< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            linkedList.add( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + linkedList.toString( 10 ) );
        StdOut.println( "DEBUG: " + linkedList.toString( 20 ) );
    }
}
