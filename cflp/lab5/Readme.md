# Exercises

1. Implement a static method RemoveAt, which receives as parameters an array, the length of the array and an index. The method removes from the array the element from the received index.

```C#
public static void RemoveAt(int[] array, ref int length, int n)
```

2. Implement a static Intersection method that receives as parameters two lists of integers and returns a list of integers that contains the elements that are present in both lists (the intersection). Make sure that the returned list does not contain duplicates.

```C#
public static List Intersection(List l1, List l2)
```

3. Implement a generic Stack<T> collection using a List<T>. The collection must have the following methods:

```C#
 public class Stack<T>
    {
        public Push(T); // adds an item to the stack
        public T Pop(); // removes an item from the stack and throws an exception if the stack is empty
	public bool TryPop(out T); // return true and the item as an out parameter if the pop was successful or false if the stack is empty
        public T Peek(); // gets the item at the top of the stack without removing it
    }
```