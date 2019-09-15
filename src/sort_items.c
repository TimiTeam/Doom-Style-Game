#include "main_head.h"

static float		len_between_points(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

t_item *getTail(t_item *cur) 
{ 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 
  
// Partitions the list taking the last element as the pivot 
t_item *partition(t_item *head, t_item *end, 
                       t_item **newHead, t_item **newEnd, t_player *player) 
{ 
    t_item *pivot = end; 
    t_item *prev = NULL, *cur = head, *tail = pivot;
    // During partition, both the head and end of the list might change 
    // which is updated in the newHead and newEnd variables 
    while (cur != pivot) 
    {
        if ((cur->dist_to_player = len_between_points(player->pos, cur->pos)) > (pivot->dist_to_player = len_between_points(player->pos, pivot->pos)))
        { 
            // First node that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;   
            cur = cur->next; 
        } 
        else // If cur node is greater than pivot 
        { 
            // Move cur node to next of tail, and change tail 
            if (prev) 
                prev->next = cur->next; 
            t_item *tmp = cur->next; 
            cur->next = NULL; 
            tail->next = cur; 
            tail = cur; 
            cur = tmp; 
        } 
    } 
  
    // If the pivot data is the smallest element in the current list, 
    // pivot becomes the head 
    if ((*newHead) == NULL) 
        (*newHead) = pivot; 
  
    // Update newEnd to the current last node 
    (*newEnd) = tail; 
  
    // Return the pivot node 
    return pivot; 
} 
  
  
//here the sorting happens exclusive of the end node 
t_item *quickSortRecur(t_item *head, t_item *end, t_player *player) 
{ 
    // base condition 
    if (!head || head == end) 
        return head; 
  
    t_item *newHead = NULL, *newEnd = NULL; 
  
    // Partition the list, newHead and newEnd will be updated 
    // by the partition function 
    t_item *pivot = partition(head, end, &newHead, &newEnd, player); 
  
    // If pivot is the smallest element - no need to recur for 
    // the left part. 
    if (newHead != pivot) 
    { 
        // Set the node before the pivot node as NULL 
        t_item *tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = NULL; 
  
        // Recur for the list before pivot 
        newHead = quickSortRecur(newHead, tmp, player); 
  
        // Change next of last node of the left half to pivot 
        tmp = getTail(newHead); 
        tmp->next =  pivot; 
    } 
  
    // Recur for the list after the pivot element 
    pivot->next = quickSortRecur(pivot->next, newEnd, player); 
	head->dist_to_player = len_between_points(head->pos, player->pos);
    return newHead; 
} 
  
// The main function for quick sort. This is a wrapper over recursive 
// function quickSortRecur() 
void  quickSort(t_item **headRef, t_player *player) 
{
	if (!headRef || !*headRef)
		return;
	(*headRef)->dist_to_player = len_between_points((*headRef)->pos, player->pos);
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef), player); 
    return ; 
}