#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct Table_Entry
{
	uint32_t hash;
	char *string;
	Table_Entry *next;
} Table_Entry;

typedef struct String_Table
{
	uint32_t entry_count;
	Table_Entry *entries;
} String_Table;

uint32_t string_hash(const char *str)
{
	uint32_t hash = 1;
	char c;
	while (c = *str++)
	{
		hash = hash * 3 + c;
	}
	return hash;
}

String_Table *create_table()
{
	const uint32_t entry_count = 1024;

	String_Table *table = (String_Table*)malloc(sizeof(String_Table));
	Table_Entry *entries = (Table_Entry*)malloc(entry_count * sizeof(Table_Entry));

	if (!table || !entries)
	{
		free(table);
		free(entries);
		return NULL;
	}

	table->entry_count = entry_count;
	table->entries = entries;

	return table;
}

bool initialize_entry(String_Table *table, Table_Entry *entry, uint32_t hash, const char *string)
{
	unsigned size = (unsigned)strlen(string) + 1;
	char *canonical_string = (char*)malloc(size);
	if (canonical_string == NULL)
		return false;

	memcpy(canonical_string, string, size + 1);

	entry->hash = hash;
	entry->string = canonical_string;
	entry->next = NULL;
	return true;
}

Table_Entry *create_entry(String_Table *table, uint32_t hash, const char *string)
{
	Table_Entry *entry = (Table_Entry*)malloc(sizeof(Table_Entry));

	if (!initialize_entry(table, entry, hash, string))
	{
		free(entry);
		return NULL;
	}

	return entry;
}


const char *intern_string(String_Table *table, const char *string)
{
	uint32_t hash = string_hash(string);
	uint32_t index = hash % table->entry_count;

	Table_Entry *entry = &table->entries[index];

	if (entry->string == NULL)
	{
		if (initialize_entry(table, entry, hash, string))
			return entry->string;
		return NULL;
	}

	while (hash != entry->hash || strcmp(string, entry->string))
	{
		if (entry->next)
			entry = entry->next;
		else
		{
			Table_Entry *new_entry = create_entry(table, hash, string);
			if (!new_entry)
				return NULL;
			entry->next = new_entry;
			return new_entry->string;
		}
	}

	return entry->string;
}

const char *find_string(const String_Table *table, const char *string)
{
	uint32_t hash = string_hash(string);
	uint32_t index = hash % table->entry_count;

	Table_Entry *entry = &table->entries[index];

	if (entry->string == NULL)
		return NULL;

	while (hash != entry->hash || strcmp(string, entry->string))
	{
		if (entry->next)
			entry = entry->next;
		else
			return NULL;
	}

	return entry->string;
}

