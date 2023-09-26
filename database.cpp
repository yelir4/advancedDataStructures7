// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots

//
// coen 79, lab 7, database.cpp
// 2/24/23
//
#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // database() copy constructor
    //
    // postcondition: src copied to database
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        this->aloc_slots = src.aloc_slots;
        this->used_slots = src.used_slots;
        company_array = new company[aloc_slots];

        // for each company in src
        for(size_type i=0; i<used_slots; ++i) {
            // initialize new company with same name as src's company
            company newComp(src.company_array[i]);
            company_array[i] = newComp;
        }
    }
    
    // = assignment operator
    //
    // postcondition: src copied to database
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        std::cout << "copying elements of database...";

        this->aloc_slots = rhs.aloc_slots;
        this->used_slots = rhs.used_slots;
        company_array = new company[aloc_slots];

        // for each company in src
        for(size_type i=0; i<used_slots; ++i) {
            // initialize new company with same name as src's company
            company newComp(rhs.company_array[i]);
            company_array[i] = newComp;
        }

        return *this;
    }
    
    // ~database() destructor
    //
    // postcondition: dynamic memory returned to heap
    database::~database() {
        delete[] company_array;
    }
    
    // reserve()
    //
    // postcondition: database current capacity changed to
    //                new_capacity (but not less than number of items
    //                              already in the database)
    //
    // insert_company works efficiently (w/o new memory) until new_capacity reached
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company *temp = new company[new_capacity];
        std::copy(company_array, company_array+used_slots, temp);
        delete[] company_array;
        company_array = new company[new_capacity];
        std::copy(temp, temp+used_slots, company_array);

        aloc_slots = new_capacity; // update aloc_slots
    }
    
    // insert_company()
    //
    // precondition: company_name is non-empty string
    //
    // postcondition: new company is added to the list
    bool database::insert_company(const std::string &entry) {
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        // need to reallocate memory
        if(used_slots == aloc_slots)
            reserve(used_slots+1);
        
        // create new company and increment used_slots
        company newComp(entry);
        company_array[used_slots++] = newComp;

        return true;
    }
    
    // insert_item()
    //
    // precondition: company_name, product_name are non-empty strings
    //
    // postcondition: new product added to list pertaining to 'company'
    //                function also checks that company is in the database
    //                returns false if the company already in database, true otherwise
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        // serarch for company in database
        size_t company_index = search_company(company);
        if(company_index != COMPANY_NOT_FOUND) {
            // company found
            company_array[company_index].insert(product_name, price);
            return false;
        } else {
            // make new company and insert item, return true
            insert_company(company); // increments used_slots
            company_array[used_slots-1].insert(product_name, price);
            return true;
        }
    }
    
    // erase_company()
    //
    // precondition: company_name is non-empty string
    //
    // postcondition: company and its products removed from database
    //                all elements to the right of company shifted left
    //
    // return false if company not found in list
    bool database::erase_company(const std::string &company) {

        // search for company in database
        size_type company_index = search_company(company);
        if(company_index != COMPANY_NOT_FOUND) {
            // company found
            delete (company_array[company_index].get_head());

            // shift companies over
            for(size_t i=company_index; i<used_slots; ++i) {
                company_array[i] = company_array[i+1];
            }
            return true;
        } else {
            return false;
        }
    }
    
    // erase_item()
    //
    // precondition: company_name, product_name are non-empty strings
    //
    // postcondition: product is erased from company in database
    //
    // returns false if company or item was not found
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        // search for company in database
        size_type company_index = search_company(cName);
        if(company_index != COMPANY_NOT_FOUND) {
            // company found, return true if pName can be erased from product list
            return company_array[company_index].erase(pName);
        } else {
            // company not found in database
            return false;
        }
    }
    
    
    // search_company()
    //
    // precondition: company is non-empty string
    //
    // postcondition: searches database for 'company'
    // returns position if found, otherwise returns COMPANY_NOT_FOUND (-1)
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // iterate through database to look for company
        for(size_t i=0; i<used_slots; ++i)
            if(company_array[i].get_name() == company)
                return i;
        
        // company not found in database
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
