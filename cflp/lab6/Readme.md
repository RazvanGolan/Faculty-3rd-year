# Lab 6 
Delegates

# Exercises

1. Implement a function called Filter that takes a boolean function as a delegate and a list and returns a new list containing the elements that meet the condition.

```C#
public static List<int> MyFilter(MyDelegate condition, List<int> list)
```

2. Implement a static method FGX, which takes 2 delegates as parameters and a float x and returns the composite value of the two given functions.

```C#
public static float FGX(MyDelegate del1, MyDelegate del2, float x)
```

Test the implementation using the following methods
```C#
public static float f(float x)
{
    return x * 3;
}

public static float g(float x)
{
    return x - 2;
}
```