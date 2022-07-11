// CHttpClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HttpClient.h"
#include "WininetHttp.h"
#include "include/json/json.h"  
#include "CJsonObject.hpp"
#pragma execution_character_set("utf-8")
#pragma comment(lib, "jsoncpp.lib")  
using namespace std;
string input;
string LastId = "";
string PageMothed = "first";
int pages = 20;
int rows = 20;
int pagenum = 0;
FILE* file;
Json::Reader JsonRead(Json::Features::strictMode());
Json::Value JsonData;
string buildjson()
{
    string jsonObject;
    neb::CJsonObject oJson;
    oJson.Add("DelFlg",1);
    oJson.Add("GroupFlg", "");
    oJson.Add("IdCode", "62412c5f83e3ebef97021241");
    oJson.Add("LastId", LastId);
    oJson.Add("PageNextOrPre", PageMothed);
    oJson.Add("pages", pages);
    oJson.Add("Role", "");
    oJson.Add("rows", rows);
    oJson.AddEmptySubArray("WhereCollection");
    return oJson.ToString();
}
/*
char* UtfToGbk(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}
*/
void jsontest(const string json)
{
#pragma region MyRegion   cjsonobjec sample
    /*int iValue;
        double fTimeout;
        std::string strValue;
        neb::CJsonObject oJson("{\"refresh_interval\":60,"
            "\"test_float\":[18.0, 10.0, 5.0],"
            "\"test_int\":[135355, -1844674407370955161, -935375],"
            "\"timeout\":12.5,"
            "\"dynamic_loading\":["
            "{"
            "\"so_path\":\"plugins/User.so\", \"load\":false, \"version\":1,"
            "\"cmd\":["
            "{\"cmd\":2001, \"class\":\"neb::CmdUserLogin\"},"
            "{\"cmd\":2003, \"class\":\"neb::CmdUserLogout\"}"
            "],"
            "\"module\":["
            "{\"path\":\"im/user/login\", \"class\":\"neb::ModuleLogin\"},"
            "{\"path\":\"im/user/logout\", \"class\":\"neb::ModuleLogout\"}"
            "]"
            "},"
            "{"
            "\"so_path\":\"plugins/ChatMsg.so\", \"load\":false, \"version\":1,"
            "\"cmd\":["
            "{\"cmd\":2001, \"class\":\"neb::CmdChat\"}"
            "],"
            "\"module\":[]"
            "}"
            "]"
            "}");
        std::cout << oJson.ToString() << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        std::cout << oJson["dynamic_loading"][0]["cmd"][1]("class") << std::endl;
        oJson["dynamic_loading"][0]["cmd"][0].Get("cmd", iValue);
        std::cout << "iValue = " << iValue << std::endl;
        oJson["dynamic_loading"][0]["cmd"][0].Replace("cmd", -2001);
        oJson["dynamic_loading"][0]["cmd"][0].Get("cmd", iValue);
        std::cout << "iValue = " << iValue << std::endl;
        oJson.Get("timeout", fTimeout);
        std::cout << "fTimeout = " << fTimeout << std::endl;
        oJson["dynamic_loading"][0]["module"][0].Get("path", strValue);
        std::cout << "strValue = " << strValue << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        oJson.AddEmptySubObject("depend");
        oJson["depend"].Add("nebula", "https://github.com/Bwar/Nebula");
        oJson["depend"].AddEmptySubArray("bootstrap");
        oJson["depend"]["bootstrap"].Add("BEACON");
        oJson["depend"]["bootstrap"].Add("LOGIC");
        oJson["depend"]["bootstrap"].Add("LOGGER");
        oJson["depend"]["bootstrap"].Add("INTERFACE");
        oJson["depend"]["bootstrap"].Add("ACCESS");
        std::cout << oJson.ToString() << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        std::cout << oJson.ToFormattedString() << std::endl;

        std::cout << "-------------------------------------------------------------------" << std::endl;
        neb::CJsonObject oCopyJson = oJson;
        if (oCopyJson == oJson)
        {
            std::cout << "json equal" << std::endl;
        }
        oCopyJson["depend"]["bootstrap"].Delete(1);
        oCopyJson["depend"].Replace("nebula", "https://github.com/Bwar/CJsonObject");
        std::cout << oCopyJson.ToString() << std::endl;
        std::cout << "-------------------------key traverse------------------------------" << std::endl;
        std::string strTraversing;
        while (oJson["dynamic_loading"][0].GetKey(strTraversing))
        {
            std::cout << "traversing:  " << strTraversing << std::endl;
        }
        std::cout << "---------------add a new key, then key traverse---------------------" << std::endl;
        oJson["dynamic_loading"][0].Add("new_key", "new_value");
        while (oJson["dynamic_loading"][0].GetKey(strTraversing))
        {
            std::cout << "traversing:  " << strTraversing << std::endl;
        }

        std::cout << oJson["test_float"].GetArraySize() << std::endl;
        float fTestValue = 0.0;
        for (int i = 0; i < oJson["test_float"].GetArraySize(); ++i)
        {
            oJson["test_float"].Get(i, fTestValue);
            std::cout << fTestValue << "\t in string: " << oJson["test_float"](i) << std::endl;
        }
        for (int i = 0; i < oJson["test_int"].GetArraySize(); ++i)
        {
            std::cout << "in string: " << oJson["test_int"](i) << std::endl;
        }
        oJson.AddNull("null_value");
        std::cout << oJson.IsNull("test_float") << "\t" << oJson.IsNull("null_value") << std::endl;
        oJson["test_float"].AddNull();
        std::cout << oJson.ToString() << std::endl;

        if (oJson.KeyExist("simeout"))
            std::cout << "timeout key exist" << std::endl;

        neb::CJsonObject oLongLong("{\"long_long\":1283949231388184576}");
        int64 llValue = 0;
        uint64 ullValue = 0;
        oLongLong.Get("long_long", llValue);
        oLongLong.Get("long_long", ullValue);
        std::cout << "llValue = " << llValue << ",  ullValue = " << ullValue << std::endl;
        //oJson.Add("json_move", std::move(oLongLong)); // C++11
        oJson.AddWithMove("json_move", oLongLong);
        std::cout << oJson.ToString() << std::endl;
        */
#pragma endregion

JsonRead.parse(json,JsonData,true);
    string jsonstr = JsonData.toStyledString().data();
    std::cout << "jsoncpp test :!\n" << jsonstr << endl;
}
// UTF-8转为GBK2312 [3/14/2017/shike]

void postjson()
{
    CWininetHttp   conn;
    string   value = "http://124.223.82.154:8222/api/ListPage/GetPage";
    string body = buildjson();
    string conetype = "Content-Type: application/json";
    string res = conn.RequestJsonInfo(value, Hr_Post, conetype, body);
    jsontest(res);
    pagenum = JsonData["data"].size();
    cout << "\n request data rows:" << pagenum << endl;
}
//neb::CJsonObject oJson;
int main()
{
 

    bool flg = true;
    while (flg)
    {
        cout << "\ninput command ?help\n" << endl;
        cin >> input;
        if (input == "quit")
        {
            flg = false;
            exit(0);
        }
        else if (input == "help")
        {
            cout << "\nCommand List:\n"
                << "get <http url>\n"
                << "post <api url/ para dont define>\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << "json: json test sample\n"
                << "clear: clear the screen\n"
                << std::endl;
        }
        else if (input == "get")
        {
            //CHttpClient   conn;
            //CString   value = "http://124.223.82.154:24200/index.html";
            //value = conn.doGet(value);

            CWininetHttp   conn;
            string   value = "http://124.223.82.154:24200/index.html";
            string body = "";
            string conetype = "";
            string res = conn.RequestJsonInfo(value, Hr_Get, conetype, body);
            //string ustr = UtfToGbk(res.data());
            cout.clear();
            cout << "\nget request:\n" << res << endl;
        }
        else if (input == "post")
        {
            bool pflg = true;
            while (pflg)
            {
                cout << "\ninput command <first or next or pre>\n" << endl;
                cin >> input;
                if (input == "first")
                {                   
                    postjson();
                    LastId = "";
                    PageMothed = "first";
                    cout << "\nLastId:" << LastId << endl;
                }
                else if (input == "next")
                {
                    postjson();
                    if (pagenum > 0)
                    {
                        if (PageMothed == "next" || PageMothed == "first") {
                            LastId = JsonData["data"][pagenum - 1]["_id"].asCString();
                        }
                        else {
                            LastId = JsonData["data"][0]["_id"].asCString();
                        }
                        PageMothed = "next";
                        cout << "\nLastId:" << LastId << endl;
                    }
                    else
                    {
                        cout << "\ndont search data" << endl;
                    }

                    ///sendPostRequest("http://124.223.82.154:24200/api/ListPage/GetPage", buildjson("next"));
                }
                else if (input == "pre")
                {
                    postjson();
                    if (pagenum > 0)
                    {
                        if (PageMothed == "pre") {
                            LastId = JsonData["data"][pagenum - 1]["_id"].asCString();
                        }
                        else {
                            LastId = JsonData["data"][0]["_id"].asCString();
                        }
                        PageMothed = "pre";
                        cout << "\nLastId:" << LastId << endl;
                    }
                    else
                    {
                        cout << "\ndont search data" << endl;
                    }
                    ///sendPostRequest("http://124.223.82.154:24200/api/ListPage/GetPage", buildjson("pre"));
                }
                else if (input == "clear")
                {
                    system("cls");
                }
                else {
                    cout << "\nthe command is error!!!\n" << endl;
                    pflg = false;
                }

            }
        }
        else if (input == "clear")
        {
            system("cls");
        }
        else if (input=="json")
        {
            //jsontest();
            cout << "\ncancel json test!!!\n" << endl;
        }
        else {
            cout << "\nthe command is error!!!\n" << endl;
        }
    }
}
/*
*使用方法
1：get方式
CHttpClient conn;
CString value= "http://8crystal.com/test.asp ";
value=conn.doGet(value);
2：post方式
CHttpClient conn;
CString value= "http://8crystal.com/test.asp ";
conn.addParam( "name1 ", "value1 ");
conn.addParam( "name2 ", "value2 ");
conn.addParam( "name3 ", "value3 ");
conn.addParam( "name4 ", "value4 ");
conn.addParam( "name5 ", "value5 ");
conn.addParam( "name6 ", "value6 ");
value=conn.doPost(value);



1：get方式

  CHttpClient   conn;
  CString   value="http://8crystal.com/test.asp";
                    value=conn.doGet(value);


2：post方式

CHttpClient   conn;
  CString   value="http://8crystal.com/test.asp";
  conn.addParam("name1","value1");
  conn.addParam("name2","value2");
  conn.addParam("name3","value3");
  conn.addParam("name4","value4");
  conn.addParam("name5","value5");
  conn.addParam("name6","value6");
  value=conn.doPost(value);
*/