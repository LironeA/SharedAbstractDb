#include "cstdlib"
#include "cstdio"

#define SLAVE_DATA "S.fl"
#define SLAVE_IND "S.ind"
#define SLAVE_SIZE sizeof(struct slave)

struct slave {
    int id;
    int m_id;
    char name[50];
};

int get_s();
int del_s();
int update_s();
int insert_s();
int calc_s();
int ut_s();
index get_index_slave();


int get_s(slave* s) {
    FILE* ind = fopen(SLAVE_IND, "rb");
    FILE* database = fopen(SLAVE_DATA, "rb");

    // TODO: Implement check if index and database tables exist. If empty, return none

    fseek(database, 0, SEEK_SET);
}

int insert_s(slave s) {
    FILE* index_collection = fopen(SLAVE_IND, "w+");
    FILE* database = fopen(SLAVE_DATA, "w+");

    // TODO: Implement check if index and database tables exist. If empty, create new one

    // Insert a data about a user in the .fl file

    fseek(database, 0, SEEK_SET);
    fwrite(&s, SLAVE_SIZE, 1, database);
    fclose(database);
    // TODO: Catch an exception if write failed, so we don't create an unused index

    // Create an indexer and store it inn the .ind file
    index i = get_index_slave();

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}

index get_index_slave() {
    struct index i{};
    i.id = lastIndex++;
    i.record_size = SLAVE_SIZE;
    i.exists = 0;

    //printf("Index created. Id: %d\n", i.id);
    return i;
};