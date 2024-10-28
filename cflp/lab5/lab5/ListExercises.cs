namespace lab5;

public static class ListExercises
{
    public static void RemoveAt(int[] array, ref int length, int n)
    {
        var arrayList = array.ToList();
        arrayList.RemoveAt(n);
        
        arrayList.CopyTo(array);
        length = arrayList.Count;
    }

    public static List<int> Intersection(List<int> l1, List<int> l2)
    {
        var intersection = new List<int>();
        
        foreach (var item in l1.Where(item => l2.Contains(item) && !intersection.Contains(item)))
        {
            intersection.Add(item);
        }

        return intersection;
    }
}