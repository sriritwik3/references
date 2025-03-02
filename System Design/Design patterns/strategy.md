# Strategy Design Pattern

## **Introduction**

The **Strategy Pattern** is a **behavioral design pattern** that enables selecting an algorithm's behavior at runtime. It defines a family of algorithms, encapsulates them, and makes them interchangeable without modifying client code.  
The Strategy Pattern is used when multiple objects require different variations of a behavior. Instead of implementing these behaviors in subclasses (which can lead to code duplication and rigid inheritance), we extract the behavior into separate strategy classes and make them interchangeable at runtime.
### **Key Features**

✅ Allows runtime selection of algorithms.  
✅ Promotes **Open/Closed Principle** (OCP).  
✅ Avoids **if-else** or **switch-case** conditions for algorithm selection.  
✅ Enhances **maintainability** and **scalability**.  

---

## **Implementation Structure**

The Strategy Pattern consists of:

1. **Strategy Interface** – Defines a contract for different strategies.
2. **Concrete Strategies** – Implement different variations of the strategy.
3. **Context Class** – Uses a strategy instance at runtime.

---

## **Example: Payment System**

We will implement a **payment system** that allows users to choose between different payment methods dynamically.

### **Step 1: Create the Strategy Interface**

```java
interface PaymentStrategy {
    void pay(int amount);
}
```

### **Step 2: Implement Concrete Strategies**

```java
class CreditCardPayment implements PaymentStrategy {
    private String cardNumber;
    public CreditCardPayment(String cardNumber) {
        this.cardNumber = cardNumber;
    }
    public void pay(int amount) {
        System.out.println("Paid " + amount + " using Credit Card: " + cardNumber);
    }
}

class PayPalPayment implements PaymentStrategy {
    private String email;
    public PayPalPayment(String email) {
        this.email = email;
    }
    public void pay(int amount) {
        System.out.println("Paid " + amount + " using PayPal: " + email);
    }
}
```

### **Step 3: Create the Context Class**

```java
class PaymentContext {
    private PaymentStrategy paymentStrategy;
    public void setPaymentStrategy(PaymentStrategy paymentStrategy) {
        this.paymentStrategy = paymentStrategy;
    }
    public void executePayment(int amount) {
        if (paymentStrategy == null) {
            throw new IllegalStateException("Payment strategy not set");
        }
        paymentStrategy.pay(amount);
    }
}
```

### **Step 4: Client Code (Using the Strategy Pattern)**

```java
public class StrategyPatternDemo {
    public static void main(String[] args) {
        PaymentContext context = new PaymentContext();
        
        // Use Credit Card Payment
        context.setPaymentStrategy(new CreditCardPayment("1234-5678-9876"));
        context.executePayment(100);
        
        // Use PayPal Payment
        context.setPaymentStrategy(new PayPalPayment("user@example.com"));
        context.executePayment(200);
    }
}
```

### **Output:**

```
Paid 100 using Credit Card: 1234-5678-9876
Paid 200 using PayPal: user@example.com
```

---

## **UML Diagram for Strategy Pattern**

```plaintext
+-------------------+
|  PaymentStrategy  |<<interface>>
|-------------------|
| +pay(amount)      |
+-------------------+
        ▲
        │
        │
+--------------------+      +----------------+
| CreditCardPayment |      |  PayPalPayment |
|--------------------|      |----------------|
| -cardNumber       |      | -email          |
|--------------------|      |----------------|
| +pay(amount)      |      | +pay(amount)    |
+--------------------+      +----------------+
        ▲
        │
        │
+-------------------+
|  PaymentContext  |
|-------------------|
| -paymentStrategy |
|-------------------|
| +setPaymentStrategy() |
| +executePayment() |
+-------------------+
```

---

## **Advantages of Strategy Pattern**

✅ **Reduces if-else complexity** – Avoids multiple conditional checks.  
✅ **Enhances flexibility** – Algorithms can be easily added or replaced.  
✅ **Follows Open/Closed Principle (OCP)** – New strategies can be added without modifying existing code.  
✅ **Encourages reusability** – Different parts of the application can use the same strategies.  

---

## **Use Cases of Strategy Pattern**

✔ Payment processing (Credit card, PayPal, etc.)  
✔ Sorting algorithms (Bubble Sort, Quick Sort, Merge Sort, etc.)  
✔ Compression algorithms (ZIP, RAR, GZIP, etc.)  
✔ Authentication mechanisms (OAuth, JWT, SAML, etc.)  
✔ Logging strategies (File logging, Database logging, Console logging)  

---

## **Conclusion**

The **Strategy Pattern** helps in writing flexible, reusable, and scalable code by allowing dynamic selection of algorithms. It is widely used in real-world applications like **payment gateways, authentication systems, and sorting mechanisms**.

By implementing the **Strategy Pattern**, you can make your code **cleaner, more maintainable, and easier to extend!** 🚀
