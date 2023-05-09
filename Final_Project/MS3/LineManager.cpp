// ***********************************************************
// File    LineManager.cpp
// Version 1.0
// Date    March 29, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// LineManager Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

    // construct the assembly line
    LineManager::LineManager(const string& file, vector<Workstation*>& stations) {
        fstream fs(file);
        Utilities ut;
        string str, item, nextItem;

        if (fs) {
            // temp Workstation pointers
            Workstation* curStation{};
            Workstation* nextStation{};
            Workstation* firstStation{};

            // read from 'file' - in this case AssemblyLine.txt
            while (getline(fs, str)) {
                bool more = true;
                size_t pos{};

                item = ut.extractToken(str, pos, more);

                // search stations to find the correct station that matches 'item'
                curStation = *find_if(stations.begin(), stations.end(), [&](Workstation* s) {
                    return s->getItemName() == item;
                });

                // generate the activeLine
                m_activeLine.push_back(curStation);

                // as long as there is 'more' to read from 'file'
                // set the next station pointer
                if (more != false) {
                    nextItem = ut.extractToken(str, pos, more);
                    nextStation = *find_if(stations.begin(), stations.end(), [&](Workstation* s) {
                        return s->getItemName() == nextItem;
                    });

                    // set the next station pointer for the 'curStation'
                    curStation->setNextStation(nextStation);
                }
            }

            // find first station pointer and set the member variable 'm_firstStation'
            for_each(stations.begin(), stations.end(), [&](Workstation* s) {
                firstStation = *find_if(stations.begin(), stations.end(), [&](Workstation* s) {
                return s->getNextStation() == firstStation;
            });
            });
            m_firstStation = firstStation;

        } else {
            throw ("ERROR: unable to open file");
        }

        fs.close();
        m_cntCustomerOrder = g_pending.size();
    }

    // sort orders based on their location in the line
    void LineManager::reorderStations() {
        Workstation* stn = m_firstStation;
        vector<Workstation*> orderedLine;
        while (stn) {
            orderedLine.push_back(stn);
            stn = stn->getNextStation();
        }
        m_activeLine = orderedLine;
    }

    // run orders through the line return true when all orders 
    // have been processed whether completed or not
    bool LineManager::run(ostream& os) {
        bool res{};

        // print and keep track of itterations
        static size_t count = 0;
        os << "Line Manager Iteration: " << ++count << endl;

        // as long as orders are still pending move one onto the line
        if (!g_pending.empty()) {
            *m_activeLine.front() += move(g_pending.front());
            g_pending.pop_front();
        }

        // attempt to fill then move an order along the line
        for (auto& i : m_activeLine)
            i->fill(os);
        for (auto& i : m_activeLine)
            i->attemptToMoveOrder();

        // finished processing orders if the size of the processed 
        // orders is equal to the number of customer orders placed
        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) res = true;

        return res;
    }

    void LineManager::display(ostream& os) const {
        for (auto& i : m_activeLine)
            i->display(os);
    }
}