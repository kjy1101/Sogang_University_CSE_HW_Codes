package cse3040fp;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;


class bookInfo implements Comparable<bookInfo>{
	private String title;
	private String author;
	private String userID;
	public String getTitle() { return this.title; }
	public String getAuthor() { return this.author; }
	public String getUserID() { return this.userID; }
	public void setTitle(String str) { this.title=str; }
	public void setAuthor(String str) { this.author=str; }
	public void setUserID(String str) { this.userID=str; }
	public String toString() {
		return "\n"+title+"\n"+author+"\n"+userID+"\n";
	}
	@Override
	public int compareTo(bookInfo o) {
		String str1, str2;
		str1=this.title; str2=o.title;
		str1=str1.toLowerCase(); str2=str2.toLowerCase();
		return str1.compareTo(str2);
	}
}

class MyFileReader{
	public static boolean readTextFile(ArrayList<bookInfo> list) {
		try {
			BufferedReader bookinput = new BufferedReader(new FileReader("books.txt"));
			while(true) {
				bookInfo newBook = new bookInfo();
				String line = bookinput.readLine();
				if(line==null) break;
				String[] book;
				book = line.split("\t");
				newBook.setTitle(book[0].trim());
				newBook.setAuthor(book[1].trim());
				newBook.setUserID(book[2].trim());
				list.add(newBook);
			}
			bookinput.close();
		} catch(Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}
}

public class Server {
	static ArrayList<bookInfo> library = new ArrayList<>();
	
	public void start(String portString) {
		ServerSocket serverSocket = null;
		Socket socket = null;
		try {
			serverSocket = new ServerSocket(Integer.valueOf(portString));
			System.out.println("server has started.");
			while(true) {
				socket = serverSocket.accept();
				System.out.println("a new connection from [" + socket.getInetAddress() + ":" +socket.getPort() + "]");
				ServerReceiver thread = new ServerReceiver(socket);
				thread.start();
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	
	public static void main(String[] args) {
		if(args.length!=1) {
			System.out.print("Please give the port number as an argument.");
			System.exit(0);
		}

		boolean rv = MyFileReader.readTextFile(library);
		Collections.sort(library);
		if(rv==false) {
			System.out.println("Input file not found.");
			return;
		}
		new Server().start(args[0]);
	}
	
	
	class ServerReceiver extends Thread{
		Socket socket;
		ServerReceiver(Socket socket) {
			this.socket = socket;
		}
	
		

		public void run() {
			while(true) {
				try {
					
					OutputStream out = socket.getOutputStream();
					DataOutputStream dos = new DataOutputStream(out);					
					InputStream in = socket.getInputStream();
					DataInputStream dis = new DataInputStream(in);
					
				
			//		int cnt=0;
					while(true) {
			//			System.out.println(cnt++);
						String command = dis.readUTF();
			//			System.out.println("명령: "+command);
						
						
						
						
						
						if(command.equals("add")) {
							String add_title = dis.readUTF();
							String add_author = dis.readUTF();
							int add_flag=0;
							String str1 = add_title;
							String str2 = add_author;
							str1=str1.toLowerCase(); str2=str2.toLowerCase();
							for(bookInfo it:library) {
								String str3 = it.getTitle();
								str3=str3.toLowerCase();
								if(str1.equals(str3)) {
									add_flag=1; break;
								}
							}
							if(add_flag==0) {
								//책 없음, 추가할 거임
								bookInfo addBook = new bookInfo();
								addBook.setTitle(add_title);
								addBook.setAuthor(add_author);
								addBook.setUserID("-");
								library.add(addBook);
								Collections.sort(library);
							
								BufferedWriter File = new BufferedWriter(new FileWriter("books.txt"));
								for(bookInfo it:library) {
									File.write(it.getTitle()+"\t"+it.getAuthor()+"\t"+it.getUserID()+"\n");
								}
								File.close();
								dos.writeUTF("A new book added to the list.");
							}
							else {
								//책 있음, 추가 안함
								dos.writeUTF("The book already exists in the list.");
							}
						}
						
						
						
						
						
						else if(command.equals("borrow")) {
						//	System.out.println("빌린대");
							String borrow_book = dis.readUTF();
							String clientID = dis.readUTF();
							int borrow_flag=0;
							String str1 = borrow_book;
							str1=str1.toLowerCase();
							String borrowID=null; String borrowedBook=null;
							for(bookInfo it:library) {
								String str2 = it.getTitle();
								str2=str2.toLowerCase();
								if(str1.equals(str2)) {
									borrowID = it.getUserID();
									borrowedBook = it.getTitle();
									borrow_flag=1; break;
								}
							}
							if(borrow_flag==1) {
								//책있음, 빌릴수있는지 확인
							//	System.out.println(borrowID.charAt(0));
							//	dos.writeUTF("확인중이야");
								if(borrowID.charAt(0)=='-') {
									dos.writeUTF("You borrowed a book. - "+borrowedBook);
									BufferedWriter File = new BufferedWriter(new FileWriter("books.txt"));
									for(bookInfo it:library) {
										if(it.getTitle().equals(borrowedBook)) {
											it.setUserID(clientID);
										}
										File.write(it.getTitle()+"\t"+it.getAuthor()+"\t"+it.getUserID()+"\n");
									}
									File.close();
								}
								else {
									//이미 누가 빌리고 있음
									dos.writeUTF("The book is not available.");
								}
							}
							else {
								//책없음, 못빌림
								dos.writeUTF("The book is not available.");
							}
						}
						
						
						
						
						
						else if(command.equals("return")) {
						//	System.out.println("반납한대");
							String return_book = dis.readUTF();
							String clientID = dis.readUTF();
							int return_flag=0;
							String str1 = return_book;
							str1=str1.toLowerCase();
							String returnedBook=null;
							for(bookInfo it:library) {
								String str2 = it.getTitle();
								str2 = str2.toLowerCase();
								if(str1.equals(str2)) {
									if(clientID.equals(it.getUserID())) {
										returnedBook=it.getTitle();
										return_flag=1; break;
									}
								}
							}
							if(return_flag==1) {
								//책 빌린거 맞음, 돌려줌
								dos.writeUTF("You returned a book. - "+returnedBook);
								BufferedWriter File = new BufferedWriter(new FileWriter("books.txt"));
								for(bookInfo it:library) {
									if(it.getTitle().equals(returnedBook)) {
										it.setUserID("-");
									}
									File.write(it.getTitle()+"\t"+it.getAuthor()+"\t"+it.getUserID()+"\n");
								}
								File.close();
							}
							else {
								//책 안빌리셨는데요
								dos.writeUTF("You did not borrow the book.");
							}
						}
						
						
						
						
						
						else if(command.equals("info")) {
						//	System.out.println("정보달래");
							String clientID = dis.readUTF();
							int count=0;
							for(bookInfo it:library) {
								if(it.getUserID().equals(clientID)) {
									count++;
								}
							}
							dos.writeUTF("You are currently borrowing "+count+" books:");
							dos.writeInt(count);
							int num=1;
							for(bookInfo it:library) {
								if(it.getUserID().equals(clientID)) {
									dos.writeUTF(num+". "+it.getTitle()+", "+it.getAuthor());
									num++;
								}
							}
						}
						
						
						
						
						
						else if(command.equals("search")) {
						//	System.out.println("찾는대");
							String search_string = dis.readUTF();
							search_string = search_string.toLowerCase();
							int count=0;
							for(bookInfo it:library) {
								String str1 = it.getTitle();
								String str2 = it.getAuthor();
								str1=str1.toLowerCase(); str2=str2.toLowerCase();
								if(str1.contains(search_string)||str2.contains(search_string)) {
									count++;
								}
							}
							dos.writeUTF("Your search matched "+count+" results.");
							dos.writeInt(count);
							int num=1;
							for(bookInfo it:library) {
								String str1 = it.getTitle();
								String str2 = it.getAuthor();
								str1=str1.toLowerCase(); str2=str2.toLowerCase();
								if(str1.contains(search_string)||str2.contains(search_string)) {
									dos.writeUTF(num+". "+it.getTitle()+", "+it.getAuthor());
									num++;
								}
							}
						}
						
					}
					
			//		System.out.println(getTime() + "sent message");
			//		dos.close();
				//	socket.close();
				} catch (IOException e) {
					e.printStackTrace();
				//	System.out.println("뭔가가 잘못되었따.");
					return;
				} finally {
					System.out.println("["+socket.getInetAddress()+":"+socket.getPort()+"]"+" has disconnected.");
				}
			}
		}
		
		
	}
}