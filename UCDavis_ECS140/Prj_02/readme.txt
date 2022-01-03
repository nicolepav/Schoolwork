Project 02
ECS 140A Fall 2021
UC Davis Prof Jiang
Nicole Pavlovich

- Written in Rust
- Project includes scanner (lexical analyzer), parser, and formatter for the provided set of EBNF rules. 

- Program can be run using cargo run filename.x
- Program reads .x files, if parsing is successful it creates an .xhtml file in the same directory with the same name,
color coded as noted in format.csv
- Attempting to pass more than one file in the command line or no files will cause the program to panic
- Failure to adhere to the the EBNF rules will cause the parser to terminate the program.


