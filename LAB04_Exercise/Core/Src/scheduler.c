#include "scheduler.h"
#include <stdlib.h>  // Để sử dụng malloc và free
#include <stdio.h>   // Tùy chọn: Để sử dụng printf (nếu cần debug)

SCH_task *mainSCH = NULL;  // Scheduler chính

void SCH_init() {
    mainSCH = (SCH_task *)malloc(sizeof(SCH_task));
    mainSCH->head = NULL;
    mainSCH->tail = NULL;
    mainSCH->size = 0;
}

void SCH_deleteHead() {
    if (mainSCH->size == 0) return;

    Node *current = mainSCH->head;
    mainSCH->head = current->next;

    if (mainSCH->head == NULL) {
        mainSCH->tail = NULL;
    }

    free(current);
    mainSCH->size--;
}

void SCH_deleteTask(int ID) {
    if (mainSCH->size == 0) return;

    Node *pFront = NULL;
    Node *pEnd = mainSCH->head;

    while (pEnd != NULL) {
        if (pEnd->ID == ID) {
            if (pFront == NULL) {
                SCH_deleteHead();
            } else {
                pFront->next = pEnd->next;
                if (pEnd == mainSCH->tail) {
                    mainSCH->tail = pFront;
                }
                free(pEnd);
                mainSCH->size--;
            }
            return;
        }
        pFront = pEnd;
        pEnd = pEnd->next;
    }
}

void SCH_addTask(void (*pFunction)(), int DELAY, int PERIOD, int ID) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->pTask = pFunction;
    node->delay = DELAY;
    node->period = PERIOD;
    node->ID = ID;
    node->next = NULL;

    Node *pFront = NULL;
    Node *pEnd = mainSCH->head;
    int remainingDelay = DELAY;

    while (pEnd != NULL && remainingDelay >= pEnd->delay) {
        remainingDelay -= pEnd->delay;
        pFront = pEnd;
        pEnd = pEnd->next;
    }

    node->delay = remainingDelay;

    if (pEnd != NULL) {
        pEnd->delay -= remainingDelay;
    }

    if (pFront == NULL) {
        node->next = mainSCH->head;
        mainSCH->head = node;
    } else {
        pFront->next = node;
        node->next = pEnd;
    }

    if (node->next == NULL) {
        mainSCH->tail = node;
    }

    mainSCH->size++;
}

void SCH_updateTask() {
    static unsigned int time_skip = 0;

    if (mainSCH->head != NULL) {
        time_skip++;
        Node *current = mainSCH->head;

        if (current->delay > time_skip) {
            current->delay -= time_skip;
        } else {
            time_skip -= current->delay;
            current->delay = 0;
        }
    }
}

void SCH_dispatchTask() {
    while (mainSCH->head != NULL && mainSCH->head->delay == 0) {
        Node *current = mainSCH->head;

        current->pTask();

        if (current->period > 0) {
            SCH_addTask(current->pTask, current->period, current->period, current->ID);
        }

        SCH_deleteHead();
    }
}
