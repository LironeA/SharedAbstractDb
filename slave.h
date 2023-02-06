#include "cstdlib"
#include "cstdio"

#define SLAVE_DATA "S.fl"
#define SLAVE_IND "S.ind"
#define SLAVE_SIZE sizeof(struct slave)
#define INDEX_SIZE sizeof(struct index)

struct slave {
    int id;
    int m_id;
    char name[50];
};

int get_s(slave* s, int id);
int del_s();
int update_s(slave* s);
int insert_s(slave* s);
int calc_s();
int ut_s();
int save_s(slave* s, index i);

index get_index_slave();

int get_s(slave* s, int id) {
    FILE* index_collection = fopen(SLAVE_IND, "rb");
    FILE* database = fopen(SLAVE_DATA, "rb");

    if (index_collection == nullptr || database == nullptr)
        return 1;
    struct index i{};
    fseek(index_collection, id * INDEX_SIZE, SEEK_SET);
    fread(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);

    fseek(database, i.id * i.record_size, SEEK_SET);
    fread(s, SLAVE_SIZE, 1, database);
    fclose(database);
    return 0;
}

int insert_s(slave* s) {
    index i = get_index_slave();
    return save_s(s, i);
}

int update_s(slave* s) {
    struct index i;
    return save_s(s, i);
}

index get_index_slave() {
    struct index i{};
    i.id = lastIndex++;
    i.record_size = SLAVE_SIZE;
    i.exists = 0;

    return i;
};

int save_s(slave* s, index i) {
    FILE* index_collection = fopen(SLAVE_IND, "w+");
    FILE* database = fopen(SLAVE_DATA, "w+");

    if (database == nullptr || index_collection == nullptr)
        return 1;

    // Insert a data about a user in the .fl file

    s->id = i.id;
    fseek(database, i.id * SLAVE_SIZE, SEEK_SET);
    fwrite(s, SLAVE_SIZE, 1, database);
    fclose(database);

    // Create an indexer and store it inn the .ind file

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}