namespace lab5;

public class MyStack<T> : IMyStack<T>
{
    private readonly List<T> _list = [];
    
    public void Push(T item)
    {
        _list.Add(item);
    }

    public T Pop()
    {
        if (_list.Count == 0)
        {
            throw new ArgumentOutOfRangeException($"Stack is empty");
        }
        
        var firstInQueue = _list.Last();
        _list.RemoveAt(_list.Count - 1);

        return firstInQueue;
    }

    public bool TryPop(out T item)
    {
        if (_list.Count == 0)
        {
            item = default(T) ?? throw new InvalidOperationException();
            return false;
        }

        item = _list.Last();
        _list.RemoveAt(_list.Count - 1);

        return true;
    }

    public T Peek()
    {
        return _list.Last();
    }

    public override string ToString()
    {
        var stackSize = $"Stack size: {_list.Count}\n";
        var stackItem = string.Empty;
        foreach (var item in _list)
        {
            stackItem += $"Stack item: {item}\n";
        }

        return stackSize + stackItem;
    }
}