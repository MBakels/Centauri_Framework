#include "textfile.h"

TextFile::TextFile() {
	endOfFile = false;
}

TextFile::~TextFile() {
	file.close();
}

bool TextFile::Open(const char * filepath) {
	// Close previous file
	file.close();
	// Open the file
	file.open(filepath, std::ios::out | std::ios::in);
	// If the file could not be opened return false
	if (!file.is_open()) return false;
	return true;
}

void TextFile::Write(std::string text) {
	// Write a line of text to the textfile
	file.write(text.c_str(), text.size());
	// Start a new line
	file.write("\n", 1);
}

void TextFile::StartReading() {
	// Set a pointer to the first line of the textfile
	file.seekg(0);
	endOfFile = false;
}

std::string TextFile::ReadLine() {
	// Read a line of text from the textfile and return it
	std::string datastream;
	if (!std::getline(file, datastream)) {
		endOfFile = true;
	}
	return datastream;
}

void TextFile::Close() {
	file.close();
}
