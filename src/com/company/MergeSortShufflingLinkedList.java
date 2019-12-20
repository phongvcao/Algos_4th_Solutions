package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Random;

public class MergeSortShufflingLinkedList {

    // LINKED-LIST IMPLEMENTATION
    public static class Node {
        Comparable item = null;
        Node next = null;
    }

    public static Node head = null;

    public static Node append( Node headNode, Comparable item ) {
        if ( headNode == null ) {
            headNode = new Node();
            headNode.item = item;
        } else {
            Node ptr = headNode;
            while ( ptr.next != null ) {
                ptr = ptr.next;
            }
            ptr.next = new Node();
            ptr.next.item = item;
        }
        return headNode;
    }

    public static void copy( Node fromNode, Node toNode, int copySize ) {
        Node fromNodePtr = fromNode;
        Node toNodePtr = toNode;

        for ( int i = 0; i < copySize; ++i ) {
            toNodePtr.item = fromNodePtr.item;
            if ( ( i < copySize - 1 ) && ( toNodePtr.next == null ) ) {
                toNodePtr.next = new Node();
            }
            fromNodePtr = fromNodePtr.next;
            toNodePtr = toNodePtr.next;
        }
    }

    public static String toString( Node headNode ) {
        String rv = "{ ";
        Node ptr = headNode;

        while ( ptr != null ) {
            rv += " " + ptr.item + ", ";
            ptr = ptr.next;
        }

        rv += " }";
        return rv;
    }
    // END OF LINKED-LIST IMPLEMENTATION

    // SHUFFLING IMPLEMENTATION
    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void shuffleMerge( Node headNode, Node auxNode, int leftSize, int rightSize ) {
        // First copy everything to auxNode
        copy( headNode, auxNode, leftSize + rightSize );

        // Seek to middle of auxNode
        Node leftAuxNodePtr = auxNode;
        Node rightAuxNodePtr = leftAuxNodePtr;

        for ( int i = 0; i < leftSize; ++i ) {
            rightAuxNodePtr = rightAuxNodePtr.next;
        }

        // Now merge left side of linked-list with right side
        Node headNodePtr = headNode;
        int leftAuxIndex = 0;
        int rightAuxIndex = leftSize;
        Random random = new Random();
        for ( int i = 0; i < leftSize + rightSize; ++i ) {
            if ( leftAuxIndex > leftSize - 1 ) {
                headNodePtr.item = rightAuxNodePtr.item;
                rightAuxNodePtr = rightAuxNodePtr.next;
                ++rightAuxIndex;
            } else if ( rightAuxIndex > leftSize + rightSize - 1 ) {
                headNodePtr.item = leftAuxNodePtr.item;
                leftAuxNodePtr = leftAuxNodePtr.next;
                ++leftAuxIndex;
            /* // DEBUG
            } else if ( less( rightAuxNodePtr.item, leftAuxNodePtr.item ) ) {
                headNodePtr.item = rightAuxNodePtr.item;
                rightAuxNodePtr = rightAuxNodePtr.next;
                ++rightAuxIndex;
            } else {
                headNodePtr.item = leftAuxNodePtr.item;
                leftAuxNodePtr = leftAuxNodePtr.next;
                ++leftAuxIndex;
            }
            // END OF DEBUG */

            } else {
                // Randomly pick element from either left or right side
                boolean pickRight = random.nextInt( 2 ) == 0 ? false : true;
                if ( ! pickRight ) {
                    headNodePtr.item = leftAuxNodePtr.item;
                    leftAuxNodePtr = leftAuxNodePtr.next;
                    ++leftAuxIndex;
                } else {
                    headNodePtr.item = rightAuxNodePtr.item;
                    rightAuxNodePtr = rightAuxNodePtr.next;
                    ++rightAuxIndex;
                }
            }
            headNodePtr = headNodePtr.next;
        }
    }

    public static void shuffleSort( Node headNode, Node auxNode, int size ) {
        if ( size < 2 ) return;

        Node firstHalfNode = headNode;
        Node secondHalfNode = firstHalfNode;
        int firstHalfSize = 0;
        // Seek secondHalfNode to middle
        for ( int i = 0; i < size / 2; ++i ) {
            secondHalfNode = secondHalfNode.next;
            ++firstHalfSize;
        }

        // Call shuffleSort() on each half of headNode
        shuffleSort( firstHalfNode, auxNode, firstHalfSize );
        shuffleSort( secondHalfNode, auxNode, size - firstHalfSize );
        // Merge
        shuffleMerge( firstHalfNode, auxNode, firstHalfSize, size - firstHalfSize );
    }
    // END OF SHUFFLING IMPLEMENTATION

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        for ( int i = 0; i < intArr.length; ++i ) {
            head = append( head, intArr[ i ] );
        }

        /* // DEBUG
        Node toNode = new Node();
        copy( head, toNode, intArr.length );
        StdOut.println( "DEBUG: toNode: " + toString( toNode ) );

        Integer[] intArr2 = { 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9 };
        Node headNode2 = null;

        for ( int i = 0; i < intArr2.length; ++i ) {
            headNode2 = append( headNode2, intArr2[ i ] );
        }
        StdOut.println( "DEBUG: headNode2 (BEFORE): " + toString( headNode2 ) );

        Node auxNode2 = new Node();
        shuffleMerge( headNode2, auxNode2, 8, 5 );
        StdOut.println( "DEBUG: headNode2 (AFTER): " + toString( headNode2 ) );
        // END OF DEBUG */

        Node aux = new Node();
        shuffleSort( head, aux, intArr.length );

        StdOut.println( "DEBUG: head (BEFORE): " + toString( head ) );
    }
}
