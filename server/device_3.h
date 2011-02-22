//=============================================================================	
//
// file :		Device.h
//
// description :	Include for the Device root classes. 
//			Three classes are declared in this file :
//				The Device class
//				The DeviceClass class
//
// project :		TANGO
//
// author(s) :		A.Gotz + E.Taurel
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010
//						European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
// This file is part of Tango.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
//
// $Revision$
//
// $Log$
// Revision 3.11  2009/01/21 12:49:04  taurel
// - Change CopyRights for 2009
//
// Revision 3.10  2009/01/19 08:06:27  taurel
// - Fix warnings generated by Doxygen
//
// Revision 3.9  2008/10/06 15:00:36  taurel
// - Changed the licensing info from GPL to LGPL
//
// Revision 3.8  2008/10/03 06:51:36  taurel
// - Add some licensing info in each files
//
// Revision 3.7  2008/06/10 07:52:14  taurel
// - Add code for the DevEncoded attribute data type
//
// Revision 3.6  2008/05/20 12:44:10  taurel
// - Commit after merge with release 7 branch
//
// Revision 3.5.2.1  2008/05/20 06:17:44  taurel
// - Last commit before merge with trunk
// (start the implementation of the new DevEncoded data type)
//
// Revision 3.5  2006/01/27 14:27:09  taurel
// - Fix a severe incompatibility problem introduced by all the modifs done for
// PY DS
// - Duplicate some EventSupplier class methods (instead of using template) in order to be able to generate Tango shared library on Suse 9.3
//
// Revision 3.4  2005/01/13 08:29:05  taurel
// - Merge trunk with Release_5_0 from brach Release_5_branch
//
// Revision 3.3.2.4  2004/11/04 09:46:38  taurel
// - Add a tuning method in the polling thread
// - Some minor fixes to pass test suite
//
// Revision 3.3.2.3  2004/10/22 11:25:50  taurel
// Added warning alarm
// Change attribute config. It now includes alarm and event parameters
// Array attribute property now supported
// subscribe_event throws exception for change event if they are not correctly configured
// Change in the polling thread: The event heartbeat has its own work in the work list
// Also add some event_unregister
// Fix order in which classes are destructed
// Fix bug in asynchronous mode (PUSH_CALLBACK). The callback thread ate all the CPU
// Change in the CORBA info call for the device type
//
// Revision 3.3.2.2  2004/09/27 09:09:07  taurel
// - Changes to allow reading state and/or status as attributes
//
// Revision 3.3.2.1  2004/09/15 06:46:28  taurel
// - Added four new types for attributes (boolean, float, unsigned short and unsigned char)
// - It is also possible to read state and status as attributes
// - Fix bug in Database::get_class_property() method (missing ends insertion)
// - Fix bug in admin device DevRestart command (device name case problem)
//
// Revision 3.3  2004/07/07 08:40:11  taurel
//
// - Fisrt commit after merge between Trunk and release 4 branch
// - Add EventData copy ctor, asiignement operator and dtor
// - Add Database and DeviceProxy::get_alias() method
// - Add AttributeProxy ctor from "device_alias/attribute_name"
// - Exception thrown when subscribing two times for exactly yhe same event
//
// Revision 3.2  2003/09/02 13:08:14  taurel
// Add memorized attribute feature (only for SCALAR and WRITE/READ_WRITE attribute)
//
// Revision 3.1  2003/08/21 07:37:04  taurel
// - End of the implementation of the new way to transfer data for read and
//   write attributes (better use of exception)
// - Added Attribute::set_date() and Attribute::set_value_date_quality() methods
// - Added DeviceAttribute ctors from "const char *"
// - Enable writing of spectrum and image attributes
// - Many new DeviceAttribute ctors/inserters to enable easy image and spectrums
//   attribute writing
// - Attribute date automatically set in case of attribute quality factor set to INVALID
// - Change in the polling thread discarding element algo. to support case of polling
//   several cmd/atts at the same polling period with cmd/attr having a long response time
// - Take cmd/attr execution time into account in the "Data not updated since" polling
//   status string
// - Split "str().c_str()" code in two lines of code. It was the reason of some problem
//   on Windows device server
// - Add the possibility to set a cmd/attr polling as "externally triggered". Add method
//   to send trigger to the polling thread
//
// Revision 3.0  2003/07/03 07:42:38  taurel
// - New IDL interface (Device3)
//
//=============================================================================

#ifndef _DEVICE_3_H
#define _DEVICE_3_H

#include <tango.h>

namespace Tango
{

class DeviceClass;
class AttributeValueList_4;

//=============================================================================
//
//			The Device_3Impl class
//
//
// description :	This class is derived directly from the Tango::Device_skel
//			class generated by CORBA. It represents the CORBA 
//			servant which will be accessed by the client. 
//			It implements all the methods
//			and attributes defined in the IDL interface for Device.
//
//=============================================================================

class Device_3ImplExt
{
public:
	Device_3ImplExt() {}
	virtual ~Device_3ImplExt() {}
	
	virtual	void		delete_dev() {}
};

struct AttIdx
{
	long	idx_in_names;
	long	idx_in_multi_attr;
	bool	failed;
};

/**
 * Base class for all TANGO device since version 3.
 *
 * This class inherits from DeviceImpl class which itself inherits from 
 * CORBA classes where all the network layer is implemented.
 * This class has been created since release 3 of Tango library where the IDL
 * Tango module has been modified in order to create a Device_3 interface
 * which inherits from the original Device interface
 *
 * $Author$
 * $Revision$
 */
 
class Device_3Impl : public virtual POA_Tango::Device_3,
		     public Device_2Impl
{
public:

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Device_3Impl object from its name.
 * 
 * The device description field is set to <i>A Tango device</i>. The device
 * state is set to unknown and the device status is set to 
 * <b>Not Initialised</b>
 *
 * @param 	device_class	Pointer to the device class object
 * @param	dev_name	The device name
 *
 */
	Device_3Impl(DeviceClass *device_class,string &dev_name);

/**
 * Constructs a newly allocated Device_3Impl object from its name and its description.
 *
 * The device
 * state is set to unknown and the device status is set to 
 * <i>Not Initialised</i>
 *
 * @param 	device_class	Pointer to the device class object
 * @param	dev_name	The device name
 * @param	desc	The device description
 *
 */		
	Device_3Impl(DeviceClass *device_class,string &dev_name,string &desc);

/**
 * Constructs a newly allocated Device_3Impl object from all its creation 
 * parameters.
 *
 * The device is constructed from its name, its description, an original state
 * and status
 *
 * @param 	device_class	Pointer to the device class object
 * @param	dev_name	The device name
 * @param	desc 		The device description
 * @param	dev_state 	The device initial state
 * @param	dev_status	The device initial status
 *
 */		
	Device_3Impl(DeviceClass *device_class,
	           string &dev_name,string &desc,
	           Tango::DevState dev_state,string &dev_status); 

/**
 * Constructs a newly allocated Device_3Impl object from all its creation 
 * parameters with some default values.
 *
 * The device is constructed from its name, its description, an original state
 * and status. This constructor defined default values for the description,
 * state and status parameters. The default device description is <i>A TANGO device</i>.
 * The default device state is <i>UNKNOWN</i> and the default device status 
 * is <i>Not initialised</i>.
 *
 * @param 	device_class	Pointer to the device class object
 * @param	dev_name	The device name
 * @param	desc	The device desc
 * @param	dev_state 	The device initial state
 * @param	dev_status	The device initial status
 *
 */		   
	Device_3Impl(DeviceClass *device_class,
	           const char *dev_name,const char *desc = "A TANGO device",
	           Tango::DevState dev_state = Tango::UNKNOWN,
	           const char *dev_status = StatusNotSet);
//@}

/**@name Destructor
 * Only one desctructor is defined for this class */
//@{
/**
 * The device desctructor.
 */		   
	virtual ~Device_3Impl() {delete ext_3;}
//@}


/**@name CORBA operation methods
 * Method defined to implement TANGO device CORBA operation */
//@{
	
/**
 * Read attribute(s) value.
 *
 * Invoked when the client request the read_attributes_2 CORBA operation.
 * It returns to the client one AttributeValue structure for each wanted
 * attribute.
 *
 * @param names The attribute(s) name list
 * @param source The data source. This parameter is new in Tango release 2. It
 * allows a client to choose the data source between the device itself or the
 * data cache for polled attribute.
 * @return A sequence of AttributeValue structure. One structure is initialised
 * for each wanted attribute with the attribute value, the date and the attribute 
 * value quality. Click <a href="../../../tango_idl/idl_html/_Tango.html#AttributeValue_3">here</a>
 * to read <b>AttributeValue_3</b> structure definition.
 * @exception DevFailed Thrown if the attribute does not exist.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevFailed">here</a> to read
 * <b>DevFailed</b> exception specification
 */
    	virtual Tango::AttributeValueList_3 *read_attributes_3(const Tango::DevVarStringArray& names,
							     Tango::DevSource source)
	throw (Tango::DevFailed, CORBA::SystemException);

/**
 * Write attribute(s) value.
 *
 * Invoked when the client request the write_attributes CORBA operation.
 * It sets the attribute(s) with the new value(s) passed as parameter.
 *
 * @param values The attribute(s) new value(s). One structure is initialised
 * for each wanted attribute with the attribute value. The attribute quality and
 * date are not used by this method.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#AttributeValue">here</a>
 * to read <b>AttributeValue</b> structure definition.
 * @exception DevFailed Thrown if the command does not exist.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevFailed">here</a> to read
 * <b>DevFailed</b> exception specification
 */
    	virtual void write_attributes_3(const Tango::AttributeValueList& values)
	throw (Tango::MultiDevFailed, Tango::DevFailed,CORBA::SystemException);

/**
 * Read attribute value history.
 *
 * Invoked when the client request the read_attribute_history_3 CORBA operation.
 * This operation allows a client to retrieve attribute value history for
 * polled attribute. The depth of the history is limited to the depth of
 * the device server internal polling buffer.
 * It returns to the client one DevAttrHistory structure for each record.
 *
 * @param name The attribute name
 * @param n The record number.
 * @return A sequence of DevAttrHistory structure. One structure is initialised
 * for each record with the attribute value, the date and in case of the attribute
 * returns an error when it was read, the DevErrors data.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevAttrHistory_3">here</a>
 * to read <b>DevAttrHistory_3</b> structure definition.
 * @exception DevFailed Thrown if the attribute does not exist or is not polled.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevFailed">here</a> to read
 * <b>DevFailed</b> exception specification
 */
	virtual Tango::DevAttrHistoryList_3 *read_attribute_history_3(const char* name,
								  CORBA::Long n)
	throw(Tango::DevFailed, CORBA::SystemException);

/**
 * Get device info.
 *
 * Invoked when the client request the info CORBA operation.
 * It updates the black box and returns a DevInfo object
 * with miscellaneous device info
 *
 * @return A DevInfo object
 */
	virtual Tango::DevInfo_3 *info_3() throw (Tango::DevFailed, CORBA::SystemException);

/**
 * Get attribute(s) configuration.
 *
 * Invoked when the client request the get_attribute_config_3 CORBA operation.
 * It returns to the client one AttributeConfig_3 structure for each wanted
 * attribute. All the attribute properties value are returned in this 
 * AttributeConfig_3 structure. Since Tango release 3, the attribute event
 * related, the attribute warning alarm and attribute rds alarm properties
 * have been added to the returned structures.
 *
 * @param names The attribute(s) name list
 * @return A sequence of AttributeConfig_3 structure. One structure is initialised
 * for each wanted attribute. Click <a href="../../../tango_idl/idl_html/_Tango.html#AttributeConfig_3">here</a>
 * to read <b>AttributeConfig_3</b> structure specification.
 *
 * @exception DevFailed Thrown if the attribute does not exist.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevFailed">here</a> to read
 * <b>DevFailed</b> exception specification
 */
    	virtual Tango::AttributeConfigList_3 *get_attribute_config_3(const Tango::DevVarStringArray& names)
        throw(Tango::DevFailed, CORBA::SystemException);

/**
 * Set attribute(s) configuration.
 *
 * Invoked when the client request the set_attribute_config_3 CORBA operation.
 * It updates the device attribute configuration actually used by the device but
 * this method also updates the Tango database. One structure of the
 * AttributeConfig_3 type is needed for each attribute to update configuration.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#AttributeConfig_3">here</a>
 * to read <b>AttributeConfig_3</b> structure specification.
 *
 * @param new_conf The attribute(s) new configuration structure sequence
 * @exception DevFailed Thrown if the command does not exist.
 * Click <a href="../../../tango_idl/idl_html/_Tango.html#DevFailed">here</a> to read
 * <b>DevFailed</b> exception specification
 */
    	virtual void set_attribute_config_3(const Tango::AttributeConfigList_3& new_conf)
    	throw (Tango::DevFailed, CORBA::SystemException);		
//@}
	void write_attributes_in_db(vector<long> &,vector<long> &);
	void add_state_status_attrs();

protected:
	void read_attributes_no_except(const Tango::DevVarStringArray&,Tango::AttributeValueList_3 *&,Tango::AttributeValueList_4 *&,bool,vector<long> &);
	void read_attributes_from_cache(const Tango::DevVarStringArray&,Tango::AttributeValueList_3 *&,Tango::AttributeValueList_4 *&);
	void write_attributes_in_db(vector<long> &,vector<AttIdx> &);
	void add_alarmed(vector<long> &);
	long reading_state_necessary(vector<AttIdx> &);
	void state2attr(Tango::DevState,Tango::AttributeValue_3 &);
	void state2attr(Tango::DevState,Tango::AttributeValue_4 &);
	void status2attr(Tango::ConstDevString,Tango::AttributeValue_3 &);
	void status2attr(Tango::ConstDevString,Tango::AttributeValue_4 &);
	void alarmed_not_read(vector<AttIdx> &);
	
	void write_attributes_34(const Tango::AttributeValueList *,const Tango::AttributeValueList_4 *);

public:
	void delete_dev() {ext_3->delete_dev();}	
		
protected:
	Device_3ImplExt				*ext_3;
};

} // End of Tango namespace

#endif // _DEVICE_H
