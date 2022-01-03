// a recursive descent parser struct that will parse the .x file by making repeated calls to the GetNextToken ()
// method of the scanner struct

// One method per EBNF rule

use crate::token::*;
use crate::scanner::*;


pub struct Parser {
    pub scanner: Scanner,
    current_token: Token,
    look_ahead: Token,
}

impl Parser {

    pub fn new(s: Scanner) -> Parser {
        Parser {
            scanner: s,
            current_token: Token::new("".to_string(), TokenType::NONE, 0, 0),
            look_ahead: Token::new("".to_string(), TokenType::NONE, 0, 0)
        }
    }

    pub fn as_token(tt: &str) -> TokenType {
        match tt {
            "None" => TokenType::NONE,
            "IntConstant" => TokenType::INTCONSTANT,
            "FloatConstant" => TokenType::FLOATCONSTANT,
            "Operator" => TokenType::OPERATOR,
            "Keyword" => TokenType::KEYWORD,
            "Variable" => TokenType::VARIABLE,
            "Function" => TokenType::FUNCTION,
            "Invalid" => TokenType::INVALID,
            &_ => TokenType::NONE
        } 
    }

    #[allow(non_snake_case)]
    pub fn updateToken(&mut self) {
        // println!("Updating Token ...  Token was {:?} ", self.current_token.get_text());
        let tt = self.look_ahead.get_type().as_str();

        self.current_token = Token::new(self.look_ahead.get_text().to_string(), Parser::as_token(tt), self.look_ahead.get_line_number(), self.look_ahead.get_char_pos());
        self.look_ahead = self.scanner.get_next_token();
    }

    // Program :=               {Declaration} MainDeclaration {FunctionDefintion}
    #[allow(non_snake_case)]
    pub fn Program(&mut self) -> bool {

        // at start of checking for program, initialize token parts of struct
        self.look_ahead = self.scanner.get_next_token();
        self.updateToken();

        if Parser::Declaration(self) {
            loop {
                if Parser::Declaration(self) { continue }
                break
            }
            if Parser::MainDeclaration(self) {
                loop {
                    if Parser::FunctionDefinition(self) { continue }
                    break
                }
                return true
            }
            panic!("Parser encountered a problem with Program rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());

        }
        
        if Parser::MainDeclaration(self) {
            loop {
                if Parser::FunctionDefinition(self) { continue }
                break
            }
        }
        else {
            return false
        }

        if Parser::FunctionDefinition(self) {
            loop {
                if Parser::FunctionDefinition(self) {  continue }
                break
            }
            println!(" 2{:?}", self.current_token.get_text());
            if self.current_token.get_text() != "" {
                panic!("Parser encountered a problem with Program rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            return true
        }
        else {
            if self.current_token.get_text() != "" {
                panic!("Parser encountered a problem with Program rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }

            return true
        }

 
    }

    // Declartion :=            DeclartionType (VariableDeclartion | FunctionDeclartion)
    #[allow(non_snake_case)]
    pub fn Declaration(&mut self) -> bool {
        if Parser::DeclarationType(self) {
            if Parser::VariableDeclaration(self) || Parser::FunctionDeclartion(self) {
                return true;
            }
            panic!("Parser encountered a problem with Declaration rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
       return false;
    }

    // MainDeclartion :=        void main () Block
    #[allow(non_snake_case)]
    pub fn MainDeclaration(&mut self) -> bool {

        if self.current_token.get_text() == "void" {
            self.updateToken();

            if self.current_token.get_text() == "main" {
                self.updateToken();

                if self.current_token.get_text() == "(" {
                    self.updateToken();

                    if self.current_token.get_text() == ")" {
                        self.updateToken();

                        if Parser::Block(self) {
                            return true;
                        }
                        panic!("Parser encountered a problem with MainDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                    }
                    panic!("Parser encountered a problem with MainDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
                panic!("Parser encountered a problem with MainDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with MainDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        panic!("Parser encountered a problem with MainDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());

    }

    // FunctionDefinition :=    DeclartionType ParameterBlock Block
    #[allow(non_snake_case)]
    pub fn FunctionDefinition(&mut self) -> bool {
        if Parser::DeclarationType(self) {
            if Parser::ParameterBlock(self) {
                if Parser::Block(self) {
                    return true
                }
                panic!("Parser encountered a problem with FunctionDeclaration rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with FunctionDeclaration rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false
    }

    // DeclartionType :=        DataType Identifier
    #[allow(non_snake_case)]
    pub fn DeclarationType(&mut self) -> bool {
        if Parser::DataType(self) {
            if Parser::Identifier(self) {
                return true;
            }
            panic!("Parser encountered a problem with DeclarationType rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false
    }

    // VariableDeclartion :=    [= Constant ] ;
    #[allow(non_snake_case)]
    pub fn VariableDeclaration(&mut self) -> bool {
        if self.current_token.get_text() == "=" {
            self.updateToken();

            if Parser::Constant(self) {
                if self.current_token.get_text() == ";" {
                    self.updateToken();
                    return true
                }
                panic!("Parser encountered a problem with VariableDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with VariableDeclaration at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        else if self.current_token.get_text() == ";" {
            self.updateToken();
            return true
        }
        else {
            return false
        }         
    }

    // FunctionDeclartion :=    ParameterBlock ;
    #[allow(non_snake_case)]
    pub fn FunctionDeclartion(&mut self) -> bool {
        if Parser::ParameterBlock(self) {
            if self.current_token.get_text() == ";" {
                self.updateToken();
                return true;
            }
            panic!("Parser encountered a problem with FunctionDeclaration rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false;
    }

    // Block :=                 { {Declaration} {Statement} {FunctionDefintion} }
    #[allow(non_snake_case)]
    pub fn Block(&mut self) -> bool {
        if self.current_token.get_text() == "{" {
            self.updateToken();

            loop {

                if Parser::Declaration(self) {
                    continue
                }
                else if Parser::Statement(self) {
                    continue
                }
                else if Parser::FunctionDefinition(self) {
                    continue
                }
                break
            }

            if self.current_token.get_text() == "}" {
                self.updateToken();
                return true
            }
            panic!("Parser encountered a problem with Block rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        else {
            return false;
        }
    }

    // ParameterBlock :=        ( [Parameter {, Parameter}] )
    #[allow(non_snake_case)]
    pub fn ParameterBlock(&mut self) -> bool {
        if self.current_token.get_text() == "(" && self.look_ahead.get_text() == ")" {
            self.updateToken();
            self.updateToken();
            return true;
        }
        else if self.current_token.get_text() == "(" {
            self.updateToken();

            if Parser::Parameter(self) {
                if self.current_token.get_text() == "," {
                    self.updateToken();

                    // start loop
                    loop {
                        if Parser::Parameter(self) {
                            if self.current_token.get_text() == "," {
                                self.updateToken();
                                continue
                            }
                            else if self.current_token.get_text() == ")" {
                                self.updateToken();
                                return true
                            }
                            panic!("Parser encountered a problem with ParameterBlock rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                        }
                    }
                    // end loop
                }
                else if self.current_token.get_text() == ")" {
                    self.updateToken();
                    return true
                }
                panic!("Parser encountered a problem with ParameterBlock rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with ParameterBlock rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        else {
            return false;
        }
    }

    // DataType :=              IntegerType | FloatType
    #[allow(non_snake_case)]
    pub fn DataType(&mut self) -> bool {
        return Parser::IntegerType(self) || Parser::FloatType(self);
    }

    // Constant :=              IntConstant | FloatConstant
    #[allow(non_snake_case)]
    pub fn Constant(&mut self) -> bool {
        return Parser::IntConstant(self) || Parser::FloatConstant(self);
    }

    // Statement :=             Assignment | WhileLoop | IfStatement | ReturnStatement | (Expression ;)
    #[allow(non_snake_case)]
    pub fn Statement(&mut self) -> bool {
        if Parser::Assignment(self) {
            return true
        }
        else if Parser::WhileLoop(self) {
            return true
        }
        else if Parser::IfStatement(self) {
            return true
        }
        else if Parser::ReturnStatement(self) {
            return true
        }
        else if Parser::Expression(self) {
            if self.current_token.get_text() == ";" {
                self.updateToken();
                return true                
            }
            panic!("Parser encountered a problem with Term rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false
    }

    // Parameter :=             DataType Identifier
    #[allow(non_snake_case)]
    pub fn Parameter(&mut self) -> bool {
        if Parser::DataType(self) {
            if Parser::Identifier(self) {
                return true;
            }
            panic!("Parser encountered a problem with Parameter rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        else {
            return false;
        }
    }   

    // IntegerType :=           [unsigned] (char | short | int | long )
    #[allow(non_snake_case)]
    pub fn IntegerType(&mut self) -> bool {
        
        let mut ctok = &self.current_token;
        if self.current_token.get_text() == "unsigned" {
            self.updateToken();
            ctok = &self.current_token;

            if ctok.get_text() == "char" || ctok.get_text() == "short" || ctok.get_text() == "int" || ctok.get_text() == "long"  {
                self.updateToken();
                return true;
            }
            panic!("Parser found an unsigned keyword not followed by char, short, int, or long at {:?}:{:?}", ctok.get_line_number(), ctok.get_char_pos());
        }  
        else if ctok.get_text() == "char" || ctok.get_text() == "short" || ctok.get_text() == "int" || ctok.get_text() == "long"  {
            self.updateToken();
            return true  
        }
        return false
    }

    // FloatType :=             float | double
    #[allow(non_snake_case)]
    pub fn FloatType(&mut self) -> bool {
        if  self.current_token.get_text() == "float" || self.current_token.get_text() == "double" {
            self.updateToken();
            return true
        }
        return false
    }

    // Assignment :=            Identifier = {Identifier =} Expression ;
    #[allow(non_snake_case)]
    pub fn Assignment(&mut self) -> bool {
        if self.look_ahead.get_text() == "=" {
            
            if Parser::Identifier(self) {
                if self.current_token.get_text() == "=" {
                    self.updateToken();

                    loop {
                        if self.look_ahead.get_text() == "=" {
                            if Parser::Identifier(self) {
                                if self.current_token.get_text() == "=" {
                                    self.updateToken();
                                    continue
                                }
                            }
                            panic!("Parser encountered a problem with Assignment rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                        }
                        break
                    }

                    if Parser::Expression(self) {
                        if self.current_token.get_text() == ";" {
                            self.updateToken();
                            return true
                        }
                        panic!("Parser encountered a problem with Assignment rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                    }
                    panic!("Parser encountered a problem with Assignment rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
                panic!("Parser encountered a problem with Assignment rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            return false
        }
        return false
        
    }

    // WhileLoop :=             while ( Expression ) Block
    #[allow(non_snake_case)]
    pub fn WhileLoop(&mut self) -> bool {
        if self.current_token.get_text() == "while" {
            self.updateToken();

            if self.current_token.get_text() == "(" {
                self.updateToken();

                if Parser::Expression(self) {
                    if self.current_token.get_text() == ")" {
                        self.updateToken();

                        if Parser::Block(self) {
                            return true
                        }
                        panic!("Parser encountered a problem with WhileLoop rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                    }
                    panic!("Parser encountered a problem with WhileLoop rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
                panic!("Parser encountered a problem with WhileLoop rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with WhileLoop rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false
    }

    // IfStatement :=           if ( Expression ) Block
    #[allow(non_snake_case)]
    pub fn IfStatement(&mut self) -> bool {
        if self.current_token.get_text() == "if" {
            self.updateToken();

            if self.current_token.get_text() == "(" {
                self.updateToken();

                if Parser::Expression(self) {
                    if self.current_token.get_text() == ")" {
                        self.updateToken();

                        if Parser::Block(self) {
                            return true
                        }
                        panic!("Parser encountered a problem with IfStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                    }
                    panic!("Parser encountered a problem with IfStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
                panic!("Parser encountered a problem with IfStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with IfStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }   
        return false
    }
    

    // ReturnStatement :=       return Expression ;
    #[allow(non_snake_case)]
    pub fn ReturnStatement(&mut self) -> bool {
        if self.current_token.get_text() == "return" {
            self.updateToken();

            if Parser::Expression(self) {
                if self.current_token.get_text() == ";" {
                    self.updateToken();
                    return true
                }
                panic!("Parser encountered a problem with ReturnStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            panic!("Parser encountered a problem with ReturnStatement rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
        return false

    }

    // Expression :=            SimpleExpression [ RelationOperator SimpleExpression ]
    #[allow(non_snake_case)]
    pub fn Expression(&mut self) -> bool {
        if Parser::SimpleExpression(self) {
            if Parser::RelationOperator(self) {
                if Parser::SimpleExpression(self) {
                    return true
                }
                // if relation succeeds but no following simple expr, error
                panic!("Parser encountered a problem with Expression rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
            // if simple succeeds and relationaloperator fails, thats acceptable
            return true
        }   
        return false
    }

    // SimpleExpression :=      Term { AddOperator Term }
    #[allow(non_snake_case)]
    pub fn SimpleExpression(&mut self) -> bool {
        if Parser::Term(self) {
            if Parser::AddOperator(self) {

                loop {
                    if Parser::Term(self) {
                        if Parser::AddOperator(self) {
                            continue
                        }
                        return true
                    }
                    panic!("Parser encountered a problem with Term rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
            }
            return true
        }
        return false
    }

    // Term :=                  Factor { MultOperator Factor }
    #[allow(non_snake_case)]
    pub fn Term(&mut self) -> bool { 
        if Parser::Factor(self) {
            if Parser::MultOperator(self) {

                loop {
                    if Parser::Factor(self) {
                        if Parser::MultOperator(self) {
                            continue
                        }
                        return true
                    }
                    panic!("Parser encountered a problem with Term rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                }
            }
            return true
        }
        return false
    }
    // Factor :=                ( (Expression) ) | Constant | (Identifier [ (Expression {, Expression } ) ] )
    #[allow(non_snake_case)]
    pub fn Factor(&mut self) -> bool {
        // Case: Expression or Ident
        if self.current_token.get_text() == "(" {
            self.updateToken();

            // Case Expression
            if Parser::Expression(self) {
                if self.current_token.get_text() == ")" {
                    self.updateToken();
                    return true
                }
                panic!("Parser encountered a problem with Factor rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
            }
           
            panic!("Parser encountered a problem with Factor rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
        }
         // Case Ident
         else if Parser::Identifier(self) {

            if self.current_token.get_text() == "(" {
                self.updateToken();

                // Case optional Expression
                if Parser::Expression(self) {
                    if self.current_token.get_text() == "," {
                        self.updateToken();

                        // start loop
                        loop {
                            if Parser::Expression(self) {
                                if self.current_token.get_text() == "," {
                                    self.updateToken();
                                    continue
                                }
                                else if self.current_token.get_text() == ")" {
                                    self.updateToken();
                                    return true
                                }
                                panic!("Parser encountered a problem with Factor rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                            }
                            panic!("Parser encountered a problem with Factor rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                        }
                        // end loop
                    }
                }
                else if self.current_token.get_text() == ")" {
                    self.updateToken();
                    return true
                }
                panic!("Parser encountered a problem with Factor rule at {:?}:{:?}", self.current_token.get_line_number(), self.current_token.get_char_pos());
                
            }
            return true    
        }
        // Case Constant
        else if Parser::Constant(self) {
            return true
        }
        return false 
      
    }

    // RelationOperator :=      == | < | > | <= | >= | != 
    #[allow(non_snake_case)]
    pub fn RelationOperator(&mut self) -> bool {
        let ctok = &self.current_token;
        if ctok.get_text() == "==" || ctok.get_text() == "<" ||  ctok.get_text() == ">" || ctok.get_text() == "<=" || ctok.get_text() == ">=" || ctok.get_text() == "!=" {
            self.updateToken();
            return true
        }
        return false
    }

    // AddOperator :=           + | -
    #[allow(non_snake_case)]
    pub fn AddOperator(&mut self) -> bool {
        if self.current_token.get_type().as_str() == "Operator" && (self.current_token.get_text() == "+" || self.current_token.get_text() == "-") {
            self.updateToken();
            return true;
        }
        return false;
    }

    // MultOperator :=          * | /
    #[allow(non_snake_case)]
    pub fn MultOperator(&mut self) -> bool {
        if self.current_token.get_type().as_str() == "Operator" && (self.current_token.get_text() == "*" || self.current_token.get_text() == "/") {
            self.updateToken();
            return true
        }
        return false
    }

    // identifier :=    ( _ | Alpha ) { ( _ | Digit | Alpha ) }
    #[allow(non_snake_case)]
    pub fn Identifier(&mut self)  -> bool {
        if self.current_token.get_type().as_str() == "Variable" || self.current_token.get_type().as_str() == "Function" {
            self.updateToken();
            return true
        }
        return false
    }

    // intConstant :=   [ - ] Digit {Digit}
    #[allow(non_snake_case)]
    pub fn IntConstant(&mut self) -> bool {
        if self.current_token.get_type().as_str() == "IntConstant" {
            self.updateToken();
            return true
        } 
        return false
    }

    // floatConstant := [ - ] Digit { Digit } [ . Digit {Digit} ]    
    #[allow(non_snake_case)]
    pub fn FloatConstant(&mut self) -> bool {
        if self.current_token.get_type().as_str() == "FloatConstant" {
            self.updateToken();
            return true
        }
        return false
    }

}