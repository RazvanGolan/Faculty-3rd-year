# Lab 8

Events

# Exercises

Create a project with 3 classes: `InputReader`, `CharListener`, and `ComplexListener`.

### InputReader
- Contains an `EventHandler<KeyboardInputEventArgs>` called `OnKeyPressed`.
- Includes a method `ReadKeys()` that reads lines from the console until an empty string is encountered.
- After reading each string, the `OnKeyPressed` event is invoked.

### CharListener
- Has a constructor that:
    - Receives a `char key` and stores it in a field.
    - Accepts an `InputReader`.
- The constructor subscribes a method `HandleKeyPressed` to the `OnKeyPressed` event in `InputReader`.
- `HandleKeyPressed`:
    - Receives `KeyboardInputEventArgs` (containing a string) from the event invocation.
    - Displays a message if the string contains the `key` character received in the constructor.

### ComplexListener
- Has a constructor that:
    - Receives an `int strNo` specifying the number of strings the `ComplexListener` should store.
    - Accepts an `InputReader`.
- The constructor subscribes a method `HandleKeyPressed` to the `OnKeyPressed` event in `InputReader`.
- `HandleKeyPressed`:
    - Receives `KeyboardInputEventArgs` (containing a string) from the event.
    - Adds the received string to a list of strings.
    - Ensures the list contains at most `strNo` elements (removes the oldest entry if the list is full).
    - If the string `"print last"` is received, displays the last entry in the list.
    - If the string `"print all"` is received, displays all strings in the list.
    - The strings `"print last"` and `"print all"` are **not** added to the list.

### Main Method
- Contains an `InputReader`.
- Creates:
    - 2 `CharListener` instances.
    - 1 `ComplexListener` instance.
- Uses the `InputReader` to read strings.