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

#ifndef TRAFFICLIGHTTVIEW_H_
#define TRAFFICLIGHTTVIEW_H_

#include <MVC/AbstractView.hh>

#include "Pixtend2DriverModel.h"
	
namespace Smart {

/**
 * This class implements the View part of the Model-View-Controller (MVC)
 * design pattern. Please implement the method update() to realize your
 * view update strategy. In addition, it is recommended to refine the
 * method getModel() such that it returns your specific model class
 * rather than the AbstractModel. This is particularly useful for the
 * Controller class of the MVC pattern.
 */
class TrafficlightView : public AbstractView
{
public:
	/// constructor requires a pointer to a specific model
	TrafficlightView(Pixtend2DriverModel *model);
	virtual ~TrafficlightView();

	/// implements AbstractModelObserver
	virtual void update() override;

	/// returns a pointer to the internally used model
	virtual Pixtend2DriverModel* getModel() const override;
};

} /* namespace Smart */

#endif /* TRAFFICLIGHTTVIEW_H_ */