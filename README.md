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
Allows you to call derived class methods through a base class pointer. The decision about which method to call is made at runtime. 
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

## Lecture 4: Sequence Containers 
### Struct in C++
Works like object except everything is public. 
```c++
PriceRange findPriceRange(int dist) {
    int min = static_cast<int>(dist * 0.08 + 100);
    int max = static_cast<int>(dist * 0.36 + 750);
    return PriceRange{min, max};
}

in main() {
    int dist = 6452;
    PriceRange p = findPriceRange(dist);
    cout << "Price range between: " << p.min << " and " << p.max; // can change p.min and p.max here too
}
```

### Initialization
There are 27 ways to initialize a variable in C++. 

#### Uniform Initialization:
```c++
int main() {
    vector<int> vec{3,1,4,1,5};
    Course now {"CS106L", {15,30}, {"Wang", "Zeng"}};
}
```

#### `initializer_list`
A lightweight vector that can be used as a parameter. Provides read-only view over a set of values. 

```c++
#include <iostream>
#include <initializer_list>

class MyClass {
public:
    MyClass(std::initializer_list<int> list) {
        for (int value : list) {
            std::cout << value << " ";
        }
    }
};

int main() {
    MyClass obj = {1, 2, 3, 4, 5};
    return 0;
}
```

#### Initializer List vs. Constructor
```c++
int main() {
    vector<int> vec1{3}; // vector = {3}
    vector<int> vec2(3); // vector = {0,0,0}
    // note: you can count on c++ zero initializing if it's a global variable or you specified it. 
}
```
### When to Use `stringstream`
- Processing/formatting strings. 
    - Simplify file path
    - Uppercase, hex, and other stream manipulators. 
- Parsing different types. 
    - stringToInteger() from previous lectures. 
So for example if you are just concatenating strings, stringstream is unnecessary and too much overhead. 

### Overview of STL
STL functions are optimized. So it's faster to use them than writing it yourself!
An example of using all STL:
```c++
int main() {
    vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), rand);
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, "\n"));
    return 0;
}
```
### Sequence Containers 
Includes:
- std::vector<T>
- std::deque<T>
- std::list<T>
- std::array<T>
- std::forward_list<T>
#### vector
When access with [], must check for bounds because it causes undefiend/unpredictable behavior. 
#### deque
Essentially a vector, but you can push to the front and back efficiently (constant time). However deque has slower access than vector.

## Lecture 5: Associative Containers & Iterators
### Container Adaptors
- Stack: just limited funcitonality of vector/deque. Only allow push_back and pop_back.
- Queue: just limited functionality of deque. Only allow push_back and pop_front. 
Plus only allow access to top element. 

#### Why? 
- Express idea and intent directly in code. 
- Compartmentalize messy contructs. 

### Associative Containers
Data is accessed using the key instead of indices. 
Includes:
- std::map<T1,T2>
- std::set<T>
- std::unordered_map<T1,T2>
- std::unordered_set<T>

#### When to use what? 
- map/set: keys in sorted order, faster to iterate through a range of elements. 
- unordered map/set: faster to acess individual elements by key. 
Map and set are fast for lookup because they are implemented with binary search tree. 

#### [] vs `get`
```c++
freqMap[word]; // automatically create an entry and default initialize it. 
freqMap.get(word); // throw error if key not exist
```

#### `count`
`freqMap.count(response)` : count how many key equal to response. This is either going to be 1 or 0 for map.

### Iterators
How we iterate over associative containers?
Iterators allow iteration over any container, whether is it ordered or not.  


Example:
```c++
// Example 1: 
set<int>::iterator itr = container.begin();
while (itr != container.end()) {
    count << *itr << ' ';
    ++itr;
}
cout << endl;
// Example 2:
set<int>::iterator itr2;
for(itr2 = container.begin(); itr2 != container.end(); ++itr2) {
    cout << *itr2 << ' ';
}
cout << endl;
```
## Lecture 6: Advanced Iterators & Containers
### `std::pair` Class
How to make pair:
method 1: `std::pair<string, int> p{"Phone number", 6507232300};`
method 2: `std::make_pair("Phone number", 6507232300);`
What's the difference? `make_pair` automatically deduces the type. 

### Multimaps
Permits multiple entries with the same key. So doesn't have [] operator. 
```c++
std::multimap<int, int> myMMap;
myMMap.insert(make_pair(3,3));
myMMap.insert({3,12});
cout << myMMap.count(3) << endl; // prints 2
```

### Map Iterators
Dereferencing it will give a pair. So you can access `(*i).first` and `(*i).second`. The parentheses has to be there, or you can use `i->first` and `i->second`. 

### Iterator Methods Exampels
```c++
const int ELEM_TO_FIND = 5;
int main() {
    // sort
    vector<int> vec{3,1,4,1,5,2,6};
    std::sort(vec.begin(), vec.begin()+4);

    // find
    set<int> elm{3,1,4,5,6,2,6};
    auto testit = std:find(elm.begin(), elm.end(), ELEM_TO_FIND);
    if (testit == elm.end()) {
        cout << "Not found!" << endl;
    }

    // lower_bound, upper_bound are associative containers member functions
    set<int>::iterator iter = elm.lower_bound(4); // first element that is not less than 4
    set<int>::iterator end = elm.upper_bound(6); // first element that is greater than 6 
    for (; iter != end; ++iter) {
        cout << *iter << " "; 
    }
}
```

### Range Based for Loop
A range based for loop is (more or less) a shorthand for iterator code:
```c++
map<string, int> myMap;
for(auto thing: myMap) {
    doSomething(thing.first, thing.second);
}
```

### Iterator Types
Order from least powerful to most:
1. Input
2. Output
3. Forward
4. Bidirectional
5. Random access

#### Input Iterators
For sequential, single-pass input. 
Read only i.e. can only be dereferenced on right side of expression. 

Use cases: `find`, `count`, input streams. 
#### Output Iterators
For sequential, single-pass output. 
Write only i.e. can only be dereferenced on left side of expression. 

Use cases: `copy`, output streams
#### Forward Iterators
Combines input and output iterators + can make multiple passes. 
Mutliple passes means you can traverse the same sequence multiple times using multiple instances of iterators without invalidating the iterators. 

#### Bidirectional Iterators 
Same as forward iterators + can go backwards with --. 

Use cases: `reverse`, `std::map`, `std::set`, `std::list`. 

#### Random Access Iterators
Same as bidirectional iteratoes + can increment or decrement by arbitrary amounts. 

Use cases: `std::vector`, `std::deque`, `std::string`, `pointers`. 

##### Side note: you could think of pointers like a class and iterator like an interface. 

## Lecture 7: Templates
In C++, you can do procedural programming (like C), you can do OOP, and you can do generic programming. Today's lecture is about generic programming! 

### Simple Template Function Example:
```c++
template <typename T> 
pair<T,T> my_minmax(T a, T b) {
    if (a < b) return {a, b};
    else return {b, a};
}

int main() {
    auto [min1, max1] = my_minmax<double>(4.2, -7.9); // replaced at compile time
}
```
### Get Type Value Example: 
```c++
template<typename T>
T getTypeValue() {
    while (true) {
        cout << "Enter a " << typeid(T).name() << ": ";

        string line, T result, char extra;
        if (!getline(cin, line))
            throw domain_error("Unable to get line from cin. ");
        istringstream iss(line);
        if (iss >> result && !(iss >> extra)) return result;
        cout << "Invalid format." << endl; 
    }
}
```

### Generic Programming and Lifting
concept lifting: looking at the assuptions you place on the parameters and questioning if they are really necessary. Can you solve a more general problem by relaxing the constraints?

A super generic function (we assume the least possible):
```c++
template <typename InputIterator, typename DataType>
int countOccurences(InputIterator begin, InputIterator end, DataType val) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter == val) ++count;
    }
    return count;
}
```
Note that we use `InputIterator` because the data types that doesnt use iterator more powerful than it will still work!

## Lecture 8: Functions and Algorithms
### Different Rules for Invalidated Iterators for Different Containers:
- vector: all iterators after erasure point invalidated. 
- deque: all iterators invalidated, unless erasure point was front or back. 
- list/set/map: all other iterators are still valid. 

### Implicit Interfaces
In your template function, you implicitly specified that a certain parameters has to be a certain type. For example, if there's `*iter` in your function, you implicitly requires the iterator parameter to be input iterator. 

### Concept Lifting Part 2
**Predicate**: a function which takes in some number of arguments and return a boolean. 

### Lambda Functions
- Started c++11. Before c++11 you need to use functor. 
- Lambdas are a type of function object (functor). 
- You can use auto as parameters in lambda functions. 
```c++
// return type is optional
// limit is out of scope, so have to capture limit. 
int limit = 5;
int called = 0;
auto isLessThanLimit = [&limit, &called](auto val) -> bool {
    ++called;
    return val < limit;
};
```

### Lazy Capture
```c++
// capture all by reference, except banned by value
auto isLessThanLimit = [&, banned](auto val) -> bool {
    ...
};

// capture all by value, except teas by reference
auto isLessThanLimit = [=, &teas](auto val) -> bool {
    ...
};
```

### STL Algorithms
We will explore:
- std::sort
- std::nth_element
- std::stable_partition
- std::copy_if
- std::remove_if

#### `std::sort` Example:
```c++
std::sort(numbers.begin(), numbers.end());

auto compareRating = [](const Course& c1, const Course& c2) {
    return c1.rating < c2.rating;
};
std::sort(courses.begin(), courses.end(), compareRating); // because course is a type struct we need to specify predicate functions.
```

#### `std::stable_partiion`
Rearrange the vector so that true is at the front false is at the back, while preserve the original relative order. 

#### `std::copy_if`
`back_inserter` is a iterator adaptor that extends the container. 
```c++
std::copy_if(csCourses.begin(), csCourses.end(), back_inserter(csCourses), isDep);
```

#### Erase-Remove Idiom
`remove_if` returns iterator to beginning of trash, and `erase` erases trash from the iterator to the end. 
```c++
v.erase(
    std::remove_if(v.begin(), v.end(), pred), 
    v.end()
);
```

## Lecture 9: STL Applications
Wraping up the STL! 

Instead of `using namespace std`, use aliases to be more specific:
```c++
using std::cout;
```

Example: get file content as a string, all lower cased. 
```c++
string fileToString(ifstream& file) {
    string ret = "";
    string line;

    while (std::getline(file, line)) {
        std::transform(line.begin(), line.end(), line.begin(), tolower);
        ret += line + " ";
    }
    return ret;
}
```

## Lecture 10: Class Design
C++ is not a OOP solely, it's only one of the ways we can use C++. We can also use C++ as a functional language, etc. 

### File Extensions
The `.h` file is where you specify the interface for your class. It's like a public facing API that you want other classes to use from your class. 

Depending on the compiler you can uses these extensions: 
- Header file: .h, .hh, .hpp
- Source file: .cc, .cpp, .cxx, .c++, .C
Now, Unix mostly uses `.cc` and outside of Unix mostly uses `.cpp`. Besides, `.h` is technically for C programs, so if mixing C and C++ code, use `.hh` instead. 

### `const`
Use `const` when possible, for safety reasons. 

There is a `const_cast` to cast away the constness but it is not advised to use it. 

`const` on objects guarantees that the object won't change by allowing you to call only const functions and you cannot modify the object's member variables. 

`const` on functions guarantees that the function won't call anything but const functions, and won't modify any non-static or non-mutable members. 

### Const Content or Const Pointer?
```c++
// constant pointer to a non-constant int
int * const p;  // the pointer is const
                // (*p)++; ok!
                // p++; not allowed!

// non-constant pointer to a constant int
const int* p; // the int is const
int const* p;
```

There's also const iterators:
```c++
vector v{1,2312};
const vector<int>::iterator itr = v.begin();
++itr;             // does NOT compile
*iter = 15;        // compiles!

vector<int>const_iterator itr = v.begin();
*itr = 5;           // does NOT compile
++itr;              // compiles!
int value = *itr;   // OK! reading from itr
```

## Lecture 11: Operators
There are 40(+4) operators you can overload!

### Example: Overloading += in vector
```c++
vector<string>& vector<string>::operator+=(const std::string& element) {
    push_back(element);
    return *this;
}
```

We should return by reference because if someone does something like below, the second string would not be added to the vector correctly:
```c++
const string s = "Ito-En";
(vec += s) += "Green Tea";
```

Why we don't need to take in the vector as parameter? Because essentially `vec += "Green tea";` is the same as `vec.operator+=("Green tea");`, and we can retrieve the vector with `this`. 

### Example: Overloading + in vector
Notice we return by copy because we are not changing neither of the vectors. We are return a new vector that combines both vectors. 

```c++
StringVector StringVector::operator+(const StringVector& other) {
    Stringvector result = *this; // copy constructor
    for (const std::string s : other) {
        result.push_back(s);
    }
    return result;
}
```

### Non Member Function
```c++
StringVector operator+(const StringVector& first, const StringVector& second) {
    StringVector result = first;
    for (const std::string& s: second) result += s;
    return result;
}
```

### Member Function vs. Non Member Function
Member Functions: Unary operators, assignment operators, and operators modifying the object (++, --, =, +=, [], (), ->).

Non-Member Functions: Binary operators where symmetry is important or where the left operand is not a class object (+, -, *, /, ==, !=, <, >, etc.). Also the >> operator because you cannot modify the definition of the istream/ostream class. 

### Friend Function
The friend function is outside of the class but can still access private variables. So you need them to access private member variables. 

To declare friend function: 
```c++
private:
    friend operator <<(ostream& os, const Fraction& f);
```

### Principle of Least Astonishment (POLA)
- Design operators primarily to mimic conventional usage. 
- Don't make surprises or things people won't understand. 
- Implement none or all operators in one category, otherwise it will be surprises to other people. For example if you implement + please implement - too. 

### Spaceship Operator
Use spaceship operator so you don't need to define so many operators:
```c++
std::strong_ordering operator<=>(const Point& other) const {
    if (auto cmp = x <=> other.x; cmp != 0) {
        return cmp;
    }
    return y <=> other.y;
}
```

## Lecture 12: Special Member Functions
If you don't declare these functions, the compiler will create it for you. 

### Initialization List
Can only be used for constructors. Reasons for using initialization list:
- Necessary for const members, reference members, and base class members (because we need to make sure all base class members are initialized before the derived class members). 
- Improves performance by avoiding extra cost to default constructor and assignment operators. 

```c++
StringVector::StringVector():
    logicalSize(0), allocatedSize(kInitialSize) {
        elems = new std::string[allocatedSize];
}
```
Note you have to initialize them in the order of the private members are declared in your class. 

### Special Member Functions
The compiler will (usually) automatically genrates:
- Default constructor: object created with no parameters. 
- Copy constructor: object is created as a copy of an existing object. 
- Copy assigment: existing object replaced as a copy of another existing object (for this just implement the operator equal size). 
- Destructor: object destroyed when it is out of scope. 

### Constructor
```c++
StringVector vec3();      // function protoytpe...
StringVector vec5{};      // default constructor
StringVector vec6{vec3 + vec4};  // copy constructor
StringVector vec7 = vec4;  // copy constructor
vec7 = vec2;      // copy assignment
return vec7;     // copy constructor: creates a copy of local variable to be returned. 
```

### Copy Constructor Example / Deep Copy Vector
```c++
StirngVector::StringVector(const StringVector& other): logicalSize(other.logicalSize), allocatedSize(other.allocatedSize):
    elems = new std::string[allocatedSize];
    std::copy(other.begin(), other.end(), begin());
```

### Implement Copy Assignment Example
```c++
// return by reference because might do v1=(v2=v3)
StringVector& StringVector::operator=(const StringVector& other) {
    if (this != &other) {
        delete[] elems; // free original list
        allocatedSize = other.allocatedSize;
        logicalSize = other.logicalSize;
        elems = new std::string[allocatedSize];
        std::copy(other.begin(), other.end(), begin());
    }
    return *this;
}
```

### Disable Copy Constructor
```c++
class LoggedVector {
    public:
        LoggedVector(int num, int denom);
        ~LoggedVector();
        LoggedVector(const LoggedVector& rhs) = delete;
        LoggedVector& operator=(const LoggedVector& rhs) = delete;
}
```
## Lecture 13: Move Semantics
### `emplace_back`
The vector will create the object you want for you, so there's no extra unecessary copies. 

### Copy Elision
Avoids unecessary copies. 
```c++
int main() {
    // with copy elision, the compiler will just create the vector over here in the readNames function, avoiding extra copies. 
    StrVector name1 = readNames(54321);
}

StrVector readNames(size_t size) {
    // without copy elision, the compiler will create a copy of the vector names locally, then create a copy of names to return
    StrVector names(size, "Ito");
    return names; 
}
```
### lvalues and rvalues
(Note: this is a overly simplification).

l-value: expression that has a name/identity. can find its address using & operator.

r-value: expression that does not have a name/identity. they are temporary values and you cannot find address using the & operator. 

### Reference 
Example: what can/can't you bind: 
```c++
int* ptr = 0x02248837;
auto& ptr2 = ptr; // l-value reference to ptr
auto&& v4 = v1+v2; // r-value reference
// can't bind l-value ref to r-value
// can't bind r-value ref to l-value
const auto& ptr3 = ptr + 5; // CAN bind const l-value ref to r-value
```

Example: as function parameters
```c++
void nocos_Lref(vector<int>& v);
void const_Lref(const vector<int> & v);

nocos_Lref(v2+v3); // ERROR
const_Lref(v2+v3); // OK
```

### Move Semantics
An object that is an r-value is disposable, so you can either copy or move them.
- Move constructor(create new from existing r-value). 
- Move assignment(overwrite existing from existing r-value). 

```c++
StringVector(StringVector&& other); // move constructor
StringVector& operator=(StringVector&& rhs); // move assignment
```

### `std::move`
`move` was introduced in C++ 11.
rhs itself is an l-value, even though it binds to an r-value. 
std::move will cast it to r-value, so instead of copying we are just transferring ownership. 
```c++
Axess& operator=(Axess&& rhs) {
    students = std::move(rhs.students);
}
```

### `std::move` Swap Example
```c++
template <typename T>
void swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}
```

## Lecture 14: Inheritance
### Passing Pointer by Copy vs. Reference
By copy: you pass a copy of the pointer value to the function. The function can modify the object the pointer points to, but it cannot modify the pointer to point somewhere else. 

By reference: you pass a reference to the pointer itself. This allows the function to modify both the object the pointer points to and the pointer itself.

### Namespaces
```c++
namespace Lecture {
    int count(const vector<int>& v) {
        // details skipped 
    }
}

int main() {
    vecotr<int> v{3,1,4,1,5,9};
    cout << "lecture count: " << Lecture::count(v) << endl;
}
```
Side note: local variables will take precedence over the using operations. 


### Interface
The simplest form of inheritance in c++. 

**Pure virtual function** is denoted by the = 0, means the inheriting class must define that function. 

There's no interface keyword in c++. To be an interface, a class must consist only of pure virtual functions. To implement an interface, a class must define all of those virtual functions. The only classes that can be defined/instantiated are the ones that don't contain any pure virtual functions. 

```c++
class Drink {
    public:
        virtual void make() = 0;
}; 

class Tea: public Drink {
    public:
        void make() {
            // implementation
        }
};
```

### Abstract Class
A class is an abstract class if a class has at least one pure virtual function. Abstract classes cannot be instantiated. 

Interfaces are subset of abstract class. 

### Constructor
Always calls the superclass constructor. 
If not specified, calls the default constructor of Base. 

```c++
class Derived : public Base {
    Derived() : Base(args), {

    }
}
```

### Destructor
If you intend to make your class inheritable, always make your destructor virtual! Otherwise will almost definitely have memory leaks. 
```c++
class Base {
    ~Base() {}
}; 

class Derived : public Base [
    ~Derived() {}
]

Base *b = new Derived();
delete b; // never calls the destructor for Derived!
```

### Inheritance Example
```c++
class Drink {
    public:
        Drink() = default;
        Drink(std::string flavor) : flavor(flavot) {}

        virtual void make() = 0;
        virtual ~Drink() = default;
    private:
        std::string flavor; 
};

class Tea: public Drink {
    public:
        Tea() = default;

        Tea(std::string flavor) : Drink(flavor) {}
        virtual ~Tea() = default;

        void make () {
            // implementations
        }
};
```

## Lecture 15: Template Class
### Template vs. Derived Class
Templates: static polymorphism, which means it does polymorphism at compile time. Use templates when runtime efficiency is important. 

Derived class: dynamic polymorphism, which means it figures out the type at runtime. Use derived class when compile-time efficiency is most important. 

### Casting
Below are not best practices in C++:
```c++
int a = (int)b;
int a = int(b);
```
This is best practice:
```c++
int a = static_cast<int>(b);
```

### Templates Class
Example: 
```c++
template <typename T>
class Box {
public:
    // Constructor
    Box(const T& item) : item_(item) {}

    // Method to get the item
    T getItem() const {
        return item_;
    }

    // Method to set a new item
    void setItem(const T& newItem) {
        item_ = newItem;
    }

private:
    T item_; // Holds the item of type T
};
```

### C++20 Concepts
- Concept is evaluated at compile-time.
- Can be used with class templates, function templates, and non-template functions (typically members of class templates). 

Example with built-in concepts: 
```c++
template<typename It, typename Type>
    requires Input_Iterator<It> && Iterator_of<It> && Equality_comparable<Value_type<It>, Type>
int countOccurences(It begin, It end, Type val);
```

## Lecture 16: RAII
### Resources Need to be Release
- Heap memory (new, delete)
- Files (open, close)
- Locks (try_lock, unlock)
- Sockets (socket, close)

### Issue with Guarantee Release of Resource
Let's say you allocate some heap memory, do some stuff, then call delete to release it. What if some exception was thrown after you allocate it but before you release it? There's memory leak! 

### Levels of Exception Safety
- Nothrow: absolutely does not throw exceptions (use cases: destructors, move constructors, etc.)
- Strong: rolled back to the state before function call. 
- Basic: program is in valid state after excetpion. 
- No: resource leaks, memory corruptiopn...

### Resoruce Acquisition Is Initialization (RAII)
All resources should be acquired in the constrcutor. 
All resources should be released in the destructor. 

Why? Because there should never be a "half-valid" state of the object. The destructor is always called, even with exceptions, so the resource is always freed. 

### `ifstream` is RAII Compliant
So you don't need to call open and close. It does it for you. 

### `lock_guard` 
`lock_guard` guarantees that the lock will be released when it goes out of scope. 
```c++
lock_guard<mutex>(databaseLock);
```

### Smart Pointers
- **std::unique_ptr**
- **std::shared_ptr**: resource can be stored by any number of shared_ptrs. Deleted when none of them point to it. 
- **std::weak_ptr**: similar to a shared_ptr, but doesn't contribute to the reference count. 

aside: std::auto_ptr is deprecated. 

Code Example:
```c++
std::unique_ptr<Node> n = std::make_unique<Node>();

std::shared_ptr<Node> n = std::make_shared<Node>();
```

## Lecture 17: Multithreading
When one thread is waiting for something, other threads can keep going, making programs faster. 

### Atomic
Makes sure, for example, an operation like a += b is atomic. Check out the \<atomic\> header in C++ documentation. 

### `std::lock_guard` vs. `std::unique_lock`
With `std::lock_guard` you can't manually lock and unlock it, and you cannot delay the lock, whereas with `std::unique_lock` you can. 

### Thread Example
```c++
std::mutex mtx;

void greet(int id) {
    std::lock_guard<std::mutex> lg(mtx);
    cout << "Hello there ! My name is " << id << endl;
}

int main() {
    cout << "Grettings from my threads..." << endl; 

    vector<std::thread> threads;
    for(size_t i = 0; i < kNumThreads; ++i) {
        threads.push_back(std::thread(greet, i));
        threads[i].join();
    }
    
    for(std::thread& t : threads) {
        t.join();
        // call join() so main thread doesn't finish before these threads finish
    }


    cout << "All greatings done!" << endl;

    return 0;
}
```

### Avoid Calling `new` and `delete` explicitly
Because they are the reasons for memory leak... 


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










