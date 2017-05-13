//
// Created by Ming Hu on 8/5/17.
//

#include "course_list.h"

CourseList * create_course_list()
{
    CourseList * list;

    if((list = malloc(sizeof(CourseList))) == NULL)
    {
        printf("> Addressbook List memory allocation failed!\n");
        return NULL;
    }

    list->length = 0;
    list->current_course = NULL;
    list->first_course = NULL;
    list->last_course = NULL;

    return list;
}

void delete_course_list(CourseList * list)
{
    /** Free up each node */
    CourseNode * current_node;
    current_node = list->first_course;

    while(current_node != NULL)
    {
        delete_course_node(current_node);
        current_node = current_node->next_node;
    }


    /** Wipe up itself */
    free(list);

}

CourseNode * create_course_node(int id, Course * course)
{
    CourseNode * node;
    if((node = malloc(sizeof(*node))) == NULL)
    {
        printf("Memory allocation for Addressbook node failed!\n");
        return NULL;
    }

    /** Assign some values to it */
    node->course = course;
    node->id = id;
    node->next_node = NULL;
    node->previous_node = NULL;

    return node;
}

void delete_course_node(CourseNode * node)
{
    /** If this node's array is not null, wipe it up too. */
    if(node->course != NULL)
    {
        delete_course(node->course);
    }

    /** Then wipe itself */
    free(node);
}

bool insert_node(CourseList * list, CourseNode * node)
{
    CourseNode * previous_current_next;
    CourseNode * previous_current;

    /** As it said above, if a node with an existed ID, then return false */
    if (find_by_node_id(list, node->id) == NULL)
    {
        /** Get the "previous current" node */
        previous_current = list->current_course;

        /** Finalize previous assigns & merges */
        if(previous_current != NULL)
        {
            previous_current_next = previous_current->next_node;

            previous_current->next_node = node;

            if(previous_current_next != NULL)
            {
                previous_current_next->previous_node = node;
            }
        }

        /** Set the amount, plus one to append */
        list->length++;

        /** All done, set **real** current one to the new node */
        node->previous_node = previous_current;
        list->current_course = node;


        return true;
    }
    else
    {
        return false;
    }

}

bool remove_current_node(CourseList * list)
{
    /**
     * Basically there are four situations:
     *
     * 1. Current node is between two non-null node
     * 2. Current node does not have its next node (tail node)
     * 3. Current node does not have its previous node (head node)
     * 4. Current node does not have both next node and previous node, i.e. it is alone, single, no friend, no family etc...
     *
     * By the way, is this one of the bonus mark lol?? Anyway I've done it and it is proved to work very smoothly. :)
     *
     * */
    CourseNode * current_node;

    if (list->current_course != NULL && list->length != 0)
    {
        if(list->current_course->next_node != NULL && list->current_course->previous_node != NULL)
        {
            /** Situation #1 - Current node is between two non-null node */
            /** Break its connection, then connect the neighbour nodes together */
            current_node = list->current_course;
            current_node->previous_node->next_node = current_node->next_node;
            current_node->next_node->previous_node = current_node->previous_node;
            list->current_course = current_node->next_node;
            delete_course_node(current_node);
        }
        else if(list->current_course->next_node == NULL && list->current_course->previous_node != NULL)
        {
            /** Situation #2 - Current node does not have its next node (tail node) */
            /** Break its connection, then connect the previous node's next node to NULL */
            current_node = list->current_course;
            current_node->previous_node->next_node = NULL;
            list->current_course = current_node->previous_node;
            delete_course_node(current_node);
        }
        else if(list->current_course->next_node != NULL && list->current_course->previous_node == NULL)
        {
            /** Situation #3 - Current node does not have its previous node (head node) */
            /** Break its connection, then connect the next node's previous node to NULL */
            current_node = list->current_course;
            current_node->next_node->previous_node = NULL;
            list->current_course = current_node->next_node;
            delete_course_node(current_node);
        }
        else
        {
            /** Situation #4 - Current node does not have both next node and previous node */
            delete_course_node(list->current_course);
        }

        /** Shrink the size of the list */
        list->length--;
        return true;
    }
    else
    {
        return false;
    }

}

bool forward(CourseList * list, int forward)
{
    /** Assign the current node to default current node */
    CourseNode * current_node = list->current_course;

    /** Assign a step index */
    int step_index = 0;

    /** Loop the index to the desired value */
    while (step_index < forward)
    {
        /** Judge if it can be forward */
        if (current_node->next_node != NULL)
        {
            /** Forward it and return true */
            current_node = current_node->next_node;
            step_index++;
        }
        else
        {
            return false;
        }
    }

    return true;

}

bool backward(CourseList * list, int backward)
{

    /** Assign the current node to default current node */
    CourseNode * current_node = list->current_course;

    /** Assign a step index */
    int step_index = 0;

    /** Loop the index to the desired value */
    while (step_index < backward)
    {
        /** Judge if it can be forward */
        if (current_node->previous_node != NULL)
        {
            /** Forward it and return true */
            current_node = current_node->previous_node;
            step_index++;
        }
        else
        {
            return false;
        }
    }

    return true;
}

CourseNode * find_by_node_id(CourseList * list, int node_id)
{
    /** Declare a node pointer and set to head position */
    CourseNode * node_query = list->first_course;

    /** If the node is null (even not initialized), return NULL result and stop the process */
    if(node_query == NULL)
    {
        return NULL;
    }

    /** If it's lucky enough and the this list's head node is what it wants, simply return it. */
    if (node_query->id == node_id)
    {
        return node_query;
    }

    /** If it's not lucky, do some dirty works instead! */
    while (node_query->next_node != NULL)
    {
        /** If it's lucky enough and the this next node is what it wants, simply return it. */
        if (node_query->next_node->id == node_id)
        {
            /** Set the next node to the node it needs and return */
            node_query = node_query->next_node;
            return node_query;
        }
        else
        {
            /** If it's STILL NOT lucky, continue to search,
             * ...just like a male software engineering student keeps seeking for a girlfriend! */
            node_query = node_query->next_node;
        }
    }

    /** If there is actually NOTHING, then return a NULL to finish the process. */
    return NULL;
}

