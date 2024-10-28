namespace lab4;

public class House(string address, double indoorArea, double propertyValue, double outdoorArea) : Property(address, indoorArea, propertyValue)
{
    public double OutdoorArea { get; set; } = outdoorArea;

    public double TotalArea
    {
        get => OutdoorArea + IndoorArea;
        set => TotalArea = value;
    }

    public override string ToString()
    {
        return base.ToString() + $"House with outdoor area {OutdoorArea} and total area {TotalArea}";
    }
}