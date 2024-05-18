using System;

namespace HelloWorld
{
    public enum TokenType
    {
        Plus,
        Minus,
        Multiply,
        Integer,
        Float,
        String,
        Bool,
        Equality,
        Inequality,
        Greater,
        Less,
        And,
        Or,
        Not,
        If,
        Elif,
        Else,
        For,
        While,
        Loop,
        EndLoop,
        Continue,
        Break,
        Enum,
        Function,
        Return,
        ReturnType,
        None,
        NewLine,
        Divide,
        Modulo,
        LParen,
        RParen,
        Space,
        Number,
        Text,
        Identifier,
        Semicolon,
        LessEqual,
        GreaterEqual,
        Equal,
        Comment,
        Slash,
        SingleQuote,
        DoubleQuote,
        Comma,
        Dot,
        Colon,
        LCurly,
        RCurly,
        LSquare,
        RSquare,
        Increment,
        Decrement,
        AdditionAssignment,
        SubtractionAssignment,
        MultiplicationAssignment,
        DivisionAssignment,
        ModuloAssignment,
        Hashtag,
        Other,
        End_Of_File
    }

    public struct Token
    {
        public TokenType type;
        public string value;

        public Token(TokenType tokenType, string tokenValue)
        {
            type = tokenType;
            value = tokenValue;
        }
    }

    public class Lexer
    {
        private string text;
        private int pos;

        public Lexer(string lexText)
        {
            text = lexText;
            pos = 0;
        }

        public Token getNextToken()
        {
            if (pos >= text.Length)
            {
                return new Token(TokenType.End_Of_File, "END");
            }

            char currentChar = text[pos];
            if (Char.IsDigit(currentChar))
            {
                return isDigit();
            }


            if (Char.IsLetter(currentChar))
            {
                return isLetter();
            }

            switch (currentChar)
            {
                case '+':
                    pos++;
                    if (getNextChar() == '+')
                    {
                        pos++;
                        return new Token(TokenType.Increment, "++");
                        break;
                    }
                    else if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.AdditionAssignment, "+=");
                        break;
                    }

                    return new Token(TokenType.Plus, "+");
                    break;

                case '-':
                    pos++;
                    if (getNextChar() == '-')
                    {
                        pos++;
                        return new Token(TokenType.Decrement, "--");
                        break;
                    }
                    else if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.SubtractionAssignment, "-=");
                        break;
                    }

                    return new Token(TokenType.Minus, "-");
                    break;

                case '/':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.DivisionAssignment, "/=");
                        break;
                    }

                    return new Token(TokenType.Divide, "/");
                    break;
                case '%':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.ModuloAssignment, "%=");
                        break;
                    }

                    return new Token(TokenType.Modulo, "%");
                    break;
                    break;

                case '*':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.MultiplicationAssignment, "%=");
                        break;
                    }

                    return new Token(TokenType.Multiply, "*");
                    break;

                case '(':
                    pos++;
                    return new Token(TokenType.LParen, "(");
                    break;

                case ')':
                    pos++;
                    return new Token(TokenType.RParen, ")");
                    break;

                case ' ':
                    pos++;
                    return new Token(TokenType.Space, " ");
                    break;
                case '\n':
                    pos++;
                    return new Token(TokenType.NewLine, "\\n");
                    break;
                case ';':
                    pos++;
                    return new Token(TokenType.Semicolon, ";");
                    break;
                case '<':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.LessEqual, "<=");
                        break;
                    }

                    return new Token(TokenType.Less, "<");
                    break;
                case '>':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.GreaterEqual, "<=");
                        break;
                    }

                    return new Token(TokenType.Greater, ">");
                    break;
                case '=':
                    pos++;
                    if (getNextChar() == '=')
                    {
                        pos++;
                        return new Token(TokenType.Equality, "==");
                        break;
                    }
                    else if (getNextChar() == '!')
                    {
                        pos++;
                        return new Token(TokenType.Inequality, "=!");
                        break;
                    }

                    return new Token(TokenType.Equality, "=");
                    break;
                case '\'':
                    pos++;
                    return new Token(TokenType.SingleQuote, "'");
                    break;
                case '\"':
                    pos++;
                    return LiteralString();
                    break;
                case '.':
                    pos++;
                    return new Token(TokenType.Dot, ".");
                    break;
                case ',':
                    pos++;
                    return new Token(TokenType.Comma, ",");
                    break;
                case '{':
                    pos++;
                    return new Token(TokenType.LCurly, "{");
                    break;
                case '}':
                    pos++;
                    return new Token(TokenType.RCurly, "}");
                    break;
                case '[':
                    pos++;
                    return new Token(TokenType.LSquare, "[");
                    break;
                case ']':
                    pos++;
                    return new Token(TokenType.RSquare, "]");
                    break;
                case '#':
                    return isComment();
                    break;
                case ':':
                    pos++; 
                    return new Token(TokenType.Colon, ":");
                    break;
                default:
                    pos++; 
                    return new Token(TokenType.Other, currentChar.ToString());
                    break;
            }
        }

        public char getNextChar()
        {
            char nextChar = text[pos];
            return nextChar;
        }

        public Token Identifier(string text)
        {
            if (text == "int") return new Token(TokenType.Integer, "INTEGER");
            else if (text == "float") return new Token(TokenType.Float, "FLOAT");
            else if (text == "str") return new Token(TokenType.String, "STR");
            else if (text == "bool") return new Token(TokenType.Bool, "BOOLEAN");
            else if (text == "and") return new Token(TokenType.And, "AND");
            else if (text == "or") return new Token(TokenType.Or, "OR");
            else if (text == "not") return new Token(TokenType.Not, "NOT");
            else if (text == "if") return new Token(TokenType.If, "IF");
            else if (text == "elif") return new Token(TokenType.Elif, "ELSEIF");
            else if (text == "else") return new Token(TokenType.Else, "ELSE");
            else if (text == "for") return new Token(TokenType.For, "FOR");
            else if (text == "while") return new Token(TokenType.While, "WHILE");
            else if (text == "continue") return new Token(TokenType.Continue, "CONTINUE");
            else if (text == "break") return new Token(TokenType.Break, "BREAK");
            else if (text == "fn") return new Token(TokenType.Function, "FUNCTION");
            else if (text == "ret") return new Token(TokenType.Return, "RETURN");
            else if (text == "none") return new Token(TokenType.None, "NULL");
            else if (text == "true") return new Token(TokenType.Bool, "TRUE");
            else if (text == "false") return new Token(TokenType.Bool, "FALSE");
            else return new Token(TokenType.Identifier, text);
        }

        public Token isDigit()
        {
            string result = "";
            while (pos <= text.Length && Char.IsDigit(text[pos]))
            {
                result += text[pos];
                pos++;
            }

            return new Token(TokenType.Number, result);
        }

        public Token isLetter()
        {
            string result = "";
            while (pos <= text.Length && Char.IsLetter(text[pos]))
            {
                result += text[pos];
                pos++;
            }

            return Identifier(result);
        }

        public Token LiteralString()
        {
            string result = "";
            while (pos < text.Length && text[pos] != '\"')
            {
                result += text[pos];
                pos++;
            }

            pos++;
            if (result == "\"") return new Token(TokenType.DoubleQuote, "\"");
            return new Token(TokenType.String, result);
        }

        public Token isComment()
        {
            string result = "";
            while (pos <= text.Length && text[pos] == '#')
            {
                result += text[pos];
                pos++;
            }

            if (result == "##")
            {
                result = "";
                while (pos <= text.Length && text[pos] != '\n')
                {
                    result += text[pos];
                    pos++;
                }

                return new Token(TokenType.Comment, result);
            }

            ;
            return new Token(TokenType.Hashtag, result);
        }
    }

    class Program
    {
        public static string[] tokens = {
            "PLUS", "MINUS", "MULTIPLY", "INTEGER", "FLOAT", "STRING", "BOOL", "EQUALITY",
            "INEQUALITY", "GREATER", "LESS", "AND", "OR", "NOT", "IF", "ELIF", "ELSE", "FOR",
            "WHILE", "LOOP", "ENDLOOP", "CONTINUE", "BREAK", "ENUM",
            "FUNCTION", "RETURN", "RETURNTYPE", "NONE", "NEWLINE", "DIVIDE", "MODULO", "LPAREN", "RPAREN", "SPACE", "NUMBER",
            "TEXT", "IDENTIFIER", "SEMICOLON", "LESSEQUAL", "GREATEREQUAL",
            "EQUAL", "COMMENT", "SLASH", "SINGLEQUOTE", "DOUBLEQUOTE", "COMMA", "DOT","COLON",
            "LCURLY", "RCURLY", "LSQUARE", "RSQUARE", "INCREMENT",
            "DECREMENT", "ADDITIONASSIGNMENT", "SUBTRACTIONASSIGNMENT", "MULTIPLICATIONASSIGNMENT",
            "DIVISIONASSIGNMENT", "MODULOASSIGNMENT", "HASHTAG", "OTHER", "END_OF_FILE"
        };

        static void Main(string[] args)
        {
            string input =
                "fn merhaba(x,y){\nint test = 30;\nret test+30}\nstr merhaba = \"test selam not or false merhaba and and and =>\"\nbool merhaba = true;\nfor(int x = 0; x <= 30; x++){break;}\nif(x == test){ return true;}\nwrite(\"Sifirdan programlama dili gelistiriyoruz.\");\nx++;\ny+=30;\nc %= 2;\nif(c % 2 == 0){ return true;}\nwhile (true){ break;}";
            Lexer lexer = new Lexer(input);
            Token token;
            do
            {
                token = lexer.getNextToken();
                if (token.type != TokenType.Space)
                    Console.WriteLine($"{tokens[(int)token.type]} | {token.value} |");
            } while (token.type != TokenType.End_Of_File);
        }
    }
}