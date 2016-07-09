#include "jsonrpc.h"
JsonRPC::JsonRPC(string pVersion)
{
  this->setVersion(pVersion);
}

bool JsonRPC::parse(string pText)
{
  Json::Reader reader;
	return reader.parse(pText,this->root,false);
}

bool JsonRPC::isValid()
{
  return !this->root["jsonrpc"].isNull()&&this->root["jsonrpc"].isString();
}

string JsonRPC::getVersion()
{
  if(!this->root["jsonrpc"].isNull()&&this->root["jsonrpc"].isString())
    return this->root["jsonrpc"].asString();
  else
    return "";
}

void JsonRPC::setVersion(string pVersion)
{
  this->root["jsonrpc"] = pVersion;
}

int JsonRPC::getType()
{
  if(this->isValid())/* If we have valid standard */
  {
    if(!this->root["method"].isNull()&&this->root["method"].isString())
    {
      if(!this->root["id"].isNull()&&this->root["id"].isInt())
        return this->Type::Message; /* Json-rpc object is a message */
      else
        return this->Type::Notification; /* Json-rpc object is a notification */
    }
    else if(!this->root["result"].isNull()&&this->root["error"].isNull())
    {
      if(!this->root["id"].isNull()&&this->root["id"].isInt())
        return this->Type::Result; /* Json-rpc object is a response */
      else
        return this->Type::None;
    }
    else if(!this->root["error"].isNull()&&this->root["result"].isNull())
    {
      if(!this->root["id"].isNull()&&this->root["id"].isInt())
        return this->Type::Error; /* Json-rpc object is a error */
      else
        return this->Type::None;
    }
    else
      return this->Type::None;
  }
  else
    return this->Type::None;
}

int JsonRPC::getId()
{
  if(!this->root["id"].isNull()&&this->root["id"].isInt())
    return this->root["id"].asInt();
  else
    return 0;
}

bool JsonRPC::setId(int pId)
{
  if(pId>0)
  {
    this->root["id"] = pId;
    return true;
  }

  return false;
}

string JsonRPC::getMethod()
{
  if(!this->root["method"].isNull()&&this->root["method"].isString())
    return this->root["method"].asString();
  else
    return "";
}
void JsonRPC::setMethod(string pMethod)
{
  this->root["method"] = pMethod;
}

void JsonRPC::setParams(Json::Value pValue)
{
  this->root["params"] = pValue;
}
Json::Value JsonRPC::getParams()
{
  return this->root["params"];
}

void JsonRPC::setResult(Json::Value pResult)
{
  this->root["result"] = pResult;
}
Json::Value JsonRPC::getResult()
{
  return this->root["result"];
}
void JsonRPC::setErrorCode(int pCode)
{
  this->root["error"]["code"] = pCode;
}
int JsonRPC::getErrorCode()
{
  if(!this->root["error"]["code"].isNull()&&this->root["error"]["code"].isInt())
    return this->root["error"]["code"].asInt();
  else
    return 0;
}
void JsonRPC::setErrorMessage(string pMessage)
{
  this->root["error"]["message"] = pMessage;
}
string JsonRPC::getErrorMessage()
{
  if(!this->root["error"]["message"].isNull()&&this->root["error"]["message"].isString())
    return this->root["error"]["message"].asString();
  else
    return "";
}

void JsonRPC::setErrorData(Json::Value pData)
{
  this->root["error"]["data"] = pData;
}
Json::Value JsonRPC::getErrorData()
{
  return this->root["error"]["data"];
}

void JsonRPC::print()
{
  cout << this->root << endl;
}

string JsonRPC::str()
{
  return this->root.asString();
}
