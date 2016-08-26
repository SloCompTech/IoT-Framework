#ifndef EXT_DBDRIVER
#define EXT_DBDRIVER

#include <mysql/mysql.h>
#include <Database/Database.h>

#include <string>
#include <ctime>
#include <iostream>

class DBDriver
{
  public:
    class DBDriverException:public std::exception
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
      std::string serial_number;
      std::string key;
      std::string token;
      std::string challenge;
      std::string address;
      int hello_interval;
      std::string last_talk;
      bool approved;

      Device()
      {
        this->id = 0;
        this->serial_number = "";
        this->key = "";
        this->token = "";
        this->challenge = "";
        this->address = "";
        this->hello_interval = 0;
        this->last_talk = "";
        this->approved = false;
      }

    };

    struct Object
    {
      int id;
      int device_id; //Id of device from table_devices
      std::string object_id;
      std::string type; //Type of device, eg. pir
      std::string model; //Model of device, eg. pir-024GH
      std::string last_update; //Data of last value change
      int change_interval; //Time when object considered offline
      std::string value; // Value
      short value_type; //Type of value
      std::string config_file;
      std::string handler_file; //File where callback may be located

      Object()
      {
        this->id = 0;
        this->device_id = 0;
        this->object_id = "";
        this->type = "";
        this->model = "";
        this->last_update = "";
        this->change_interval = 0;
        this->value = "";
        this->value_type = 0;
        this->config_file = "";
        this->handler_file = "";
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
      int group_id;
      std::string object_id;

      GroupMember()
      {
        this->id = 0;
        this->group_id = 0;
        this->object_id = "";
      }
    };

    Database db;

    //Device section
    bool DEVICE_create(struct Device dev);
    bool DEVICE_update(struct Device dev);
    bool DEVICE_remove(struct Device dev);
    bool DEVICE_remove(int id);
    struct Device DEVICE_getById(int id);
    struct Device DEVICE_getBySerialNumber(std::string _serialNumber);
    std::vector<struct Device> DEVICE_list();

    //Object section
    bool OBJECT_create(struct Object obj);
    bool OBJECT_update(struct Object obj);
    bool OBJECT_remove(struct Object obj);
    bool OBJECT_remove(int pId);
    struct Object OBJECT_getById(int pId);
    struct Object OBJECT_getByObjectId(std::string pId);
    std::vector<struct Object> OBJECT_list();


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
    bool GROUPLIST_create(struct GroupList gl);
    bool GROUPLIST_update(struct GroupList gl);
    bool GROUPLIST_remove(struct GroupList gl);
    bool GROUPLIST_remove(int pId);
    struct GroupList GROUPLIST_getById(int pId);
    struct GroupList GROUPLIST_getByName(std::string pName);
    std::vector<struct GroupList> GROUPLIST_list();

    //GroupMember section
    bool GROUPMEMBER_create(struct GroupMember gm);
    bool GROUPMEMBER_update(struct GroupMember gm);
    bool GROUPMEMBER_remove(struct GroupMember gm);
    bool GROUPMEMBER_remove(int pId);
    struct GroupMember GROUPMEMBER_getById(int pId);
    std::vector<struct GroupMember> GROUPMEMBER_list();
    std::vector<struct GroupMember> GROUPMEMBER_getByGroupId(int pGroupId);
    std::vector<struct GroupMember> GROUPMEMBER_getByObjectId(std::string pObjectId);

    //TODO: Security section

  private:
    const std::string TABLE_DEVICES = "table_devices";
    const std::string TABLE_OBJECTS = "table_objects";
    const std::string TABLE_LOG = "table_log";
    const std::string TABLE_GROUPLIST = "table_grouplist";
    const std::string TABLE_GROUPMEMBERS = "table_groupmembers";
};

#endif
