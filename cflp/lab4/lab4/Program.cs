using lab4;

var house = new House("address1", 100, 200, 300);
var apartment = new Apartment("address2", 200, 300, 4, true);
var rentalApartment = new RentableApartment("address3", 200, 300, 4, false, false, 2000);

var realEstateAgency = new RealEstateAgency();

realEstateAgency.AddProperty(house);
realEstateAgency.AddProperty(apartment);
realEstateAgency.AddProperty(rentalApartment);

Console.WriteLine(realEstateAgency);

realEstateAgency.RentProperty("address3");
realEstateAgency.RentProperty("address3");
realEstateAgency.RentProperty("address2");