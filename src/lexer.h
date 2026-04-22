#pragma
#include <string>
#include <vector>

// 1. Define all possible JSON tokens
enum class TokenType
{
    BraceOpen,
    BraceClose,
    BracketOpen,
    BracketClose,
    Comma,
    Colon,
    String,
    Number,
    Boolean,
    Null,
    EndOfFile // Helps the parser know when to stop
};

// 2. Token structure to hold the type and value of each token
struct Token
{
    TokenType type;
    std::string value;
};

class Lexer
{
public:
    // Constructor that takes the raw JSON string
    Lexer(const std::string &source);

    // the main function to tokenize the input JSON string
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t position; // Keeps track of where we are in the string

    // Helper methods to navigate the string
    char peek() const;      // Look at the current character without moving
    char advance();         // Get current character and move forward
    bool is_at_end() const; // Are we done
    void skip_whitespace(); // Ignore spaces, tabs, newlines

    // Methods to handle specific, complex data types
    Token read_string();
    Token read_number();
    Token read_keyword(); // for boolean and null
};