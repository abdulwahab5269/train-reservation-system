#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 

using namespace std;

// Function prototypes
void processFile(const string& inputFilename, const string& outputFilename);
bool isWordCharacter(char c);

int main() {
    string inputFile, outputFile;
    
    cout << "Enter input file name: ";
    getline(cin, inputFile);
    cout << "Enter output file name: ";
    getline(cin, outputFile);
    
    processFile(inputFile, outputFile);
    
    return 0;
}

void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);
    
    // Error checking for file opening
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file '" << inputFilename << "'\n";
        return;
    }
    
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create/open output file '" << outputFilename << "'\n";
        inputFile.close();
        return;
    }
    
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    bool inWord = false;
    char c;
    
    while (inputFile.get(c)) {
        charCount++;
        // Count lines
        if (c == '\n') {
            lineCount++;
        }
        
        // Check for word boundaries
        if (isWordCharacter(c)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }
    
    // Count the last line if file doesn't end with newline
    if (charCount > 0 && c != '\n') {
        lineCount++;
    }
    
    // Write results to output file
    outputFile << "File analysis results for: " << inputFilename << "\n";
    outputFile << "Lines: " << lineCount << "\n";
    outputFile << "Words: " << wordCount << "\n";
    outputFile << "Characters: " << charCount << "\n";
    
    // Close files
    inputFile.close();
    outputFile.close();
    
    cout << "File processing complete. Results written to " << outputFilename << "\n";
}

bool isWordCharacter(char c) {
    // Consider a character part of a word if it's not whitespace
    return !isspace(static_cast<unsigned char>(c));
}