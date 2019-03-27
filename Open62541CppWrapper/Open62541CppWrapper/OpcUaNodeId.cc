//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#include "OpcUaNodeId.hh"

#include <sstream>

#ifdef HAS_OPCUA
#ifndef UA_ENABLE_AMALGAMATION
#include <open62541/ua_types_generated_handling.h>
#endif
#endif

namespace OPCUA {

NodeId::NodeId()
{
#ifdef HAS_OPCUA
	UA_NodeId_init(&_id);
	_id= UA_NODEID_NULL;
#endif
}

NodeId::~NodeId()
{
#ifdef HAS_OPCUA
	UA_NodeId_deleteMembers(&_id);
#endif
}


NodeId::NodeId(const std::string &id, const unsigned short &index)
{
#ifdef HAS_OPCUA
	_id = UA_NODEID_STRING_ALLOC(index, id.c_str());
#endif
}

NodeId::NodeId(const unsigned int &id, const unsigned short &index)
{
#ifdef HAS_OPCUA
	_id = UA_NODEID_NUMERIC(index, id);
#endif
}


void NodeId::copy(const NativeIdType &id, const bool cleanupPreviousId)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousId == true) {
		UA_NodeId_deleteMembers(&_id);
	}
	UA_NodeId_copy(&id, &_id);
#endif
}

NodeId::operator const NodeId::NativeIdType*() const
{
	return &_id;
}

NodeId::operator NodeId::NativeIdType() const
{
#ifdef HAS_OPCUA
	UA_NodeId id;
	UA_NodeId_copy(&_id, &id);
	return id;
#else
	return_id;
#endif
}

bool NodeId::operator ==(const NodeId &id) const
{
#ifdef HAS_OPCUA
	return UA_NodeId_equal(&_id, &id._id);
#else
	return _id == id._id;
#endif
}

bool NodeId::operator <(const NodeId &id) const
{
#ifdef HAS_OPCUA
	return (_id.identifier.numeric < id._id.identifier.numeric);
#else
	return _id < id._id;
#endif
}

bool NodeId::isNull() const
{
#ifdef HAS_OPCUA
	return UA_NodeId_isNull(&_id);
#else
	return _id.empty();
#endif
}

/// returns true if ID is a numeric type
bool NodeId::isNumericType() const
{
#ifdef HAS_OPCUA
	return (_id.identifierType == UA_NODEIDTYPE_NUMERIC);
#else
	return false;
#endif
}

/// returns true if ID is a numeric type
bool NodeId::isStringType() const
{
#ifdef HAS_OPCUA
	return (_id.identifierType == UA_NODEIDTYPE_STRING);
#else
	return true;
#endif
}


std::string NodeId::getSimpleName() const
{
#ifdef HAS_OPCUA
	if(isStringType()==true) {
		return std::string((const char*)_id.identifier.string.data, _id.identifier.string.length);
	} else if(isNumericType()) {
		std::stringstream ss;
		ss << _id.identifier.numeric;
		return ss.str();
	}
	return std::string();
#else
	return _id;
#endif
}

} /* namespace OPCUA */
