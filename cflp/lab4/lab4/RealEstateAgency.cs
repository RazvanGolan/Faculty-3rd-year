namespace lab4;

public class RealEstateAgency
{
    private List<Property> Properties = [];

    public void AddProperty(Property property)
    {
        Properties.Add(property);
    }

    public void RentProperty(string propertyAddress)
    {
        foreach (var prop in Properties)
        {
            if (prop.Address != propertyAddress) continue;

            if (prop.GetType() != typeof(RentableApartment))
            {
                Console.WriteLine($"This apartment is not rentable");
                return;
            }

            var rentableApartment = (RentableApartment)prop;

            if (rentableApartment.IsRented)
            {
                Console.WriteLine($"Apartment is already rented");
                return;
            }

            rentableApartment.IsRented = true;
            Console.WriteLine($"RENTED");
        }
    }

    public override string ToString()
    {
        var propertiesString = "";
        foreach (var property in Properties)
            propertiesString += property + "\n";

        return propertiesString;
    }
}