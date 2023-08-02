#include <iostream>
class Token {
public:
    enum class Kind {
        Number,
        Identifier,
        LeftParen,
        RightParen,
        LeftSquare,
        RightSquare,
        LeftCurly,
        RightCurly,
        LessThan,
        GreaterThan,
        Equal,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Hash,
        Dot,
        Comma,
        Colon,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        Comment,
        Pipe,
        End,
        Unexpected,
    };
    Token(Kind kind) noexcept : m_kind{ kind } {}
private:
    Kind m_kind{};
};
const static char* PRINTABLE_TYPES[] = {
        "Number",
        "Identifier",
        "LeftParen",
        "RightParen",
        "LeftSquare",
        "RightSquare",
        "LeftCurly",
        "RightCurly",
        "LessThan",
        "GraterThan",
        "Equal",
        "Plus",
        "Minus",
        "Asterisk",
        "Slash",
        "Hash",
        "Dot",
        "Comma",
        "Colon",
        "Semicolon",
        "SingleQuote",
        "DoubleQuote",
        "Comment",
        "Pipe",
        "End",
        "Unexpected"
};

class Lexer
{
public:
    Token static atom(Token::Kind) noexcept;
    Token static number() noexcept;
    Token static identifier() noexcept;
};
Token Lexer::atom(Token::Kind kind) noexcept { int value = static_cast<int>(kind); std::cout << PRINTABLE_TYPES[value] << "\n"; return kind; }
Token Lexer::number() noexcept { return atom(Token::Kind::Number); }
Token Lexer::identifier() noexcept { return atom(Token::Kind::Identifier); }

Token next(char c)
{
    switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return Lexer::identifier();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return Lexer::number();
    case '(':
        return Lexer::atom(Token::Kind::LeftParen);
    case ')':
        return Lexer::atom(Token::Kind::RightParen);
    case '[':
        return Lexer::atom(Token::Kind::LeftSquare);
    case ']':
        return Lexer::atom(Token::Kind::RightSquare);
    case '{':
        return Lexer::atom(Token::Kind::LeftCurly);
    case '}':
        return Lexer::atom(Token::Kind::RightCurly);
    case '<':
        return Lexer::atom(Token::Kind::LessThan);
    case '>':
        return Lexer::atom(Token::Kind::GreaterThan);
    case '=':
        return Lexer::atom(Token::Kind::Equal);
    case '+':
        return Lexer::atom(Token::Kind::Plus);
    case '-':
        return Lexer::atom(Token::Kind::Minus);
    case '*':
        return Lexer::atom(Token::Kind::Asterisk);
    case '#':
        return Lexer::atom(Token::Kind::Hash);
    case '.':
        return Lexer::atom(Token::Kind::Dot);
    case ',':
        return Lexer::atom(Token::Kind::Comma);
    case ':':
        return Lexer::atom(Token::Kind::Colon);
    case ';':
        return Lexer::atom(Token::Kind::Semicolon);
    case '\'':
        return Lexer::atom(Token::Kind::SingleQuote);
    case '"':
        return Lexer::atom(Token::Kind::DoubleQuote);
    case '|':
        return Lexer::atom(Token::Kind::Pipe);
    }
}
int main()
{
    std::string code("213)||;:#");
    for (int i = 0; i < code.length(); i++)
    {
        next(code[i]);
    }
    return 0;
}
// TO DO 

// Rewrite and understand lexer