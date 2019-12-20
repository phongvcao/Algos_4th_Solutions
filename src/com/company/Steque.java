package com.company;
import edu.princeton.cs.algs4.*;

public class Steque< Item > {
    private class DoubleNode {
        Item item = null;
        DoubleNode prev = null;
        DoubleNode next = null;
    }

    private int N = 0;

    private DoubleNode first = null;
    private DoubleNode last = null;

    public void enqueue( Item item ) {
        // Insert at the end
        DoubleNode newNode = new DoubleNode();
        newNode.item = item;

        // If the list is empty, both first and last should point to same element
        if ( last == null ) {
            last = newNode;
            first = newNode;
        } else {
            last.next = newNode;
            newNode.prev = last;
            last = newNode;
        }

        ++N;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void push( Item item ) {
        // Insert at the beginning
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

    public Item pop() {
        // Remove at the beginning
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
        Steque< String > linkedList = new Steque< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            // linkedList.enqueue( strArr[ i ] );
            linkedList.push( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );

        StdOut.println( "DEBUG: " + linkedList.pop() );

        StdOut.println( "DEBUG: " + linkedList.toString() );
    }
}
