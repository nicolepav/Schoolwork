// A struct SCANNER that will open the .x file as specified on the command line and 
// tokenize the text of the files into operators, intConstants, floatConstants, keywords, and identifiers

use crate::character_stream::*;
use crate::token::*;

pub struct Scanner {
    charstream: CharStream,
    pub token_vec: Vec<Token>,
    pub linecounter: i32,
    pub charcounter: i32
}

impl Scanner {
    pub fn new(c: CharStream) -> Scanner {
        Scanner {
            charstream: c,
            token_vec: Vec::new(),
            linecounter: 1,
            charcounter: 0
        }
    }

    // Gets and consumes next token, placing it in tokenVec
    // Returns none token if no tokens are available
    pub fn get_next_token(&mut self) -> Token{

        

        let mut charstart = self.charcounter;
        let mut negative = false;
        
        // check there are more chars
        if !self.charstream.more_available() {
            return Token::new("".to_string(), TokenType::NONE,0, 0);
        }

        
        let mut i = self.charstream.peek_next_char().unwrap();
        // println!("CHAR {:?} start {:?} counter {:?}", i, charstart, self.charcounter);

        // if i is a whitespace
        // account for spaces as tabs and replace as tabs essentially
        let mut spacesinarow = 0;
        if i == ' ' || i == '\t' || i == '\n'{

            while i == ' ' || i == '\t' || i == '\n' {
            
                if i == '\n' {
                    self.linecounter += 1;
                    self.charcounter = 0;
                }   
                else if i == ' ' {
                    spacesinarow += 1;
                    self.charcounter += 1;
                }

                if spacesinarow % 4 == 0 {
                    self.charcounter -= spacesinarow;
                    spacesinarow = 0;
                    if i == '\n' {
                        self.charcounter = 0;
                    }
                }

                charstart = self.charcounter;
                self.charstream.get_next_char(); // toss whitespace
                
                if self.charstream.more_available() {
                    i = self.charstream.peek_next_char().unwrap();
                }
                else {
                    return Token::new("".to_string(), TokenType::NONE,0, 0 );
                }

                
            }





        }


        // check operators 
        if i == '(' || i == ')' || i == '{' || i == '}' || i == ';' || i == ',' {
            // token is operator, add token to vector, return string              
            self.charstream.get_next_char();
            self.charcounter += 1;
            self.token_vec.push(Token::new(i.to_string(), TokenType::OPERATOR, self.linecounter, charstart));
            return Token::new(i.to_string(), TokenType::OPERATOR,self.linecounter, charstart);
        }
        // The special case for the - sign vs - operator
        else if i == '-' {
            if self.token_vec.len() == 0 {
                panic!("No previous tokens to compare to - sign, improper syntax suspected")
            }
            
            let prior = self.token_vec[self.token_vec.len()-1].get_type().as_str();

            // if prior token is intConst, floatConst, var, or func
            if prior != "Operator" {
                // minus is an operator
                // add token to vector, return string
                self.token_vec.push(Token::new(i.to_string(), TokenType::OPERATOR, self.linecounter, charstart));
                self.charstream.get_next_char();
                self.charcounter += 1;
                return Token::new(i.to_string(), TokenType::OPERATOR, self.linecounter, charstart)
            }
            else {
                // minus is a negative, flag and increment
                self.charstream.get_next_char();
                self.charcounter += 1;
                negative = true;
                i = self.charstream.peek_next_char().unwrap();
            }
        }


        let mut st = String::new();
        if negative {
            st.push('-');
        }


        // while i is not a no space op, space, or new line, or a minus, push chars to token string
        while self.charstream.more_available() && i != ' ' && i != '\t' && i != '(' && i != ')' && i != '{' && i != '}' && i != ';' && i != ',' && i != '-' && i != '\n' {
            st.push(self.charstream.get_next_char().unwrap());
            self.charcounter += 1;
            i = self.charstream.peek_next_char().unwrap();
            // println!("CHAR {:?} start {:?} counter {:?}", i, charstart, self.charcounter);

        }


        let ( s,  t,  linenum,  charpos);

        // Categorize the token collected
        // token is keyword
        if st == "unsigned" || st == "char" || st == "short" || st == "int" || st == "long" || st == "float" || st == "double" || st == "while" ||  st == "if" || st == "return" || st == "void" || st == "main" {
            
            s = st;
            t = TokenType::KEYWORD;
            linenum = self.linecounter;
            charpos = charstart;

            let tok = Token::new(s.to_string(), t, linenum, charpos);
            self.token_vec.push(tok);
            return Token::new(s.to_string(), TokenType::KEYWORD, linenum, charpos);
        }
        // token is operator
        else if st == "=" || st == "==" || st == "<" || st == ">" || st == "<=" || st == "=>" || st == "!=" || st == "+" || st == "*" || st == "/" {
            
            s = st;
            t = TokenType::OPERATOR;
            linenum = self.linecounter;
            charpos = charstart;

            let tok = Token::new(s.to_string(), t, linenum, charpos);
            self.token_vec.push(tok);
            return Token::new(s.to_string(), TokenType::OPERATOR, linenum, charpos);
        }
        // token is integer constant
        else if st.parse::<i64>().is_ok() {

            s = st;
            t = TokenType::INTCONSTANT;
            linenum = self.linecounter;
            charpos = charstart;

            let tok = Token::new(s.to_string(), t, linenum, charpos);
            self.token_vec.push(tok);
            return Token::new(s.to_string(), TokenType::INTCONSTANT, linenum, charpos);
        }
        // token is a float constant
        else if st.parse::<f64>().is_ok() {
            
            s = st;
            t = TokenType::FLOATCONSTANT;
            linenum = self.linecounter;
            charpos = charstart;

            let tok = Token::new(s.to_string(), t, linenum, charpos);
            self.token_vec.push(tok);
            return Token::new(s.to_string(), TokenType::FLOATCONSTANT, linenum, charpos);
        }
        // token is an identifier-Function
        else if i == '(' {
            let k = &st;
            self.token_vec.push(Token::new(k.to_string(), TokenType::FUNCTION, self.linecounter, charstart));
            return Token::new(k.to_string(), TokenType::FUNCTION, self.linecounter, charstart);
        }
        // token is an identifier-variable
        else {
            
            s = st;
            t = TokenType::VARIABLE;
            linenum = self.linecounter;
            charpos = charstart;

            let tok = Token::new(s.to_string(), t, linenum, charpos);
            self.token_vec.push(tok);
            return Token::new(s.to_string(), TokenType::VARIABLE, linenum, charpos);
        }
     
    }
}