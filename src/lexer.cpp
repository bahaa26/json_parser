#include "lexer.h"   // Include the header file for the Lexer class
#include <cctype>    // For character classification functions
#include <stdexcept> // For error handling

// Constructor initializes the source string and sets position to 0
Lexer::Lexer(const std::string &source) : source(source), position(0) {}

char Lexer::peek() const
{
    if (is_at_end())
        return '\0'; // Return null character if we've reached the end
    return source[position];
}

char Lexer::advance()
{
    if (is_at_end())
        return '\0'; // Return null character if we've reached the end
    return source[position++];
}

bool Lexer::is_at_end() const
{
    return position >= source.length();
}

void Lexer::skip_whitespace()
{
    while (std::isspace(peek()))
    {
        advance();
    }
}

std::vector<Token> Lexer::tokenize()
{
    // initialize an empty vector to hold the tokens we will generate
    std::vector<Token> tokens;

    // keep reading characters until we reach the end of the input string
    while (!is_at_end())
    {
        skip_whitespace();
        if (is_at_end())
            break;

        char c = peek();

        // Handle simple single-character tokens
        switch (c)
        {
        case '{':
            tokens.push_back({TokenType::BraceOpen, std::string(1, advance())});
            break;
        case '}':
            tokens.push_back({TokenType::BraceClose, std::string(1, advance())});
            break;
        case '[':
            tokens.push_back({TokenType::BracketOpen, std::string(1, advance())});
            break;
        case ']':
            tokens.push_back({TokenType::BracketClose, std::string(1, advance())});
            break;
        case ',':
            tokens.push_back({TokenType::Comma, std::string(1, advance())});
            break;
        case ':':
            tokens.push_back({TokenType::Colon, std::string(1, advance())});
            break;
        default:
            // If not simple character, it must be String, Number, Boolean, or Null
            if (c == '"')
            {
                tokens.push_back(read_string());
            }
            else if (std::isdigit(c) || c == '-')
            {
                tokens.push_back(read_number());
            }
            else if (std::isalpha(c))
            {
                tokens.push_back(read_keyword());
            }
            else
            {
                throw std::runtime_error("Unexpected characater in JSON: " + std::string(1, c));
            }
            break;
        }
    }

    // When reach the end of file
    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}

Token Lexer::read_string()
{
    advance();
    std::string value = "";

    while (peek() != '"' && !is_at_end())
    {
        // Note: A production parser would handle escape characters (like \n or \") here.
        // We will keep it simple for now.
        value += advance();
    }

    if (is_at_end())
    {
        throw std::runtime_error("Unterminated string");
    }

    advance();
    return {TokenType::String, value};
}

Token Lexer::read_number()
{
    std::string value = "";

    // Read character that can be part of number (digits, -, ., +, e, E)
    while (!is_at_end() && (std::isdigit(peek()) || peek() == '.' || peek() == '-' || peek() == '+' || peek() == 'e' || peek() == 'E'))
    {
        value += advance();
    }

    return {TokenType::Number, value};
}

Token Lexer::read_keyword()
{
    std::string value = "";

    // Read standard alphabetical characters
    while (!is_at_end() && std::isalpha(peek()))
    {
        value += advance();
    }

    // Check against standard JSON keywords

    if (value == "true" || value == "false")
    {
        return {TokenType::Boolean, value};
    }
    else if (value == "null")
    {
        return {TokenType::Null, value};
    }

    throw std::runtime_error("Invalid keyword: " + value);
}