/*
 * PlayList method implementations for CMPT 225 assignment
 * NAME: Aadavn Nimalthas
 * DATE: 09/10/25
 */
#include "PlayList.h"
#include <stdexcept>
#include <utility>

using std::out_of_range;

// PlayList method implementations go here
// Constructor
// POST: head is set to nullptr and count = 0
PlayList::PlayList() : head(nullptr), count(0) {}

// Copy constructor
// PARAM: pl - PlayList to be copied
// POST: new PlayList is a deep copy of pl
PlayList::PlayList(const PlayList& pl) : head(nullptr), count(0)
{
    if (pl.head == nullptr) {
        head = nullptr;
        count = 0;
    } else {
        // Copy first node
        head = new PlayListNode(pl.head->song, nullptr);
        PlayListNode* curNew = head;
        PlayListNode* curOld = pl.head->next;

        // Copy rest
        while (curOld != nullptr) {
            curNew->next = new PlayListNode(curOld->song, nullptr);
            curNew = curNew->next;
            curOld = curOld->next;
        }
        count = pl.count;
    }
}

// Destructor
// POST: dynamic memory deallocated
PlayList::~PlayList()
{
    while (head != nullptr) {
        PlayListNode* tmp = head->next;
        delete head;
        head = tmp;
    }
    count = 0;
}

// Overloaded assignment operator
// POST: calling object is a deep copy of pl
PlayList& PlayList::operator=(const PlayList& pl)
{
    if (this == &pl) return *this;

    // Clear current
    while (head != nullptr) {
        PlayListNode* tmp = head->next;
        delete head;
        head = tmp;
    }
    count = 0;

    // Copy
    if (pl.head != nullptr) {
        head = new PlayListNode(pl.head->song, nullptr);
        PlayListNode* curNew = head;
        PlayListNode* curOld = pl.head->next;

        while (curOld != nullptr) {
            curNew->next = new PlayListNode(curOld->song, nullptr);
            curNew = curNew->next;
            curOld = curOld->next;
        }
        count = pl.count;
    }

    return *this;
}

// Mutators
// PRE: 0 <= pos <= length of list
// POST: sng inserted at position pos
void PlayList::insert(Song sng, unsigned int pos)
{
    if (pos > static_cast<unsigned int>(count)) {
        throw out_of_range("insert: invalid position");
    }

    if (pos == 0) {
        head = new PlayListNode(sng, head);
    } else {
        PlayListNode* prev = head;
        for (unsigned int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }
        prev->next = new PlayListNode(sng, prev->next);
    }
    count++;
}

// PRE: 0 <= pos <= length-1
// POST: song at pos is removed and returned
Song PlayList::remove(unsigned int pos)
{
    if (pos >= static_cast<unsigned int>(count)) {
        throw out_of_range("remove: invalid position");
    }

    PlayListNode* toDelete = nullptr;

    if (pos == 0) {
        toDelete = head;
        head = head->next;
    } else {
        PlayListNode* prev = head;
        for (unsigned int i = 0; i < pos - 1; ++i) {
            prev = prev->next;
        }
        toDelete = prev->next;
        prev->next = toDelete->next;
    }

    // Copy-construct the return value from the node we're deleting (✅ no default ctor needed)
    Song removed = toDelete->song;

    delete toDelete;
    --count;
    return removed;
}


// PRE: 0 <= pos1, pos2 <= length-1
// POST: songs at pos1 and pos2 are swapped
void PlayList::swap(unsigned int pos1, unsigned int pos2)
{
    if (pos1 >= static_cast<unsigned int>(count) ||
        pos2 >= static_cast<unsigned int>(count)) {
        throw out_of_range("swap: invalid position");
    }

    if (pos1 == pos2) return;

    PlayListNode* n1 = head;
    for (unsigned int i = 0; i < pos1; i++) {
        n1 = n1->next;
    }

    PlayListNode* n2 = head;
    for (unsigned int i = 0; i < pos2; i++) {
        n2 = n2->next;
    }

    std::swap(n1->song, n2->song);
}

// Accessors
// PRE: 0 <= pos <= length-1
// POST: returns song at pos
Song PlayList::get(unsigned int pos) const
{
    if (pos >= static_cast<unsigned int>(count)) {
        throw out_of_range("get: invalid position");
    }

    PlayListNode* cur = head;
    for (unsigned int i = 0; i < pos; i++) {
        cur = cur->next;
    }
    return cur->song;
}

// POST: returns number of songs in list
unsigned int PlayList::size() const
{
    return static_cast<unsigned int>(count);
}