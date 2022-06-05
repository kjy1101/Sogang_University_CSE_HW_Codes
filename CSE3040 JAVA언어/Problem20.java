package cse3040mp2_3;

import java.util.ArrayList;
import java.util.Collections;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

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
	private static ArrayList<BookInfo> bookArray = new ArrayList<BookInfo>();
	public static ArrayList<BookInfo> readBooksJsoup(String string) {
		String url = string;
		Document doc = null;
		
		try {
			doc = Jsoup.connect(url).get();
		}catch(Exception e) {
			e.printStackTrace();
			System.exit(0);
		}
		
		Elements title1 = doc.select("h3.product-info-title");
		Elements title2 = title1.select("a[title]");
		
		Elements author1 = doc.select("div.product-shelf-author");
		Elements author2 = author1.select("a[href]");
	//	System.out.println(author1);
		int[] n_authors = new int[20]; int idx=0, count=0;
		for(int i=0;i<20;i++) {
		//	System.out.println(author1.eq(i).text());
			if(author1.eq(i).text().contains(",")==true) {
		//		System.out.println("multi authors");
				while(idx<author1.eq(i).text().length()) {
					if(author1.eq(i).text().charAt(idx)==',') {
						count++;
					}
					idx++;
				}
				n_authors[i]=count+1;
			}
			else {
				n_authors[i]=1;
			}
			count=0; idx=0;
		}
	//	for(int i=0;i<20;i++) System.out.println(n_authors[i]);
		
		Elements price1 = doc.select("span.current");
		Elements price2 = price1.select("a[href]");
		int j=0;
		for(int i=0;i<20;i++) {
			BookInfo book = new BookInfo();
			book.setTitle(title2.eq(i).text());
			book.setAuthor(author2.eq(j).text());
			j=j+n_authors[i];
			book.setPrice(price2.eq(i).text());
			book.setRank(i+1);
			bookArray.add(book);
		}
		
		return bookArray;
	}
	
}

public class Problem20 {
	public static void main(String[] args) {
		ArrayList<BookInfo> books;
		books = BookReader.readBooksJsoup("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
		Collections.sort(books);
		for(int i=0; i<books.size(); i++) {
			BookInfo book = books.get(i);
			System.out.println(book);
		}
	}
}
