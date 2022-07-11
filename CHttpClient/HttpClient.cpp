//#include   "stdafx.h"
//#include   "emailsenderv2.h"
#include <iostream>
#include   "HttpClient.h"

#ifdef   _DEBUG
#undef   THIS_FILE
static   char   THIS_FILE[] = __FILE__;
#define   new   DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//   Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHttpClient::CHttpClient()
{

}

CHttpClient::~CHttpClient()
{

}

CString   CHttpClient::doGet(CString   href)
{
    CString   httpsource = "";
    CInternetSession   session1(NULL, 0);
    CHttpFile* pHTTPFile = NULL;
    try {
        pHTTPFile = (CHttpFile*)session1.OpenURL(href);
        //session1.
    }
    catch (int e) {
        pHTTPFile = NULL;
    }
    if (pHTTPFile)
    {
        CString   text;
        for (int i = 0; pHTTPFile->ReadString(text); i++)
        {
            httpsource = httpsource + text + "rn";
        }
        pHTTPFile->Close();
        delete   pHTTPFile;
    }
    else
    {

    }
    const char* ch = (LPCTSTR)httpsource;
    CString result = UtfToGbk(ch);
    return   result;
}
/// <summary>
/// 表单提交
/// </summary>
/// <param name="href"></param>
/// <returns></returns>
CString   CHttpClient::doPost(CString   href)
{
    CString   httpsource = "";
    CInternetSession   session1;
    CHttpConnection* conn1 = NULL;
    CHttpFile* pFile = NULL;
    CString   strServerName;
    CString   strObject;
    INTERNET_PORT   nPort;
    DWORD   dwServiceType;
    AfxParseURL((LPCTSTR)href, dwServiceType, strServerName, strObject, nPort);
    DWORD   retcode;
    char* outBuff = CONTENT.GetBuffer(1000);
    try
    {
        conn1 = session1.GetHttpConnection(strServerName, nPort);
        pFile = conn1->OpenRequest(0, strObject, NULL, 1, NULL, "HTTP/1.1", INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT);
        pFile->AddRequestHeaders("Content-Type:   application/x-www-form-urlencoded");
        pFile->AddRequestHeaders("Accept:   */*");
        pFile->SendRequest(NULL, 0, outBuff, strlen(outBuff) + 1);
        pFile->QueryInfoStatusCode(retcode);
    }
    catch (CInternetException* e) {};
    if (pFile)
    {
        CString   text;
        for (int i = 0; pFile->ReadString(text); i++)
        {
            httpsource = httpsource + text + "rn";
        }
        pFile->Close();
    }
    else
    {

    }
    return   httpsource;
    delete   pFile;
    delete   conn1;
    session1.Close();
}
/// <summary>
/// json 提交
/// </summary>
/// <param name="href"></param>
/// <returns></returns>
CString   CHttpClient::doPostjosn(CString   href)
{
    CString   httpsource = "";
    CInternetSession   session1;
    CHttpConnection* conn1 = NULL;
    CHttpFile* pFile = NULL;
    CString   strServerName;
    CString   strObject;
    INTERNET_PORT   nPort;
    DWORD   dwServiceType;
    AfxParseURL((LPCTSTR)href, dwServiceType, strServerName, strObject, nPort);
    DWORD   retcode;
    char* outBuff = CONTENT.GetBuffer(1000);
    try
    {
        conn1 = session1.GetHttpConnection(strServerName, nPort);
        pFile = conn1->OpenRequest(0, strObject, NULL, 1, NULL, "HTTP/1.1", INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT);
        pFile->AddRequestHeaders("Content-Type: application/json");
        pFile->AddRequestHeaders("Accept: application/json");
        pFile->SendRequest(NULL, 0, outBuff, strlen(outBuff) + 1);
        pFile->QueryInfoStatusCode(retcode);
    }
    catch (CInternetException* e) {
        std::cout << "post err"  << std::endl;
    };
    if (pFile)
    {
        CString   text;
        for (int i = 0; pFile->ReadString(text); i++)
        {
            httpsource = httpsource + text + "/r/n";
        }
        pFile->Close();
    }
    else
    {

    }
    //return   httpsource;
    const char* ch = (LPCTSTR)httpsource;
    CString result = UtfToGbk(ch);
    return   result;
    delete   pFile;
    delete   conn1;
    session1.Close();
}

void   CHttpClient::addParam(CString   name, CString   value)
{
    names.AddTail((LPCTSTR)name);
    values.AddTail((LPCTSTR)value);
    CString   eq = "=";
    CString   an = "&";
    if (CONTENT.GetLength() > 0)
    {
        CONTENT += an + name + eq + value;
    }
    else
    {
        CONTENT +=  name + eq + value;
    }
    //CONTENT = CONTENT + name + eq + value + an;
    CL = CONTENT.GetLength();
}
void   CHttpClient::addJson(CString  body)
{
    /*names.AddTail((LPCTSTR)name);
    values.AddTail((LPCTSTR)value);
    CString   eq = "=";
    CString   an = "&";*/
    CONTENT = body;
    CL = CONTENT.GetLength();
}
// UTF-8转为GBK2312 [3/14/2017/shike]
CString CHttpClient::UtfToGbk(const char* utf8)
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