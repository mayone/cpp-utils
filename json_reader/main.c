#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include "cjson/cJSON.h"

#define USER_JSON "users.json"
#define OUTPUT_JSON "output.json"

#define WRITE_JSON_FILE(fpath, x, y...) \
    do                                  \
    {                                   \
        FILE *fp = NULL;                \
        fp = fopen(fpath, "w+");        \
        flock(fileno(fp), LOCK_EX);     \
        fprintf(fp, x, ##y);            \
        fflush(fp);                     \
        flock(fileno(fp), LOCK_UN);     \
        fclose(fp);                     \
    } while (0)

cJSON *readJSON(char *fpath);

cJSON *createUsers();

cJSON *createUser(
    char *name, int age,
    double height, double weight,
    char *langList[], int numLangs);

int main(int argc, char const *argv[])
{
    cJSON *jsonConfig;
    cJSON *users;
    cJSON *user;
    cJSON *newUsers;

    jsonConfig = readJSON(USER_JSON);
    if (jsonConfig == NULL)
    {
        printf("%s():%d    Failed to read JSON %s\n", __func__, __LINE__, USER_JSON);
        return 0;
    }
    printf("Original users\n");
    printf("%s\n", cJSON_Print(jsonConfig));

    /* Add users */
    users = cJSON_GetObjectItemCaseSensitive(jsonConfig, "users");
    newUsers = createUsers();
    cJSON_ArrayForEach(user, newUsers)
    {
        cJSON_AddItemReferenceToArray(users, user);
    }

    printf("Updated users\n");
    printf("%s\n", cJSON_Print(jsonConfig));

    WRITE_JSON_FILE(OUTPUT_JSON, "%s", cJSON_Print(jsonConfig));

    cJSON_Delete(jsonConfig);

    return 0;
}

cJSON *readJSON(char *fpath)
{
    char *buffer = NULL;
    long length;
    FILE *fp = NULL;

    cJSON *jsonConfig;

    fp = fopen(fpath, "r");
    if (fp == NULL)
    {
        printf("%s():%d    Failed to open %s\n", __func__, __LINE__, fpath);
        return NULL;
    }

    /* Prepare buffer */
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = malloc(length + 1);

    fread(buffer, 1, length, fp);
    buffer[length] = '\0';
    fclose(fp);
    if (buffer == NULL)
    {
        printf("%s():%d    Failed to read to buffer\n", __func__, __LINE__);
        return NULL;
    }

    jsonConfig = cJSON_Parse(buffer);

    return jsonConfig;
}

cJSON *createUsers()
{
    cJSON *users = cJSON_CreateArray();
    cJSON *user;

    char *langList1[2] = {"English", "Chinese"};
    char *langList2[5] = {"Korean", "English", "Chinese", "Cantonese", "Japanese"};
    user = createUser(
        "IV", 27,
        163.3, 52.5,
        langList1, sizeof(langList1) / sizeof(char *));
    cJSON_AddItemToArray(users, user);

    user = createUser(
        "IU", 28,
        161.8, 0,
        langList2, sizeof(langList2) / sizeof(char *));
    cJSON_AddItemToArray(users, user);

    return users;
}

cJSON *createUser(
    char *name, int age,
    double height, double weight,
    char *langList[], int numLang)
{
    int i;
    cJSON *user;
    cJSON *list;
    cJSON *item;

    user = cJSON_CreateObject();
    item = cJSON_CreateString(name);
    if (item)
    {
        cJSON_AddItemToObject(user, "name", item);
    }

    item = cJSON_CreateNumber(age);
    if (item)
    {
        cJSON_AddItemToObject(user, "age", item);
    }

    item = cJSON_CreateNumber(height);
    if (item)
    {
        cJSON_AddItemToObject(user, "height", item);
    }

    if (weight == 0)
    {
        item = cJSON_CreateNull();
    }
    else
    {
        item = cJSON_CreateNumber(weight);
    }
    if (item)
    {
        cJSON_AddItemToObject(user, "weight", item);
    }

    list = cJSON_CreateArray();
    for (i = 0; i < numLang; i++)
    {
        item = cJSON_CreateString(langList[i]);
        cJSON_AddItemToArray(list, item);
    }
    if (list)
    {
        cJSON_AddItemToObject(user, "languages", list);
    }

    return user;
}