#include "cstdlib"
#include "cstdio"
#include "index.h"
#include "string.h"

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

    // TODO: Implement check if index and database tables exist. If empty, return none

    struct index i{};
    fseek(index_collection, id * INDEX_SIZE, SEEK_SET);
    fread(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);

    // TODO: Implement check on index. If empty, return none. If exists == 0, return none.

    fseek(database, i.id * i.record_size, SEEK_SET);
    fread(m, MASTER_SIZE, 1, database);
    fclose(database);
    return 1;
}

int insert_m(master* m) {
    index i = get_index_master();
    save_m(m, i);
    return 1;
}

int update_m(master* m) {
    struct index i;
    save_m(m, i);
    return 1;
}

index get_index_master() {
    struct index i{};
    i.id = lastIndex++;
    i.record_size = sizeof(master);
    i.exists = 0;

    return i;
};

int save_m(master* m, index i) {
    FILE* index_collection = fopen(MASTER_IND, "w+");
    FILE* database = fopen(MASTER_DATA, "w+");

    // TODO: Implement check if index and database tables exist. If empty, create new one

    // Insert a data about a user in the .fl file

    m->id = i.id;
    fseek(database, i.id * MASTER_SIZE, SEEK_SET);
    fwrite(m, MASTER_SIZE, 1, database);
    fclose(database);
    // TODO: Catch an exception if write failed, so we don't create an unused index

    // Create an indexer and store it inn the .ind file

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}