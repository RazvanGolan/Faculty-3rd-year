namespace lab9;

public class Tamagotchi
{
    public Tamagotchi(string name, int food, int hungerRate, string keys, InputReader inputReader)
    {
        Name = name;
        Food = food;
        HungerRate = hungerRate;
        Keys = keys;
        IsAlive = true;
        
        inputReader.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object? sender, string e)
    {
        if (!e.Equals(Keys))
            return;

        Food += 5;

        if (Food > 20)
        {
            IsAlive = false;
        }
        Console.WriteLine(ToString());
    }

    private string Name { get; set; }
    private int Food { get; set; }
    private int HungerRate { get; set; }
    private bool IsAlive { get; set; }
    private string Keys { get; set; }

    public async Task Run()
    {
        while (IsAlive)
        {
            await Task.Delay(HungerRate);

            Food -= 3;

            if (Food is <= 0 or > 20)
            {
                IsAlive = false;
            }
            
            Console.WriteLine(ToString());
        }
    }

    public override string ToString()
    {
        return IsAlive
            ? $"{Name} is healthy and alive. Food remaining: {Food}"
            : $"{Name} is dead :(";
    }
}