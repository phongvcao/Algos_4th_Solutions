package com.company;
import edu.princeton.cs.algs4.*;

public class LinkedListReverse< Item > {
    private class Node {
        Item item = null;
        Node next = null;
    }

    private int N = 0;

    public Node first;

    public void add( Item item ) {
        Node newNode = new Node();
        newNode.item = item;
        newNode.next = first;
        first = newNode;
        ++N;
    }

    public Node reverse( Node x ) {
        Node firstNode = x;
        Node reverseNode = null;
        Node secondNode = firstNode.next;

        while ( firstNode != null ) {
            secondNode = firstNode.next;
            firstNode.next = reverseNode;
            reverseNode = firstNode;
            firstNode = secondNode;
        }
        first = reverseNode;

        return reverseNode;
    }

    public Node reverseRecursively( Node firstNode, Node secondNode, Node reverseNode ) {
        if ( firstNode == null ) {
            first = reverseNode;
            return reverseNode;
        }

        secondNode = firstNode.next;
        firstNode.next = reverseNode;
        // reverseNode = firstNode;
        // firstNode = secondNode;

        return reverseRecursively( secondNode, firstNode.next, firstNode );
    }

    public Node reverseRecursively_2( Node firstNode ) {
        if ( firstNode == null ) return null;
        if ( firstNode.next == null ) {
            first = firstNode;
            return firstNode;
        }
        Node secondNode = firstNode.next;
        Node rest = reverseRecursively_2( secondNode );

        // This step truly reverses the Nodes
        secondNode.next = firstNode;
        firstNode.next = null;
        return rest;
    }

    public String toString() {
        String rv = "{";
        Node ptr = first;
        while ( ptr != null ) {
            rv += " " + ptr.item + ",";
            ptr = ptr.next;
        }
        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        LinkedListReverse< String > linkedList = new LinkedListReverse< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            linkedList.add( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );
        linkedList.reverse( linkedList.first );
        StdOut.println( "DEBUG: " + linkedList.toString() );
        linkedList.reverseRecursively( linkedList.first, linkedList.first.next, null );
        StdOut.println( "DEBUG: " + linkedList.toString() );
        linkedList.reverseRecursively_2( linkedList.first );
        StdOut.println( "DEBUG: " + linkedList.toString() );
    }
}
