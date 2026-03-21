# A1 - C# Console App with Intentional Code Duplication

This project is intentionally written with duplicate code blocks for code-smell detection and refactoring exercises.

## Intentional duplication areas

1. Price calculation duplication
- `Services/CheckoutService.cs`
- `ProcessStandardOrder` and `ProcessPriorityOrder` both repeat subtotal + tax logic.

2. Validation duplication
- `Services/CustomerService.cs`
- `RegisterCustomer` and `UpdateCustomerEmail` both repeat customer validation rules.

3. Report formatting duplication
- `Services/ReportService.cs`
- `PrintOrderReport` and `PrintArchivedOrderReport` both repeat report layout and product listing output.

## Run

```bash
dotnet run
```
