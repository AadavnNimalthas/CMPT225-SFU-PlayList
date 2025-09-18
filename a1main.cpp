/*
 * Play List main program for CMPT 225 assignment
 * NAME: Aadavn Nimalthas
 * DATE: 09/10/25
 *
 * PART 3 — Worst-case time complexities (briefly justified)
 *
 * PlayList Methods  (your implementation is a singly linked list with a stored count)
 * - Default constructor:        O(1) — initialize head/count.
 * - Destructor:                 O(n) — delete every node.
 * - Copy constructor:           O(n) — deep copy nodes.
 * - Assignment operator:        O(n) — clear old (O(n)) + deep copy (O(n)).
 * - insert(pos, song):          O(n) — traverse up to pos to link in.
 * - remove(pos):                O(n) — traverse up to pos-1 to unlink.
 * - get(pos):                   O(n) — traverse to pos.
 * - swap(i, j):                 O(n) — traverse to both positions then swap data.
 * - size():                     O(1) — returns maintained count.
 *
 * Main Function Commands
 * - Enter a song:               O(n) — dominated by PlayList::insert.
 * - Remove a song:              O(n) — dominated by PlayList::remove.
 * - Swap two songs:             O(n) — dominated by traversals in swap.
 * - Print all the songs:        O(n) — iterate and fetch/print each song.
 */

#include <iostream>
#include <string>
#include <limits>
#include "Song.h"
#include "PlayList.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    PlayList pl;

    // Print the static menu once (matches the sample)
    cout << "Menu:\n"
            "1 - Enter a song in the play list at a given position\n"
            "2 - Remove a song from the play list at a given position\n"
            "3 - Swap two songs in the play list\n"
            "4 - Print all the songs in the play list\n"
            "5 - Quit\n\n";

    while (true) {
        // ---- Prompt for a valid command [1..5] ----
        int cmd;
        while (true) {
            cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
            if (cin >> cmd && cmd >= 1 && cmd <= 5) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (cmd == 1) {
            // -------- INSERT --------
            // Read song fields (use getline for strings)
            string name, artist;
            int length;

            cout << "Song name: ";
            std::getline(cin, name);

            cout << "Artist: ";
            std::getline(cin, artist);

            // Positive integer for length
            while (true) {
                cout << "Length: ";
                if (cin >> length && length > 0) {
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Valid 1-based insertion position is [1..n+1]
            unsigned int n = pl.size();
            int pos1;
            if (n == 0) {
                while (true) {
                    cout << "Position (1): ";
                    if (cin >> pos1 && pos1 == 1) {
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } else {
                while (true) {
                    cout << "Position (1 to " << (n + 1) << "): ";
                    if (cin >> pos1 && pos1 >= 1 && pos1 <= static_cast<int>(n + 1)) {
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            // Convert to 0-based for PlayList
            unsigned int pos0 = static_cast<unsigned int>(pos1 - 1);
            pl.insert(Song(name, artist, length), pos0);

            cout << "You entered " << name << " at position " << pos1 << " in the play list\n\n";
        }
        else if (cmd == 2) {
            // -------- REMOVE --------
            unsigned int n = pl.size();
            if (n == 0) {
                cout << "Play list is empty. Nothing to remove.\n\n";
                continue;
            }

            int pos1;
            while (true) {
                cout << "Position (1 to " << n << "): ";
                if (cin >> pos1 && pos1 >= 1 && pos1 <= static_cast<int>(n)) {
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Keep the name for feedback (use 0-based get)
            Song s = pl.get(static_cast<unsigned int>(pos1 - 1));
            pl.remove(static_cast<unsigned int>(pos1 - 1));
            cout << "You removed " << s.getName() << " from the play list\n\n";
        }
        else if (cmd == 3) {
            // -------- SWAP --------
            unsigned int n = pl.size();
            if (n < 2) {
                cout << "Need at least two songs to swap.\n\n";
                continue;
            }

            int p1, p2;
            while (true) {
                cout << "Swap song at position (1 to " << n << "): ";
                if (cin >> p1 && p1 >= 1 && p1 <= static_cast<int>(n)) {
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            while (true) {
                cout << "with the song at position (1 to " << n << "): ";
                if (cin >> p2 && p2 >= 1 && p2 <= static_cast<int>(n)) {
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            pl.swap(static_cast<unsigned int>(p1 - 1), static_cast<unsigned int>(p2 - 1));
            cout << "You swapped the songs at positions " << p1 << " and " << p2 << "\n\n";
        }
        else if (cmd == 4) {
            // -------- PRINT --------
            unsigned int n = pl.size();
            for (unsigned int i = 0; i < n; ++i) {
                Song s = pl.get(i);
                cout << " " << (i + 1) << " " << s.getName()
                     << " (" << s.getArtist() << ") "
                     << s.getLength() << "s\n";
            }
            cout << "There are " << n << " songs in the play list.\n\n";
        }
        else { // cmd == 5
            cout << "You have chosen to quit the program.\n";
            break;
        }
    }

    return 0;
}
