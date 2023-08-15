#include <iostream>
#include <regex>

enum TokenType
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    LPAREN,
    SPACE,
    NUMBER,
    IDENTIFIER,
    RPAREN,
    HASHTAG,
    SEMICOLON,
    LESSTHAN,
    GREATERTHAN,
    EQUAL,
    COMMENT,
    SLASH,
    SINGLEQUOTE,
    DOUBLEQUOTE,
    COMMA,
    DOT,
    COLON,
    LCURLY,
    RCURLY,
    LSQUARE,
    RSQUARE,
    END_OF_FILE
};
struct Token
{
    TokenType type;
    std::string value;
};

const char* tokens[]{ "PLUS" , "MINUS", "MULTIPLY", "DIVIDE","MODULO", "LPAREN", "SPACE", "NUMBER",
                      "IDENTIFIER", "RPAREN","HASHTAG","SEMICOLON","LESSTHAN","GREATERTHAN",
                      "EQUAL","COMMENT","SLASH","SINGLEQUOTE","DOUBLEQUOTE","COMMA","DOT",
                      "COLON","LCURLY","RCURLY","LSQUARE","RSQUARE", "END_OF_FILE"};
class Lexer
{
public:
    Lexer(const std::string& text) : text(text), pos(0) {}
    Token getNextToken()
    {
        if (pos >= text.length())
        {
            return { END_OF_FILE, "" };
        }
        char currentChar = text[pos];
        if (isdigit(currentChar))
        {
            return isDigit();
        }


        if (isalpha(currentChar))
        {
            return isLetter();
        }
        switch (currentChar)
        {
        case '+':
            pos++;
            return { PLUS, "+" };
            break;

        case '-':
            pos++;
            return { MINUS, "-" };
            break;

        case '/':
            pos++;
            return { DIVIDE, "/" };
            break;
        case '%':
            pos++;
            return { MODULO, "%" };
            break;

        case '*':
            pos++;
            return { MULTIPLY, "*" };
            break;

        case '(':
            pos++;
            return { LPAREN, "(" };
            break;

        case ')':
            pos++;
            return { RPAREN, ")" };
            break;

        case ' ':
            pos++;
            return { SPACE, " " };
            break;
        case '\n':
            pos++;
            return { SPACE, "\\n" };
            break;
        case ';':
            pos++;
            return { SEMICOLON, ";" };
            break;
        case '<':
            pos++;
            return { LESSTHAN, "<" };
            break;
        case '>':
            pos++;
            return { GREATERTHAN, ">" };
            break;
        case '=':
            pos++;
            return { EQUAL, "=" };
            break;
        case '\'':
            pos++;
            return { SINGLEQUOTE, "'" };
            break;
        case '"':
            pos++;
            return { DOUBLEQUOTE, "\"" };
            break;
        case '.':
            pos++;
            return { DOT, "." };
            break;
        case ',':
            pos++;
            return { COMMA, "," };
            break;
        case '{':
            pos++;
            return { LCURLY, "{" };
            break;
        case '}':
            pos++;
            return { RCURLY, "}" };
            break;
        case ':':
            pos++;
            return { COLON, ":" };
            break;
        case '[':
            pos++;
            return { LSQUARE, "[" };
            break;
        case ']':
            pos++;
            return { RSQUARE, "]" };
        case '#':
            return isComment();
            break;
        }

    }
private:
    Token isDigit()
    {
        std::string result = "";
        while (pos <= text.length() && isdigit(text[pos]))
        {
            result += text[pos];
            pos++;
        }
        return { NUMBER, result };
    }
    Token isLetter()
    {
        std::string result = "";
        while (pos <= text.length() && isalpha(text[pos]))
        {
            result += text[pos];
            pos++;
        }
        return { IDENTIFIER, result };
    }
    Token isComment()
    {
        std::string result = "";
        while (pos <= text.length() && text[pos] == '#')
        {
            result += text[pos];
            pos++;
        }
        if (result == "##")
        {
            result = "";
            while (pos <= text.length() && text[pos] != '\n')
            {
                result += text[pos];
                pos++;
            }
            return { COMMENT, result };
        };
        return { HASHTAG, result };
    }
    std::string text = "";
    size_t pos;

};

int main()
{
    auto input =
        "def Fibonacci(n): ## Recursive Function created.\n"
        "if (n <= 1) : ## If n smaller than 1 returned 1\n"
        "return 1\n"
        "else: ## Else n* (n - 1)\n"
        "return (n * Fibonacci(n - 1))\n"
        "n = Fibonacci(int(input('Write number of fibonacci : ')))\n"
        "print(n)";


    /*std::regex pattern("\\s+");
    std::string result = std::regex_replace(input, pattern, "");*/
    Lexer lexer(input);
    Token token = lexer.getNextToken();
    while(token.type != END_OF_FILE) 
    {
        if(token.type != SPACE) std::cout << tokens[token.type] << " |" << token.value << "| " << std::endl;
        token = lexer.getNextToken();
    }
    
    return 0;
}

