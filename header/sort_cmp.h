#ifndef SORT_CMP_H
#define SORT_CMP_H

#include "task.h"

using namespace std;

//根據date, completion, name排序
bool cmp_completed_date_name(const task* c1, const task* c2);

//根據date排序
bool cmp_date(const task* c1, const task* c2);

////根據name排序
bool cmp_name(const task* c1, const task* c2);

////根據category排序
bool cmp_category(const task* c1, const task* c2);

#endif