package cse3040fp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Scanner;


public class Client {
	

	public static void main(String[] args) {
		
		if(args.length!=2) {
			System.out.print("Please give the IP address and port number as arguments.");
			System.exit(0);
		}
		
		try {
			String serverIp = args[0];
			@SuppressWarnings("resource")
			Socket socket = new Socket(serverIp, Integer.valueOf(args[1]));
			System.out.println("connected to server.");
			
			String userID;
			@SuppressWarnings("resource")
			Scanner scanner = new Scanner(System.in);
			while(true) {
				System.out.print("Enter userID>> ");
				userID = scanner.nextLine();
	
				int IDflag=0;
				if(userID.length()==0) IDflag=1;
				for(int i=0;i<userID.length();i++) {
					if(userID.charAt(i)<'a'||userID.charAt(i)>'z') {
						if(userID.charAt(i)<'0'||userID.charAt(i)>'9') {
							IDflag=1; break;
						}
					}
				}
				if(IDflag==0) {
					System.out.println("Hello "+userID+"!");
					break;
				}
				else {
					System.out.println("UserID must be a single word with lowercase alphabets and numbers.");
				}
			}
			
			
			
			
			
			//로그인 성공 후 명령어에 따른 기능 수행
			OutputStream out = socket.getOutputStream();
			DataOutputStream dos = new DataOutputStream(out);
			InputStream in = socket.getInputStream();
			DataInputStream dis = new DataInputStream(in);
			
			
			
			while(true) {
				System.out.print(userID+">> ");
				String command = scanner.nextLine();
				
				
				
				
				
				
				if(command.equals("add")) {
				//	System.out.println("님이 <add> 입력했음. 책 추가할거임.");
					System.out.print("add-title> ");
					String add_title = scanner.nextLine();
					if(add_title.trim().equals("")) continue;
					System.out.print("add-author> ");
					String add_author = scanner.nextLine();
					if(add_author.trim().equals("")) continue;
					dos.writeUTF(command);
					dos.writeUTF(add_title);
					dos.writeUTF(add_author);
					
					System.out.println(dis.readUTF());
					
				}
				
				
				
				
				
				else if(command.equals("borrow")) {
				//	System.out.println("님이 <borrow> 입력했음. 책 빌릴거임.");
					System.out.print("borrow-title> ");
					String borrow_title = scanner.nextLine();
					if(borrow_title.trim().equals("")) continue;
					dos.writeUTF(command);
					dos.writeUTF(borrow_title);
					dos.writeUTF(userID);
					
					System.out.println(dis.readUTF());
				}
				
				
				
				
				
				else if(command.equals("return")) {
				//	System.out.println("님이 <return> 입력했음. 책 반납할거임.");
					System.out.print("return-title> ");
					String return_title = scanner.nextLine();
					if(return_title.trim().equals("")) continue;
					dos.writeUTF(command);
					dos.writeUTF(return_title);
					dos.writeUTF(userID);
					
					System.out.println(dis.readUTF());
				}
				
				
				
				
				
				else if(command.equals("info")) {
				//	System.out.println("님이 <info> 입력했음. 책정보 출력할거임.");
					dos.writeUTF(command);
					dos.writeUTF(userID);
					
					System.out.println(dis.readUTF());
					int num=dis.readInt();
					for(int i=0;i<num;i++) {
						System.out.println(dis.readUTF());
					}
				}
				
				
				
				
				
				else if(command.equals("search")) {
				//	System.out.println("님이 <search> 입력했음. 책정보 찾을거임.");
					String search_string; int search_flag=0;
					while(true) {
						System.out.print("search-string> ");
						search_string = scanner.nextLine();
						if(search_string.length()>=3) {
							search_flag=1;
							break;
						}
						else if(search_string.length()==0) {
							search_flag=2;
							break;
						}
						else {
							System.out.println("Search string must be longer than 2 characters.");
						}
					}
					if(search_flag!=1) continue;
					dos.writeUTF(command);
					dos.writeUTF(search_string);
					
					System.out.println(dis.readUTF());
					int num=dis.readInt();
					for(int i=0;i<num;i++) {
						System.out.println(dis.readUTF());
					}
				}
				
				
				
				
				
				else {
					System.out.println("[available commands]");
					System.out.println("add: add a new book to the list of books.");
					System.out.println("borrow: borrow a book from the library.");
					System.out.println("return: return a book to the library.");
					System.out.println("info: show list of books I am currently borrowing.");
					System.out.println("search: search for books.");
				}
			}
			
			
		} catch(ConnectException ce) {
			System.out.print("Connection establishment failed.");
			System.exit(0);
		} catch(IOException ie) {
			ie.printStackTrace();
		} catch(Exception e) {
			e.printStackTrace();
		}

	}

}
