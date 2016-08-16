#ifndef LIB_DATABASE
#define LIB_DATABASE

#include <mysql/mysql.h>

#include <vector>
#include <string>


class Database
{
  public:

    class DatabaseException:public exception
    {
      public:
        std::string message = "";
        int fid = 0;
        DatabaseException(int _fid,std::string _message)
        {
          this->fid = _fid;
          this->message = _message;
        }
        const char * what () const throw ()
        {
          return ("[FID:"+std::to_string(this->fid)+"]"+message).c_str();
        }

    };


    Databse();
    ~Databse();

    void setCredentials(std::string address,std::string name,std::string username,std::string password);
    bool checkCredentials();

    bool connect();
    bool isConnected();
    bool disconnect();
    bool testConnection();

    std::string parse(std::string str);

    bool execNonQuery(std::string sql_cmd);
    MYSQL_RES *execQuery(std::string sql_cmd);
    std::vector<std::vector<std::string>> execVector(std::string sql_cmd);


  private:
    MYSQL *mysql_link;

    std::string DB_USER = "";
    std::string DB_PASS = "";
    std::string DB_ADDR = "";
    std::string DB_NAME = "";

};

#endif
