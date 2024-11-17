namespace lab8;

public class ComplexListener
{
    private int MaxStrings { get; set; }
    private List<string> StoredStrings { get; set; } = [];

    public ComplexListener(int maxStrings, InputReader inputReader)
    {
        MaxStrings = maxStrings;
        
        inputReader.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object? sender, KeyboardInputEventArgs e)
    {
        switch (e.StringArg)
        {
            case "print last":
                Console.WriteLine(StoredStrings.Last());
                break;
            case "print all":
            {
                foreach (var stored in StoredStrings)
                {
                    Console.WriteLine(stored);
                }

                break;
            }
            default:
            {
                if (StoredStrings.Count == MaxStrings)
                {
                    StoredStrings.RemoveAt(0);
                }
                StoredStrings.Add(e.StringArg);
                break;
            }
        }
    }
}