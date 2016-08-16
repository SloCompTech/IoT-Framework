#ifndef EXT_DBDRIVER
#define EXT_DBDRIVER

#include <mysql/mysql.h>
#include <Database/Database.h>

#include <string>
#include <ctime>

class DBDriver
{
  public:
    class DBDriverException:public exception
    {
      public:
        std::string message = "";
        int fid = 0;
        DBDriverException(int _fid,std::string _message)
        {
          this->fid = _fid;
          this->message = _message;
        }
        const char * what () const throw ()
        {
          return ("[FID:"+std::to_string(this->fid)+"]"+message).c_str();
        }

    };

    struct Device
    {
      int id;
      std::string serialNumber;
      std::string key;
      std::string token;
      std::string challenge;
      std::string address;
      int helloInterval;
      std::string lastTalk;
      bool approved;

      Device()
      {
        this->id = 0;
        this->serialNumber = "";
        this->key = "";
        this->token = "";
        this->chalange = "";
        this->address = "";
        this->helloInterval = 0;
        this->lastTalk = "";
        this->approved = false;
      }

    };

    struct Object
    {
      int id;
      std::string uid;
      std::string type; //Type of device, eg. pir
      std::string model; //Model of device, eg. pir-024GH
      std::string lastUpdate; //Data of last value change
      int changeInterval; //Time when object considered offline
      std::string value; // Value
      short valueType; //Type of value
      std::string handlerFile; //File where callback may be located

      Object()
      {
        this->id = 0;
        this->uid = "";
        this->type = "";
        this->model = "";
        this->lastUpdate = "";
        this->changeInterval = 0;
        this->value = "";
        this->valueType = 0;
        this->handlerFile = "";
      }
    };

    struct Log
    {
      int id;
      std::string date;
      short type; // Type of info, eg. warning,error,info
      std::string category; //Thematic
      std::string message;
      short display; //If it will be displayed

      Log()
      {
        this->id = 0;
        this->date = "";
        this->type = 0;
        this->category = "";
        this->message = "";
        this->display = 0;
      }
    };

    struct GroupList
    {
      int id;
      std::string name;

      GroupList()
      {
        this->id = 0;
        this->name = "";
      }
    };

    struct GroupMember
    {
      int id;
      int groupId;
      std::string objectId;

      GroupMember()
      {
        this->id = 0;
        this->groupId = 0;
        this->objectId = "";
      }
    };

    Databse db;

    //Device section
    bool DEVICE_create(struct Device dev);
    bool DEVICE_update(struct Device dev);
    bool DEVICE_remove(struct Device dev);
    bool DEVICE_remove(int id);
    struct Device DEVICE_getById(int id);
    struct Device DEVICE_getBySerialNumber(std::string _serialNumber);
    std::vector<struct Device> DEVICE_list();

    //Object section

    //Log section
    bool LOG_create(struct Log log);
    bool LOG_update(struct Log log);
    bool LOG_remove(struct Log log);
    bool LOG_remove(int id);
    struct Log LOG_getById(int id);
    bool LOG_mark(int id,short display);
    std::vector<struct Log> LOG_list();
    std::vector<struct Log> LOG_getByType(short type);
    std::vector<struct Log> LOG_getByCategory(std::string category);
    std::vector<struct Log> LOG_getForDisplay();


    //GroupList section

    //GroupMember section

    //TODO: Security section

  private:
    const std::string TABLE_DEVICES = "table_devices";
    const std::string TABLE_LOG = "table_log";

};

#endif
