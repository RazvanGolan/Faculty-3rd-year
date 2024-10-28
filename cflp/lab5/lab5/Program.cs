using lab5;

// exercise 1
Console.WriteLine("EXERCISE 1\n");

int[] array = {1, 2, 3, 4, 5};
var length = array.Length;
ListExercises.RemoveAt(array, ref length, 2);

Console.WriteLine($"Length: {length}");
for (var i = 0; i < length; i++)
{
    Console.WriteLine($"Number: {array[i]}");
}

// exercise 2
Console.WriteLine("\nEXERCISE 2\n");

var list1 = new List<int>{1, 2, 3};
var list2 = new List<int>{2 ,3, 4, 5};

var list3 = ListExercises.Intersection(list1, list2);

foreach (var number in list3)
{
    Console.WriteLine($"Number: {number}");
}

// exercise 3
Console.WriteLine("\nEXERCISE 3\n");

var stack = new MyStack<int>();

try
{
    stack.Pop();
}
catch (Exception e)
{
    Console.WriteLine(e.Message);
}
Console.WriteLine(stack.TryPop(out var itemTryPop) ? $"Try pop value {itemTryPop}" : "Array is empty");
stack.Push(1);
stack.Push(2);
stack.Push(3);
stack.Push(4);
stack.Push(5);
stack.Pop();
Console.WriteLine(stack.TryPop(out var item) ? $"Try pop value {item}" : "Array is empty");
Console.WriteLine(stack);

Console.WriteLine($"Item at the top of the stack {stack.Peek().ToString()}");