namespace lab4;

public class Property(string address, double indoorArea, double propertyValue)
{
    public string Address { get; set; } = address;
    public double IndoorArea { get; set; } = indoorArea;
    public double PropertyValue { get; set; } = propertyValue;

    public override string ToString()
    {
        return $"Property with address {Address}, indoor area {IndoorArea}, property value {PropertyValue}";
    }
}