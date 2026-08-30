// =====
// Please Read:
// This code is using cjson/cJSON.h
// You must add option to '-lcjson'
// 
// Command:
//   ./run.bat "JSON (CJSON)" "-lcjson"
// =====

#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main(void) {
    char json[40] = "{ \"a\": \"bcdef\", \"b\": 12345, \"c\": true }"; // json string
    cJSON *parse = cJSON_Parse(json); // parse
    if (parse == NULL) {
        printf("JSON Parse Failed\n");
        return 1;
    }

    cJSON *a = cJSON_GetObjectItem(parse, "a");
    cJSON *b = cJSON_GetObjectItem(parse, "b");
    cJSON *c = cJSON_GetObjectItem(parse, "c");

    printf("Original: %s\n", json);
    printf("Parsed a: %s\n", a->valuestring);
    printf("Parsed b: %d\n", b->valueint);
    printf("Parsed c: %s\n", cJSON_IsTrue(c) ? "true" : "false");

    cJSON_Delete(parse);

    cJSON *obj = cJSON_CreateObject(); // Create a JSON Object

    cJSON_AddStringToObject(obj, "hello", "hi");
    cJSON_AddNumberToObject(obj, "a", 1);
    cJSON_AddBoolToObject(obj, "hehe", 0);

    char* json2 = cJSON_Print(obj); // to stringify
    printf("Generated JSON:\n%s\n", json2);
    free(json2);
    return 0;
}