/*
@brief 本程序测试sqlite数据库的增删改查
@date 2012-09-03
*/
// SQLiteTest.cpp : Defines the entry point for the console application.
//

#include "sqlite3.h"
#include <iostream>
using namespace std;

sqlite3* pDB = NULL;

//增加用户
bool AddUser(const string& sName, const string& sAge);
//删除用户
bool DeleteUser(const string& sName);
//修改用户
bool ModifyUser(const string& sName, const string& sAge);
//查找用户
bool SelectUser();
bool CreateTable();

int main(int argc, char* argv[]) {
    //打开路径采用utf-8编码
    //如果路径中包含中文，需要进行编码转换
    int nRes = sqlite3_open(":memory:", &pDB);
    //int nRes = sqlite3_open("db.file", &pDB);
    if (nRes != SQLITE_OK) {
        cout << "Open database fail: " << sqlite3_errmsg(pDB);
        return -1;
    }

    CreateTable();

    //添加“赵钱孙李”
    for (int i = 0; i < 10000; i++) {
        AddUser(std::to_string(i), "18");
    }

    //查找用户
    for (int i = 0; i < 1000000; i++) {
        SelectUser();
    }

    sqlite3_close(pDB);

    return 0;
}

bool AddUser(const string& sName, const string& sAge) {
    string strSql = "";
    strSql +=
        "insert into user(name,age, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)";
    strSql += "values(";
    strSql += sName;
    strSql += ",";
    strSql += sAge;
    for (int i = 0; i < 10; i++) {
        strSql += ",";
        strSql += std::to_string(random() % 5);
    }
    strSql += ");";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK) {
        cout << "add user fail: " << cErrMsg << endl;
        return false;
    } else {
        cout << "add user success: " << sName.c_str() << "\t" << sAge.c_str()
             << endl;
    }

    return true;
}

bool DeleteUser(const string& sName) {
    string strSql = "";
    strSql += "delete from user where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK) {
        cout << "delete user fail: " << cErrMsg << endl;
        return false;
    } else {
        cout << "delete user success: " << sName.c_str() << endl;
    }

    return true;
}

bool ModifyUser(const string& sName, const string& sAge) {
    string strSql = "";
    strSql += "update user set age =";
    strSql += sAge;
    strSql += " where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK) {
        cout << "modify user fail: " << cErrMsg << endl;
        return false;
    } else {
        cout << "modify user success: " << sName.c_str() << "\t" << sAge.c_str()
             << endl;
    }

    return true;
}

static int UserResult(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", ";
    }
    cout << endl;

    return 0;
}
bool CreateTable() {
    char* cErrMsg;
    int res = sqlite3_exec(pDB,
                           "create table user(name char(10), age int, p1 "
                           "char(10), p2 char(10), p3 char(10), p4 char(10), "
                           "p5 char(10), p6 char(10), p7 char(10), p8 "
                           "char(10), p9 char(10), p10 char(10) ) ;",
                           0, 0, &cErrMsg);
    if (res != SQLITE_OK) {
        cout << "create table fail: " << cErrMsg << endl;
        return false;
    }

    res = sqlite3_exec(pDB,
                       "CREATE INDEX xxx_xxx_xxx on user(name, age, p1, p2, "
                       "p3, p4, p5, p6, p7, p8, p9, p10);",
                       0, 0, &cErrMsg);

    if (res != SQLITE_OK) {
        cout << "create index fail: " << cErrMsg << endl;
        return false;
    }

    return true;
}

bool SelectUser() {
    char* cErrMsg;
    static string strSql = "select age from user where ";
    strSql = "select age from user where ";
    strSql += "name=";
    strSql += std::to_string(random() % 10000);
    for (int i = 1; i <= 4; i++) {
        strSql += " and p";
        strSql += std::to_string(i);
        strSql += "=";
        strSql += std::to_string(random() % 7);
    }
    //cout << strSql << endl;
    int res = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);

    if (res != SQLITE_OK) {
        cout << "select fail: " << cErrMsg << endl;
        return false;
    }

    return true;
}
