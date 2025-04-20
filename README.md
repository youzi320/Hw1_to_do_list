# To-Do list
---
## 執行專案
windows:
```
cd src
g++ *.cpp to_do_list_class\*.cpp -o to_do_list.exe
./to_do_list.exe
```

## 專案目錄結構
```
.
├── header/  
|  ├── Basic_task.h  
|  ├── calendar.h  
|  ├── check.h  
|  ├── handle_input.h  
|  ├── print_line.h  
|  ├── sort_cmp.h  
|  ├── task.h  
|  ├── to_do_list.h 
|  └── user.h 
└── src/ 
  ├── to_do_list_class/ 
  │ ├── to_do_list_add.cpp 
  │ ├── to_do_list_calendar.cpp 
  │ ├── to_do_list_del.cpp 
  │ ├── to_do_list_edit.cpp 
  │ ├── to_do_list_man.cpp 
  │ ├── to_do_list_undo_redo.cpp 
  │ ├── to_do_list_view.cpp 
  │ └── to_do_list.cpp 
  ├── calendar.cpp 
  ├── check.cpp 
  ├── handle_input.cpp 
  ├── main.cpp
  ├── print_line.cpp 
  ├── sort_cmp.cpp 
  ├── task.cpp 
  |── user.cpp
  └─── user_file/ 
      └── user_data.txt 
```
### 說明
- header/ : 存放標頭檔
- src/to_do_class/ : 各類to_do_list指令實作
- src/*.cpp : 各主要類別的實作檔案與一些檢查資料、輸出版面的程式
- src/user_file/user_data.txt : 存放使用者資料


## task
一個task(任務)有以下欄位:
| name             | date             | category         | completed         |
|------------------|------------------|------------------|-------------------|

- 相同名子與日期的任務在視為同一個任務
- 英文字串，不含空格
- 日期格式: [year]/[month]/[date], ex. 2025/04/20
## 功能列表
- Add a task
- Delete a task
- View task(s) by different label
- Edit a task
- Undo / Redo for add, delete, and edit task
- Calendar mode(月曆形式輸出，更方便查找任務與每天的任務新增、修改、刪除)
- 多個使用者註冊、登入
- 刪除使用者
- 紀錄多個使用者的 To-Do list 資料 
---

## 指令說明

### add
- add 指令至少要帶以下一種flag
```
add [-n] [-d] [-ca]
-n [name]: 使用 -n flag 時，需帶參數 [name] 當作新增的任務名
-d [date]: 使用 -d flag 時，需帶參數 [date] 當作新增的日期，日期格式: [year]/[month]/[date], ex. 2025/04/20
-ca [category]: 使用 -ca flag 時，需帶參數 [category] 當作新增的任務分類

ex. add -n t1 -d 2025/04/20 (新增名為 t1 日期為 2025/04/20 的任務)
```
### view
- view 不帶flag時預設為輸出全部任務(排列順序為1.日期 2.是否完成 3.名字)
```
view [-a] [-n] [-d] [-ca] [-done] [-undone]
-a: 輸出全部任務(排列順序為1.日期 2.是否完成 3.名子)
-n [name]: 輸出全部名為 [name] 的任務
-d [date]: 輸出全部日期為 [date] 的任務
-ca [category]: 輸出全部類別為 [category] 的任務
-done: 輸出已完成任務
-undone: 輸出未完成任務

ex. view -done (輸出全部未完成任務)
```

### edit
```
edit [original name] [orginal date] [-n] [-d] [-ca] [-co] 
-n [new name]: 使用 -n flag 時，需帶參數 [new name]，將 orginal task 的名子改為 [new name]
-d [new date]: 使用 -d flag 時，需帶參數 [new date]，將 orginal task 的日期改為 [new name]
-ca [new category]: 使用 -ca flag 時，需帶參數 [new category]，將 orginal task 的分類改為 [new category]
-co [new completed]: 使用 -co flag 時，需帶參數 1 或 0，將 orginal task 的 completed 欄位改為 1(完成)或 0(未完成)

ex. edit t1 2025/04/20 -n t2 (將名為 t1 的任務名子改為 t2)
```

### del
```
del [name] [date] : 刪除名子為 [name]，日期為 [date] 的任務
```

### calendar mode
- 行事曆模式，在此模式下可以使用以下指令:
#### calendar
```
calendar: 進入行事曆模式               
```
#### 設定年份、月份、天
```
- year [year]: 設定為 [year] 年
- month [month]: 設定為 [year] 年 [month] 月，並輸出當月行事曆(使用此指令時需先設定年份)
- day [day]: 設定為 [year] 年 [month] 月[day] 日，並輸出當日任務(使用此指令時需先設定年份與月份)
```
#### mt
- 設定好年份、月份與天時，可以使用此指令
```
mt [-e] [-add] [-done] [-del]
-e [original name] [new name]: 使用 -e flag 時，需帶參數 [new name]，將當日 orginal task 的名子改為 [name]
-add [name]: 使用 -add flag 時，需帶參數 [name] 當作當日新增的任務名
-done [name]: 使用 -done flag 時，需帶參數 [name]，將當日名為 [name] 的任務的 completed 欄位改為 1(完成)
-undone [name]: 使用 -undone flag 時，需帶參數 [name]，將當日名為 [name] 的任務的 completed 欄位改為 0(未完成)
```
## 使用者登入功能
- 可以在登入介面註冊使用者帳號與密碼，註冊完就可以登入並使用 To-Do list
- 使用者帳號與 To-Do list 資料持存在"./src./user_file/user_data.txt"中，其中密碼會經過雜湊後儲存

