#ifndef LIB_JSONRPC
#define LIB_JSONRPC

#include <iostream>
#include <string>
#include <jsoncpp/dist/json/json.h>
#include <jsoncpp/dist/json/json-forwards.h>

using namespace std;


class JsonRPC
{

  public:
    enum Type:int
    {
      None,
      Message,
      Notification,
      Result,
      Error
    };
    JsonRPC();
    JsonRPC(string pVersion);

    bool parse(string pText);
    bool isValid();
    void print();
    string str();

    /* Values manipulation */
    string getVersion();
    void setVersion(string pVersion);

    int getType();

    int getId();
    bool setId(int pId );

    string getMethod();
    void setMethod(string pMethod);

    void setParams(Json::Value pValue);
    Json::Value getParams();

    void setResult(Json::Value pResult);
    Json::Value getResult();

    bool hasError();
    void setErrorCode(int pCode);
    int getErrorCode();
    void setErrorMessage(string pMessage);
    string getErrorMessage();
    void setErrorData(Json::Value pData);
    Json::Value getErrorData();

  private:
    Json::Value root;
};
#endif
