//===================================================================================
//
//  Copyright (C) 2019 Alex Lotz, Vineet Nagrath
//
//        lotz@hs-ulm.de
//        nagrath@hs-ulm.de
//
//        Servicerobotik Ulm
//        Christian Schlegel
//        Ulm University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm
//        Germany
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//===================================================================================

#ifndef JOYSTICKTVIEW_H_
#define JOYSTICKTVIEW_H_

#include <MVC/AbstractView.hh>

#include "LinuxJoystickDriverModel.hh"

namespace Smart {

/**
 * This class implements the View part of the Model-View-Controller (MVC)
 * design pattern. Please implement the method update() to realize your
 * view update strategy. In addition, it is recommended to refine the
 * method getModel() such that it returns your specific model class
 * rather than the AbstractModel. This is particularly useful for the
 * Controller class of the MVC pattern.
 */
class JoystickView : public AbstractView
{
public:
	/// constructor requires a pointer to a specific model
	JoystickView(LinuxJoystickDriverModel *model);
	virtual ~JoystickView();

	/// implements AbstractModelObserver
	virtual void update() override;

	/// returns a pinter to the internally used model
	virtual LinuxJoystickDriverModel* getModel() const override;
};

} /* namespace Smart */

#endif /* JOYSTICKTVIEW_H_ */
