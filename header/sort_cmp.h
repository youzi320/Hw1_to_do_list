#ifndef SORT_CMP_H
#define SORT_CMP_H

#include "task.h"

using namespace std;


bool cmp_completed_date_name(const task* c1, const task* c2);

bool cmp_date(const task* c1, const task* c2);

bool cmp_name(const task* c1, const task* c2);

bool cmp_category(const task* c1, const task* c2);

#endif