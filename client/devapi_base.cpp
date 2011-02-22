static const char *RcsId = "$Id$\n$Name$";
//
// devapi_base.cpp 	- C++ source code file for TANGO device api 
//
// programmer(s)	- Andy Gotz (goetz@esrf.fr)
//
// original 		- March 2001
//
// log			- $Log$
// log			- Revision 3.6.2.6  2004/02/06 11:57:04  taurel
// log			- - Many changes in the event system
// log			-
// log			- Revision 3.6.2.5  2004/01/20 08:30:07  taurel
// log			- -First commit after merge with the event branch and work on the AttributeProxy class
// log			- - Fix bug in the stream "clear()" method usage when used with gcc 3.3
// log			-
// log			- Revision 3.6.2.4  2003/12/10 16:07:39  taurel
// log			- Last commit before merging with the event branch.
// log			-
// log			- Revision 3.6.2.3  2003/10/16 11:58:17  taurel
// log			- - Fix some memory leaks in DeviceProxy::is_polled() and in
// log			- Database::get_device_exported() methods
// log			- - Add some bug fixes in Database::get_device_attribute_property(),
// log			- Database::put_class_attribute_property()
// log			-
// log			- Revision 3.6.2.2  2003/10/02 14:53:42  taurel
// log			- Forgot to copy the Connection class copy constructor from Main trunck !
// log			-
// log			- Revision 3.6.2.1  2003/09/18 14:07:41  taurel
// log			- Fixes some bugs:
// log			-  - Bug fix in DeviceProxy copy constructor and assignement operator
// log			-  - Change the way how DeviceProxy::write_attribute() is coded
// log			-  - Added DeviceAttribute ctors from "const char *"
// log			-  - Split "str().c_str()" in two lines of code. It was the reason of some
// log			-    problems using Windows VC6
// log			-
// log			- Revision 3.6  2003/05/28 14:42:56  taurel
// log			- Add (conditionaly) autoconf generated include file
// log			-
// log			- Revision 3.5  2003/05/16 08:48:02  taurel
// log			- Many changes for release 3.0.1. The most important ones are :
// log			- - Timeout are backs
// log			- - Multiple db servers (change in TANGO_HOST syntax)
// log			- - Added methods to print DeviceData, DeviceDataHistory, DeviceAttribute and DeviceAttributeHistory instances
// log			- - Attributes name stored in blackbox
// log			- - Remove check if a class is created without any device
// log			- - It's now possible to create a DeviceProxy from its alias name
// log			- - Command, attribute names are case insensitive
// log			- - Change parameters of some DeviceProxy logging methods
// log			- - Change parameters of DeviceProxy asynchronous replies calls
// log			- - New serialization model in device server (no serialization model)
// log			- - Win32 (2000) device server service does not exit at loggoff anymore
// log			- - Miscellaneous bug fixes
// log			-
// log			- Revision 3.4  2003/04/28 08:34:26  nleclercq
// log			- Changed add/remove_logging_target parameter to type::name
// log			-
// log			- Revision 3.3  2003/04/08 15:08:57  taurel
// log			- - Fix bug in reconnection algo.
// log			-
// log			- Revision 3.2  2003/04/03 15:21:53  taurel
// log			- Added methods to print DeviceData, DeviceAttribute, DeviceDataHistory
// log			- and DeviceAttributeHistory instance
// log			-
// log			- Revision 3.1  2003/04/02 12:22:07  taurel
// log			- Miscellaneous changes to :
// log			-  - Modify TANGO_HOST env. variable syntax to be able to have several db servers
// log			-  - Asynchronous calls are now done on device_2 or device depending on the device IDL version
// log			-  - Timeout are bcks (omniORB 4.0.1)
// log			-  - Fix bug when killing a device server via the kill command of the admin device
// log			-    (Solaris only)
// log			-  - Cleanup device server code to have only one ORB and one db connection within a server
// log			-
// log			- Revision 3.0  2003/03/25 16:30:42  taurel
// log			- Change revision number to 3.0 before release 3.0.0 of Tango lib
// log			-
// log			- Revision 2.8  2003/03/25 16:28:12  taurel
// log			- Fix a comment spelling mistake !!!
// log			-
// log			- Revision 2.7  2003/03/20 08:54:54  taurel
// log			- Updated to support asynchronous calls
// log			-
// log			- Revision 2.6  2003/03/11 17:52:00  nleclercq
// log			- Switch from log4cpp to log4tango
// log			-
// log			- Revision 2.5  2003/02/17 15:02:01  taurel
// log			- Added the new Tango logging stuff (Thanks Nicolas from Soleil)
// log			-
// log			- Revision 2.4  2003/01/09 12:00:33  taurel
// log			- - Ported to gcc 3.2
// log			- - Added ApiUtil::cleanup() and ApiUtil::~ApiUtil() methods
// log			- - Replace some ORB * by ORB_ptr
// log			- - Use CORBA::ORB::is_nil() instead of comparing to NULL
// log			-
// log			- Revision 2.3  2002/12/16 11:58:36  taurel
// log			- - Change the underlying ORB fom ORBacus to omniORB
// log			- - New method get_device_list() in Util class
// log			- - Util::get_class_list() takes DServer device into account
// log			- - Util::get_device_by_name() takes DSErver device into account
// log			- - Util::get_device_list_by_class() takes DServer device into account
// log			- - New parameter to the attribute::set_value() method to ebnable CORBA to frre memory allocated for the attribute
// log			-
// log			- Revision 2.2  2002/10/14 09:32:43  taurel
// log			- Fix bugs in devapi_base.cpp file :
// log			- - In read_attribute and read_attributes method of the DeviceProxy class
// log			-   Do not create sequence the same way if the call is local or remote.
// log			- - Add reconnection in the Connection::set_timeout_millis method
// log			- - Add flags to the Connection::set_timeout_millis method
// log			- - Fix bug in the DeviceProxy constructor when device is not marked as exported
// log			-   in the database. The constructor was not stateless in this case.
// log			-
// log			- Revision 2.1  2002/08/12 12:43:24  taurel
// log			- Fix bug in DeviceProxy::write_attributes method when writing several
// log			- attributes in one call. (File devapi_base.cpp)
// log			-
// log			- Revision 2.0  2002/06/28 13:43:08  taurel
// log			- Lot of changes since last releases :
// log			- 	- Database object managed as a singleton per control system
// log			- 	- Support all tango device naming syntax (using TANGO_HOST env.
// log			-  	  variable, without env variable and non database device)
// log			- 	- No more copy during read_attribute and command_inout
// log			- 	- Added some missing methods
// log			- 	- Build an exception class hierarchy
// log			- 	- Added correct management of device time-out
// log			- 	- Support all Tango device interface release 2 features
// log			- 	  (data/attribute comming from polling buffer, polling related methods,
// log			- 	   command/attribute result history)
// log			-

#if HAVE_CONFIG_H
#include <ac_config.h>
#endif

#include <tango.h>

#ifdef WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif /* WIN32 */

#include <time.h>
#include <signal.h>

#include <algorithm>
                                                    
using namespace CORBA;

namespace Tango
{

//-----------------------------------------------------------------------------
//
// Connection::Connection() - constructor to manage a connection to a device
//
//-----------------------------------------------------------------------------

Connection::Connection(ORB *orb_in):pasyn_ctr(0),pasyn_cb_ctr(0),
				    timeout(CLNT_TIMEOUT),
				    timeout_changed(0),
				    version(0),source(Tango::CACHE_DEV)
{

	ext = new ConnectionExt();

//
// If the proxy is created from inside a device server, use the server orb
//

	ApiUtil *au = ApiUtil::instance();		
	if ((orb_in == NULL) && (CORBA::is_nil(au->get_orb()) == true)) 
	{
		if (au->in_server() == true)
			ApiUtil::instance()->set_orb(Util::instance()->get_orb());
		else
			ApiUtil::instance()->create_orb();
	}
	else
	{
		if (orb_in != NULL)
			au->set_orb(orb_in);
	}
}

//-----------------------------------------------------------------------------
//
// Connection::~Connection() - destructor to destroy connection to TANGO device
//
//-----------------------------------------------------------------------------

Connection::~Connection()
{
	if (ext != NULL)
		delete ext;
}

//-----------------------------------------------------------------------------
//
// Connection::Connection() - copy constructor
//
//-----------------------------------------------------------------------------

Connection::Connection(const Connection &sou)
{
	dbase_used = sou.dbase_used;
	from_env_var = sou.from_env_var;	
	host = sou.host;
	port = sou.port;
	port_num = port_num;
	
	db_host = sou.db_host;
	db_port = sou.db_port;
	db_port_num = sou.db_port_num;
	
	ior = sou.ior;
	pasyn_ctr = sou.pasyn_ctr;
	pasyn_cb_ctr = sou.pasyn_cb_ctr;
		
	device = sou.device;
	if (sou.version >= 2)
		device_2 = sou.device_2;
	
	timeout = sou.timeout;
	timeout_changed = sou.timeout_changed;
	
	connection_state = sou.connection_state;
	version = sou.version;
	source = sou.source;

	if (sou.ext != NULL)
	{
		ext = new ConnectionExt();
		*ext = *(sou.ext);
	}
	else
		ext = NULL;
}

//-----------------------------------------------------------------------------
//
// Connection::connect() - method to create connection to a TANGO device 
//		using it's stringified CORBA reference i.e. IOR or corbaloc
//
//-----------------------------------------------------------------------------

void Connection::connect(string &corba_name)
{
	try
	{
//
// narrow CORBA string name to CORBA object
//

        	Object_var obj;
		obj = ApiUtil::instance()->get_orb()->string_to_object(corba_name.c_str());

		version = 1;
		device = Device::_narrow(obj.in());

        	if (CORBA::is_nil(device))
        	{
        		cerr << "Can't build connection to object " << corba_name << " (idl release 1)" << endl;
			
			connection_state = CONNECTION_NOTOK;
			
			TangoSys_OMemStream desc;
			desc << "Failed to connect to device " << dev_name();
			desc << " (device nil after _narrowing)" << ends;
                	ApiConnExcept::throw_exception((const char*)"API_CantConnectToDevice",
                        			       desc.str(),
						       (const char*)"Connection::connect()");
        	}
		
//
// Also initialise device_2 if it supports IDL release 2
//

		if (obj->_is_a("IDL:Tango/Device_2:1.0") == true)
		{
			version = 2;
			device_2 = Device_2::_narrow(obj);

        		if (CORBA::is_nil(device_2))
        		{
        			cerr << "Can't build connection to object " << corba_name << " (idl release 2)" << endl;
			
				connection_state = CONNECTION_NOTOK;
			
				TangoSys_OMemStream desc;
				desc << "Failed to connect to device " << dev_name();
				desc << " (device nil after _narrowing)" << ends;
                		ApiConnExcept::throw_exception((const char*)"API_CantConnectToDevice",
                        			       desc.str(),
						       (const char*)"Connection::connect()");
        		}
		}
		
// Mark the connection as OK and set timeout to its value
// (The default is 3 seconds)

		connection_state = CONNECTION_OK;

		if (timeout != CLNT_TIMEOUT)		
			set_timeout_millis(timeout);
#ifdef WIN32
		timeout_changed = 0;
#endif

	}
        catch (CORBA::SystemException &ce)
        {			
		TangoSys_OMemStream desc;
		TangoSys_MemStream reason;
		desc << "Failed to connect to ";
			
		string::size_type pos = corba_name.find(':');
		if (pos == string::npos)
		{
			desc << "device " << dev_name() << ends;
			reason << "API_CantConnectToDevice" << ends;
		}
		else
		{
			string prot = corba_name.substr(0,pos);
			if (prot == "corbaloc")
			{
				string::size_type tmp = corba_name.find('/');
				if (tmp != string::npos)
				{
					string dev = corba_name.substr(tmp + 1);
					if (dev == "database")
					{
						desc << "database on host ";
						desc << db_host << " with port ";
						desc << db_port << ends;
						reason << "API_CantConnectToDatabase" << ends;
					}
					else
					{
						CORBA::SystemException *se;
						desc << "device " << dev_name() << ends;
						if ((se = CORBA::OBJECT_NOT_EXIST::_downcast(&ce)) != 0)
							reason << "API_DeviceNotDefined" << ends;
						else if ((se = CORBA::TRANSIENT::_downcast(&ce)) != 0)
							reason << "API_ServerNotRunning" << ends;
						else
							reason << "API_CantConnectToDevice" << ends;
					}
				}
				else
				{
					desc << "device " << dev_name() << ends;
					reason << "API_CantConnectToDevice" << ends;
				}
			}
			else
			{
				desc << "device " << dev_name() << ends;
				reason << "API_CantConnectToDevice" << ends;
			}
		}
						
		ApiConnExcept::re_throw_exception(ce,reason.str(),desc.str(),
					          (const char *)"Connection::connect");
	}
	
}


//-----------------------------------------------------------------------------
//
// Connection::reconnect() - reconnect to a CORBA object
//
//-----------------------------------------------------------------------------

void Connection::reconnect(bool db_used)
{

	if (connection_state != CONNECTION_OK)
	{
		string corba_name;
		if (db_used == true)
			corba_name = get_corba_name();
		else
			corba_name = build_corba_name();

		connect(corba_name);
	}

//
// Try to ping the device. With omniORB, it is possible that the first
// real access to the device is done when a call to one of the interface
// operation is done. Do it now.
//
	
	try
	{
		device->ping();
	}
	catch (CORBA::SystemException &ce)
	{
		connection_state = CONNECTION_NOTOK;
		
		TangoSys_OMemStream desc;
		desc << "Failed to connect to device " << dev_name() << ends;
								
		ApiConnExcept::re_throw_exception(ce,
						  (const char *)"API_CantConnectToDevice",
						  desc.str(),
					          (const char *)"Connection::reconnect");
	}
}

//-----------------------------------------------------------------------------
//
// Connection::get_timeout_millis() - public method to get timeout on a TANGO device
//
//-----------------------------------------------------------------------------

int Connection::get_timeout_millis()
{
	return(timeout);
}


//-----------------------------------------------------------------------------
//
// Connection::set_timeout_millis() - public method to set timeout on a TANGO device
//
//-----------------------------------------------------------------------------

void Connection::set_timeout_millis(int millisecs)
{

	if (connection_state != CONNECTION_OK) reconnect(dbase_used);
	
	omniORB::setClientCallTimeout(device,millisecs);
	
	if (version == 2)
	{
		omniORB::setClientCallTimeout(device_2,millisecs);
	}
	
	timeout = millisecs;
	
/*
#ifdef WIN32
	timeout_changed++;
#endif*/
}


//-----------------------------------------------------------------------------
//
// Connection::command_inout() - public method to execute a command on a TANGO device
//
//-----------------------------------------------------------------------------


DeviceData Connection::command_inout(string &command)
{
	DeviceData data_in;

	return(command_inout(command,data_in));
}

//-----------------------------------------------------------------------------
//
// Connection::command_inout() - public method to execute a command on a TANGO device
//
//-----------------------------------------------------------------------------


DeviceData Connection::command_inout(string &command, DeviceData &data_in)
{

//
// We are using a pointer to an Any as the return value of the command_inout
// call. This is because the assignament to the Any_var any in the
// DeviceData object in faster in this case (no copy).
// Don't forget that the any_var in the DeviceData takes ownership of the
// memory allocated 
//

	DeviceData data_out;
	int ctr = 0;
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			CORBA::Any *received;
			if (version == 2)
				received = device_2->command_inout_2(command.c_str(),data_in.any,source);
			else
				received = device->command_inout(command.c_str(),data_in.any);

			ctr = 2;
			data_out.any = received;
		}
		catch (Tango::ConnectionFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
                	ApiConnExcept::re_throw_exception(e,(const char*)"API_CommandFailed",
                        	desc.str(), (const char*)"Connection::command_inout()");
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
                	Except::re_throw_exception(e,(const char*)"API_CommandFailed",
                        	desc.str(), (const char*)"Connection::command_inout()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT_CMD(trans);		
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                        			   desc.str(),
						   (const char*)"Connection::command_inout()");
		}
	}
	
	return data_out;
}

//-----------------------------------------------------------------------------
//
// Connection::command_inout() - public method to execute a command on a TANGO device
//				 using low level CORBA types
//
//-----------------------------------------------------------------------------


CORBA::Any_var Connection::command_inout(string &command, CORBA::Any &any)
{
	int ctr = 0;
	
	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			if (version == 2)
				return (device_2->command_inout_2(command.c_str(),any,source));
			else
				return (device->command_inout(command.c_str(),any));
			ctr = 2;
		}
		catch (Tango::ConnectionFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
                	ApiConnExcept::re_throw_exception(e,(const char*)"API_CommandFailed",
                        	desc.str(), (const char*)"Connection::command_inout()");
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
                	Except::re_throw_exception(e,(const char*)"API_CommandFailed",
                        	desc.str(), (const char*)"Connection::command_inout()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT_CMD(trans);
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute command_inout on device " << dev_name();
			desc << ", command " << command << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                        			   desc.str(),
						   (const char*)"Connection::command_inout()");
		}
	}
//
// Just to make VC++ quiet (will never reach this code !)
//

#ifdef WIN32
	CORBA::Any_var tmp;
	return tmp;
#endif
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::DeviceProxy() - constructor for device proxy object 
//
//-----------------------------------------------------------------------------

DeviceProxy::DeviceProxy (string &name, CORBA::ORB *orb) : Connection(orb),
							   alias(false),
							   adm_device(NULL)
{
	real_constructor(name);
}

DeviceProxy::DeviceProxy (const char *na, CORBA::ORB *orb) : Connection(orb),
							     alias(false),
							     adm_device(NULL)
{
	string name(na);
	real_constructor(name);
}

void DeviceProxy::real_constructor (string &name)
{

//
// parse device name
//

	parse_name(name);
	string corba_name;
	bool exported = true;
		
	if (dbase_used == true)
	{
		try
		{
			if (from_env_var == true)
			{	
				ApiUtil *ui = ApiUtil::instance();
				db_dev = new DbDevice(device_name);
				int ind = ui->get_db_ind();
				db_host = (ui->get_db_vect())[ind]->get_db_host();
				db_port = (ui->get_db_vect())[ind]->get_db_port();
				db_port_num = (ui->get_db_vect())[ind]->get_db_port_num();
			}
			else
			{
				db_dev = new DbDevice(device_name,db_host,db_port);
			}
		}
		catch (Tango::DevFailed &e)
		{
			if (strcmp(e.errors[0].reason.in(),"API_TangoHostNotSet") == 0)
			{
				cerr << e.errors[0].desc.in() << endl;
			}
			throw;
		}

		try
		{		
			corba_name = get_corba_name();
		}
		catch (Tango::DevFailed &dfe)
		{
			if (strcmp(dfe.errors[0].reason,"DB_DeviceNotDefined") == 0)
			{
				delete db_dev;
				TangoSys_OMemStream desc;
				desc << "Can't connect to device " << device_name << ends;
				ApiConnExcept::re_throw_exception(dfe,
						(const char *)"API_DeviceNotDefined",
					 	desc.str(),
						(const char *)"DeviceProxy::DeviceProxy");
			}
			else if (strcmp(dfe.errors[0].reason,"API_DeviceNotExported") == 0)
				exported = false;
		}
	}
	else
	{
		corba_name = build_corba_name();
	}

//
// Implement stateless new() i.e. even if connect fails continue
// If the DeviceProxy was created using device alias, ask for the real
// device name.
//
	try
	{
		if (exported == true)
		{
			connect(corba_name);
			
			if (alias == true)
			{
				CORBA::String_var real_name = device->name();
				device_name = real_name.in();
				db_dev->set_name(device_name);
			}
		}
	}
        catch (Tango::ConnectionFailed &dfe)
	{
		connection_state = CONNECTION_NOTOK;
		if (dbase_used == false)
		{
			if (strcmp(dfe.errors[1].reason,"API_DeviceNotDefined") == 0)
				throw;
		}
	}
        catch (CORBA::SystemException &) 
	{
		connection_state = CONNECTION_NOTOK;
		if (dbase_used == false)
			throw;
	}
	
//
// For non-database device , try to ping them. It's the only way to know that 
// the device is not defined
//

	if (dbase_used == false)
	{
		try
		{
			ping();
		}
		catch (Tango::ConnectionFailed &dfe)
		{
			if (strcmp(dfe.errors[1].reason,"API_DeviceNotDefined") == 0)
				throw;
		}
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::DeviceProxy() - copy constructor
//
//-----------------------------------------------------------------------------

DeviceProxy::DeviceProxy(const DeviceProxy &sou):Connection(sou)
{
	
//
// Copy DeviceProxy members
//
	
	device_name = sou.device_name;
	alias_name = sou.alias_name;
	alias = sou.alias;
			
	if (dbase_used == true)
	{
		if (from_env_var == true)
		{	
			ApiUtil *ui = ApiUtil::instance();
			if (ui->in_server() == true)
				db_dev = new DbDevice(device_name,Tango::Util::instance()->get_database());
			else
				db_dev = new DbDevice(device_name);
		}
		else
		{
			db_dev = new DbDevice(device_name,db_host,db_port);
		}
	}

//
// Copy adm device pointer
//
		
	if (sou.adm_device == NULL)
		adm_device = NULL;
	else
	{
		adm_device = new DeviceProxy(sou.adm_device->dev_name().c_str());
	}
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::DeviceProxy() - assignement operator 
//
//-----------------------------------------------------------------------------

DeviceProxy &DeviceProxy::operator=(const DeviceProxy &rval)
{

//
// First Connection class members
//
	if (dbase_used == true)
		delete db_dev;
	dbase_used = rval.dbase_used;
	from_env_var = rval.from_env_var;
	host = rval.host;
	port = rval.port;
	port_num = rval.port_num;
	db_host = rval.db_host;
	db_port = rval.db_port;
	db_port_num = rval.db_port_num;
	ior = rval.ior;
	pasyn_ctr = rval.pasyn_ctr;
	pasyn_cb_ctr = rval.pasyn_cb_ctr;
	device = rval.device;
	device_2 = rval.device_2;
	timeout = rval.timeout;
	timeout_changed = rval.timeout_changed;
	connection_state = rval.connection_state;
	version = rval.version;
	source = rval.source;
	
//
// Now DeviceProxy members
//
	
	device_name = rval.device_name;
			
	if (dbase_used == true)
	{
		if (from_env_var == true)
		{	
			ApiUtil *ui = ApiUtil::instance();
			if (ui->in_server() == true)
				db_dev = new DbDevice(device_name,Tango::Util::instance()->get_database());
			else
				db_dev = new DbDevice(device_name);
		}
		else
		{
			db_dev = new DbDevice(device_name,db_host,db_port);
		}
	}
	
	if (adm_device != NULL)
		delete adm_device;
	if (rval.adm_device != NULL)
	{
		adm_device = new DeviceProxy(rval.adm_device->dev_name().c_str());
	}
	else
		adm_device = NULL;
	
	return *this;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::parse_name() - Parse device name according to Tango device
//			       name syntax
//
// in :	- full_name : The device name
//
//-----------------------------------------------------------------------------

void DeviceProxy::parse_name(string &full_name)
{
	string name_wo_prot;
	string name_wo_db_mod;
	string dev_name,object_name;

//
// Device name in lower case letters
//
	
	transform(full_name.begin(),full_name.end(),full_name.begin(),::tolower);
		
//
// Try to find protocol specification in device name and analyse it
//

	string::size_type pos = full_name.find(PROT_SEP);
	if (pos == string::npos)
	{
		name_wo_prot = full_name;
	}
	else
	{
		string protocol = full_name.substr(0,pos);

		if (protocol == TANGO_PROTOCOL)
		{
			name_wo_prot = full_name.substr(pos + 3);
		}		
		else if (protocol == TACO_PROTOCOL)
		{		
			TangoSys_OMemStream desc;
			desc << "Taco protocol is not supported" << ends;
			ApiWrongNameExcept::throw_exception((const char*)"API_UnsupportedProtocol",
						desc.str(),
						(const char*)"DeviceProxy::parse_name()");			exit(0);
		}
		else
		{		
			TangoSys_OMemStream desc;
			desc << protocol;
			desc << " protocol is an unsupported protocol" << ends;
			ApiWrongNameExcept::throw_exception((const char*)"API_UnsupportedProtocol",
						desc.str(),
						(const char*)"DeviceProxy::parse_name()");
		}			
	}

//
// Try to find database database modifier and analyse it
//

	pos = name_wo_prot.find(MODIFIER);
	if (pos != string::npos)
	{
		string mod = name_wo_prot.substr(pos + 1);
		
		if (mod == DBASE_YES)
		{
			string::size_type len = name_wo_prot.size();
			name_wo_db_mod = name_wo_prot.substr(0,len - (len - pos)); 
			dbase_used = true;
		}
		else if (mod == DBASE_NO)
		{
			string::size_type len = name_wo_prot.size();
			name_wo_db_mod = name_wo_prot.substr(0,len - (len - pos));
			dbase_used = false;
		}
		else
		{
			cerr << mod << " is a non supported database modifier!" << endl;

			TangoSys_OMemStream desc;
			desc << mod;
			desc << " modifier is an unsupported db modifier" << ends;
			ApiWrongNameExcept::throw_exception((const char*)"API_UnsupportedDBaseModifier",
						desc.str(),
						(const char*)"DeviceProxy::parse_name()");
		}
	}
	else
	{
		name_wo_db_mod = name_wo_prot;
		dbase_used = true;
	}

	if (dbase_used == false)
	{
	
//
// Extract host name and port number
//

		pos = name_wo_db_mod.find(HOST_SEP);
		if (pos == string::npos)
		{
			cerr << "Host and port not correctly defined in device name " << full_name << endl;

			ApiWrongNameExcept::throw_exception((const char*)"API_WrongDeviceNameSyntax",
						(const char*)"Host and port not correctly defined in device name",
						(const char*)"DeviceProxy::parse_name()");
		}
		
		host = name_wo_db_mod.substr(0,pos);
		string::size_type tmp = name_wo_db_mod.find(PORT_SEP);
		if (tmp == string::npos)
		{
			cerr << "Host and port not correctly defined in device name " << full_name << endl;

			ApiWrongNameExcept::throw_exception((const char*)"API_WrongDeviceNameSyntax",
						(const char*)"Host and port not correctly defined in device name",
						(const char*)"DeviceProxy::parse_name()");
		}
		port = name_wo_db_mod.substr(pos + 1,tmp - pos - 1);
		TangoSys_MemStream s;
		s << port << ends;
		s >> port_num;
		device_name = name_wo_db_mod.substr(tmp + 1);
		
//
// Check device name syntax (domain/family/member). Alias are forbidden without
// using the db
//

		tmp = device_name.find(DEV_NAME_FIELD_SEP);
		if (tmp == string::npos)
		{
			cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			cerr << "Rem: Alias are forbidden when not using database" << endl;
			
			ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
		}
		string::size_type prev_sep = tmp;
		tmp = device_name.find(DEV_NAME_FIELD_SEP,tmp + 1);
		if ((tmp == string::npos) || (tmp == prev_sep + 1))
		{
			cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			cerr << "Rem: Alias are forbidden when not using database" << endl;
			
			ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
		}
		prev_sep = tmp;
		tmp = device_name.find(DEV_NAME_FIELD_SEP,tmp + 1);
		if (tmp != string::npos)
		{
			cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			cerr << "Rem: Alias are forbidden when not using database" << endl;
			
			ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
		}
				
		db_host = db_port = NOT_USED;
		db_port_num = 0;
				 
	}
	else
	{
	
//
// Search if host and port are specified
//

		pos = name_wo_db_mod.find(PORT_SEP);
		if (pos == string::npos)
		{

//
// It could be an alias name, check its syntax
//

			pos = name_wo_db_mod.find(HOST_SEP);
			if (pos != string::npos)
			{
				cerr << "Wrong alias name syntax in " << full_name << " (: is not allowed in alias name)" << endl;
			
				ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong alias name (: not allowed in alias name)",
						(const char *)"DeviceProxy::parse_name()");
			}
			
			pos = name_wo_db_mod.find(RES_SEP);
			if (pos != string::npos)
			{
				cerr << "Wrong alias name syntax in " << full_name << " (-> is not allowed in alias name)" << endl;
			
				ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong alias name (-> not allowed in alias name)",
						(const char *)"DeviceProxy::parse_name()");
			}
			
//
// Alias name syntax OK
//

			alias_name = device_name = name_wo_db_mod;
			alias = true;
			from_env_var = true;
			port_num = 0;
			host = FROM_IOR;
			port = FROM_IOR;
		}
		else
		{
			string bef_sep = name_wo_db_mod.substr(0,pos);
			string::size_type tmp = bef_sep.find(HOST_SEP);
			if (tmp == string::npos)
			{
			
//
// There is at least one / in dev name but it is not a TANGO_HOST definition. 
// A correct dev name must have 2 /. Check this. An alias cannot have any /
//

				if (pos == 0)
				{
					cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			
					ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
				}
				
				string::size_type prev_sep = pos;
				pos = name_wo_db_mod.find(DEV_NAME_FIELD_SEP,pos + 1);
				if ((pos == string::npos) || (pos == prev_sep + 1))
				{
					cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			
					ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
				}
				
				prev_sep = pos;
				pos = name_wo_db_mod.find(DEV_NAME_FIELD_SEP,prev_sep + 1);
				if (pos != string::npos)
				{
					cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			
					ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
				}
										
				device_name = name_wo_db_mod;
				from_env_var = true;
				port_num = 0;
				port = FROM_IOR;
				host = FROM_IOR;
			}
			else
			{
				db_host = bef_sep.substr(0,tmp);
				db_port = bef_sep.substr(tmp + 1);
				TangoSys_MemStream s;
				s << db_port << ends;
				s >> db_port_num;
				object_name = name_wo_db_mod.substr(pos + 1);
				
//
// We should now check if the object name is a device name or an alias
//

				pos = object_name.find(DEV_NAME_FIELD_SEP);
				if (pos == string::npos)
				{
				
//
// It is an alias. Check its syntax
//

					pos = object_name.find(HOST_SEP);
					if (pos != string::npos)
					{
						cerr << "Wrong alias name syntax in " << full_name << " (: is not allowed in alias name)" << endl;
			
						ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong alias name (: not allowed in alias name)",
						(const char *)"DeviceProxy::parse_name()");
					}
			
					pos = object_name.find(RES_SEP);
					if (pos != string::npos)
					{
						cerr << "Wrong alias name syntax in " << full_name << " (-> is not allowed in alias name)" << endl;
			
						ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong alias name (-> not allowed in alias name)",
						(const char *)"DeviceProxy::parse_name()");
					}
					alias_name = device_name = object_name;
					alias = true;
			
//
// Alias name syntax OK, but is it really an alias defined in db ?
//
				}
				else
				{
				
//
// It's a device name. Check its syntax.
// There is at least one / in dev name but it is not a TANGO_HOST definition. 
// A correct dev name must have 2 /. Check this. An alias cannot have any /
//

					string::size_type prev_sep = pos;
					pos = object_name.find(DEV_NAME_FIELD_SEP,pos + 1);
					if ((pos == string::npos) || (pos == prev_sep + 1))
					{
						cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			
						ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
					}

					prev_sep = pos;
					pos = object_name.find(DEV_NAME_FIELD_SEP,prev_sep + 1);
					if (pos != string::npos)
					{
						cerr << "Wrong device name syntax (domain/family/member) in " << full_name << endl;
			
						ApiWrongNameExcept::throw_exception((const char *)"API_WrongDeviceNameSyntax",
						(const char *)"Wrong device name (domain/family/member)",
						(const char *)"DeviceProxy::parse_name()");
					}
								
					device_name = object_name;				
				}
				from_env_var = false;
				port_num = 0;
				port = FROM_IOR;
				host = FROM_IOR;
			}
		}

	}
		
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_corba_name() - return IOR for device from database
//
//-----------------------------------------------------------------------------

string DeviceProxy::get_corba_name()
{
	DbDevImportInfo import_info;

	import_info = db_dev->import_device();

	if (import_info.exported != 1)
	{
		connection_state = CONNECTION_NOTOK;
		
		TangoSys_OMemStream desc;		
		desc << "Device " << device_name << " is not exported (hint: try starting the device server)" << ends;
		ApiConnExcept::throw_exception((const char*)"API_DeviceNotExported",
					       desc.str(),
					       (const char*)"DeviceProxy::get_corba_name()");
	}

	return(import_info.ior);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::build_corba_name() - build corba name for non database device
//				     server. In this case, corba name uses
//				     the "corbaloc" naming schema
//
//-----------------------------------------------------------------------------

string DeviceProxy::build_corba_name()
{

        string db_corbaloc = "corbaloc:iiop:";
        db_corbaloc = db_corbaloc + host + ":" + port;
	db_corbaloc = db_corbaloc + "/" + device_name;

	return db_corbaloc;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::reconnect() - Call the reconnection method and in case
//			      the device has been created from its alias,
//		              get its real name.
//
//-----------------------------------------------------------------------------

void DeviceProxy::reconnect(bool db_used)
{
	Connection::reconnect(db_used);

	if (connection_state == CONNECTION_OK)
	{	
		if (alias == true)
		{
			CORBA::String_var real_name = device->name();
			device_name = real_name.in();
			db_dev->set_name(device_name);
		}
	}
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::import_info() - return import info for device from database
//
//-----------------------------------------------------------------------------

DbDevImportInfo DeviceProxy::import_info()
{
	DbDevImportInfo import_info;
	
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					        desc.str(),
					        (const char *)"DeviceProxy::import_info");
	}
	else
	{
		import_info = db_dev->import_device();
	}

	return(import_info);
}


//-----------------------------------------------------------------------------
//
// DeviceProxy::~DeviceProxy() - destructor to destroy proxy to TANGO device
//
//-----------------------------------------------------------------------------

DeviceProxy::~DeviceProxy()
{
	if (dbase_used == true)
		delete db_dev;
		
	if (adm_device != NULL)
		delete adm_device;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::ping() - ping TANGO device and return time elapsed in microseconds
//
//-----------------------------------------------------------------------------

int DeviceProxy::ping()
{
	int elapsed;

#ifndef WIN32
        struct timeval before, after;

	gettimeofday(&before, NULL);
#else
	struct _timeb before, after;

	_ftime(&before);
#endif /* WIN32 */

	int ctr = 0;
	
	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			device->ping();
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","ping");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;			
			desc << "Failed to execute ping on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                        			   desc.str(),
						   (const char*)"DeviceProxy::ping()");
		}
	}
#ifndef WIN32
	gettimeofday(&after, NULL);
	elapsed = (after.tv_sec-before.tv_sec)*1000000;
	elapsed = (after.tv_usec-before.tv_usec) + elapsed;
#else
	_ftime(&after);
	elapsed = (after.time-before.time)*1000000;
	elapsed = (after.millitm-before.millitm)*1000 + elapsed;
#endif /* WIN32 */

	return(elapsed);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::name() - return TANGO device name as string
//
//-----------------------------------------------------------------------------

string DeviceProxy::name()
{
	string na;
	int ctr = 0;
	
	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			CORBA::String_var n = device->name();
			ctr = 2;
			na = n;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","name");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute name() on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::name()");
		}
	}

	return(na);
}


//-----------------------------------------------------------------------------
//
// DeviceProxy::state() - return TANGO state of device
//
//-----------------------------------------------------------------------------

DevState DeviceProxy::state()
{
	DevState sta;
	int ctr = 0;

	while (ctr < 2)
	{	
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			sta = device->state();
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &transp)
		{
			TRANSIENT_EXCEPT(transp,"DeviceProxy","state");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute state() on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                    				      desc.str(),
						      (const char*)"DeviceProxy::state()");
		}
	}
	
	return sta;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::status() - return TANGO status of device
//
//-----------------------------------------------------------------------------

string DeviceProxy::status()
{
	string status_str;
	int ctr = 0;

	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			CORBA::String_var st = device->status();
			ctr = 2;
			status_str = st;
		}
		catch (CORBA::TRANSIENT &transp)
		{
			TRANSIENT_EXCEPT(transp,"DeviceProxy","status");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute status() on device (CORBA exception)" << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::status()");
		}
	}

	return(status_str);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::adm_name() - return TANGO admin name of device
//
//-----------------------------------------------------------------------------

string DeviceProxy::adm_name()
{
	string adm_name_str;
	int ctr = 0;

	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			CORBA::String_var st = device->adm_name();
			ctr = 2;
			adm_name_str = st;
		}
		catch (CORBA::TRANSIENT &transp)
		{
			TRANSIENT_EXCEPT(transp,"DeviceProxy","adm_name");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute adm_name() on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::adm_name()");
		}
	}

	return(adm_name_str);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::description() - return TANGO device description as string
//
//-----------------------------------------------------------------------------

string DeviceProxy::description()
{
	string description_str;
	int ctr = 0;

	while (ctr < 2)
	{
		try
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			CORBA::String_var st = device->description();
			ctr = 2;
			description_str = st;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","description");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute description() on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::description()");
		}
	}

	return(description_str);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::black_box() - return the list of the last n commands exectued on
//		this TANGO device 
//
//-----------------------------------------------------------------------------
 
vector<string> *DeviceProxy::black_box(int last_n_commands) 
{
	DevVarStringArray_var last_commands;
	int ctr = 0;
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			last_commands = device->black_box(last_n_commands);
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","black_box");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute black_box on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                      				      desc.str(),
						      (const char*)"DeviceProxy::black_box()");
		}
	}

	vector<string> *last_commands_vector = new(vector<string>);
	last_commands_vector->resize(last_commands->length());

	for (unsigned int i=0; i<last_commands->length(); i++)
	{
		(*last_commands_vector)[i] = last_commands[i];
	}

	return(last_commands_vector);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::info() - return information about this device
//
//-----------------------------------------------------------------------------
 
DeviceInfo DeviceProxy::info() 
{
	DevInfo_var dev_info;
	DeviceInfo device_info;
	int ctr = 0;

	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			dev_info = device->info();
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","info");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute info() on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                        			   desc.str(),
						   (const char*)"DeviceProxy::info()");
		}
	}

	device_info.dev_class = dev_info->dev_class;
	device_info.server_id = dev_info->server_id;
	device_info.server_host = dev_info->server_host;
	device_info.server_version = dev_info->server_version;
	device_info.doc_url = dev_info->doc_url;
	device_info.dev_type = 0;

	return(device_info);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::command_query() - return the description for the specified 
//		command implemented for this TANGO device 
//
//-----------------------------------------------------------------------------
 
CommandInfo DeviceProxy::command_query(string cmd) 
{
	CommandInfo command_info;
	DevCmdInfo_var cmd_info;
	DevCmdInfo_2_var cmd_info_2;
	int ctr = 0;

	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			if (version == 1)
			{
				cmd_info = device->command_query(cmd.c_str());

				command_info.cmd_name = cmd_info->cmd_name;
				command_info.cmd_tag = cmd_info->cmd_tag;
				command_info.in_type = cmd_info->in_type;
				command_info.out_type = cmd_info->out_type;
				command_info.in_type_desc = cmd_info->in_type_desc;
				command_info.out_type_desc = cmd_info->out_type_desc;
				command_info.disp_level = Tango::OPERATOR;
			}
			else
			{
				cmd_info_2 = device_2->command_query_2(cmd.c_str());

				command_info.cmd_name = cmd_info_2->cmd_name;
				command_info.cmd_tag = cmd_info_2->cmd_tag;
				command_info.in_type = cmd_info_2->in_type;
				command_info.out_type = cmd_info_2->out_type;
				command_info.in_type_desc = cmd_info_2->in_type_desc;
				command_info.out_type_desc = cmd_info_2->out_type_desc;
				command_info.disp_level = cmd_info_2->level;
			}
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","command_query");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute command_query on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                        			   desc.str(),
						   (const char*)"DeviceProxy::command_query()");
		}
	}


	
	return(command_info);
}


//-----------------------------------------------------------------------------
//
// DeviceProxy::command_list_query() - return the list of commands implemented for this TANGO device 
//
//-----------------------------------------------------------------------------
 
CommandInfoList *DeviceProxy::command_list_query() 
{
	CommandInfoList *command_info_list = new CommandInfoList();
	DevCmdInfoList_var cmd_info_list;
	DevCmdInfoList_2_var cmd_info_list_2;
	int ctr = 0;
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			if (version == 1)
			{	
				cmd_info_list = device->command_list_query();

				command_info_list->resize(cmd_info_list->length());

				for (unsigned int i=0; i < cmd_info_list->length(); i++)
				{
					(*command_info_list)[i].cmd_name = cmd_info_list[i].cmd_name;
					(*command_info_list)[i].cmd_tag = cmd_info_list[i].cmd_tag;
					(*command_info_list)[i].in_type = cmd_info_list[i].in_type;
					(*command_info_list)[i].out_type = cmd_info_list[i].out_type;
					(*command_info_list)[i].in_type_desc = cmd_info_list[i].in_type_desc;
					(*command_info_list)[i].out_type_desc = cmd_info_list[i].out_type_desc;
					(*command_info_list)[i].disp_level = Tango::OPERATOR;
				}
			}
			else
			{
				cmd_info_list_2 = device_2->command_list_query_2();

				command_info_list->resize(cmd_info_list_2->length());

				for (unsigned int i=0; i < cmd_info_list_2->length(); i++)
				{
					(*command_info_list)[i].cmd_name = cmd_info_list_2[i].cmd_name;
					(*command_info_list)[i].cmd_tag = cmd_info_list_2[i].cmd_tag;
					(*command_info_list)[i].in_type = cmd_info_list_2[i].in_type;
					(*command_info_list)[i].out_type = cmd_info_list_2[i].out_type;
					(*command_info_list)[i].in_type_desc = cmd_info_list_2[i].in_type_desc;
					(*command_info_list)[i].out_type_desc = cmd_info_list_2[i].out_type_desc;
					(*command_info_list)[i].disp_level = cmd_info_list_2[i].level;
				}		
			}
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","command_list_query");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute command_list_query on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::command_list_query()");
		}
	}



	return(command_info_list);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_property() - get a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::get_property(string &property_name, DbData &db_data) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::get_property");
	}
	else
	{
		db_data.resize(1);
		db_data[0] = DbDatum(property_name);

		db_dev->get_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_property() - get a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::get_property(vector<string> &property_names, DbData &db_data) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::get_property");
	}
	else
	{
		db_data.resize(property_names.size());
		for (unsigned int i=0; i<property_names.size(); i++)
		{
			db_data[i] = DbDatum(property_names[i]);
		}

		db_dev->get_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_property() - get a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::get_property(DbData &db_data) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::get_property");
	}
	else
	{
		db_dev->get_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::put_property() - put a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::put_property(DbData &db_data) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::put_property");
	}
	else
	{
		db_dev->put_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::delete_property() - deleteget a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::delete_property(string &property_name) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::delete_property");
	}
	else
	{
		DbData db_data;

		db_data.push_back(DbDatum(property_name));

		db_dev->delete_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::delete_property() - delete a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::delete_property(vector<string> &property_names) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::delete_property");
	}
	else
	{
		DbData db_data;

		for (unsigned int i=0; i<property_names.size(); i++)
		{
			db_data.push_back(DbDatum(property_names[i]));
		}

		db_dev->delete_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::delete_property() - delete a property from the database
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::delete_property(DbData &db_data) 
{
	if (dbase_used == false)
	{
		TangoSys_OMemStream desc;
		desc << "Method not available for device ";
		desc << device_name;
		desc << " which is a non database device";
		
		ApiNonDbExcept::throw_exception((const char *)"API_NonDatabaseDevice",
					desc.str(),
					(const char *)"DeviceProxy::delete_property");
	}
	else
	{
		db_dev->delete_property(db_data);
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_attribute_config() - return a list of attributes
//
//-----------------------------------------------------------------------------
 
AttributeInfoList *DeviceProxy::get_attribute_config(vector<string>& attr_string_list) 
{
	AttributeConfigList_var attr_config_list;
	AttributeConfigList_2_var attr_config_list_2;
	AttributeInfoList *dev_attr_config = new AttributeInfoList();
	DevVarStringArray attr_list;
	int ctr = 0;
	
	attr_list.length(attr_string_list.size());
	for (unsigned int i=0; i<attr_string_list.size(); i++)
	{
		attr_list[i] = string_dup(attr_string_list[i].c_str());
	}
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			if (version == 1)
			{
				attr_config_list = device->get_attribute_config(attr_list);

				dev_attr_config->resize(attr_config_list->length());

				for (unsigned int i=0; i<attr_config_list->length(); i++)
				{
					(*dev_attr_config)[i].name = attr_config_list[i].name;
					(*dev_attr_config)[i].writable = attr_config_list[i].writable;
					(*dev_attr_config)[i].data_format = attr_config_list[i].data_format;
					(*dev_attr_config)[i].data_type = attr_config_list[i].data_type;
					(*dev_attr_config)[i].max_dim_x = attr_config_list[i].max_dim_x;
					(*dev_attr_config)[i].max_dim_y = attr_config_list[i].max_dim_y;
					(*dev_attr_config)[i].description = attr_config_list[i].description;
					(*dev_attr_config)[i].label = attr_config_list[i].label;
					(*dev_attr_config)[i].unit = attr_config_list[i].unit;
					(*dev_attr_config)[i].standard_unit = attr_config_list[i].standard_unit;
					(*dev_attr_config)[i].display_unit = attr_config_list[i].display_unit;
					(*dev_attr_config)[i].format = attr_config_list[i].format;
					(*dev_attr_config)[i].min_value = attr_config_list[i].min_value;
					(*dev_attr_config)[i].max_value = attr_config_list[i].max_value;
					(*dev_attr_config)[i].min_alarm = attr_config_list[i].min_alarm;
					(*dev_attr_config)[i].max_alarm = attr_config_list[i].max_alarm;
					(*dev_attr_config)[i].writable_attr_name = attr_config_list[i].writable_attr_name;
					(*dev_attr_config)[i].extensions.resize(attr_config_list[i].extensions.length());
					for (unsigned int j=0; j<attr_config_list[i].extensions.length(); j++)
					{
						(*dev_attr_config)[i].extensions[j] = attr_config_list[i].extensions[j];
					}
					(*dev_attr_config)[i].disp_level = Tango::OPERATOR;
				}
			}
			else
			{
				attr_config_list_2 = device_2->get_attribute_config_2(attr_list);

				dev_attr_config->resize(attr_config_list_2->length());

				for (unsigned int i=0; i<attr_config_list_2->length(); i++)
				{
					(*dev_attr_config)[i].name = attr_config_list_2[i].name;
					(*dev_attr_config)[i].writable = attr_config_list_2[i].writable;
					(*dev_attr_config)[i].data_format = attr_config_list_2[i].data_format;
					(*dev_attr_config)[i].data_type = attr_config_list_2[i].data_type;
					(*dev_attr_config)[i].max_dim_x = attr_config_list_2[i].max_dim_x;
					(*dev_attr_config)[i].max_dim_y = attr_config_list_2[i].max_dim_y;
					(*dev_attr_config)[i].description = attr_config_list_2[i].description;
					(*dev_attr_config)[i].label = attr_config_list_2[i].label;
					(*dev_attr_config)[i].unit = attr_config_list_2[i].unit;
					(*dev_attr_config)[i].standard_unit = attr_config_list_2[i].standard_unit;
					(*dev_attr_config)[i].display_unit = attr_config_list_2[i].display_unit;
					(*dev_attr_config)[i].format = attr_config_list_2[i].format;
					(*dev_attr_config)[i].min_value = attr_config_list_2[i].min_value;
					(*dev_attr_config)[i].max_value = attr_config_list_2[i].max_value;
					(*dev_attr_config)[i].min_alarm = attr_config_list_2[i].min_alarm;
					(*dev_attr_config)[i].max_alarm = attr_config_list_2[i].max_alarm;
					(*dev_attr_config)[i].writable_attr_name = attr_config_list_2[i].writable_attr_name;
					(*dev_attr_config)[i].extensions.resize(attr_config_list_2[i].extensions.length());
					for (unsigned int j=0; j<attr_config_list_2[i].extensions.length(); j++)
					{
						(*dev_attr_config)[i].extensions[j] = attr_config_list_2[i].extensions[j];
					}
					(*dev_attr_config)[i].disp_level = attr_config_list_2[i].level;
				}
			}
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","get_attribute_config");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute get_attribute_config on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						   (const char*)"API_CommunicationFailed",
                       				   desc.str(),
						   (const char*)"DeviceProxy::get_attribute_config()");
		}
	}

	return(dev_attr_config);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_attribute_config() - return a single attribute config
//
//-----------------------------------------------------------------------------
 
AttributeInfo DeviceProxy::get_attribute_config(string& attr_string) 
{
	vector<string> attr_string_list;
	AttributeInfoList *dev_attr_config_list;
	AttributeInfo dev_attr_config;

	attr_string_list.push_back(attr_string);
	dev_attr_config_list = get_attribute_config(attr_string_list);

	dev_attr_config = (*dev_attr_config_list)[0];
	delete(dev_attr_config_list);
	
	return(dev_attr_config);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::set_attribute_config() - set config for a list of attributes
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::set_attribute_config(AttributeInfoList &dev_attr_list) 
{
	AttributeConfigList attr_config_list;
	DevVarStringArray attr_list;
	int ctr = 0;

	attr_config_list.length(dev_attr_list.size());

	for (unsigned int i=0; i<attr_config_list.length(); i++)
	{
		attr_config_list[i].name = dev_attr_list[i].name.c_str();
		attr_config_list[i].writable = dev_attr_list[i].writable;
		attr_config_list[i].data_format = dev_attr_list[i].data_format;
		attr_config_list[i].data_type = dev_attr_list[i].data_type;
		attr_config_list[i].max_dim_x = dev_attr_list[i].max_dim_x;
		attr_config_list[i].max_dim_y = dev_attr_list[i].max_dim_y;
		attr_config_list[i].description = dev_attr_list[i].description.c_str();
		attr_config_list[i].label = dev_attr_list[i].label.c_str();
		attr_config_list[i].unit = dev_attr_list[i].unit.c_str();
		attr_config_list[i].standard_unit = dev_attr_list[i].standard_unit.c_str();
		attr_config_list[i].display_unit = dev_attr_list[i].display_unit.c_str();
		attr_config_list[i].format = dev_attr_list[i].format.c_str();
		attr_config_list[i].min_value = dev_attr_list[i].min_value.c_str();
		attr_config_list[i].max_value = dev_attr_list[i].max_value.c_str();
		attr_config_list[i].min_alarm = dev_attr_list[i].min_alarm.c_str();
		attr_config_list[i].max_alarm = dev_attr_list[i].max_alarm.c_str();
		attr_config_list[i].writable_attr_name = dev_attr_list[i].writable_attr_name.c_str();
		attr_config_list[i].extensions.length(dev_attr_list[i].extensions.size());
		for (unsigned int j=0; j<dev_attr_list[i].extensions.size(); j++)
		{
			attr_config_list[i].extensions[j] = string_dup(dev_attr_list[i].extensions[j].c_str());
		}
	}
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			device->set_attribute_config(attr_config_list);
			ctr = 2;

		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","set_attribute_config");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute set_attribute_config on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::set_attribute_config()");
		}
	}


	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::read_attributes() - return a list of attributes
//
//-----------------------------------------------------------------------------
 
vector<DeviceAttribute> *DeviceProxy::read_attributes(vector<string>& attr_string_list) 
{
	AttributeValueList_var attr_value_list;
	vector<DeviceAttribute> *dev_attr = new(vector<DeviceAttribute>);
	DevVarStringArray attr_list;
	
	attr_list.length(attr_string_list.size());
	for (unsigned int i=0; i<attr_string_list.size(); i++)
	{
		attr_list[i] = string_dup(attr_string_list[i].c_str());
	}

	int ctr = 0;
		
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);



			if (version == 2)
				attr_value_list = device_2->read_attributes_2(attr_list,source);
			else
				attr_value_list = device->read_attributes(attr_list);
			ctr = 2;
		}
		catch (Tango::ConnectionFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to read_attributes on device " << device_name;
			desc << ", attributes ";
			int nb_attr = attr_string_list.size();
			for (int i = 0;i < nb_attr;i++)
			{
				desc << attr_string_list[i];
				if (i != nb_attr - 1)
					desc << ", ";
			}
			desc << ends;
                	ApiConnExcept::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::read_attributes()");
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to read_attributes on device " << device_name;
			desc << ", attributes ";
			int nb_attr = attr_string_list.size();
			for (int i = 0;i < nb_attr;i++)
			{
				desc << attr_string_list[i];
				if (i != nb_attr - 1)
					desc << ", ";
			}
			desc << ends;
                	Except::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::read_attributes()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","read_attributes");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute read_attributes on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::read_attributes()");
		}
	}

	dev_attr->resize(attr_value_list->length());

	const DevVarLongArray *tmp_seq_lo;
	CORBA::Long *tmp_lo;
	const DevVarShortArray *tmp_seq_sh;
	CORBA::Short *tmp_sh;
	const DevVarDoubleArray *tmp_seq_db;
	CORBA::Double *tmp_db;
	const DevVarStringArray *tmp_seq_str;
	char **tmp_str;
	CORBA::ULong max,len;
	
	for (unsigned int k=0; k<attr_value_list->length(); k++)
	{
		(*dev_attr)[k].name = attr_value_list[k].name;
		(*dev_attr)[k].quality = attr_value_list[k].quality;
		(*dev_attr)[k].time = attr_value_list[k].time;
		(*dev_attr)[k].dim_x = attr_value_list[k].dim_x;
		(*dev_attr)[k].dim_y = attr_value_list[k].dim_y;

		if ((*dev_attr)[k].quality != Tango::ATTR_INVALID)
		{
			TypeCode_var ty = attr_value_list[k].value.type();
			TypeCode_var ty_alias = ty->content_type();
			TypeCode_var ty_seq = ty_alias->content_type();			
			switch (ty_seq->kind())
			{
			case tk_long:		
				attr_value_list[k].value >>= tmp_seq_lo;
				max = tmp_seq_lo->maximum();
				len = tmp_seq_lo->length();
				if (tmp_seq_lo->release() == true)
				{
					tmp_lo = (const_cast<DevVarLongArray *>(tmp_seq_lo))->get_buffer((CORBA::Boolean)true);
					(*dev_attr)[k].LongSeq = new DevVarLongArray(max,len,tmp_lo,true);
				}
				else
				{
					tmp_lo = const_cast<CORBA::Long *>(tmp_seq_lo->get_buffer());
					(*dev_attr)[k].LongSeq = new DevVarLongArray(max,len,tmp_lo,false);
				}
				break;
		
			case tk_short:
				attr_value_list[k].value >>= tmp_seq_sh;
				max = tmp_seq_sh->maximum();
				len = tmp_seq_sh->length();
				if (tmp_seq_sh->release() == true)
				{
					tmp_sh = (const_cast<DevVarShortArray *>(tmp_seq_sh))->get_buffer((CORBA::Boolean)true);
					(*dev_attr)[k].ShortSeq = new DevVarShortArray(max,len,tmp_sh,true);
				}
				else
				{
					tmp_sh = const_cast<CORBA::Short *>(tmp_seq_sh->get_buffer());
					(*dev_attr)[k].ShortSeq = new DevVarShortArray(max,len,tmp_sh,false);
				}
				break;
		
			case tk_double:
				attr_value_list[k].value >>= tmp_seq_db;
				max = tmp_seq_db->maximum();
				len = tmp_seq_db->length();
				if (tmp_seq_db->release() == true)
				{
					tmp_db = (const_cast<DevVarDoubleArray *>(tmp_seq_db))->get_buffer((CORBA::Boolean)true);
					(*dev_attr)[k].DoubleSeq = new DevVarDoubleArray(max,len,tmp_db,true);
				}
				else
				{
					tmp_db = const_cast<CORBA::Double *>(tmp_seq_db->get_buffer());
					(*dev_attr)[k].DoubleSeq = new DevVarDoubleArray(max,len,tmp_db,false);
				}
				break;
		
			case tk_string:
				attr_value_list[k].value >>= tmp_seq_str;
				max = tmp_seq_str->maximum();
				len = tmp_seq_str->length();
				if (tmp_seq_str->release() == true)
				{
					tmp_str = (const_cast<DevVarStringArray *>(tmp_seq_str))->get_buffer((CORBA::Boolean)true);
					(*dev_attr)[k].StringSeq = new DevVarStringArray(max,len,tmp_str,true);
				}
				else
				{
					tmp_str = const_cast<char **>(tmp_seq_str->get_buffer());
					(*dev_attr)[k].StringSeq = new DevVarStringArray(max,len,tmp_str,false);
				}
				break;
			}
		}	
	}

	return(dev_attr);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::read_attribute() - return a single attribute 
//
//-----------------------------------------------------------------------------
 

DeviceAttribute DeviceProxy::read_attribute(string& attr_string) 
{
	AttributeValueList_var attr_value_list;
	DeviceAttribute dev_attr;
	DevVarStringArray attr_list;
	int ctr = 0;

	attr_list.length(1);
	attr_list[0] = CORBA::string_dup(attr_string.c_str());

	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			if (version == 2)
				attr_value_list = device_2->read_attributes_2(attr_list,source);
			else
				attr_value_list = device->read_attributes(attr_list);
			ctr = 2;
		}
		catch (Tango::ConnectionFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to read_attribute on device " << device_name;
			desc << ", attribute " << attr_string << ends;
                	ApiConnExcept::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::read_attribute()");
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to read_attributes on device " << device_name;
			desc << ", attribute " << attr_string << ends;

                	Except::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::read_attribute()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","read_attribute");
		}        
		catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to read_attribute on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::read_attribute()");
		}
	}

	dev_attr.name = attr_value_list[0].name;
	dev_attr.quality = attr_value_list[0].quality;
	dev_attr.time = attr_value_list[0].time;
	dev_attr.dim_x = attr_value_list[0].dim_x;
	dev_attr.dim_y = attr_value_list[0].dim_y;

	const DevVarLongArray *tmp_seq_lo;
	CORBA::Long *tmp_lo;
	const DevVarShortArray *tmp_seq_sh;
	CORBA::Short *tmp_sh;
	const DevVarDoubleArray *tmp_seq_db;
	CORBA::Double *tmp_db;
	const DevVarStringArray *tmp_seq_str;
	char **tmp_str;
	CORBA::ULong max,len;

	if (dev_attr.quality != Tango::ATTR_INVALID)
	{
		CORBA::TypeCode_var ty = attr_value_list[0].value.type();
		CORBA::TypeCode_var ty_alias = ty->content_type();
		CORBA::TypeCode_var ty_seq = ty_alias->content_type();		
		switch (ty_seq->kind())
		{
		case tk_long:		
			attr_value_list[0].value >>= tmp_seq_lo;
			max = tmp_seq_lo->maximum();
			len = tmp_seq_lo->length();
			if (tmp_seq_lo->release() == true)
			{
				tmp_lo = (const_cast<DevVarLongArray *>(tmp_seq_lo))->get_buffer((CORBA::Boolean)true);
				dev_attr.LongSeq = new DevVarLongArray(max,len,tmp_lo,true);
			}
			else
			{
				tmp_lo = const_cast<CORBA::Long *>(tmp_seq_lo->get_buffer());
				dev_attr.LongSeq = new DevVarLongArray(max,len,tmp_lo,false);
			}
			break;
		
		case tk_short:
			attr_value_list[0].value >>= tmp_seq_sh;
			max = tmp_seq_sh->maximum();
			len = tmp_seq_sh->length();
			if (tmp_seq_sh->release() == true)
			{
				tmp_sh = (const_cast<DevVarShortArray *>(tmp_seq_sh))->get_buffer((CORBA::Boolean)true);
				dev_attr.ShortSeq = new DevVarShortArray(max,len,tmp_sh,true);
			}
			else
			{
				tmp_sh = const_cast<CORBA::Short *>(tmp_seq_sh->get_buffer());
				dev_attr.ShortSeq = new DevVarShortArray(max,len,tmp_sh,false);
			}
			break;
		
		case tk_double:
			attr_value_list[0].value >>= tmp_seq_db;
			max = tmp_seq_db->maximum();
			len = tmp_seq_db->length();
			if (tmp_seq_db->release() == true)
			{
				tmp_db = (const_cast<DevVarDoubleArray *>(tmp_seq_db))->get_buffer((CORBA::Boolean)true);
				dev_attr.DoubleSeq = new DevVarDoubleArray(max,len,tmp_db,true);
			}
			else
			{
				tmp_db = const_cast<CORBA::Double *>(tmp_seq_db->get_buffer());
				dev_attr.DoubleSeq = new DevVarDoubleArray(max,len,tmp_db,false);
			}
			break;
		
		case tk_string:
			attr_value_list[0].value >>= tmp_seq_str;
			max = tmp_seq_str->maximum();
			len = tmp_seq_str->length();
			if (tmp_seq_str->release() == true)
			{
				tmp_str = (const_cast<DevVarStringArray *>(tmp_seq_str))->get_buffer((CORBA::Boolean)true);
				dev_attr.StringSeq = new DevVarStringArray(max,len,tmp_str,true);
			}
			else
			{
				tmp_str = const_cast<char **>(tmp_seq_str->get_buffer());
				dev_attr.StringSeq = new DevVarStringArray(max,len,tmp_str,false);
			}
			break;
		}
	}	

	return(dev_attr);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::write_attributes() - write a list of attributes
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::write_attributes(vector<DeviceAttribute>& attr_list) 
{
	AttributeValueList attr_value_list;

	attr_value_list.length(attr_list.size());
	for (unsigned int i=0; i<attr_list.size(); i++)
	{
		attr_value_list[i].name = attr_list[i].name.c_str();
		attr_value_list[i].quality = attr_list[i].quality;
		attr_value_list[i].time = attr_list[i].time;
		attr_value_list[i].dim_x = attr_list[i].dim_x;
		attr_value_list[i].dim_y = attr_list[i].dim_y;
		
		if (attr_list[i].LongSeq.operator->() != NULL)
		{
			attr_value_list[i].value <<= attr_list[i].LongSeq.in();	
			continue;
		}
		if (attr_list[i].ShortSeq.operator->() != NULL)
		{	
			attr_value_list[i].value <<= attr_list[i].ShortSeq.in();
			continue;
		}	
		if (attr_list[i].DoubleSeq.operator->() != NULL)
		{	
			attr_value_list[i].value <<= attr_list[i].DoubleSeq.in();
			continue;
		}
		if (attr_list[i].StringSeq.operator->() != NULL)
		{	
			attr_value_list[i].value  <<= attr_list[i].StringSeq.in();
			continue;
		}
	}

	int ctr = 0;
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			device->write_attributes(attr_value_list);
			ctr = 2;
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to write_attributes on device " << device_name;
			desc << ", attributes ";
			int nb_attr = attr_value_list.length();
			for (int i = 0;i < nb_attr;i++)
			{
				desc << attr_value_list[i].name.in();
				if (i != nb_attr - 1)
					desc << ", ";
			}
			desc << ends;
                	Except::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::write_attribute()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","write_attributes");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute write_attributes on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::write_attributes()");
		}
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::write_attribute() - write a single attribute 
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::write_attribute(DeviceAttribute &dev_attr) 
{
	AttributeValueList attr_value_list;

	attr_value_list.length(1);

	attr_value_list[0].name = dev_attr.name.c_str();
	attr_value_list[0].quality = dev_attr.quality;
	attr_value_list[0].time = dev_attr.time;
	attr_value_list[0].dim_x = dev_attr.dim_x;
	attr_value_list[0].dim_y = dev_attr.dim_y;
		
	if (dev_attr.LongSeq.operator->() != NULL)
		attr_value_list[0].value <<= dev_attr.LongSeq.in();	
	else if (dev_attr.ShortSeq.operator->() != NULL)
		attr_value_list[0].value <<= dev_attr.ShortSeq.in();
	else if (dev_attr.DoubleSeq.operator->() != NULL)
		attr_value_list[0].value <<= dev_attr.DoubleSeq.in();
	else if (dev_attr.StringSeq.operator->() != NULL)
		attr_value_list[0].value  <<= dev_attr.StringSeq.in();

	int ctr = 0;
	
	while (ctr < 2)
	{
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			device->write_attributes(attr_value_list);
			ctr = 2;
		}
		catch (Tango::DevFailed &e)
		{
			TangoSys_OMemStream desc;
			desc << "Failed to write_attribute on device " << device_name;
			desc << ", attribute ";
			desc << attr_value_list[0].name.in();
			desc << ends;
                	Except::re_throw_exception(e,(const char*)"API_AttributeFailed",
                        	desc.str(), (const char*)"DeviceProxy::write_attribute()");
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","write_attribute()");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Failed to execute write_attributes on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::write_attribute()");
		}
	}

	return;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_attribute_list() - get list of attributes
//
//-----------------------------------------------------------------------------
 
vector<string> *DeviceProxy::get_attribute_list() 
{
	vector<string> all_attr;
	AttributeInfoList * all_attr_config;
	vector<string> *attr_list = new vector<string>;

	all_attr.push_back(AllAttr);
	all_attr_config = get_attribute_config(all_attr);

	attr_list->resize(all_attr_config->size());
	for (unsigned int i=0; i<all_attr_config->size(); i++)
	{
		(*attr_list)[i] = (*all_attr_config)[i].name;

	}
	delete all_attr_config;

	return attr_list;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::attribute_list_query() - get list of attributes
//
//-----------------------------------------------------------------------------
 
AttributeInfoList *DeviceProxy::attribute_list_query() 
{
	vector<string> all_attr;
	AttributeInfoList *all_attr_config;

	all_attr.push_back(AllAttr);
	all_attr_config = get_attribute_config(all_attr);

	return all_attr_config;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::command_history() - get command history (only for polled command)
//
//-----------------------------------------------------------------------------
 
vector<DeviceDataHistory> *DeviceProxy::command_history(string &cmd_name,int depth) 
{
	if (version == 1)
	{
		TangoSys_OMemStream desc;
		desc << "Device " << device_name;
		desc << " does not support command_history feature" << ends;
		ApiNonSuppExcept::throw_exception((const char *)"API_UnsupportedFeature",
						  desc.str(),
						  (const char *)"DeviceProxy::command_history");
	}

	DevCmdHistoryList *hist;

	int ctr = 0;
	
	while (ctr < 2)
	{		
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			hist = device_2->command_inout_history_2(cmd_name.c_str(),depth);
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","command_history");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Command_history failed on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::command_history()");
		}
	}

	int *ctr_ptr = new int;
	*ctr_ptr = 0;
		
	vector<DeviceDataHistory> *ddh = new vector<DeviceDataHistory>;
	ddh->reserve(hist->length());
	
	for (unsigned int i = 0;i < hist->length();i++)
	{
		ddh->push_back(DeviceDataHistory(i,ctr_ptr,hist));
	}

	return ddh;

}

//-----------------------------------------------------------------------------
//
// DeviceProxy::attribute_history() - get attribute history
//				      (only for polled attribute)
//
//-----------------------------------------------------------------------------
 
vector<DeviceAttributeHistory> *DeviceProxy::attribute_history(string &cmd_name,int depth) 
{
	if (version == 1)
	{
		TangoSys_OMemStream desc;
		desc << "Device " << device_name;
		desc << " does not support attribute_history feature" << ends;
		ApiNonSuppExcept::throw_exception((const char *)"API_UnsupportedFeature",
						  desc.str(),
						  (const char *)"DeviceProxy::attribute_history");
	}

	DevAttrHistoryList_var hist;
	int ctr = 0;

	while (ctr < 2)
	{		
		try 
		{
			if (connection_state != CONNECTION_OK) reconnect(dbase_used);

			hist = device_2->read_attribute_history_2(cmd_name.c_str(),depth);
			ctr = 2;
		}
		catch (CORBA::TRANSIENT &trans)
		{
			TRANSIENT_EXCEPT(trans,"DeviceProxy","attribute_history");
		}
        	catch (CORBA::SystemException &ce)
        	{
			connection_state = CONNECTION_NOTOK;

			TangoSys_OMemStream desc;
			desc << "Attribute_history failed on device " << device_name << ends;
			ApiCommExcept::re_throw_exception(ce,
						      (const char*)"API_CommunicationFailed",
                        			      desc.str(),
						      (const char*)"DeviceProxy::attribute_history()");
		}
	}
		
	vector<DeviceAttributeHistory> *ddh = new vector<DeviceAttributeHistory>;
	ddh->reserve(hist->length());
	
	for (unsigned int i = 0;i < hist->length();i++)
	{
		ddh->push_back(DeviceAttributeHistory(i,hist));
	}

	return ddh;

}

//-----------------------------------------------------------------------------
//
// DeviceProxy::connect_to_adm_device() - get device polling status
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::connect_to_adm_device() 
{
	string adm_dev_name = adm_name();
	
	adm_device = new DeviceProxy(adm_dev_name);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::polling_cmd_except() - Throw polling command exception
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::polling_cmd_except(Tango::DevFailed *ex,string &command,const char *Source) 
{
	TangoSys_OMemStream desc;
	desc << "Administration device for DS hosting device " << device_name;
	desc << " failed when executing " << command << " command" << ends;

	Tango::ConnectionFailed *con_ptr;
	Tango::CommunicationFailed *comm_ptr;
	Tango::DevFailed *fail_ptr;
				
	if ((con_ptr = dynamic_cast<Tango::ConnectionFailed *>(ex)) != NULL)
	{
		ApiConnExcept::re_throw_exception(*con_ptr,
						  (const char *)"API_",
						  desc.str(),Source);
	}
	else if ((comm_ptr = dynamic_cast<Tango::CommunicationFailed *>(ex)) != NULL)
	{
		ApiCommExcept::re_throw_exception(*comm_ptr,
						  (const char *)"API_",
						  desc.str(),Source);
	}
	else if ((fail_ptr = dynamic_cast<Tango::DevFailed *>(ex)) != NULL)
	{
		Except::re_throw_exception(*fail_ptr,
						  (const char *)"API_",
						  desc.str(),Source);
	}
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::polling_status() - get device polling status
//
//-----------------------------------------------------------------------------
 
vector<string> *DeviceProxy::polling_status() 
{
	if (adm_device == NULL)
		connect_to_adm_device();
		
	DeviceData dout,din;
	string cmd("DevPollStatus");
	din.any <<= device_name.c_str();
	
//
// In case of connection failed error, do a re-try
//

	try
	{
		dout = adm_device->command_inout(cmd,din);
	}
	catch (Tango::CommunicationFailed &)
	{
		dout = adm_device->command_inout(cmd,din);
	}

	const DevVarStringArray *out_str;
	dout >> out_str;

	vector<string> *poll_stat = new vector<string>;
	poll_stat->reserve(out_str->length());
	
	for (unsigned int i = 0;i < out_str->length();i++)
	{
		string str = (*out_str)[i].in();
		poll_stat->push_back(str);
	}	
	return poll_stat;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::is_polled() - return true if the object "obj_name" is polled.
//			      In this case, the upd string is initialised with
//			      the polling period.
//
//-----------------------------------------------------------------------------
 
bool DeviceProxy::is_polled(polled_object obj, string &obj_name,string &upd) 
{
	bool ret = false;
	vector<string> *poll_str;
	
	poll_str = polling_status();
	if (poll_str->size() == 0)
	{
		delete poll_str;
		return ret;
	}

	for (unsigned int i = 0;i < poll_str->size();i++)
	{
		string &tmp_str = (*poll_str)[i];
		string::size_type pos,end;
		pos = tmp_str.find(' ');
		pos++;
		end = tmp_str.find(' ',pos + 1);
		string obj_type = tmp_str.substr(pos, end - pos);
		if (obj_type == "command")
		{
			if (obj == Attr)
				continue;
		}
		else if (obj_type == "attribute")
		{
			if (obj == Cmd)
				continue;
		}
		
		pos = tmp_str.find('=');
		pos = pos + 2;
		end = tmp_str.find('\n',pos + 1);
		string name = tmp_str.substr(pos, end - pos);
		transform(name.begin(),name.end(),name.begin(),::tolower);
		string loc_obj_name(obj_name);
		transform(loc_obj_name.begin(),loc_obj_name.end(),loc_obj_name.begin(),::tolower);
		if (name == loc_obj_name)
		{
		
//
// Now that it's found, serach for its polling period
//
			pos = tmp_str.find('=',end);
			pos = pos + 2;
			end = tmp_str.find('\n',pos + 1);
			string per = tmp_str.substr(pos, end - pos);
			upd = per;
			ret = true;
			break;
		}
	}
			
	delete poll_str;
	
	return  ret;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_command_poll_period() - Return command polling period
//					    (in mS)
//
//-----------------------------------------------------------------------------
 
int DeviceProxy::get_command_poll_period(string &cmd_name) 
{
	string poll_per;
	bool poll = is_polled(Cmd,cmd_name,poll_per);

	int ret;	
	if (poll == true)
	{
		TangoSys_MemStream stream;
		
		stream << poll_per << ends;
		stream >> ret;
	}
	else
		ret = 0;
		
	return ret;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_attribute_poll_period() - Return attribute polling period
//					    (in mS)
//
//-----------------------------------------------------------------------------
 
int DeviceProxy::get_attribute_poll_period(string &attr_name) 
{
	string poll_per;
	bool poll = is_polled(Attr,attr_name,poll_per);

	int ret;	
	if (poll == true)
	{
		TangoSys_MemStream stream;
		
		stream << poll_per << ends;
		stream >> ret;
	}
	else
		ret = 0;
		
	return ret;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::poll_command() - If object is already polled, just update its
//				 polling period. If object is not polled, add
//				 it to the list of polled objects
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::poll_command(string &cmd_name, int period) 
{
	string poll_per;
	bool poll = is_polled(Cmd,cmd_name,poll_per);
	
	DevVarLongStringArray in;
	in.lvalue.length(1);
	in.svalue.length(3);
	
	in.svalue[0] = CORBA::string_dup(device_name.c_str());
	in.svalue[1] = CORBA::string_dup("command");
	in.svalue[2] = CORBA::string_dup(cmd_name.c_str());
	in.lvalue[0] = period;
	
	if (poll == true)
	{
	
//
// If object is polled and the polling period is the same, simply retruns
//		
		TangoSys_MemStream stream;
		int per;
		
		stream << poll_per << ends;
		stream >> per;
		
		if (per == period)
			return;
		else
		{
	
//
// If object is polled, this is an update of the polling period
//

			DeviceData din;
			string cmd("UpdObjPollingPeriod");
			din.any <<= in;

			try
			{			
				adm_device->command_inout(cmd,din);
			}
			catch (Tango::CommunicationFailed &)
			{
				adm_device->command_inout(cmd,din);
			}

		}
	}
	else
	{
	
//
// This a AddObjPolling command
//

		DeviceData din;
		string cmd("AddObjPolling");
		din.any <<= in;

		try
		{			
			adm_device->command_inout(cmd,din);
		}
		catch (Tango::CommunicationFailed &)
		{
			adm_device->command_inout(cmd,din);
		}

	}
	
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::poll_attribute() - If object is already polled, just update its
//				 polling period. If object is not polled, add
//				 it to the list of polled objects
//
//-----------------------------------------------------------------------------
 
void DeviceProxy::poll_attribute(string &attr_name, int period) 
{
	string poll_per;
	bool poll = is_polled(Attr,attr_name,poll_per);
	
	DevVarLongStringArray in;
	in.lvalue.length(1);
	in.svalue.length(3);
	
	in.svalue[0] = CORBA::string_dup(device_name.c_str());
	in.svalue[1] = CORBA::string_dup("attribute");
	in.svalue[2] = CORBA::string_dup(attr_name.c_str());
	in.lvalue[0] = period;
	
	if (poll == true)
	{
	
//
// If object is polled and the polling period is the same, simply retruns
//		
		TangoSys_MemStream stream;
		int per;
		
		stream << poll_per << ends;
		stream >> per;
		
		if (per == period)
			return;
		else
		{
	
//
// If object is polled, this is an update of the polling period
//

			DeviceData din;
			string cmd("UpdObjPollingPeriod");
			din.any <<= in;

			try
			{			
				adm_device->command_inout(cmd,din);
			}
			catch (Tango::CommunicationFailed &)
			{
				adm_device->command_inout(cmd,din);
			}

		}
	}
	else
	{
	
//
// This a AddObjPolling command
//

		DeviceData din;
		string cmd("AddObjPolling");
		din.any <<= in;
		
		try
		{	
			adm_device->command_inout(cmd,din);
		}
		catch (Tango::CommunicationFailed &)
		{
			adm_device->command_inout(cmd,din);
		}

	}
	
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::is_cmd_polled() - return true if the command is polled
//
//-----------------------------------------------------------------------------

bool DeviceProxy::is_command_polled(string &cmd_name)
{
	string upd;
	return is_polled(Cmd,cmd_name,upd);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::is_attribute_polled() - return true if the attribute is polled
//
//-----------------------------------------------------------------------------

bool DeviceProxy::is_attribute_polled(string &attr_name)
{
	string upd;
	return is_polled(Attr,attr_name,upd);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::stop_poll_command() - Stop polling a command
//
//-----------------------------------------------------------------------------

void DeviceProxy::stop_poll_command(string &cmd_name)
{
	if (adm_device == NULL)
		connect_to_adm_device();
		
	DevVarStringArray in;
	in.length(3);
	
	in[0] = CORBA::string_dup(device_name.c_str());
	in[1] = CORBA::string_dup("command");
	in[2] = CORBA::string_dup(cmd_name.c_str());
	
	DeviceData din;
	string cmd("RemObjPolling");
	din.any <<= in;

	try
	{			
		adm_device->command_inout(cmd,din);
	}
	catch (Tango::CommunicationFailed &)
	{
		adm_device->command_inout(cmd,din);
	}

}

//-----------------------------------------------------------------------------
//
// DeviceProxy::stop_poll_attribute() - Stop polling attribute
//
//-----------------------------------------------------------------------------

void DeviceProxy::stop_poll_attribute(string &attr_name)
{
	if (adm_device == NULL)
		connect_to_adm_device();
		
	DevVarStringArray in;
	in.length(3);
	
	in[0] = CORBA::string_dup(device_name.c_str());
	in[1] = CORBA::string_dup("attribute");
	in[2] = CORBA::string_dup(attr_name.c_str());
	
	DeviceData din;
	string cmd("RemObjPolling");
	din.any <<= in;

	try
	{			
		adm_device->command_inout(cmd,din);
	}
	catch (Tango::CommunicationFailed &)
	{
		adm_device->command_inout(cmd,din);
	}

}

#ifdef TANGO_HAS_LOG4TANGO
//-----------------------------------------------------------------------------
//
// DeviceProxy::add_logging_target - Add a logging target
//
//-----------------------------------------------------------------------------
void DeviceProxy::add_logging_target(const string &target_type_name)
{
	if (adm_device == NULL)
		connect_to_adm_device();
		
	DevVarStringArray in(2);
	in.length(2);

	in[0] = CORBA::string_dup(device_name.c_str());
	in[1] = CORBA::string_dup(target_type_name.c_str());
	
	DeviceData din;
	string cmd("AddLoggingTarget");
	din.any <<= in;

	try
	{			
		adm_device->command_inout(cmd,din);
	}
	catch (Tango::CommunicationFailed &)
	{
		adm_device->command_inout(cmd,din);
	}
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::remove_logging_target - Remove a logging target
//
//-----------------------------------------------------------------------------
void DeviceProxy::remove_logging_target (const string &target_type_name)
{
	if (adm_device == NULL)
		connect_to_adm_device();
		
	DevVarStringArray in(2);
	in.length(2);
	
	in[0] = CORBA::string_dup(device_name.c_str());
	in[1] = CORBA::string_dup(target_type_name.c_str());
	
	DeviceData din;
	string cmd("RemoveLoggingTarget");
	din.any <<= in;

	try
	{			
		adm_device->command_inout(cmd,din);
	}
	catch (Tango::CommunicationFailed &)
	{
		adm_device->command_inout(cmd,din);
	}
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_logging_target - Returns the logging target list
//
//-----------------------------------------------------------------------------
vector<string> DeviceProxy::get_logging_target (void)
{
  	if (adm_device == NULL)
		connect_to_adm_device();

  	DeviceData din;
	din << device_name;

  	string cmd("GetLoggingTarget");

  	DeviceData dout;
  	DevVarStringArray_var logging_targets;
	try
	{			
		dout = adm_device->command_inout(cmd, din);
	}
	catch (Tango::CommunicationFailed &)
	{
		dout = adm_device->command_inout(cmd, din);
	}

  	vector<string> logging_targets_vec;

  	dout >> logging_targets_vec;

  	return logging_targets_vec;
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::get_logging_level - Returns the current logging level
//
//-----------------------------------------------------------------------------

int DeviceProxy::get_logging_level (void)
{
  	if (adm_device == NULL)
		connect_to_adm_device();

  	string cmd("GetLoggingLevel");

  	DevVarStringArray in;
	in.length(1);
	in[0] = CORBA::string_dup(device_name.c_str());

  	DeviceData din;
  	din.any <<= in;

  	DeviceData dout;
	try
	{			
		dout = adm_device->command_inout(cmd, din);
	}
	catch (Tango::CommunicationFailed &)
	{
		dout = adm_device->command_inout(cmd, din);
	}

  	long level;
  	dout >> level;
  
  	return (int)level; 
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::set_logging_level - Set the logging level
//
//-----------------------------------------------------------------------------

void DeviceProxy::set_logging_level (int level)
{
  	if (adm_device == NULL)
		connect_to_adm_device();

  	string cmd("SetLoggingLevel");

  	DevVarLongStringArray in;
	in.lvalue.length(1);
	in.lvalue[0] = level;
  	in.svalue.length(1);
	in.svalue[0] = CORBA::string_dup(device_name.c_str());

  	DeviceData din;
  	din.any <<= in;

	try
	{			
		adm_device->command_inout(cmd, din);
	}
	catch (Tango::CommunicationFailed &)
	{
		adm_device->command_inout(cmd, din);
	}
}
#endif // TANGO_HAS_LOG4TANGO

//-----------------------------------------------------------------------------
//
// DeviceProxy::subscribe_event - Subscribe to an event
//
//-----------------------------------------------------------------------------

int DeviceProxy::subscribe_event (const string &attr_name, EventType event, CallBack *callback, const vector<string> &filters)
{
  	if (ApiUtil::instance()->get_event_consumer() == NULL)
	{
		ApiUtil::instance()->create_event_consumer();
	}

	ApiUtil::instance()->get_event_consumer()->connect(this);

	
	return ApiUtil::instance()->get_event_consumer()->subscribe_event(this, attr_name, event, callback, filters);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::unsubscribe_event - Unsubscribe to an event
//
//-----------------------------------------------------------------------------

void DeviceProxy::unsubscribe_event (int event_id)
{
  	if (ApiUtil::instance()->get_event_consumer() == NULL)
	{
		return;
	}

	ApiUtil::instance()->get_event_consumer()->connect(this);

	
	ApiUtil::instance()->get_event_consumer()->unsubscribe_event(event_id);
}

//-----------------------------------------------------------------------------
//
// DeviceProxy::unsubscribe_event - Unsubscribe to an event
//
//-----------------------------------------------------------------------------

Database * DeviceProxy::get_device_db()
{
	return db_dev->get_dbase();
}


} // End of Tango namespace
