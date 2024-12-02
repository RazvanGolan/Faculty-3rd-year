using lab10;

var store = new Store();

store.AddGame(new Game("Adventure Quest", "Artix Entertainment", new DateTime(2002, 10, 15), 19.99f, ["RPG", "Fantasy", "Multiplayer"]));
store.AddGame(new Game("Space Invaders", "Taito", new DateTime(1978, 6, 14), 9.99f, ["Arcade", "Classic"]));
store.AddGame(new Game("Cyberpunk 2077", "CD Projekt Red", new DateTime(2020, 12, 10), 59.99f, ["RPG", "Open World"]));
store.AddGame(new Game("The Witcher 3", "CD Projekt Red", new DateTime(2015, 5, 19), 39.99f, ["RPG", "Fantasy", "Singleplayer"]));
store.AddGame(new Game("Pong", "Atari", new DateTime(1972, 11, 29), 4.99f, ["Arcade", "Classic"]));

Console.WriteLine("Games before 2000:");
var gamesBefore2000 = store.GamesBefore(new DateTime(2000, 1, 1));
foreach (var game in gamesBefore2000)
{
    Console.WriteLine(game);
}

Console.WriteLine("\nNumber of games released between 2000 and 2020:");
var countGames = store.GamesBetween(2000, 2020);
Console.WriteLine(countGames);

Console.WriteLine("\nGames ordered by Developer and Name:");
var orderedGames = store.OrderByDeveloperAndByName();
foreach (var game in orderedGames)
{
    Console.WriteLine(game);
}

Console.WriteLine("\nGames by CD Projekt Red ordered by price:");
var cdProjektGames = store.GamesByDeveloperOrderedByPrice("CD Projekt Red");
foreach (var game in cdProjektGames)
{
    Console.WriteLine(game);
}

Console.WriteLine("\nFirst game by CD Projekt Red:");
var firstGame = store.FirstGameByDeveloper("CD Projekt Red");
Console.WriteLine(firstGame);

Console.WriteLine("\nIs there a game more expensive than $50?");
var expensiveGame = store.GameMoreExpensiveThan(50.0f);
Console.WriteLine(expensiveGame);

Console.WriteLine("\nSum of prices for games with the tag 'RPG':");
var rpgSum = store.SumOfPriceForGamesWithTag("RPG");
Console.WriteLine($"${rpgSum:F2}");

Console.WriteLine("\nGames that contain at least one of the tags: ['Arcade', 'Fantasy']:");
var taggedGames = store.GamesWhichContainAtLeastOneTag(new List<string> { "Arcade", "Fantasy" });
foreach (var game in taggedGames)
{
    Console.WriteLine(game);
}