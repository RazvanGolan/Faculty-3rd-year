namespace lab5;

public interface IMyStack<T>
{
    void Push(T item); // adds an item to the stack
    T Pop(); // removes an item from the stack and throws an exception if the stack is empty
    bool TryPop(out T item); // return true and the item as an out parameter if the pop was successful or false if the stack is empty
    T Peek(); // gets the item at the top of the stack without removing it
}