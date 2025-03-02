# Introduction

**SOLID** is an acronym for five design principles that help in writing maintainable, scalable, and robust software. These principles improve software architecture by making it more modular and flexible.

# Single Responsibility Principle
- A class should have only one reason to change
- It should have one and only one responsibility.
- This makes code more readable, testable, and maintainable.
Example:
```java
class Report {
    public void generateReport() {
        // Logic for generating report
    }
    public void printReport() {
        // Printing logic (violates SRP!)
    }
}
```
✅ Fix: Separate concerns into different classes:
```java
class ReportGenerator {
    public void generateReport() {
        // Logic for generating report
    }
}
class ReportPrinter {
    public void printReport() {
        // Logic for printing
    }
}
```

# Open close principle
- Open for extension but closed for modification.
- New functionality should be added without altering existing code.

**Example:**

❌ Violation:
```java
class DiscountCalculator {
    public double calculateDiscount(String type, double amount) {
        if (type.equals("NewCustomer")) {
            return amount * 0.1;
        } else if (type.equals("LoyalCustomer")) {
            return amount * 0.2;
        }
        return 0;
    }
}
```
✅ Fix: Use polymorphism to avoid modifying existing code:
```java
interface Discount {
    double apply(double amount);
}
class NewCustomerDiscount implements Discount {
    public double apply(double amount) {
        return amount * 0.1;
    }
}
class LoyalCustomerDiscount implements Discount {
    public double apply(double amount) {
        return amount * 0.2;
    }
}
class DiscountCalculator {
    public double calculateDiscount(Discount discount, double amount) {
        return discount.apply(amount);
    }
}
```

# Liskov Substitution principle
- If a class B is subtype of class A, then we should be able to replace the object of A with B without breaking the behaviour of the program. 
- Subtypes must be substitutable for their base types without altering correctness.
- Ensures that a derived class can be used in place of a base class without causing errors.

**Example:**

❌ Violation: A subclass that breaks the behavior of the base class.
```java
class Bird {
    void fly() {
        System.out.println("Flying");
    }
}
class Penguin extends Bird {
    void fly() { // ❌ Violates LSP (Penguins cannot fly!)
        throw new UnsupportedOperationException("Penguins cannot fly");
    }
}
```
✅ Fix: Use a better hierarchy:
```java
interface Bird {}
interface FlyingBird extends Bird {
    void fly();
}
class Sparrow implements FlyingBird {
    public void fly() {
        System.out.println("Flying");
    }
}
class Penguin implements Bird {
    // No fly method, no violation
}
```


# Interface Segmented principle
- Interfaces should be such, that client should not implement unnecessary functions that they do not need
- Clients should not be forced to depend on interfaces they do not use.
- Instead of one large interface, create smaller, specific interfaces.

**Example:**

❌ Violation: A class implementing unnecessary methods.
```java
interface Worker {
    void work();
    void eat();
}
class Robot implements Worker {
    public void work() {
        // Working logic
    }
    public void eat() { // ❌ Robots don’t eat! Violates ISP
        throw new UnsupportedOperationException("Robots don't eat");
    }
}
```
✅ Fix: Split interfaces based on responsibilities.
```java
interface Workable {
    void work();
}
interface Eatable {
    void eat();
}
class Robot implements Workable {
    public void work() {
        // Working logic
    }
}
class Human implements Workable, Eatable {
    public void work() {
        // Working logic
    }
    public void eat() {
        // Eating logic
    }
}
```

# Dependency inversion principle
- class should depend on interfaces rather than concrete classes
- High-level modules should not depend on low-level modules. Both should depend on abstractions.
- Abstractions should not depend on details. Details should depend on abstractions.

**Example:**

❌ Violation:
```java
class Keyboard {}
class Monitor {}
class Computer {
    private Keyboard keyboard;
    private Monitor monitor;
    public Computer() {
        keyboard = new Keyboard(); // ❌ Direct dependency on concrete class
        monitor = new Monitor();
    }
}
```
✅ Fix: Depend on interfaces instead of concrete classes.
```java
interface Keyboard {}
class MechanicalKeyboard implements Keyboard {}
class MembraneKeyboard implements Keyboard {}
class Computer {
    private Keyboard keyboard;
    public Computer(Keyboard keyboard) {
        this.keyboard = keyboard; // ✅ Now Computer is independent of Keyboard type
    }
}
```
