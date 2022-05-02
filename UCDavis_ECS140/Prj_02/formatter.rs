use std::fs;
use std::io;
use crate::parser::*;

pub struct Formatter {
    parser: Parser,
    pub elements_vec: Vec<String>
}

impl Formatter {

    pub fn new(p: Parser) -> Formatter{
        Formatter {
            parser: p,
            elements_vec: Vec::new()
        }
    }

    #[allow(non_snake_case)]
    pub fn create_XHTML(&mut self, filename: String) -> io::Result<()> {
        
        // format the stream
        self.format();

        // create output file (name.x + html = name.xhtml)
        let file = filename + "html";
        std::fs::File::create(&file)?;

        // all html files use this header
        let header = 
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
        \n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\">
        \n<head><title> X Formatted file</title></head>
        \n<body bgcolor=\"navy\" text=\"yellow\" link=\"yellow\" vlink=\"yellow\">
        \n<font face=\"Courier New\">";

        let footer = "</font></body></html>";

        // string with all elements from element vector
        let mut elements = String::from("");
        for i in 0..self.elements_vec.len() {
            elements =  elements + &self.elements_vec[i].to_string();
        }

        let printstring = header.to_string() + &elements + footer;

        fs::write(&file, printstring)?;
        Ok(())
    }

    fn format(&mut self) {

        let mut numtabs = 0;
        let mut currentchar = 0;

        for i in 0..self.parser.scanner.token_vec.len() {

            // println!("Token {:?} at position {:?} with length {:?}", self.parser.scanner.token_vec[i].get_text(), self.parser.scanner.token_vec[i].get_char_pos(), self.parser.scanner.token_vec[i].get_text().len());
            if currentchar != 0 {
                if self.parser.scanner.token_vec[i].get_char_pos() - currentchar > 1 {
                    self.elements_vec.push("&nbsp;".to_string());
                    currentchar += 1;
                }
                currentchar = currentchar + self.parser.scanner.token_vec[i].get_text().len() as i32;
            }
            else {
                if self.parser.scanner.token_vec[i].get_text() == "}" {
                    numtabs -= 1;
                }
                for _j in 0..numtabs {
                    self.elements_vec.push("&nbsp;&nbsp;&nbsp;&nbsp;".to_string());
                }
                currentchar = self.parser.scanner.token_vec[i].get_text().len() as i32 - 1
            }

            


            if self.parser.scanner.token_vec[i].get_type().as_str() == "Function" {
                let element = "<font color=\"orange\">".to_string() + self.parser.scanner.token_vec[i].get_text() + "</font>";
                self.elements_vec.push(element);

            }
            else if self.parser.scanner.token_vec[i].get_type().as_str() == "Variable" {
                let element = "<font color=\"yellow\">".to_string() + self.parser.scanner.token_vec[i].get_text() + "</font>";
                self.elements_vec.push(element);
            }
            else if self.parser.scanner.token_vec[i].get_type().as_str() == "FloatConstant" {
                let element = "<font color=\"aqua\"><b>".to_string() + self.parser.scanner.token_vec[i].get_text() + "</b></font>";
                self.elements_vec.push(element);
            }
            else if self.parser.scanner.token_vec[i].get_type().as_str() == "IntConstant" {
                let element = "<font color=\"aqua\"><b>".to_string() + self.parser.scanner.token_vec[i].get_text() + "</b></font>";
                self.elements_vec.push(element);
            }
            else if self.parser.scanner.token_vec[i].get_type().as_str() == "Operator" {
                let element = "<font color=\"white\"><b>".to_string() + self.parser.scanner.token_vec[i].get_text() + "</b></font>";
                self.elements_vec.push(element);
            }
            else if self.parser.scanner.token_vec[i].get_type().as_str() == "Keyword" {
                let element = "<font color=\"white\"><b>".to_string() + self.parser.scanner.token_vec[i].get_text() + "</b></font>";
                self.elements_vec.push(element);
            }

            if self.parser.scanner.token_vec[i].get_text() == ";" || self.parser.scanner.token_vec[i].get_text() == "{" || self.parser.scanner.token_vec[i].get_text() == "}" {
                self.elements_vec.push("<br/>".to_string());
                currentchar = 0;
            }

            if self.parser.scanner.token_vec[i].get_text() == "{" {
                numtabs +=1;
            }
        

        }
   
    }
}