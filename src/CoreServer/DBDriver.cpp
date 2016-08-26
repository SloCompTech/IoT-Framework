#include "DBDriver.h"


/*
*     DEVICE section
*/


bool DBDriver::DEVICE_create(struct DBDriver::Device dev)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_DEVICES+" ('serial_number','key','token','challenge','address','hello_interval','last_talk','approved') "
      +"VALUES ('"+this->db.parse(dev.serial_number)+"','"+this->db.parse(dev.key)
      +"','"+this->db.parse(dev.token)+"','"+this->db.parse(dev.challenge)
      +"','"+this->db.parse(dev.address)+"','"+std::to_string(dev.hello_interval)
      +"','"+this->db.parse(dev.last_talk)+"','"+std::to_string(dev.approved)+"');";
    return this->db.execNonQuery(cmd);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::DEVICE_update(struct DBDriver::Device dev)
{
  if(this->db.isConnected())
  {
    if(dev.id > 0) //Not new device structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_DEVICES+" SET 'serial_number'='"+this->db.parse(dev.serial_number)
        +"','key'='"+this->db.parse(dev.key)+"','token'='"+this->db.parse(dev.token)+"','challenge'='"+this->db.parse(dev.challenge)
        +"','address'='"+this->db.parse(dev.address)+"','hello_interval'='"+std::to_string(dev.hello_interval)
        +"','last_talk'='"+this->db.parse(dev.last_talk)+"','approved'='"+std::to_string(dev.approved)+"' "
        +"WHERE id='"+std::to_string(dev.id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New device structure
    {
      this->DEVICE_create(dev);
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::DEVICE_remove(struct DBDriver::Device dev)
{
  if(this->db.isConnected())
  {
    if(dev.id > 0) //Not new device structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_DEVICES+" WHERE id='"+std::to_string(dev.id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New device structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::DEVICE_remove(int id)
{
  if(this->db.isConnected())
  {
    if(id > 0) //Not new device structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_DEVICES+" WHERE id='"+std::to_string(id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New device structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

struct DBDriver::Device DBDriver::DEVICE_getById(int id)
{
  struct Device dev;
  if(this->db.isConnected())
  {
    if(id > 0) //Not new device structure
    {
      std::string cmd = (std::string)"SELECT 'id','serial_number','key','token','challenge','address','hello_interval','last_talk','approved' FROM "+this->TABLE_DEVICES+" WHERE id='"+std::to_string(id)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 9)
  			{
			    int i = atoi(row[0]);
  				if(i==id)
					{
            dev.id = atoi(row[0]);
            dev.serial_number = (std::string)row[1];
            dev.key = (std::string)row[2];
            dev.token = (std::string)row[3];
            dev.challenge = (std::string)row[4];
            dev.address = (std::string)row[5];
            dev.hello_interval = atoi(row[6]);
            dev.last_talk = (std::string)row[7];
            dev.approved = (bool)atoi(row[8]);
						break;
					}
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
				}
  		}
      mysql_free_result(result);
    }
    else //New device structure
    {
      return dev;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return dev;
  }
  return dev;
}
struct DBDriver::Device DBDriver::DEVICE_getBySerialNumber(std::string _serialNumber)
{
  struct Device dev;
  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','serial_number','key','token','challenge','address','hello_Interval','last_talk','approved' FROM "+this->TABLE_DEVICES+" WHERE serial_number='"+_serialNumber+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 9)
  			{
			    std::string i(row[1]);
  				if(i==_serialNumber)
					{
            dev.id = atoi(row[0]);
            dev.serial_number = (std::string)row[1];
            dev.key = (std::string)row[2];
            dev.token = (std::string)row[3];
            dev.challenge = (std::string)row[4];
            dev.address = (std::string)row[5];
            dev.hello_interval = atoi(row[6]);
            dev.last_talk = (std::string)row[7];
            dev.approved = (bool)atoi(row[8]);
						break;
					}
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return dev;
  }
  return dev;
}

std::vector<struct DBDriver::Device> DBDriver::DEVICE_list()
{
  std::vector<struct Device> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','serial_number','key','token','challenge','address','hello_interval','last_talk','approved' FROM "+this->TABLE_DEVICES+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 9)
  			{
          struct Device dev;

          dev.id = atoi(row[0]);
          dev.serial_number = (std::string)row[1];
          dev.key = (std::string)row[2];
          dev.token = (std::string)row[3];
          dev.challenge = (std::string)row[4];
          dev.address = (std::string)row[5];
          dev.hello_interval = atoi(row[6]);
          dev.last_talk = (std::string)row[7];
          dev.approved = (bool)atoi(row[8]);

          buff.push_back(dev);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}

/*
*     Object section
*/
bool DBDriver::OBJECT_create(struct DBDriver::Object obj)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_OBJECTS+" ('device_id','object_id','type','model','last_update','change_interval','value','value_type','config_file','handler_file') "
      +"VALUES ('"+std::to_string(obj.device_id)+"','"+this->db.parse(obj.object_id)
      +"','"+this->db.parse(obj.type)+"','"+this->db.parse(obj.model)
      +"','"+this->db.parse(obj.last_update)+"','"+std::to_string(obj.change_interval)
      +"','"+this->db.parse(obj.value)+"','"+std::to_string(obj.value_type)+
      +"','"+this->db.parse(obj.config_file)+"','"+this->db.parse(obj.handler_file)+"');";
    return this->db.execNonQuery(cmd);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::OBJECT_update(struct DBDriver::Object obj)
{
  if(this->db.isConnected())
  {
    if(obj.id > 0) //Not new object structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_OBJECTS+" SET 'device_id'='"+std::to_string(obj.device_id)
        +"','object_id'='"+this->db.parse(obj.object_id)+"','type'='"+this->db.parse(obj.type)+"','model'='"+this->db.parse(obj.model)
        +"','last_update'='"+this->db.parse(obj.last_update)+"','change_interval'='"+std::to_string(obj.change_interval)
        +"','value'='"+this->db.parse(obj.value)+"','value_type='"+std::to_string(obj.value_type)
        +"','config_file'='"+this->db.parse(obj.config_file)+"','handler_file'='"+this->db.parse(obj.handler_file)+"' "
        +"WHERE id='"+std::to_string(obj.id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New object structure
    {
      this->OBJECT_create(obj);
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::OBJECT_remove(struct DBDriver::Object obj)
{
  if(this->db.isConnected())
  {
    if(obj.id > 0) //Not new Object structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_OBJECTS+" WHERE id='"+std::to_string(obj.id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New Object structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::OBJECT_remove(int pId)
{
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new object structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_OBJECTS+" WHERE id='"+std::to_string(pId)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New object structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
struct DBDriver::Object DBDriver::OBJECT_getById(int pId)
{
  struct Object obj;
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new object structure
    {
      std::string cmd = (std::string)"SELECT 'id','device_id','object_id','type','model','last_update','change_interval','value','value_type','config_file','handler_file' FROM "+this->TABLE_OBJECTS+" WHERE id='"+std::to_string(pId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 11)
        {
          int i = atoi(row[0]);
          if(i==pId)
          {
            obj.id = atoi(row[0]);
            obj.device_id = atoi(row[1]);
            obj.object_id = (std::string)row[2];
            obj.type = (std::string)row[3];
            obj.model = (std::string)row[4];
            obj.last_update = (std::string)row[5];
            obj.change_interval = atoi(row[6]);
            obj.value = (std::string)row[7];
            obj.value_type = (short)atoi(row[8]);
            obj.config_file = (std::string)row[9];
            obj.handler_file = (std::string)row[10];
            break;
          }
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
        }
      }
      mysql_free_result(result);
    }
    else //New object structure
    {
      return obj;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return obj;
  }
  return obj;
}
struct DBDriver::Object DBDriver::OBJECT_getByObjectId(std::string pId)
{
  struct Object obj;
  if(this->db.isConnected())
  {
    if(pId != "") //Not new object structure
    {
      std::string cmd = (std::string)"SELECT 'id','device_id','object_id','type','model','last_update','change_interval','value','value_type','config_file','handler_file' FROM "+this->TABLE_OBJECTS+" WHERE object_id='"+this->db.parse(pId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 11)
        {
          std::string i = (std::string)(row[2]);
          if(i==pId)
          {
            obj.id = atoi(row[0]);
            obj.device_id = atoi(row[1]);
            obj.object_id = (std::string)row[2];
            obj.type = (std::string)row[3];
            obj.model = (std::string)row[4];
            obj.last_update = (std::string)row[5];
            obj.change_interval = atoi(row[6]);
            obj.value = (std::string)row[7];
            obj.value_type = (short)atoi(row[8]);
            obj.config_file = (std::string)row[9];
            obj.handler_file = (std::string)row[10];
            break;
          }
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
        }
      }
      mysql_free_result(result);
    }
    else //New object structure
    {
      return obj;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return obj;
  }
  return obj;
}
std::vector<struct DBDriver::Object> DBDriver::OBJECT_list()
{
  std::vector<struct Object> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','device_id','object_id','type','model','last_update','change_interval','value','value_type','config_file','handler_file' FROM "+this->TABLE_OBJECTS+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 11)
  			{
          struct Object obj;

          obj.id = atoi(row[0]);
          obj.device_id = atoi(row[1]);
          obj.object_id = (std::string)row[2];
          obj.type = (std::string)row[3];
          obj.model = (std::string)row[4];
          obj.last_update = (std::string)row[5];
          obj.change_interval = atoi(row[6]);
          obj.value = (std::string)row[7];
          obj.value_type = (short)atoi(row[8]);
          obj.config_file = (std::string)row[9];
          obj.handler_file = (std::string)row[10];

          buff.push_back(obj);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}


/*
*     Log section
*/

bool DBDriver::LOG_create(struct DBDriver::Log log)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_LOG+" ("+((log.date!="")?"'date',":"")+"'type','category','message','display') "
      +"VALUES ('"+((log.date!="")?(this->db.parse(log.date)+"','"):"")+this->db.parse(std::to_string(log.type))+"','"+this->db.parse(log.category)
      +"','"+this->db.parse(log.message)+"','"+this->db.parse(std::to_string(log.display))
      +"');";
    return this->db.execNonQuery(cmd);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::LOG_update(struct DBDriver::Log log)
{
  if(this->db.isConnected())
  {
    if(log.id > 0) //Not new log structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_LOG+" SET 'date'='"+this->db.parse(log.date)
        +"','type'='"+this->db.parse(std::to_string(log.type))+"','category'='"+this->db.parse(log.category)+"','message'='"+this->db.parse(log.message)
        +"','display'='"+this->db.parse(std::to_string(log.display))+"' "
        +"WHERE id='"+std::to_string(log.id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New log structure
    {
      this->LOG_create(log);
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::LOG_remove(struct DBDriver::Log log)
{
  if(this->db.isConnected())
  {
    if(log.id > 0) //Not new log structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_LOG+" WHERE id='"+std::to_string(log.id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New device structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

bool DBDriver::LOG_remove(int id)
{
  if(this->db.isConnected())
  {
    if(id > 0) //Not new log structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_LOG+" WHERE id='"+std::to_string(id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New log structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

struct DBDriver::Log DBDriver::LOG_getById(int id)
{
  struct Log log;
  if(this->db.isConnected())
  {
    if(id > 0) //Not new log structure
    {
      std::string cmd = (std::string)"SELECT 'id','date','type','category','message','display' FROM "+this->TABLE_LOG+" WHERE id='"+std::to_string(id)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 6)
  			{
			    int i = atoi(row[0]);
  				if(i==id)
					{
            log.id = atoi(row[0]);
            log.date = (std::string)row[1];
            log.type = (short)atoi(row[2]);
            log.category = (std::string)row[3];
            log.message = (std::string)row[4];
            log.display = (short)atoi(row[5]);
						break;
					}
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
				}
  		}
      mysql_free_result(result);
    }
    else //New log structure
    {
      return log;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return log;
  }
  return log;
}

bool DBDriver::LOG_mark(int id,short display)
{
  if(this->db.isConnected())
  {
    if(id > 0) //Not new log structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_LOG+" SET 'display'='"+this->db.parse(std::to_string(display))
      +"' WHERE id='"+std::to_string(id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New log structure
    {
      return false;
    }
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}

std::vector<struct DBDriver::Log> DBDriver::LOG_list()
{
  std::vector<struct Log> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','date','type','category','message','display' FROM "+this->TABLE_LOG+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 6)
  			{
          struct Log log;

          log.id = atoi(row[0]);
          log.date = (std::string)row[1];
          log.type = (short)atoi(row[2]);
          log.category = (std::string)row[3];
          log.message = (std::string)row[4];
          log.display = (short)atoi(row[5]);

          buff.push_back(log);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}

std::vector<struct DBDriver::Log> DBDriver::LOG_getByType(short type)
{
  std::vector<struct Log> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','date','type','category','message','display' FROM "+this->TABLE_LOG+" WHERE 'type'='"+std::to_string(type)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 6)
  			{
          struct Log log;

          log.id = atoi(row[0]);
          log.date = (std::string)row[1];
          log.type = (short)atoi(row[2]);
          log.category = (std::string)row[3];
          log.message = (std::string)row[4];
          log.display = (short)atoi(row[5]);

          buff.push_back(log);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}

std::vector<struct DBDriver::Log> DBDriver::LOG_getByCategory(std::string category)
{
  std::vector<struct Log> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','date','type','category','message','display' FROM "+this->TABLE_LOG+" WHERE 'category'='"+category+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 6)
  			{
          struct Log log;

          log.id = atoi(row[0]);
          log.date = (std::string)row[1];
          log.type = (short)atoi(row[2]);
          log.category = (std::string)row[3];
          log.message = (std::string)row[4];
          log.display = (short)atoi(row[5]);

          buff.push_back(log);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}

std::vector<struct DBDriver::Log> DBDriver::LOG_getForDisplay()
{
  std::vector<struct Log> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','date','type','category','message','display' FROM "+this->TABLE_LOG+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 6)
  			{
          struct Log log;

          log.id = atoi(row[0]);
          log.date = (std::string)row[1];
          log.type = (short)atoi(row[2]);
          log.category = (std::string)row[3];
          log.message = (std::string)row[4];
          log.display = (short)atoi(row[5]);

          buff.push_back(log);
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
          return buff;
				}
  		}
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}



/*
*     GroupList section
*/

bool DBDriver::GROUPLIST_create(struct DBDriver::GroupList gl)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_GROUPLIST+" ('name') "
      +"VALUES ('"+this->db.parse(gl.name)+"');";
    return this->db.execNonQuery(cmd);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPLIST_update(struct DBDriver::GroupList gl)
{
  if(this->db.isConnected())
  {
    if(gl.id > 0) //Not new GroupList structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_GROUPLIST+" SET 'name'='"+this->db.parse(gl.name)+"' "+"WHERE id='"+std::to_string(gl.id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupList structure
    {
      this->GROUPLIST_create(gl);
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPLIST_remove(struct DBDriver::GroupList gl)
{
  if(this->db.isConnected())
  {
    if(gl.id > 0) //Not new GroupList structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_GROUPLIST+" WHERE id='"+std::to_string(gl.id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupList structure
    {
      return false;
    }
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPLIST_remove(int pId)
{
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new groupId structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_GROUPLIST+" WHERE id='"+std::to_string(pId)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupList structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
struct DBDriver::GroupList DBDriver::GROUPLIST_getById(int pId)
{
  struct GroupList gl;
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new GroupList structure
    {
      std::string cmd = (std::string)"SELECT 'id','name' FROM "+this->TABLE_GROUPLIST+" WHERE id='"+std::to_string(pId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 2)
  			{
			    int i = atoi(row[0]);
  				if(i==pId)
					{
            gl.id = atoi(row[0]);
            gl.name = (std::string)row[1];
						break;
					}
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
				}
  		}
      mysql_free_result(result);
    }
    else //New GroupList structure
    {
      return gl;
    }
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return gl;
  }
  return gl;
}
struct DBDriver::GroupList DBDriver::GROUPLIST_getByName(std::string pName)
{
  struct GroupList gl;
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"SELECT 'id','name' FROM "+this->TABLE_GROUPLIST+" WHERE name='"+this->db.parse(pName)+"';";
    MYSQL_RES *result =  this->db.execQuery(cmd);
    MYSQL_ROW row;
    int num_fields = mysql_num_fields(result);
    while((row = mysql_fetch_row(result)))
    {
      if(num_fields >= 2)
      {
        gl.id = atoi(row[0]);
        gl.name = (std::string)row[1];
        break;
      }else{
        mysql_free_result(result);
        throw DBDriverException(0,"Not enough fields");
      }
    }
    mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return gl;
  }
  return gl;
}
std::vector<struct DBDriver::GroupList> DBDriver::GROUPLIST_list()
{
  std::vector<struct GroupList> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','name' FROM "+this->TABLE_GROUPLIST+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 2)
        {
          struct GroupList gl;
          gl.id = atoi(row[0]);
          gl.name = (std::string)row[1];
          buff.push_back(gl);
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
          return buff;
        }
      }
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}

/*
*     GroupMember section
*/
bool DBDriver::GROUPMEMBER_create(struct DBDriver::GroupMember gm)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_GROUPMEMBERS+" ('group_id','object_id') "
      +"VALUES ('"+std::to_string(gm.group_id)+"','"+this->db.parse(gm.object_id)+"');";
    return this->db.execNonQuery(cmd);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPMEMBER_update(struct DBDriver::GroupMember gm)
{
  if(this->db.isConnected())
  {
    if(gm.id > 0) //Not new GroupMember structure
    {
      std::string cmd = (std::string)"UPDATE "+this->TABLE_GROUPMEMBERS+" SET 'group_id'='"+std::to_string(gm.group_id)+"','object_id'='"+this->db.parse(gm.object_id)+"' "+"WHERE id='"+std::to_string(gm.id)+"'";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupMember structure
    {
      this->GROUPMEMBER_create(gm);
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPMEMBER_remove(struct DBDriver::GroupMember gm)
{
  if(this->db.isConnected())
  {
    if(gm.id > 0) //Not new GroupMember structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_GROUPMEMBERS+" WHERE id='"+std::to_string(gm.id)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupMember structure
    {
      return false;
    }
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
bool DBDriver::GROUPMEMBER_remove(int pId)
{
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new GroupMember structure
    {
      std::string cmd = (std::string)"REMOVE FROM "+this->TABLE_GROUPMEMBERS+" WHERE id='"+std::to_string(pId)+"';";
      return this->db.execNonQuery(cmd);
    }
    else //New GroupMember structure
    {
      return false;
    }

  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return false;
  }
  return false;
}
struct DBDriver::GroupMember DBDriver::GROUPMEMBER_getById(int pId)
{
  struct GroupMember gm;
  if(this->db.isConnected())
  {
    if(pId > 0) //Not new GroupList structure
    {
      std::string cmd = (std::string)"SELECT 'id','group_id','object_id' FROM "+this->TABLE_GROUPMEMBERS+" WHERE id='"+std::to_string(pId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 3)
  			{
			    int i = atoi(row[0]);
  				if(i==pId)
					{
            gm.id = atoi(row[0]);
            gm.group_id = atoi(row[1]);
            gm.object_id = (std::string)row[2];
						break;
					}
        }else{
					mysql_free_result(result);
					throw DBDriverException(0,"Not enough fields");
				}
  		}
      mysql_free_result(result);
    }
    else //New GroupMember structure
    {
      return gm;
    }
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return gm;
  }
  return gm;
}
std::vector<struct DBDriver::GroupMember> DBDriver::GROUPMEMBER_list()
{
  std::vector<struct GroupMember> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','group_id','object_id' FROM "+this->TABLE_GROUPMEMBERS+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 3)
        {
          struct GroupMember gm;
          gm.id = atoi(row[0]);
          gm.group_id = atoi(row[1]);
          gm.object_id = (std::string)row[2];
          buff.push_back(gm);
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
          return buff;
        }
      }
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}
std::vector<struct DBDriver::GroupMember> DBDriver::GROUPMEMBER_getByGroupId(int pGroupId)
{
  std::vector<struct GroupMember> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','group_id','object_id' FROM "+this->TABLE_GROUPMEMBERS+" WHERE group_id='"+std::to_string(pGroupId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 3)
        {
          struct GroupMember gm;
          gm.id = atoi(row[0]);
          gm.group_id = atoi(row[1]);
          gm.object_id = (std::string)row[2];
          buff.push_back(gm);
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
          return buff;
        }
      }
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}
std::vector<struct DBDriver::GroupMember> DBDriver::GROUPMEMBER_getByObjectId(std::string pObjectId)
{
  std::vector<struct GroupMember> buff;

  if(this->db.isConnected())
  {
      std::string cmd = (std::string)"SELECT 'id','group_id','object_id' FROM "+this->TABLE_GROUPMEMBERS+" WHERE object_id='"+this->db.parse(pObjectId)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      MYSQL_ROW row;
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
        if(num_fields >= 3)
        {
          struct GroupMember gm;
          gm.id = atoi(row[0]);
          gm.group_id = atoi(row[1]);
          gm.object_id = (std::string)row[2];
          buff.push_back(gm);
        }else{
          mysql_free_result(result);
          throw DBDriverException(0,"Not enough fields");
          return buff;
        }
      }
      mysql_free_result(result);
  }
  else
  {
    throw DBDriverException(0,"Not connected to database");
    return buff;
  }
  return buff;
}
