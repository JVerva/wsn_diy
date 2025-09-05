#include <stdio.h>
#include <string.h>
#include "contiki.h"
#include "lib/memb.h"
#include "os/storage/cfs/cfs.h"

/*---------------------------------------------------------------------------*/
PROCESS(memory_operations_process, "memory_operations process");
AUTOSTART_PROCESSES(&memory_operations_process);
/*---------------------------------------------------------------------------*/

typedef struct int_2 {
    int a;
    int b;
}int_2;

MEMB(int_2_memb, int_2, 3);

static int_2 * add_int2(int a, int b) {
    int_2 *new = memb_alloc(&int_2_memb);
    if(new != NULL) {
        new->a = a;
        new->b = b;
    }
    return new;
}

static void remove_int2(int_2 *int2) {
    memb_free(&int_2_memb, int2);
}

static void print_int2_memb_contents(void) {
    for(int i = 0; i < int_2_memb.num; i++) {
        if(int_2_memb.used[i]) {
            int_2 *ptr = (int_2 *)(int_2_memb.mem + i * int_2_memb.size);
            printf("Block %d: %d, %d\n", i, ptr->a, ptr->b);
        } else {
            printf("Block %d: FREE\n", i);
        }
    }
}

PROCESS_THREAD(memory_operations_process, ev, data) {

    PROCESS_BEGIN();

    //stack operations
    //initialize memory pool (size 3)
    memb_init(&int_2_memb);
    //add 3 elements
    printf("Adding 3 elements to memory pool:\n");
    int_2 *e1 = add_int2(1, 2);
    int_2 *e2 = add_int2(3, 4);
    int_2 *e3 = add_int2(5, 6);
    //print contents of memory pool
    print_int2_memb_contents();
    //remove 1 element
    printf("Removing 1 element from memory pool:\n");
    remove_int2(e2);
    //print contents of memory pool
    print_int2_memb_contents();
    printf("Removing remaining elements from memory pool\n");
    //clean up remaining elements
    remove_int2(e1);
    remove_int2(e3);
    //print contents of memory pool
    print_int2_memb_contents();

    //file system operations
    //create file, read and write buffers
    printf("Creating file my_first_file.txt\n");
    int fd = cfs_open("my_first_file.txt", CFS_WRITE + CFS_READ);
    char buf[50];
    char text[20] = "Hello, World!\n";
    //write to file
    printf("Writing to file\n");
    cfs_write(fd, text, strlen(text));
    //print file contents
    cfs_seek(fd, 0, CFS_SEEK_SET);
    cfs_read(fd, buf, sizeof(text));
    printf("File contents: %s\n", buf);
    //append to file
    printf("Appending to file\n");
    memset(buf, 0, sizeof(buf));
    strcpy(text,"whoops. somethings wrong\n");
    cfs_write(fd, text, strlen(text));
    //print file contents
    cfs_seek(fd, 0, CFS_SEEK_SET);
    cfs_read(fd, buf, sizeof(buf)-1);
    printf("File contents: %s\n", buf);
    //close file
    cfs_close(fd);

    PROCESS_END();
}