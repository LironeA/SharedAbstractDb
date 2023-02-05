#include "cstdlib"
#include "cstdio"
#include "index.h"
#include <cstring>

#define MASTER_DATA "M.fl"
#define MASTER_IND "M.ind"
#define MASTER_SIZE sizeof(struct master)
#define INDEX_SIZE sizeof(struct index)

using namespace std;

int lastIndex = 0;

struct master {
    int id;
    string name;
};

int get_m();
int del_m();
int update_m();
int insert_m();
int calc_m();
int ut_m();
int save_m(master* m, index i);

index get_index_master();

int get_m(master* m, int id) {
    FILE* index_collection = fopen(MASTER_IND, "rb");
    FILE* database = fopen(MASTER_DATA, "rb");

    if (index_collection == nullptr || database == nullptr)
        return 1;
    struct index i{};
    fseek(index_collection, id * INDEX_SIZE, SEEK_SET);
    fread(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);

    fseek(database, i.id * i.record_size, SEEK_SET);
    fread(m, MASTER_SIZE, 1, database);
    fclose(database);
    return 0;
}

int insert_m(master* m) {
    index i = get_index_master();
    return save_m(m, i);
}

int update_m(master* m) {
    struct index i;
    return save_m(m, i);
}

index get_index_master() {
    struct index i{};
    i.id = lastIndex++;
    i.record_size = MASTER_SIZE;
    i.exists = 0;

    return i;
};

int save_m(master* m, index i) {
    FILE* index_collection = fopen(MASTER_IND, "w+");
    FILE* database = fopen(MASTER_DATA, "w+");

    if (database == nullptr || index_collection == nullptr)
        return 1;

    // Insert a data about a user in the .fl file

    m->id = i.id;
    fseek(database, i.id * MASTER_SIZE, SEEK_SET);
    fwrite(m, MASTER_SIZE, 1, database);
    fclose(database);

    // Create an indexer and store it inn the .ind file

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}