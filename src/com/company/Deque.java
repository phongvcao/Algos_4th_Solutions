package com.company;
import edu.princeton.cs.algs4.*;

public class Deque< Item > {
    private class DoubleNode {
        Item item = null;
        DoubleNode prev = null;
        DoubleNode next = null;
    }

    private int N = 0;

    private DoubleNode first = null;
    private DoubleNode last = null;

    public void pushLeft( Item item ) {
        // Insert at beginning
        DoubleNode newNode = new DoubleNode();
        newNode.item = item;

        if ( first == null ) {
            first = newNode;
            last = newNode;
        } else {
            first.prev = newNode;
            newNode.next = first;
            first = newNode;
        }

        ++N;
    }

    public void pushRight( Item item ) {
        // Insert at end
        DoubleNode newNode = new DoubleNode();
        newNode.item = item;

        if ( last == null ) {
            first = newNode;
            last = newNode;
        } else {
            last.next = newNode;
            newNode.prev = last;
            last = newNode;
        }

        ++N;
    }

    public Item popLeft() {
        // Remove at beginning
        DoubleNode removedNode = first;

        if ( first.next != null ) {
            first.next.prev = null;
        }
        first = first.next;

        --N;

        if ( N <= 1 ) {
            last = first;
        }

        return removedNode.item;
    }

    public Item popRight() {
        // Remove at end
        DoubleNode removedNode = last;

        if ( last.prev != null ) {
            last.prev.next = null;
        }
        last = last.prev;

        --N;

        if ( N <= 1 ) {
            first = last;
        }

        return removedNode.item;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public String toString() {
        String rv = "{";
        DoubleNode ptr = first;
        while ( ptr != null ) {
            rv += " " + ptr.item + ",";
            ptr = ptr.next;
        }
        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        Deque< String > deque = new Deque< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            // deque.pushLeft( strArr[ i ] );
            deque.pushRight( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + deque.toString() );

        StdOut.println( "DEBUG: popLeft(): " + deque.popLeft() );

        StdOut.println( "DEBUG: " + deque.toString() );

        StdOut.println( "DEBUG: popRight(): " + deque.popRight() );

        StdOut.println( "DEBUG: " + deque.toString() );

    }
}
