// use std::fs::File;
// use std::io;
// use std::convert::TryFrom;
// use std::io::prelude::*;


pub struct CharStream {
	stream: String,
	pub streamsize: usize
}

impl CharStream {

	pub fn new(f: &str) -> CharStream {
		CharStream{
			stream: f.to_string(),
			streamsize: f.len()
		}
		
	}
	
	// Returns true if more characters are available, false otherwise.
	pub fn more_available(&self) -> bool {
		if self.stream.len() == 0 {
			false
		}
		else {
			true
		}
	}

	// Returns the next character without consuming it.
	// Returns None if no more characters are available. 
	pub fn peek_next_char(&self) -> Option<char> {
		
		if self.stream.len() != 0 {
			let ch = self.stream.chars().next().unwrap();
			return Some(ch as char)
		}
		else {
			return None
		}
		
	}

	// Returns the kth character ahead in the stream without consuming it.
	// peek_ahead_char(0) returns the same character as peek_next_char().
	// Returns None if no more characters are available at the position.
	// The input k cannot be negative.
	#[allow(dead_code)]
	pub fn peek_ahead_char(&self, k: i32) -> Option<char> {
		if self.stream.len() != 0 && k >= 0 {
			let ch = self.stream.chars().nth(k.try_into().unwrap()).unwrap();
			return Some(ch as char)
		}
		else if k < 0 {
			panic!("Inputted a negative k value for char position");
		}
		else {
			return None
		}
	}

	// Returns the next character and consumes it.
	// Returns None if no more characters are available.
	pub fn get_next_char(&mut self) -> Option<char> {
		if self.stream.len() != 0 {
			let ch = self.stream.chars().nth(0).unwrap();
			self.stream.remove(0);
			self.streamsize -= 1;
			return Some(ch as char)
		}
		else {
			return None
		}
	}
}

// Reference for testing charstream functions
/*
println!("{:?}", contents);

for i in 0..fstream.streamsize {
	if fstream.more_available() {
		println!("More are available");
		println!("Peeking: {:?}", fstream.peek_next_char());
		println!("Consuming char {:?}", fstream.get_next_char());
		println!("Streamsize is now {:?}", fstream.streamsize);
		
	}
	else {
		println!("No More avaialable")
	}
}
*/

