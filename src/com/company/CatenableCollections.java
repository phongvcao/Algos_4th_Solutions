package com.company;
import edu.princeton.cs.algs4.*;

public class CatenableCollections< Item > {

    public CircularLinkedList< Item > catenationQueues( Queue< Item > q1, Queue< Item > q2 ) {
        CircularLinkedList< Item > cirList = new CircularLinkedList< Item >();

        while ( ! q1.isEmpty() ) {
            cirList.insert( q1.dequeue() );
        }

        while ( ! q2.isEmpty() ) {
            cirList.insert( q2.dequeue() );
        }

        return cirList;
    }

    public CircularLinkedList< Item > catenationStacks( Stack< Item > s1, Stack< Item > s2 ) {
        CircularLinkedList< Item > cirList = new CircularLinkedList< Item >();

        while ( ! s1.isEmpty() ) {
            cirList.insert( s1.pop() );
        }

        while ( ! s2.isEmpty() ) {
            cirList.insert( s2.pop() );
        }

        return cirList;
    }

    public CircularLinkedList< Item > catenationSteques( Steque< Item > stq1, Steque< Item > stq2 ) {
        CircularLinkedList< Item > cirList = new CircularLinkedList< Item >();

        while ( ! stq1.isEmpty() ) {
            cirList.insert( stq1.pop() );
        }

        while ( ! stq2.isEmpty() ) {
            cirList.insert( stq2.pop() );
        }

        return cirList;
    }

    public static void main( String[] args ) {

    }
}
