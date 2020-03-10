//lang::CwC

#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>


// returns the size of the given file
size_t getFileSize(FILE* fp) {
	assert(fp != NULL);
	// move the file file pointer to the end of the fil
	fseek(fp, 0, SEEK_END);
	// get the size of the file
	size_t fileSize = static_cast<size_t>(ftell(fp));

	// move the file pointer back
	rewind(fp);
	return fileSize;
}


// returns the begin index given the file and the start index
// given by the user
// rewinds the file
long getBeginIndex(FILE* fp, size_t from) {
	assert(fp != NULL);
	// index of the next read position
	long beginIndex = 0;
	// if the file is not being read from the beginning
	// move the begin file pointer to the character following
	// the next line break
	if (from > 0) {
		// get the character at the current file index
		int c = fgetc(fp);
		while (c != '\n') {
			// move file pointer one position to the right
			fseek(fp, 1L, SEEK_CUR);
			// increment begin index
			beginIndex++;
			// get next character
			c = fgetc(fp);
		}
		// increment begin index so it points to the character after line break
		beginIndex++;
	}
	// move the file pointer to the begining of the file
	rewind(fp);

	return beginIndex;
}


// double the size of the given c-string given the size of the buffer
void doubleBuffer(char* buffer, size_t size) {
	assert(buffer != nullptr);
	size_t newBuffer = size * 2;
	char* temp = new char[newBuffer];
	strcpy(temp, buffer);
	delete[] buffer;
	buffer = temp;
}


// optimizes the length of the buffer - removes any unused space
char* optimizeLength(char* buffer) {
	assert(buffer != nullptr);
	size_t length = strlen(buffer);
	char* temp = new char[length + 1]; // 1 extra for \0 character
	strcpy(temp, buffer);
	delete[] buffer;
	return temp;
}


// returns the endIndex to be read from the file given
// the begin index and the to index specified by the user
// rewinds the file
long getEndIndex(FILE* fp, long beginIndex, size_t to) {
	assert(fp != nullptr);
	assert(static_cast<size_t>(beginIndex) < to);
	// TODO create helper function
	// index of the ending position
	long endIndex = getFileSize(fp) - 1;
	// if the 'to' position is less than the position of the filesize - 1
	if (to < endIndex) {
		// move the file 0 positions from the end
		fseek(fp, 0, SEEK_END);
		// get the character at the end of the file
		int c = fgetc(fp);
		// loop through the file until the new line character is foud
		while (c != '\n') {
			// move the file pointer one position to the left
			fseek(fp, -1L, SEEK_CUR);
			// decrement end index
			endIndex--;
			// check if read past the beginIndex
			if (endIndex <= beginIndex) {
				fprintf(stderr, "Invalid read parameters: endIndex <= beginIndex.\n");
				exit(1);
			}
			// get the next character
			c = fgetc(fp);
		}
		// decrement the
	}
	// move the file pointer to the begining of the file
	rewind(fp);

	return endIndex;
}


// reads the file from index to index given the file pointer,
// begin index and end index. the indices are already at the positions
// that skip lines (if neccessary)
char* readFileHelper(FILE* fp, long beginIndex, long endIndex) {	
	assert(fp != NULL);
	// check if begin index is greater or equal than end idnex
	if (beginIndex >= endIndex) {
		fprintf(stderr, "Error: begin index must be less than end index.\n");
		exit(1);
	}
	// move the file pointer to beginIndex from the begining of the file
	fseek(fp, beginIndex, SEEK_SET);

	// create a buffer required for reading from the file
	size_t bufferSize = 1024;
	char* buffer = new char[bufferSize];

	// the result string
	// initial size is the buffer size
	char* result = new char[bufferSize];

	size_t totalMemoryRead = 0; // keepts track of total memory read
	size_t resultSize = bufferSize; // keeps track of the result size

	// read the file using buffer from beginIndex to endIndex
	while (beginIndex < endIndex) {
		// read from the file into the buffer
		fgets(buffer, bufferSize, fp);
		size_t memoryRead = strlen(buffer);
		// increment totalMemoryRead by the number of bytes read
		// includes line break (\n) in count
		totalMemoryRead += memoryRead;
		// check if need to double the size of the result memory
		// if equals, there is not enough room for \0 character
		if (totalMemoryRead >= resultSize) {
			doubleBuffer(result, resultSize);
			resultSize *= 2;
		}
		// increment the begin index by memory read
		beginIndex += memoryRead;
		// copy buffer into result
		strcat(result, buffer);
	}
	// optimize length of the result of necessary
	result = optimizeLength(result);

	return result;
}



// reads a file from the file name and returns a pointer to a c-string
// if the from and to are not the beginning and the end index
// truncates the file to the nearest line breaks
char* readFile(const char* filename, size_t from, size_t to) {
	assert(filename != nullptr);
	// check if from is greater or equal than to
	if (from >= to) {
		fprintf(stderr, "Error: begin index must be less than end index.\n");
		exit(1);
	}

	FILE* fp = fopen(filename, "r");

	if (fp == nullptr) {
		fprintf(stderr, "File: %s\nFailed to open the file.\n", filename);
		exit(1);
	}

	size_t filesize = getFileSize(fp);

	// check if to index is greater than the filesize
	// if true, set to the filesize
	if (to > filesize - 1) {
		to = filesize - 1;
	}

	long beginIndex = getBeginIndex(fp, from);
	long endIndex = getEndIndex(fp, beginIndex, to);

	char* str = readFileHelper(fp, beginIndex, endIndex);

	fclose(fp);
	return str;
}


// returns the number of rows in a string
size_t getNumRows(char* str) {
	assert(str != nullptr);
	size_t numRows = 0;
	size_t i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\n') {
			numRows++;
		}
		i++;
	}
	return numRows;
}

// TODO Megha
// returns the number of columns given the string of entries
// entries contains brackets < >
size_t getNumCols(char* str) {
	size_t numCols = 0;

	size_t length = strlen(str);

	// circle through every row
	size_t i = 0;

	// read every character until the end of the string
	while (str[i] != '\0') {
		size_t numElements = 0; // number of elements on the given row
		bool qFlag = false; 
		bool openFlag = false; // flag to hold the opening brace
		// read everything on the line
		while (str[i] != '\n' && str[i] != '\0') {
			if (str[i] == '<' && !openFlag && !qFlag) {
				openFlag = true;
			} else if (str[i] == '>' && openFlag && !qFlag) {
				openFlag = false;
				numElements++;
			} else if (str[i] == '"' && !qFlag && openFlag) {
				qFlag = true;
			} else if (str[i] == '"' && qFlag && openFlag) {
				qFlag = false;
			}
			i++;
		}
		// check if the number of elements on this row is the maxium numElements
		if (numElements > numCols) {
			numCols = numElements;
		}
		// reset number of elements on the row
		numElements = 0;
		i++;
	}
	return numCols;
}


// a helper function for getNext entry that returns a pointer to the next
// entry in the given string
char* nextEntryPtr(char* str, size_t* currentReadPosition) {
	assert(str != nullptr);
	size_t i = *currentReadPosition;
	while (str[i] != '\0') {
		// if encountered line break, reached end of the line
		if (str[i] == '\n') {
			
			//*(currentReadPosition) = *(currentReadPosition) + 1;
			return nullptr;
		}
		if (str[i] == '<') {
			return str + i;
		}
		// increment the position the file is being read from
		*(currentReadPosition) = *(currentReadPosition) + 1;
		i++;
	}
	// return nullptr at the end of file
	return nullptr;
}


// returns true if the given sequence of characters is a valid entry until
// the next space or the angle bracket
// assumes no escape sequences
// str is guaranteed to begin with the actual entry (not < or spaces after <)
// str is the first character after the '<' and any following spaces
// currentReadPtr is guaranteed to be at the end of the entry at '>' character
bool isValidEntry(char* str, size_t* endValidIndex, size_t* currentReadPtr) {
	assert(str != nullptr);
	assert(endValidIndex != nullptr);
	assert(currentReadPtr != nullptr);
	printf("str in valid: %s\n", str);
	bool result = true;
	bool readingCharacter = true;
	bool qFlag = false; // flag for determining the end of quotes if any
	size_t i = 0;
	// empty string
	if (str[0] == '>') {
		return false;
	}
	// loop until the end of the entry
	while(str[i] != '>' && !qFlag) {
		if (str[i] == '\0') {
			// end of file, malformed
			//*(currentReadPtr) += i;
			return false;
		}
		// read a character
		if (str[i] != ' ') {
			if (str[0] == '"' && !qFlag) {
				// character within quotes
				*(endValidIndex) = *(endValidIndex) + 1;
			} else if (!readingCharacter) {
				// finished reading a character and read a space and read another character, then malfored
				result = false;
			} else if (qFlag) {
				// character after closing quote
				result = false;
			} else {
				// else regular character
				printf("char: %c\tendIndex: %zu\n", str[i], *endValidIndex);
				*(endValidIndex) = *(endValidIndex) + 1;
			}
		} 
		// read a space
		else if (str[i] == ' ' && readingCharacter) { // case 3: characters with spaces
			*(endValidIndex) = *(endValidIndex) - 1; // last valid index is the previous character
			readingCharacter = false;
		} else if (str[i] == ' ' && str[0] == '"' && !qFlag) {
			// space within quotes
			*(endValidIndex) = *(endValidIndex) + 1;
		} else if (str[0] == '"' && str[i] == '"') {
			qFlag = true; // reached end of quotes
			*(endValidIndex) = i;
		}
		// increment loop counter after reading a character
		i++;
	}
	*(currentReadPtr) += i;
	/*
	printf("currentReadPTr: %zu\n", *currentReadPtr);
	printf("at index - 1: %c\n", str[*endValidIndex - 1]);
	printf("at index - 2: %c\n", str[*endValidIndex - 2]);
	*/
	if (str[*endValidIndex - 1] == '>') {
		*(endValidIndex) = *(endValidIndex) - 1;
	}
	
	printf("endValidIndex: %zu\n", *endValidIndex);
	return result;
}



// skips spaces given the string and the index
// increments index
void skipSpaces(char* str, size_t* i) {
	assert(str != nullptr);
	assert(i != nullptr);
	size_t count = 0;
	printf("i in skipspaces: %zu\n", *i);
	printf("str in space: %s\n", str);
	while(str[count] == ' ') {
		printf("space skipped\n");
		*(i) = *(i) + 1;
		count++;
	}
}



// returns a copy of the next entry
// removes angle brackets
// caller is responsible for freeing the memory
// parameter is a string containing all the entries 
// from the file including brackets
// if called consequtively, string has to be adjusteed
char* getNextEntry(char* str, size_t* currentReadPosition) {
	printf("current read pos: %zu\n", *currentReadPosition);
	// get the pointer to the beginning of the next set of characters
	char* nextEntry = nextEntryPtr(str, currentReadPosition); // increments currentRead position
	// if nextEntryPtr is nullptr, there are no more entries to read; end of row or EOF
	if (nextEntry == nullptr) {
		return nullptr;
	} else {
		printf("nextEntry: %s\n", nextEntry);
	}
	// holds the end index of a valid entry
	size_t beginValidIndex = 1; // holds
	size_t endValidIndex = 1;
	// skip any spaces following < 
	skipSpaces(nextEntry + 1, &beginValidIndex);
	// increment read position
	*(currentReadPosition) += beginValidIndex;
	endValidIndex = beginValidIndex;

	printf("beginValidIndex: %zu\n", beginValidIndex);
	printf("following curr index: %zu\n", *currentReadPosition);
	// check validity of the middle
	// endValidIndex is incremented here
	char* result;
	if (isValidEntry(nextEntry + beginValidIndex, &endValidIndex, currentReadPosition)) {
		// check if begin entry is a quote mark
		if (str[beginValidIndex] == '"') {
			beginValidIndex++;
			endValidIndex--;
		}
		// create a copy of the valid string and return
		size_t length = endValidIndex - beginValidIndex + 1;
		printf("length: %zu\n", length);
		result = new char[length + 1];
		char* endPos = nextEntry + beginValidIndex;
		strncpy(result, endPos, length);
		result[length] = '\0';
		printf("result after copy: %s\n", result);
		return result;
	} else {
		// empty string
		printf("invalid entry\n");
		result = new char[1];
		result[0] = '\0';
	}
	*(currentReadPosition) = *(currentReadPosition) + 1;
	return result;
}

// TODO Alex
// generates an array of strings representing a table with values
// populates the given array using values from string str
// remove brakets from entries
char*** generateArray(char* str) {
	assert(str != nullptr);
	// get the number of columns and rows
	// numCols is the maximum number of columns
	size_t numCols = getNumCols(str);
	size_t numRows = getNumRows(str);

	// create columns
	char*** cols = new char**[numCols];

	// allocate memory for each column
	for (size_t colIndex = 0; colIndex < numCols; colIndex++) {
		cols[colIndex] = new char*[numRows]; 
	}
	
	// value that stores the current read pointer in the str
	size_t currentStrPtr = 0;

	// go through array of characters and populate the array
	for (size_t rowIndex = 0; rowIndex < numRows; rowIndex++) {
		for (size_t colIndex = 0; colIndex < numCols; colIndex++) {
			
			// read the row and populate entries

			// method that reads in adjusted str, size_t currentStrIndex,
			// and returns a new substring
			// new entry is without brackets and preceeding/trailing spaces
			char* newEntry = getNextEntry(str, &currentStrPtr);
			printf("new entry: %s\n", newEntry);
		
			// if newEntry is null, there are no more entries in that row
			if (newEntry == nullptr) {
				// if no more new entries are in the row
				// empty c-string
				newEntry = new char[1];
				newEntry[0] = '\0';
			}
			// set the value of the new entry
			cols[colIndex][rowIndex] = newEntry;
		}
		// increment currentStrPtr to move onto the next row
		currentStrPtr++;
	}
	return cols;
}



// returns a pointer to the next row in the given string
// returns nullptr if no more rows found
char* nextRowPtr(char* str) {
	char* nextRow = str;
	size_t i = 0;
	while(nextRow[i] != '\n') {
		if (nextRow[i] == '\0') {
			return nullptr;
		}
		nextRow += 1;
	}
	return nextRow;
}

// returns the longest sequence of characters in the given c-string
size_t longestLine(char* str) {
	assert(str != nullptr);
	size_t max = 0;
	size_t currentMax = 0;
	size_t i = 0;
	while (str[i] != '\0') {
		// when reached new line and if current max counter is greater than max
		if (str[i] == '\n' && currentMax > max) {
			// reset max
			max = currentMax;
			currentMax = 0;
		} else {
			currentMax++;
		}
	}
	return max + 1; // 1 for new line character
}




// returns true if str is boolean and false otherwise
bool isBool(const char* str) {
	if (!strcmp(str, "0") || !strcmp(str, "1")) {
		return true;
	}
	return false;
}

// returns true if str is integer and false otherwise
bool isInteger(const char* str) {
	// finds and stores the length of the str 
	size_t length = strlen(str);

	// to check if the first item in the str is a + or - to represent the integer
	int plusOrMinus = static_cast<int>(str[0]);
	//compares against ASCII values
	if(plusOrMinus != 43 && plusOrMinus != 45) {
		// if doesn't have a sign, return false
		return false;
	}

	for(int i = 1; i< length; i++) {
		int intConverted = static_cast<int>(str[i]);
		if(!isdigit(intConverted)) { return false;}
	}	
	return true;
}

// returns true if str is float and false otherwise
bool isFloat(const char* str) {
	// finds and stores the length of the str 
	size_t length = strlen(str);
	//counter to check how many times the point occurs in float
	int periodCounter = 0;

	if(str[0] != 43 && str[0] != 45) {
		// doesn't have a sign
		return false;
	}
	for(int i = 1; i< length; i++) {
		//int intConverted = static_cast<int>(str[i]);
		//if more than one period occurs, it is not a valid float value
		if(periodCounter > 1) {
			return false;
		}
		//compares against ASCII value
		if(str[i] == 46) {
			periodCounter++;
			continue;
		}
		if(!isdigit(str[i])) {
			return false;
		}
	}
	// must have a period counter
	return periodCounter == 1;
}


// returns true if the str is empty ( <> )
bool isEmpty(const char* str) {
	return strlen(str) == 0;
}

// returns true if str is string and false otherwise
bool isString(const char* str) {
	return !isBool(str) && !isFloat(str) && !isInteger(str) && !isEmpty(str);
}


// filters the given column using the given predicate function
void filterColumn(char** column, size_t numRows, bool (*predicate)(const char*)) {
	assert(column != nullptr);
	assert(predicate != nullptr);
	for (size_t rowIndex = 0; rowIndex < numRows; rowIndex++) {
		// entry at the given row does not satisfy the condition of the predicate
		// replace the entry with an empty string
		if (!predicate(column[rowIndex])) {
			char* temp = column[rowIndex];
			delete[] temp;
			// empty string
			column[rowIndex] = new char[1];;
		}
	}
}


// TODO Alex
// filters the array to have the same datatype per column
// the type of the column is determined by the number of items occuring the most
void filterArray(char*** array, size_t numCols, size_t numRows) {
	printf("numCols: %zu\nnumRows: %zu\n", numCols, numRows);
	printf("filtering array\n");
	for (size_t colIndex = 0; colIndex < numCols; colIndex++) {
		size_t intCount = 0;
		size_t floatCount = 0;
		size_t stringCount = 0;
		size_t boolCount = 0;
		size_t highestCount = 0;
		for (size_t rowIndex = 0; rowIndex < numRows; rowIndex++) {
			if (isBool(array[colIndex][rowIndex])) {
				boolCount++;
				if (boolCount > highestCount) {
					highestCount = boolCount;
				}
			} else if (isFloat(array[colIndex][rowIndex])) {
				floatCount++;
				if (floatCount > highestCount) {
					highestCount = floatCount;
				}

			} else if (isInteger(array[colIndex][rowIndex])) {
				intCount++;
				if (intCount > highestCount) {
					highestCount = intCount;
				}
			} else if (isString(array[colIndex][rowIndex])) {
				stringCount++;
				if (stringCount > highestCount) {
					highestCount = stringCount;
				}
			}
			// else value is missing
		}
		// determine which count is the highest and filter this column
		// using corresponding predicate
		if (highestCount == intCount) {
			filterColumn(array[colIndex], numRows, &isInteger);
		} else if (highestCount == floatCount) {
			filterColumn(array[colIndex], numRows, &isFloat);
		} else if (highestCount == stringCount) {
			filterColumn(array[colIndex], numRows, &isString);
		} else if (highestCount == boolCount) {
			filterColumn(array[colIndex], numRows, &isBool);
		} 
		
	}
	printf("filtered\n");
}


// TODO Alex
// prints the type of the given column
void printColType(char*** array, size_t colIndex, size_t numRows) {
	assert(array != nullptr);
	size_t rowIndex = 0;
	while (rowIndex < numRows && isEmpty(array[colIndex][rowIndex])) {
		rowIndex++;
	}
	// happen if all entries are empty
	if (rowIndex == numRows) {
		rowIndex--;
	}
	char* entry = array[colIndex][rowIndex];
	if (isBool(entry)) {
		printf("BOOL\n");
	} else if (isInteger(entry)) {
		printf("INT\n");
	} else if (isFloat(entry)) {
		printf("FLOAT\n");
	} else if (isString(entry)) {
		printf("STRING\n");
	} else {
		// entire column of missing entries
		// pick bool in this case
		printf("BOOL\n");
	}
}

// TODO Alex
// prints the value of the entry at the given col and row index
void printColIndex(char*** array, size_t colIndex, size_t rowIndex) {
	assert(array != nullptr);
	printf("%s\n", array[colIndex][rowIndex]);	
}

// TODO Alex
// prints if the given entry is missing a value
void isMissingIndex(char*** array, size_t colIndex, size_t rowIndex) {
	assert(array != nullptr);
	printf("%d\n", isEmpty(array[colIndex][rowIndex]));	
}

