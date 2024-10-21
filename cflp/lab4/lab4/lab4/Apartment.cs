namespace lab4;

public class Apartment(string address, double indoorArea, double propertyValue, int floor, bool hasElevator) 
    : Property(address, indoorArea, propertyValue)
{
    public int Floor { get; set; } = floor;
    public bool HasElevator { get; set; } = hasElevator;

    public override string ToString()
    {
        return base.ToString() + $"Apartment at {Floor} floor and has elevator {HasElevator}";
    }
}