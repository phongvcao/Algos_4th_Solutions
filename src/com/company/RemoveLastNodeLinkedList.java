package com.company;
import edu.princeton.cs.algs4.*;

public class RemoveLastNodeLinkedList< Item > {
    // first node of the list
    private Node first;

    // size of the linked-list
    private int N = 0;

    public class Node {
        Item item = null;
        Node next = null;
    }

    public boolean isEmpty() { return first == null; };
    public int size() { return N; }

    public void prepend( Item item ) {
        // Prepend item to end of linked list
        Node oldFirst = first;
        first = new Node();
        first.item = item;
        first.next = oldFirst;
        ++N;
    }

    public void removeLastNode() {
        // Remove the last node in the linked list
        Node last = first;
        Node beforeLast = last;
        while ( last != null ) {
            if ( last.next != null ) {
                beforeLast = last;
                last = last.next;
            } else {
                break;
            }


            // DEBUG
            StdOut.println( "DEBUG: beforeLast: " + beforeLast.item + "; last: " + last.item );
            // END OF DEBUG
        }

        beforeLast.next = null;
        --N;
    }

    public boolean find( Item key ) {
        Node ptr = first;
        while ( ptr != null ) {
            if ( ptr.item == key ) {
                return true;
            }
            ptr = ptr.next;
        }
        return false;
    }

    public Node removeAfter( Node node ) {
        if ( isEmpty() ) return null;

        if ( node.next != null ) {
            Node oldNode = node.next;
            node.next = node.next.next;
            --N;
            return oldNode;
        }

        return null;
    }

    public void insertAfter( Node first, Node second ) {
        Node currentAfterFirst = first.next;
        first.next = second;
        second.next = currentAfterFirst;
    }

    public Item delete( int k ) {
        if ( k > N ) {
            return null;
        }

        Node kNode = first;
        Node beforeKNode = kNode;

        while ( kNode != null ) {
            if ( kNode.next != null ) {
                beforeKNode = kNode;
                kNode = kNode.next;
                --k;

                if ( k <= 1 ) break;
            } else {
                break;
            }
        }

        beforeKNode.next = kNode.next;
        --N;

        return kNode.item;
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
        RemoveLastNodeLinkedList< String > linkedList = new RemoveLastNodeLinkedList<>();

        // StdOut.println( "DEBUG: " );

        for ( int i = 0; i < strArr.length; ++i ) {
            linkedList.prepend( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );

        linkedList.removeLastNode();

        StdOut.println( "DEBUG: " + linkedList.toString() );

        linkedList.delete( 3 );

        StdOut.println( "DEBUG: " + linkedList.toString() );
    }
}
