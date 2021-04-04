# Serum
Serum is a header-only dependency injection library for C++17.

## Getting Started
Serum is header-only, so add the contents of `Serum/include` to your include directories.
Add `#include "Serum/Serum.hpp"` to include Serum.

```cpp
#include <string>
#include "Serum/Serum.hpp"

int main() 
{
    auto container = SerumContainer();

    container.BindConstant<std::string>("Hello World");

    auto stringValue = container.Get<std::string>(); // stringValue = "Hello World"

    return 0;
}

```

## Acknowledgements
Serum uses [Catch2](https://github.com/catchorg/Catch2 "Catch2 repository.") for testing.