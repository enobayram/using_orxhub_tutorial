OrxPP orxConfig Utilities
=========================

This package contains utility classes to make it more convenient and safe to work with orxConfig using C++.

The package provides the following utilities:

**Persist:** A utility function to convert a given string to a persistent string. Persistent strings have unique IDs and they remain in memory until the process ends.

**ConfigSectionGuard:** A utility class to make the task of pushing and popping config sections easier and safer. It's used as:  
```cpp
{ // Some local scope

  ConfigSectionGuard guard("MySection"); // My section gets pushed

  ... // do stuff

} // End of scope, MySection gets popped by guard's destructor.
```

**ConfigListBuilder:** A utility class for accummulating config lists and then writing them. Used as:
```cpp
// You can also use ConfigSectionGuard
orxConfig_PushSection("SomeSection");

ConfigListBuilder builder;
builder << "Hello";
builder << "World";

builder.WriteToConfig("SomeList");
// [SomeSection]
// SomeList = Hello # World

orxConfig_PopSection();
```
