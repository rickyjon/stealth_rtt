#include "cameramovement.h"
//#include "unitcontroller.h"
//#include "unit.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseMotion.hpp>
#include <InputEvent.hpp>
#include <Object.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>
#include <Node2D.hpp>
#include <Array.hpp>
#include <String.hpp>

using namespace godot;

void CameraMovement::_register_methods() {

	register_method((char *)"_process", &CameraMovement::_process);
	register_method((char *)"_ready", &CameraMovement::_ready);
	register_method((char *)"_input", &CameraMovement::_input);

}

CameraMovement::CameraMovement() {}
CameraMovement::~CameraMovement() {}

void CameraMovement::_process(float delta) {

	owner->set_position(owner->get_position()+process_direction
		*Vector2(camera_speed, camera_speed));

}

void CameraMovement::_ready() {

	viewport_size = owner->get_viewport()->get("size");
	viewport_leeway = viewport_size/8;
	camera_speed = 8;

	Array arr = owner->get_tree()->get_nodes_in_group("unit_squad");
	Unit *u = (Unit *)(Object *)arr[0];
	Area2D *a = (Area2D *)(Object *)arr[0];
	//u->selected = false;
	u->selected = true;
	a->set("selected", true);



}

/**
 * Get the vector of any mouse movement and
 * set the _process to true if it's in near the edge of the screen.
 */
void CameraMovement::_input(Variant event) {

	InputEvent *ie = (InputEvent *)(Object *)event;

	if (ie->get_class() == "InputEventMouseMotion") {
		directional_edge(ie);
	} else {
		if (ie->is_action("camera_center")) {
			center_camera();
		} else if (ie->is_action("unit_1")) {
			move_camera_unit(0);
			Godot::print("Pressed Key 1");
		} else if (ie->is_action("unit_2")) {
			move_camera_unit(1);
			Godot::print("Pressed Key 2");
		} else if (ie->is_action("unit_3")) {
			move_camera_unit(3);
		} else if (ie->is_action("unit_4")) {
			move_camera_unit(4);
		} //for the sake of this game, limit to 4 characters

	}

}

void CameraMovement::center_camera() {

	Label *label = (Label *)owner->get_node("Label");
	Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
	/*Camera2D *c = ((Camera2D *)owner->get_parent()->get_parent()
					->get_node("Camera2D"));*/

	int i = 0;
	int l = a.size();

	while (i < l) {

		Unit *up = (Unit *)(Object *)a[i];
		//Area2D *n = (Area2D *)(Object *)a[i];
		//Unit &ru = (Unit &)(Object &)a[i];
		//Unit u = (Unit &)(Object &)a[i];
		if (up->selected) {
		//if (u.selected) {

			label->set_text("Selected Unit "+String::num(i+1));
			Node2D *n = (Node2D *)(Object *)a[i];
			owner->set_position(n->get_position());
			//u->open_arr = a;
			break;
		}
		++i;

	}

}

void CameraMovement::move_camera_unit(int i) {

	Label *label = (Label *)owner->get_node("Label");
	Array arr = owner->get_tree()->get_nodes_in_group("unit_squad");
	//Array *var =(Array *)new Array();
//		var->append(false);

	int k = 0;
	int l = arr.size();

	//owner->get_tree()->call_group("unit_squad",
	//		"set_visible", var); //why the hell does this not work
	while(k < l) {
		Unit *up = (Unit *)(Object *)arr[k];
		//Unit &ru = (Unit &)(Object &)a[k];
		//Unit u = (Unit &)(Object &)a[k];
		//NodePath np = ((Node2D *)(Object *)a[k])->get_path();

		//Godot::print(np);
		//if (!np.is_empty()) {
			//Unit *tmp = (Unit *)owner->get_node(np);
			//	tmp->selected = false;
		//NodePath np = ((Node2D *)(Object *)a[k])->get_path();
		up->selected = false;
		Area2D *n = (Area2D *)(Object *)arr[k];
		n->set("selected", false);


		//}
		//ru.selected = false;
		//((Unit *)(Object *)a[k])->selected = false;
		//u.selected = false;

		++k;
	}

	if (i < l) {
		Node2D *n = (Node2D *)(Object *)arr[i];
		//Variant &v = a[i];
		Unit *up = (Unit *)(Object *)arr[i];
		//Area2D *a = (Area2D *)(Object *)a[i];
		//Unit &ru = (Unit &)(Object &)a[i];
		//Unit u = (Unit &)(Object &)a[i];

		//Godot::print(String::num(i)+n->get_position());
		//((Unit *)(Object *)a[i])->selected = true;

		up->selected = true;
		n->set("selected",  true);
		//a[i] = (Variant *)(Object *)up;
		//ru.selected = true;
		//u.selected = true;

		//u->owner->set("selected", true);
		label->set_text("Selected Unit "+String::num(i+1));
		owner->set_global_position(n->get_global_position());

	}

}

void CameraMovement::directional_edge(InputEvent *ie) {

	Label *label = (Label *)owner->get_node("Label");

	const Vector2 VEC2_ZERO = Vector2(0, 0);
	Vector2 direction = Vector2(0, 0);

	InputEventMouse *iem = (InputEventMouse *)ie;
	Vector2 iem_pos = iem->get_position();

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
	label->set_text(iem_pos);

}
