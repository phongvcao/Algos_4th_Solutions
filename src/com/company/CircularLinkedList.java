package com.company;
import edu.princeton.cs.algs4.*;

public class CircularLinkedList< Item > {

    private int N = 0;
    private Node last = null;

    private class Node {
        Item item = null;
        Node next = null;
    }

    public CircularLinkedList() {

    }

    public void insert( Item item ) {
        Node newNode = new Node();
        newNode.item = item;

        if ( isEmpty() ) {
            last = newNode;
            last.next = last;
        } else {
            Node first = last.next;
            last.next = newNode;
            last = newNode;
            last.next = first;
        }

        ++N;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public String toString() {
        String rv = "{";
        Node ptr = last.next;

        for ( int i = 0; i < N; ++i ) {
            rv += " " + ptr.item + "( next: " + ptr.next.item + " )" + ",";
            ptr = ptr.next;
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        CircularLinkedList< String > cirList = new CircularLinkedList< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            cirList.insert( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + cirList.toString() );
    }
}
