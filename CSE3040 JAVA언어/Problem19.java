package cse3040mp2;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collections;

class BookInfo implements Comparable<BookInfo>{
	private String title;
	private String author;
	private String price;
	private int rank;
	public void setTitle(String str) {
		this.title=str;
	}
	public void setAuthor(String str) {
		this.author=str;
	}
	public void setPrice(String str) {
		this.price=str;
	}
	public void setRank(int r) {
		this.rank=r;
	}
	public String toString() {
		return "#"+rank+" "+title+", "+author+", "+price;
	}
	@Override
	public int compareTo(BookInfo o) {
		if(this.rank>o.rank) {
			return -1;
		}else if(this.rank<o.rank) {
			return 1;
		}else {
			return 0;
		}
	}
}

class BookReader{
	private static ArrayList<String> lines = new ArrayList<String>();
	private static ArrayList<BookInfo> bookArray = new ArrayList<BookInfo>();
	
	public static ArrayList<BookInfo> readBooks(String string) {
		// TODO Auto-generated method stub
		
		URL url = null;
		BufferedReader input = null;
		String address =  string;
		String line = "";
		
		try {
			url = new URL(address);
			input = new BufferedReader(new InputStreamReader(url.openStream()));
			while((line=input.readLine()) != null) {
				if(line.trim().length() > 0)
					lines.add(line);
			}
			input.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		int rank = 1;
		int begin=0, end=0;
		String tn = null,an=null;
		
		for(int i=0;i<lines.size();i++) {
			String l = lines.get(i);
			BookInfo book = new BookInfo();
			//title
			if(l.contains("product-info-title")) {
				if(lines.get(i+1).contains("<a title=\"\" class=\" \" onclick=\"")) {
					begin = lines.get(i+1).indexOf("\">")+"\">".length();
					end = lines.get(i+1).indexOf("</a><span");
					tn=lines.get(i+1).substring(begin,end);
				}
			}
			//author
			if(l.contains("product-shelf-author")) {
				begin = l.indexOf("\">", l.indexOf(">by"))+"\">".length();
				end=l.indexOf("</a>");
				an=l.substring(begin,end);
			}
			//price
			if(l.contains("Current price")) {
				begin = l.indexOf("is ")+"is ".length();
				end=l.indexOf(", Original");
				book.setTitle(tn);
				book.setAuthor(an);
				book.setPrice(l.substring(begin,end));
				book.setRank(rank);
				bookArray.add(book);
				rank++;
			}
		}
		
		return bookArray;
	}
	
}

public class Problem19 {
	public static void main(String[] args) {
		ArrayList<BookInfo> books;
		books = BookReader.readBooks("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
		Collections.sort(books);
		for(int i=0; i<books.size(); i++) {
			BookInfo book = books.get(i);
			System.out.println(book);
		}
	}
}
