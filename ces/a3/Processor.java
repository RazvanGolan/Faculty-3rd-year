
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Processor {

    public List<Car> cars;

    public Processor(List<Car> cars) {
        this.cars = cars;
    }

    public void processCars() {
        for (Car c : cars) {
            // Generating car info
            // Generare informații masina
            String cI = "Car: " + c.getBrand() + ", HorsePower: " + c.getHorsePower() + ", Color: " + c.getColor();
            System.out.println(cI);

            // Calculating average price of car functions
            // Calcularea pretului mediu al functiilor masinii
            double t = 0;
            for (CarFunction carFunction : c.getCarFunctions()) {
                t += carFunction.getPrice();
            }
            double avg = t / c.getCarFunctions().size();
            System.out.println("Average Price: " + avg);

            // Categorizing the average price of car functions
            // Clasificarea pretului mediu al functiilor masinii
            String cat;
            if (avg >= 900) {
                cat = "Expensive";
            } else if (avg >= 750) {
                cat = "Affordable";
            } else if (avg >= 500) {
                cat = "Cheap";
            } else {
                cat = "Promo";
            }
            System.out.println("Price Category: " + cat);
        }
    }

    // Method 1: Returns a list of all car brands in lowercase, having the color "grey".
    public List<String> methodOne() {
        return cars.stream()
                .filter(car -> "grey".equals(car.getColor()))
                .map(car -> car.getBrand().toLowerCase())
                .collect(Collectors.toList());
    }

    // Method 2: Returns a list of all car brands in uppercase, having the average price of their functions greater than or equal to 900.
    public List<String> methodTwo() {
        return cars.stream()
            .filter(car -> car.getCarFunctions().stream()
                .mapToDouble(CarFunction::getPrice)
                .average()
                .orElse(0.0) >= 900)
            .map(car -> car.getBrand().toUpperCase())
            .collect(Collectors.toList());
    }

    // Method 3: Returns the average power of cars with the color "red" and the average price of their functions over 600. Throws CarException if no such cars exist.
    public double methodThree() {
        return cars.stream()
            .filter(car -> "red".equals(car.getColor()))
            .filter(car -> car.getCarFunctions().stream()
                .mapToDouble(CarFunction::getPrice)
                .average()
                .orElse(0.0) > 600)
            .mapToInt(Car::getHorsePower)
            .average()
            .orElseThrow(CarException::new);
    }

    // Method to help methodFour get all distinct names of car functions
    private Set<String> getAllCarFunctionNames() {
        Set<String> allSubjectNames = new HashSet<>();
        for (Car car : cars) {
            for (CarFunction carFunction : car.getCarFunctions()) {
                allSubjectNames.add(carFunction.getName());
            }
        }
        return allSubjectNames;
    }

    // Method 4: Returns a dictionary (map) in which the keys are names of car functions, and the values are lists of cars sorted by the price of the respective function.
    // The list should include only cars with a price over 500 for the respective function.
    // Hint: You can use the getPriceForCarFunction(String carFunctionName) method from the Car class which returns the price of a car function by its name.
    public Map<String, List<Car>> methodFour() {
        Set<String> allCarFunctionNames = getAllCarFunctionNames();
        return allCarFunctionNames.stream()
            .collect(Collectors.toMap(
                Function.identity(),
                carFunctionName -> cars.stream()
                    .filter(car -> car.getPriceForCarFunction(carFunctionName)
                        .map(price -> price > 500)
                        .orElse(false))
                    .sorted(Comparator.comparing(car ->
                        car.getPriceForCarFunction(carFunctionName).orElse(Double.MAX_VALUE)))
                    .collect(Collectors.toList())
            ));
    }

    // Method 5: Prints the brand of cars which have a price under 500 for any function of the car and returns a list with these cars.
    public List<Car> methodFive() {
        return cars.stream()
                .filter(car -> car.getCarFunctions().stream().anyMatch(carFunction -> carFunction.getPrice() < 500))
                .peek(car -> System.out.println(car.getBrand()))
                .collect(Collectors.toList());
    }

    // Method 6: Returns a dictionary (map) in which the keys are cars and the values are the average prices for the functions of the car.
    public Map<Car, Double> methodSix() {
        return cars.stream()
            .collect(Collectors.toMap(
                Function.identity(),
                car -> car.getCarFunctions().stream()
                    .mapToDouble(CarFunction::getPrice)
                    .average()
                    .orElse(0.0)
            ));
    }
}
