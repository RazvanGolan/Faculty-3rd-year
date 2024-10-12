# Requirements

## Overview
This homework assignment consists of three exercises that involve implementing mathematical operations using assembly language in the Little Man Computer (LMC) model. The goal is to create simple programs to perform multiplication, squaring, and exponentiation.

## Exercises

### Exercise 1: Multiplication (a * b)
- **Objective**: Implement a program that multiplies two numbers \( a \) and \( b \).
- **Input**:
  - The first number \( a \) (integer).
  - The second number \( b \) (integer).
- **Output**:
  - The result of \( a \times b \).
- **Notes**:
  - Use repeated addition to perform the multiplication operation.
  - Initialize an accumulator to store the result.

### Exercise 2: Squaring (a^2)
- **Objective**: Implement a program that computes the square of a number \( a \).
- **Input**:
  - The number \( a \) (integer).
- **Output**:
  - The result of \( a^2 \) (i.e., \( a \times a \)).
- **Notes**:
  - Utilize the multiplication program from Exercise 1 for this task.
  - Initialize an accumulator for the multiplication operation.

### Exercise 3: Exponentiation (a^b)
- **Objective**: Implement a program that calculates \( a \) raised to the power of \( b \).
- **Input**:
  - The base number \( a \) (integer).
  - The exponent \( b \) (integer).
- **Output**:
  - The result of \( a^b \) (i.e., \( a \) multiplied by itself \( b \) times).
- **Notes**:
  - Use a loop to perform the multiplication \( b \) times.
  - Initialize an accumulator for the result and a counter for the exponent.

## Implementation Guidelines
- Use appropriate variable names for clarity.
- Include comments in your code to explain the logic behind each step.
- Ensure your program handles edge cases, such as when \( b = 0 \) (which should return 1).
- Test your programs with various input values to ensure correctness.

