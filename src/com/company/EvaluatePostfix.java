package com.company;

import edu.princeton.cs.algs4.*;

public class EvaluatePostfix {
    public static void main( String[] args ) {
        Stack< String > operators = new Stack< String >();
        Stack< String > operands = new Stack< String >();

        String line = StdIn.readLine();

        String[] itemsArr = line.split( "\\s+", -1 );
        // int finalValue = Integer.parseInt( itemsArr[ 0 ] );
        // String lastRead = itemsArr[ 1 ];
        operands.push( itemsArr[ 0 ] );
        operands.push( itemsArr[ 1 ] );

        for ( String item : java.util.Arrays.copyOfRange( itemsArr, 2, itemsArr.length ) ) {
        // for ( String item : itemsArr ) {
            if ( item.equals( "+" ) ) {
                operands.push( "" + ( Integer.parseInt( operands.pop() ) + Integer.parseInt( operands.pop() ) ) );
            } else if ( item.equals( "-" ) ) {
                int operand2 = Integer.parseInt( operands.pop() );
                int operand1 = Integer.parseInt( operands.pop() );
                operands.push( "" + ( operand1 - operand2 ) );
            } else if ( item.equals( "*" ) ) {
                operands.push( "" + ( Integer.parseInt( operands.pop() ) * Integer.parseInt( operands.pop() ) ) );
            } else if ( item.equals( "/" ) ) {
                int operand2 = Integer.parseInt( operands.pop() );
                int operand1 = Integer.parseInt( operands.pop() );
                operands.push( "" + ( operand1 / operand2 ) );
            } else {
                operands.push( item );
            }
        }

        StdOut.println( operands.pop() );
    }
}
