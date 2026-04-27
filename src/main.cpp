#include <iostream>
#include "lexer.h"
#include "json_value.h"
#include "parser.h"

// A simple helper to print enum types as text
std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::BraceOpen:
        return "BraceOpen";
    case TokenType::BraceClose:
        return "BraceClose";
    case TokenType::BracketOpen:
        return "BracketOpen";
    case TokenType::BracketClose:
        return "BracketClose";
    case TokenType::Comma:
        return "Comma";
    case TokenType::Colon:
        return "Colon";
    case TokenType::EndOfFile:
        return "EOF";
    case TokenType::String:
        return "String";
    case TokenType::Number:
        return "Number";
    case TokenType::Boolean:
        return "Boolean";
    case TokenType::Null:
        return "Null";
    default:
        return "Other";
    }
}

int main()
{
    // A highly nested, raw JSON string
    std::string raw_json = R"({
        "developer": {
            "name": "Bahaa Mohamed",
            "title": "Full Stack & Flutter Dev",
            "stats": {
                "experience_years": 5,
                "is_freelancer": true
            },
            "tech_stack": [
                "C++",
                "Laravel",
                "Flutter",
                "Vue.js"
            ]
        }
    })";

    try
    {
        std::cout << "Parsing JSON string...\n\n";

        // One line of code to do all the lexing and parsing!
        JsonValue root = Parser::parse(raw_json);

        // Query our deeply nested C++ tree structure
        std::cout << "--- Parsed Data ---\n";
        std::cout << "Name: " << root["developer"]["name"].as_string() << "\n";
        std::cout << "Title: " << root["developer"]["title"].as_string() << "\n";
        std::cout << "Experience: " << root["developer"]["stats"]["experience_years"].as_number() << " years\n";
        std::cout << "Freelance: " << (root["developer"]["stats"]["is_freelancer"].as_bool() ? "Yes" : "No") << "\n";
        std::cout << "Core Skill 1: " << root["developer"]["tech_stack"][0].as_string() << "\n";
        std::cout << "Core Skill 2: " << root["developer"]["tech_stack"][1].as_string() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Parser Error: " << e.what() << '\n';
    }
    
    return 0;
}