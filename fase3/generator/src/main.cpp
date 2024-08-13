#include "main.hpp"


// Function to convert the string to lower case
string toLowerCase(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


int main(int argc, char **argv) {
	if(argc >= 2){
	string geometricType = toLowerCase(argv[1]);
	//checks that the number of arguments is correct and that the content also corresponds to what is intended
	if((geometricType == "sphere") && argc == 6) 
		sphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4]), argv[5]); 
	else if((geometricType == "plane") && argc == 5) 
		plane(stof(argv[2]), stoi(argv[3]), argv[4]);
	else if((geometricType == "box") && argc == 5) 
		box(stof(argv[2]), stoi(argv[3]), argv[4]);
	else if((geometricType == "cone") && argc == 7)
		cone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]), argv[6]);
	else if((geometricType == "patch") && argc == 5)
		readPatchFile(argv[2], stoi(argv[3]), argv[4]);
	else cout << "erro" << endl;
	}


	return 0;

} 