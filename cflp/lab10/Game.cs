namespace lab10;

public class Game
{
    public Game(string name, string developer, DateTime releaseDate, float price, List<string> tags)
    {
        Name = name;
        Developer = developer;
        ReleaseDate = releaseDate;
        Price = price;
        Tags = tags;
    }

    public string Name { get; set; }
    public string Developer { get; set; }
    public DateTime ReleaseDate { get; set; }
    public float Price { get; set; }
    public List<string> Tags { get; set; }

    public override string ToString()
    {
        return $"Name: {Name}, " +
               $"Developer: {Developer}, " +
               $"Release Date: {ReleaseDate:yyyy-MM-dd}, " +
               $"Price: ${Price:F2}, " +
               $"Tags: [{string.Join(", ", Tags)}]";
    }

}