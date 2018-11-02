#include "mousemovement.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseMotion.hpp>
#include <InputEvent.hpp>
#include <Object.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>

using namespace godot;

void CameraMovement::_register_methods() {
    register_method((char *)"_process", &CameraMovement::_process);
    register_method((char *)"_input", &CameraMovement::_input);
}

CameraMovement::CameraMovement() {
    // initialize any variables here
    time_passed = 0.0;
    viewport_size = Vector2(1920, 1080); //TODO: get the screen resolution, by getting the viewport
}

CameraMovement::~CameraMovement() {
    // add your cleanup here
}

void CameraMovement::_process(float delta) {

	const int SPEED = 12; //TODO: move this to the class

	Vector2 speed = Vector2(SPEED, SPEED);
	owner->set_position(owner->get_position()+process_direction*speed);


}

void CameraMovement::_input(Variant event) {

	Label *a = (Label *)owner->get_node("Label"); //TODO: rename a to label

	const Vector2 LEEWAY = viewport_size/8;
	const Vector2 VEC2_ZERO = Vector2(0, 0);
	Vector2 direction = Vector2(0, 0);

	Vector2 iemm_pos;

	if (((InputEvent *)((Object *)event))->get_class() == "InputEventMouseMotion") {
		InputEventMouse *iemm = (InputEventMouse *)((Object *)event); //TODO: rename *iemm to iem

		iemm_pos = iemm->get_position();

		// X-AXIS
		if (iemm_pos[0] >= (viewport_size-LEEWAY)[0]) {
			direction += Vector2(1, 0);
		} else if (iemm_pos[0] <= (VEC2_ZERO+LEEWAY)[0]) {
			direction += Vector2(-1, 0);
		}

		// Y-AXIS
		if (iemm_pos[1] >= (viewport_size-LEEWAY)[1]) {
			direction += Vector2(0, 1);
		} else if (iemm_pos[1] <= (VEC2_ZERO+LEEWAY)[1]) {
			direction += Vector2(0, -1);
		}

		//check if the direction is not 0, 0
		if (direction != VEC2_ZERO) {
			process_direction = direction;
			owner->set_process(true);
		} else {
			owner->set_process(false);
			process_direction = VEC2_ZERO;
		}

		//position of the iem
		a->set_text(iemm_pos);

	}

}
