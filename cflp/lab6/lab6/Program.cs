// exercise 1

using lab6;

Console.WriteLine("EXERCISE 1\n");

List<int> list = [1, 2, 3, 4, 5];
var newList = Exercises.Filter(x => x % 2 == 0, list);

foreach (var x in newList)
{
    Console.WriteLine(x);
}

// exercise 2
Console.WriteLine("\nEXERCISE 2\n");

var result = Exercises.FGX(ExampleMethods.f, ExampleMethods.g, 20);

Console.WriteLine(result);