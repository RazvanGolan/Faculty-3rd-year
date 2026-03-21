using A1.Models;
using A1.Services;

var customer = new Customer("Alex Ionescu", "alex@example.com");
var products = new List<Product>
{
	new Product("Laptop", 4200m),
	new Product("Mouse", 150m),
	new Product("Keyboard", 300m)
};

var order = new Order(1001, customer, products);

var customerService = new CustomerService();
var checkoutService = new CheckoutService();
var reportService = new ReportService();

customerService.RegisterCustomer(customer);
customerService.UpdateCustomerEmail(customer, "alex.ionescu@example.com");

var standardTotal = checkoutService.ProcessStandardOrder(order);
var priorityTotal = checkoutService.ProcessPriorityOrder(order, 35m);

reportService.PrintOrderReport(order, standardTotal);
reportService.PrintArchivedOrderReport(order, priorityTotal);
