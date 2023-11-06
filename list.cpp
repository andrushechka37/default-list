#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "string.h"


void create_new_grapth(void) {
    char command1[1000] = "dot -Tpng /Users/anzhiday/Documents/default_list/grath.dot  -o /Users/anzhiday/Documents/default_list/grapth/grath";
    char command2[] = ".png";
    strcat(command1, count_gr);
    strcat(command1, command2);
    system(command1);
    snprintf(count_gr, 2,  "%d", (1 + atoi(count_gr)));
}


list_elem * list_insert_after(list_elem * elem, int value, list_struct * list) {


    //list->data[list->data[position].next].prev = cur;      // prev of the next elem is current
    list_elem * insert_elem = (list_elem *) calloc(1, sizeof(list_elem));
    insert_elem->value = value;

    insert_elem->next = elem->next;
    insert_elem->prev = elem;
    elem->next->prev = insert_elem;


    elem->next = insert_elem;


    list->size++;

    return insert_elem;
}

int list_delete(list_elem * elem, list_struct * list) {
    elem->value = 0;
    (elem->next)->prev = elem->prev;
    (elem->prev)->next = elem->next;
    free(elem);
    list->size--;
    return 0;
}

int list_ctor(list_struct * list) {
    list->zero_elem = (list_elem *) calloc(1, sizeof(list_elem));
    list->zero_elem->next = list->zero_elem;
    list->zero_elem->prev = list->zero_elem;
    list->size = 0;
    return 0;
}


int main(void) {
    list_struct list = {};
    list_ctor(&list);
    list_elem * k = list_insert_after(list.zero_elem, 5, &list);
    list_insert_after(k, 25, &list);
    grapth_dump(&list);

}






void grapth_dump(list_struct * list) {
    FILE * pfile = fopen("grath.dot", "wb");
    fprintf(pfile, "digraph structs {\n");
    fprintf(pfile, "\trankdir=LR;\n");
    fprintf(pfile, "\tgraph [bgcolor=\"#31353b\"]\n");
    fprintf(pfile, "\tnode[color=\"black\",fontsize=14];\n");
    //fprintf(pfile, "\tedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");

    int value = list->zero_elem->value;
    list_elem * next = list->zero_elem->next;
    list_elem * prev = list->zero_elem->prev;
    list_elem * pointer_elem = list->zero_elem;

    
    for (int i = 0; i <= list->size; i++) {
        
        fprintf(pfile, "\t%d [shape=Mrecord,style=filled, fillcolor=\"#7293ba\", label=\" ip: %p ", pointer_elem, pointer_elem);
        fprintf(pfile, "| data: %d", value);
        fprintf(pfile, "| next: %p", next);
        fprintf(pfile, "| prev: %p\" ];\n", prev);
        if (pointer_elem->next != NULL) {
            value = pointer_elem->next->value;
            next = pointer_elem->next->next;
            prev = pointer_elem->next->prev;
            pointer_elem = pointer_elem->next;
        }
    }
    fprintf(pfile, "\n\t");

    pointer_elem = list->zero_elem;
    
    for (int i = 0; i <= list->size - 1; i++) {
        fprintf(pfile, "%d->",pointer_elem);
        if (pointer_elem->next != NULL) {
            pointer_elem = pointer_elem->next;
        }
    }

    fprintf(pfile, "%d[weight = 100, color = \"invis\"];\n", pointer_elem);
    pointer_elem = list->zero_elem;
    next = list->zero_elem->next;

    for(int i = 0; i <= list->size; i++) {
        if (next == 0) {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\", constraint=false];\n", pointer_elem, list->zero_elem);
        } else {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\", constraint=false];\n", pointer_elem, next);
        }
        if (pointer_elem->next != NULL) { 
            next = pointer_elem->next->next;
            pointer_elem = pointer_elem->next;
        }
    }
    pointer_elem = list->zero_elem;
    prev = list->zero_elem->prev;

    for(int i = 0; i <= list->size; i++) {
        if (prev == 0) {
            fprintf(pfile, "\t%d -> %d[color = \"#ff0a0a\", constraint=false];\n", pointer_elem, list->zero_elem);
        } else {
            fprintf(pfile, "\t%d -> %d[color = \"#ff0a0a\", constraint=false];\n", pointer_elem, prev);
        }
        
        if (pointer_elem->next != NULL) {
            prev = pointer_elem->next->prev;
            pointer_elem = pointer_elem->next;
        }
    }


    fprintf(pfile, "\th [shape=tripleoctagon,label=\"HEAD\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled  ];\n");
    fprintf(pfile, "\tt [shape=tripleoctagon,label=\"TALE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\th->t[weight = 100, color = \"invis\"];\n");
    fprintf(pfile, "\th->%d[color = \"orange\", constraint=false];\n", list->zero_elem->next);
    fprintf(pfile, "\tt->%d[color = \"orange\", constraint=false];\n", list->zero_elem->prev);

    fprintf(pfile, "\n}");
    fclose(pfile);
    create_new_grapth(); 
}