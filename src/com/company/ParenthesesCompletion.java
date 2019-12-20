package com.company;
import edu.princeton.cs.algs4.*;

public class ParenthesesCompletion {
    public static void main( String[] args ) {
        Stack< String > operators = new Stack< String >();
        Stack< String > operands = new Stack< String >();

        while ( !StdIn.isEmpty() ) {
            String line = StdIn.readLine();

            String[] itemsArr = line.split( "\\s+", -1 );

            for ( String item : itemsArr ) {
                if ( item.equals( "+" ) || item.equals( "-" ) || item.equals( "*" ) || item.equals( "/" ) ) {
                    operators.push( item );
                } else {
                    if ( item.equals( ")" ) ) {
                        String operand2 = operands.pop();
                        String operand1 = operands.pop();
                        String expression = "( " + operand1 + " " + operators.pop() + " " + operand2 + " )";
                        operands.push( expression );
                    } else {
                        operands.push( item );
                    }
                }
            }

            break;
        }

        StdOut.println( operands.pop() );
    }
}
