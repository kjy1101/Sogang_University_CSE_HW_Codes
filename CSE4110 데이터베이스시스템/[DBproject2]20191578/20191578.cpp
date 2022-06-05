#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "mysql";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;


	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		char buffer[1000];
		int size;
		FILE* fp = fopen("20191578_start.txt", "r");
		if (fp == NULL) {
			printf("No input file.\n");
			exit(1);
		}

		const char* query;
		int state = 0;
		/* create table & insert data */
		printf("There is a lot of data, so it may take a long time...\n");
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			query = (const char*)buffer;
			state = mysql_query(connection, query);
			if (state == 0) {
				//printf("create&insert success\n");
			}
		}
		fclose(fp);
		printf("create&insert success\n");

		int input;
		int k;
		int ranking = 1;
		char brand[40];
		char qbuffer[1000];
		int qsize;
		int flag;
		char date1[32];
		char date2[32];
		while (1) {
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf(">> ");
			scanf("%d", &input);
			if (input == 0) {
				char ebuffer[1000];
				int esize;
				FILE* efp = fopen("20191578_end.txt", "r");
				if (efp == NULL) {
					printf("No input file.\n");
					exit(1);
				}
				while (fgets(ebuffer, sizeof(ebuffer), efp) != NULL) {
					query = (const char*)ebuffer;
					state = mysql_query(connection, query);
					if (state == 0) {
						printf("delete&drop success\n");
					}
				}
				fclose(efp);
				break;
			}
			switch (input) {
			case 1:
				printf("---- TYPE 1 ----\n\n");
				printf("\t** Show the sales trends for a particular brand over the past k years. **\n");
				printf("\tWhich K? (K < 4) : ");
				scanf("%d", &k);
				if (k > 3 || k < 1) {
					printf("\n\tK must be at least 1 and not more than 3.\n\n\n");
					continue;
				}
				printf("\tWhich brand? : ");
				scanf("%s", brand);

				sprintf(qbuffer, "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='%s') select year, sum(sales) from sales_trend where year<2021 group by year order by year desc limit %d", brand, k);
				//query = "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='Audi') select year, sum(sales) from sales_trend group by year";
				query = (const char*)qbuffer;
				state = mysql_query(connection, query);
				flag = 0;
				if (state == 0)
				{
					printf("\n\tSales trends of %s for past %d years:\n", brand, k);
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\t%s년 Sales - $ %s\n", sql_row[0], sql_row[1]);
						flag = 1;
					}
					mysql_free_result(sql_result);
				}
				if (flag == 0) {
					printf("\n\tThere is no brand matched with your input '%s'.\n\n\n", brand);
					continue;
				}
				printf("\n\n");


				printf("---- Suptypes in TYPE 1 ----\n\n");
				printf("\t1. TYPE 1-1\n");
				printf(">> ");
				scanf("%d", &input);
				if (input != 1) break;
				else {
					printf("\t** Then break these data out by gender of the buyer. **\n");
					sprintf(qbuffer, "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='%s') select year, gender, sum(sales) from sales_trend where year < 2021 group by year,gender order by year desc limit %d", brand, k * 2);
					//query = "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='Audi') select year, sum(sales) from sales_trend group by year";
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\tSales trends of %s for past %d years according to gender:\n", brand, k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (!strcmp(sql_row[1], "F")) {
								printf("\n\t%s년 Sales by Female - $ %s\n", sql_row[0], sql_row[2]);
							}
							else {
								printf("\n\t%s년 Sales by Male - $ %s\n", sql_row[0], sql_row[2]);
							}
						}
						mysql_free_result(sql_result);
					}
				}
				printf("\n\n");

				printf("---- Suptypes in TYPE 1-1 ----\n\n");
				printf("\t1. TYPE 1-1-1\n");
				printf(">> ");
				scanf("%d", &input);
				if (input != 1) break;
				else {
					printf("\t** Then by income range. **\n");
					sprintf(qbuffer, "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='%s') select year, gender, sum(sales), income from sales_trend where year < 2021 group by year,gender,income order by year desc limit %d", brand, k * 6);
					//query = "with sales_trend(year, month, gender, income, sales) as (select date_year, date_month, gender, income, sales from brand_sales where brand_name='Audi') select year, sum(sales) from sales_trend group by year";
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\tSales trends of %s for past %d years according to gender:\n", brand, k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (!strcmp(sql_row[1], "F")) {
								printf("\n\t%s년 Sales by Female ( income range : $ %s ~ ) - $ %s\n", sql_row[0], sql_row[3], sql_row[2]);
							}
							else {
								printf("\n\t%s년 Sales by Male ( income range: $ %s ~ ) - $ %s\n", sql_row[0], sql_row[3], sql_row[2]);
							}
						}
						mysql_free_result(sql_result);
					}
				}
				printf("\n\n");

				break;
			case 2:
				printf("---- TYPE 2 ----\n\n");
				printf("\t** Show sales trends for various brands over the past k months. **\n");
				printf("\tWhich K? (K < 6) : ");
				scanf("%d", &k);
				if (k > 5 || k < 1) {
					printf("\n\tK must be at least 1 and not more than 5.\n\n\n");
					continue;
				}
				sprintf(qbuffer, "with sales_trend(brand, month, gender, income, sales) as (select brand_name, date_month, gender, income, sales from brand_sales where date_year='2021') select brand, month, sum(sales) from sales_trend group by brand, month order by month desc limit %d", k * 15);
				query = (const char*)qbuffer;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("\n\tSales trends of all brands for past %d months:\n", k);
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\t%s월 Sales of %s - $ %s\n", sql_row[1], sql_row[0], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");


				printf("---- Suptypes in TYPE 2 ----\n\n");
				printf("\t1. TYPE 2-1\n");
				printf(">> ");
				scanf("%d", &input);
				if (input != 1) break;
				else {
					printf("\t** Then break these data out by gender of the buyer. **\n");
					sprintf(qbuffer, "with sales_trend(brand, month, gender, income, sales) as (select brand_name, date_month, gender, income, sales from brand_sales where date_year='2021' and gender='F') select month, brand, gender, sum(sales) from sales_trend group by brand, month, gender order by month desc limit %d", k * 15);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\tSales trends of all brands for past %d months by Female:\n", k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\t%s월 Sales of %s by Female - $ %s\n", sql_row[0], sql_row[1], sql_row[3]);
							//printf("\n\t%s월 Sales of %s - $ %s\n", sql_row[1], sql_row[0], sql_row[2]);
						}
						mysql_free_result(sql_result);
					}
					sprintf(qbuffer, "with sales_trend(brand, month, gender, income, sales) as (select brand_name, date_month, gender, income, sales from brand_sales where date_year='2021' and gender='M') select month, brand, gender, sum(sales) from sales_trend group by brand, month, gender order by month desc limit %d", k * 15);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\n\tSales trends of all brands for past %d months by Male:\n", k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\t%s월 Sales of %s by Male - $ %s\n", sql_row[0], sql_row[1], sql_row[3]);
							//printf("\n\t%s월 Sales of %s - $ %s\n", sql_row[1], sql_row[0], sql_row[2]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n\n");
				}


				printf("---- Suptypes in TYPE 2-1 ----\n\n");
				printf("\t1. TYPE 2-1-1\n");
				printf(">> ");
				scanf("%d", &input);
				if (input != 1) break;
				else {
					printf("\t** Then by income range. **\n");
					sprintf(qbuffer, "with sales_trend(brand, month, gender, income, sales) as (select brand_name, date_month, gender, income, sales from brand_sales where date_year='2021' and gender='F') select month, brand, gender, sum(sales), income from sales_trend group by brand, month, gender, income order by month desc limit %d", k * 45);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\tSales trends of all brands for past %d months by Female:\n", k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\t%s월 Sales of %s by Female ( income range : $ %s ~ ) - $ %s\n", sql_row[0], sql_row[1], sql_row[4], sql_row[3]);
							//printf("\n\t%s월 Sales of %s - $ %s\n", sql_row[1], sql_row[0], sql_row[2]);
						}
						mysql_free_result(sql_result);
					}
					sprintf(qbuffer, "with sales_trend(brand, month, gender, income, sales) as (select brand_name, date_month, gender, income, sales from brand_sales where date_year='2021' and gender='M') select month, brand, gender, sum(sales), income from sales_trend group by brand, month, gender, income order by month desc limit %d", k * 45);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n\n\tSales trends of all brands for past %d months by Male:\n", k);
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\t%s월 Sales of %s by Male ( income range : $ %s ~ ) - $ %s\n", sql_row[0], sql_row[1], sql_row[4], sql_row[3]);
							//printf("\n\t%s월 Sales of %s - $ %s\n", sql_row[1], sql_row[0], sql_row[2]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n\n");
				}
				break;
			case 3:
				printf("---- TYPE 3 ----\n\n");
				printf("\t**  Find that transmissions made by supplier (company name) between two given dates are defective. **\n");
				printf("\tFrom when? (Format: YYYY-MM-DD) : ");
				scanf("%s", date1);
				if (date1[4] != '-' || date1[7] != '-') {
					printf("\tWrong Format: YYYY-MM-DD\n\n\n");
					continue;
				}
				printf("\tUntil when? (Format: YYYY-MM-DD) : ");
				scanf("%s", date2);
				if (date2[4] != '-' || date2[7] != '-') {
					printf("\tWrong Format: YYYY-MM-DD\n\n\n");
					continue;
				}
				flag = 0;
				printf("\tFind defective transmissions which is made during %s ~ %s\n\n", date1, date2);
				sprintf(qbuffer, "select supplier_name, supplied_date from plant_supplier where supplied_part='X-transmission' AND DATE(supplied_date) BETWEEN '%s' AND '%s';", date1, date2);
				query = (const char*)qbuffer;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\tSupplier '%s' supplied defective transmission in %s\n", sql_row[0], sql_row[1]);
						flag = 1;
					}
					mysql_free_result(sql_result);
				}
				if (flag == 0) {
					printf("\tThere is no supplier which supplied defective transmission during %s ~ %s.\n\n\n", date1, date2);
					continue;
				}
				printf("\n\n");


				printf("---- Suptypes in TYPE 3 ----\n\n");
				printf("\t1. TYPE 3-1\n");
				printf("\t2. TYPE 3-2\n");
				printf(">> ");
				scanf("%d", &input);
				if (input == 1) {
					printf("\t** Find the VIN of each car containing such a transmission and the customer to which it was sold. **\n");
					sprintf(qbuffer, "with defective_VIN(supplier, def_VIN) as (select supplier_name, related_car_VIN from plant_supplier where supplied_part='X-transmission' AND DATE(supplied_date) BETWEEN '%s' AND '%s') select C.customer_name, C.purchased_VIN from customer C right join defective_VIN DV on C.purchased_VIN=DV.def_VIN;", date1, date2);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\tCustomer '%s' purchased vehicle '%s' which has defective transmission.\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n\n");
				}
				else if (input == 2) {
					printf("\t** Find the dealer who sold the VIN and transmission for each vehicle containing these transmissions. **\n");
					sprintf(qbuffer, "with defective_VIN(supplier, def_VIN) as (select supplier_name, related_car_VIN from plant_supplier where supplied_part='X-transmission' AND DATE(supplied_date) BETWEEN '%s' AND '%s') select C.dealer_name, C.purchased_VIN from customer C right join defective_VIN DV on C.purchased_VIN=DV.def_VIN;", date1, date2);
					query = (const char*)qbuffer;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("\n\tDealer '%s' sold vehicle '%s' which has defective transmission.\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n\n");
				}
				else break;
				break;
			case 4:
				printf("---- TYPE 4 ----\n\n");
				printf("\t** Find the top k brands by dollar-amount sold by the year. **\n");
				printf("\tWhich K? (K < 6) : ");
				scanf("%d", &k);
				if (k == 1) query = "select brand_name, dollar_amount_sold from brand_info order by dollar_amount_sold desc limit 1";
				else if (k == 2) query = "select brand_name, dollar_amount_sold from brand_info order by dollar_amount_sold desc limit 2";
				else if (k == 3) query = "select brand_name, dollar_amount_sold from brand_info order by dollar_amount_sold desc limit 3";
				else if (k == 4) query = "select brand_name, dollar_amount_sold from brand_info order by dollar_amount_sold desc limit 4";
				else if (k == 5) query = "select brand_name, dollar_amount_sold from brand_info order by dollar_amount_sold desc limit 5";
				else {
					printf("\n\tK must be at least 1 and not more than 5.\n\n\n");
					continue;
				}

				state = mysql_query(connection, query);
				ranking = 1;
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\t%d. %s ( $ %s )\n", ranking++, sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
				break;
			case 5:
				printf("---- TYPE 5 ----\n\n");
				printf("\t** Find the top k brands by unit sales by the year. **\n");
				printf("\tWhich K? (K < 6) : ");
				scanf("%d", &k);
				if (k == 1) query = "select brand_name, unit_sales from brand_info order by unit_sales desc limit 1";
				else if (k == 2) query = "select brand_name, unit_sales from brand_info order by unit_sales desc limit 2";
				else if (k == 3) query = "select brand_name, unit_sales from brand_info order by unit_sales desc limit 3";
				else if (k == 4) query = "select brand_name, unit_sales from brand_info order by unit_sales desc limit 4";
				else if (k == 5) query = "select brand_name, unit_sales from brand_info order by unit_sales desc limit 5";
				else {
					printf("\n\tK must be at least 1 and not more than 5.\n\n\n");
					continue;
				}

				state = mysql_query(connection, query);
				ranking = 1;
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\t%d. %s ( $ %s )\n", ranking++, sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
				break;
			case 6:
				printf("\t---- TYPE 6 ----\n\n");
				printf("\t** In what month(s) do convertibles sell best? **\n");
				query = "with conv_sales(mon, sale) as (select month, sum(sales) from model_info group by month) select mon from conv_sales where sale = (select max(sale) from conv_sales)";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\tThe car with the body style convertible sold the most in %s월.\n\n\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				break;
			case 7:
				printf("\t---- TYPE 7 ----\n\n");
				printf("\t** Find those dealers who keep a vehicle in inventory for the longest average time. **\n");
				query = "SELECT * FROM dealer WHERE keeping_average_time=(SELECT max(keeping_average_time) FROM dealer)";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\n\tDealer '%s' keeps the vehicle in inventory for an average of %s days.\n\n\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				break;
			}
		}
		//query = (const char*)buffer;
		//printf("query: %s\n", query);
		//const char* buffer = "create table company (company_name varchar(15), primary key (company_name));";

		/*state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			mysql_free_result(sql_result);
		}*/
		mysql_close(connection);
	}

	return 0;
}





/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}
*/