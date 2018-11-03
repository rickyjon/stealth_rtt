#include "cameramovement.h"
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
    register_method((char *)"_ready", &CameraMovement::_ready);
    register_method((char *)"_input", &CameraMovement::_input);
}

CameraMovement::CameraMovement() {}
CameraMovement::~CameraMovement() {}

void CameraMovement::_process(float delta) {

	owner->set_position(owner->get_position()+process_direction*Vector2(camera_speed, camera_speed));

}

void CameraMovement::_ready() {

	viewport_size = owner->get_viewport()->get("size");
	viewport_leeway = viewport_size/8;
	camera_speed = 8;

}

void CameraMovement::_input(Variant event) {


	Label *a = (Label *)owner->get_node("Label"); //TODO: rename a to label


	const Vector2 VEC2_ZERO = Vector2(0, 0);
	Vector2 direction = Vector2(0, 0);

	Vector2 iemm_pos;

	if (((InputEvent *)((Object *)event))->get_class() == "InputEventMouseMotion") {
		InputEventMouse *iem = (InputEventMouse *)((Object *)event); //TODO: rename *iem to iem

		iem_pos = iem->get_position();

		// X-AXIS
		if (iem_pos.x >= (viewport_size-viewport_leeway).x) {
			direction += Vector2(1, 0);
		} else if (iem_pos.x <= (VEC2_ZERO+viewport_leeway).x) {
			direction += Vector2(-1, 0);
		}

		// Y-AXIS
		if (iem_pos.y >= (viewport_size-viewport_leeway).y) {
			direction += Vector2(0, 1);
		} else if (iem_pos.y <= (VEC2_ZERO+viewport_leeway).y) {
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
