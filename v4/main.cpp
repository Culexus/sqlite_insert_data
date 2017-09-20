#include <iostream>
#include <conio.h>
#include <string>
#include "sqlite3.h"

struct test_struct
{
	std::string v1;
	std::string v2;
	int v3;
};

char* SQL1 = "CREATE TABLE IF NOT EXISTS test(value1, value2);";
char* SQL2 = "INSERT INTO test VALUES(4,4);INSERT INTO test VALUES(8,5);INSERT INTO test VALUES(12,6);";
char* SQL3 = "SELECT value1 FROM test WHERE value2 == 3;";

sqlite3* db_pointer;
char* error_msg = 0;
int return_code;
test_struct resoults;

static int callback(void *data, int argc, char **argv, char **azColName);

int main()
{
	printf("START\n");

	return_code = sqlite3_open("test.db", &db_pointer);
	printf("db openned with code: %i\n", return_code);

	return_code = sqlite3_exec(db_pointer, SQL1, callback, 0, &error_msg);
	printf("db closed with code: %i\n", return_code);

	/*
	return_code = sqlite3_exec(db_pointer, SQL2, callback, 0, &error_msg);
	printf("SQL2 end with code: %i\n", return_code);
	*/

	return_code = sqlite3_exec(db_pointer, SQL3, callback, &resoults, &error_msg);
	printf("v1: %s", resoults.v1);
	printf("SQL3 end with code: %i\n", return_code);

	return_code = sqlite3_close(db_pointer);
	printf("SQL1 end with code: %i\n", return_code);

	printf("END\n");
	getchar();
	return 0;
}
static int callback(void *data, int argc, char **argv, char **azColName)
{
	printf("callback done\n");
	fprintf(stderr, "%s: ", (const char*)data);
	test_struct* resoults = (test_struct*)data;
	for (int i = 0; i<argc; i++)
	{
		resoults->v1 = argv[0];
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}