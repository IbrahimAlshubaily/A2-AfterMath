//Ibrahim Alshubaily
//I heavily depended on your answer, but I promise I copied nothing.
#include "arraysStrings.h"

//Part 1 - 2 points
//write a function joinrev that takes 2 strings and returns a 3rd string that is th first string followed by the 2nd string reversed
//Output should be:
//Hello dlroW
//Hint: joining the strings first and then reversing part of the joined string may be easier - ymmv
char *joinrev(char a[], char *b){
	int aLength = strlen(a);//Get a length
	int bLength = strlen(b);//Get b length
	char *c = malloc(aLength+bLength+1);//Allocate enough memory for both a,b and \o
	if(!c)return 0;//check if memory was allocated
	memcpy(c,a,aLength);//copy a into c
	memcpy(c+aLength,b, bLength+1);//copy b into c
	char tmp;//Temporally store right for the swap
	char *left = c+aLength;//points the char right before the second word.
	char *right =  c+aLength+bLength-1;//Points to the last char.
	while (left < right) {//loop until we reverse all chars in the second word.
		tmp=*right;
	    *right--=*left;
	    *left++=tmp;
	    // move pointers and swap chars.
	}
	return c;
}

//Part 2 - 2 points
//write a function joinrev_generic that takes pointers to any two arrays, a typesize, and the number of elements in each array and does the same
//thing as joinrev except that it will return a void pointer and will work on any type of array. HINT - copy the code from part 1 and change the code so that the pointer arithmetic is done explicitly and the copies are done using memcpy and memmove as in the class example reverse3
void * joinrev_generic(void * a, void * b, int elementSize, int aSize, int bSize) {
	char * c = malloc( (aSize+bSize)* elementSize);//Allocate enough memory for a and b
	if(!c) return 0;//check if memory was allocated
	memcpy(c, a, aSize*elementSize);//copy a into c
	memcpy(c+(aSize*elementSize),b, bSize*elementSize);//copy b into c
	char tmp [elementSize];//needed for the swap (temporarily holds right)
	char *right = c+((aSize+bSize-1)*elementSize);//points to the end of the second half and moves to the left
	char *left = c+(aSize*elementSize);//points to the middle and moves to the right
	while(left < right) {
		 memcpy(tmp,right,elementSize);//copy right into tmp
		 memmove(right,left,elementSize);//copy left into right
		 memcpy(left,tmp,elementSize);//copy right into left
		 right-=elementSize;//move the right pointer to the next element on its left
		 left+=elementSize;//move the left pointer to the next element on its right
	}
	return (void*) c;
}
//Part 3 - 2 points
//Write a function readTextAddBinary that takes two strings (filenames) and returns 0 if the function completes successfully. The function reads from the first filename,  a set of vectors, 2 per line and add them together and writes out a binary file (the second filename) with the new vectors (just the vectors - no spaces or other delimiters)
//A test file is given to you along with the expected output - you can use the Unix diff function to compare your output with the expected output in testFiles
int readTextAddBinary(char * input, char * output){
	FILE * ifp = fopen(input, "r");
	FILE * ofp = fopen(output, "wb");
	if (!ifp || !ofp){//check if the files are opened.
		printf("%s\n", "Couldn't open input or output file in method 3");
		return 1;
	}
	char line[1024];//allocate char array big enough to store the elements of two vectors
	while(fgets(line, sizeof(line), ifp)){//read one line
		float x1,x2,y1,y2,z1,z2;//variables to store the elements of two vectors
		int i = sscanf(line,"%f %f %f %f %f %f",&x1,&y1,&z1,&x2,&y2,&z2);//parse the line into floats
		if (i != 6){//make sure the line was read properly
			printf("%s\n", "Format error in method 3");//report the error
			return 1;
		}
		vector v = vector_init(x1+x2, y1+y2 ,z1+z2);//Initialize vector that is the result of adding the two vectors we read.
		fwrite(&v, sizeof(vector), 1, ofp);//write the vector to the output file
	}
	fclose(ifp);
	fclose(ofp);
	return 0;
}
//Part 4 - 2 points
//Write a function readBinaryNormText that takes two strings as input (filenames) and returns 0 if the function completes successfully. The first argument is a binary file of type produced in part 3. The function will read it in,  normalize a, and print out to the text file in argument 2, the components, x,y,z, and length separated by tabs (all as one big line) ;
int readBinaryNormText(char * input, char * output){
	FILE * ifp = fopen(input, "rb");
	FILE * ofp = fopen(output, "w");
	if (!ifp || !ofp){//check if file are opened.
			printf("%s\n", "Couldn't open input or output file in method 4");//report the error
			return 1;
	}
	vector v;
	while(fread(&v, sizeof(vector), 1, ifp)){//read the vectors from the input file one by one
		vector_normalize(&v);
		fprintf(ofp, "%f\t%f\t%f\t%f\t", v.x, v.y, v.z, v.length);//write the normalized vector to the output file
	}
	fclose(ifp);
	fclose(ofp);
	return 0;
}
//Part 5 - 2 points
//Write a function readNormTextWriteNormBinary that takes two strings as input (filenames) and returns 0 if the function completes successfully.. The first argument is the text file of type produced in part 4.  Read in the line using fgets or fread. Either use realloc or check for the size of the file using fseek, ftell to allocate enough space to store the line. Then use strtok to parse the file. Print the results out to a binary file in the same format as the binary file produced in part 3. Remember to free the memory.
int readNormTextWriteNormBinary(char * input, char * output) {
	FILE * ifp = fopen(input, "r");
	FILE * ofp = fopen(output, "wb");
	if (!ifp || !ofp){//check if file are opened.
		printf("%s\n", "Couldn't open input or output file in method 5");
		return 1;
	}

	fseek(ifp, 0, SEEK_END);//go to the end of the file.
	int size = ftell(ifp);//store the size of the file into size
	rewind(ifp);//go back to the beginning
	char *line = (char*) malloc(size+1);//allocate memory to store the line(file content)
	fread(line,size,1,ifp);//read the file into line
	line[size]='\0';//add end of string char at the end of the line
	char * delem = "\t\n";
	char *token = strtok(line, delem);//read chars until the the next tab or line break
	while (token){//loop until there is we parse all vetors
		vector v;
		v.x = atof(token);//parse the char representation of the x value into a float
		if(! (token = strtok(0,delem)) ) {//check if there is no more tokens
			free(line);
			return 1;
		}
		v.y = atof(token);//parse the char representation of the y value into a float
			if(! (token = strtok(0,delem)) ) {//check if there is no more tokens
				free(line);
				return 1;
			}
		v.z = atof(token);//parse the char representation of the z value into a float
			if(! (token = strtok(0,delem)) ) {//check if there is no more tokens
				free(line);
				return 1;
		}
		v.length = atof(token);//parse the char representation of the length value into a float

		if (!fwrite(&v, sizeof(vector), 1, ofp)){//writes the vector into the out put file and check if it worked
			free(line);
			return 1;
		}
		token=strtok(0,delem);//move to the next token
	}
	if(line) free(line);//free the line if it has not been freed yet
	fclose(ifp);
	fclose(ofp);
	return 0;
}
//Bonus - 1 bonus point
//Write a function wc that reads in the text file given and count the number of lines, number of words and number of characters. The output should be the same as given by the UNIX function wc i.e by typing the command "wc gettysburg.txt"
//Hint read in char by char and use the built in C isspace() function to determine if the character is whitespace
int wc(char * input) {
	FILE *ifp = fopen(input, "r");
	if (!ifp ){//check if input file is opened.
		printf("%s\n", "Couldn't open input or output file in method 5");
	}

	int inWord = 0;//Reports if we are at a char inside a word or not.
	int words = 0;//the number of words
	int lines = 0;//the number of lines
	int chars= 0;//the number of chars
	char c;//the runner char
	while(fread(&c, sizeof(char), 1, ifp)) {//loop to read the file char by char
		if (isspace(c)){//check if the current char is a space
			if(inWord){//check if the current char is inside a words
				words++;
				inWord=0;//change of the status of inWord to false because we already counted the current word;
			}
			if(c == '\n')lines++;//if the current char is a line break -> increase the number of lines
		}else{
			inWord = 1;//if the current char is not a space change inWord to true so next time we come across a space we increment the number of words
		}
		chars++;// every time we loop we increment the number of chars
	}
	fclose(ifp);
	if(inWord) words++;//edge case
	printf("\t%d\t%d\t %d %s\n", lines, words, chars, input);//print out the report in the same format as wc.
	return 0;
}
