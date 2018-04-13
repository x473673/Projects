#include <stdio.h>

#include "queue.h"

int main(void)
{
    struct queue *queue;
    queueCreate(&queue, sizeof(int), 5u);

    puts("Adding 10 elements to the queue");
    for (int elem = 0; elem < 10; ++elem) {
        if (queueEnqueue(queue, &elem)) {
            printf("  %d enqueued\n", elem);
        } else {
            printf("  %d could not be enqueued\n", elem);
        }
    }

    putchar('\n');
    puts("Contents of the queue");

    int data;
    while (queueDequeue(queue, &data)) {
        printf("  %d\n", data);
    }

    putchar('\n');
    puts("Cleaning up");
    queueDestroy(queue);

    return 0;
}
