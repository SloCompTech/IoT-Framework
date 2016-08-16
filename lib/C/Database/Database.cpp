#include "Database.h"

// Basic section

Database::Database()
{
  //Init
  mysql_link = NULL;
}

Database::~Database()
{
  if(this->isConnected())
    this->disconnect();
}

// Other
void Databse::setCredentials(std::string address,std::string name,std::string username,std::string password)
{
  this->DB_ADDR = address;
  this->DB_NAME = name;
  this->DB_USER = username;
  this->DB_PASS = password;
}

bool Databse::checkCredentials()
{
  if(this->DB_ADDR==""||this->DB_USER==""||this->DB_NAME=="")
    return false;

  return true;
}

bool Databse::connect()
{
  if(this->mysql_link == NULL)
	{
    //Check credentials
    if(!this->checkCredentials())
    {
      throw DatabaseException(0,"Credentials not set correctly");
      return false;
    }

    //Init object
    this->mysql_link = mysql_init(NULL);

    //Check if created
		if(this->mysql_link == NULL)
		{
			mysql_close(this->mysql_link);
			this->mysql_link = NULL;
      throw DatabaseException(0,"SQL Initalization error");
			return false;
		}

		//Connect to the database
		if(mysql_real_connect(this->mysql_link, this->DB_ADDR.c_str(), this->DB_USER.c_str(), this->DB_PASS.c_str(), this->DB_NAME.c_str(), 0, NULL, 0) == NULL)
		{
      //Failed to connect
			mysql_close(this->mysql_link);
			this->mysql_link = NULL;
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool Database::isConnected()
{
  if(this->mysql_link == NULL)
		return false;

	string info(mysql_stat(this->mysql_link));
	if(info=="")
	{
		mysql_close(this->mysql_link);
		this->mysql_link = NULL;
		return false;
	}
	return true;
}

bool Database::disconnect()
{
  if(this->mysql_link != NULL)
	{
		mysql_close(this->mysql_link);
		this->mysql_link = NULL;
		return true;
	}
	return false;
}

bool Databse::testConnection()
{
  if(!this->checkCredentials())
    return false;
  if(!this->connect())
    return false;
  if(!this->isConnected())
  {
    this->disconnect();
    return false;
  }

  this->disconnect();
  return true;
}

std::string Database::parse(std::string str)
{
  if(this->mysql_link != NULL)
  {
		char *tmp = new char[(str.length() * 2) + 1]; //Double size because special chars
		mysql_real_escape_string(mysql_link,tmp,str.c_str(),str.length());
		string res(tmp);
		delete tmp;
		return res;
	}else{
		throw DatabaseException(0,"Not connected to database");
	}
	return "";
}
bool Databse::execNonQuery(std::string sql_cmd)
{
  if(this->mysql_link!=NULL)
  {
    if (mysql_query(this->mysql_link,sql_cmd.c_str()))
		{
			throw DatabaseException(0,(std::string)mysql_error(this->mysql_link));
			return false;
		}
    return true;
  }
  else
  {
    throw DatabaseException(0,"Not connected to database");
    return false;
  }
  return false;
}

MYSQL_RES *Database::execQuery(std::string sql_cmd)
{
  if (this->mysql_link != NULL)
  {
		if (!mysql_query(this->mysql_link, sql_cmd.c_str()))
    {
    	MYSQL_RES *result = mysql_store_result(this->mysql_link);
    	if (result != NULL)
    	{
        return result;
    	}
      else
      {
	      throw DatabaseException(0,(std::string)mysql_error(this->mysql_link));
        return NULL;
      }
    }else{
			throw DatabaseException(0,(std::string)mysql_error(this->mysql_link));
			return NULL;
		}

  }else{
		throw DatabaseException(0,"Not connected to database");
		return NULL;
	}
}

std::vector<std::vector<std::string>> Database::execVector(std::string sql_cmd)
{
  std::vector<std::vector<std::string>> buff;

  MYSQL_RES *result = this->execQuery(sql_cmd);
  if(result != NULL)
  {
    //Get the number of columns
    int num_rows = mysql_num_rows(result);
		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;
    while((row = mysql_fetch_row(result)))
    {
  			std::vector<std::string> buffItem;
        for(int i=0;i<num_fields;i++)
          buffItem.push_back((std::string)row[i]);
        buff.push_back(buffItem);
    }
    mysql_free_result(result);
		return buff;
  }
  else
  {
    throw DatabaseException(0,"Failed to get results");
    return buff;
  }

}
