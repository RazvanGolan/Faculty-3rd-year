# Lab 9

Asynchronous programming

# Exercise

Create a **Tamagotchi game**. Each Tamagotchi pet must be fed regularly, or it will starve. If overfed, the Tamagotchi will also die. The goal is to keep it alive as long as possible.

## Required Classes

### 1. `InputReader`
- **Attributes**:
    - `EventHandler<string>`: `OnKeyPressed`.
- **Methods**:
    - `ReadKeys()`: Reads input from the console using `Console.ReadLine()` until an empty string is detected. After each input, the `OnKeyPressed` event is invoked.

### 2. `Tamagotchi`
Responsible for managing the lifecycle of a Tamagotchi.

#### Properties
- `string Name`
- `int Food`: If it reaches `0`, the Tamagotchi will starve.
- `int HungerRate`: Time interval in milliseconds for food reduction.
- `bool IsAlive`: Tamagotchi's current status.
- `string Keys`: Keys used to feed the Tamagotchi.

#### Constructor
- Accepts:
    - `name` (string),
    - Initial food amount (`int`),
    - Hunger rate (`int`),
    - Keys for feeding (`string`),
    - An `InputReader` instance.
- Subscribes to `OnKeyPressed` from `InputReader` with `HandleKeyPressed`.
- `HandleKeyPressed`:
    - Feeds the Tamagotchi 5 food units when the designated keys are pressed.
    - If `Food > 20`, the Tamagotchi dies of overfeeding.

#### Methods
- `async Run()`:
    - Simulates Tamagotchi's life.
    - Runs while the Tamagotchi is alive.
    - After every `HungerRate` interval, subtracts 3 food units.
    - If `Food == 0` or `Food > 20`, the Tamagotchi dies.
    - Displays Tamagotchi's status after each interval.

- `ToString()`:
    - Displays status:
        - `"Name is healthy and alive. Food remaining: Food;"`
        - `"Name is dead :("`
