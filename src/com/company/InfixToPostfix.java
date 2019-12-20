package com.company;
import edu.princeton.cs.algs4.*;

public class InfixToPostfix {
    public static void main( String[] args ) {
        Stack< String > operators = new Stack< String >();
        Stack< String > operands = new Stack< String >();

        // line = ( ( ( 1 + 2 ) * ( 3 - 4 ) ) * ( 5 - 6 ) )
        String line = StdIn.readLine();

        String[] itemsArr = line.split( "\\s+", -1 );

        for ( String item : itemsArr ) {
            if ( item.equals( "+" ) || item.equals( "-" ) || item.equals( "*" ) || item.equals( "/" ) ) {
                operators.push( item );
            } else if ( item.equals( "(" ) ) {
                // Do NOTHING
            } else {
                if ( item.equals( ")" ) ) {
                    String operand2 = operands.pop();
                    String operand1 = operands.pop();
                    String expression = "( " + operand1 + " " + operand2 + " " + operators.pop()  + " )";
                    operands.push( expression );
                } else {
                    operands.push( item );
                }
            }
        }

        StdOut.println( operands.pop() );
        StdOut.println( java.util.Arrays.toString( itemsArr ) );
        StdOut.println( operands.toString() );
    }
}
