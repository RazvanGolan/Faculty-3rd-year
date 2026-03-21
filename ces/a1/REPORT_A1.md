# A1 Report - Code Duplication and Refactoring Proposals

## 1. Context and Objective
This report analyzes code duplications in the C# Console project located in the `a1` folder.
The goal is to identify relevant duplications and propose refactoring solutions for at least 3 cases.

## 2. Methodology
- Manual static analysis of files in `Models` and `Services`.
- Identification of similar instruction blocks (same logic, minor text/parameter variations).
- Grouping by duplication type: calculation, validation, formatting.

## 3. Identified Duplications

### Duplication #1: Subtotal + Tax + Total Calculation
Location:
- `Services/CheckoutService.cs` - `ProcessStandardOrder`
- `Services/CheckoutService.cs` - `ProcessPriorityOrder`

Observation:
- Both methods recalculate the subtotal by iterating through products.
- Both methods calculate tax using the same formula (`subtotal * TaxRate`).
- The only difference is the `priorityFee` added in the priority method.

Risk:
- If the pricing formula changes, it must be updated in 2 places.
- This increases the risk of divergence between flows.

Proposed refactoring:
- Extract Method: `CalculateSubtotal(Order order)`.
- Extract Method: `CalculateTax(decimal subtotal)`.
- Optional: an `OrderTotals` DTO/helper for clarity.

Benefit:
- A single modification point for financial logic.

---

### Duplication #2: Customer Data Validation
Location:
- `Services/CustomerService.cs` - `RegisterCustomer`
- `Services/CustomerService.cs` - `UpdateCustomerEmail`

Observation:
- Checks for `Name` and `Email` are repeated almost identically.
- Only the email source differs (`customer.Email` vs `newEmail`).

Risk:
- Validation rules may become inconsistent if one method is changed separately.

Proposed refactoring:
- Extract Method: `ValidateCustomerName(string name)`.
- Extract Method: `ValidateEmail(string email)`.
- Or a dedicated validator (`CustomerValidator`) reused across all operations.

Benefit:
- Centralized rules, easier to extend and test.

---

### Duplication #3: Order Report Format
Location:
- `Services/ReportService.cs` - `PrintOrderReport`
- `Services/ReportService.cs` - `PrintArchivedOrderReport`

Observation:
- The report structure (header, customer, products, total, separator) is repeated.
- The only difference is the title (`ORDER REPORT` vs `ARCHIVED ORDER REPORT`).

Risk:
- Format changes must be manually replicated in both methods.

Proposed refactoring:
- Extract Method: `PrintReport(Order order, decimal total, string title)`.
- Existing methods become simple wrappers that pass the appropriate title.

Benefit:
- Eliminates duplicated output logic and ensures visual consistency between reports.

## 4. Refactoring Prioritization
1. Duplication #1 (financial calculation) - direct functional impact, high priority.
2. Duplication #2 (validation) - data correctness impact, high priority.
3. Duplication #3 (report formatting) - maintainability impact, medium priority.

## 5. Conclusion
The project contains intentional duplications, useful for detection and refactoring exercises.
At least 3 significant duplications were identified and documented, and each has a clear refactoring direction with positive maintainability impact.
