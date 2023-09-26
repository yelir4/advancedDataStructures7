// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)
//
// invariant: company has company_name and head and tail ptr
//            head_ptr and tail_ptr may be NULL but if not they point
//            to head and tail of list respectively

#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // company() constructor
    //
    // precondition: company_name is non-empty string
    //
    // postcondition: company object initialized with 'company_name'
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // company() copy constructor
    //
    // postcondition: src copied to company object
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        company_name = src.company_name;
        list_copy(src.get_head(), head_ptr, tail_ptr);
        // use list copy toolkit function to copy
        // old list over to new list
    }

    // = assignment operator
    //
    // postcondition: src copied to company object
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        company_name = src.company_name;
        list_copy(src.get_head(), head_ptr, tail_ptr);
        // use list copy toolkit function to copy
        // old list over to new list

        return *this;
    }
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    // insert()
    //
    // precondition: product_name is non-empty string
    //
    // postcondition: creates, inserts new node (product)
    //                to back of linked list
    //                returns true if successfully inserted,
    //                false if duplicate (not inserted)
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            const std::string newName = product_name;
            const float newPrice = price;
            list_init(head_ptr, tail_ptr, newName, newPrice);
        }
        else {
            const std::string newName = product_name;
            const float newPrice = price;
            list_tail_insert(tail_ptr, newName, newPrice);
        }
        
        return true;
    }

    // erase()
    //
    // postcondition: erases product whose name matches product_name
    //                returns true if product found and deleted,
    //                false otherwise
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        const std::string name = product_name;
        node* cur = list_search(head_ptr, name);

        // product_name found in list
        // copy head information over to 'cur' (because order doesn't matter)
        // list_head_remove
        if(cur != NULL) {
            cur->setName(head_ptr->getName());
            cur->setPrice(head_ptr->getPrice());
            list_head_remove(head_ptr);

            if(head_ptr == NULL) // case: only node in list was erased
                tail_ptr = NULL;

            return true;
        }

        return false;
    }

}
