# Game and Store Application

Create an application used for storing and searching game titles. The following two classes are required:

## Game

This class will store the following properties:

- `string Name`
- `string Developer`
- `DateTime ReleaseDate`
- `float Price`
- `List<string> Tags`

The properties will be set using the constructor. The `ToString()` method will be used for display.

## Store

This class will contain a list of available games and provide the following methods:

- `void AddGame(Game game)` - adds a new game to the list;
- `List<Game> GamesBefore(DateTime date)` - returns a list of games released before the specified date;
- `int GamesBetween(int year1, int year2)` - returns the number of games released between the specified years (Hint: use the `Count` method from LINQ);
- `List<Game> OrderByDeveloperAndByName()` - returns a list of all games, ordered first by the developer's name, then by the game's name;
- `List<Game> GamesByDeveloperOrderedByPrice(string developer, bool descending = false)` - returns a list of games made by the specified developer, ordered by price. The second parameter is optional and specifies ascending/descending order;
- `Game FirstGameByDeveloper(string developer)` - returns the oldest game made by the specified developer;
- `bool GameMoreExpensiveThan(float price)` - returns `true` if at least one game costs more than the specified price. Use the `Any` method;
- `float SumOfPriceForGamesWithTag(string tag)` - returns the sum of prices for all games that contain the specified tag;
- `List<Game> GamesWhichContainAtLeastOneTag(List<string> tags)` - returns a list of games that contain at least one of the specified tags in the list (Hint: you can use the `Any` or `Intersect` methods).

### Notes

All queries must be implemented using LINQ. Loops like `for`, `while`, or `do while` will not be accepted.
