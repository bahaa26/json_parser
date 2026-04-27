#pragma once
#include "lexer.h"
#include "json_value.h"

class Parser
{
public:
    static JsonValue parse(const std::string &source);

private:
    Parser(const std::vector<Token> &tokens);

    // Recursive parsing methods
    JsonValue parse_value();
    JsonValue::Object parse_object();
    JsonValue::Array parse_array();

    // Helper methods to navigate the token list
    const Token &peek() const;
    Token advance();
    void consume(TokenType expected, const std::string &error_message);
    bool is_at_end() const;

    std::vector<Token> tokens;
    size_t position;
};