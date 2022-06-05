#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>

#define MAXDATASIZE 1000

int main(int argc, char *argv[]){
	/* ARGUMENT PARSING */
	/* 인자가 없거나 2개 이상인 경우 */
	if(argc != 2){
		fprintf(stderr, "usage: http_client http://hostname[:port][/path/to/file]\n");
		exit(1);
	}

	/* 인자에 http://가 올바르게 안붙은 경우 */
	if((strstr(argv[1], "http://") == NULL)||(strstr(argv[1], "http://")!=argv[1])){
		fprintf(stderr, "usage: http_client http://hostname[:port][/path/to/file]\n");
		exit(1);
	}

	char hostname[100]="\0";
	char port_num[10]="\0";
	char path_to_file[100]="\0";
	char *ptr = strtok(argv[1], "/");

	if(ptr != NULL){
		ptr = strtok(NULL, "/"); //hostname[:port]
		if(ptr != NULL){
			strcpy(hostname, ptr);
			ptr = strtok(NULL, ""); //path to file
			if(ptr != NULL){
				path_to_file[0] = '/';
				strcat(path_to_file, ptr);
			}
			else{
				path_to_file[0] = '/'; //default path
			}
		}
	}

	ptr = strtok(hostname, ":"); //hostname
	if(ptr != NULL){
		ptr = strtok(NULL, ""); //portnum
		if(ptr != NULL){
			strcpy(port_num, ptr);
		}
		else{
			strcpy(port_num, "80"); //default port num
		}
	}

	/*if(hostname != NULL) printf("hostname: %s\n", hostname);
	if(port_num != NULL) printf("port num: %s\n", port_num);
	if(path_to_file != NULL) printf("path to file: %s\n", path_to_file);*/


	int sockfd, numbytes;
	int accumulate_numbytes = 0;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo;
	int rv;
	char s[INET_ADDRSTRLEN];


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	/* hostname이 domain name인 경우 해당 domain name에 대한 IP address를 찾는다. */
	if((rv = getaddrinfo(hostname, port_num, &hints, &servinfo)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	/* servinfo 구조체를 이용하여 socket을 만든다. */
	if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))==-1){
		perror("client: socket");
		return 2;
	}

	/* 서버로 연결한다. */
	if(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
		close(sockfd);
		perror("connect");
		exit(1);
	}

	/* 서버로 연결을 성공하면 서버의 정보를 담고 있는 구조체를 free시킨다. */
	freeaddrinfo(servinfo);

	/* socket이 연결된 후에 메세지를 주고받기 위한 함수는 send와 recv */
	/* HTTP request message를 보낸다.(client -> server) */
	strcpy(buf, "GET ");
	strcat(buf, path_to_file);
	strcat(buf, " HTTP/1.1\r\nHost: ");
	strcat(buf, hostname);
	strcat(buf, ":");
	strcat(buf, port_num);
	strcat(buf, "\r\n\r\n");
	if(send(sockfd, buf, strlen(buf), 0) == -1){
		perror("send");
		close(sockfd);
		exit(1);
	}

	char header[MAXDATASIZE]="\0";
	char data[MAXDATASIZE]="\0";
	int content_length = -1;
	int header_length = 0;
	int header_or_data = 0; //0이면 아직 header, 1이면 data 읽는 중
	char *ptr_buf;

	while(1){
		/* HTTP response를 받는다.(server -> client) */
		strcpy(buf, "\0");
		if((numbytes = recv(sockfd, buf, sizeof buf, 0)) == -1){
			perror("recv");
			close(sockfd);
			exit(1);
		}

		buf[numbytes] = '\0';
		accumulate_numbytes += numbytes;

		if(header_or_data == 0){
			//header
			ptr_buf = strtok(buf, "\n");
			if(strcmp(header, "\0") == 0){
				strcpy(header, ptr_buf);
			}
			while(ptr_buf != NULL){
				if(strcmp(ptr_buf, "\r") == 0){
					//header end
					header_length += 2;
					ptr_buf = strtok(NULL, "\0");
					header_or_data = 1;
					break;
				}
				for(unsigned int i=0;i<strlen(ptr_buf);i++){
					if(ptr_buf[i] >= 'A' && ptr_buf[i] <= 'Z'){
						ptr_buf[i] = ptr_buf[i] + 32;
					}
				}
				if(strstr(ptr_buf, "content-length")!=NULL){
					content_length = strtol(ptr_buf+15, NULL, 10);
				}
				header_length += (strlen(ptr_buf)+1);		
				ptr_buf = strtok(NULL, "\n");
			}
			if(header_or_data == 1){
				//header end
				if(ptr_buf != NULL){
					strcpy(data, ptr_buf);
				}
				if(content_length > 0){
					printf("%s\n", header);
					printf("%d bytes written to 20191578.out\n", content_length);
					FILE *fp = fopen("20191578.out", "w");
					fprintf(fp, "%s", data);
					fclose(fp);
					accumulate_numbytes -= header_length;
				}
				else{
					printf("%s\n", header);
					printf("Content-Length not specified.\n");
				}
			}
		}
		else{
			//data
			if(content_length > 0){
				FILE *fp_data = fopen("20191578.out", "a");
				fprintf(fp_data, "%s", buf);
				fclose(fp_data);
			}
		}
		if(accumulate_numbytes >= content_length) break;
	}

	close(sockfd);
	return 0;
}
