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

using namespace godot;

void UnitController::_register_methods() {

	register_method((char *)"_process", &UnitController::_process);
	register_method((char *)"_ready", &UnitController::_ready);
	register_method((char *)"_input", &UnitController::_input);

}

UnitController::UnitController() {

	selected_units = Array();

}

UnitController::~UnitController() {}


void UnitController::_process(float delta) {

	//move_to(point_b);

}

void UnitController::_ready() {

	//point_b = owner->get_global_position();
	//selected = false;
	//selected = !selected;
	//selected = true;
	//owner->set_process(true);

}


void UnitController::_input(Variant event) {

	InputEvent *ie = (InputEvent *)(Object *)event;

	//Godot::print(owner->get_parent()->get_name()
	//		+" IS SELECTED: "+String::num(selected));

	//if (ie->get_class() == "InputEventMouseButton") {
		//Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
		//Unit *u = (Unit *)(Object *)a[0];
		//int index = a.find((Variant *)(Object *)this);
/*
		Godot::print(owner->get_parent()->get_name()
			+ owner->get("selected")
			+" IS SELECTED: "+String::num(selected)
			+String::num(index)
			);//+", OPEN_ARRAY SIZE:"+open_arr.size());
			*/
		//if (index != -1) {
			//Unit *u = (Unit *)(Object *)a[index];
		//if (owner->get("selected")) {
		if (ie->get_class() == "InputEventMouseButton") {
			//Godot::print("now this is epic");
			//get_move_cursor_position(ie);
		//	}
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


void UnitController::get_move_cursor_position(InputEvent *ie) { //redo this

	//owner->set_input_handled();
	Vector2 a = ((Vector2)owner->get_viewport()->get("size"))/Vector2(2, 2);

	InputEventMouseButton *iemb = (InputEventMouseButton *)ie;
	if (iemb->get_button_index() == 1) {
		
		Vector2 target = iemb->get_global_position()-a;
		Camera2D *c = (Camera2D *)owner->get_tree()->get_root()
			->find_node("Camera2D");

		target = c->get_global_position()+target;
		//todo: multi moving
		//Array a =
		Godot::print(selected_units.size());
		//if (a.size() != 0) {
		//Unit *u = (Unit *)(Object *)a[0];
		/*
		Node2D *n = (Node2D *)u;

		u->point_b = target;
		/**/
		Godot::print("epic");
		//}
		//Godot::print(point_b);

		//n->set_process(true);
		//owner->set_process(true);
	}

}

void UnitController::move_to(Vector2 point_b) {

	Unit *u = (Unit *)(Object *)get_selected_units()[0];
	Node2D *n = (Node2D *)u;
	Sprite *s = (Sprite *)n->get_node("Sprite");
	//Sprite *s = (Sprite *)owner->get_parent()->get_node("MoveCursor");

	//Label *a = (Label *)owner->get_node("Label");

	Vector2 pos = n->get_position();
	const int leeway = 20;
	float deg = pos.angle_to_point(point_b)*180/3.141; //angle to degrees
	Vector2 spd = (pos+Vector2(cos(-deg), -sin(-deg)));

	s->set_position(point_b);

	//s->set_global_position(point_b);
	//owner->set_position(point_b);

	//leeway
	bool flag_x = (pos.x > point_b.x-leeway && pos.x < point_b.x+leeway);
	bool flag_y = (pos.y > point_b.y-leeway && pos.y < point_b.y+leeway);

	if (flag_x && flag_y) {
		//owner->set_process(false);
	} else {
		//owner->set_position(spd);
		//owner->look_at(point_b);
		//owner->update();
	}

}
/*
Array UnitController::get_points() {

	//Array maximum = owner->get_tree()->get_root()
	//	->get_node("Map")->get("Boundry");
	Array points = maximum;
	points.clear();
	int i = 0;
	int k = 0;
	int l = ((Vector2 *)(Object *)maximum[0])->x;
	int p = ((Vector2 *)(Object *)maximum[0])->y;
	//y
	while(i < l) {
		points.append(Vector2(i, 0));
		//x
		while(k < p) {
			points.append(Vector2(i, k));
			++k;
		}
		++i;
	}

	return points;

}

void UnitController::find_path() {
//make every level have a set boundary
	AStar *as = new AStar();

	int i = 0;
	int l = 0;
	Array points = get_points();
	l = points.size();

	while(i < l) {
		as->add_point(i, vec_vec((Vector2 *)(Object *)points[i]));
		++i;
	}
	//as->add_point(1, vec_vec(owner->get_position()));
	//as->add_point(2, vec_vec(point_b));

	as->connect_points(1, 2, false);

	PoolVector3Array pv3a = as->get_point_path(1, 2);
	//Godot::print(as->get_point_path(1, 2));

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
