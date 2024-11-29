/*
 * scheduler.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Admin
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h>  // Để sử dụng NULL
#include <stdint.h>  // Để sử dụng các kiểu dữ liệu uint8_t, uint32_t

#define TICK    10

typedef struct Node {
    void (*pTask)();
    int delay;
    int period;
    int ID;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} SCH_task;

void SCH_init(void);
void SCH_addTask(void (*pFunction)(), int DELAY, int PERIOD, int ID);
void SCH_updateTask(void);
void SCH_dispatchTask(void);
void SCH_deleteHead(void);
void SCH_deleteTask(int ID);

#endif
