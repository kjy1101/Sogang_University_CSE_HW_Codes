#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <math.h>

using namespace std;

string modulo_2(string dividend, string divisor, int size);
char change_to_char(string binary);

int main(int argc, char *argv[]){

	if(argc != 6){
		fprintf(stderr, "usage: ./crc_decoder input_file output_file result_file generator dataword_size\n");
		exit(1);
	}

	FILE *input_file, *output_file, *result_file;
	input_file = fopen(argv[1], "r");
	if(input_file == NULL){
		fprintf(stderr, "input file open error.\n");
		exit(1);
	}
	output_file = fopen(argv[2], "w");
	if(output_file == NULL){
		fprintf(stderr, "output file open error.\n");
		exit(1);
	}
	result_file = fopen(argv[3], "w");
	if(result_file == NULL){
		fprintf(stderr, "result file open error.\n");
		exit(1);
	}

	if(strcmp(argv[5], "4")&&strcmp(argv[5], "8")){
		fprintf(stderr, "dataword size must be 4 or 8.\n");
		exit(1);
	}

	int dataword_size = strtol(argv[5], NULL, 10);
	int paddingsize;
	string divisor(argv[4]);

		
	int readbyte = 8; /* 인코딩 전에 문자 1개가 codeword 몇개로 나눠졌는지? */
	if(dataword_size == 4) readbyte += (divisor.length()-1)*2;
	else readbyte += (divisor.length()-1);

	int codewordsize = dataword_size + divisor.length()-1; /* codeword 1개의 길이 */
	readbyte /= codewordsize;

	char *buffer;
	int size;
	char *wbuffer;
	int wsize=0;

	fseek(input_file, 0, SEEK_END);
	size = ftell(input_file);
	buffer = (char*)malloc(size+1);
	memset(buffer, 0, size+1);
	fseek(input_file, 0, SEEK_SET);
	fread(buffer, size, 1, input_file);

	//printf("size: %d\n", size);

	paddingsize = buffer[0];
	//printf("paddingsize: %d\n", paddingsize);
	//printf("readbyte: %d\n", readbyte);

	wbuffer = (char*)malloc(size+1);

	string codewordbit;
	for(int i=1;i<size;i++){
		bitset<8> bit(buffer[i]);
		string s = bit.to_string();
		codewordbit += s;
	}
	/* padding 제거 */
	string codewords = codewordbit.substr(paddingsize, size*8);

	int error=0, total=0;
	for(int i=0;i<size*8-paddingsize-8;i+=(codewordsize*readbyte)){
		string result;
		for(int j=0;j<readbyte;j++){
			string codeword = codewords.substr(i+j*codewordsize, codewordsize);
			string modulo_result;
			modulo_result = modulo_2(codeword, divisor, dataword_size);
			if(modulo_result.find("1") == string::npos){
				// all 0, no error 
			}else{
				error++;
			}
			total++;
			result += codeword.substr(0, dataword_size);
		}
		char ch_output = change_to_char(result);
		//if(ch_output != 0) {
			wbuffer[wsize++] = ch_output;
			//fprintf(output_file, "%c", ch_output);
		//}else{
		//	wsize++;
		//}
	}
	wbuffer[wsize] = '\0';
	//printf("wsize: %d\n", wsize);
	//printf("sizeof(wbuffer): %d\n", sizeof(wbuffer));
	//printf("wbuffer: %s\n", wbuffer);
	//printf("wbuffer+8: %s\n", wbuffer+8);

	//fprintf(output_file, "%s", wbuffer);
	for(int l=0;l<wsize;l++){
		fprintf(output_file, "%c", wbuffer[l]);
	}
	fprintf(result_file, "%d %d", total, error);

	fclose(input_file);
	fclose(output_file);
	fclose(result_file);
	return 0;
}

string modulo_2(string dividend, string divisor, int size){
	string remainder;
	string temp(dividend);
	for(int i=0;i<size;i++){
		if(temp[i]=='1'){
			for(unsigned int j=0;j<divisor.length();j++){
				int xor_result;
				xor_result = temp.at(i+j) xor divisor.at(j);
				if(xor_result == 0) temp.at(i+j) = '0';
				else temp.at(i+j) = '1';
			}
		}
	}
	remainder = temp.substr(size, divisor.length());
	return remainder;
}

char change_to_char(string binary){
	char ch;
	int binary_int = 0;

	for(unsigned int i=0;i<binary.length();i++){
		if(binary[i] == '1')
			binary_int += pow(2, binary.length()-1-i);
	}
	ch = binary_int;
	return ch;
}
