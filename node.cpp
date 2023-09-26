// invariant: node always has a name, price, and link to next product
//            link may be NULL
//
// coen 79, lab 7, node.cpp
// 2/24/23
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    node* node::getLink() {
        return link;
    }
    
    const node* node::getLink() const {
        return link;
    }
    
    std::string node::getName() const {
        return name;
    }
    
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    // list_tail_insert()
    //
    // precondition: tail_ptr is tail pointer of non-empty linked list,
    //               newName is non empty string
    //
    // postcondition: adds node to end of linked list
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        tail->setLink(new node(newName, newPrice)); // insert new node to tail
        tail = tail->getLink();
    }
    
    // list_clear()
    //
    // precondition: head is head pointer of linked list
    //
    // postcondition: all list nodes returned to heap, head is now NULL
    void list_clear(node*& head) {
        if(head == NULL)
            return;

        if(head->getLink() != NULL) { // recursively clear the list
            node *next = head->getLink();
            list_clear(next);
        }

        head->setLink(NULL);
        delete head;
        head = NULL;
    }
    
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = NULL;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            } else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    // list_head_remove()
    //
    // precondition: head is head pointer of linked list with at least one node
    //
    // postcondition: head removed and returned to heap, head is head pointer
    //                of new, shorter linked list
    void list_head_remove(node*& head) {
        node *cursor = head;
        head = head->getLink(); // if head is only node, head = NULL
        delete cursor;
        cursor = NULL;
    }
    
    
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
