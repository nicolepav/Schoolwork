mod character_stream;
mod token;
mod scanner;
mod parser;
mod formatter;

use scanner::*;
use parser::*;
use character_stream::*;
use formatter::*;

use std::env;
use std::fs;

// Nicole Pavlovich
// ECS 140A Fall 2021 Prof Jiang


fn main() {

	// Collect argumemt from command line
	let args: Vec<String> = env::args().collect();
	if args.len() != 2 {
		panic!("Did not include the correct amount of files to run this program")
	}

	// Collect file from argument
	// Collect file contents into a string and create CharStream object
	let contents = fs::read_to_string(&args[1]).expect("Something went wrong reading the file");

	// Establish stream, scanner, and parser
	let fstream = CharStream::new(&contents);
	let fscanner = Scanner::new(fstream);	
	let mut fparser = Parser::new(fscanner);

	// Attempt parsing
	if fparser.Program() {
		println!("Program parsed successfully");
	}

	// Establish formatter
	let mut formatter = Formatter::new(fparser);

	// Create file, handle err if file fails
	formatter.create_XHTML(args[1].to_string()).unwrap_or_else(|err| println!("{:?}", err));
	println!("Program formatted successfully");

}

