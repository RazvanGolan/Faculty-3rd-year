using lab3;

var a = 10;
var b = 20;

Console.WriteLine("EXERCISE 1\n");
Console.WriteLine($"A is equal to {a}, B is equal to {b}");

Exercise1.Swap(ref a,ref b);

Console.WriteLine($"A is equal to {a}, B is equal to {b}\n");

Console.WriteLine("EXERCISE 2\n");

var coordsA = new Coords(2, 2);
var coordsB = new Coords(1, 1);

var coordsM = Exercise2.FindMiddle(coordsA, coordsB);

Console.WriteLine($"The middle of the two coordinates A {coordsA} and B {coordsB} is {coordsM}\n");

Console.WriteLine("EXERCISE 3\n");

var account = new Account("TEST ACCOUNT", 300);

Console.WriteLine(account.Withdraw(200, out var remainingFunds) 
    ? $"Current remaining funds: {remainingFunds}" : "Not enough funds");

Console.WriteLine(account.Withdraw(200, out remainingFunds) 
    ? $"Current remaining funds: {remainingFunds}" : "Not enough funds");

