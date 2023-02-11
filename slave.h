#pragma once

#include "cstdlib"
#include "cstdio"
#include "master.h"

#define SLAVE_DATA "S.fl"
#define SLAVE_IND "S.ind"
#define SLAVE_SIZE sizeof(struct slave)
#define INDEX_SIZE sizeof(struct index)

long last_index_slave = 0;

struct slave {
    int id;
    int m_id;
    char name[50];
};

int get_s(slave* s, int id);
int del_s();
int del_m(int id);
int del_all_s_mid(int m_id);
int update_s(slave* s);
int insert_s(slave* s);
int calc_s();
int ut_s();
int save_s(slave* s, index i);
index get_next_index_slave();
index get_index_slave(int id);
int is_index_slave(int id);
int insert_index_s(index i);
int try_del_s_mid(index i, int id);

int get_s(slave* s, int id) {
    index i = get_index_slave(id);
    if (i.id == -1 || i.exists == 1)
        return 1;

    FILE* database = fopen(SLAVE_DATA, "rb");

    fseek(database, i.id * i.record_size, SEEK_SET);
    fread(s, SLAVE_SIZE, 1, database);
    fclose(database);

    return 0;
}

int insert_s(slave* s) {
    if(is_index_master(s->m_id) == 1) return 2;
    index i = get_next_index_slave();
    return save_s(s, i);
}

int update_s(slave* s) {
    if(is_index_slave(s->id) == 1)
        return 1;
    struct index i;
    struct master m;
    if(get_m(&m, s->m_id) == 1) return 2;
    return save_s(s, i);
}

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

// TODO: Implement simple slave delete based on slave_id
int del_s(int id)
{
    if(is_index_slave(id) == 1) return 1;

    index i = get_index_slave(id);
    if (i.id == -1 || i.exists == 1) return 1;

    i.exists = 1;
    if (insert_index_s(i) == 1) return 1;

    return 0;
}

int del_m(int id) {
    if (is_index_master(id) == 1)
        return 1;

    index i = get_index_master(id);
    if (i.id == -1 || i.exists == 1)
        return 1;

    i.exists = 1;
    if (insert_index_m(i) == 1)
        return 1;

    // TODO: Either Cascade delete: Implement deletion of slaves, which depend on this id. Or: Set null on delete: Slaves referencing this master will be set on null.
    if (del_all_s_mid(id) == 1)
        return 1;
    return 0;
}


int del_all_s_mid(int m_id)
{
    if (is_index_master(m_id) == 1)
        return 1;
    for (int j = 0; j < last_index_slave; j++)
    {
        index i = get_index_slave(j);
        if (i.exists == 1)
            continue;
        try_del_s_mid(i, m_id);
    }
    return 0;
}

int try_del_s_mid(index i, int id)
{
    struct slave s{};
    if (get_s(&s, i.id) == 1)
        return 1;
    if (s.m_id == id)
        del_s(i.id);
    return 0;
}

int insert_index_s(index i) {
    FILE* index_collection = fopen(SLAVE_IND, "w+");
    if (index_collection == nullptr)
        return 1;

    fseek(index_collection, i.id * INDEX_SIZE, SEEK_SET);
    fwrite(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}

index get_next_index_slave() {
    struct index i{};
    i.id = last_index_slave++;
    i.record_size = SLAVE_SIZE;
    i.exists = 0;

    return i;
};


index get_index_slave(int id) {
    struct index i{};
    if (is_index_slave(id) == 1)
    {
        i.id = -1;
        return i;
    }

    FILE* index_collection = fopen(SLAVE_IND, "rb");
    fseek(index_collection, id * INDEX_SIZE, SEEK_SET);
    fread(&i, INDEX_SIZE, 1, index_collection);
    fclose(index_collection);
}

int is_index_slave(int id) {
    FILE* index_collection = fopen(SLAVE_IND, "rb");
    if (index_collection == nullptr)
        return 1;

    fseek(index_collection, 0, SEEK_END);
    long index_size = ftell(index_collection);

    if (index_size == 0 || id * INDEX_SIZE > index_size)
        return 1;

    fclose(index_collection);
    return 0;
}
