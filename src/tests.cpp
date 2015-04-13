#include "string_table.h"
#include <cstdio>

bool had_error;

void test_assert(bool condition, const char *expression, const char *file, int line)
{
	if (!condition)
	{
		printf("%s(%d): Test fail: %s\n", file, line, expression);
		had_error = true;
	}
}

#define TEST_ASSERT(x) test_assert(x, #x, __FILE__, __LINE__)

void test_string_table()
{
	String_Table *table = create_table();

	const char *test0 = find_string(table, "test");
	const char *test1 = intern_string(table, "test");
	const char *test2 = intern_string(table, "test");
	const char *test3 = find_string(table, "test");

	TEST_ASSERT(test0 == NULL);
	TEST_ASSERT(test1 == test2);
	TEST_ASSERT(test2 == test3);
}

int main(int argc, char **argv)
{
	test_string_table();

	return had_error ? 1 : 0;
}

