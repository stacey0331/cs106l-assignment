# CS106L Standard C++ Programming Notes
## Goals of CS106L 
1. Learn what features are out there in C++ and why they exist. 
2. Become comfortable with reading C++ documentation.
3. Become familiar with the design philosophy of modern C++. 

## OOP concepts
We often need OOP for: 
- Data hiding that is good for security concerns. 
- Closer to real-world problems.
- Ensure code usability, lets us write generic code so we don't have to write basic stuff over and over again. 

### Data Abstraction
Hiding background details or implementation. Consider a real-life example of a man driving a car. The man only knows to press the brakes and gas, but he doe not know how the inner mechanism of the brakes and gas. 

### Encapsulation
Wrapping up of data under a single unit. Variables or data of a class are hidden from any other class and can be accessed only through any member function of thier class. 

### Inheritance
A class can derive properties and chatracteristic from another class. 

#### Function Overriding
Redefinition of base class function in its derived class with the same signature. 
1. **Compile Time Function Overriding**
    ```c++
    class Parent {
    public:
        void GeeksforGeeks_Print()
        {
            cout << "Base Function" << endl;
        }
    };

    class Child : public Parent {
    public:
        void GeeksforGeeks_Print()
        {
            cout << "Derived Function" << endl;
        }
    };
    ```
2. **Runtime Function Overriding (Late Binding/Dynamic Binding)**
    ```c++
    class Base {
    public:
        virtual func()
        {
            // definition
        }
    };

    class Derived : public Base {
    public:
        func() override
        {
            // new definition
        }
    };
    ```
cons:
- Virtual function calls are generally slower than non-virtual functions because of virtual table lookup. 
- Virtual tables add to memory overhead. 
- Errors related to function overriding might only be detected at runtime. 

### Polymorphism

#### Compile-Time Polymorphism
1.  **Function Overloading**: 
Functions with the same name but different parameters. 
    ```c++
    class Geeks {
    public:
        // Function with 1 int parameter
        void func(int x)
        {
            cout << "value of x is " << x << endl;
        }
    
        // Function with same name but
        // 1 double parameter
        void func(double x)
        {
            cout << "value of x is " << x << endl;
        }
    
        // Function with same name and
        // 2 int parameters
        void func(int x, int y)
        {
            cout << "value of x and y is " << x << ", " << y
                << endl;
        }
    };
    ```

2. **Operator Overloading**: 
Provide the operators with special meaning for a data type. 
    ```c++
    public:
        Complex(int r = 0, int i = 0)
        {
            real = r;
            imag = i;
        }
    
        // This is automatically called
        // when '+' is used with between
        // two Complex objects
        Complex operator+(Complex const& obj)
        {
            Complex res;
            res.real = real + obj.real;
            res.imag = imag + obj.imag;
            return res;
        }
    ```
#### Runtime Polymorphism
Allows you to call derived class methids through a base class pointer. The devision about which method to call is made ar runtime. 
Primarily achieved through virtual functions. 
```c++
#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() { // Virtual function
        cout << "Display function of Base class" << endl;
    }

    void show() {
        cout << "Show funciton of Base class" << endl;
    }
};

class Derived : public Base {
public:
    void display() override { // Override the base class function
        cout << "Display function of Derived class" << endl;
    }

    void show() {
        cout << "Show funciton of Derived class" << endl;
    }
};

int main() {
    Base* basePtr;
    Derived derivedObj;
    basePtr = &derivedObj;

    basePtr->display(); // Outputs: "Display function of Derived class"
    basePtr->show(); // Output: "Show function of Based class"
    return 0;
}
```

## Lecture 1: Intro
### Why C++? 
- C++ is a strong performance language. 
- Browsers are all written in C++ (chrome, safari, etc.) because performamce is important. 
- Java is written in C++. 
- CS106L uses C++17 (and sneak peek into C++20). 
### History of C++
- C++ is backward compatible. You can put C and assembly code in there. 
- Compiler: a program that convert C/C++ code into assembly.
- C is fast, simple, cross-platform. However it is difficult to write code that work generically in C, which makes it tedious when writing large programs. 
- C++ is fast, simple, cross-platform, and has high level features. 
### Design Philosophy of C++
- Allow the programmer full control, responsibiity, and choice if they want it (e.g. heap memory). 
- Express ideas and intent directly in code. For example, instead of finding sum of vector through for loop, we use std::accumulate. 
- Enforce satefy at compile time whenever possible. Or the compiler is really good at checking errors. 
- Do not waste time or space. 
- Compartmentalize messy constructs. 
### Look at some code
- #include <>: predefined libraries
- #include "": classes we defined ourselves. 
- All standard library header files part of the std namespace. 

## Lecture 2: Streams
- In C++ you can treat string as an array of character (so you can do str[1]='i'). 
- C string has type char *, C++ string has type string. 
- Stream usecases: console & keyboard, files, other programs (pipelines), and sockets (networking).

### stringstream
A stringstream is not connected to any external source. 
- ostringstream: can write to it, but can't read it. 
Use ostringstream::ate to append string at the end instead of overwritting. 
- cout is also a stream.

`istringstream`
```c++
int main() {
    istringstream iss("16.9 Ounces");
    double amount; // type matters. will grab the type
    string unit;

    iss >> amount; // grab until reaches white space
    iss >> unit;

    count << amount/2 << endl;
}
```
The above program will print 8. 

You can chain operations. 
```C++
// convert var1 to characters then insert into oss buffer, then var2
oss << var1 << var2; 
// extracted from iss's buffer, reads into v1, then extract and read into v2. 
iss >> var1 >> var2; 
```

Example: implement the string to integer function
```c++
int stringToInteger(const string& s) {
    istringstream iss(s);
    int output;
    iss >> output;
    return output;
}
```
### State Bit
G. Good: ready for read/write. 

F. Fail: previous operation failed, all future operations frozen. Usually happen because of type mismatch, file cannot be opened. 

E. EOF: previous operation reached the end of buffer content. 

B. Bad: external error, likely irrecoverable. Example of why this happen would be the file you are reading from suddenly is deleted. 

```c++
istringstream iss(str);
int result;
iss >> result; // this op returns the stream as a boolean of whether the op is successful (fail bit off)
if (iss.fail()) throw std::domain_error("no value int at beginning!");
char remain;
iss >> remain;
if (!iss.fail()) throw std::domain_error("more stuff after a valid int!");
```

### Buffer & Flush
`cout` is a buffer string. It will wait to print stuff out. The below program will print CS106L all at once. 
```c++
cout << "CS";
mindlesswork();

cout << "106L";
mindlesswork();

cout << endl; // endl consist of '\n' and flush
```
`cerror` has no buffer, which means eveything prints out immediately. The below program will print CS and then 106L seperately. 
```c++
cerror << "CS";
mindlesswork();

cerror << "106L";
mindlesswork();

cerror << endl;
```
Use `endl` at the end once will make the code much faster than using `endl` all the time (aka. flush all the time).
If you are writing high performance code, don't use `endl` too much!

There are a few operations that will automatically trigger flush (e.g. cin will flush cout).

## Lecture 3: Types and Advanced Streams
### `cin`
- `cin`'s position pointer skip whitespace before the token with each >> operation. 
- `cin` reads up to the white space but does not consume/include the white space. 
- `cin` will stall when nothing is in the buffer (waiting for user to type something). 

### getline
- Reads up to new line character, and cosumes the new line character. Or it reads up to end of the buffer. 
- Cleaner for prompting responses than `cin`. 
    ```c++
    string name;
    getline(cin, name);
    ```
- Does not skip the white space at the beginning. 

### getInteger
```c++
int getInteger(const sring& prompt, const string& reprompt) {
    while(true) {
        cout << prompt;
        string line; int result; char trash;
        if (!getline(cin, line)) throw domain_error(...);
        istringstream iss(line);
        if (iss >> result && !(iss >> trash)) return result;
        cout << reprompt << endl;
    }
}
```

### Modern C++ Types
#### Type Aliases
```c++
using map_iterator = std::unordered_map<forward_list<Student>, unordered_set>::const_iterator;

map_iterator begin = studentMap.cbegin();
```
#### Auto
Use when:
- You don't care what the type is (iterators).
- Its type is clear from context (templates).
- You don't know what the type is (lambdas). 

Some gotchas: 
```c++
// cannot use auto for parameters!
auto calculateSum(const vector<string>& v) {
    auto name = "Avery"; // char * 
    auto betterName1 = string{"Avery"} // string
    const auto& betterName2 = string{"Avery"} // const string&
    auto copy = v; // vector<string>, w/o const
}
```
Normally we should use C++ string. However there are some cases where the functions only can take C strings. 

#### Structure Binding (C++ 17)
```c++
auto prices = make_pair(3.4, 5); // pair<double, int>
auto [a,b] = prices;
```

#### `struct`
```c++
struct Discount {
    double discoutFactor;
    int expirationDate;
    string nameOfDiscount;
}
auto coupon1 = Discount{0.9, 30, "New Years"};
auto [factor, date, name] = coupon1; // structure binding C++17
```
### Parameters
- Pass by value `f(X)`: cheap to copy or impossible to copy (e.g. int, unique_ptr). 
- Pass by reference `f(X&)`: use when expensive to copy. 

## Assignment WikiRacer
### Overview
- `std::search`: use when looking or an occurance of multiple elements in a row in a container. 
- `std::find`: use when looking for an occurrence of a single character in a container. 
- `std::count_if`: Returns the number of elements in the range [first, last) satisfying specific criteria. Can use lambda function as criteria. 
- Priority queue comparator funciton: 
    ```c++
    // max heap, pop order 5,4,3,2,1
    auto cmp = [](int left, int right) { return left < right; };

    // min heap, pop order 1,2,3,4,5
    auto cmp = [](int left, int right) { return left > right; };
    ```
    I thought it would be the oppositie. Kind of unintuitive. 
### Code
My implementation is [here](https://github.com/stacey0331/cs106l-assignment/tree/master/WikiRacer). 










