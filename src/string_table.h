
typedef struct String_Table String_Table;

String_Table *create_table();
const char *intern_string(String_Table *table, const char *string);
const char *find_string(const String_Table *table, const char *string);

