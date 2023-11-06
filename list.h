

inline char count_gr[] = "1";

struct list_elem {
    int value;
    list_elem * next;
    list_elem * prev;
};

struct list_struct {
    list_elem * zero_elem;
    int size;
};



void create_new_grapth(void);

int list_delete(list_elem * elem, list_struct * list);

void grapth_dump(list_struct * list);

int list_elem_add(list_struct * list, list_elem * elem, int value);
list_elem * list_insert_after(list_elem * elem, int value, list_struct * list);

