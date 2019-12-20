package com.company;

import edu.princeton.cs.algs4.StdOut;

public class DoublyLinkedList< Item > {
    private int N = 0;

    private class DoubleNode {
        Item item = null;
        DoubleNode next = null;
        DoubleNode prev = null;
    }

    private DoubleNode first;
    private DoubleNode last;

    public void insertAtBeginning( Item item ) {
        DoubleNode newNode = new DoubleNode();
        newNode.item = item;

        if ( first != null ) {
            newNode.next = first;
            first.prev = newNode;

            if ( last == null ) {
                last = first;
            }
        }
        first = newNode;

        ++N;
    }

    public void insertAtEnd( Item item ) {
        DoubleNode newNode = new DoubleNode();
        newNode.item = item;

        if ( last != null ) {
            newNode.prev = last;
            last.next = newNode;

            if ( first == null ) {
                first = last;
            }
        }
        last = newNode;

        ++N;
    }

    public DoubleNode removeFromBeginning() {
        DoubleNode removedNode = null;

        removedNode = first;
        first = first.next;
        first.prev = null;

        --N;
        return removedNode;
    }

    public DoubleNode removeFromEnd() {
        DoubleNode removedNode = null;
        removedNode = last;
        last = last.prev;
        last.next = null;

        --N;
        return removedNode;
    }

    public void insertBeforeNode( Item item, DoubleNode node ) {
        DoubleNode newNode = new DoubleNode();
        newNode.next = node;
        newNode.prev = node.prev;

        if ( newNode.prev != null ) {
            newNode.prev.next = newNode;
        }
        node.prev = newNode;

        ++N;
    }

    public void insertAfterNode( Item item, DoubleNode node ) {
        DoubleNode newNode = new DoubleNode();
        newNode.prev = node;
        newNode.next = node.next;

        if ( newNode.next != null ) {
            newNode.next.prev = newNode;
        }
        node.next = newNode;

        ++N;
    }

    public DoubleNode removeNode( Item item ) {
        DoubleNode ptr = first;
        while ( ptr != null ) {
            if ( ptr.item == item ) {
                ptr.prev.next = ptr.next;
                ptr.next.prev = ptr.prev;
                break;
            }
            ptr = ptr.next;
        }

        --N;
        return ptr;
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

    public boolean isEmpty() {
        return N == 0;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        DoublyLinkedList< String > linkedList = new DoublyLinkedList< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            // linkedList.insertAtBeginning( strArr[ i ] );
            linkedList.insertAtEnd( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );

        linkedList.removeFromBeginning();
        linkedList.removeFromEnd();

        StdOut.println( "DEBUG: " + linkedList.toString() );

        linkedList.removeNode( "4" );

        StdOut.println( "DEBUG: " + linkedList.toString() );
    }
}
