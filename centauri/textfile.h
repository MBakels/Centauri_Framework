#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <fstream>
#include <string>

class TextFile {
public:
	// Constructor of the TextFile
	TextFile();
	// Destructor of the TextFile
	virtual ~TextFile();
	// Open a text file, if no file exists it creats one
	bool Open(const char* filepath);
	// Write to a text file
	void Write(std::string text);
	// Sets a pointer to beginning of the text file
	void StartReading();
	// Read a line of text
	std::string ReadLine();
	// Closes the text file
	void Close();
	// Returns true if we reached the end of the file
	bool EndOfFile() { return endOfFile; };

private:
	std::fstream file; // filestream for reading the file
	bool endOfFile; // Has the end of the file been reached
};

#endif