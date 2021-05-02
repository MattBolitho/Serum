# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## 🔖 [0.2.0] - Unreleased
### ✨ Added
- Resolution contexts.
- Type trait for checking if a type has a Serum constructor.
- More bindings:
    - To `std::shared_ptr`.
    - To raw pointer.
    - To self.

### 🛠 Improvements
- Tidies binding object hierarchy.

## 🔖 [0.1.0] - 2021-04-19
### ✨ Added
- Initial container with support for the following bindings:
    - A constant value.
    - A derived `SerumResolver` instance.
    - The type's default instance.
    - The return value of a function.