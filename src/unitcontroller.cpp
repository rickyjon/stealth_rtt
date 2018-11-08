#include "unitcontroller.h"
#include "unit.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>

#include <CoreTypes.hpp>
#include <InputMap.hpp>
#include <Sprite.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>
#include <AStar.hpp>
#include <Color.hpp>
#include <RayCast2D.hpp>
#include <Physics2DDirectSpaceState.hpp>
#include <World2D.hpp>
#include <Dictionary.hpp>
#include <CollisionShape2D.hpp>
using namespace godot;

void UnitController::_register_methods() {

	//register_method((char *)"_process", &UnitController::_process);
	register_method((char *)"_physics_process", &UnitController::_physics_process);
	register_method((char *)"_ready", &UnitController::_ready);
	register_method((char *)"_input", &UnitController::_input);

}

UnitController::UnitController() {

	selected_units = Array();

}

UnitController::~UnitController() {}

void UnitController::_process(float delta) {}

void UnitController::_physics_process(float delta) {

	spawn_raycast(delta);

}

void UnitController::_ready() {

	//point_b = owner->get_global_position();
	owner->set_physics_process(false);

}


void UnitController::_input(Variant event) {

	const int LEFT_CLICK = 1;
	const int RIGHT_CLICK = 2;
	InputEvent *ie = (InputEvent *)(Object *)event;

	//Godot::print(owner->get_parent()->get_name()
	//		+" IS SELECTED: "+String::num(selected));

	//if (ie->get_class() == "InputEventMouseButton") {
		//Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
		//Unit *u = (Unit *)(Object *)a[0];
		//int index = a.find((Variant *)(Object *)this);
		//if (index != -1) {
			//Unit *u = (Unit *)(Object *)a[index];
	if (ie->get_class() == "InputEventMouseButton") {

		InputEventMouseButton *iemb = (InputEventMouseButton *)ie;
		int index = iemb->get_button_index();
		//Godot::print(String("Pressed mouse: ")+String::num(index));
		//get_move_cursor_position(ie);

		switch (index) {
			case LEFT_CLICK:
				move_raycast(ie);
				break;
			case RIGHT_CLICK:
				move_unit(iemb);
				break;
		}

	}
	//}

}

void UnitController::set_selected_units(Array u) {
	selected_units = u;
	//UnitController::selected_units = u;
}

void UnitController::set_selected_units(Unit *u) {
	Array a = Array();
	a.append((Variant *)(Object *)u);
	//UnitController::selected_units = a;
	selected_units = a;
}

Array UnitController::get_selected_units() {

//	return UnitController::selected_units;
	return selected_units;

}

void UnitController::move_unit(InputEventMouseButton *iemb) {

	//Label *label = (Label *)owner->get_node("Label");
	Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
	/*Camera2D *c = ((Camera2D *)owner->get_parent()->get_parent()
					->get_node("Camera2D"));*/

	int i = 0;
	int l = a.size();

	while (i < l) {

		Unit *up = (Unit *)(Object *)a[i];
		Area2D *n = (Area2D *)(Object *)a[i];

		Godot::print(String::num(i));
		if (n->get("selected")) {
			n->call("get_move_cursor_position", iemb->get_global_position());
		} else {
			//n->call("get_move_cursor_position", iemb);
		}

		++i;

	}

}

void UnitController::move_unit(Vector2 v) {

	//Label *label = (Label *)owner->get_node("Label");
	Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
	/*Camera2D *c = ((Camera2D *)owner->get_parent()->get_parent()
					->get_node("Camera2D"));*/

	int i = 0;
	int l = a.size();

	while (i < l) {

		Unit *up = (Unit *)(Object *)a[i];
		Area2D *n = (Area2D *)(Object *)a[i];

		if (n->get("selected")) {
			n->call("get_move_cursor_position", v);
		} else {
			//n->call("get_move_cursor_position", iemb);
		}

		++i;

	}


}

void UnitController::move_raycast(InputEvent *ie) { //TODO: rename this

	Vector2 a = ((Vector2)owner->get_viewport()->get("size"))/Vector2(2, 2);
	InputEventMouseButton *iemb = (InputEventMouseButton *)ie;

	if (iemb->get_button_index() == 1) {

		Vector2 target = iemb->get_global_position()-a;
		Camera2D *c = (Camera2D *)owner->get_node("Camera2D");
		RayCast2D *rc = (RayCast2D *)owner->get_node("RayCast2D");

		target = c->get_global_position()+target;
		point_b = target;
		rc->set_global_position(point_b);
		rc->set_rotation(0);

		//owner->set_process(true);
		owner->set_physics_process(true);

	}

}

void UnitController::spawn_raycast(float delta) {
	/*
 	TODO: spawn four raycasts, left to right -> up and down
	northwest to southeast, northeast to southwest. it's no circle,
	but it should do the job.
	no wait shoot 8 raycasts, use cos -sin, move the angle by 45degrees
	45*8=360 and it should do the work
	TODO: alternate between left click & right click to move LOAD FROM CONFIG
	FILE
	*/
	bool flag = false;
	Camera2D *c = (Camera2D *)owner->get_node("Camera2D");
	//Label *label = (Label *)owner->get_node("Node2D")->get_node("Label");
	Label *label = (Label *)owner->find_node("Label");

	Vector2 start = point_b; //c->get_global_position();
	Vector2 end = point_b+Vector2(0, 50);

	Physics2DDirectSpaceState *space = (Physics2DDirectSpaceState *)
		c->get_world_2d()->get_direct_space_state();
	Dictionary dic = (Dictionary ) space->intersect_ray(start, end);

	if (dic.size() == 0) {
		label->set_text("No Target, Move Instead");
		move_unit(point_b);
		owner->set_physics_process(false);
	} else {
		Array arr_val = dic.values();
		Array arr_key = dic.keys();
		Variant vp = (Variant )arr_val[3];
		Object *op = (Object *)arr_val[3];

		Array node_arr = owner->get_tree()->get_nodes_in_group("unit_squad");

		label->set_text(String("Target Get: ")+op->get_class());

		int k = 0;
		int l = node_arr.size();

		while(k < l) {
			Unit *up = (Unit *)(Object *)node_arr[k];
			Area2D *n = (Area2D *)(Object *)node_arr[k];

			n->set("selected", false);
			n->set_process_input(false);

			++k;
		}

		Area2D *a = (Area2D *)(Object *)arr_val[3];
		a->set("selected", true);
		//a->set("show", false);
		k=0;
		while(k < l) {
			Unit *up = (Unit *)(Object *)node_arr[k];
			Area2D *n = (Area2D *)(Object *)node_arr[k];

			n->set_process_input(true);

			++k;
		}
	}
	owner->set_physics_process(false);

}

/*
void UnitController::check_objects_in_raycast(float delta) { //TODO: delete

	RayCast2D *rc = (RayCast2D *)owner->get_node("RayCast2D");
	Label *label = (Label *)rc->get_node("Label");
	const int DEG_MAX = 359;

	if (rc->get_rotation_degrees() < DEG_MAX) {

		rc->set_rotation_degrees(rc->get_rotation_degrees()+360*delta);
		label->set_text(String::num_real(rc->get_rotation_degrees()));

		if (rc->is_colliding()) {

			Object *o = rc->get_collider();
			owner->set_process(false);
		}

	} else {

		owner->set_process(false);

	}

}
*/


Vector3 UnitController::vec_vec(Vector2 *a) {

	return Vector3(a->x, a->y, 0);

}

Vector3 UnitController::vec_vec(Vector2 a) {

	return Vector3(a.x, a.y, 0);
}

Vector2 UnitController::vec_vec(Vector3 a) {

	return Vector2(a.x, a.y);

}
