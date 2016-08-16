#include "DBDriver.h"


/*
*     DEVICE section
*/


bool DBDriver::DEVICE_create(struct DBDriver::Device dev)
{
  if(this->db.isConnected())
  {
    std::string cmd = (std::string)"INSERT INTO "+this->TABLE_DEVICES+" ('serialNumber','key','token','challenge','address','helloInterval','lastTalk','approved') "
      +"VALUES ('"+this->db.parse(dev.serialNumber)+"','"+this->db.parse(dev.key)
      +"','"+this->db.parse(dev.token)+"','"+this->db.parse(dev.challenge)
      +"','"+this->db.parse(dev.address)+"','"+std::to_string(dev.helloInterval)
      +"','"+this->db.parse(dev.lastTalk)+"','"+std::to_string(dev.approved)+"');";
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
      std::string cmd = (std::string)"UPDATE "+this->TABLE_DEVICES+" SET 'serialNumber'='"+this->db.parse(dev.serialNumber)
        +"','key'='"+this->db.parse(dev.key)+"','token'='"+this->db.parse(dev.token)+"','challenge'='"+this->db.parse(dev.challenge)
        +"','address'='"+this->db.parse(dev.address)+"','helloInterval'='"+std::to_string(dev.helloInterval)
        +"','lastTalk'='"+this->db.parse(dev.lastTalk)+"','approved'='"+std::to_string(dev.approved)+"' "
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
      std::string cmd = (std::string)"SELECT 'id','serialNumber','key','token','challenge','address','helloInterval','approved' FROM "+this->TABLE_DEVICES+" WHERE id='"+std::to_string(id)+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 8)
  			{
			    int i = atoi(row[0]);
  				if(i==id)
					{
            dev.id = atoi(row[0]);
            dev.serialNumber = (std::string)row[1];
            dev.key = (std::string)row[2];
            dev.token = (std::string)row[3];
            dev.challenge = (std::string)row[4];
            dev.address = (std::string)row[5];
            dev.helloInterval = atoi(row[6]);
            dev.approved = (bool)atoi(row[7]);
						break;
					}
        }else{
					mysql_free_result(result);
					throw DatabseException(0,"Not enough fields");
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
      std::string cmd = (std::string)"SELECT 'id','serialNumber','key','token','challenge','address','helloInterval','approved' FROM "+this->TABLE_DEVICES+" WHERE serialNumber='"+_serialNumber+"';";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 8)
  			{
			    std::string i(row[1]);
  				if(i==_serialNumber)
					{
            dev.id = atoi(row[0]);
            dev.serialNumber = (std::string)row[1];
            dev.key = (std::string)row[2];
            dev.token = (std::string)row[3];
            dev.challenge = (std::string)row[4];
            dev.address = (std::string)row[5];
            dev.helloInterval = atoi(row[6]);
            dev.approved = (bool)atoi(row[7]);
						break;
					}
        }else{
					mysql_free_result(result);
					throw DatabseException(0,"Not enough fields");
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
      std::string cmd = (std::string)"SELECT 'id','serialNumber','key','token','challenge','address','helloInterval','approved' FROM "+this->TABLE_DEVICES+";";
      MYSQL_RES *result =  this->db.execQuery(cmd);
      int num_fields = mysql_num_fields(result);
      while((row = mysql_fetch_row(result)))
      {
  			if(num_fields >= 8)
  			{
          struct Device dev;

          dev.id = atoi(row[0]);
          dev.serialNumber = (std::string)row[1];
          dev.key = (std::string)row[2];
          dev.token = (std::string)row[3];
          dev.challenge = (std::string)row[4];
          dev.address = (std::string)row[5];
          dev.helloInterval = atoi(row[6]);
          dev.approved = (bool)atoi(row[7]);

          buff.push_back(dev);
        }else{
					mysql_free_result(result);
					throw DatabseException(0,"Not enough fields");
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
					throw DatabseException(0,"Not enough fields");
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
      return false
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
					throw DatabseException(0,"Not enough fields");
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
					throw DatabseException(0,"Not enough fields");
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
					throw DatabseException(0,"Not enough fields");
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
					throw DatabseException(0,"Not enough fields");
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
