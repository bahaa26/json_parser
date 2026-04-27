#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>

class JsonValue
{
public:
    // A JSON Object is a map of strings to other JsonValues
    using Object = std::map<std::string, JsonValue>;
    // A JSON Array is a list of other JsonValues
    using Array = std::vector<JsonValue>;

    // The Core of the tree: This value can be ANY of these types
    using VariantType = std::variant<std::nullptr_t, bool, double, std::string, Object, Array>;

    // 1. Constructors (Allows to easily create JsonValue from standard types)

    JsonValue() : value(nullptr) {} // Default to null
    JsonValue(std::nullptr_t) : value(nullptr) {}
    JsonValue(bool val) : value(val) {}
    JsonValue(double val) : value(val) {}
    JsonValue(const std::string &val) : value(val) {}
    JsonValue(const Array &val) : value(val) {}
    JsonValue(const Object &val) : value(val) {}

    // 2. Type checker
    bool is_null() const { return std::holds_alternative<std::nullptr_t>(value); }
    bool is_bool() const { return std::holds_alternative<bool>(value); }
    bool is_number() const { return std::holds_alternative<double>(value); }
    bool is_string() const { return std::holds_alternative<std::string>(value); }
    bool is_array() const { return std::holds_alternative<Array>(value); }
    bool is_object() const { return std::holds_alternative<Object>(value); }

    

    // 3. Type Extractors
    bool as_bool() const { return std::get<bool>(value); }
    double as_number() const { return std::get<double>(value); }
    const std::string &as_string() const { return std::get<std::string>(value); }
    const Array &as_array() const { return std::get<Array>(value); }
    const Object &as_object() const { return std::get<Object>(value); }

    // 4. Convenience Operators
    JsonValue &operator[](const std::string &key)
    {
        if (!is_object())
        {
            throw std::runtime_error("Not an object");
        }

        return std::get<Object>(value).at(key);
    }

    JsonValue &operator[](size_t index)
    {
        if (!is_array())
        {
            throw std::runtime_error("Not an array");
        }
        return std::get<Array>(value).at(index);
    }

private:
    VariantType value;
};