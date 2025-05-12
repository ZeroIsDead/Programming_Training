# Clean Code

Remove most dependencies - modules or packages from other files

## Meaningful Names

Each folder, file, variable, function, class, etc must have a name that is self-explanatory

There will be code, most of which will be bad code at first, however we can refine and make it better.

## Functions

A Function must only have one purpose/action
A Function can call other functions to help do its purpose
Error-Handling is a function in its own

### Function Name Rules

- Self-explanatory
- Query and Event Seperation
- Names of similar functions are written with the same predicate (to help the intellisence help)
  ex. getName() and getJob() or setEmployeeName() and setEmployeeJob()
-

### Function Length Rules

- Verticle Space
  - Max 5 Lines
- Horizontal Space
  - Max 200 Characters
  - Do not use any special fonts to make the code smaller so it can fit
    - If Necessary then write in the document

## Comments

The number of comments must be low
The comments must not explain the code, but the code must be self-explanatory

### (THE ONLY) Reasons to write Comments

- Intentions
- Warnings
- Documentations
  - Only in the beginning of the file (usually to only specify copyright)
-

## Code Format

### Verticle Spacing

- Code that are related to one another are placed close together
  ex. variable declarations, functions that call one another, ...
- Make Code Similar to an Newspaper
- Code can be seperated into Multiple Files
  - One File (max 250 lines)
  - Files that are closely related should be close together
  -

### Horizontal Spacing

- Code that are related to one another are placed close together
  ex. - space between the assignment operator to the variable and the value - no space between the function name and the brackets

variable = 0
Setvariable(variable)

---

-

### Code Formatting in IDE

## Objects and Data Structures

Objects and Data Structures are Opposites

Objects - Has public and meaningful functions but private variables

Data Structures - Has private and non-meaningful functions but public variables - accessors and mutators are still ok due to standards and frameworks such as beans

A structure must be an Object or a Data Structure but not a hybrid of both - contains public and meaningful functions and public variables

### Code with Objects - Object Oriented Code

    - Easy to make new classses without changing existing functions
    - Harder to make new functions because all classes must change

### Code with Data Structures - Procedural Code

    - Easy to add new functions without changing existing data structures
    - Harder to make new data structures because all the functions must change

### Law of Demeter

You should not be able to access the variables of an Object or even know the variables inside
ex. object.call().call() -> because we know its an object

Accessing the variable of a Data Structure is fine || Data Structures are not under the law of Demeter
ex. object.variable.variable

Instead of using getters in an object or knowing the variables inside and then using it to do something, you can create a method inside the object that will use its own variables to do it.

### Data Transfer objects (DTO)

The quintessential form of a data structure is a class with public variables and no functions also called a data transfer object.

DTOs are useful structures - communicate with databases - parsing messanges from sockets - first in a series of translation stages - convert raw data in a database into an object in application code

Beans - a data structure with private variables manipulated by getters and setters.

This quasi-encapulation of beans seem to make some OO purist feel better but usually provides no other benefit.

#### Active Record

Active Records are special forms of DTOs.

- Data structure with public or (bean-accessed) variables
- navigational methods
  - save
  - find
- direct translation from database tables or other data sources.

Most people treat this as an object by putting business rule methods in them
-> becomes a hybrid between a data structure and an object.

Treat active record as a data structure and to create seperate objects that contain the business rules and that hide their internal data.

### Conclusion

Object expose behavior and hide data 
- (easy) add new kinds of objects without changing existing behaviors. 
- (hard) add new behaviors to existing objects

Data structures expose data and have no significant behavior 
- (easy) add new behaviors to existing data structures 
- (hard) add new data structures to existing functions

Understand the two and choose the approach that is best for the job

- Prefer flexibility to add new data types
  -> Prefer Objects for that part of the system
- Prefer Flexibility to add new behaviors
  -> Prefer data types and procedures for that part of the system

## Error Handling

### Exceptions
Exceptions instead of returning Error Codes
  - Error Handling and the algorithm is separated
    - Clean & Simple -> Easier to understand and fix

Write tests that forces exceptions

Checked Exceptions - Errors where thr program can recover from the exceptions
  - In some languages such as Java
    - Throws must be used in every function that throw a checked exception
      - Including the caller function
      - This can be bad because every low level change can cause big changes
  - Only useful in a critical library where the exceptions are catched
  - In general, this dependency outweight the benefits

Unchecked Exceptions - Errors where the program must stop

### Contexts in Exceptions

Exceptions should be able to provide enough information regarding the error
  - location 
  - source
    - operation that failed
    - type of failure

Pass along the information to log in the catch