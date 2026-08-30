#include <stdio.h>

int main(void) {
    //     ↓ Struct Name
    struct MyStruct {
        int a;
        int b;
        float hello;
        char ch;
        int arr[5];
    };
    
    struct MyStruct my_struct = { 1, 2 }; // a = 1, b = 2
    printf("a = %d, b = %d\n", my_struct.a, my_struct.b);

    my_struct.ch = 'c';
    printf("ch = %c\n", my_struct.ch);

    my_struct.hello = 3.14f;
    printf("hello = %f\n", my_struct.hello);

    my_struct.arr[0] = 5;
    my_struct.arr[1] = 2;
    my_struct.arr[2] = 8;
    my_struct.arr[3] = 6;
    my_struct.arr[4] = 1;

    for (int i = 0; i < sizeof(my_struct.arr) / sizeof(my_struct.arr[0]); i++) {
        printf("%d: %d\n", i, my_struct.arr[i]);
    }

    struct MyStruct* my_struct_pointer = &my_struct;
    printf("== pointer ==\n");
    printf("a = %d, b = %d\n", my_struct_pointer->a, my_struct_pointer->b);
    printf("a = %d, b = %d\n", (*my_struct_pointer).a, (*my_struct_pointer).b);

    my_struct_pointer->a = 2;
    printf("Changed a: %d", my_struct_pointer->a);

    return 0;
}