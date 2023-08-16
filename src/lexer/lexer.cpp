#include <iostream>
#include <regex>

enum TokenType
{
    PLUS,
    MINUS,
    MULTIPLY,
    INTEGER,
    FLOAT,
    STR,
    BOOL,
    EQUALITY,
    INEQUALITY,
    GREATER,
    LESS,
    AND,
    OR,
    NOT,
    IF,
    ELSEIF,
    ELSE,
    FOR,
    WHILE,
    LOOP,
    ENDLOOP,
    CONTINUE,
    BREAK,
    STRUCT,
    ENUM,
    FUNC,
    RETURNTYPE,
    RETURN,
    NONE,
    NEWLINE,
    DIVIDE,
    MODULO,
    LPAREN,
    SPACE,
    NUMBER,
    IDENTIFIER,
    RPAREN,
    HASHTAG,
    SEMICOLON,
    LESSEQUAL,
    GREATEREQUAL,
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
    STRING,
    INCREMENT,
    DECREMENT,
    ADDITIONASSIGNMENT,
    SUBTRACTIONASSIGNMENT,
    MULTIPLICATIONASSIGNMENT,
    DIVISIONASSIGNMENT,
    MODULUSASSIGNMENT,
    IMPORT,
    END_OF_FILE
};
struct Token
{
    TokenType type;
    std::string value;
};

const char* tokens[]{ "PLUS" , "MINUS", "MULTIPLY","INTEGER","FLOAT","STRING","BOOL","EQUALITY",
                      "INEQUALITY","GREATER","LESS","AND","OR","NOT","IF","ELSEIF","ELSE","FOR",
                      "WHILE","LOOP","ENDLOOP","CONTINUE","BREAK","STRUCT","ENUM","FUNCTION",
                      "RETURNTYPE","RETURN","NONE","NEWLINE", "DIVIDE","MODULO", "LPAREN", "SPACE", "NUMBER",
                      "IDENTIFIER", "RPAREN","HASHTAG","SEMICOLON","LESSEQUAL","GREATEREQUAL",
                      "EQUAL","COMMENT","SLASH","SINGLEQUOTE","DOUBLEQUOTE","COMMA","DOT",
                      "COLON","LCURLY","RCURLY","LSQUARE","RSQUARE","STRING","INCREMENT",
                      "DECREMENT","ADDITIONASSIGNMENT","SUBTRACTIONASSIGNMENT","MULTIPLICATIONASSIGNMENT",
                      "DIVISIONASSIGMENT","MODULUSASSIGNMENT","IMPORT", "END_OF_FILE" };
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
            if (getNextChar() == '+') { pos++; return { INCREMENT, "++" }; break; }
            else if (getNextChar() == '=') { pos++; return { ADDITIONASSIGNMENT, "+=" }; break; }
            return { PLUS, "+" };
            break;

        case '-':
            pos++;
            if (getNextChar() == '-') { pos++; return { DECREMENT, "--" }; break; }
            else if (getNextChar() == '=') { pos++; return { SUBTRACTIONASSIGNMENT, "-=" }; break; }
            return { MINUS, "-" };
            break;

        case '/':
            pos++;
            if (getNextChar() == '=') { pos++; return { DIVISIONASSIGNMENT, "/=" }; break; }
            return { DIVIDE, "/" };
            break;
        case '%':
            pos++;
            if (getNextChar() == '=') { pos++; return { MODULUSASSIGNMENT, "%=" }; break; }
            return { MODULO, "%" };
            break;

        case '*':
            pos++;
            if (getNextChar() == '=') { pos++; return { MULTIPLICATIONASSIGNMENT, "%=" }; break; }
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
            return { NEWLINE, "\\n" };
            break;
        case ';':
            pos++;
            return { SEMICOLON, ";" };
            break;
        case '<':
            pos++;
            if (getNextChar() == '=')
            {
                pos++;
                return { LESSEQUAL, "<=" };
                break;
            }

            return { LESS, "<" };
            break;
        case '>':
            pos++;
            if (getNextChar() == '=')
            {
                pos++;
                return { GREATEREQUAL, "<=" };
                break;
            }
            return { GREATER, ">" };
            break;
        case '=':
            pos++;
            if (getNextChar() == '=')
            {
                pos++;
                return { EQUALITY, "==" };
                break;
            }
            else if (getNextChar() == '!')
            {
                pos++;
                return { INEQUALITY, "=!" };
                break;
            }
            return { EQUAL, "=" };
            break;
        case '\'':
            pos++;
            return { SINGLEQUOTE, "'" };
            break;
        case '\"':
            pos++;
            return LiteralString();
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
    char getNextChar()
    {
        char nextChar = text[pos];
        return nextChar;
    }
    Token Identifier(const std::string& text)
    {
        if (text == "int") return { INTEGER, "INTEGER" };
        else if (text == "float") return { FLOAT, "FLOAT" };
        else if (text == "string") return { STR, "STR" };
        else if (text == "bool") return { BOOL, "BOOLEAN" };
        else if (text == "and") return { AND, "AND" };
        else if (text == "or") return { OR, "OR" };
        else if (text == "not") return { NOT, "NOT" };
        else if (text == "if") return { IF, "IF" };
        else if (text == "elseif") return { ELSEIF, "ELSEIF" };
        else if (text == "else") return { ELSE, "ELSE" };
        else if (text == "for") return { FOR, "FOR" };
        else if (text == "while") return { WHILE, "WHILE" };
        else if (text == "continue") return { CONTINUE, "CONTINUE" };
        else if (text == "break") return { BREAK, "BREAK" };
        else if (text == "struct") return { STRUCT, "STRUCT" };
        else if (text == "enum") return { ENUM, "ENUM" };
        else if (text == "fn") return { FUNC, "FUNCTION" };
        else if (text == "return") return { RETURN, "RETURN" };
        else if (text == "none") return { NONE, "NULL" };
        else if (text == "true") return { BOOL, "TRUE" };
        else if (text == "false") return { BOOL, "FALSE" };
        else if (text == "include") return { IMPORT, "INCLUDE" };
        else return { IDENTIFIER, text };
    }
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
        return Identifier(result);
    }
    Token LiteralString()
    {
        std::string result = "";
        while (pos <= text.length() && text[pos] != '\"')
        {
            result += text[pos];
            pos++;
        }
        pos++;
        if (result == "\"") return { DOUBLEQUOTE, "\"" };
        return { STRING, result };
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
    auto input = "fn merhaba(x,y):\n"
        "int test = 30\n"
        "return test+30\n"
        "string merhaba = \"test selam not or false merhaba and and and =>\"\n"
        "bool merhaba = true;\n"
        "for(int x = 0; x <= 30; x++)\n"
        "if(x == test): return true\n"
        "print(\"Sifirdan programlama dili gelistiriyoruz.\")\n"
        "x++;"
        "y+=30;"
        "c %= 2"
        "if(c % 2 == 0) return true;"
        "while (true): break;"
        "include discord";

    /*std::regex pattern("\\s+");
    std::string result = std::regex_replace(input, pattern, "");*/
    Lexer lexer(input);
    Token token = lexer.getNextToken();
    while (token.type != END_OF_FILE)
    {
        if (token.type != SPACE) std::cout << tokens[token.type] << " |" << token.value << "| " << std::endl;
        token = lexer.getNextToken();
    }
    std::cout << tokens[TokenType::END_OF_FILE];
    return 0;
}

