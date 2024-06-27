# FAQs

## Can I throw an exception from a constructor? From a destructor?
For constructors, yes: You should throw an exception from a constructor whenever you cannot properly initialize (construct) an object. There is no really satisfactory alternative to exiting a constructor by a throw. If a constructor throws an exception, the object’s destructor is not run. If your object has already done something that needs to be undone (such as allocating some memory, opening a file, or locking a semaphore), this “stuff that needs to be undone” must be remembered by a data member inside the object.

For destructors, not really: You can throw an exception in a destructor, but that exception must not leave the destructor; if a destructor exits by emitting an exception, all kinds of bad things are likely to happen because the basic rules of the standard library and the language itself will be violated. Don’t do it.


## How can I handle a destructor that fails?  
Write a message to a log-file. Terminate the process. Or call Aunt Tilda. But do not throw an exception!

Here’s why (buckle your seat-belts):

The C++ rule is that you must never throw an exception from a destructor that is being called during the “stack unwinding” process of another exception. For example, if someone says throw Foo(), the stack will be unwound so all the stack frames between the
```c++
    throw Foo()
```
and the
```c++
  }
  catch (Foo e)
  {
```
will get popped. This is called stack unwinding.

During stack unwinding, all the local objects in all those stack frames are destructed. If one of those destructors throws an exception (say it throws a Bar object), the C++ runtime system is in a no-win situation: should it ignore the Bar and end up in the
```c++
  }
  catch (Foo e)
  {
```
where it was originally headed? Should it ignore the Foo and look for a
```c++
  }
  catch (Bar e)
  {
```
handler? There is no good answer — either choice loses information.

So the C++ language guarantees that it will call terminate() at this point, and terminate() kills the process. Bang you’re dead.

The easy way to prevent this is never throw an exception from a destructor. But if you really want to be clever, you can say never throw an exception from a destructor while processing another exception. But in this second case, you’re in a difficult situation: the destructor itself needs code to handle both throwing an exception and doing “something else”, and the caller has no guarantees as to what might happen when the destructor detects an error (it might throw an exception, it might do “something else”). So the whole solution is harder to write. So the easy thing to do is always do “something else”. That is, never throw an exception from a destructor.

Of course the word never should be “in quotes” since there is always some situation somewhere where the rule won’t hold. But certainly at least 99% of the time this is a good rule of thumb.

## What should I throw?  
C++, unlike just about every other language with exceptions, is very accomodating when it comes to what you can throw. In fact, you can throw anything you like. That begs the question then, what should you throw?

Generally, it’s best to throw objects, not built-ins. If possible, you should throw instances of classes that derive (ultimately) from the std::exception class. By making your exception class inherit (ultimately) from the standard exception base-class, you are making life easier for your users (they have the option of catching most things via std::exception), plus you are probably providing them with more information (such as the fact that your particular exception might be a refinement of std::runtime_error or whatever).

The most common practice is to throw a temporary:
```c++
#include <stdexcept>
class MyException : public std::runtime_error {
public:
  MyException() : std::runtime_error("MyException") { }
};
void f()
{
   // ...
   throw MyException();
}
```
Here, a temporary of type MyException is created and thrown. Class MyException inherits from class std::runtime_error which (ultimately) inherits from class std::exception.

## What should I catch?  
In keeping with the C++ tradition of “there’s more than one way to do that” (translation: “give programmers options and tradeoffs so they can decide what’s best for them in their situation”), C++ allows you a variety of options for catching.

You can catch by value.
You can catch by reference.
You can catch by pointer.
In fact, you have all the flexibility that you have in declaring function parameters, and the rules for whether a particular exception matches (i.e., will be caught by) a particular catch clause are almost exactly the same as the rules for parameter compatibility when calling a function.

Given all this flexibility, how do you decide what to catch? Simple: unless there’s a good reason not to, catch by reference. Avoid catching by value, since that causes a copy to be made and the copy can have different behavior from what was thrown. Only under very special circumstances should you catch by pointer.

## How do I throw polymorphically?  
Sometimes people write code like:
```c++
class MyExceptionBase { };
class MyExceptionDerived : public MyExceptionBase { };
void f(MyExceptionBase& e)
{
  // ...
  throw e;
}
void g()
{
  MyExceptionDerived e;
  try {
    f(e);
  }
  catch (MyExceptionDerived& e) {
    // ...code to handle MyExceptionDerived...
  }
  catch (...) {
    // ...code to handle other exceptions...
  }
}
```
If you try this, you might be surprised at run-time when your catch (...) clause is entered, and not your catch (MyExceptionDerived&) clause. This happens because you didn’t throw polymorphically. In function f(), the statement throw e; throws an object with the same type as the static type of the expression e. In other words, it throws an instance of MyExceptionBase. The throw statement behaves as-if the thrown object is copied, as opposed to making a “virtual copy”.

Fortunately it’s relatively easy to correct:
```c++
class MyExceptionBase {
public:
  virtual void raise();
};
void MyExceptionBase::raise()
{ throw *this; }
class MyExceptionDerived : public MyExceptionBase {
public:
  virtual void raise();
};
void MyExceptionDerived::raise()
{ throw *this; }
void f(MyExceptionBase& e)
{
  // ...
  e.raise();
}
void g()
{
  MyExceptionDerived e;
  try {
    f(e);
  }
  catch (MyExceptionDerived& e) {
    // ...code to handle MyExceptionDerived...
  }
  catch (...) {
    // ...code to handle other exceptions...
  }
}
```
Note that the throw statement has been moved into a virtual function. The statement e.raise() will exhibit polymorphic behavior, since raise() is declared virtual and e was passed by reference. As before, the thrown object will be of the static type of the argument in the throw statement, but within MyExceptionDerived::raise(), that static type is MyExceptionDerived, not MyExceptionBase.

## Why doesn’t C++ provide a “finally” construct?  
Because C++ supports an alternative that is almost always better: The “resource acquisition is initialization” technique. The basic idea is to represent a resource by a local object, so that the local object’s destructor will release the resource. That way, the programmer cannot forget to release the resource.

