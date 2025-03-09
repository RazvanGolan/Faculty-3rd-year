// Structure definition
struct Point {
    int x;
    double y;
};

// Function prototype
void printPoint(struct Point p);

// Global variables
int global_var = 123;
double pi = 3.14159;
char newline = '\n';

// Main function with various constructs
int main() {
    // Variable declarations
    int i;
    double result;
    char c = 'A';

    // Array
    int numbers[10];

    // String constant
    char *message = "Hello, AtomC lexer!";

    // Simple assignment
    i = 0;

    // While loop with comparison operators
    while (i < 10) {
        // If statement with logical operators
        if (i > 5 && i <= 8 || i == 0) {
            result = i * 2.5;
        } else {
            result = i / 2.0;
        }

        // Increment
        i = i + 1;
    }

    // Scientific notation
    double scientific = 1.23e-4;
    double another = 5e+3;

    // Nested if with various operators
    if (!(i == 10)) {
        if (global_var >= 100) {
            result = result - 5.0;
        }
    }

    // Struct usage
    struct Point p;
    p.x = 10;
    p.y = 20.5;

    // Function call
    printPoint(p);

    return 0;
}

// Function implementation
void printPoint(struct Point p) {
}