coding is more science than math
    - math - use itself to prove an equation to be true
    - science - if it is not false for almost every possibility -> true

SOLID principle - basic rules
 - SRP - Single Responsibility - everything is responsible to one actor (function/interface/etc)
 - OCP - Open Closed - Open to Expand; Closed to Modification
 - LSP - Liskov Seperation - Separate Codes into Modules
 - ISP - Interface Segregation - Two modules should communicate through an interface (own entity which only has function(s) that are specialized for communication) instead of a function inside the module - therefore if the modules that communicate change, you can easily change the interface.
        ex. Class C depends on Interface I that depends on Database D; if interface has a useless function or database has an unrelated function then it could cause problems such as redeployment
 - DIP - Dependency Inverse - Similar to ISP, instead of using a function from  a module, create a class that has the functions that you use and in the correct way - create an inheritence or subtype of the class in the module

Component Principle
