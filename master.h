#pragma once

#include "cstdlib"
#include "cstdio"
#include "index.h"
#include <cstring>
#include "master.h"

#define MASTER_DATA "M.fl"
#define MASTER_IND "M.ind"
#define MASTER_SIZE sizeof(struct master)
#define INDEX_SIZE sizeof(struct index)

using namespace std;

int last_index_master = 0;

struct master {
    int id;
    string name;
};

int get_m(master* m, int id);
int update_m(master* m);
int insert_m(master* m);
int calc_m();
int ut_m();
int save_m(master* m, index i);

index get_index_master(int id);
index get_next_index_master();
int insert_index_m(index i);

int get_m(master* m, int id) {
    index i = get_index_master(id);
    if (i.id == -1 || i.exists == 1)
        return 1;

    FILE* database = fopen(MASTER_DATA, "rb");

    fseek(database, i.id * i.record_size, SEEK_SET);
    fread(m, MASTER_SIZE, 1, database);
    fclose(database);

    return 0;
}

int is_index_master(int id) {
    if (id > last_index_master)
        return 1;
    FILE* index_collection = fopen(MASTER_IND, "rb");
    if (index_collection == nullptr)
        return 1;

    fseek(index_collection, 0, SEEK_END);
    long index_size = ftell(index_collection);

    if (index_size == 0 || id * INDEX_SIZE > index_size)
        return 1;

    fclose(index_collection);
    return 0;
}

index get_index_master(int id) {
    struct index i{};
    if (is_index_master(id) == 1)
    {
        i.id = -1;
        return i;
    }

    FILE* index_collection = fopen(MASTER_IND, "rb");
    fseek(index_collection, id * INDEX_SIZE, SEEK_SET);
    fread(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}

int insert_m(master* m) {
    index i = get_next_index_master();
    return save_m(m, i);
}

int update_m(master* m) {
    struct index i{};
    if (is_index_master(i.id) == 1)
        return 1;
    return save_m(m, i);
}


index get_next_index_master() {
    struct index i{};
    i.id = last_index_master++;
    i.record_size = MASTER_SIZE;
    i.exists = 0;

    return i;
};

int save_m(master* m, index i) {
    FILE* database = fopen(MASTER_DATA, "w+");

    if (database == nullptr)
        return 1;

    // Insert a data about a user in the .fl file

    m->id = i.id;
    fseek(database, i.id * MASTER_SIZE, SEEK_SET);
    fwrite(m, MASTER_SIZE, 1, database);
    fclose(database);

    // Create an indexer and store it inn the .ind file
    insert_index_m(i);
}

int insert_index_m(index i) {
    FILE* index_collection = fopen(MASTER_IND, "w+");
    if (index_collection == nullptr)
        return 1;

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}

int calc_m() {
    FILE* index_collection = fopen(MASTER_IND, "rb");
    if (index_collection == 0)
        return -1;

    int counter = 0;

    for (int i = 0; i < last_index_master; i++)
    {
        struct index ind{};
        fseek(index_collection, 0 * INDEX_SIZE, SEEK_SET);
        fread(&ind, INDEX_SIZE, 1, index_collection);
        fclose(index_collection);
        if (ind.exists == 0)
            counter++;
    }

    return counter;
}