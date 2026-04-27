#include "parser.h"

JsonValue Parser::parse(const std::string &source)
{
    Lexer lexer(source);
    // transform the raw JSON string into a list of tokens that represent the structure and data of the JSON
    std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    return parser.parse_value();
}

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), position(0) {}

const Token &Parser::peek() const
{
    return tokens[position];
}

Token Parser::advance()
{
    if (!is_at_end())
        position++;
    return tokens[position - 1];
}

bool Parser::is_at_end() const
{
    return peek().type == TokenType::EndOfFile;
}

void Parser::consume(TokenType expected, const std::string &error_message)
{
    if (peek().type == expected)
    {
        advance();
        return;
    }
    throw std::runtime_error(error_message + " (Got: '" + peek().value + "')");
}

// Determines WHAT kind of data we are looking at and routes it to the right function
JsonValue Parser::parse_value()
{
    Token token = advance();

    switch (token.type)
    {
    case TokenType::String:
        return JsonValue(token.value);
    case TokenType::Number:
        return JsonValue(std::stod(token.value)); // Convert string to double
    case TokenType::Boolean:
        return JsonValue(token.value == "true");
    case TokenType::Null:
        return JsonValue(nullptr);
    case TokenType::BraceOpen:
    {
        position--; // Step back so parse_object can consume the '{'
        return JsonValue(parse_object());
    }
    case TokenType::BracketOpen:
    {
        position--; // Step back so parse_array can consume the '['
        return JsonValue(parse_array());
    }
    default:
        throw std::runtime_error("Unexpected token while parsing value: " + token.value);
    }
}

// Parses: { "key": value, "key2": value2 }
JsonValue::Object Parser::parse_object()
{
    JsonValue::Object object;
    consume(TokenType::BraceOpen, "Expected '{' at start of object");

    while (peek().type != TokenType::BraceClose && !is_at_end())
    {
        // 1. Get the Key
        Token key_token = advance();
        if (key_token.type != TokenType::String)
        {
            throw std::runtime_error("Object key must be a string");
        }

        // 2. Expect a Colon
        consume(TokenType::Colon, "Expected ':' after object key");

        // 3. Get the Value (This calls parse_value, which could be another object!)
        JsonValue value = parse_value();

        // 4. Store it in our C++ map
        object[key_token.value] = value;

        // 5. Handle commas
        if (peek().type == TokenType::Comma)
        {
            advance(); // Eat the comma and continue loop
        }
        else if (peek().type != TokenType::BraceClose)
        {
            throw std::runtime_error("Expected ',' or '}' after object value");
        }
    }

    consume(TokenType::BraceClose, "Expected '}' at end of object");
    return object;
}

// Parses: [ value, value2, value3 ]
JsonValue::Array Parser::parse_array() {
    JsonValue::Array array;
    consume(TokenType::BracketOpen, "Expected '[' at start of array");

    while (peek().type != TokenType::BracketClose && !is_at_end()) {
        // 1. Get the value and push it to our C++ vector
        array.push_back(parse_value());

        // 2. Handle commas
        if (peek().type == TokenType::Comma) {
            advance();
        } else if (peek().type != TokenType::BracketClose) {
            throw std::runtime_error("Expected ',' or ']' after array element");
        }
    }

    consume(TokenType::BracketClose, "Expected ']' at end of array");
    return array;
}