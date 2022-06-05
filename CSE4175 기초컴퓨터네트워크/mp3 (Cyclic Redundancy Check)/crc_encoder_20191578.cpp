#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>

using namespace std;

string modulo_2(string dividend, string divisor, int datawordsize, int generatorsize);
int binary_to_decimal(string binary);

int main(int argc, char *argv[]){
	if(argc != 5){
		fprintf(stderr, "usage: ./crc_encoder input_file output_file generator dataword_size\n");
		exit(1);
	}

	FILE *infp, *outfp;
	infp = fopen(argv[1], "r");
	if(infp == NULL){
		fprintf(stderr, "input file open error.\n");
		exit(1);
	}
	outfp = fopen(argv[2], "w");
	if(outfp == NULL){
		fprintf(stderr, "output file open error.\n");
		exit(1);
	}

	if(strcmp(argv[4], "4") && strcmp(argv[4], "8")){
		fprintf(stderr, "dataword size must be 4 or 8.\n");
		exit(1);
	}

	int datawordsize = strtol(argv[4], NULL, 10);
	int generatorsize = strlen(argv[3]);
	int ch;
	string codeword;
	int codewordsize=0, paddingnum=0;

	char *buffer;
	int size;
	int index=0;

	fseek(infp, 0, SEEK_END);
	size = ftell(infp);
	buffer = (char*)malloc(size+1);
	memset(buffer, 0, size+1);
	fseek(infp, 0, SEEK_SET);
	fread(buffer, size, 1, infp);

	do{
		//ch = fgetc(infp);
		ch = buffer[index++];
		//if(feof(infp)) break;
		bitset<8> bit(ch);
		string s = bit.to_string();

		string dataword1, dataword2;
		if(datawordsize == 4){
			dataword1 = s.substr(0,4);
			dataword2 = s.substr(4,4);
			codewordsize += (4+generatorsize-1)*2;
		}else{
			dataword1 = s;
			codewordsize += (8+generatorsize-1);
		}

		for(int i=0;i<generatorsize-1;i++){
			dataword1 += "0";
			dataword2 += "0";
		}

		string remainder = modulo_2(dataword1, argv[3], datawordsize, generatorsize);
		int j=0;
		for(int i=datawordsize;i<datawordsize+generatorsize-1;i++){
			dataword1[i] = remainder[j++];
		}
		if(datawordsize == 4){
			string remainder2 = modulo_2(dataword2, argv[3], datawordsize, generatorsize);
			j=0;
			for(int i=datawordsize;i<datawordsize+generatorsize-1;i++){
				dataword2[i] = remainder2[j++];
			}
		}


		codeword += dataword1;
		if(datawordsize == 4){
			codeword += dataword2;
		}

	}while(index < size);

	while(1){
		if (codewordsize % 8 == 0) break;
		codewordsize++;
		paddingnum++;
	}


	string finalcodeword;
	for(int i=0;i<paddingnum;i++){
		finalcodeword += "0";
	}
	finalcodeword += codeword;

	fprintf(outfp, "%c", paddingnum);
	for(int i=0;i<codewordsize;i+=8){
		string token = finalcodeword.substr(i, 8);
		int num = binary_to_decimal(token);
		fprintf(outfp, "%c", num);
	}
	

	fclose(infp);
	fclose(outfp);

	return 0;
}

string modulo_2(string dividend, string divisor, int datawordsize, int generatorsize){
	string remainder;

	for(int i=0;i<datawordsize;i++){
		if(dividend[i] == '1'){
			for(int j=0;j<generatorsize;j++){
				int xor_result;
				xor_result = dividend[i+j] xor divisor[j];
				if(xor_result == 1){
					dividend[i+j] = '1';
				}else{
					dividend[i+j] = '0';
				}
			}
			//cout << dividend << "\n";
		}
	}

	remainder = dividend.substr(datawordsize, generatorsize-1);
	return remainder;
}

int binary_to_decimal(string binary){
	int num=0;
	for(int i=0;i<8;i++){
		num = (num << 1) + binary[i] - '0';
	}
	return num;
}
