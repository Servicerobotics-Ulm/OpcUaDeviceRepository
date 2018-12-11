//============================================================================
// Name        : OpcUaSimpleClient.cpp
// Author      : Alexej
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "OpcUaGenericClient.hh"

#include <chrono>
#include <thread>
#include <mutex>

std::mutex mutex;

class MyClient: public OPCUA::GenericClient {
protected:
	virtual void handleVariableValueUpdate(const std::string &entityName, const OPCUA::ValueType &value) override
	{
		std::cout << "handleEntityUpdate(" << entityName << "): " << value << std::endl;
	}

	virtual bool createClientSpace(const bool activateUpcalls=true) override
	{
		std::chrono::steady_clock::duration interval = std::chrono::milliseconds(100);
		return addVariableNode("MyVar", activateUpcalls, interval);
	}
public:
	MyClient() { }
	virtual ~MyClient() { }
};

void run(MyClient *client) {
	OPCUA::StatusCode status;
	do {
		std::cout << "run_once()..." <<std::endl;
		status = client->run_once();
	} while(status == OPCUA::StatusCode::ALL_OK);
}

int main(int argc, char* argv[]) 
{
	std::string address = "opc.tcp://localhost:4840";
	std::string objectName;	
	if(argc < 2) {
		std::cerr << "Usage: ./SimpleClient <RootObjectName>" << std::endl;
		return -1;
	} else {
		objectName = argv[1];
	}

	// create and connect client
	MyClient client;
	std::cout << "connecting client: " << client.connect(address, objectName) << std::endl;

	// call a remote method at the sever
	std::vector<OPCUA::ValueType> inputArguments(2);
	inputArguments[0] = 100;
	inputArguments[1] = std::string("Hello");
	std::vector<OPCUA::ValueType> outputArguments;
	std::cout << "call method MyMethod: " << client.callMethod("MyMethod", inputArguments, outputArguments) << std::endl;
	for(size_t i=0; i<outputArguments.size(); ++i) {
		std::cout << "output" << i << ": " << outputArguments[i] << std::endl;
	}

	// execute client's upcall interface (i.e. its method "run_once()") in a separate thread (just for testing, can also be executed in this main)
	std::thread th(run, &client);

	while(true) {
		OPCUA::ValueType v;
		// actively poll for variable values
		client.getVariableCurrentValue("MyVar", v);
		std::cout << "polling MyVar: " << v << std::endl;
		std::this_thread::sleep_for (std::chrono::milliseconds(50));
	}

	th.join();
	return 0;
}
