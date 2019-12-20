package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Iterator;

public class StackClient {

    public static Stack< String > copy( Stack< String > stack ) {
        Stack< String > newStack1 = new Stack< String >();

        Iterator it = stack.iterator();
        while ( it.hasNext() ) {
            newStack1.push( (String)it.next() );
        }

        Stack< String > newStack = new Stack< String >();

        it = newStack1.iterator();
        while ( it.hasNext() ) {
            newStack.push( (String)it.next() );
        }

        return newStack;
    }

    public static void main( String[] args ) {
        Stack< String > stack = new Stack< String >();
        stack.push( "0" );
        stack.push( "1" );
        stack.push( "2" );
        stack.push( "3" );

        StdOut.println( "oldStack: " + stack.toString() );
        StdOut.println( "newStack: " + copy( stack ).toString() );
    }
}
