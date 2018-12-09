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

#include "OpcUaGenericClient.hh"

#include <vector>
#include <sstream>
#include <functional>

namespace OPCUA {

#ifdef HAS_OPCUA
static void
inactivityCallback (UA_Client *client)
{
	//TODO: check if this method is of any use
	std::cerr << "Server Inactivity" << std::endl;
}

#ifdef UA_ENABLE_SUBSCRIPTIONS
// this is an internal registry map that connects subscription handle_entity_update(...)
// method with the client's handleEntity(...) object-member-method
static std::map<UA_UInt32,std::function<void(const UA_UInt32&,UA_DataValue*)>> subscription_bindings;

// static and generic subscription handling method (shared by all client instances)
static void
handle_entity_update(UA_Client *client, UA_UInt32 subId, void *subContext,
                         UA_UInt32 monId, void *monContext, UA_DataValue *value)
{
	auto it = subscription_bindings.find(subId);
	if(it != subscription_bindings.end()) {
		// call bound function
		it->second(subId, value);
	}
}


static std::map<UA_Client*,std::function<void(const UA_UInt32&,UA_Variant*)>> on_read_registry;

static
void handle_on_read (UA_Client *client, void *userdata, UA_UInt32 requestId, UA_Variant *value)
{
	auto it = on_read_registry.find(client);
	if(it != on_read_registry.end()) {
		// call bound function
		it->second(requestId, value);
	}

    /*more type distinctions possible*/
    return;
}
static
void attrWritten (UA_Client *client, void *userdata, UA_UInt32 requestId, UA_WriteResponse *response)
{
    /*assuming no data to be retrieved by writing attributes*/
    UA_WriteResponse_deleteMembers(response);
}
#endif

bool GenericClient::hasEndpoints(const std::string &address, const bool &display)
{
    // Listing endpoints
    UA_EndpointDescription* endpointArray = NULL;
    size_t endpointArraySize = 0;
    UA_StatusCode retval = UA_Client_getEndpoints(client, address.c_str(),
                                                  &endpointArraySize, &endpointArray);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Array_delete(endpointArray, endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        return false;
    }
    if(display==true) {
    	printf("%i endpoints found\n", (int)endpointArraySize);
        for(size_t i=0;i<endpointArraySize;i++) {
            printf("URL of endpoint %i is %.*s\n", (int)i,
                   (int)endpointArray[i].endpointUrl.length,
                   endpointArray[i].endpointUrl.data);
        }
    }
    UA_Array_delete(endpointArray,endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
    return (endpointArraySize > 0);
}
#endif // HAS_OPCUA

GenericClient::GenericClient()
{
#ifdef HAS_OPCUA
	// set client to initially to zero (the real initialization happens during connection)
	client = 0;

	// default parent object is the default Objects Folder
	rootObjectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
#endif // HAS_OPCUA
}

GenericClient::~GenericClient()
{
	// make sure the client is disconnected before destroying this instance
	this->disconnect();
}

OPCUA::StatusCode GenericClient::connect(const std::string &address, const std::string &objectName, const bool activateUpcalls)
{
	// make sure the client is disconnected in any case
	this->disconnect();
#ifdef HAS_OPCUA
	UA_ClientConfig config = UA_ClientConfig_default;
	/* Set stateCallback */
	config.inactivityCallback = inactivityCallback;
	/* Perform a connectivity check every 2 seconds */
	config.connectivityCheckInterval = 2000;

	// create a new client
	client = UA_Client_new(config);

	if( hasEndpoints(address) == true ) 
	{
		// Connect client to a server
		UA_StatusCode retval = UA_Client_connect(client, address.c_str());
		//retval = UA_Client_connect_username(client, "opc.tcp://localhost:4840", "user1", "password");
		if(retval != UA_STATUSCODE_GOOD) {
			UA_Client_delete(client);
			client = 0;
			return OPCUA::StatusCode::ERROR_COMMUNICATION;
		}

		// find the root object using its browseName under the default objects folder
		rootObjectId = this->findElement(objectName,
			UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), // the the default objects folder as parent
			UA_NODECLASS_OBJECT // look for object types only
		);
		if(rootObjectId.isNull()) {
			// if the object could no be found -> disconnect client and return wrong ID
			this->disconnect();
			return OPCUA::StatusCode::WRONG_ID;
		}

		on_read_registry[client] = std::bind(&GenericClient::handleReadRequest, this, std::placeholders::_1, std::placeholders::_2);

		// call the method that hopefully creates the client space in derived classes
		if( this->createClientSpace(activateUpcalls) == true ) {
			// client is now connected
			return OPCUA::StatusCode::ALL_OK;
		}
	} else {
		UA_Client_delete(client);
		client = 0;
	}
#endif // HAS_OPCUA
	// something else went wrong
	return OPCUA::StatusCode::ERROR_COMMUNICATION;
}

bool GenericClient::createClientSpace(const bool activateUpcalls)
{
	// no-op
	return true;
}

OPCUA::StatusCode GenericClient::disconnect()
{
#ifdef HAS_OPCUA
	// disconnect and clean-up client
	if(client != 0) {
	    UA_Client_disconnect(client);
	    UA_Client_delete(client);
	    client = 0;
	}
#endif // HAS_OPCUA
	return OPCUA::StatusCode::ALL_OK;
}

#ifdef HAS_OPCUA
/**
 * This implementation used a somewhat complicated low-level API at the moment because the client's
 * high-level API seems not yet to be implemented. This implementation can be simplified in the future when
 * the high level API is provided.
 */
NodeId GenericClient::browseObjectPath(const std::string &objectPath, const unsigned short namespaceIndex) const
{
    // create new node id
    NodeId nodeId;

    // parse path
	std::vector<std::string> path_segments;
	std::stringstream ss(objectPath);
	std::string segment;
	const char delimiter = '/';
	// parse path to get individual path elements
	while(std::getline(ss, segment, delimiter)) {
		path_segments.push_back(segment);
	}

	if(path_segments.size() > 0)
	{
		// create a UA relative-path struct array and fill it with values
		UA_RelativePathElement* ua_paths = (UA_RelativePathElement*)UA_Array_new(path_segments.size(), &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
		for(size_t i = 0; i < path_segments.size(); i++) {
			if(i==0) {
				// the first element is assumed to be the object type, hence, use the UA_NS0ID_ORGANIZES typeId
				ua_paths[i].referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
			} else {
				// all the following path elements are assumed to be components
				ua_paths[i].referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
			}
			ua_paths[i].targetName = UA_QUALIFIEDNAME_ALLOC(namespaceIndex, path_segments[i].c_str());
		}

		// create the browse-path struct
		UA_BrowsePath browsePath;
		UA_BrowsePath_init(&browsePath);
		// use the default objects foulder as root
		browsePath.startingNode = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
		browsePath.relativePath.elements = ua_paths;
		browsePath.relativePath.elementsSize = path_segments.size();

		// create the request struct including the browse path
		UA_TranslateBrowsePathsToNodeIdsRequest request;
		UA_TranslateBrowsePathsToNodeIdsRequest_init(&request);
		request.browsePaths = &browsePath;
		request.browsePathsSize = 1;

		// call the browse service
		UA_TranslateBrowsePathsToNodeIdsResponse response = UA_Client_Service_translateBrowsePathsToNodeIds(client, request);

		if(response.responseHeader.serviceResult == UA_STATUSCODE_GOOD) {
			if(response.resultsSize > 0 && response.results[0].targetsSize > 0) {
				// we just get the first target's node-id (typically there should be just one single target found, if any)
				nodeId = response.results[0].targets[0].targetId.nodeId;
			}
		}

		// cleanup allocated memory
		UA_BrowsePath_deleteMembers(&browsePath);
		UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);
	} // end if(path_elements.size() > 0)

	// nodeId is UA_NODEID_NULL in case the element has no been found
	return nodeId;
}

NodeId GenericClient::findElement(const std::string &elementBrowseName, const NodeId &parentNodeId, const UA_NodeClass &filterNodeType) const
{
	// new id
	NodeId resultId;

    // create default browse request
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    // use given nodeId as parent (default is UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER))
    bReq.nodesToBrowse[0].nodeId = parentNodeId;
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */

    // call the browse service
    UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

    // look for the element with the given name within the response
    for(size_t i = 0; i < bResp.resultsSize; ++i)
    {
    	// pointer to the browse-results struct
    	UA_BrowseResult *result = &(bResp.results[i]);
        for(size_t j = 0; j < result->referencesSize; ++j)
        {
        	UA_ReferenceDescription *ref = &(result->references[j]);
            // check the node-class type
            if(ref->nodeClass == filterNodeType) {
            	// check the browseName
            	std::string browseName((const char*)ref->browseName.name.data, ref->browseName.name.length);
            	if(browseName == elementBrowseName) {
            		// copy node id into the variable that is returned below
                    resultId = ref->nodeId.nodeId;
                    // we only use the first match and ignore further possible matches
                    break;
            	}
            }
        }
    }
    // cleanup allocated memory
    UA_BrowseRequest_deleteMembers(&bReq);
    UA_BrowseResponse_deleteMembers(&bResp);

    // nodeId can also be NULL in case that the searched element was not found
    return resultId;
}

UA_StatusCode GenericClient::registerNode(const NodeId &nodeId)
{
    UA_RegisterNodesRequest request;
    UA_RegisterNodesRequest_init(&request);

    request.nodesToRegister = UA_NodeId_new();
    // example: req.nodesToRegister[0] = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);
    request.nodesToRegister[0] = nodeId;
    request.nodesToRegisterSize = 1;

    UA_RegisterNodesResponse response = UA_Client_Service_registerNodes(client, request);

    // copy result
    UA_StatusCode result = response.responseHeader.serviceResult;

    // store result-nodeIds if needed
    if(result == UA_STATUSCODE_GOOD && response.registeredNodeIdsSize > 0) {
//    	std::cout << "registered node: " << nodeId.identifier.numeric <<
//    			" now is: " << response.registeredNodeIds[0].identifier.numeric << std::endl;
//    UA_NodeId nodeId = res.registeredNodeIds[0];
    }

    UA_RegisterNodesRequest_deleteMembers(&request);
    UA_RegisterNodesResponse_deleteMembers(&response);

    return result;
}

UA_StatusCode GenericClient::unregisterNode(const NodeId &nodeId)
{
    UA_UnregisterNodesRequest reqUn;
    UA_UnregisterNodesRequest_init(&reqUn);

    reqUn.nodesToUnregister = UA_NodeId_new();
    reqUn.nodesToUnregister[0] = nodeId;
    reqUn.nodesToUnregisterSize = 1;

    UA_UnregisterNodesResponse resUn = UA_Client_Service_unregisterNodes(client, reqUn);
    UA_StatusCode result = resUn.responseHeader.serviceResult;

    UA_UnregisterNodesRequest_deleteMembers(&reqUn);
    UA_UnregisterNodesResponse_deleteMembers(&resUn);

    return result;
}


OPCUA::StatusCode GenericClient::checkAndGetEntityId(const std::string &entityBrowseName, NodeId &entityId, const UA_NodeClass &filterNodeType) const
{
	// check if client is connected, if not, return immediately
	if(client == 0) {
		return OPCUA::StatusCode::DISCONNECTED;
	}

	// look for an entity name under the given object
	auto entityIt = entityRegistry.find(entityBrowseName);
	if(entityIt != entityRegistry.end()) {
		entityId = entityIt->second;
	} else {
		// browse for the entity ID on the fly (please implement the createClientSpace() to prevent on-the-fly browsing
		entityId = this->findElement(entityBrowseName, rootObjectId, filterNodeType);
	}

	// check that the entityId has been found
	if(entityId.isNull()) {
		return OPCUA::StatusCode::WRONG_ID;
	}

    return OPCUA::StatusCode::ALL_OK;
}


UA_StatusCode GenericClient::createSubscription(const std::string &entityBrowseName, const unsigned int samplingIntervalMS)
{
	// try getting the entity ID
	NodeId entityId;
	OPCUA::StatusCode result = checkAndGetEntityId(entityBrowseName, entityId);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return UA_STATUSCODE_BADSUBSCRIPTIONIDINVALID;
	}
#ifdef UA_ENABLE_SUBSCRIPTIONS
    /* Create a subscription */
    UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
    request.requestedPublishingInterval = samplingIntervalMS;
    UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request,
                                                                            NULL, NULL, NULL);

    if(response.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
    	// subscription failed, return immediately
    	return response.responseHeader.serviceResult;
    }

    // save the entity-name for the new subscription-id
    subscriptionsRegistry[response.subscriptionId] = entityBrowseName;

    // create upcall binding
    subscription_bindings[response.subscriptionId] = std::bind(&GenericClient::handleEntity, this, std::placeholders::_1, std::placeholders::_2);

    // create a monitored item
    UA_MonitoredItemCreateRequest monRequest = UA_MonitoredItemCreateRequest_default(entityId);
    monRequest.requestedParameters.samplingInterval = samplingIntervalMS;
    UA_MonitoredItemCreateResult monResponse =
    UA_Client_MonitoredItems_createDataChange(client, response.subscriptionId,
                                              UA_TIMESTAMPSTORETURN_BOTH,
                                              monRequest, NULL, handle_entity_update, NULL);
    UA_MonitoredItemCreateRequest_deleteMembers(&monRequest);
    return monResponse.statusCode;
#else
    return UA_STATUSCODE_BADSUBSCRIPTIONIDINVALID;
#endif
}

UA_StatusCode GenericClient::deleteSubscription(const std::string &entityBrowseName)
{
#ifdef UA_ENABLE_SUBSCRIPTIONS
	for(auto it=subscriptionsRegistry.begin(); it!=subscriptionsRegistry.end(); it++) {
		// search for the entity to unsubscribe
		if(it->second == entityBrowseName) {
			// delete a single subscription
			return UA_Client_Subscriptions_deleteSingle(client, it->first);
		}
	}
#endif
    return UA_STATUSCODE_BADSUBSCRIPTIONIDINVALID;
}

void GenericClient::handleEntity(const UA_UInt32 &subscriptionId, UA_DataValue *data)
{
	// extract the actual value
	OPCUA::ValueType value(data->value);

	auto it = subscriptionsRegistry.find(subscriptionId);
	if(it != subscriptionsRegistry.end())
	{
		{
			// acquire the entityUpdateMutex
			std::unique_lock<std::mutex> entityUpdateLock(entityUpdateMutex);
			// store the update for the respective entity
			entityUpdateValueRegistry[it->second] = value;
			// notify all waiting clients
			entityUpdateSignalRegistry[it->second].notify_all();
		}
		// propagate the update handling to the user method implemented in derived classes
		this->handleVariableValueUpdate(it->second, value);
	}
}
#endif // HAS_OPCUA


void GenericClient::handleVariableValueUpdate(const std::string &variableBrowseName, const OPCUA::ValueType &value)
{
	// no-op
}

bool GenericClient::addVariableNode(const std::string &entityBrowseName, const bool activateUpdateUpcall, const unsigned int samplingIntervalMS)
{
#ifdef HAS_OPCUA
	// try getting the entity ID
	NodeId entityId;
	OPCUA::StatusCode result = checkAndGetEntityId(entityBrowseName, entityId);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return false;
	}

	// save the entity ID within the internal registry
	entityRegistry[entityBrowseName] = entityId;
	
	if(activateUpdateUpcall == true) {
		// create subscription for the current entity
		this->createSubscription(entityBrowseName, samplingIntervalMS);
	}
	return true;
#else
	return false;
#endif // HAS_OPCUA
}

bool GenericClient::addMethodNode(const std::string &methodBrowseName)
{
#ifdef HAS_OPCUA
	NodeId methodId;
	OPCUA::StatusCode result = checkAndGetEntityId(methodBrowseName, methodId, UA_NODECLASS_METHOD);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return false;
	}

	// save the method ID within the internal registry
	entityRegistry[methodBrowseName] = methodId;
	return true;
#else
	return false;
#endif // HAS_OPCUA
}

void GenericClient::handleReadRequest(const UA_UInt32 &requestId, UA_Variant *data)
{
	std::unique_lock<std::mutex> readRequestLock(readRequestMutex);
	readRequestValueRegistry[requestId] = *data;
	readRequestSignal.notify_all();
}


OPCUA::StatusCode GenericClient::getVariableCurrentValue(const std::string &variableName, OPCUA::ValueType &value) const
{
	OPCUA::StatusCode result = OPCUA::StatusCode::ERROR_COMMUNICATION;
#ifdef HAS_OPCUA
	// check if the entity ID can be found
	NodeId entityId;
	result = checkAndGetEntityId(variableName, entityId);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return result;
	}

	// Read attribute value
	UA_NodeId uaId = entityId;
	UA_UInt32 requestId = 0;

	// don't use the synchronous (i.e. direct) access to variables as it will conflict with the asynchronous API
//	UA_StatusCode retval = UA_Client_readValueAttribute(client, uaId, variant);
	UA_StatusCode retval = UA_Client_readValueAttribute_async(client, uaId, handle_on_read, NULL, &requestId);
	if(retval == UA_STATUSCODE_GOOD) {
		while(true)
		{
			// grab the mutex
			std::unique_lock<std::mutex> readRequestLock(readRequestMutex);
			// wait for a read-request to finish
			readRequestSignal.wait(readRequestLock);
			// check if the registry has the result
			auto it = readRequestValueRegistry.find(requestId);
			// if request has been processed, then get the value and exit the while loop
			if(it != readRequestValueRegistry.end()) {
				// copy variant value
				value = it->second;
				// clean-up registry entry
				readRequestValueRegistry.erase(it);
				break;
			}
			// the required read request has not yet been processed -> wait for another signal
		}
		result = OPCUA::StatusCode::ALL_OK;
	} else {
		result = OPCUA::StatusCode::ERROR_COMMUNICATION;
	}
	UA_NodeId_deleteMembers(&uaId);
#endif // HAS_OPCUA
	return result;
}

OPCUA::StatusCode GenericClient::getVariableNextValue(const std::string &variableName, OPCUA::ValueType &value)
{
	OPCUA::StatusCode result = OPCUA::StatusCode::ERROR_COMMUNICATION;
#ifdef HAS_OPCUA
	// check if the entity ID can be found
	NodeId entityId;
	result = checkAndGetEntityId(variableName, entityId);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return result;
	}

	// acquire the entityUpdateMutex
	std::unique_lock<std::mutex> entityUpdateLock(entityUpdateMutex);
	// blocking wait until the entity is released
	entityUpdateSignalRegistry[variableName].wait(entityUpdateLock);
	// copy the updated value
	value = entityUpdateValueRegistry[variableName];
#endif // HAS_OPCUA
	// return result
	return result;
}

OPCUA::StatusCode GenericClient::setVariableValue(const std::string &variableName, const OPCUA::ValueType &value)
{
	OPCUA::StatusCode result = OPCUA::StatusCode::ERROR_COMMUNICATION;
#ifdef HAS_OPCUA
	// check if the entity ID can be found
	NodeId entityId;
	result = checkAndGetEntityId(variableName, entityId);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return result;
	}

	// write attribute value
	UA_UInt32 reqId;
	UA_StatusCode retval = UA_Client_writeValueAttribute_async(client, entityId, value, attrWritten, NULL, &reqId);
	if(retval == UA_STATUSCODE_GOOD) {
    	result = OPCUA::StatusCode::ALL_OK;
	} else {
		result = OPCUA::StatusCode::ERROR_COMMUNICATION;
	}
#endif // HAS_OPCUA
	// return result
	return result;
}

OPCUA::StatusCode GenericClient::callMethod(const std::string &methodName,
                        const std::vector<OPCUA::ValueType> &inputArguments,
                        std::vector<OPCUA::ValueType> &outputArguments)
{
#ifdef UA_ENABLE_METHODCALLS
	// check if the method ID can be found
	NodeId methodId;
	OPCUA::StatusCode result = checkAndGetEntityId(methodName, methodId, UA_NODECLASS_METHOD);
	if(result != OPCUA::StatusCode::ALL_OK) {
		return result;
	}

	// create input arguments
	std::vector<UA_Variant> uaInputArguments(inputArguments.size());
	for(size_t i=0; i<inputArguments.size(); ++i) {
		uaInputArguments[i] = inputArguments[i];
	}

	// output variables
	size_t outputSize=0;
	UA_Variant *output;

	// call the method (using high-level interface)
	UA_StatusCode retval = UA_Client_call(client,
    	rootObjectId, 	// the parent object ID
		methodId,		// the current method ID
		inputArguments.size(), uaInputArguments.data(), // input arguments
		&outputSize, &output // output arguments
	);

	if(retval == UA_STATUSCODE_GOOD) {
		// collect and return the output arguments
		outputArguments.resize(outputSize);
		for(size_t i=0; i<outputSize; ++i) {
			outputArguments[i] = output[i];
		}
		// cleanup output arguments memory
		UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
		// cleanup input arguments memory
		for(size_t i=0; i<uaInputArguments.size(); ++i) {
			UA_Variant_deleteMembers(&uaInputArguments[i]);
		}
		// return SUCCESS
		return OPCUA::StatusCode::ALL_OK;
	}
#endif
	return OPCUA::StatusCode::ERROR_COMMUNICATION;
}

OPCUA::StatusCode GenericClient::run_once(const std::string &address, const unsigned short &timeoutMS)
{
#ifdef HAS_OPCUA
	if(client == 0) {
		UA_sleep_ms(timeoutMS);
		return OPCUA::StatusCode::DISCONNECTED;
	}
	/* if already connected, this will return GOOD and do nothing */
	/* if the connection is closed/errored, the connection will be reset and then reconnected */
	/* Alternatively you can also use UA_Client_getState to get the current state */
	//UA_ClientState clientState = UA_Client_getState(client);
	UA_StatusCode status = UA_Client_connect(client, address.c_str());
	if(status != UA_STATUSCODE_GOOD) {
		std::cerr << "client connection status != UA_STATUSCODE_GOOD: " << status << std::endl;
		/* The connect may timeout after 1 second (see above) or it may fail immediately on network errors */
		/* E.g. name resolution errors or unreachable network. Thus there should be a small sleep here */
		UA_sleep_ms(timeoutMS);
		return OPCUA::StatusCode::DISCONNECTED;
	}
	// run client's callback interface with 500ms timeout
	UA_Client_run_iterate(client, timeoutMS);
	return OPCUA::StatusCode::ALL_OK;
#else
	return OPCUA::StatusCode::ERROR_COMMUNICATION;
#endif
}

} /* namespace OPCUA */
