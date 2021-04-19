# Serum
Serum is a header-only dependency injection library for C++17 that allows you to bind and resolve dependencies at runtime.

## Getting Started
### Prerequisites
Serum does not have any 3rd party dependencies.

It is regularly tested on Windows 10 and macOS Big Sur.
If there are any problems on specific platforms, please get in touch.

As the library is header only, nothing needs to be built.
The CMake project included in this repository builds the tests.

### Usage
Serum is header-only, so add the contents of `Serum/include` to your compiler's include directories.

To use Serum, instantiate a `SerumContainer` instance and register bindings to it.
Bindings can be resolved using the `Get` method.

```cpp
#include "Serum/Serum.hpp"

int main() 
{
    auto container = SerumContainer();

    auto config = { "example", 1 };
    auto serviceResolver = ServiceResolver("example", "instance");

    container.BindConstant<MyConfigType>(config)
             .BindResolver<MyService, MyServiceResolver>()
             .BindResolver<MyService, MyServiceResolver>(serviceResolver, "special-case")
             .BindToSelf<MyOtherService>();

    // Returns value of 'config'.
    auto resolvedConfig = container.Get<MyConfigType>();

    // Returns MyService instance from default constructed instance of MyServiceResolver.
    auto resolvedService = container.Get<MyService>(); 

    // Returns MyService instance from 'serviceResolver' if the request has name "special-case".
    auto specialResolvedService = container.Get<MyService>("special-case");

    // Returns the default instance of MyOtherService.
    auto otherService = container.Get<MyOtherService>();

    return 0;
}

```

## License
Distributed under the MIT License. See `LICENSE.md` for more information.

## Acknowledgements
Serum uses [Catch2](https://github.com/catchorg/Catch2 "Catch2 repository.") for testing.