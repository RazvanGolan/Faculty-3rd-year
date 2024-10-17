# Requirements

## Overview
This homework assignment consists of three exercises that involve implementing mathematical and comparison operations using RISC assembly language. The tasks include performing arithmetic operations, printing ranges of numbers, and determining the maximum between two numbers or computing exponentiation when they are equal.

## Exercises

### Exercise 1: Arithmetic Operation (A / B - C * D)
- **Objective**: Implement a RISC assembly program that calculates \( \frac{A}{B} - C \times D \).
- **Input**:
  - The first number \( A \) (integer), input through a register.
  - The second number \( B \) (integer), input through a register.
  - The third number \( C \) (integer), input through a register.
  - The fourth number \( D \) (integer), input through a register.
- **Output**:
  - The result of the expression \( \frac{A}{B} - C \times D \), output through a register.
- **Notes**:
  - Ensure that division is performed first, as per the order of operations, and handle cases where \( B = 0 \) to avoid division by zero.
  - Use appropriate RISC instructions for division (`DIV`), multiplication (`MUL`), and subtraction (`SUB`).
  - Store intermediate results in temporary registers and use proper branching and comparison logic to handle edge cases.

### Exercise 2: Print Range [A, B)
- **Objective**: Implement a RISC assembly program that prints all numbers in the interval \([A, B)\).
- **Input**:
  - The starting number \( A \) (integer), input through a register.
  - The ending number \( B \) (integer), input through a register.
- **Output**:
  - The program outputs all numbers starting from \( A \) and ending before \( B \) (i.e., it prints \( A, A+1, ..., B-1 \)).
- **Notes**:
  - Use a loop to repeatedly output the current value of \( A \) and increment it until \( A \geq B \).
  - Compare \( A \) and \( B \) at the beginning of each iteration to decide whether to continue the loop.
  - Ensure that no numbers are printed if \( A \geq B \).

### Exercise 3: Print Maximum or Exponentiation
- **Objective**: Implement a RISC assembly program that prints the maximum between \( A \) and \( B \), or prints \( A^B \) if \( A \) and \( B \) are equal.
- **Input**:
  - The first number \( A \) (integer), input through a register.
  - The second number \( B \) (integer), input through a register.
- **Output**:
  - If \( A > B \), print \( A \).
  - If \( B > A \), print \( B \).
  - If \( A = B \), print \( A^B \) (i.e., \( A \) raised to the power of \( B \)).
- **Notes**:
  - Use comparison instructions (`CMP`) to check the relationships between \( A \) and \( B \).
  - For exponentiation, use a loop to multiply \( A \) by itself \( B \) times (i.e., repeated multiplication).
  - Handle the case where \( B = 0 \) appropriately, as \( A^0 \) should output 1.

## Implementation Guidelines
- **Registers**: Use appropriate registers to hold inputs, intermediate values, and outputs.
- **Instructions**: Utilize RISC instructions such as `INP`, `CMP`, `MUL`, `DIV`, `SUB`, `OUT`, and branch instructions for flow control.
- **Edge Cases**: Ensure proper handling of edge cases, such as division by zero, zero exponentiation, and ranges where \( A \geq B \).
- **Testing**: Test your programs thoroughly with different input values to ensure correctness.
- **Comments**: Include detailed comments in your code to explain the purpose of each instruction and the flow of the program.

### Example Workflow:
For each exercise:
1. Input values via registers.
2. Perform the necessary comparisons and calculations using RISC instructions.
3. Use branching to control the flow of the program, especially for loops and condition checks.
4. Output results via registers.
5. Halt the program once the task is completed.
