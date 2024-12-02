namespace lab10;

using System;
using System.Collections.Generic;
using System.Linq;

public class Store
{
    private readonly List<Game> _games = [];

    public void AddGame(Game game)
    {
        _games.Add(game);
    }

    public List<Game> GamesBefore(DateTime date)
    {
        return _games.Where(game => game.ReleaseDate < date).ToList();
    }

    public int GamesBetween(int year1, int year2)
    {
        return _games.Count(game => game.ReleaseDate.Year >= year1 && game.ReleaseDate.Year <= year2);
    }

    public List<Game> OrderByDeveloperAndByName()
    {
        return _games
            .OrderBy(game => game.Developer)
            .ThenBy(game => game.Name)
            .ToList();
    }

    public List<Game> GamesByDeveloperOrderedByPrice(string developer, bool descending = false)
    {
        return descending
            ? _games.Where(game => game.Developer == developer)
                .OrderByDescending(game => game.Price)
                .ToList()
            : _games.Where(game => game.Developer == developer)
                .OrderBy(game => game.Price)
                .ToList();
    }

    public Game? FirstGameByDeveloper(string developer)
    {
        return _games.Where(game => game.Developer == developer).MinBy(game => game.ReleaseDate);
    }

    public bool GameMoreExpensiveThan(float price)
    {
        return _games.Any(game => game.Price > price);
    }

    public float SumOfPriceForGamesWithTag(string tag)
    {
        return _games.Where(game => game.Tags.Contains(tag))
            .Sum(game => game.Price);
    }

    public List<Game> GamesWhichContainAtLeastOneTag(List<string> tags)
    {
        return _games.Where(game => game.Tags.Any(tag => tags.Contains(tag)))
            .ToList();
    }
}