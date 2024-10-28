namespace lab4;

public class RentableApartment(string address, double indoorArea, double propertyValue, int floor, bool hasElevator, bool isRented, double monthlyRent) 
    : Apartment(address, indoorArea, propertyValue, floor, hasElevator), IRentable
{
    public bool IsRented { get; set; } = isRented;
    public double MonthlyRent { get; set; } = monthlyRent;

    public override string ToString()
    {
        return base.ToString() + $"Rentable apartment is rented? {IsRented}. Monthly rent {MonthlyRent}";
    }
}